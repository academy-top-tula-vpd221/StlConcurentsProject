#include <iostream>
#include <thread>
#include <future>
#include <chrono>

using namespace std;

int Amount(int number)
{
    int amount{};
    for (int i = 1; i <= number; i++)
    {
        amount += i;
        this_thread::sleep_for(10ms);
    }

    return amount;
}

void AmountProm(int number, promise<int> prom)
{
    int amount{};
    for (int i = 1; i <= number; i++)
    {
        amount += i;
        this_thread::sleep_for(10ms);
    }
    prom.set_value(amount);
}


int main()
{
    /*
    auto res1 = async(Amount, 300);
    auto res2 = async(Amount, 100);

    cout << "main is work...\n";

    res1.wait();
    res2.wait();
    */
    promise<int> prom1;
    future<int> pres1 = prom1.get_future();
    promise<int> prom2;
    future<int> pres2 = prom2.get_future();

    thread th1(AmountProm, 300, move(prom1));
    thread th2(AmountProm, 100, move(prom2));

    auto e1 = async([&pres1]() {cout << pres1.get() << "\n"; });
    auto e2 = async([&pres2]() {cout << pres2.get() << "\n"; });

    cout << "main is work again...\n";
   
    th1.join();
    th2.join();
    
}
