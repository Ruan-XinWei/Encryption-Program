#pragma once
#include <string>
using namespace std;
class RSA
{
public:
	RSA();
	~RSA();
	/*
	* 功能：加密
	* 参数：信息（string），公钥（string）
	* 返回：string
	*/
	string encrypt(string m, string p);
	/*
	* 功能：解密
	* 参数：信息（string）
	* 返回：
	*/
	string decrypt(string m);
	string decrypt(string m, string p);
	/*
	* 功能：公钥转字符串e+n
	* 参数：void
	* 返回：公钥字符串
	*/
	string getPublic();
	/*
	* 功能：私钥转字符串d+n
	* 参数：void
	* 返回：私钥字符串
	*/
	string getPrivate();
private:
	/*
	* 功能：加密
	* 参数：信息（string），e（long long），n（long long）
	* 返回：十进制加密报文
	*/
	string encrypt(string m, long long e, long long n);
	/*
	* 功能：解密
	* 参数：加密报文，私钥d，n
	* 返回：信息（string）
	*/
	string decrypt(int* m, long long d, long long n);

	//string deMessage(string m);
	long long p, q, phi, e, d, n;
	/*
	* 功能：随机产生一个满足范围的素数
	* 参数：默认形参（MINPRIME，MAXPRIME）
	* 返回：素数
	*/
	long long getPrime(long long min = MINPRIME, long long max = MAXPRIME);
	/*
	* 功能：确定p是不是素数
	* 参数：p
	* 返回：bool类型
	*/
	bool isPrime(long long p);
	/*
	* 功能：返回一个随机数
	* 参数：min,max
	* 返回：min<=long long<=max
	*/
	long long getRandNum(long long min, long long max);
	/*
	* 功能：调整成合理的数
	* 参数：需要调整的数，最小数，最大数
	* 返回：基于需要调整的数，返回一个处于最小数和最大数之间的数（min<=n<=max）
	*/
	long long getNum(long long n, long long min = MINPRIME, long long max = MAXPRIME);
	/*
	* 功能：判断m，n是否互质
	* 参数：long long，long long
	* 返回值：最大公因数（long long）
	*/
	long long relPrime(long long m, long long n);
	/*
	* 功能：获取一个公钥e
	* 参数：void
	* 返回值：long long
	*/
	long long getE();
	/*
	* 功能：获取一个私钥d
	* 参数：void
	* 返回值：long long
	*/
	long long getD();
	/*
	* 功能：a^b%c
	* 参数：long long，long long, long long
	* 返回：a^b%c
	*/
	int modpow(long long a, long long b, long long c);
	/*
	* 功能：两个long long转字符串
	* 参数：e（long long），n（long long）
	* 返回：公钥字符串“+”进行分隔
	*/
	string intsStringtoString(string ints);
	string stringtoIntsString(string str);
	string twoLongtoString(long long e, long long n);
	/*
	* 功能：字符串解e（long long），n（long long）
	* 参数：string，long long&，long long&
	* 返回：void
	*/
	void stringTotwoLong(string s, long long& e, long long& n);
	/*
	* 功能：long long转加密字符串
	* 参数：long long
	* 返回：字符串
	*/
	string longToString(long long s);
	/*
	* 功能：加密字符串转long long
	* 参数：string
	* 返回值：long long
	*/
	long long stringToLong(string str);
	string intsToString(int* ints);
	int* stringToInts(string s);
	/*
	* 功能：单数字转单字符
	* 参数：int
	* 返回：char
	*/
	char intToChar(int t);
	string intToString(int num);
	/*
	* 功能：字符转数字
	* 参数：char
	* 返回：int
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