/*    
 
  December Challenge 2019 Division 2
  problem 4-- Addition
  solution by -- RITIK DAGAR
                 SRM IST NCR CAMPUS
                 contact -- 9958152151
        
*/

#include <iostream>   // cin, cout
#include <string>     // string
#include <bitset>     // bitset
#include <algorithm>  // max
#include <cassert>    // assert
#include <time.h>     // time
#include <stdlib.h>   // rand,srand


using namespace std;

typedef unsigned long(*FuncPtr)(const string&, const string&);


struct Input;

template<typename T> T read();
template<typename T> void read(T& obj);
void readTestcases(unsigned long T);
unsigned long compute(const Input& in);
unsigned long compute(const string& a, const string& b);
string randString(unsigned long n);
unsigned long MSB(unsigned long n);
unsigned long binadd_v6(const string& a, const string& b);
unsigned long binadd_v5(const string& a, const string& b);
unsigned long binadd_v4(const string& a, const string& b);
unsigned long binadd_generic(const string& a, const string& b);
template<unsigned long T_N> unsigned long binadd(const string& a, const string& b);
template<unsigned long T_N> unsigned long binadd(bitset<T_N> a, bitset<T_N> b);


struct Input
{
    Input() : a(read<string>()), b(read<string>())
    {
    }

    const string a;
    const string b;
};


/////////////////////////////
//
// definition function
//
/////////////////////////////
template<typename T> T read()
{
    T n;
    cin >> n;
    return n;
}

template<typename T> void read(T& obj)
{
    cin >> obj;
}

void readTestcases(unsigned long T)
{
    for (unsigned long i = 0; i < T; ++i)
        cout << compute(Input()) << endl;
}

unsigned long compute(const Input& in)
{
    return compute(in.a, in.b);
}



unsigned long compute(const string& a, const string& b)
{
    return binadd_v6(a, b);
 
}

string randString(unsigned long n)
{
    string s(rand() % n, '0');

    for (unsigned long i = 0; i < s.size(); ++i)
        s[i] = (rand() % 2 == 0 ? '0' : '1');

    return s;
}

unsigned long binadd_v6(const string& a, const string& b)
{
    unsigned long cnt(0);

    if (a.size() >= b.size())
    {
        for (unsigned long i = 0; i < b.size(); ++i)
            if (a[a.size() - 1 - i] == '1' && b[b.size() - 1 - i] == '1')
            {
                unsigned long j = i + 1;
                for (; j < a.size(); ++j)
                {
                    const char u = j < a.size() ? a[a.size() - 1 - j] : '0';
                    const char v = j < b.size() ? b[b.size() - 1 - j] : '0';
                    if (!(u == '0' && v == '1') && !(u == '1' && v == '0'))
                        break;
                }
                cnt = max(cnt, j - i + 1);
            }
            else if (a[a.size() - 1 - i] == '0' && b[b.size() - 1 - i] == '1')
                cnt = max(cnt, 1ul);
    }
    else
    {
        for (unsigned long i = 0; i < a.size(); ++i)
            if (a[a.size() - 1 - i] == '1' && b[b.size() - 1 - i] == '1')
            {
                unsigned long j = i + 1;
                for (; j < b.size(); ++j)
                {
                    const char u = j < a.size() ? a[a.size() - 1 - j] : '0';
                    const char v = j < b.size() ? b[b.size() - 1 - j] : '0';
                    if (!(u == '0' && v == '1') && !(u == '1' && v == '0'))
                        break;
                }
                cnt = max(cnt, j - i + 1);
            }
            else if (a[a.size() - 1 - i] == '0' && b[b.size() - 1 - i] == '1')
                cnt = max(cnt, 1ul);

        for (unsigned long i = a.size(); i < b.size(); ++i)
            if (b[b.size() - 1 - i] == '1')
                cnt = max(cnt, 1ul);
    }

    return cnt;
}


//SOLUTION5
unsigned long binadd_v5(const string& a, const string& b)
{
    unsigned long cnt(0);
    const unsigned long minSize(min(a.size(), b.size()));
    const unsigned long maxSize(max(a.size(), b.size()));

    for (unsigned long i = 0; i < minSize; ++i)
        if (a[a.size() - 1 - i] == '1' && b[b.size() - 1 - i] == '1')
        {
            unsigned long j = i + 1;
            for (; j < maxSize; ++j)
            {
                const char u = j < a.size() ? a[a.size() - 1 - j] : '0';
                const char v = j < b.size() ? b[b.size() - 1 - j] : '0';
                if (!(u == '0' && v == '1') && !(u == '1' && v == '0'))
                    break;
            }
            cnt = max(cnt, j - i + 1);
        }
        else if (a[a.size() - 1 - i] == '1' || b[b.size() - 1 - i] == '1')
            cnt = max(cnt, 1ul);


    return cnt;
}


