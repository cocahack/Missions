# STEP1. 디지털 논리회로



## NAND 게이트

AND 게이트에 NOT(인버터)를 붙인 것과 동일하다.

입력이 2개일 때 NAND 게이트의 진리표(truth table)은 다음과 같다.

| NAND  | false | true  |
| :---- | :---- | :---- |
| false | true  | true  |
| true  | true  | false |

코드로 구현하면 다음과 같다.

```c++
bool nand(const bool a, const bool b)
{
    return !(a & b);
}
```



## NOR 게이트

OR 게이트에 NOT(인버터)를 붙인 것과 동일하다.

입력이 2개일 때 NOR 게이트의 진리표(truth table)은 다음과 같다.

| NOR   | false | true  |
| :---- | :---- | :---- |
| false | true  | false |
| true  | false | false |

코드로 구현하면 다음과 같다.

```c++
bool nor(const bool a, const bool b)
{
    return !(a | b);
}
```





## 이진 덧셈기

**가산기**(adder)란 덧셈 연산을 수행하는 논리 회로이다. 가산기의 종류에는 크게 반가산기(half adder)와 전가산기(full adder)가 있다.



### 반가산기

반가산기는 이진수의 한자리수를 연산하고, 자리올림수는 자리올림수 출력(carry out)에 따라 출력한다.

<img style="width:250px;" src="https://upload.wikimedia.org/wikipedia/commons/thumb/1/14/Half-adder.svg/2560px-Half-adder.svg.png">

