#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

bool xor_impl(const bool a, const bool b)
{
    return (a | b) & !(a & b);
}

bool nand(const bool a, const bool b)
{
    return !(a & b);
}

bool nor(const bool a, const bool b)
{
    return !(a | b);
}

vector<bool> half_adder(const bool a, const bool b)
{
    bool carry = a & b, sum = xor_impl(a, b);
    return {carry, sum};
}

vector<bool> full_adder(const bool a, const bool b, const bool carry)
{
    auto first_exec = half_adder(a, b);
    auto second_exec = half_adder(carry, first_exec[1]);
    bool full_adder_carry = first_exec[0] ^ second_exec[0];

    return {full_adder_carry, second_exec[1]};
}

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

vector<bool> dex2bin(int dex)
{
    vector<bool> ret;
    while (dex){
        ret.push_back(dex - (dex / 2 * 2));
        dex /= 2;
    }
    return ret;
}

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

int dex_adder(const int a, const int b)
{
    return bin2dex(byte_adder(dex2bin(a), dex2bin(b)));
}

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

template <class T>
bool vector_checker(const vector<T>& lhs, const vector<T>& rhs)
{
    return lhs == rhs;
}

int main(){
    int result;
    vector<bool> byte_a, byte_b;

    // nand test
    assert(nand(0, 0) == 1);
    assert(nand(0, 1) == 1);
    assert(nand(1, 0) == 1);
    assert(nand(1, 1) == 0);

    // nor test
    assert(nor(0, 0) == 1);
    assert(nor(0, 1) == 0);
    assert(nor(1, 0) == 0);
    assert(nor(1, 1) == 0);

    // Mission1-1 : Half Adder
    assert(vector_checker(half_adder(0, 0), {0, 0}) == 1);
    assert(vector_checker(half_adder(0, 1), {0, 1}) == 1);
    assert(vector_checker(half_adder(1, 0), {0, 1}) == 1);
    assert(vector_checker(half_adder(1, 1), {1, 0}) == 1);

    // Mission1-2 : Full Adder
    assert(vector_checker(full_adder(0, 0, 0), {0, 0}) == 1);
    assert(vector_checker(full_adder(0, 0, 1), {0, 1}) == 1);
    assert(vector_checker(full_adder(0, 1, 0), {0, 1}) == 1);
    assert(vector_checker(full_adder(0, 1, 1), {1, 0}) == 1);
    assert(vector_checker(full_adder(1, 0, 0), {0, 1}) == 1);
    assert(vector_checker(full_adder(1, 0, 1), {1, 0}) == 1);
    assert(vector_checker(full_adder(1, 1, 0), {1, 0}) == 1);
    assert(vector_checker(full_adder(1, 1, 1), {1, 1}) == 1);

    // Mission2-1 : Byte Adder
    byte_a = {1, 1, 0, 1, 1, 0, 1, 0};
    byte_b = {1, 0, 1, 1, 0, 0, 1, 1};
    assert(vector_checker(byte_adder(byte_a, byte_b), 
                                     {0, 0, 0, 1, 0, 1, 0, 0, 1}) == 1);
    byte_a = {1, 1, 0, 0, 1, 0, 1, 0};
    byte_b = {1, 1, 0, 1, 1, 0, 0, 1};
    assert(vector_checker(byte_adder(byte_a, byte_b), 
                                     {0, 1, 1, 1, 0, 1, 1, 1, 0}) == 1);

    // Mission 3-1
    assert(vector_checker(dex2bin(10), {0, 1, 0, 1}) == 1);
    assert(vector_checker(dex2bin(173), {1, 0, 1, 1, 0, 1, 0, 1}) == 1);

    // Mission 3-2
    assert(bin2dex({0, 1, 0, 1}) == 10);
    assert(bin2dex({1, 0, 1, 1, 0, 1, 0, 1}) == 173);

    // Exercise 1
    assert(dex_adder(15, 7) == 22);

    // Exercise 2
    assert(bin2hex({0, 1, 0, 1}) == "A");
    assert(bin2hex({1, 0, 1, 1, 0, 1, 0, 1}) == "DA");
    assert(bin2hex({1, 0, 1, 1, 0, 1, 0, 1, 1}) == "DA1"); // 429 -> 1AD

    // Exercise 3
    assert(vector_checker({0, 1, 0, 1}, 
                          hex2bin("A")) == true);
    assert(vector_checker({1, 0, 1, 1, 0, 1, 0, 1}, 
                          hex2bin("DA")) == true);
    assert(vector_checker({1, 0, 1, 1, 0, 1, 0, 1, 1}, 
                          hex2bin("DA1")) == true);



    cout << "Success" << endl;

    return 0;
}
