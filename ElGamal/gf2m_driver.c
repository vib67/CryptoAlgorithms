#include <stdio.h>
#include <string.h>
#include "gf2m.h"

int main() {

	unsigned char check[] = {0x6d,0xfa,0x33,0x2d,0xa5,0x3b,0x94,0x09,0xad,0x72,0x01,0x09,0x07,0xf2,0xec,0xb8,0xeb,0x20,0xf4,0xc1,0xe7,0xdc,0x1c,0x12,0xa5,0xf8,0xdd,0xc0,0xca,0x18,0x2f,0xbf,0xf4,0x58,0xce,0x0e,0x72,0x35,0xa9,0xa2,0xf7,0xbc,0xf1,0x95,0x5c,0x66,0x49,0xc8,0x9c,0xd4,0x4a,0x55,0x2c,0x47,0x05,0xf0,0xf5,0x6d,0x2d,0x7c,0xec,0x7b,0x2a,0x30,0xaa,0x70,0x32,0x17,0xad,0xf3,0xf5,0x5b,0x97,0x99,0x3b,0xc3,0x2a,0xf0,0xc7,0xec,0x38,0xa8,0x9d,0x8a,0x63,0x3d,0x74,0xa0,0x8e,0xf1,0xd6,0x4b,0xf0,0x4d,0xe2,0x08,0xd3,0x86,0xf4,0x43,0x74,0x29,0xfa,0xd5,0x6a,0x07,0x72,0xb2,0x38,0x55,0x80,0x69,0x40,0x07,0x6e,0x39,0xdf,0xcf,0xc1,0x78,0x98,0x9d,0x1f,0xf1,0x3d,0xbe,0x66,0xee,0x1c,0xda,0x84,0xc6,0x3e,0x96,0x67,0xb7,0x0b,0x16,0x05,0x46,0xca,0x0b,0x0e,0xe4,0x75,0xb9,0x3a,0x8e,0xd6,0x78,0x1d,0xdc,0x2d,0x9e,0xd4,0x28,0xcd,0x41,0xfe,0x1d,0x05,0x31,0x26,0xd7,0xbe,0xbb,0x9e,0x34,0x71,0x15,0x8d,0x64,0xab,0xb2,0xfa,0xf8,0x0d,0x2a,0x69,0x1a,0x72,0x98,0x64,0xb3,0x27,0x62,0x64,0xb0,0x24,0x50,0x4b,0x78,0x60,0x6c,0xfb,0xae,0x25,0x10,0x68,0xe0,0x8f,0x5d,0xaa,0x1b,0xdc,0xef,0x42,0xe5,0xf0,0xf9,0x37,0xa6,0x64,0x4f,0x34,0xe1,0xe5,0xb0,0x73,0xba,0x5c,0xb7,0xcc,0xea,0x2e,0x0b,0xb2,0x0d,0x48,0xe1,0x94,0xef,0x77,0x80,0x53,0x72,0x0c,0x40,0x72,0x4f,0x80,0x1e,0xa1,0xeb,0xe4,0x07,0xd6,0x9b,0xdc,0xf0,0x70,0x76,0x1c,0x1f,0xca,0xd4,0xbf,0xf4,0x0d,0xed,0x09,0xcd,0x9a,0xf6,0xe4,0x01,0x65,0x73,0x1a,0x51,0x59,0x2e,0x68,0x35,0x2a,0x55,0xcf,0x12,0x9c,0xf6,0x76,0xef,0x01,0x9f,0x44,0xc5,0x60,0x39,0x73,0x77,0x61,0x1d,0x4c,0x40,0xb7,0x78,0x77,0x07,0xdf,0x5f,0x5e,0xf1,0x2d,0x0c,0xa3,0x5d,0xa0,0x80,0xd4,0xbc,0x2b,0xce,0xc3,0xe1,0xe1,0x80,0x92,0x7c,0x94,0xf3};

	ff_t check_priv = {0x69a9d730, 0xd6b6560e, 0xb7ec7679, 0xf5a702d2, 0xbaf31068, 0x3dd1fe13, 0x98296593, 0xc173cbaa, 0xa5a811f9, 0x051fe5e3, 0x56465cc7, 0xca225e3c, 0x08160477, 0xe023f173, 0xea6bc508, 0x2a8c4cd4, 0x5ad0764b, 0x25ba8aec, 0x1a09b769, 0x1cd7ef00, 0x57a8e4a2, 0xe5b32fd1, 0x00824ec5, 0x6ca1d0d2, 0x6ee26004, 0xaa3cb545, 0xb94f13ab, 0x648b7528, 0xb4f2935c, 0xda7418e0, 0x5234268a, 0x855597ff, 0x871f0f70, 0x47ca8e8f, 0xada8920b, 0x9b2f45e5, 0xbebe7700, 0x3e966ff2, 0xd5b4816e, 0x4e241a32};

	ff_t check_pub = {0x32e7d93d, 0x5e158710, 0xdc575eb3, 0x72252444, 0x15962325, 0x7e3acfcd, 0x9ff9976c, 0x3dc04514, 0xef1cff41, 0x06ce2180, 0x3c0dbd17, 0x6f740081, 0xa7f01614, 0x6b916812, 0x1a3e08bd, 0x4a3e1a0c, 0xa668cbeb, 0x201ad01b, 0x17fd765b, 0xd303e3e0, 0x13cbdace, 0xcedf43a9, 0x03ad6d6b, 0x7479ce8f, 0xf3d1b084, 0xa6c8e443, 0xecebb40d, 0x730f1e36, 0x6e5d8fe1, 0xb023fbbd, 0x4f41eb42, 0x2e118341, 0x67f3f4ef, 0x03c4934f, 0x5db9b0ab, 0x9c826959, 0x0abc565b, 0xbeeabf40, 0xf9a035f8, 0x217f148b};

	ff_t check_inv = {0x6af8aea8, 0x33781ef7, 0xff17f3a2, 0x72cb3023, 0x1db96c52, 0x70112735, 0xc884f430, 0x17ac146e, 0x4807e1d7, 0x0896358f, 0x39efc505, 0xf01b620a, 0x76059220, 0x064145e9, 0x76d759fc, 0x350ad321, 0xac97c429, 0x8ede27ea, 0x1d90461f, 0x16408a75, 0xea1ae86d, 0x0733dca5, 0x50b15c71, 0xda1a9e98, 0x2eb9d9b3, 0xd2b146ff, 0x554749a3, 0xb8cc82ab, 0xe0cec918, 0x1a43fcb9, 0x39a521cf, 0x5e867785, 0xa2b5c116, 0xa315e73c, 0x499c6375, 0x5b131225, 0x395b26c8, 0xa58837e8, 0xd6dc9778, 0x37219e90};

	ff_t private, public, t0;
	unsigned char m[] = {0, 1, 2, 3}, b[NUMWORDS*4], c[NUMWORDS*8];

	// check 1: field inversion
	ff_rnd(t0);


       
      
	ff_inv(t0, t0);
	printf("%s\n", !memcmp(t0, check_inv, NUMWORDS * sizeof(uint32_t)) ? "PASS" : "FAIL");

	// check 2-3: key pair generation
	ff_keygen(private, public);
	printf("%s\n", !memcmp(private, check_priv, NUMWORDS * sizeof(uint32_t)) ? "PASS" : "FAIL");
	printf("%s\n", !memcmp(public, check_pub, NUMWORDS * sizeof(uint32_t)) ? "PASS" : "FAIL");

	// check 4: public key encryption
	ff_encrypt(c, m, 4, public);
	printf("%s\n", !memcmp(c, check, 320) ? "PASS" : "FAIL");

	// check 5: public key decryption
	int len = ff_decrypt(b, c, private);
	printf("%s\n", len == 4 && !memcmp(m, b, len) ? "PASS" : "FAIL");

	return 0;
}

//	for(int i=0; i<NUMWORDS; i++) printf("0x%08x, ", c[i]);