반가산기는 AND, XOR 게이트 각각 하나씩 사용하여 구현할 수 있다. XOR 게이트는 AND, OR, NOT을 적절히 사용하여 구현할 수 있다. 이에 관한 내용은 [이곳](https://en.wikipedia.org/wiki/XOR_gate)에서 볼 수 있다.

반가산기의 진리표는 다음과 같다.

| A    | B    | C    | S    |
| ---- | ---- | ---- | ---- |
| 0    | 0    | 0    | 0    |
| 0    | 1    | 0    | 1    |
| 1    | 0    | 0    | 1    |
| 1    | 1    | 1    | 0    |

회로도를 보고 그대로 구현하면 된다.

```c++
bool xor_impl(const bool a, const bool b)
{
    return (a | b) & !(a & b);
}

vector<bool> half_adder(const bool a, const bool b)
{
    bool carry = a & b, sum = xor_impl(a, b);
    return {carry, sum};
}
```



### 전가산기

전가산기는 이진수의 한 자릿수를 연산하고, 하위의 자리올림수 입력을 포함하여 출력한다. 하위의 자리올림수 출력을 상위의 자리올림수 입력에 연결함으로써 임의의 자리수의 이진수 덧셈이 가능해진다. 

전가산기를 구현하는 방법은 두 개의 반가산기와 OR 게이트를 다음과 같이 연결하면 된다.

![nor](http://public.codesquad.kr/jk/cs23/step1-fulladder.png)

내부 구현을 가리면 다음과 같이 입력 3개를 받아 출력 2개를 만드는 구조가 된다.

![nor](http://public.codesquad.kr/jk/cs23/step1-fulladder-symbol.png)

전가산기 회로도의 첫번째 그림을 참조하여 구현하면 다음과 같다.

```c++
vector<bool> full_adder(const bool a, const bool b, const bool carry)
{
    auto first_exec = half_adder(a, b);
    auto second_exec = half_adder(carry, first_exec[1]);
    bool full_adder_carry = first_exec[0] ^ second_exec[0];

    return {full_adder_carry, second_exec[1]};
}
```



### 바이트 덧셈기

n-비트를 가산하려면 복수의 전가산기를 이용하는 방법이 있다. 4비트 가산기를 회로도로 나타내면 아래 그림과 같다.

<img style="width:400px" src="https://upload.wikimedia.org/wikipedia/commons/thumb/5/5d/4-bit_ripple_carry_adder.svg/1000px-4-bit_ripple_carry_adder.svg.png">

앞서 구현했던 전가산기를 이용하여 비트 수 만큼 루프를 돌리면 덧셈 구현이 가능하다. 

```c++
vector<bool> byte_adder(const vector<bool>& byte_a, const vector<bool>& byte_b)
{
    vector<bool> ret, sub_ret;
    bool carry = false;
    for(auto i = 0; i < byte_a.size(); ++i){
        sub_ret = full_adder(byte_a[i], byte_b[i], carry);
        carry = sub_ret[0];
        ret.push_back(sub_ret[1]);
    }

    ret.push_back(sub_ret[0]);

    return ret;
}
```



### 정리 

4비트나 16비트도 같은 함수로 한꺼번에 처리 가능한가? : 비트 수 만큼 루프를 돌기 때문에 가능하다.

byteA와 byteB 배열의 크기가 다르면 어떻게 처리할까? : byteA의 비트 수와 byteB의 비트 수 중 더 작은 비트를 가진 배열에 0을 채워 넣어 비트 수를 같게 만든 다음, 위에서 구현한 함수를 사용하면 된다.



## 진법 변환기

### 십진수를 이진수로

십진수를 이진수로 변환하는 방법은 십진수를 2로 나눈 나머지를 배열에 저장하고, 십진수를 2로 나누는 행동을 반복하면 된다.

```c++
vector<bool> dex2bin(int dex)
{
    vector<bool> ret;
    while (dex){
        ret.push_back(dex - (dex / 2 * 2));
        dex /= 2;
    }
    return ret;
}
```

C++에서는 정수형을 나누게 되면, 나머지는 버려지기 때문에 `dex - (dex / 2 * 2)`와 같은 방법으로 나머지를 구할 수 있다.

### 이진수를 십진수로

이진수에서 각 자릿수는 1, 2, 4, 8 … 등을 뜻하게 된다. 따라서 비트 수 만큼 루프를 돌면서 bits[i] * 2^i 의 결과를 모두 더한 다음, 그 값을 반환하면 된다.

```c++
int bin2dex(const vector<bool>& bin)
{
    if(bin.empty()) return 0;

    int ret = bin[0], base = 1;
    for(auto i = 1; i < bin.size(); ++i){
        base *= 2;
        ret += (int)bin[i] * base;
    }
    return ret;
}
```



### 정리

- 앞서 만들었던 이진 덧셈기에 입력과 출력에 연결해서 10진수 덧셈이 동작하는지 여부를 확인한다.

구현했던 함수들을 사용하면 된다.

```c++
int dex_adder(const int a, const int b)
{
    return bin2dex(byte_adder(dex2bin(a), dex2bin(b)));
}
```



- 같은 방식으로 2진수를 16진수로 변환하는 함수를 만들어본다.

2진수를 4바이트씩 끊어서 16진수로 변환한다. 비트 수가 4의 배수가 아니면, 4의 배수가 되도록 0을 채워넣는다. 쉬운 변환을 위해서 char형 배열을 사용했다.

```c++
char hex_map[16]{'0','1','2','3',
                 '4','5','6','7',
                 '8','9','A','B',
                 'C','D','E','F'};
                 
string bin2hex(vector<bool> a)
{
    string ret = "";
    int new_size = a.size();
    if(a.size() - (a.size() / 4 * 4) != 0){
        int padding = (a.size() / 4 + 1) * 4 - a.size();
        for(auto i = 0; i < padding; ++i){
            a.push_back(0);
        }
        new_size += padding;
    }

    for(auto i = 1; i <= new_size / 4; ++i){
        int sub_dex = bin2dex(vector<bool>(a.begin() + 4 * (i - 1),
                                           a.begin() + 4 * i));
        ret += hex_map[sub_dex];
    }

    return ret;
}
```



- 같은 방식으로 16진수를 2진수로 변환하는 함수를 만들어본다.

```c++
vector<bool> hex2bin(const string& hex)
{
    vector<bool> ret;
    for(char c : hex){
        int dex = (c >= 'A' ? 10 + c - 'A' :
                              c - '0');
        auto converted = dex2bin(dex);
        ret.insert(ret.end(), converted.begin(), converted.end());
    }

    return ret;
}
```

