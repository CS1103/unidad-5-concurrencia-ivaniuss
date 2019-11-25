#include <iostream>
#include <future>
#include <vector>

using namespace std;

void fibo_thread(unsigned int n, promise<unsigned int>* prom){
    vector<int> fibo;
    if(n==0)
        prom->set_value(0);
    int valor = 0;
    int output = 1;

    for (int i = 1; i < n; i++)
    {
        int temporal;
        temporal = valor + output;
        valor = output;
        output = temporal;
        fibo.push_back(output);
    }

    for(auto &v:fibo)
        cout << v << " ";

    prom->set_value(output);

};

int main() {
    int n = 10;
    auto prom1=  promise<unsigned int>();
    auto fut1= prom1.get_future();
    thread t1=  thread(fibo_thread,n,prom1);
    t1.join();
    return 0;

}