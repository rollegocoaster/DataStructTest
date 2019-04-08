#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <QApplication>

using namespace std;

const int MAX_SIZE = 5; // maximum size of the array

// Creating a class named queue
class Queue{
private:
  int A[MAX_SIZE];
  int front, rear;
public:
  // Notice in this program the methods are inlined
  // In CPP this is possible however, you can avoid doing this by using header
  // Constructor - set front and rear as -1
  // We are assuming that for an empty Queue, both front and rear will be -1
  Queue(){
    front = -1;
    rear = -1;
  }

  // To check whether Queue is empty or not
  bool isEmpty(){
    return (front == -1 && rear == -1);
  }

  bool isFull(){
    return (rear+1)%MAX_SIZE == front? true : false;
  }
  void enqueue(int x){
    cout << "enqueuing\r";
    if(isFull()){
      cout<<"Error: Queue is Full"<<endl;
      return;
    }

    if (isEmpty()){
      front = rear = 0;
    } else {
      rear = (rear+1)%MAX_SIZE;
    }
    A[rear] = x;
  }

  void dequeue(){
    cout<<"Dequeuing \r";
    if(isEmpty()){
      cout<<"Error: Queue is empty\r";
      return;
    } else if(front == rear){
      rear = front = -1;
    } else {
      front = (front+1)%MAX_SIZE;
    }
  }
  // Returns element at front of queue
  int peek(){ // Peek function - checking what is in the front
    if(front==-1){
      cout << "Error- queue is empty"<< endl;
      return -1;
    } else {
      return A[front];
    }
  }
  /*
    printing the elements in the queue from front to rear
    This function is only to test the code
  */
  void print(){
    if(!isEmpty())
    {
      for(int i=front; i != rear; i = (i+1)%MAX_SIZE){
        cout << A[i] << ", ";
      }
      cout << A[rear] << endl;
    }
  }
};





int main() {
  Queue q;
  q.print();
  for(int i=0; i<MAX_SIZE; i++){
    q.enqueue(i*i);
    q.print();
  }
  q.dequeue();
  q.dequeue();
  q.enqueue(55);
  q.dequeue();
  q.enqueue(11);

  q.print();


  return 0;
}
