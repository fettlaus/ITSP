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
#define DIGEST_SIZE 20

int main(int argc, char *argv[]){

	SHA_CTX sha;

	char key[BLOCKSIZE];
	char *tmp_key;
	int key_length;

	char *msg;
	int msg_length;
	char o_key_pad[BLOCKSIZE];
	char i_key_pad[BLOCKSIZE];


	tmp_key = *++argv;
	msg = *++argv;
	key_length = strlen(tmp_key);
	msg_length = strlen(msg);

	//debug
	printf("Key (size %i): %s\nMessage (size %i): %s\n",key_length, tmp_key, msg_length, msg);

	//Pad or truncate
	int i;
	for(i = 0;i < BLOCKSIZE;i++){
		if(i < key_length)
			key[i] = tmp_key[i];
		else
			key[i] = '0';
	}
	//debug
	puts("Key padded or truncated");
	for(i = 0;i < BLOCKSIZE;i++)
		printf("%X",key[i]);

	//Calc Pads
	for(i = 0;i < BLOCKSIZE;i++){
		o_key_pad[i] = 0x5c ^ key[i];
		i_key_pad[i] = 0x36 ^ key[i];
	}
	//debug pads
	puts("\no_key_pad");
	for(i = 0;i < BLOCKSIZE;i++)
		printf("%X",o_key_pad[i]);
	puts("\ni_key_pad");
	for(i = 0;i < BLOCKSIZE;i++)
		printf("%X",i_key_pad[i]);
	puts("\nmsg");
	for(i = 0;i < msg_length;i++)
		printf("%X",msg[i]);


	//hash it
	char i_key_pad_msg[BLOCKSIZE + msg_length];
	char o_key_pad_hsh[BLOCKSIZE + DIGEST_SIZE];
	char digest[DIGEST_SIZE];

	strncpy(i_key_pad_msg,i_key_pad,BLOCKSIZE);
	strncpy(o_key_pad_hsh,o_key_pad,BLOCKSIZE);
	strncpy(&(i_key_pad_msg[BLOCKSIZE]),msg,msg_length);
	puts("\ni_key_pad_msg");
	for(i = 0;i < (BLOCKSIZE+msg_length);i++)
		printf("%X",i_key_pad_msg[i]);
	/*puts("\ni_key_pad");
	for(i = 0;i < BLOCKSIZE;i++)
		printf("%X",i_key_pad[i]);
	*/
	puts("\nNow SHA1");
	SHAInit(&sha);
	SHAUpdate(&sha, (BYTE*)i_key_pad_msg, (BLOCKSIZE + msg_length) );
	SHAFinal((unsigned char*)&o_key_pad_hsh[BLOCKSIZE], &sha);
	puts("\no_key_pad_hsh");
	for(i = 0;i < DIGEST_SIZE;i++)
		printf("%X",o_key_pad_hsh[i+BLOCKSIZE]);
	printf("ipad_length: %i\nopad_length: %i\n", strlen(i_key_pad_msg), strlen(o_key_pad_hsh));
	//strncat(o_key_pad_hsh,i_key_pad_msg,strlen(i_key_pad_msg));

	SHAInit(&sha);
	SHAUpdate(&sha, (BYTE*)o_key_pad_hsh, (BLOCKSIZE + DIGEST_SIZE) );
	SHAFinal((unsigned char*)digest, &sha);
	for(i = 0;i < DIGEST_SIZE;i++)
		printf("%X",digest[i]);
	return 0;
}
