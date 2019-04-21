#ifndef BACKEND_HPP
#define BACKEND_HPP
#include <vector>
#include <iostream>
#include <string>

struct Node
{
  string name;
  int value;
  std::vector<std::string> ingrediants;
};
struct preferences{
    std::vector<std::string>positiveIngredients;
    std::vector<std::string>negativeIngredients;
    std::vector<int>negativeIngredientsWeight; // if 0 use default
    std::string foodStylePositive;
    std::string foodStyleNegative;
    std::string regionPositive;
    std::string regionNegative;
    int recipeComplexity; // if -1 user has no preference
  };
class Backend
{
  public:

  Backend(int size);// constructior has one paramitor the maximum size of the heap

  ~Backend();// destructor

  void PrintHeap();// outputs all values in the heap

  void ReHeap(Node* arr[],int i);// updates the heap to make sure it it a valid heap

  void HeapSort(Node* arr[]);// sorts the values using heap sort

  void ChangeValues(std::string name, preferences pref);// updates the values of every node using the specified ingrediant and weighting

  void addToHeap(Node *recipie);//adds a node to the bottom of the heap

  Node* removeFromHeap();//removes the root of the heap

  private:

  int parent(int idx);//returns parent of the given node

  int leftChild(int idx);//returns the left child of the given node

  int rightChild(int idx);//returns the right child of the given node

  Node *Heap;// pointer to the heap
  int currentSize;// the current size of the heap
  int maxSize;// the maximum size of the heap

};
#endif
