# 基于RSA和MFC实现加密程序

## 前言

RSA公开密钥密码体制是一种使用不同的加密密钥与解密密钥，“由已知加密密钥推导出解密密钥在计算上是不可行的”密码体制。

在公开密钥密码体制中，加密密钥（即公开密钥）PK是公开信息，而解密密钥（即秘密密钥）SK是需要保密的。加密算法E和解密算法D也都是公开的。虽然解密密钥SK是由公开密钥PK决定的，但却不能根据PK计算出SK。

正是基于这种理论，1978年出现了著名的RSA算法，它通常是先生成一对RSA密钥，其中之一是保密密钥，由用户保存；另一个为公开密钥，可对外公开，甚至可在网络服务器中注册。为提高保密强度，RSA密钥至少为500位长，一般推荐使用1024位。这就使加密的计算量很大。为减少计算量，在传送信息时，常采用传统加密方法与公开密钥加密方法相结合的方式，即信息采用改进的DES或IDEA对话密钥加密，然后使用RSA密钥加密对话密钥和信息摘要。对方收到信息后，用不同的密钥解密并可核对信息摘要。

RSA是被研究得最广泛的公钥算法，从提出到现在已近三十年，经历了各种攻击的考验，逐渐为人们接受，普遍认为是目前最优秀的公钥方案之一。1983年麻省理工学院在美国为RSA算法申请了专利。

RSA允许你选择公钥的大小。512位的密钥被视为不安全的；768位的密钥不用担心受到除了国家安全管理（NSA）外的其他事物的危害；1024位的密钥几乎是安全的。RSA在一些主要产品内部都有嵌入，像Windows、网景Navigator、 Quicken和 Lotus Notes。

## 技术简介

### 算法原理

RSA公开密钥密码体制的原理是：根据数论，寻求两个大素数比较简单，而将它们的乘积进行因式分解却极其困难，因此可以将乘积公开作为加密密钥。

### 算法简要描述

1. 产生公私钥
   1. 随意选取两个足够大的素数，假定为P和Q，计算N = P * Q。
   2. 求欧拉函数r =φ(N) =φ(P)φ(Q) = (P - 1)(Q - 1)。
   3. 选择一个小于r的整数e，使e与r互质。并求得e关于r的模逆元，命名为d，即ed mod r = 1。
   4. N和e组成公钥，N和d组成私钥。
2. 加密信息
   1. 将消息m每一个字转换成一定的编码，计算S = me mod N。
   2. 计算结果S也被称为加密信息。
3. 解密信息
   1. 将加密信息S，对应每一个字进行计算m = Sd mod N。
   2. 计算结果m即是原始信息。

### 安全性问题

假设黑客获取到加密信息和公钥，即知道S，N，e，但是无法知道私钥d，最简单的方法是将N分解为P和Q，再根据ed mod r = 1，计算出d，再代入解密公式m = Sd mod N，求解原始信息。

​    至今为止也没有人能够证明对N进行因数分解是唯一的从S导出N的方法，直到今天也还没有找到比它更简单的方法。（至少没有公开的方法。）

​    因此，在现在这个时代，一般认为只要N足够大，就没有对RSA加密算法破解的方法了。

### 速度问题

比起AES、3DES和其它对称算法来说，RSA要慢得多。实际的运用（如TLS）一般结合了对称加密（如AES）和非对称加密（如RSA）两者。

### 签名信息

RSA也可以用来为一个消息署名。假如想传递一个署名的消息的话，那么可以为消息计算一个散列值（Message digest），然后用私钥“加密”（如同前面“加密消息”的步骤）这个散列值并将这个“署名”加在消息的后面。这个消息只有用公钥才能被解密。获得这个消息后可以用公钥“解密”（如同前面“解密消息”的步骤）这个散列值，然后将这个数据与他自己为这个消息计算的散列值相比较。假如两者相符的话，那么就可以知道发信人持有加密的私钥，以及这个消息在传播路径上没有被篡改过。

## 实现简介

### 在指定范围取随机素数

先在指定范围取一个数，如果不是素数，则在指定范围随机加一个数，直到是素数

