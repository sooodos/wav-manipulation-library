#ifndef __WAVFILES_H__
#define __WAVFILES_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef unsigned char Byte;
typedef unsigned short int word;
typedef unsigned int dword;

typedef struct{
	Byte chunkID[4];
	dword chunkSize;
	Byte Format[4];
	
	Byte subChunk1ID[4];
	dword subChunk1Size;
	word audioFormat;
	word numChannels;
	dword sampleRate;
	dword ByteRate;
	word blockAlign;
	word bitsPerSample;
	
	Byte subChunk2ID[4];
	dword subChunk2Size;
		
} __attribute__((packed)) HEADER;

typedef struct{
	HEADER *header_part;
	Byte *data_part;
} __attribute__((packed)) WAV;

int readWAV(char *,WAV **);

int writeWAV(char *, WAV *);

void printHeader(HEADER *);

WAV* monoMaker(WAV *,char *);
<<<<<<< .mine

WAV* mix(WAV *,WAV *);
||||||| .r31
WAV* mix(WAV *,WAV *);
=======
WAV* mix(WAV *,char *,WAV *,char *);
>>>>>>> .r36

WAV* wavChop(WAV *, int, int, char *);

#endif
