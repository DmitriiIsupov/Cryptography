//
//  main.cpp
//  6(Hamming code c++)
//
//  Created by Dmitrii Isupov on 12/12/2019.
//  Copyright © 2019 Mac. All rights reserved.
//

#include<iostream>
#include<cmath>
 
#include<string>

using namespace std;

 class Hamming

{
 
 string message;

 int codeword[50],temp[50];
  int n,check;
  char parity;
public:
 Hamming()
 {
     parity = 'E';
     message = "";
     n=check=0;
     for(int i=0;i<50;i++)
     {
         temp[i]=codeword[i]=0;
     }
 }
 
 void generate()
 {
     do
     {
         cout<<"Enter the message in binary : ";
         cin>>message;
     }while(message.find_first_not_of("01") != string::npos);
     n=message.size();
     cout<<"Odd(O)/Even(E) Parity ? ";
     cin>>parity;
     for(unsigned int i=0;i<message.size();i++)
     {
         if(message[i] == '1')
             temp[i+1]=1;
         else
             temp[i+1]=0;
     }
     computeCode();
 }
  void computeCode()
 {
     check = findr();
     cout<<"Number of Check Bits : "<<check<<endl;
     cout<<"Number of Bits in Codeword : "<<n+check<<endl;
     for(int i=(n+check),j=n;i>0;i--)
     {
         if((i & (i - 1)) != 0)
             codeword[i] = temp[j--];
         else
             codeword[i] = setParity(i);
     }
     cout<<"Parity Bits - ";
     for(int i=0;i<check;i++)
      cout<<"P"<<pow(2,i)<<" : "<<codeword[(int)pow(2,i)]<<"\t";
     cout<<endl;
     cout<<"Codeword :"<<endl;
     for(int i=1;i<=(n+check);i++)
         cout<<codeword[i]<<" ";
     cout<<endl;
 }
  int findr()
 {
     for(int i=1;;i++)
     {
         if(n+i+1 <= pow(2,i))
             return i;
     } }
  int setParity(int x)
 {
     bool flag = true;
     int bit;
     if(x == 1)
     {
         bit = codeword[x+2];
         for(int j=x+3;j<=(n+check);j++)
         {
             if(j%2)
             {
                 bit ^= codeword[j];
             }
         }
     }
     else
     {
         bit = codeword[x+1];
         for(int i=x;i<=(n+check);i++)
         {
             if(flag)
             {
                 if(i==x || i==x+1)
                     bit = codeword[x+1];
                 else
                     bit ^= codeword[i];
             }
             if((i+1)%x == 0)
                 flag = !flag;
         }
     }
     if(parity == 'O' || parity == 'o')
         return !bit;
     else
         return bit;
 }
       void correct()
 {
     do
     {
         cout<<"Enter the received codeword : ";
         cin>>message;
     }while(message.find_first_not_of("01") != string::npos);
     for(unsigned int i=0;i<message.size();i++)
     {
         if(message[i] == '1')
             codeword[i+1]=1;
         else
             codeword[i+1]=0;
     }
     detect();
 }
 void detect()
 {
     int position = 0;
     cout<<"Parity Bits - ";
     for(int i=0;i<check;i++)
     {
         bool flag = true;
         int x = pow(2,i);
         int bit = codeword[x];
         if(x == 1)
         {
             for(int j=x+1;j<=(n+check);j++)
             {
                 if(j%2)
                 {
                     bit ^= codeword[j];
                 }
             }
         }
         else
         {
             for(int k=x+1;k<=(n+check);k++)
             {
                 if(flag)
                 {
                     bit ^= codeword[k];
                 }
                 if((k+1)%x == 0)
                     flag = !flag;
             }
         }
         cout<<"P"<<x<<": "<<bit<<"\t";
         if((parity=='E' || parity == 'e') && bit==1)
             position += x;
         if((parity=='O' || parity == 'o') && bit==0)
             position += x;
     }
     cout<<endl<<"Received Codeword :"<<endl;
     for(int i=1;i<=(n+check);i++)
         cout<<codeword[i]<<" ";
     cout<<endl;
     if(position != 0)
     {
         cout<<"Error at bit : "<<position<<endl;
         codeword[position] = !codeword[position];
         cout<<"Corrected Codeword : "<<endl;
         for(int i=1;i<=(n+check);i++)
             cout<<codeword[i]<<" ";
         cout<<endl;
     }
     else
         cout<<"No Error in Received code."<<endl;
     cout<<"Received Message is : ";
     for(int i=1;i<=(n+check);i++)
         if((i & (i - 1)) != 0)
             cout<<codeword[i]<<" ";
     cout<<endl;
 }
};
 int main()
{
 char choice;
 do
 {
     Hamming a;
     cout<<"At Sender's side : "<<endl;
     a.generate();
     cout<<endl<<"At Receiver's Side : "<<endl;
     a.correct();
     cout<<endl<<"Enter another code ? (Y/N) : ";
     cin>>choice;
     cout<<endl;
 }while(choice == 'y' || choice == 'Y');
 return 0;
}