//SOLUTION4
unsigned long binadd_v4(const string& a, const string& b)
{
    unsigned long cnt(0);
    unsigned long i = 0;
    {
        for (; i < b.size() - 1; ++i)
            if (b[b.size() - 1 - i] == '1' && b[b.size() - 1 - i - 1] == '0')
            {
                unsigned long j = i;
                for (; j < a.size(); ++j)
                    if (a[a.size() - 1 - j] == '0')
                        break;

                cnt = max(cnt, j - i + 1);
            }

        if (b[b.size() - 1 - i] == '1')
        {
            unsigned long j = i;
            for (; j < a.size(); ++j)
                if (a[a.size() - 1 - j] == '0')
                    break;

            cnt = max(cnt, j - i + 1);
        }
    }

    i = 0;
    {
        for (; i < a.size() - 1; ++i)
            if (a[a.size() - 1 - i] == '1' && a[a.size() - 1 - i - 1] == '0')
            {
                unsigned long j = i;
                for (; j < b.size(); ++j)
                    if (b[b.size() - 1 - j] == '0')
                        break;

                cnt = max(cnt, j - i + 1);
            }

        if (a[a.size() - 1 - i] == '1')
        {
            unsigned long j = i;
            for (; j < b.size(); ++j)
                if (b[b.size() - 1 - j] == '0')
                    break;

            cnt = max(cnt, j - i + 1);
        }
    }


    return cnt;
}


//SOLUTION3
unsigned long binadd_generic(const string& a, const string& b)
{
    static const FuncPtr funcArray[18] = {
      &binadd<(1 << 0)>,
      &binadd<(1 << 1)>,
      &binadd<(1 << 2)>,
      &binadd<(1 << 3)>,
      &binadd<(1 << 4)>,
      &binadd<(1 << 5)>,
      &binadd<(1 << 6)>,
      &binadd<(1 << 7)>,
      &binadd<(1 << 8)>,
      &binadd<(1 << 9)>,
      &binadd<(1 << 10)>,
      &binadd<(1 << 11)>,
      &binadd<(1 << 12)>,
      &binadd<(1 << 13)>,
      &binadd<(1 << 14)>,
      &binadd<(1 << 15)>,
      &binadd<(1 << 16)>,
      &binadd<100000> };

    return funcArray[MSB(max(a.size(), b.size())) + 1](a, b);
}


// Most Significant Bit
unsigned long MSB(unsigned long n)
{
    unsigned int pos = 0;
    while (n >>= 1) ++pos;

    return pos;
}
template<unsigned long T_N> unsigned long binadd(const string& a, const string& b)
{
    return binadd<T_N>(bitset<T_N>(a), bitset<T_N>(b));
}

template<unsigned long T_N> unsigned long binadd(bitset<T_N> a, bitset<T_N> b)
{
    unsigned long cnt(0);
    unsigned long posB(0);

    bitset<T_N> aa, bb;
    while (b.count() > 0)
    {
        // step 1
        while (posB < T_N && !b[posB])
            ++posB;

        if (posB >= T_N / 2)
            return cnt + binadd<T_N / 2>(bitset<T_N / 2>(a.to_string(), 0, T_N / 2), bitset<T_N / 2>(b.to_string(), 0, T_N / 2));

        aa = a ^ b;
        bb = (a & b) << 1;

        ++cnt;

        // step 2
        while (posB < T_N && !bb[posB])
            ++posB;

        if (posB >= T_N / 2)
            return cnt + binadd<T_N / 2>(bitset<T_N / 2>(aa.to_string(), 0, T_N / 2), bitset<T_N / 2>(bb.to_string(), 0, T_N / 2));

        a = aa ^ bb;
        b = (aa & bb) << 1;

        ++cnt;
    }

    return cnt;
}

template<> unsigned long binadd<1>(bitset<1> a, bitset<1> b)
{
    return b.count() > 0 ? 1 : 0;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    readTestcases(read<unsigned long>());

    return 0;
}
