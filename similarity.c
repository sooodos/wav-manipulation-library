/*
*similarity.c Implemantation of of wav similarity algorithms.
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
/** @file similarity.c
 *  @brief Implemantation of of wav similarity algorithms.
 *  
 * By giving the -similarity argument in the command line,
 * the wavSimilarity functiong will be called, implemented 
 * here. The wavSimilarity will check the similarity for each 
 * byte of the file data (only on the data, not the header). 
 * Similarity determination is based on two known algorithmic
 * methods: 
 * (a) Euclid's matching technique (Euclidean matching)
 * (b) The maximum common sub-sequence (LCSS matching technique) 
 * In the Euclid matching technique, the two sequences involved
 * are compared "in parallel", element to element. At the same
 * time, the Euclidean distance is calculated.The maximum
 * sub-sequence between two sequences can be calculated by
 * the maximum common sub-sequence matching technique (LCSS)
 * implement below. 
 *
 * @author Marcos Antonios Charalambous
 * @bug No known bugs.
 */
#include "wavFiles.h"

PRIVATE int max(int a, int b); 

void wavSimilarity(WAV *wa, WAV *wb){
	// Check if the two WAV files can be compared.
	if(wa->header_part->bitsPerSample != wb->header_part->bitsPerSample){
		printf("The two wav files do not have the same number of bits per sample.\n");
		return;
	}
	if(wa->header_part->numChannels != wb->header_part->numChannels){
		printf("The two wav files do not have the same number of channels.\n");
		return;
	}
	
	// Calculation of the Euclidean distance.
	double dEuclidean=0.0;
	int smallest=0;
		
	if ((wa->header_part->subChunk2Size) <= (wb->header_part->subChunk2Size))
		smallest=wa->header_part->subChunk2Size;
	else
		smallest=wb->header_part->subChunk2Size;
	
	int i=0;
	for (i=0; i<smallest; i++){
		dEuclidean+=pow(abs(wa->data_part[i] - wb->data_part[i]), 2);
	}
	dEuclidean=sqrt(dEuclidean);
	printf("Euclidean distance\t: %.3f",dEuclidean);
	
	// Calculation of the LCSS.
	int j=0;
	dword *DP0=NULL; 	
	dword *DP1=NULL;
	dword *temp=NULL;
	DP0=(dword*)calloc(wb->header_part->subChunk2Size +1,sizeof(dword)); // Allocate to arrays to 
	DP1=(dword*)calloc(wb->header_part->subChunk2Size +1,sizeof(dword)); // the size of the smallest one.
	
	for (i=1; i<=wa->header_part->subChunk2Size; i++){
		for (j=1; j<=wb->header_part->subChunk2Size; j++){
			if (wa->data_part[i-1] == wb->data_part[j-1])
				DP1[j]= DP0[j-1]+1;
			else
				DP1[j]= max(DP0[j],DP1[j-1]);
		}
		temp=DP0;
		DP0=DP1;
		DP1=temp;
	}
		
	double x=DP1[wb->header_part->subChunk2Size];
	x=x/smallest;
	double dLCSS=0.0;
	dLCSS = 1.0-x;
	printf("\nLCSS distance\t\t: %.3f",dLCSS);
	
	// Free allocated data.experimenta frees, not functional 
	free(DP0);
	free(DP1);
	//free(temp);
}

/** @brief Find max between number a and b.
*
* @param a First number.
* @param b Second number.
*/
PRIVATE int max(int a, int b) 
{ 
    return (a > b)? a : b; 
} 

/** @brief Unit driver for checking similarity.c.
*
*/
#ifdef DEBUG
int main(int argc,char *argv[]){

	char *fileName1 = NULL;
	char *fileName2 = NULL;
	fileName1=argv[argc-2];
	fileName2=argv[argc-1];
	printf("Similarity of file %s and %s:\n",fileName1,fileName2);
	WAV *wavA=(WAV*)malloc(sizeof(WAV));
	wavA->header_part=NULL;
	wavA->data_part=NULL;
	readWAV(fileName1,&wavA);
	
	WAV *wavB=(WAV*)malloc(sizeof(WAV));
	wavB->header_part=NULL;
	wavB->data_part=NULL;
	readWAV(fileName2,&wavB);
	
	wavSimilarity(wavA,wavB);
	
	return 0;

}
#endif
