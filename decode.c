/*
*decode.c Implemantation of wav decode algorithm.
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
/** @file decode.c
*	 @brief implementation of decoding strategy for an encoded wav file
*
* With this function we take a WAV file that supposedly has an encrypted
* message within its data segment. By receating the exact
* same permutations table using the same key we basically follow the 
* reverse procedure of encoding. That means finding the "random" x-th byte
* of the data segment via the permutations table which contains the i-th
* bit in its least significant bit. We store that bit using bitwise operation
* &1. The way it works is that when a bit is zero if we bit-and it with
* one we will get zero, if it is one and-ing it with one will once again
* grant as one. The tactic that I followed is storing each bit to char table
* and every time the table has 8 bits stored it means that we have completed 
* a single byte(char) so we can proceed to add that char to the final
* message. A very useful method for this was @see strtol().
*
* @author Sotiris Loizidis
* @bug No known bugs
*/
#include "wavFiles.h"

/** @brief Takes the generated string and stores it in a file
* A function responsible for putting the final message into a given file.
*
* @param *message the string
* @param *fileName the name of the file that the string will be stored
*/
PRIVATE void writeMessage(char *message,char *fileName);

/** @brief This is the function where the actual decoding takes place.
* In this fucntion we essentialy take as parameters the data segment of
* the wav file and the length of the message which is supposedly known 
* beforehand. By length we mean the number of all characters including
* normal printable ASCII characters, newLines spaces tabs AND the '\0'
* character which indicates the end of the string. It is vital to
* be completely clear that the length we give as a parameter is the 
* number of characters INCLUDING the null character '\0' in this herein
* implementation. We create the same permutation table that was creating in
* the encoding process and then in a for-loop we begin the decoding.
* The first bit of the message is stored in the x-th bit of the data segment
* where x is the number given by the i-th place of the same permutation
* table used in encoding. This is the only way to decode the correct bytes.
* We get the bit by bitwise and-ing it with 1 in its least significant bit
* (we don't have to shift since it is the last bit) and then store that
* bit in string which,when completed(8 bits for a byte) is essentlially
* the binary representation of the character. Then through the usage of
* functions like @see strtol() we process that binary string and turn it
* to its printable char form. We do this for all bits of the message until
* we have recreated all the characters and stored them to a final string 
* which is the decoded message.
*
*/
PRIVATE char *wavDECODE(Byte *data,int msgLength);					

/*FUNCTION IMPLEMENTATIONS*/

int system_key_integer=3;

char* wavDECODE(Byte *data,int msgLength){
 	int N=8*(msgLength);
 	int x,bit;
 	int *perm=NULL;
 	char *msg=(char*)malloc(msgLength);
 	for(int i=0;i<msgLength;i++){
 		msg[i]=0x00;
 	}
 	char *singleChar=(char*)malloc(8);
 	for(int j=0;j<8;j++){
 		singleChar[j]='\0';
 	}
 	int counter=0;
 	int counterOfChars=0;
 	char toChar;
 	perm=createPermutationFunction(N,system_key_integer);
 	for(int i=0;i<(N);i++){
 		//printf("bitPointer:%d ",bitPointer);
 		x=perm[i];
 		bit = data[x] & 1;
 		//printf("bit:%d\n",bit);
 		toChar=bit+'0';					//change the int to char.
		singleChar[counter]=toChar;
 		counter++;
 		if(counter==8){
 			#ifdef DEBUG
 			printf("binary representation of char %s",singleChar);
 			#endif
 			counter=0;
 			long int decimal=0;
 			decimal=strtol(singleChar,NULL,2);			//DECIMAL IN ASCII
 			#ifdef DEBUG
 			printf("-decimal representation of char:%ld\t",decimal);
 			#endif
 			toChar=(int)decimal-48+'0';					//HEXADECIMAL REPRESENTATION
 			#ifdef DEBUG
 			if(toChar=='\n'){
 				printf("\\");
 				printf("newLine\n");
 			}else{	
 				printf(" char %c\n",toChar);					
 				}
 			#endif	
 			msg[counterOfChars++]=toChar;
 		}
 	}
 	#ifdef DEBUG
	printf("%s",msg);
 	#endif
 	free(singleChar);
 	free(perm);
 	return msg; 
}

 void createDECODED(WAV *wavFile,int msgLength,char *fileName){
	char *msg=wavDECODE(wavFile->data_part,msgLength);
 	writeMessage(msg,fileName);
 	free(msg);
 	free(wavFile->header_part);
 	free(wavFile->data_part);
 	free(wavFile);
}	

void writeMessage(char *message,char *fileName){
	FILE *fp;
	 	fp=fopen(fileName,"w");
	 	if(fp == NULL){
	 		printf("\nCannot create decoded.txt");
			exit(-1);
	 	}
	for(int i=0;i<strlen(message);i++){
		fprintf(fp,"%c",message[i]);
	}
	fclose(fp);
}
#ifdef DEBUG
int main(int argc,char *argv[]){
	if(argc<4){
		printf("not enough arguments.\n");
		exit(-1);	
	}
	char *out=NULL;
	char *encodedFileName=NULL;
	
	out=argv[argc-1];
	int length=atoi(argv[argc-2]);
	encodedFileName=argv[argc-3];
	
	WAV *wavENCODED=(WAV*)malloc(sizeof(WAV));
	wavENCODED->header_part=NULL;
	wavENCODED->data_part=NULL;
	readWAV(encodedFileName,&wavENCODED);
	createDECODED(wavENCODED,length,out);	
}
#endif
