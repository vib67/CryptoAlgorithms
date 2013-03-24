// GF(2^1279) = GF(2)[x]/(x^1279 + x^319 + x^127 + x^63 + 1)
#include <string.h>
#include <stdio.h>
#include "gf2m.h"

void ff_rnd(ff_t a) {
	FILE* urandom = fopen("/dev/urandom", "r");
	size_t bytes_read = fread(a, NUMWORDS, sizeof(uint32_t), urandom);
	fclose(urandom);
	a[NUMWORDS-1] &= 0x7FFFFFFF;
}

void ff_print(ff_t a) {
	for(int i=NUMWORDS-1; i>=0; i--) printf("%08X ", a[i]);
	printf("\n");
}

void ff_print_poly(ff_t a) {
	for(int i=0; i<NUMWORDS; i++)
		for(int j=0; j<32; j++)
			if(a[i] >> j & 1)
				printf("+x^%d", i*32+j);
	printf("\n");
}

/*
calculate the adiition modulo GF(2^1279) 
@pram     a:first 1279 bit number 
          b: second 1279 bit number
          c: output of addition 
*/
void ff_add(ff_t c, const ff_t a, const ff_t b) {
int i;        //add modulo GF(2^1279)
for (i=0;i<NUMWORDS;i++)
   c[i] = a[i] ^ b[i];
}

/*
calculates the multiplication of a and b modulo GF(2^1279)
@param c: output of a*bmodulo GF(2^1279)
       a: first 1279 bit number 
       b: second 1279 bit number
       
      

*/

void ff_mul(ff_t c, const ff_t a, const ff_t b) {

ff_t  tempb; 
ff_t tempres;
unsigned int msb=0,temp,checkbit=1; 
int i,j,k=0;
int bitinx=0;
 
      //b is const so take a working copy of it 
    ff_copy(tempb,b);

    if(a[0]&0x00000001)   //check lsb of number a
    {
      for (i=0;i<40;i++)
      
         //if lsb is 1 then c <-- b
    ff_copy(tempres,tempb);  
    }
   else
   {
    for (i=0;i<NUMWORDS;i++)
             //else make c <-- 0
      ff_zero(tempres);
   }



for (i = 0; i<NUMWORDS;i++)
{  
   if(i==0)   //reinitialize the checkbit and bitinx for the next word!!
    {checkbit =1;bitinx =1;}
    else
    {checkbit =1;bitinx = 0;}
              
  for(;bitinx<32;bitinx++)
   {
   for(j=NUMWORDS-1 ;j>=0;j--)   //multiply b by 2 
    {
     msb = 0;
     if(j !=0)      //take the msb of the word and transer to the next word !!
      msb = tempb[j-1] & 0x80000000;
     tempb[j] = tempb[j]<< 1; //multiply by 2
     if(msb) //transfer to the next word
       tempb[j]= tempb[j]|0x00000001;

     
    }  
  
     if(tempb[39] & 0x80000000) //check the 1279 bit , if crosses then xor it with the polynomial
    
      {
       tempb[39] = tempb[39] ^ 0x80000000;
       tempb[9]  = tempb[9]  ^ 0x80000000;
       tempb[3]  = tempb[3]  ^ 0x80000000;
       tempb[1]  = tempb[1]  ^ 0x80000000;
       tempb[0]  = tempb[0]  ^ 0x00000001;
      }
     if(a[i]&(checkbit<<bitinx))  //check whether a[i] is 1 
     {
          for (j=0;j<NUMWORDS; j++)
             //changed
              tempres[j] = tempres[j] ^ tempb[j];
             //ff_add(tempres,tempres,tempb);
             
     }       
   }  
 }
// 
 /*copy the resul to the output */
 /*tempres was taken because in some cases the call can be made for this function with the same three
    word memeory location , to avoid some kind of surprises I have taken a working copy of the result
*/
ff_copy(c,tempres);
// ff_print( c);


}


/*
calcualtes the exponent of two numbers  the a^b modulo GF(2^1279), 
@param : c output of the a^b modulo GF(2^1279)
       : a expressed in 1279 bit   
       : b expressed in 1279 bit 
algorithm is  Left-to-right binary exponentiation

INPUT: g element of G and a positive integer e = (et et-1 · · · e1 e0 )2 .
OUTPUT: g^e .
  1. A<--1.
  2. For i from t down to 0 do the following:
      2.1 A<- -A * A.
      2.2 If ei = 1, then A<-A * g.
  3. Return(A).


*/
void ff_exp(ff_t c, const ff_t a, const ff_t b) {


  int i,j,k=0;
  unsigned  int temp,checkbit;
  ff_t res,tempres ; 
  /**/
  ff_zero(c);
  ff_zero(res);
  res[0]= 1; //make the res to 1
  for (i=39;i>=0;i--)
      { 
       checkbit = 2147483648;  //2^31
       for(k=0;k<32;k++)
        {  
          
                                 //calculate res <-- res*res
           ff_mul(tempres,res,res); 
           ff_copy(res,tempres); //tempres is taken to avoid surprises of res becoming 0 above!!

                                      //check whether b is 1
          if(b[i] & (checkbit >> k ))
            { 
             
              ff_zero(tempres);      //res <-- res*a
              ff_mul(tempres,res,a);
              ff_copy(res,tempres);  //
            }
        }  
      }
         
         /*copy the res to the output */
   ff_copy(c,res);

      
}


