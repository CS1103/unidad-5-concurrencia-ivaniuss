#include <iostream>
#include <thread>
#include <vector>
using namespace std;

class Node{
private:
    int data;
    Node *next;
public:
    Node(int newData){
        data=newData;
        next=nullptr;
    }
    int getData(){
        return data;
    }
    void setData(int newData){
        data=newData;
    }

    Node* goNext(int i){
        while(i>=1){
            if(i==1){
                return next;
            }
            else{
                next->setNext(next->goNext(1));
            }
            i=i-1;
        }
    }

    void setNext(Node *new_next){
        next=new_next;
    }

};

int main() {

    auto creatorNodes = [](Node* head_ref,int new_data){
        Node* new_node = new Node(new_data);
        Node *last = head_ref;
        new_node->setData(new_data);
        new_node->setNext(NULL);

        if (head_ref == NULL)
        {head_ref = new_node;
            return;}
        while (last->goNext(1)!= NULL)
            last = last->goNext(1);
        last->setNext(new_node);
    };

    Node *pmyNode=new Node(2);


    thread t1 = thread(creatorNodes,pmyNode,3);
    if(t1.joinable())
        t1.join();
    thread t2 = thread(creatorNodes,pmyNode->goNext(1),4);
    if(t2.joinable())
        t2.join();
    thread t3 = thread(creatorNodes,pmyNode->goNext(2),5);
    if(t3.joinable())
        t3.join();

    {
        while (pmyNode != NULL)
        {
            cout<<" "<<pmyNode->getData();
            pmyNode = pmyNode->goNext(1);
        }
    }

    return 0;
}