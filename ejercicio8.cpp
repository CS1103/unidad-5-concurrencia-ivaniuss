#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

mutex mt;
condition_variable cv;
int b = 0;

bool isReady(){return b!=0;}

void mergeSort(vector<int>&left, vector<int>& right, vector<int>& bars)
{
    int nL = left.size();
    int nR = right.size();
    int i = 0, j = 0, k = 0;

    while (j < nL && k < nR) {
        if (left[j] < right[k]) {
            bars[i] = left[j];
            j++;
        }
        else {
            bars[i] = right[k];
            k++;
        }
        i++;
    }
    while (j < nL) {
        bars[i] = left[j];
        j++; i++;
    }
    while (k < nR) {
        bars[i] = right[k];
        k++; i++;
    }
}

void sort(vector<int> & bar) {
    if (bar.size() <= 1) return;

    int mid = bar.size() / 2;
    vector<int> left;
    vector<int> right;

    for (size_t j = 0; j < mid;j++)
        left.push_back(bar[j]);
    for (size_t j = 0; j < (bar.size()) - mid; j++)
        right.push_back(bar[mid + j]);

    std::thread t1(sort,std::ref(left));
    std::thread t2(sort,std::ref(right));
    t1.join();
    t2.join();

    mergeSort(left, right, bar);
}

void showv(vector<int>& v){
    std::unique_lock<std::mutex> lock(mt);
    cv.wait(lock,isReady);
    for(auto it : v){
        cout << it << ' ';
    }
}


int main() {
    vector<int> v {22,12,5,1,43};

    thread t1([&v](){
        sort(v);
        b = 1;
        cv.notify_one();
    });
    thread t2(showv,ref(v));
    t1.join();
    t2.join();


    return 0;
}

