#include "wavFiles.h"

void wavREVERSE(WAV *file,char *fileName){
	WAV* reversed=(WAV*)malloc(sizeof(WAV));
	reversed->header_part=NULL;
	reversed->data_part=NULL;
	reversed->header_part = (HEADER*)malloc(sizeof(HEADER));
	reversed->header_part=file->header_part;
	reversed->data_part=(Byte*)malloc(sizeof(Byte)*(file->header_part->subChunk2Size));
	int i;
	int j=reversed->header_part->subChunk2Size;
	
	for(i=0;i<reversed->header_part->subChunk2Size;i++){
		reversed->data_part[i]=file->data_part[j--];
	}
	char reversedFilename[40]="";
	char *r="reverse-";
	strcat(reversedFilename,r);
	strcat(reversedFilename,fileName);
	writeWAV(reversedFilename,reversed);
}

#ifdef DEBUG
int main(int argc,char *argv[]){	
	if(argc < 2){
		printf("Not enough arguments.\n");
      return EXIT_FAILURE;
	}
	char *fName1 = NULL;
	fName1=argv[argc-1];
	
	WAV *FILE=(WAV*)malloc(sizeof(WAV));
	FILE->header_part=NULL;
	FILE->data_part=NULL;
	readWAV(fName1,&FILE);
	
	wavREVERSE(FILE,fName1);
}
#endif
