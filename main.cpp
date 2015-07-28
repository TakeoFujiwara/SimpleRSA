#include <stdio.h>
#include <string.h>
#include "RSA.h"

int main()
{
	{
		LONG a, n, m, v, d;

		a = 1234567890123;
		n = 184436886841;
		m = 86706662670157;

		v = ::PMod(a, n, m);

		::printf("%lld\n", v);

		a = v;
		d = 70276475859277;

		v = ::PMod(a, d, m);

		::printf("%lld\n", v);
	}

	{
		RSA rsa(3, 65536 - 1);
		LONG d, e, n, p, q;
		LONG m = 12345678, c;

		rsa.generateKey(&d, &e, &n, &p, &q);

		LONG ed = e * d;
		LONG B = (p-1)*(q-1);
		LONG v = ed % B;

		c = ::PMod(m, e, n);
		m = 0;
		::printf("%lld\n", c);

		m = ::PMod(c, d, n);
		::printf("%lld\n", m);

	}

	{
		RSA rsa;
		LONG d, e, n;
		LONG m = 12345678, c;

		rsa.generateKey(&d, &e, &n);

		c = rsa.encrypt(m, e, n);
		m = 0;
		::printf("%lld\n", c);

		m = rsa.decrypt(c, d, n);
		::printf("%lld\n", m);

	}

	{
		RSA rsa;
		LONG d, e, n, p, q;
		rsa.generateKey(&d, &e, &n, &p, &q);
		LONG ed = e * d;
		LONG B = (p-1)*(q-1);
		LONG v = ed % B;

		char* m = "�K�C�E�X�E�����E�X�E�J�G�T���i�ÓT���e����FGaius Iulius Caesar�A�I���O100�N - �I���O44�N3��15��[1]�j�́A���a�����[�}���̐����ƁA�R�l�ł���A���M�ƁB�u�΂͓�����ꂽ�v(Alea jacta est)�A�u�����A�����A�������v(Veni, vidi, vici)�Ȃǂ̈��p��ł��m����B";

		size_t len = ::strlen(m);
		LONG* c = new LONG [len];
		for(size_t i = 0; i < len; i++) {
			c[i] = rsa.encryptc(m[i], e, n);
		}

		char* mm = new char [len + 1];
		for(size_t i = 0; i < len; i++) {
			mm[i] = rsa.decryptc(c[i], d, n);
		}
		mm[len] = 0;

		::printf("%s\n", mm);
	}
}
