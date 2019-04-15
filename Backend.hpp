#ifndef BACKEND_HPP
#define BACKEND_HPP
#include <vector>
#include <iostream>
#include <string>

struct Node
{
  int value;
  std::vector<std::string> ingrediants;
  Node* left=NULL;
  Node* right=NULL;
  Node* parrent=NULL;
};

class Backend
{
  public:

  Backend(int size);// constructior has one paramitor the maximum size of the heap

  ~Backend();// destructor

  void PrintHeap();// outputs all values in the heap

  void ReHeap();// updates the heap to make sure it it a valid heap

  void ChangeValues(std::string name, int weight);// updates the values of every node using the specified ingrediant and weighting

  private:

  int parent(int idx);//returns parent of the given node

  int leftChild(int idx);//returns the left child of the given node

  int rightChild(int idx);//returns the right child of the given node

  Node *Heap;// pointer to the heap
  int currentSize;// the current size of the heap
  int maxSize;// the maximum size of the heap

};
#endif
