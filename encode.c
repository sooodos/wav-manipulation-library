/*
*encode.c Implemantation of wav decode algorithm.
*Copyright (C) 2018  Sotiris Loizids
* 
*This program is free software: you can redistribute it and/or modify
*it under the terms of the GNU General Public License as published by
*the Free Software Foundation, either version 3 of the License, or
*at your option) any later version. 
* 
*This program is distributed in the hope that it will be useful,
*but WITHOUT ANY WARRANTY; without even the implied warranty of
*MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*GNU General Public License for more details. 
* 
*Υou should have received a copy of the GNU General Public License
*along with this program.  If not, see <http://www.gnu.org/licenses/>. 
*/
/** @file encode.c
*	 @brief implementation of encoding strategy for a wav file
* 
* encode.c is responsible for taking a wav file, a message and hiding
* that message inside the data segment of the wav file making a new
* seemingly unchanged wav file. The algorithm for encoding the message
* into the wav file has a clear stepping procedure. First, we create an
* exact copy of the wav file we have received and we give that file to the
* actual encoding function which will alter its data part.Now, in the encoding
* function we create the permutation table which will be explained in detail
* later but for now let's just say it's a way to make somewhat random the  
* choice of what byte we will hide the message fragments(bits).Once the 
* permutation table is completed we proceed to a for-loop which will
* keep iterating each and every bit of the message and everytime finding what
* is the current bit's value using the @see getBit() function.Continuing
* inside the loop we will choose via the permutation table a "random" byte
* in which we will store the bit we got from getBit() in it's least significant
* bit by first: clearing the value of that bit (bitwise and with zero) and then
* assigning the new value using bitwise or. When all the bits are put in 
* sparse bytes in the data part of the new wav file, the sound is seemingly
* unchanged but we have managed to store information within!
*
* @author Sotiris Loizidis
* @bug No known bugs
*/

#include "wavFiles.h"

/** @brief This function is responsible for returning the value of a 
*	 certain bit within a string. 		
* By the utilization of bit shifting we manage to extract any
* given bit from a centrain byte of the string.
*
* @param n The bit of the message that we want to learn its value.
* @param *m The message.
* @return returnBit the value of the bit we are interested in.
*/
PRIVATE int getBit(char *m, int n);						

/** @brief This function is where the actual encoding takes place.
* We create the permutation table and then in a for-loop we take
* the value of the first to last bit of the message using getBit() and then
* choosing a random byte from the permutation table that will get its
* least significant bit changed to the bit of the message. We do that
* by first clearing the bit using and with zero and then assigning the new
* bit by or-ing it.
*
* @param *data the data segment of a wav file in bytes
* @param *message the string we will encode
* @return data the altered data segment
*/
void wavENCODE(Byte *data,char *message);			

/** @brief a function that opens a file and stores the text to a string
* This functions follows the standard procedure of reading chars from
* a file.
*
*@param *inputName the name of the file that contains the message
*@return m The string message
*/
PRIVATE char *read(char *inputName);

/*FUNCTION IMPLEMENTATIONS*/

int getBit(char *m, int n){
	return m[n/8]>>(7-(n%8)) &1;
}

int* createPermutationFunction(int N,unsigned int systemkey){
/* Intializes random number generator */
   srand( systemkey );  
   int *permutations=(int*)malloc(N*sizeof(int));
   int c;
   for(c = 0;c < N;c++){
   	permutations[c]=c;	//f(x)=x
   }
   int i,j,temp;   
   for(c = 0;c < N;c++){
   	i=rand() % (N-1);	//create a random number between 1 and N-1
   	j=rand() % (N-1);	//create a random number between 1 and N-1
   	temp=permutations[i];				//swap positions i and j.
   	permutations[i]=permutations[j];
   	permutations[j]=temp;
   }
   return permutations;
}

void wavENCODE(Byte *data,char *message){
 	int N=8*strlen(message);
 	unsigned int u,x;
 	int *perm=NULL;
 	perm=createPermutationFunction(N,system_key_integer);
 	#ifdef DEBUG
	 	int count=0;
	 	int ch=0;
	#endif
 	for(int i=0;i<N;i++){
 		u=getBit(message,i);
 		x=perm[i];
 		data[x] &=~(1);		//clear the least significant bit.
 		data[x] |=(u);			//assingn the value of u(0/1) to the least significant bit.
 		#ifdef DEBUG
	 		printf("is stored in byte:%d of data\n",x);
	 		count++;
	 		if(count==8){
	 			printf("char %d\n\n\n",ch++);
	 			count=0;
	 		}
 		#endif
 	}
 	free(perm); 	
}

void createENCODED(char *inputName,char *fileName,WAV *wavFile){
	char *msg=NULL;
	msg=read(inputName);
	printf("Length of hidden message to give to decode is:%ld\n",strlen(msg));
 	wavENCODE(wavFile->data_part,msg);
	char encodedFilename[50]="";
 	char *new="new-";
 	strcat(encodedFilename,new);
 	strcat(encodedFilename,fileName);
 	writeWAV(encodedFilename,wavFile);
 	free(msg);
}

char *read(char *inputName){
	FILE *fp;
	 fp=fopen(inputName,"rb");
	 if(fp == NULL){
	 	printf("\nCannot open input file.");
		exit(-1);
	 }
	char *m=NULL;
	m=(char*)malloc(10000000*sizeof(char));
	char buffer[200];
	char *flag=NULL;
	flag=fgets(buffer,200,fp);
	while(flag!=NULL){
		strcat(m,buffer);
		flag=fgets(buffer,200,fp);
	}
	#ifdef DEBUG
	printf("%s",m);
	#endif
	fclose(fp);
	return m;
}
#ifdef DEBUG
int main(int argc,char *argv[]){	
	if(argc<3){
		printf("not enough arguments.\n");
		exit(-1);	
	}
	char *msge="ca";
	int res;
	res=getBit(msge,15);
	printf("%d \n",res);
	res=getBit(msge,16);
	printf("%d \n",res);
	res=getBit(msge,0);
	printf("%d \n",res);
	res=getBit(msge,9);
	printf("%d \n",res);
	res=getBit(msge,40);
	printf("%d \n",res);
	res=getBit(msge,8);
	printf("%d \n",res);
	printf("\n***************************\n");
	char *textFile=NULL;
	char *wavFile=NULL;
	textFile=argv[argc-1];
	wavFile=argv[argc-2];
	WAV *encode=NULL;
	encode=(WAV*)malloc(sizeof(WAV));
	encode->header_part=NULL;
	encode->data_part=NULL;
	readWAV(wavFile,&encode);
	createENCODED(textFile,wavFile,encode);
	Byte *data=(Byte*)malloc(8);
	memset(data,0x00,8);
	char msg[2];
	msg[0]=0x7f;
	msg[1]='\0';
	printf("\n");
	wavENCODE(data,msg);
	for(int i=0;i<8;i++){
	printf("%x",data[i]);
	}	
	free(data);
	free(encode);
	return (1);
}
#endif
