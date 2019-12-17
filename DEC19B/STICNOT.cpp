


/*    
 
  December Challenge 2019 Division 2
  problem 7--  Sticky Notes
  solution by -- RITIK DAGAR
                 SRM IST NCR CAMPUS
                 contact -- 9958152151
        
*/




#include <iostream>  // cin, cout
#include <set>       // set
#include <queue>     // priority_queue


using namespace std;

struct InputData;

template<typename T> T read();
template<typename T> void read(T& obj);
void readTestcases(unsigned long T);
unsigned long compute(InputData& inputData);
unsigned long compute(multiset<unsigned long>& aSet, priority_queue<unsigned long>& bQueue);

struct InputData
{
    InputData() : N(read<unsigned long>())
    {
        // read edge
        for (unsigned long i = 0; i < N - 1; ++i)
        {
            const unsigned long u(read<unsigned long>());
            const unsigned long v(read<unsigned long>());
            const unsigned long b(read<unsigned long>());
            bQueue.push(b);
        }

        // read vertice
        for (unsigned long i = 0; i < N; ++i)
        {
            const unsigned long a(read<unsigned long>());
            aSet.insert(a);
        }
    }

    unsigned long N;
    multiset<unsigned long> aSet;
    priority_queue<unsigned long> bQueue;
};

template<typename T> T read()
{
    T n;
    cin >> n;
    return n;
}

template<typename T> void read(T& o)
{
    cin >> o;
}

void readTestcases(unsigned long T)
{
    for (unsigned long i = 0; i < T; ++i)
    {
        InputData inputData;
        cout << compute(inputData) << endl;
    }
}

unsigned long compute(InputData& inputData)
{
    return compute(inputData.aSet, inputData.bQueue);
}

unsigned long compute(multiset<unsigned long>& aSet, priority_queue<unsigned long>& bQueue)
{
    unsigned long coin(0);

    {
        const auto aMax(prev(aSet.cend()));
        const auto aMin(aSet.begin());
        const unsigned long bMax(bQueue.top());


        if (*aMax >= bMax)
        {
            aSet.erase(aMax);
        }
        else
        {
            aSet.erase(aMin);
            ++coin;
        }
    }

    while (!bQueue.empty())
    {
        const auto aMax(prev(aSet.cend()));
        const auto aMin(aSet.begin());
        const unsigned long bMax(bQueue.top());
        bQueue.pop();

        if (*aMax >= bMax)
        {
            aSet.erase(aMax);
        }
        else
        {
            aSet.erase(aMin);
            ++coin;
        }
    }

    return coin;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    readTestcases(read<unsigned long>());

    return 0;
}
