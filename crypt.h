/** @file crypt.h
 *  @brief Prototypes mainly for encode/decode.
 *
 * @author Marcos Antonios Charalambous.
 * @author Sotiris Loizidis.
 * @bug No known bugs.
 */
#ifndef __CRYPT_H__
#define __CRYPT_H__
	
#include "wavFiles.h"


/** @brief A function which creates a pseudorandom sequence of numbers
* This function makes use of the @see srand() to create pseudorandom
* numbers ranging from zero to the table length and swapping this
* positions creating a somewhat random table.
*
* @param N this is the size of the prmutation table and is essentially  
* the number of bits of the message including the '\0' character.
* @param systemkey An integer which is used as a key for both encoding/decoding.
* @return permutations the randomized table.
*/
int* createPermutationFunction(int N,unsigned int systemkey);	//used in both decode.c and encode.c


/** @brief This function is the caller function which will create the final
*   enoded wav file
* This function copies the unprocessed wav to a new wav and then proceeds to
* give its data part as a parameter to wavENCODE() so it can encode the message.
* 
* @param *inputName the name of the file which contains the message.
* @param *fileName The name of the unprocessed wav File.
* @param *The wav file itself.
*/
void createENCODED(char *inputName,char *fileName,WAV *wavFile);	//encode.c

 
/** @brief The function whch is called for decoding a WAV
* The function responsible for calling the functions necessary to create the
* text file containing the message @see wavDECODE() @see writeMessage()
*
* @param *wavFile the encoded WAV
* @param *msgLength the Length of the message INCLUDING the null character.
* @param *fileName the name of the file that the message is stored.
*/
void createDECODED(WAV *wavFile,int msgLength,char *fileName);		//decode.c


/** @brief A common key which is used by both decode.c and encode.c
* in order to generate the same prmutation table.
*
*/	
extern int system_key_integer;				//used in both decode.c and encode.c
	
#endif
