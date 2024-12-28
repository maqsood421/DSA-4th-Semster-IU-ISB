#include<iostream>
using namespace std;
#define SIZE 20

class queue{
    char* arr;
    int front;
    int rear;

    public:

    queue(){
arr =new char[SIZE];
     front=-1;
     rear=-1;
    }
     


     void enqueue(char val){
        if(rear==SIZE-1){
            cout<<"queue is full";
            return;
        }
        rear++;
        arr[rear]=val;
        if(front==-1){
            front++;
        }


     }
     void dequeue(){
        if(front==-1 && front>rear){
            cout<<"queue is empty";
            return;
        }
        front++;
     }

     char peek(){
        if(front==-1 && front>rear){
            cout<<"queue is empty";
            return -1;
        }
        return arr[front];
     }
    bool empty(){
        if(front==-1 && front>rear){
            return true;
        }
        return false;
    }

    void display(){
        if(front==-1 && front>rear){
            cout<<"queue is empty";
            return;
        }
        int i = front;
        while(i <= rear){
            cout << arr[i++] << '\n';
        }
    }

};

int main(){

    queue q;
    q.enqueue('A');
    q.enqueue('B');
    q.enqueue('C');
    q.dequeue();
    q.enqueue('D');
    q.enqueue('E');
    q.display();
    cout<<"qustomer to be served is: "<<q.peek();
    cout<<endl;
    q.dequeue();
    q.dequeue();
    q.display();
    // cout << q.front << endl;



}