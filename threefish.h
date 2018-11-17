/* Implement the following API.
 * You can add your own functions above, but don't modify below this line.
 */

#include <inttypes.h>
/* Under key at k and tweak at t, encrypt 32 bytes of plaintext at p and store it at c. */
void threefish(unsigned char *c, const unsigned char *p, const unsigned char *k, const unsigned char *t);

uint64_t * get_round_key(uint64_t * keys, uint64_t * t, int round);
uint64_t * MIXfunction(uint64_t x_0, uint64_t x_1, int j, int round);