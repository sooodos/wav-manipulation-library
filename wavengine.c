#include "wavFiles.h"

void printGPL(){
	printf("\nGPL\n");
	printf("**************************************\n");
	printf("client.c Checking of the wav operations.\n");
	printf("Copyright (C) 2018  Marcos Charalambous & Sotiris Loizidis\n"); 
	printf("\n");
	printf("This program is free software: you can redistribute it and/or modify\n");
	printf("it under the terms of the GNU General Public License as published by\n");
	printf("the Free Software Foundation, either version 3 of the License, or\n");
	printf("at your option) any later version.\n");
	printf("\n");
	printf("This program is distributed in the hope that it will be useful,\n");
	printf("but WITHOUT ANY WARRANTY; without even the implied warranty of\n");
   printf("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n");
	printf("GNU General Public License for more details.\n");
	printf("\n");
	printf("Υou should have received a copy of the GNU General Public License along\n");
	printf("with this program.  If not, see <http://www.gnu.org/licenses/>.\n");
}

int containExtension(char *fileName){
	if (fileName[strlen(fileName)-1] != 'v')
		return EXIT_FAILURE;
	if (fileName[strlen(fileName)-2] != 'a')
		return EXIT_FAILURE;
	if (fileName[strlen(fileName)-3] != 'w')
		return EXIT_FAILURE;
	if (fileName[strlen(fileName)-4] != '.')
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

int main(int argc, char* argv[] ) {
	int i=0;
	char *fileName1 = NULL;
	char *fileName2 = NULL;
	
	if ( strcmp("-list",argv[1]) == 0 ){
		if(argc < 3){
			printf("Not enough arguments.\n");
			printGPL();
			exit(-1);
		}
		for ( i=2; i<argc; i++){
			fileName1=argv[i];
			WAV *wavFile=(WAV*)malloc(sizeof(WAV));
			wavFile->header_part=NULL;
			wavFile->data_part=NULL;
			if (containExtension(fileName1) == EXIT_FAILURE)
				printf("\nThe argument %s is not a .wav audio file.\n",fileName1);
 	 		else if (readWAV(fileName1,&wavFile) == EXIT_SUCCESS)
				printHeader(wavFile->header_part);
			free(wavFile->header_part);
			free(wavFile->data_part);
			free(wavFile);
		}
	}
	else if ( strcmp("-mono",argv[1]) == 0 ){
		if(argc < 3){
			printf("Not enough arguments.\n");
			printGPL();
			exit(-1);
		}
		for ( i=2; i<argc; i++){
			fileName1=argv[i];
			WAV *wavStereo=(WAV*)malloc(sizeof(WAV));
			wavStereo->header_part=NULL;
			wavStereo->data_part=NULL;
			if (containExtension(fileName1) == EXIT_FAILURE)
				printf("\nThe argument %s is not a .wav audio file.\n",fileName1);
 	 		else if (readWAV(fileName1,&wavStereo) == EXIT_SUCCESS){
				monoMaker(wavStereo,fileName1);
			}	
				free(wavStereo->data_part);
				free(wavStereo);
		}
	}
	else if ( strcmp("-mix",argv[1]) == 0 ){
		if(argc < 4){
			printf("Not enough arguments.\n");
			printGPL();
			exit(-1);
		}
		fileName1=argv[argc-2];
		fileName2=argv[argc-1];
		WAV *RIGHT=(WAV*)malloc(sizeof(WAV));
		RIGHT->header_part=NULL;
		RIGHT->data_part=NULL;	
		WAV *LEFT=(WAV*)malloc(sizeof(WAV));
		LEFT->header_part=NULL;
		LEFT->data_part=NULL;	
		if (containExtension(fileName1) == EXIT_FAILURE)
			printf("\nThe argument %s is not a .wav audio file.\n",fileName1);
		else if (containExtension(fileName2) == EXIT_FAILURE)
			printf("\nThe argument %s is not a .wav audio file.\n",fileName2);
		else if (readWAV(fileName1,&RIGHT) == EXIT_SUCCESS && readWAV(fileName2,&LEFT)== EXIT_SUCCESS)
			mix(RIGHT,fileName1,LEFT,fileName2);
				
		free(RIGHT->header_part);
		free(RIGHT->data_part);
		free(RIGHT);
		free(LEFT->header_part);
		free(LEFT->data_part);
		free(LEFT);
	}			
	else if ( strcmp("-chop",argv[1]) == 0 ){
		if(argc != 5  ){
			printf("Arguments given are not valid. Check and try again.\n");
			printGPL();
			exit(-1);
		}
		fileName1=argv[argc-3];
		int start = atoi(argv[argc-2]);
		int end = atoi(argv[argc-1]);
		WAV *wavFull=(WAV*)malloc(sizeof(WAV));
		wavFull->header_part=NULL;
		wavFull->data_part=NULL;
		if (containExtension(fileName1) == EXIT_FAILURE)
			printf("\nThe argument %s is not a .wav audio file.\n",fileName1);
		else if (readWAV(fileName1,&wavFull) == EXIT_SUCCESS)
			wavChop(wavFull,start,end,fileName1);
		free(wavFull->header_part);
		free(wavFull->data_part);
		free(wavFull);
	
	}
	else if ( strcmp("-reverse",argv[1]) == 0 ){
		if(argc < 3){
			printf("Not enough arguments.\n");
			printGPL();
			exit(-1);
		}
		for ( i=2; i<argc; i++){
			fileName1=argv[i];
			WAV *file=NULL;
			file=(WAV*)malloc(sizeof(WAV));
			file->header_part=NULL;
			file->data_part=NULL;
			if (containExtension(fileName1) == EXIT_FAILURE)
				printf("\nThe argument %s is not a .wav audio file.\n",fileName1);
 	 		else if (readWAV(fileName1,&file) == EXIT_SUCCESS){
				wavReverse(file,fileName1);
			}	
			free(file->data_part);
			free(file);
		}
	 }
	 else if ( strcmp("-similarity",argv[1]) == 0 ){
		if(argc < 4){
			printf("Not enough arguments.\n");
			printGPL();
			exit(-1);
		}
		
		fileName1=argv[2];
		WAV *wavA=(WAV*)malloc(sizeof(WAV));
		wavA->header_part=NULL;
		wavA->data_part=NULL;
		if (containExtension(fileName1) == EXIT_FAILURE){
				printf("\nThe argument %s is not a .wav audio file.\n",fileName1);
		}else	if (readWAV(fileName1,&wavA) == EXIT_SUCCESS){
				
				for ( i=3; i<argc; i++){
					fileName2=argv[i];
					WAV *wavB=NULL;
					wavB=(WAV*)malloc(sizeof(WAV));
					//printf("%s",fileName2);
					wavB->header_part=NULL;
					wavB->data_part=NULL;
					if (containExtension(fileName2) == EXIT_FAILURE){
						printf("\nThe argument %s is not a .wav audio file.\n",fileName2);
					}
					else if( readWAV(fileName2,&wavB) == EXIT_SUCCESS ){
						printf("\nSimilarity of file %s and %s:\n",fileName1,fileName2);
						wavSimilarity(wavA,wavB);
					}
					free(wavB->header_part);
					free(wavB->data_part);
					free(wavB);
				}
			
		}
		free(wavA->header_part);
		free(wavA->data_part);
		free(wavA);
	 }	 
	 else if ( strcmp("-encodeText",argv[1]) == 0 ){
		if(argc<4){
			printf("Wrong number of arguments.\n");
			printGPL();
			exit(-1);
		}
		fileName1=argv[2];	//the name of the .wav file.
		fileName2=argv[3];	//the .txt input file.
		WAV *wavEncode=NULL;
		wavEncode=(WAV*)malloc(sizeof(WAV));
		wavEncode->header_part=NULL;
		wavEncode->data_part=NULL;
		if (containExtension(fileName1) == EXIT_FAILURE){
			printf("\nThe argument %s is not a .wav audio file.\n",fileName1);
		}
			else if( readWAV(fileName1,&wavEncode) == EXIT_SUCCESS ){
				createENCODED(fileName2,fileName1,wavEncode);
			}
		free(wavEncode->header_part);
		free(wavEncode->data_part);
		free(wavEncode);
		
	}
	else if ( strcmp("-decodeText",argv[1]) == 0 ){ 
		if(argc<5){
			printf("Wrong number of arguments.\n");
			printGPL();
			exit(-1);
		}
		
		fileName1=argv[2];			//the name of the .wav file.
		int length=atoi(argv[3]);	//the length of the message including the '\0' character.
		fileName2=argv[4];			//the .txt output file.
		WAV *wavEncoded=(WAV*)malloc(sizeof(WAV));
		wavEncoded->header_part=NULL;
		wavEncoded->data_part=NULL;
		if (containExtension(fileName1) == EXIT_FAILURE){
			printf("\nThe argument %s is not a .wav audio file.\n",fileName1);
		}
			else if( readWAV(fileName1,&wavEncoded) == EXIT_SUCCESS ){
				createDECODED(wavEncoded,length,fileName2);
				return (0);	
			}
			printf("Not a valid option.\n");
		printGPL();		
	}
	else if(strcmp("-fastForward",argv[1]) == 0){
		if(argc<4){
			printf("Not enough arguments.\n");
			printGPL();
			exit(-1);
		}
		int wavSpeed=atoi(argv[argc-1]);
		for ( i=2; i<argc-1; i++){
			fileName1=argv[i];
			WAV *wavFast=NULL;
			wavFast=(WAV*)malloc(sizeof(WAV));
			wavFast->header_part=NULL;
			wavFast->data_part=NULL;
			if (containExtension(fileName1) == EXIT_FAILURE){
				printf("\nThe argument %s is not a .wav audio file.\n",fileName1);
			}
			else if( readWAV(fileName1,&wavFast) == EXIT_SUCCESS ){
				wavFastForward(wavFast,fileName1,wavSpeed);
				}
				//free(wavFast->header_part);
				free(wavFast->data_part);
				free(wavFast);
		}
		
	}
}
