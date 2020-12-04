#include "wavFiles.h"

WAV* mix(WAV *wRightChannel,char *fileName1,WAV *wLeftChannel,char *fileName2){	
	if(wRightChannel->header_part->bitsPerSample != wLeftChannel->header_part->bitsPerSample){
		printf("The two wav files do not have the same number of bits per sample\n");
		return NULL;
	}
	WAV* mixed=(WAV*)malloc(sizeof(WAV));
	mixed->header_part=NULL;
	mixed->data_part=NULL;
	mixed->header_part = (HEADER*)malloc(sizeof(HEADER));
	
	if((wRightChannel->header_part->subChunk2Size)<=(wLeftChannel->header_part->subChunk2Size)){
		/*THE NEW MIXED FILE HAS THE LENGTH OF THE SMALLEST OF THE TWO*/
		mixed->header_part=wRightChannel->header_part;
		mixed->data_part = (Byte*)malloc(sizeof(Byte)*(wRightChannel->header_part->subChunk2Size));
	}else{
		mixed->header_part=wLeftChannel->header_part;
		mixed->data_part = (Byte*)malloc(sizeof(Byte)*(wLeftChannel->header_part->subChunk2Size));
	}
	int i=0;
	int j=2;
	int k=0;
	if (mixed->header_part->bitsPerSample == 16){
		while ( i < (mixed->header_part->subChunk2Size)){
			mixed->data_part[i++]=wLeftChannel->data_part[k++];
			mixed->data_part[i++]=wLeftChannel->data_part[k++];
			mixed->data_part[i++]=wRightChannel->data_part[j++];
			mixed->data_part[i++]=wRightChannel->data_part[j++];
			j+=2;
			k+=2;
		}
	}else{
		j=1;
		k=0;
		for (i=0; i < (mixed->header_part->subChunk2Size); i++){
			if((i%2)==0){
				mixed->data_part[i++]=wLeftChannel->data_part[k];
				k+=2;
			}else{
				mixed->data_part[i++]=wRightChannel->data_part[j];
				j+=2;
			}
		}
	}
	char mixedFilename[100]="";
	char *a="mix";
	char *b="<";
	char *c=">";
	char *d="-";
	char *e=".wav";
	strcat(mixedFilename,a);				//mix
	strcat(mixedFilename,d);				//-
	strcat(mixedFilename,b);				//<
	strcat(mixedFilename,fileName1);		//filename1
	strcat(mixedFilename,c);				//>
	strcat(mixedFilename,d);				//-
	strcat(mixedFilename,b);				//<
	strcat(mixedFilename,fileName2);		//filename2
	strcat(mixedFilename,c);				//>
	strcat(mixedFilename,e);				//.wav
	writeWAV(mixedFilename,mixed);
	return mixed;
}
	
int main(int argc,char *argv[]){
	
	if(argc < 3){
		printf("Not enough arguments.\n");
      return EXIT_FAILURE;
	}
	
	char *fName1 = NULL;
	char *fName2 = NULL;
	fName1=argv[argc-2];
	fName2=argv[argc-1];
		
	WAV *RIGHT=(WAV*)malloc(sizeof(WAV));
	RIGHT->header_part=NULL;
	RIGHT->data_part=NULL;
	readWAV(fName1,&RIGHT);
	
	WAV *LEFT=(WAV*)malloc(sizeof(WAV));
	LEFT->header_part=NULL;
	LEFT->data_part=NULL;
<<<<<<< .mine
 	readWAV(fileName2,&LEFT);
 	
	WAV *MIXED=mix(RIGHT,LEFT);
	char mixedFilename[50]="";
	char a[4]="mix";
	char b[2]="<";
	char c[2]=">";
	char d[2]="-";
	char e[5]=".wav";
	strcat(mixedFilename,a);				//mix
	strcat(mixedFilename,d);				//-
	strcat(mixedFilename,b);				//<
	strcat(mixedFilename,fileName1);		//filename1
	strcat(mixedFilename,c);				//>
	strcat(mixedFilename,d);				//-
	strcat(mixedFilename,b);				//<
	strcat(mixedFilename,fileName2);		//filename2
	strcat(mixedFilename,c);				//>
	strcat(mixedFilename,e);				//.wav
	writeWAV(mixedFilename,MIXED);
		
||||||| .r31
 	readWAV(fileName2,&LEFT);
 	
	WAV *MIXED=mix(RIGHT,LEFT);
	char mixedFilename[50];
	char a[4]="mix";
	char b[2]="<";
	char c[2]=">";
	char d[2]="-";
	char e[5]=".wav";
	strcat(mixedFilename,a);				//mix
	strcat(mixedFilename,d);				//-
	strcat(mixedFilename,b);				//<
	strcat(mixedFilename,fileName1);		//filename1
	strcat(mixedFilename,c);				//>
	strcat(mixedFilename,d);				//-
	strcat(mixedFilename,b);				//<
	strcat(mixedFilename,fileName2);		//filename2
	strcat(mixedFilename,c);				//>
	strcat(mixedFilename,e);				//.wav
	writeWAV(mixedFilename,MIXED);
		
=======
 	readWAV(fName2,&LEFT);
	WAV *MIXED=mix(RIGHT,fName1,LEFT,fName2);		
>>>>>>> .r36
	return 0;
}
