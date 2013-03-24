// GF(2^1279) = GF(2)[x]/(x^1279 + x^319 + x^127 + x^63 + 1)
#include <string.h>
#include <stdio.h>
#include "gf2m.h"

// TODO: drop in your stuff old stuff where applicable (or vice-versa)


#define CLOCK(x) (x >> 8 | (x ^ (x >> 7) ^ (x >> 6) ^ (x >> 2)) << 24)
//void shiftleft(ff_t res, ff_t v, int shift);
//int degree(ff_t p);
// don't modify this fxn
void ff_rnd(ff_t a) {
	static uint32_t s = 0xFEEDFACE;
	unsigned char *p = (unsigned char *)a;
	for(int i=0; i<NUMWORDS * sizeof(uint32_t); i++, s=CLOCK(s)) p[i] = (unsigned char)s;
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

/* c = a + b */
void ff_add(ff_t c, const ff_t a, const ff_t b) {

}

/* c = a * b */
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

/* c = b^e */
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

/* store the inverse of a in c; implement the extended Euclidean algorithm */

void ff_inv(ff_t c, const ff_t a) {
ff_t u,v,res,cc,bb,t;
int i,j;
char ch;
ff_zero(bb); ff_zero(cc) ;  //cc<--0
//bb<--- 1
bb[0] =1; 
ff_copy(u,a);ff_zero(v);  
v[39] =  0x80000000;  //v<---f
v[9]  =  0x80000000;
v[3]  =  0x80000000;
v[1]  =  0x80000000;
v[0]  =  0x00000001;

for(;degree(u);)   //run the diviosn till the degree is 0 i.e u is 1
  { 
     
   j = degree(u) - degree(v);
//   printf("deg U = %d  deg V = %d \n" , degree(u) , degree(v)); 
    if(j<0)
      {
        j = -j; 
        
        ff_copy(t,u);  //Swap u and v
        ff_copy(u,v);
        ff_copy(v,t);
        
        
        ff_copy(t,bb); //swap bb and cc
        ff_copy(bb,cc);
        ff_copy(cc,t);
        
      }
       
       
      shiftleft(res,v,j);       //shift left v by j bits    
      
      for(i=0;i<NUMWORDS ;i++)   //it is actually dividing u by  v, res <-- 2^j*v  
          u[i] = u[i] ^ res[i];   //xoring clears the top bit every time and other matching bits also
     
      shiftleft(res,cc,j);  //shift left cc by j bits  
      
      for(i=0;i<NUMWORDS ;i++)     
         bb[i] = bb[i]^ res[i];   //same as above ,just that bb will contain the inverse after u is 1 
    
                         
    }
    
    ff_copy(c,bb);
    /*printf(" printing c \n\n\n");
    ff_print(c);*/
}

/*Shift the word by shift bits  */

void shiftleft(ff_t res, ff_t v, int shift)
{

   int t =  shift/32,i,j;
 
  ff_t a;
  ff_copy(a,v);
  ff_zero(res); 

  if(shift ==0)  //if no shift then copy the v to res
   {
    ff_copy(res,v);
    return;

  }

  for(j=NUMWORDS-1;j>=0;j--)  //if shift >=32 bits then directly shift the wotd bt shift/32 positions left
   {   if((j-t) >= 0 )
         a[j] =  a[j-t];
       else
        a[j] =0x0;
   }

 if(shift%32)  //Caution !! only when remainder is != 0
 {
  for(j=NUMWORDS-1;j>=0;j--)
  {
   if(j != 0)    //spill the bits to next word by shift%32 bits
  {
    a[j] = (a[j]<< (shift%32)) | (a[j-1] >> (32-(shift%32)))  ;
  }
  else  //for 0th word 
   a[j] = a[j] << (shift%32);

  }
}
 ff_copy(res, a);

} 
/*find the highest degree of polynomial ,nothing but what is the msb position of the word */
int degree(ff_t p)
{
    int i,j;
    unsigned long int checkbit;
    for(i=NUMWORDS-1;i>=0;i--)
     {  checkbit = 0x80000000;  //start from the msb itself
       for(j=31;j>=0;j--)
         if( p[i] & checkbit)   
         {   
              return (j+ i*32);   
         }
         else
         {
             checkbit=checkbit>> 1; //go for next bit 
         }
            
                              }
                              return 0;
}


/* generate a private key and corresponding public key. call to ff_rnd for randomness */
void ff_keygen(ff_t private, ff_t public) {
ff_t t0, gen;
ff_rnd(t0);
ff_zero(gen);

gen[0] = 0x2;
ff_exp(public, gen , t0);  //calulate public key <-- 2^k0
ff_copy(private,t0);   //private key is t0

}



/* 
   encrypt message m of length len under public key public, placing result in c
   you can assume m has exactly len bytes allocated.
   you can assume c has exactly 320 bytes allocated.
*/

void ff_encrypt(unsigned char *c, unsigned char *m, int len, const ff_t public) {
   int i,k=0;
   ff_t pkdword,k0,gen,res,res1,msg;
   
   unsigned char tempmsg[160],*tempc;
   if(len<1 || len> 158)  //check for length constraint
      {
            printf("length of the message is not proper, please have it between 1 to 158\n");
             return;
      }
   ff_zero(gen);
   ff_zero(pkdword);
   memcpy(tempmsg,m,len); //copy into temp variable
   //memcpy(pkdword,m,len);
   gen[0]= 0x2; //generator is ready
   
   for(i=len; i<159;i++) //pad the message
       tempmsg[i] = 159-len; 
   tempmsg[i] = 0x0;
   
   for(i=0;i<160;i+=4) //pack the message into 32 bit 40 words
    { 
      pkdword[k++] = tempmsg[i] + 256*tempmsg[i+1] + 256*256*tempmsg[i+2] +256*256*256*tempmsg[i+3];
    }
    
  /* printf("message to encrypted is \n");
   ff_print(pkdword);*/
 
   ff_rnd(k0); 
   
   
   ff_zero(res); 
   ff_exp(res,gen, k0);  //Calculate Y <-- 2^k0 
   memcpy(c,res, NUMWORDS*4);
   /*printf ("c_1  in encryption is  \n");
   ff_print(res); */
   
   tempc = (unsigned char *) res;
   tempc = tempc+159;  //take it to msb
   for(i=0;i<160 ; i++)   //populate the ciphet text first 160 bytes has to be from Y 
   {
     c[i] = *tempc  ;
     tempc--;
   }
   ff_exp(res,public,k0);   //calculate (2^public)^k0

   ff_mul(res1,pkdword,res);  //calculate pkdword*(2^public)^k0  ,actual encryption of the message
  
  
   tempc = (unsigned char *) res1;
   tempc = tempc+159;
   for(i=0;i<160 ; i++)   //put the c_2 in right order !!
   {   
     c[160+i] = *tempc  ;
     tempc--;
   }

  
}

/* 
   decrypt message c using private key private, placing result in b and
   returning the number of bytes in the result
   you can assume b has exactly 160 bytes allocated.
   you can assume c has exactly 320 bytes allocated.
*/
int ff_decrypt(unsigned char *b, unsigned char *c, const ff_t private) {

  unsigned char *temp;
  ff_t c_1,c_2,p,res;
  int i,j,pad;
 

  /*printf("1st half cipher text is \n");
  for(i=0;i<160;i++) 
   printf("%x\t",c[i]);*/



  for (i=NUMWORDS-1,j=0;i>=0;i--,j+=4)   //get the C_1 (Y) in right order !!
    c_1[i] = c[j]*256*256*256+c[j+1]*256*256+c[j+2]*256+ c[j+3];           
  




  /* printf("second half cipher text is \n");
   for(i=160;i<320;i++) 
      printf("%x\t",c[i]);*/





   for (i=NUMWORDS-1,j=160;i>=0;i--,j+=4) //similarly get the actual encrypted message in right order !!
    c_2[i] = c[j]*256*256*256+c[j+1]*256*256+c[j+2]*256+ c[j+3];

 
  
  
  ff_exp(res,c_1, private);  // Y^private
  ff_inv(p,res);      // Y^(-private)
  ff_mul(res,c_2,p);  //c_2*p <=> m*Y^(-private)


  
   ff_copy(b,res);  //copy the resul to o/p
   temp = (unsigned char*) b; 
  
  return (159 - *(b+158));  //return the lenght of the message 159-pad(stored at 158th byte of the message)

}



