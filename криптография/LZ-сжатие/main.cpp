#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STR_FILE_IN_NAME "input.txt"
#define STR_FILE_OUT_NAME "output.txt"
#define BITS_IN_CODE 12
#define TABLE_SIZE 4095

int CompressFile(FILE *f_in, FILE *f_out);
int DecompressFile(FILE *f_in, FILE *f_out);
int SearchInStringTable(int *iPrefixCode, unsigned char *cCharacter, int iNumberOfCodes, int iSearchingPrefixCode, unsigned char cSearchingCharacter);
int OutputCode(FILE *f_out,int iCode);
int InitializeStringTable(int *iaPrefixCode, unsigned char *caCharacter);
int GetNextCodeFromFile(FILE *f_in);
int OutputStringForCode(int *iPrefixCode, unsigned char *cCharacter, FILE *f_out,int iCurrentCode);
unsigned char GetFirstCharacterForCode(int *iPrefixCode,unsigned char *cCharacter, int iCurrentCode);
bool bAll=false;

int main(int argc, char* argv[])
{
   char sFInName[256]=STR_FILE_IN_NAME, sFOutName[256]=STR_FILE_OUT_NAME, *pNothingDo;
   FILE *f_in, *f_out;
   char cRead;
   // .::Reading of the Command StrinG::.
   if(argc>1){
      if((argv[1][0]=='-')&&(argv[1][1]=='l')&&(argv[1][2]=='\0')){
         bAll=true;
      } else if((argv[1][0]=='-')&&(argv[1][1]=='c')&&(argv[1][2]=='\0')){
         cRead='c';
      } else if((argv[1][0]=='-')&&(argv[1][1]=='d')&&(argv[1][2]=='\0')){
         cRead='d';
      } else {
         bAll=true;
      }
      if(argc>2) pNothingDo=strcpy(sFInName,argv[2]);
      else bAll=true;
      if(argc>3) pNothingDo=strcpy(sFOutName,argv[3]);
      else bAll=true;
   } else {
      bAll=true;
   }
   // .::-----------------------------::.
   // .::Keyboard inpuT::.
   if(bAll){
      printf("Enter the first letter of the operation (c - compressing; d - decompressing):");
      scanf("%c",&cRead);
      printf("Enter name of Input File:\n");
      scanf("%s",sFInName);
      printf("Enter name of Output File:\n");
      scanf("%s",sFOutName);
   }
   // .::--------------::.
   f_in=fopen(sFInName,"rb");
   f_out=fopen(sFOutName,"wb");
   if (cRead!='c' && cRead!='d'){
      printf("Error: can't recognize this operation!..\n");
      if(bAll) scanf("%c", &cRead);
      return -1;
   }
   if (!f_in){
      printf("Error: can't open file with name %s!..\n", sFInName);
      if(bAll) scanf("%c", &cRead);
      return -1;
   }
   if (!f_out){
      printf("Error: can't open file with name %s!..\n", sFOutName);
      if(bAll) scanf("%c", &cRead);
      return -1;
   }
   if (cRead=='c')
      if(CompressFile(f_in, f_out)>=0){
         printf("Compressing finished successfully!\n");
      } else {
         printf("Compressing finished UNsuccessfully!\n");
      }
   if (cRead=='d')
      if(DecompressFile(f_in, f_out)>=0){
         printf("Decompressing finished successfully!\n");
      } else {
         printf("Decompressing finished UNsuccessfully!\n");
      }
   fclose(f_in);
   fclose(f_out);
   return 0;
}

