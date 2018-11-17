#include <stdio.h>
#include <stdint.h>
#include<string.h>
#include <inttypes.h>
#include <stdlib.h>
#include "threefish.h"

#if 0 /* TODO change to 0 after you complete this task */
/*

TODO FREE TEXT ASSIGNMENT

If there was a FAQ for this assignment, what question and answer would've helped you the most?

Q: Do you use C or C++ compiler when you are running the program

A: No idea

*/
#warning "FAIL you have not completed the free text assignment"
#endif

uint64_t * MIXfunction(uint64_t x_0, uint64_t x_1, int j, int round) {

	static  uint64_t results[2];
	uint64_t left_shift;
	uint64_t right_shift;
	uint64_t rotate;
	int rotates;

	static int const_R[8][2] = { { 14,16 },{ 52,57 },{ 23,40 },{ 5,37 },{ 25,33 },{ 46,12 },{ 58,22 },{ 32,32 } };

	results[0] = x_0 + x_1;
	rotates = const_R[round % 8][j];

	 left_shift = x_1 << rotates;
	 right_shift = x_1 >> (64 - rotates);
	 rotate = left_shift ^ right_shift;
	results[1] = rotate ^ results[0];

	return results;

}

uint64_t * get_round_key(uint64_t * keys, uint64_t * t, int round) {

	static uint64_t round_key[4];


	round_key[0] = keys[round % 5];


	round_key[1] = keys[(round + 1) % 5] + t[round % 3];


	round_key[2] = keys[(round + 2) % 5] + t[(round + 1) % 3];


	round_key[3] = keys[(round + 3) % 5] + round;

	return round_key;

}

/* Under key at k and tweak at t, encrypt 32 bytes of plaintext at p and store it at c. */
void threefish(unsigned char *c, const unsigned char *p, const unsigned char *k, const unsigned char *t) {

	uint64_t t_array[3];

	uint64_t p_array[4];
	uint64_t k_array[5];


	uint64_t k_5 = 0x1BD11BDAA9FC1A22;
	uint64_t new_index_3;

	uint64_t * f_1;
	uint64_t * f_2;

	uint64_t t_2;

	uint64_t * new_key;
	uint64_t * final_key;


	memcpy(t_array, t, 16);
	memcpy(k_array, k, 32);
	memcpy(p_array, p, 32);


	t_2 = t_array[0] ^ t_array[1];
	t_array[2] = t_2;


	for (int i = 0; i<4; i++) {
		k_5 = k_5 ^k_array[i];
	}
	k_array[4] = k_5;


	for (int rounds = 0; rounds<72; rounds++) {


		if (rounds % 4 == 0) {

			new_key = get_round_key(k_array, t_array, rounds / 4);


			for (int index = 0; index<4; index++) {

				p_array[index] = p_array[index] + new_key[index];
			}

		}

		f_1 = MIXfunction(p_array[0], p_array[1], 0, rounds);

		p_array[0] = f_1[0];
		new_index_3 = f_1[1];


		f_2 = MIXfunction(p_array[2], p_array[3], 1, rounds);


		p_array[1] = f_2[1];
		p_array[2] = f_2[0];
		p_array[3] = new_index_3;




	}
	final_key = get_round_key(k_array, t_array, 18);

	for (int i = 0; i<4; i++) {
		p_array[i] = p_array[i] + final_key[i];
	}

	memcpy(c, p_array, 32);



	return;
}


