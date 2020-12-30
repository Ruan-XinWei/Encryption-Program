#pragma once
#include <string>
using namespace std;
class RSA
{
public:
	RSA();
	~RSA();
	/*
	* ���ܣ�����
	* ��������Ϣ��string������Կ��string��
	* ���أ�string
	*/
	string encrypt(string m, string p);
	/*
	* ���ܣ�����
	* ��������Ϣ��string��
	* ���أ�
	*/
	string decrypt(string m);
	string decrypt(string m, string p);
	/*
	* ���ܣ���Կת�ַ���e+n
	* ������void
	* ���أ���Կ�ַ���
	*/
	string getPublic();
	/*
	* ���ܣ�˽Կת�ַ���d+n
	* ������void
	* ���أ�˽Կ�ַ���
	*/
	string getPrivate();
private:
	/*
	* ���ܣ�����
	* ��������Ϣ��string����e��long long����n��long long��
	* ���أ�ʮ���Ƽ��ܱ���
	*/
	string encrypt(string m, long long e, long long n);
	/*
	* ���ܣ�����
	* ���������ܱ��ģ�˽Կd��n
	* ���أ���Ϣ��string��
	*/
	string decrypt(int* m, long long d, long long n);

	//string deMessage(string m);
	long long p, q, phi, e, d, n;
	/*
	* ���ܣ��������һ�����㷶Χ������
	* ������Ĭ���βΣ�MINPRIME��MAXPRIME��
	* ���أ�����
	*/
	long long getPrime(long long min = MINPRIME, long long max = MAXPRIME);
	/*
	* ���ܣ�ȷ��p�ǲ�������
	* ������p
	* ���أ�bool����
	*/
	bool isPrime(long long p);
	/*
	* ���ܣ�����һ�������
	* ������min,max
	* ���أ�min<=long long<=max
	*/
	long long getRandNum(long long min, long long max);
	/*
	* ���ܣ������ɺ������
	* ��������Ҫ������������С���������
	* ���أ�������Ҫ��������������һ��������С���������֮�������min<=n<=max��
	*/
	long long getNum(long long n, long long min = MINPRIME, long long max = MAXPRIME);
	/*
	* ���ܣ��ж�m��n�Ƿ���
	* ������long long��long long
	* ����ֵ�����������long long��
	*/
	long long relPrime(long long m, long long n);
	/*
	* ���ܣ���ȡһ����Կe
	* ������void
	* ����ֵ��long long
	*/
	long long getE();
	/*
	* ���ܣ���ȡһ��˽Կd
	* ������void
	* ����ֵ��long long
	*/
	long long getD();
	/*
	* ���ܣ�a^b%c
	* ������long long��long long, long long
	* ���أ�a^b%c
	*/
	int modpow(long long a, long long b, long long c);
	/*
	* ���ܣ�����long longת�ַ���
	* ������e��long long����n��long long��
	* ���أ���Կ�ַ�����+�����зָ�
	*/
	string intsStringtoString(string ints);
	string stringtoIntsString(string str);
	string twoLongtoString(long long e, long long n);
	/*
	* ���ܣ��ַ�����e��long long����n��long long��
	* ������string��long long&��long long&
	* ���أ�void
	*/
	void stringTotwoLong(string s, long long& e, long long& n);
	/*
	* ���ܣ�long longת�����ַ���
	* ������long long
	* ���أ��ַ���
	*/
	string longToString(long long s);
	/*
	* ���ܣ������ַ���תlong long
	* ������string
	* ����ֵ��long long
	*/
	long long stringToLong(string str);
	string intsToString(int* ints);
	int* stringToInts(string s);
	/*
	* ���ܣ�������ת���ַ�
	* ������int
	* ���أ�char
	*/
	char intToChar(int t);
	string intToString(int num);
	/*
	* ���ܣ��ַ�ת����
	* ������char
	* ���أ�int
	*/
	int charToInt(char c);
	int getIntLength(int num);
	//long long p, q, phi, e, d, n;
	//long long p, q, phi;

	static const long long MAXPRIME = 20000;
	static const long long MINPRIME = 10240;
	//static const long long MAXPRIME = 1024;
	//static const long long MINPRIME = 100;
};