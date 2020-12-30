#include "pch.h"
#include "RSA_Algorithm.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <Windows.h>

using namespace std;

RSA::RSA()
{
	srand(int(time(0)));
	p = getPrime();
	//p = 3e9;
	q = getPrime();
	//q = 3e9;
	//p = 61;
	//q = 53;
	n = p * q;
	phi = (p - 1) * (q - 1);
	e = getE();
	//e = 17;
	d = getD();
}

RSA::~RSA()
{
}

/*
* ���ܣ��������һ�����㷶Χ������
* ������Ĭ���βΣ�MINPRIME��MAXPRIME��
* ���أ�����
*/
long long RSA::getPrime(long long min, long long max) {
	long long prime = getNum(rand(), min, max);
	while (isPrime(prime) == false) {
		prime = getNum(prime + rand(), min, max);
	}
	return prime;
}

/*
* ���ܣ�ȷ��p�ǲ�������
* ������p
* ���أ�bool����
*/
bool RSA::isPrime(long long p) {
	if (p == 2 || p == 3) {
		return true;
	}
	else if (p < 2){
		return false;
	}
	for (long long i = 2; i <= sqrt(p); ++i) {
		if (p % i == 0) {
			return false;
		}
	}
	return true;
}

/*
* ���ܣ�����һ�������
* ������min,max
* ���أ�min<=long long<=max
*/
long long RSA::getRandNum(long long min, long long max) {
	long long n = rand();
	return getNum(n, min, max);
}

/*
* ���ܣ������ɺ������
* ��������Ҫ������������С���������
* ���أ�������Ҫ��������������һ��������С���������֮�������min<=n<=max��
*/
long long RSA::getNum(long long n, long long min, long long max) {
	if (n >= min && n <= max) {
		return n;
	}
	else {
		do
		{
			if (n < 0) {
				n = -n;
			}
			n = n % (max - min) + min;
		} while (n < min || n > max);
	}
	return n;
}

/*
* ���ܣ��ж�m��n�Ƿ���
* ������long long��long long
* ����ֵ�����������long long��
*/
long long RSA::relPrime(long long m, long long n) {
	while (n != 0) {
		long long r = m % n;
		m = n;
		n = r;
	}
	return m;
}

/*
* ���ܣ���ȡһ����Կe
* ������void
* ����ֵ��long long
*/
long long RSA::getE() {
	long long e = 0;
	do {
		e = getPrime(phi / 2, phi);
	} while (relPrime(e, phi) > 1);
	//e = 3;
	return e;
}

/*
* ���ܣ���ȡһ��˽Կd
* ������void
* ����ֵ��long long
*/
long long RSA::getD() {
	long long x1 = 1, x2 = 0, y1 = 0, y2 = 1;
	long long m = e, n = phi;
	//m = 3, n = 11;
	long long r, t;
	while (n > 1) {
		r = m / n, t = m % n;
		m = n;
		n = t;
		t = x1 - x2 * r;
		x1 = x2;
		x2 = t;
		t = y1 - y2 * r;
		y1 = y2;
		y2 = t;
	}
	if (x2 < 0) {
		x2 += phi;
	}
	return x2;
}

/*
* ���ܣ�a^b%c
* ������long long��long long, long long
* ���أ�a^b%c
*/
int RSA::modpow(long long a, long long b, long long c) {
	long long res = 1;
	while (b > 0) {
		if (b & 1) {
			res = (res * a) % c;
		}
		b = b >> 1;
		a = (a * a) % c;
	}
	return int(res);
}

//string RSA::deMessage(string m) {
//	cout << m << endl;
//	int i = 0;
//	printf("���ȣ�%d\n", m.size());
//	int* s = (int*)malloc(sizeof(int) * (m.size() + 1));
//	string str = "";
//	string restr;
//	char* res = (char*)malloc(sizeof(char) * (m.size() + 10));
//	if (res == NULL) {
//		return "ERROR";
//	}
//	else {
//		for (i = 0; i < m.size(); ++i) {
//			cout << "ԭ��" << int(m[i]) << "\t";
//			int t = modpow(int(m[i]), e, n);
//			cout << "�ܣ�" << t << endl;
//			//str[i] = t;
//			//str += modpow(m[i],e, n);
//			//cout << int(str[i]) <<"ʵ�ʣ�" << t << endl;
//			t = (modpow(t, d, n));
//			res[i] = t;
//			//restr[i] = t;
//			//restr += (modpow(t, d, n));
//			cout << "�⣺" << t << endl;
//		}
//		res[i] = '\0';
//		
//		restr = res;
//	}
//	return restr;
//}

