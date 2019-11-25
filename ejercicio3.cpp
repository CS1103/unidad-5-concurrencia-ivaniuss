#include <iostream>
#include <thread>
#include <vector>
#include <future>


using namespace std;



bool isPrime(int num){
    bool flag=true;
    for(int i = 2; i <= num / 2; i++) {
        if(num % i == 0) {
            flag = false;
            break;
        }
    }
    return flag;
}


int main() {

    auto nt=5;
    int m = 10;
    vector<int> v;

    vector<promise<vector<int>>> vec_promise(nt);
    vector<future<vector<int>>> vec_future(nt);
    vector<thread> vec_thread2(nt);


    for (int i = 0; i < nt; i++){
        vec_future[i] = vec_promise[i].get_future();
    }

    auto prime = [](promise<vector<int>> &prom, size_t position, size_t subSize){
        cout<<"id del thread: "<<this_thread::get_id()<<endl;
        vector<int> subVector;

        for(int number=position;number<position+subSize;number++){
            if(isPrime(number) && number!=0 && number!=1){
                subVector.push_back(number);
            }
        }
        prom.set_value(subVector);

    };

    int size=m/nt;
    int position=0;

    for (int i = 0; i < nt; i++){
        vec_thread2[i] = thread(prime,ref(vec_promise[i]),position,size);
        position=size+position;
    }

    for(int i = 0; i<nt; i++)
        vec_thread2[i].join();


    for(int i=0;i<nt;i++){
        auto respFuture = vec_future[i].get();
        for(int primo : respFuture){
            v.push_back(primo);
        }
    }

    for(int primo: v)
        cout<<"es primo: "<<primo<<endl;



    return 0;
}