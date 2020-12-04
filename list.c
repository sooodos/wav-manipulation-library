/*
*list.c Implemantation of printing a wav file.
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
/** @file list.c
 *  @brief Implemantation of printing a wav file.
 *  
 * The -list argument refers to printing the header
 * elements of a specified audio file in the format
 * that is shown in the exercise pronunciation.
 * 
 * @author Marcos Antonios Charalambous.
 * @author Sotiris Loizidis.
 * @bug No known bugs.
 */
#include "wavFiles.h"

void printHeader(HEADER *h){
	char *buffer=(char*)malloc(5 * sizeof(char));
	memcpy(buffer,h->chunkID,4); // We use buffer everytime there is a string.
	buffer[4]='\0'; // Terminating null character at the end of buffer.
	
	printf("\nRIFF_CHUNK_HEADER\n");
	printf("=================\n");
	printf("ChunkID: %s\n",buffer);
 	printf("ChunkSize: %d\n",h->chunkSize);
 	memcpy(buffer,h->Format,4);
 	printf("Format: %s\n\n",buffer);
 	
	printf("FMT_SUBCHUNK_HEADER\n");
	printf("===================\n");
	memcpy(buffer,h->subChunk1ID,4);
 	printf("Subchunk1ID: %s\n",buffer);
 	printf("Subchunk1Size: %d\n",h->subChunk1Size);
 	printf("AudioFormat: %d\n",h->audioFormat);
 	printf("NumChannels: %d\n",h->numChannels);
 	printf("SampleRate: %d\n",h->sampleRate);
 	printf("ByteRate: %d\n",h->ByteRate);
 	printf("BlockAlign: %d\n",h->blockAlign);
 	printf("BitsPerSample: %d\n\n",h->bitsPerSample);

	printf("DATA_SUBCHUNK_HEADER\n");
	printf("====================\n");
	memcpy(buffer,h->subChunk2ID,4);
 	printf("Subchunk2ID: %s\n",buffer);
 	printf("Subchunk2Size: %d\n",h->subChunk2Size);
	
	printf("\n************************************");
	free(buffer);
}

/** @brief Unit driver for checking list.c.
*
*/
#ifdef DEBUG
int main(int argc,char *argv[]){
	
	if(argc < 3){
		printf("Not enough arguments.\n");
      return EXIT_FAILURE;
	}
	
	char *fileName1 = NULL;
	char *fileName2 = NULL;
	fileName1=argv[argc-2];
	fileName2=argv[argc-1];
		
	WAV *wavFile=NULL;
	wavFile=(WAV*)malloc(sizeof(WAV));
	wavFile->header_part=NULL;
	wavFile->data_part=NULL; 		
 	readWAV(fileName1,&wavFile);
 	printHeader(wavFile->header_part);
 	
	free(wavFile->header_part);
	free(wavFile->data_part);
	free(wavFile);
	
	WAV *wavFile2=NULL;
	wavFile2=(WAV*)malloc(sizeof(WAV));
	readWAV(fileName2,&wavFile2);
 	printHeader(wavFile2->header_part);
 	
 	free(wavFile2->header_part);
	free(wavFile2->data_part);
	free(wavFile2);
	
	return 0;
}	
#endif
