#include <stdio.h>
#include <string.h>
#include "gf2m.h"

int main() {

	ff_t c, d, zero, one; ff_zero(zero); ff_zero(one); one[0] = 0x1;

	ff_t a = {0x94ccba66, 0x0b922a58, 0x43dfa1d6, 0x1860c1fa, 0xf566c8bb, 0x0a2c46e6, 0xa82a229d, 0x5bdc0859, 0x743ac579, 0x0149e61c, 0xdb7557d0, 0x84aaf6fc, 0x5c1ebd9d, 0xaf4d0a4c, 0x35e6e149, 0x5cdcdb06, 0xd9e9f7c1, 0x7fcedd2c, 0x6ef5df79, 0x87928289, 0x203332b8, 0x2d34f6ab, 0xd727b998, 0xb7436e13, 0xbe8506ab, 0xdb688a68, 0xe978945d, 0x75b69a48, 0x64c09edf, 0xbcdcb666, 0xe21f6f72, 0x36f5116f, 0xdb3da236, 0x9f71f0ae, 0x4bddd28a, 0x1dcfbb1b, 0x9b3b7c35, 0x619d3552, 0x141a4617, 0x175e699d};
	ff_t b = {0x212cb2f5, 0x8fa3193d, 0xe756f455, 0x2ddef46f, 0xe5c190ea, 0xcb0a47de, 0x02c3460b, 0x3df84e46, 0xa180fee8, 0x46ad72af, 0xf4628fe5, 0x9122cf0e, 0x85532090, 0x6ccae256, 0x720bd4fc, 0x82dd4792, 0x384fb7df, 0xb83ec7b1, 0xec6a2928, 0x2a0f4982, 0xe8c7b704, 0x0daa7bb8, 0x51d9931a, 0x1128bea0, 0xdafa703a, 0x531056a2, 0x00528552, 0x1a51c93f, 0x69594a3d, 0xa4be7a0a, 0x245c009e, 0xd1f187fd, 0x03fc8b56, 0x8a5f505f, 0x6201a420, 0x09d9c08e, 0x052585c5, 0x80a066a9, 0x2d5907db, 0x41dd3e8f};
	ff_t check = {0x3df70052, 0x2c5f468b, 0x4b829154, 0x5bc18ca0, 0x5d6edfd2, 0xd58d45e7, 0x9425ec7d, 0x9aadf5a7, 0xc531e3b4, 0x6e5b6bda, 0x6348e455, 0x25869611, 0x3e8519ed, 0x183f6e67, 0x2409a33f, 0x748ac5d8, 0x071a7ccb, 0x96b161b2, 0x8d6cf9c7, 0xcb9d071c, 0x082f472a, 0xeae8cf43, 0xefb10af9, 0x123c89c9, 0x873a5ab8, 0xe34c8632, 0x11008ec2, 0xd650fe40, 0x1a0c0000, 0x99c34cb2, 0x077eb9bf, 0x0f86d600, 0x6b7d531a, 0x20445628, 0xeaae9e8e, 0xde7bddb1, 0x76d669b0, 0xc7d397b3, 0xccddbc0a, 0x6c93a5ef};
	ff_t checkexp = {0xf42eb58d, 0x7fcb0a61, 0x5f1284d9, 0x583adb55, 0x7f91a692, 0x8e951ac2, 0x93ab10ef, 0xdd101b57, 0xc1505d09, 0x527d5ec8, 0x1497c50b, 0x1563ec12, 0x141af09f, 0x12811c2a, 0x23bfd9b0, 0x7015df7e, 0x020e1b32, 0x7aa0e653, 0xa3dc879d, 0x11665182, 0xc8740f5e, 0xc9186cd9, 0xbf2dac97, 0x79e7a6b3, 0x76dd1cf9, 0x9e505150, 0x934271fe, 0xf949431e, 0x5e4634ed, 0x88ea5420, 0x46aeaf3d, 0x744ca69f, 0x204b6cd2, 0x2f6202c4, 0x5208091d, 0xe8fe4cdb, 0xd3cd8010, 0xfdc3c1aa, 0xb60d418f, 0x7b3b91e7};

	// test 1: general multiplication
	ff_mul(c, a, b);
	if(!memcmp(c, check, NUMWORDS * sizeof(uint32_t))) printf("PASS\n");
	else printf("FAIL\n");

	// test 2: multiplication by zero
	ff_mul(c, a, zero);
	if(!memcmp(c, zero, NUMWORDS * sizeof(uint32_t))) printf("PASS\n");
	else printf("FAIL\n");

	// test 3: multiplication by one
	ff_mul(c, a, one);
	if(!memcmp(c, a, NUMWORDS * sizeof(uint32_t))) printf("PASS\n");
	else printf("FAIL\n");

	// test 4: general exponentiation
	ff_exp(c, a, b);
	if(!memcmp(c, checkexp, NUMWORDS * sizeof(uint32_t))) printf("PASS\n");
	else printf("FAIL\n");

	// test 5: power 0
	ff_exp(c, a, zero);
	if(!memcmp(c, one, NUMWORDS * sizeof(uint32_t))) printf("PASS\n");
	else printf("FAIL\n");

	// test 6: power 1
	ff_exp(c, a, one);
	if(!memcmp(c, a, NUMWORDS * sizeof(uint32_t))) printf("PASS\n");
	else printf("FAIL\n");

	// test 7: power 2
	ff_zero(d); d[0] = 0x2;
	ff_exp(c, a, d); ff_mul(d, a, a);
	if(!memcmp(c, d, NUMWORDS * sizeof(uint32_t))) printf("PASS\n");
	else printf("FAIL\n");

	// test 8: power 2^m
	ff_copy(c, a);
        //ff_print(c);
	for(int i=0; i<1279; i++) ff_mul(c, c, c);
	if(!memcmp(c, a, NUMWORDS * sizeof(uint32_t))) printf("PASS\n");
	else printf("FAIL\n");

	// test 9: inverse
	memset(d, 0xFF, NUMWORDS * sizeof(uint32_t)); d[NUMWORDS-1] = 0x7FFFFFFF; d[0] = 0xFFFFFFFE;
	ff_exp(c, a, d);
	ff_mul(c, c, a);
	if(!memcmp(c, one, NUMWORDS * sizeof(uint32_t))) printf("PASS\n");
	else printf("FAIL\n");

	return 0;
}

//	for(int i=0; i<NUMWORDS; i++) printf("0x%08x, ", c[i]);