int CompressFile(FILE *f_in, FILE *f_out)
{
   // .::String tablE::.
   int *iPrefixCode = new int[TABLE_SIZE];
   unsigned char *cCharacter = new unsigned char[TABLE_SIZE];
   // .::------------::.
   int iCurrentPrefixCode = -1;
   unsigned char cCurrentCharacter;
   int iNumberOfCodes = 0;
   int iReturnCode;
   int iCounter=0, iKbCounter=0;
   // .::Initializing of string tablE::.
   iNumberOfCodes=InitializeStringTable(iPrefixCode, cCharacter);
   // .::----------------------------::.
   // .::CompressioN::.
   // .::Begin of compressioN::.
   if(OutputCode(f_out,-2)<0) {
      delete [] iPrefixCode;
      delete [] cCharacter;
      return -1;
   }
   // .::--------------------::.
   while(fscanf(f_in, "%c", &cCurrentCharacter)==1){
      // .::Kb-counter::.
      iCounter++;
      if(iCounter>=1024){
         iKbCounter++;
         iCounter-=1024;
         printf("%10d Kb compressed...\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r", iKbCounter);
      }
      // .::----------::.
      if ((iReturnCode=SearchInStringTable(iPrefixCode, cCharacter, iNumberOfCodes, iCurrentPrefixCode, cCurrentCharacter))>=0){
         iCurrentPrefixCode=iReturnCode;
      } else {
         iPrefixCode[iNumberOfCodes]=iCurrentPrefixCode;
         cCharacter[iNumberOfCodes]=cCurrentCharacter;
         iNumberOfCodes++;
         if(OutputCode(f_out,iCurrentPrefixCode)<0) {
            delete [] iPrefixCode;
            delete [] cCharacter;
            return -1;
         }
         iCurrentPrefixCode=(unsigned int)cCurrentCharacter;
      }
      if(iNumberOfCodes>=TABLE_SIZE){
         if(OutputCode(f_out,iCurrentPrefixCode)<0) {
            delete [] iPrefixCode;
            delete [] cCharacter;
            return -1;
         }
         iCurrentPrefixCode = -1;
         // .::Outputting of the code for overflowing of string tablE::.
         if(OutputCode(f_out,TABLE_SIZE)<0) { // code for overflowing of string tablE = (TABLE_SIZE-1)+1;
            delete [] iPrefixCode;
            delete [] cCharacter;
            return -1;
         }
         // .::------------------------------------------------------::.
         // .::Reinitializing of string tablE::.
         iNumberOfCodes=InitializeStringTable(iPrefixCode, cCharacter);
         // .::------------------------------::.
      }
   }
   if(OutputCode(f_out,iCurrentPrefixCode)<0) {
      delete [] iPrefixCode;
      delete [] cCharacter;
      return -1;
   }
   // .::End of compressioN::.
   if(OutputCode(f_out,-1)<0) {
      delete [] iPrefixCode;
      delete [] cCharacter;
      return -1;
   }
   // .::------------------::.
   // .::----------::.
   delete [] iPrefixCode;
   delete [] cCharacter;
   return 0;
}
int DecompressFile(FILE *f_in, FILE *f_out)
{
   // .::String tablE::.
   int *iPrefixCode = new int[TABLE_SIZE];
   unsigned char *cCharacter = new unsigned char[TABLE_SIZE];
   // .::------------::.
   int iNumberOfCodes = 0;
   int iCurrentPrefixCode = -1;
   int iCurrentCode;
   int iOldCode;
   unsigned char cCurrentCharacter;
   int iCounter=0, iKbCounter=0;
   iNumberOfCodes=InitializeStringTable(iPrefixCode, cCharacter);
   iCurrentCode=GetNextCodeFromFile(f_in);
   if(OutputStringForCode(iPrefixCode, cCharacter, f_out, iCurrentCode)<0) {
      delete [] iPrefixCode;
      delete [] cCharacter;
      return -1;
   }
   iOldCode=iCurrentCode;
   while((iCurrentCode=GetNextCodeFromFile(f_in))>=0){
      // .::Kb-counter::.
      iCounter++;
      if(iCounter>=((1024*8)/BITS_IN_CODE)){
         iKbCounter++;
         iCounter-=((1024*8)/BITS_IN_CODE);
         printf("%10d Kb decompressed...\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r", iKbCounter);
      }
      // .::----------::.
      if(iCurrentCode==TABLE_SIZE){
         iNumberOfCodes=InitializeStringTable(iPrefixCode, cCharacter);
         iCurrentCode=GetNextCodeFromFile(f_in);
         // .::Kb-counter::.
         iCounter++;
         if(iCounter>=((1024*8)/BITS_IN_CODE)){
            iKbCounter++;
            iCounter-=((1024*8)/BITS_IN_CODE);
            printf("%10d Kb decompressed...\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r", iKbCounter);
         }
         // .::----------::.
         if(iCurrentCode<0) break ;
         if(OutputStringForCode(iPrefixCode, cCharacter, f_out, iCurrentCode)<0) {
            delete [] iPrefixCode;
            delete [] cCharacter;
            return -1;
         }
         iOldCode=iCurrentCode;
      } else {
         if(iCurrentCode<=iNumberOfCodes-1){
            if(OutputStringForCode(iPrefixCode, cCharacter, f_out, iCurrentCode)<0) {
               delete [] iPrefixCode;
               delete [] cCharacter;
               return -1;
            }
            iCurrentPrefixCode=iOldCode;
            cCurrentCharacter=GetFirstCharacterForCode(iPrefixCode, cCharacter, iCurrentCode);
            iPrefixCode[iNumberOfCodes]=iCurrentPrefixCode;
            cCharacter[iNumberOfCodes]=cCurrentCharacter;
            iNumberOfCodes++;
            iOldCode=iCurrentCode;
         } else {
            iCurrentPrefixCode=iOldCode;
            cCurrentCharacter=GetFirstCharacterForCode(iPrefixCode, cCharacter, iCurrentPrefixCode);
            iPrefixCode[iNumberOfCodes]=iCurrentPrefixCode;
            cCharacter[iNumberOfCodes]=cCurrentCharacter;
            iNumberOfCodes++;
            if(OutputStringForCode(iPrefixCode, cCharacter, f_out, iNumberOfCodes-1)<0) {
               delete [] iPrefixCode;
               delete [] cCharacter;
               return -1;
            }
            iOldCode=iCurrentCode;
         }
      }
   }
   delete [] iPrefixCode;
   delete [] cCharacter;
   return 0;
}
// .::Is the code for string (==prefix+character) in string table, when compressinG::.
int SearchInStringTable(int *iPrefixCode, unsigned char *cCharacter, int iNumberOfCodes, int iSearchingPrefixCode, unsigned char cSearchingCharacter)
{
   int i = 0;
   while(i<iNumberOfCodes){
      if ((iPrefixCode[i]==iSearchingPrefixCode) && (cCharacter[i]==cSearchingCharacter)) return i;
      i++;
   }
   return -1;
}
// .::-----------------------------------------------------------------------------::.
// .::Outputting of the code to the output filE::.
int OutputCode(FILE *f_out,int iCode)
{
   static unsigned char cBuffer;
   static int iNumberOfBitsInBuffer;
   int i=0;
   int i2_in_power_NOBI=1;
   if(iCode==-2) {
      cBuffer=(unsigned char)0;
      iNumberOfBitsInBuffer=0;
      return 0;
   }
   if(iCode==-1) {
      if(iNumberOfBitsInBuffer!=0) fprintf(f_out,"%c",cBuffer);
      return 0;
   }
   if(iCode>=0) {
      while(i<iNumberOfBitsInBuffer){
         i2_in_power_NOBI*=2;
         i++;
      }
      i=0;
      while(i<BITS_IN_CODE){
         cBuffer+=i2_in_power_NOBI*(iCode%2);
         iCode/=2;
         i2_in_power_NOBI*=2;
         iNumberOfBitsInBuffer++;
         i++;
         if (iNumberOfBitsInBuffer>=8){
            fprintf(f_out,"%c",cBuffer);
            cBuffer=(unsigned char)0;
            iNumberOfBitsInBuffer=0;
            i2_in_power_NOBI=1;
         }
      }
      return 0;
   }
   return -1;
}
// .::-----------------------------------------::.
// .::Initializing of string tablE::.
int InitializeStringTable(int *iaPrefixCode,unsigned char *caCharacter)
{
   int i = 0;
   while(i<256){
      iaPrefixCode[i]=-1;
      caCharacter[i]=(unsigned char)i;
      i++;
   }
   return i;
}
// .::----------------------------::.
// .::Getting the first char from the string for codE::.
unsigned char GetFirstCharacterForCode(int *iPrefixCode, unsigned char *cCharacter, int iCurrentCode)
{
   while(iPrefixCode[iCurrentCode]>=0){
      iCurrentCode=iPrefixCode[iCurrentCode];
   }
   return (cCharacter[iCurrentCode]);
}
// .::-----------------------------------------------::.
// .::Outputting of the string for the code to the output filE::.
int OutputStringForCode(int *iPrefixCode, unsigned char *cCharacter, FILE *f_out,int iCurrentCode)
{
   if(iCurrentCode>=0){
      int iCode = iCurrentCode;
      int iLengthOfString = 0, i;
      while(iPrefixCode[iCode]>=0){
         iCode=iPrefixCode[iCode];
         iLengthOfString++;
      }
      unsigned char *sOutputtingString = new unsigned char[iLengthOfString+1];
      iCode=iCurrentCode;
      i=iLengthOfString;
      while(i>=0){
         sOutputtingString[i]=cCharacter[iCode];
         iCode=iPrefixCode[iCode];
         i--;
      }
      i=0;
      while(i<=iLengthOfString){
         fprintf(f_out,"%c",sOutputtingString[i]);
         i++;
      }
      delete [] sOutputtingString;
      return 0 ;
   } else return -1;
}
// .::--------------------------------------------------------::.
// .::Getting the next code from filE::.
int GetNextCodeFromFile(FILE *f_in)
{
   static unsigned char cBuffer;
   static int iNumberOfBitsInBuffer = 0;
   int i = 0;
   int i2_in_power_i = 1 ;
   int iCode = 0;
   while(i<BITS_IN_CODE){
      if(iNumberOfBitsInBuffer==0){
         if(fscanf(f_in, "%c", &cBuffer)!=1) return -1;
         iNumberOfBitsInBuffer=8;
      }
      iCode+=(cBuffer%2)*i2_in_power_i;
      cBuffer/=2;
      iNumberOfBitsInBuffer--;
      i++;
      i2_in_power_i*=2;
   }
   return iCode ;
}
