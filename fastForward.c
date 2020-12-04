#include "wavFiles.h"

void wavFastForward(WAV *ws,char* fileName,int speed){
	if(ws->header_part->numChannels==1){
		printf("Sorry, can only speed up stero WAVs.\n");
		exit(-1);
	}
	
	WAV* wFast=	NULL;
	wFast=(WAV*)malloc(sizeof(WAV));
	wFast->header_part=NULL; 
	wFast->data_part=NULL; 
	wFast->data_part = (Byte*)malloc(sizeof(Byte)*((ws->header_part->subChunk2Size)/speed));	
	wFast->header_part = ws->header_part;
	
	if (wFast->header_part->bitsPerSample == 16)
		wFast->header_part-> subChunk2Size = (ws->header_part->subChunk2Size)/(speed);
	else
		wFast->header_part-> subChunk2Size = (ws->header_part->subChunk2Size)/(speed*2);
		
	int i=0;
	int j=0;
	
	if (wFast->header_part->bitsPerSample == 16){
		while (( i < (wFast->header_part->subChunk2Size))&&(j<=wFast->header_part->subChunk2Size)){
			wFast->data_part[i++]=ws->data_part[j++];
			wFast->data_part[i++]=ws->data_part[j++];
			j+=(2*speed);
		}
	}else{
		while (( i < (wFast->header_part->subChunk2Size))&&(j<=wFast->header_part->subChunk2Size)){
			wFast->data_part[i++]=ws->data_part[j++];
			j+=(1*speed);
		}
	}
	
	wFast->data_part = (Byte*)realloc(wFast->data_part,i);
	wFast->header_part->subChunk2Size=i;
	char *outFileName=NULL;
	outFileName=(char*)malloc(strlen(fileName)+9);
	strcpy(outFileName,"sped up-");
	outFileName=strcat(outFileName,fileName);
	writeWAV(outFileName,wFast);
	free(wFast->data_part);
	free(wFast->header_part);
	free(wFast);
	free(outFileName);
}
