/*
*mono.c Implemantation of wav mono maker algorithm.
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
/** @file mono.c
 *  @brief Implemantation of wav mono maker algorithm.
 *  
 * The -mono argument converts the audio file from a
 * stereo (2-channel) to a mono (1-channel only). This
 * can be done by deleting the right or left channel.
 * In our implementation, the right channel is removed.
 * The result is saved in a new file named new-sound1.wav,
 * where sound1.wav is the original audio file name.
 * 
 * @author Marcos Antonios Charalambous
 * @bug No known bugs.
 */
#include "wavFiles.h"

void monoMaker(WAV *ws,char* fileName){
	
	WAV* wm=	NULL;
	wm=(WAV*)malloc(sizeof(WAV));
	wm->header_part=NULL; 
	wm->data_part=NULL; 
	
	wm->data_part = (Byte*)malloc(sizeof(Byte)*((ws->header_part->subChunk2Size)/2));
	
	wm->header_part = ws->header_part;
	wm->header_part-> chunkSize = (ws->header_part->subChunk2Size)/2 +36;
	wm->header_part-> ByteRate = (ws->header_part->ByteRate)/2;
	wm->header_part-> numChannels = 1;
	wm->header_part-> blockAlign = (ws->header_part->blockAlign)/2;
	wm->header_part-> subChunk2Size = (ws->header_part->subChunk2Size)/2;
	
	int i=0;
	int j=0;
	if (wm->header_part->bitsPerSample == 16){
		while ( i < (wm->header_part->subChunk2Size)){
			wm->data_part[i++]=ws->data_part[j++];
			wm->data_part[i++]=ws->data_part[j];
			j+=3;
		}
	}else{
		for (i=0; i < (wm->header_part->subChunk2Size); i++){
			wm->data_part[i]=ws->data_part[j];
			j+=2;
		}
	}
	
	char *outFileName=NULL;
	outFileName=(char*)malloc(strlen(fileName)+5);
	strcpy(outFileName,"new-");
	outFileName=strcat(outFileName,fileName);
	writeWAV(outFileName,wm);
	free(wm->data_part);
	free(wm->header_part);
	free(wm);
	free(outFileName);
}

/** @brief Unit driver for checking mono.c.
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
		
	WAV *wavStereo=(WAV*)malloc(sizeof(WAV));
	wavStereo->header_part=NULL;
	wavStereo->data_part=NULL;
	
	readWAV(fileName1,&wavStereo);
	monoMaker(wavStereo,fileName1);
	
	WAV *wavStereo2=(WAV*)malloc(sizeof(WAV));
	wavStereo2->header_part=NULL;
	wavStereo2->data_part=NULL;
 	 		
 	readWAV(fileName2,&wavStereo2);
	monoMaker(wavStereo2,fileName2);

	free(wavStereo->data_part);
	free(wavStereo);
		
	free(wavStereo2->data_part);
	free(wavStereo2);
	return 0;
}
#endif