/*
* ���ܣ�����
* ��������Ϣ��string������Կ��string��
* ���أ�string
*/
string RSA::encrypt(string m, string p) {
	long long i = 0, j = 0;
	stringTotwoLong(p, i, j);
	//return encrypt(m, i, j);	//����ʮ���Ƽ��ַ���
	return intsStringtoString(encrypt(m, i, j));	//���ؼ����ַ���
}

/*
* ���ܣ�����
* ��������Ϣ��string��,long long e, long long n
* ���أ�ʮ���Ƽ��ܱ���
*/
string RSA::encrypt(string m, long long e, long long n) {
	int* dm = (int*)malloc(sizeof(int) * (m.size() + 1));
	if (dm != NULL) {
		dm[0] = m.size();
		for (int i = 1; i <= m.size(); ++i) {
			//dm[i] = int(m[i - 1]);
			dm[i] = modpow(m[i - 1], e, n);
		}
	}
	return intsToString(dm);
}

/*
* ���ܣ�����
* ������ʮ���Ƽ��ܱ��ģ�string��
* ���أ���Ϣ��string��
*/
string RSA::decrypt(string m) {
	long long i = 0, j = 0;
	stringTotwoLong(getPrivate(), i, j);
	string str = stringtoIntsString(m);
	return decrypt(stringToInts(str), i, j);
}

/*
* ���ܣ�����
* ���������ܱ��ģ�string��,��Կ��string��
* ���أ���Ϣ��string��
*/
string RSA::decrypt(string m, string p) {
	long long i = 0, j = 0;
	stringTotwoLong(p, i, j);
	/*return decrypt(stringToInts(m), i, j);*/
	string str = stringtoIntsString(m);
	return decrypt(stringToInts(str), i, j);
}

/*
* ���ܣ�����
* ���������ܱ��ģ�int*��
* ���أ���Ϣ��string��
*/
//string RSA::decrypt(int* m) {
//	long long i = 0, j = 0;
//	stringTotwoLong(getPrivate(), i, j);
//	return decrypt(m, i, j);
//}

/*
* ���ܣ�����
* ���������ܱ��ģ�˽Կd��n
* ���أ���Ϣ��string��
*/
string RSA::decrypt(int* m, long long d, long long n) {
	if (m != NULL) {
		string str;
		char* pstr = (char*)malloc(sizeof(char) * (m[0] + 1));
		for (int i = 1; i <= m[0]; ++i) {
			pstr[i - 1] = modpow(m[i], d, n);
		}
		pstr[m[0]] = '\0';
		str = pstr;
		return str;
	}
	return "ERROR";
}

/*
* ���ܣ���Կת�ַ���e+n
* ������void
* ���أ���Կ�ַ���
*/
string RSA::getPublic() {
	return twoLongtoString(e, n);
}

/*
* ���ܣ�˽Կת�ַ���d+n
* ������void
* ���أ�˽Կ�ַ���
*/
string RSA::getPrivate() {
	return twoLongtoString(d, n);
}

/*
* ���ܣ���ʮ���Ƽ��ܱ���ת���ɼ��ܱ��ģ�string��
* ��������ʮ���Ƽ��ܱ��ģ�string��
* ���أ����ܱ��ģ�string��
*/
string RSA::intsStringtoString(string ints) {
	string s = "";
	for (int i = 0; i < ints.size(); ++i) {
		if (ints[i] == '-') {
			//58-62 : ; < = > (����=)
			//      0 1 2   4
			//	   58 59 60 62
			int r = rand() % 4;
			if (r > 2) {
				r += 1;
			}
			s += char(58 + r);
			//s += '/';
		}
		else {
			s += intToChar(ints[i] - '0');
		}
	}
	return s;
}

/*
* ���ܣ����ܱ��ģ�string��ת���ɼ�ʮ���Ƽ��ܱ���
* ���������ܱ��ģ�string��
* ���أ���ʮ���Ƽ��ܱ��ģ�string��
*/
string RSA::stringtoIntsString(string str){
	string ints = "";
	for (int i = 0; i < str.size(); ++i) {
		if (str[i]==':'||str[i]==';' || str[i] == '<' || str[i] == '>') {
			ints += '-';
		}
		else {
			ints += charToInt(str[i]) + '0';
		}
	}
	return ints;
}

