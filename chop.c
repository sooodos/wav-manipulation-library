/*
*chop.c Implemantation of wav chop algorithm.
*Copyright (C) 2018  Marcos Antonios Charalambous
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
/** @file chop.c
 *  @brief Implemantation of wav chop algorithm.
 *  
 * In chop.c the function for chopping a wav audio
 * file is implemented.By giving the -chop argument
 * in the command line, the wavChop functiong will
 * be called, implemented here. The -chop command 
 * breaks a wav audio file from one specific second
 * to another. The result is saved in a new file
 * named chopped-sound1.wav, where sound1.wav is the
 * original audio file name. Checks are made for input
 * start second and end second to see if they are within
 * the duration of the input file.
 * 
 * @author Marcos Antonios Charalambous
 * @bug No known bugs.
 */
#include "wavFiles.h"

void wavChop(WAV *wFull, int start, int end, char* fileName){ 
		
	int startByte = (wFull->header_part->numChannels * wFull->header_part->sampleRate * wFull->header_part->bitsPerSample)/8;
	startByte = start*startByte;
	int endByte = (wFull->header_part->numChannels * wFull->header_part->sampleRate * wFull->header_part->bitsPerSample)/8;
	endByte = end * endByte;
	
	// Invalid numbers given.
	if (startByte > wFull->header_part->subChunk2Size || endByte > wFull->header_part->subChunk2Size){
		printf("The numbers you have given are not valid");
		return;
	}
	
	// In case the second number is smaller than the first one.
	if (endByte < startByte){ 
		int temp;
		temp=startByte;
		startByte=endByte;
		endByte=temp;
	}
	
	int dif = endByte-startByte;
	
	WAV* wChop=(WAV*)malloc(sizeof(WAV));
	wChop->header_part=NULL;
	wChop->data_part=NULL;
	
	wChop->data_part = (Byte*)malloc(sizeof(Byte)*dif);
	
	wChop->header_part = wFull->header_part;
	wChop->header_part-> chunkSize = dif +36;
	wChop->header_part-> subChunk2Size = dif;
	
	int i=0;
	while ( i < (wChop->header_part->subChunk2Size)){
		wChop->data_part[i] = wFull->data_part[i+startByte];
		i++;
	}
		
	char *outFileName=NULL;
	outFileName=(char*)malloc(strlen(fileName)+9);
	strcpy(outFileName,"chopped-");
	outFileName=strcat(outFileName,fileName);
	writeWAV(outFileName,wChop);
	free(outFileName);
	free(wChop->data_part);
	free(wChop);
}

/** @brief Unit driver for checking chop.c.
*
*/
#ifdef DEBUG
int main(int argc,char *argv[]){
	
	if(argc < 4){
		printf("Not enough arguments.\n");
      return EXIT_FAILURE;
	}
	
	char *fileName1 = NULL;
	fileName1=argv[argc-3];

	int start = atoi(argv[argc-2]);
	int end = atoi(argv[argc-1]);
	
	WAV *wavFull=(WAV*)malloc(sizeof(WAV));
	wavFull->header_part=NULL;
	wavFull->data_part=NULL;
	
	readWAV(fileName1,&wavFull);
	wavChop(wavFull,start,end,fileName1);
		
	return 0;

}
#endif
