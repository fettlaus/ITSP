/*
 * main.c
 *
 *  Created on: 13.12.2010
 *      Author: Fettlaus
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sha.h"

#define BLOCKSIZE 512

unsigned char digest[20];
unsigned char message[3] = {'a', 'b', 'c' };
unsigned char *mess56 =
	"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";

/* Correct solutions from FIPS PUB 180-1 */
char *dig1 = "A9993E36 4706816A BA3E2571 7850C26C 9CD0D89D";
char *dig2 = "84983E44 1C3BD26E BAAE4AA1 F95129E5 E54670F1";
char *dig3 = "34AA973C D4C4DAA4 F61EEB2B DBAD2731 6534016F";

/* Output should look like:-
 a9993e36 4706816a ba3e2571 7850c26c 9cd0d89d
 A9993E36 4706816A BA3E2571 7850C26C 9CD0D89D <= correct
 84983e44 1c3bd26e baae4aa1 f95129e5 e54670f1
 84983E44 1C3BD26E BAAE4AA1 F95129E5 E54670F1 <= correct
 34aa973c d4c4daa4 f61eeb2b dbad2731 6534016f
 34AA973C D4C4DAA4 F61EEB2B DBAD2731 6534016F <= correct
*/

int main(int argc, char *argv[]){
	puts(*++argv);

/*
	int msg_len;
	char *msg;
	char test[20];
	msg = *argv;
	puts(itoa(strlen(msg),test,10));
	*/
	SHA_CTX sha;

	char key[BLOCKSIZE];
	char *tmp_key;
	int key_length;

	char *msg;
	int msg_length;
	char o_key_pad[BLOCKSIZE];
	char i_key_pad[BLOCKSIZE];


	tmp_key = *argv++;
	msg = *argv;
	key_length = strlen(tmp_key);
	msg_length = strlen(msg);

	//debug
	printf("%i: %s\n%i: %s\n",key_length, tmp_key, msg_length, msg);
	int i;
	for(i = 0;i < BLOCKSIZE;i++){
		if(i < key_length)
			key[i] = tmp_key[i];
		else
			key[i] = '0';
	}
	//debug
	printf("Key padded or truncated: %s\n", key);

	//Calc Pads
	for(i = 0;i < BLOCKSIZE;i++){
		o_key_pad[i] = 0x5c ^ key[i];
		i_key_pad[i] = 0x36 ^ key[i];
	}
	//debug pads
	printf("o_key_pad: %s\ni_key_pad: %s\n", o_key_pad, i_key_pad);

	//hash it
	char *ipad_msg = i_key_pad;
	char *opad_msg = o_key_pad;

	strncat(ipad_msg,msg,msg_length);
	puts("Now SHA1");
	SHAInit(&sha);
	SHAUpdate(&sha, (BYTE*)ipad_msg, strlen(ipad_msg));
	SHAFinal((unsigned char*)ipad_msg, &sha);
	printf("ipad_length: %i\nopad_length: %i\n", strlen(ipad_msg), strlen(opad_msg));
	strncat(opad_msg,ipad_msg,strlen(ipad_msg));

	SHAInit(&sha);
	SHAUpdate(&sha, (BYTE*)opad_msg, strlen(opad_msg));
	SHAFinal((unsigned char*)opad_msg, &sha);

	puts(opad_msg);
	return 0;


	//shorten long keys
if(key_length > BLOCKSIZE){
	SHAInit(&sha);
	SHAUpdate(&sha, (unsigned char*)tmp_key, key_length);
	SHAFinal((unsigned char*)key, &sha);
}

//pad with zeros
if(key_length < BLOCKSIZE){

}


	SHAInit(&sha);


		BYTE big[1000];

		SHAInit(&sha);
		SHAUpdate(&sha, message, 3);
		SHAFinal(digest, &sha);

		for (i = 0; i < 20; i++)
		{
			if ((i % 4) == 0) printf(" ");
			printf("%02x", digest[i]);
		}
		printf("\n");
		printf(" %s <= correct\n", dig1);

		SHAInit(&sha);
		SHAUpdate(&sha, mess56, 56);
		SHAFinal(digest, &sha);

		for (i = 0; i < 20; i++)
		{
			if ((i % 4) == 0) printf(" ");
			printf("%02x", digest[i]);
		}
		printf("\n");
		printf(" %s <= correct\n", dig2);

		/* Fill up big array */
		for (i = 0; i < 1000; i++)
			big[i] = 'a';

		SHAInit(&sha);
		/* Digest 1 million x 'a' */
		for (i = 0; i < 1000; i++)
			SHAUpdate(&sha, big, 1000);
		SHAFinal(digest, &sha);

		for (i = 0; i < 20; i++)
		{
			if ((i % 4) == 0) printf(" ");
			printf("%02x", digest[i]);
		}
		printf("\n");
		printf(" %s <= correct\n", dig3);

		return 0;



}
