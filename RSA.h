#pragma once

typedef long long LONG;

class RSA
{
	LONG kmin, kmax;

public:
	RSA(LONG kmin = 3, LONG kmax = 4294967296 - 1);
	~RSA(void);

	void generateKey(LONG* d, LONG* e, LONG* n, LONG* vp = 0, LONG* vq = 0);

	LONG encrypt(const LONG m, const LONG e, const LONG n);
	LONG decrypt(const LONG c, const LONG d, const LONG n);

	LONG encryptc(const char m, const LONG e, const LONG n);
	char decryptc(const LONG c, const LONG d, const LONG n);
};

LONG MMod(const LONG va, const LONG vn, const LONG m);
LONG PMod(const LONG va, const LONG vn, const LONG m);
void ExEuclideanGCD(LONG x, LONG y, LONG *a, LONG *b, LONG *c);
