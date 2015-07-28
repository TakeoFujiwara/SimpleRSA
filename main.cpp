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

		char* m = "ガイウス・ユリウス・カエサル（古典ラテン語：Gaius Iulius Caesar、紀元前100年 - 紀元前44年3月15日[1]）は、共和政ローマ期の政治家、軍人であり、文筆家。「賽は投げられた」(Alea jacta est)、「来た、見た、勝った」(Veni, vidi, vici)などの引用句でも知られる。";

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
