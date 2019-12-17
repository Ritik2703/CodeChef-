

/*    
 
  December Challenge 2019 Division 2
  problem 6--  Chefina and Ranges
  solution by -- RITIK DAGAR
                 SRM IST NCR CAMPUS
                 contact -- 9958152151
        
*/




#include <iostream>  // cin, cout
#include <utility>   // pair
#include <algorithm> // min,max
//#include <set>       // set
#include <map>       // map
//#include <cassert>   // assert
#include <limits>    // numeric_limits



using namespace std;

static constexpr unsigned int CONST_N = 100000;


struct InputData;
struct Input;

template<typename T> T read();
template<typename T> void read(T& obj);
istream& operator>>(istream& is, InputData& o);
//istream& operator>>(istream& is, multiset<pair<unsigned long, unsigned long>>& v);
istream& operator>>(istream& is, pair<unsigned long, unsigned long>& p);
void readTestcases(unsigned long T);
long compute(InputData& inputData);
long compute(
    unsigned long N,
    const pair<unsigned long, unsigned long>(&ranges)[CONST_N],
    map<unsigned long, pair<unsigned long, unsigned long>>& cnt);
long chfran(
    unsigned long N,
    const pair<unsigned long, unsigned long>(&ranges)[CONST_N],
    map<unsigned long, pair<unsigned long, unsigned long>>& cnt);
struct InputData
{
    unsigned long N;
    pair<unsigned long, unsigned long> ranges[CONST_N];
    map<unsigned long, pair<unsigned long, unsigned long>> cnt;

};

struct Input
{
    Input()
    {
        read<InputData>(data);
    }

    //multiset<pair<unsigned long, unsigned long>> data;
    static InputData data;
};

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
istream& operator>>(istream& is, InputData& o)
{
    o.cnt.clear();
    o.N = read<unsigned long>();

    for (unsigned long i = 0; i < o.N; ++i)
    {
        pair<unsigned long, unsigned long> p = read<pair<unsigned long, unsigned long>>();
        o.ranges[i] = p;

        {
            auto it(o.cnt.lower_bound(p.first));
            if (it != o.cnt.end() && it->first == p.first)
                ++(it->second).first;
            else
                o.cnt.insert(it, pair<unsigned long, pair<unsigned long, unsigned long>>(p.first, pair<unsigned long, unsigned long>(1,0)));
        }
        {
            auto it(o.cnt.lower_bound(p.second));
            if (it != o.cnt.end() && it->first == p.second)
                ++(it->second).second;
            else
                o.cnt.insert(it, pair<unsigned long, pair<unsigned long, unsigned long>>(p.second, pair<unsigned long, unsigned long>(0, 1)));
        }
    }

    return is;
}


istream& operator>>(istream& is, pair<unsigned long, unsigned long>& p)
{
    read<unsigned long>(p.first);
    read<unsigned long>(p.second);

    return is;
}

void readTestcases(unsigned long T)
{
    static InputData data;

    for (unsigned long i = 0; i < T; ++i)
    {
        read(data);
        cout << compute(data) << endl;
    }
}

long compute(InputData& inputData)
{
    return compute(
        inputData.N,
        inputData.ranges,
        inputData.cnt);
}

long compute(
    unsigned long N,
    const pair<unsigned long, unsigned long>(&ranges)[CONST_N],
    map<unsigned long, pair<unsigned long, unsigned long>>& cnt)
{
    if (N > 1)
        return chfran(
            N,
            ranges,
            cnt);
    else
        return -1;
}

long chfran(
    unsigned long N,
    const pair<unsigned long, unsigned long>(&ranges)[CONST_N],
    map<unsigned long, pair<unsigned long, unsigned long>>& cnt)
{
    
    {
        auto it = cnt.cbegin();
        long tmp(it->second.first - it->second.second);
        long u(0);
        long r(std::numeric_limits<long>::max());

        bool isLeftSubsetEmpty(it->second.second == 0);
        for (++it; isLeftSubsetEmpty && it != cnt.cend(); ++it)
        {
            if (it->second.second > 0)
                isLeftSubsetEmpty = false;

            u += tmp;


            tmp = it->second.first - it->second.second;
        }

        for (; it != cnt.cend(); ++it)
        {
            u += tmp;

            if (it->second.first > 0)
                r = min(r, u);

            tmp = it->second.first - it->second.second;
        }

        return r < std::numeric_limits<long>::max() ? r : -1;
    }
}




int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    readTestcases(read<unsigned long>());

    return 0;
}

