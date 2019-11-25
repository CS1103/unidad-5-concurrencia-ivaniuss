#include <iostream>
#include <vector>
#include <thread>

using namespace std;


void borrar(vector<int> c, int v)
{
    vector <int> temp;

    for(auto it = c.begin(); it != c.end(); it++ )
    {
        int var = 0;

        var = v +*it;

        temp.push_back(var);
    }
    for(auto it : temp)
    {
        cout << it << " ";
    }
}

int main() {

vector<int> vec1 = {1,2,3};

thread* t1 = new thread (borrar,vec1,10);
t1->join();
delete(t1);


    return 0;
}