```c++
/*
* 功能：随机产生一个满足范围的素数
* 参数：默认形参（MINPRIME，MAXPRIME）
* 返回：素数（long long）
*/
long long RSA::getPrime(long long min, long long max) {
	long long prime = getNum(rand(), min, max);
	while (isPrime(prime) == false) {
		prime = getNum(prime + rand(), min, max);
	}
	return prime;
}
```

### 获取公钥

在r/2 ~r之间取公钥e，处理过程：先取范围内的一个素数，如果和r没有互质，则循环进行，直到取到公钥e

```c++
/*
* 功能：获取一个公钥e
* 参数：void
* 返回值：long long
*/
long long RSA::getE() {
	long long e = 0;
	do {
		e = getPrime(phi / 2, phi);
	} while (relPrime(e, phi) > 1);
	//e = 3;
	return e;
}
```

### 获取私钥

使用扩展欧几里得算法，求取私钥d，使得满足ed mod r = 1。如果使用扩展欧几里得算法算取的结果是负数，通过再＋r，进行调整为正数。

```c++
/*
* 功能：获取一个私钥d
* 参数：void
* 返回值：long long
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
```

### 公私钥组合方式

主要过程是：先将公钥e、私钥d和N转换成字符串，再通过“+”连接符，进行连接字符串，以下算法以公钥为例。

```c++
/*
* 功能：公钥转字符串e+n
* 参数：void
* 返回：公钥字符串
*/
string RSA::getPublic() {
	return twoLongtoString(e, n);
}
/*
* 功能：long long转加密字符串
* 参数：long long
* 返回：字符串
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
```

### 加密

将信息的每一位进行整数转换，每个单字符，如字母、数字、符号等将会转换成正数，而汉字则会转换成两个负数，再进行计算S = me mod N，将信息转换成数字数组，再按每一个数字位，按一定随机过程生成对应字符，最后组合成加密信息。

1. 数字转换成“随机”字符

    根据指定的一部分字符，进行十进制ASCII码模10的结果排序，例如余数为0的ASCII码字符，将对应数字0，以此类推，通过这种方式，达到了“随机”的效果，也加强了保密性和安全性。

    ```c++
    /*
    * 功能：单数字转单字符
    * 参数：int
    * 返回：char
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
        return char(code[r%index[t]][t]);
    }
    ```

2. 信息加密

    ```c++
    /*
    * 功能：加密
    * 参数：信息（string）,long long e, long long n
    * 返回：十进制加密报文
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
    ```

### 解密

先通过密文按位获取到各个数字，组成数字数组，再通过计算m = Sd mod N，获取到解密后的数字数组，根据加密的过程，逆推回去，返还出原始信息。

1. “随机”字符转成数字

   ```c++
   /*
   * 功能：字符转数字
   * 参数：char
   * 返回：int
   */
   int RSA::charToInt(char c) {
   	return int(c) % 10;
   }
   ```

2. 信息解密

   ```c++
   /*
   * 功能：解密
   * 参数：加密报文，私钥d，n
   * 返回：信息（string）
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
   ```

## 展示模型

### 加密

![image-20210505222907983](https://gitee.com/ruanxinwei/image/raw/master/image-20210505222907983.png)

### 解密

![image-20210505222936516](https://gitee.com/ruanxinwei/image/raw/master/RIP/image-20210505222936516.png)

## 主要应用方面

### 数据库数据保存方面

无论在构建网站还是APP，都离不开数据库的支持，如果数据库被黑客攻击，获取到数据库中的数据后，假设数据没有进行加密操作，将黑客很容易获取到有用的信息。通过在数据库存放数据之前，通过加密操作，将能大大提高黑客破解的成本，相对地就提高了数据的安全性，也在另一方面保证了私密数据不被直接破解。

### 信息传输方面

在现在十分发达的网络时代，人们生活中的交流，少不了要在网络上进行传输，而通过窃听的技术，很有可能就获取到了传输过程中的信息，所以想要保证信息的安全，加密技术必不可少。

### 身份确认方面

通过RSA加密技术，很容易能够确定是谁真正的发出这一条信息。如果在防诈骗等需要身份确认的地方，使用到了该技术，则能够大大降低人们被骗的可能性，也进一步保证了人们的钱财等的安全。