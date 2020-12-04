/*
*read.c Reading and writing of files.
*Copyright (C) 2018  Marcos Antonios Charalambous & Sotiris Loizidis.
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
/** @file read.c
 *  @brief Reading and writing of files.
 * 
 * The implementation of the methods for 
 * writing and readig a binary file are found
 * in read.c
 * 
 * @author Marcos Antonios Charalambous.
 * @author Sotiris Loizidis.
 * @bug No known bugs.
 */
#include "wavFiles.h"

int readWAV(char *fileName, WAV **h){
	(*h)->header_part=(HEADER*)malloc(sizeof(HEADER));
 	if( (*h)->header_part == NULL){
 		printf("\nCannot allocate memory.");
 		return EXIT_FAILURE;
 	}
	FILE *fp;
 	fp=fopen(fileName,"rb");
 	if(fp == NULL){
 		printf("\nCannot open input WAV file.");
 		return EXIT_FAILURE;
 	}
 	int flag;
 	flag=fread((*h)->header_part,sizeof(HEADER),1,fp);
 	if(flag==0){
 		printf("Could not read header segment.\n");
 		return EXIT_FAILURE;
 	}
 	int dataSize=0;
 	dataSize=(*h)->header_part->subChunk2Size;
	(*h)->data_part=(Byte*)malloc(sizeof(Byte)*dataSize);
 	
 	if( (*h)->data_part == NULL){
 		printf("\nCannot allocate memory.");
 		return EXIT_FAILURE;
 	}
	if(fread((*h)->data_part,sizeof(Byte),dataSize,fp)==0){
		printf("Could not read data segment.\n");
 		return EXIT_FAILURE;
	}
	fclose(fp);	
 	return EXIT_SUCCESS;
}

int writeWAV(char *fileName, WAV *h){
	char outFileName[100]="";
	strcat(outFileName,fileName);
	FILE *fp2=NULL;
 	fp2=fopen(outFileName,"wb");
 	if(fp2 == NULL){
 		printf("\nCannot make output WAV file.");
 		return EXIT_FAILURE;
 	}	
	
 	fwrite(h->header_part,sizeof(HEADER),1,fp2);
 	fwrite(h->data_part,sizeof(Byte),h->header_part->subChunk2Size,fp2);
	
 	fclose(fp2);
	return EXIT_SUCCESS;
}
