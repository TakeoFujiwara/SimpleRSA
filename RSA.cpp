#include "RSA.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

bool isPrime(LONG n)
{
	if(n % 2 == 0) return false;

	LONG N = (LONG)::sqrt((long double)n);
	for(LONG i = 3; i < N; i+=2) {
		if(n % i == 0) {
			return false;
		}
	}

	return true;
}

LONG getRandom()
{
	LONG r = 0;
	LONG a = ::rand();
	a = a << 48;
	r += a;
	a = ::rand();
	a = a << 32;
	r += a;
	a = ::rand();
	a = a << 16;
	r += a;
	a = ::rand();
	r += a;
	return r;
}

LONG getPrime(LONG minnum, LONG m)
{
	LONG p = minnum + ::getRandom() % m;
	while(!::isPrime(p)) {
		p = minnum + ::getRandom() % m;
	}
	return p;
}

void ExEuclideanGCD(LONG x, LONG y, LONG *a, LONG *b, LONG *c)
{
	LONG r0 = x, r1 = y;
	LONG a0 = 1, a1 = 0;
	LONG b0 = 0, b1 = 1;

	while(r1 > 0) {
		LONG q1 = r0 / r1;
		LONG r2 = r0 % r1;
		LONG a2 = a0 - (q1 * a1);
		LONG b2 = b0 - (q1 * b1);
		r0 = r1; r1 = r2;
		a0 = a1; a1 = a2;
		b0 = b1; b1 = b2;
	}

	*c = r0;
	*a = a0;
	*b = b0;
}

LONG PMod(const LONG va, const LONG vn, const LONG m)
{
	LONG n = vn;
	LONG a = va % m;

	if(a < 0) {
		a = a + m;
	}
	
	LONG pw = 1;
	while(n >= 1) {
		if(n % 2 == 1) {
			pw = ::MMod(a, pw, m);
		}
		a = MMod(a, a, m);
		n = n / 2;
	}

	return pw;
}

LONG MMod(const LONG va, const LONG vn, const LONG m)
{
	LONG n = vn;
	LONG a = va % m;

	if(a < 0) {
		a = a + m;
	}

	LONG mu = 0L;
	while(n >= 1L) {
		if(n % 2 == 1) {
			mu = (a + mu) % m;
		}
		a = (a * 2) % m;
		n = n / 2;
	}

	return mu;
}

RSA::RSA(LONG kmin, LONG kmax)
{
	this->kmin = kmin;
	this->kmax = kmax;

	::srand((unsigned int)::time(NULL));
}

RSA::~RSA(void)
{
}

void RSA::generateKey(LONG* d, LONG* e, LONG* n, LONG* vp, LONG* vq)
{
	LONG p;
	LONG q;
	do {
		*e = 13;
		LONG r = this->kmax - this->kmin;
		p = ::getPrime(this->kmin, r);
		q = ::getPrime(this->kmin, r);
		while(p == q) q = ::getPrime(this->kmin, r);
		LONG a, b, c;

		::ExEuclideanGCD(*e, (p-1)*(q-1), &a, &b, &c);

		*d = a;
		*n = p * q;

		if(vp != 0) {
			*vp = p;
		}
		if(vq != 0) {
			*vq = q;
		}
	} while(*d < 2 || p < 0 || q < 0 || (*e) * (*d) < 0);
}

LONG RSA::encrypt(const LONG m, const LONG e, const LONG n)
{
	LONG c = ::PMod(m, e, n);
	return c;
}

LONG RSA::decrypt(const LONG c, const LONG d, const LONG n)
{
	LONG m = ::PMod(c, d, n);
	return m;
}

LONG RSA::encryptc(const char m, const LONG e, const LONG n)
{
	LONG mm = ((LONG)m) + 128L;
	LONG c = ::PMod(mm, e, n);
	return c;
}

char RSA::decryptc(const LONG c, const LONG d, const LONG n)
{
	LONG m = ::PMod(c, d, n);
	return (char)(m - 128L);
}