/*
* ���ܣ�����long longת�ַ���
* ������e��long long����n��long long��
* ���أ���Կ�ַ�����+�����зָ�
*/
string RSA::twoLongtoString(long long e, long long n) {
	return longToString(e) + "+" + longToString(n);
}

/*
* ���ܣ��ַ�����e��long long����n��long long��
* ������string��long long&��long long&
* ���أ�void
*/
void RSA::stringTotwoLong(string s, long long& e, long long& n) {
	int index = s.find("+");
	e = 0;
	for (int i = 0; i < index; ++i) {
		e *= 10;
		e += charToInt(s[i]);
	}
	n = 0;
	for (int i = index + 1; i < s.size(); ++i) {
		n *= 10;
		n += charToInt(s[i]);
	}
}

/*
* ���ܣ�long longת�����ַ���
* ������long long
* ���أ��ַ���
*/
string RSA::longToString(long long s) {
	if (s < 0) {
		return "";
	}
	int length = 0;
	long long t = s;
	while (t > 0) {
		t /= 10;
		++length;
	}
	t = s;
	char* str = (char*)malloc(sizeof(char) * (length + 1));
	str[length] = '\0';
	while (t > 0) {
		--length;
		str[length] = intToChar(t % 10);
		t /= 10;
	}
	return str;
}

/*
* ���ܣ������ַ���תlong long
* ������string
* ����ֵ��long long
*/
long long RSA::stringToLong(string str) {
	long long ans = 0;
	for (int i = 0; i < str.size(); ++i) {
		ans = ans * 10 + charToInt(str[i]);
	}
	return ans;
}

/*
* ���ܣ���������ת�ַ���
* ������int*
* ���أ�string
*/
string RSA::intsToString(int* ints) {
	string s = "";
	for (int i = 0; i <= ints[0]; ++i) {
		s += intToString(ints[i]);
	}
	return s;
}

/*
* ���ܣ��ַ���ת��������
* ������string
* ���أ�int*
*/
int* RSA::stringToInts(string s) {
	int length = s.size() / 10;
	int* ints = (int*)malloc(sizeof(int) * length);
	if (ints == NULL) {
	}
	else {
		for (int i = 0; i < length; ++i) {
			//cout << s.substr(i*10, 10) << endl;
			ints[i] = atoi(s.substr(i*10, 10).c_str());
			//cout << ints[i] << endl;
		}
	}
	return ints;
}

/*
* ���ܣ�������ת���ַ�
* ������int
* ���أ�char
*/
char RSA::intToChar(int t) {
	int r = rand();
	int index[] = { 7,6,6,6,6,7,7,8,8,7 };
	int init[10], code[10][10];
	for (int i = 0; i < 10; ++i) {
		init[i] = 0;
		for (int j = 0; j < 10; ++j) {
			code[i][j] = 0;
		}
	}
	for (int i = 33; i <= 122; ++i) {
		if ((i >= 33 && i <= 38) || (48 <= i && i <= 57) || (65 <= i && i <= 90) || (97 <= i && i <= 122)) {
			code[init[i % 10]][i % 10] = i;
			init[i % 10]++;
		}
	}
	//cout << " " << code[r % index[t]][t];
	return char(code[r%index[t]][t]);
}

/*
* ���ܣ�intתstring����10λ
* ������int
* ����ֵ��string
*/
string RSA::intToString(int num) {
	string s = "";
	int length = 0;
	if (num < 0) {
		s = "-";
		length += 1;
		num = -num;
	}
	//if (num >= 0) {
	//	
	//}
	//else {
	//	s += "-";
	//	length = getIntLength(-num) + 1;
	//}
	length += getIntLength(num);
	while (length < 10) {
		s += "0";
		++length;
	}
	s += to_string(num);
	return s;
}

/*
* ���ܣ��ַ�ת����
* ������char
* ���أ�int
*/
int RSA::charToInt(char c) {
	return int(c) % 10;
}

/*
* ���ܣ���ȡ����λ��
* ������int
* ����ֵ��length��int��
*/
int RSA::getIntLength(int num) {
	if (num == 0) {
		return 1;
	}
	int t = num;
	int length = 0;
	while (t) {
		++length;
		t /= 10;
	}
	return length;
}