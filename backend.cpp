#include"backend.hpp"
using namespace std;
//constructor
Backend::Backend(int size){
  currentSize=0;
  maxSize=size;
  Node Arr[size];
}
//destructor
Backend::~Backend(){

}
// resorts the heap for now in psudocode
void Backend::ReHeap(Node* arr[],int i){
  int largest = i; // Initialize largest as root
    int l = 2*i + 1; // left = 2*i + 1
    int r = 2*i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < currentSize && arr[l]->value > arr[largest]->value)
        largest = l;

    // If right child is larger than largest so far
    if (r < currentSize && arr[r]->value > arr[largest]->value)
        largest = r;

    // If largest is not root
    if (largest != i)
    {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        Reheap(arr,largest);
    }
}
void Backend::HeapSort(Node* arr[]){
  // Build heap (rearrange array)
    for (int i = currentSize / 2 - 1; i >= 0; i--)
        ReHeap(arr, i);

    // One by one extract an element from heap
    for (int i=currentSize-1; i>=0; i--)
    {
        // Move current root to end
        swap(arr[0], arr[i]);

        // call max heapify on the reduced heap
        ReHeap(arr, 0);
    }
}
/*
Finds the parent of a node, given its index.
*/
int Backend::parent(int index)
{
  return (index-1)/2;
}

/*
Returns the left child of a node.
*/
int Backend::leftChild(int index)
{
  return ((2*index) + 1);
}

/*
Returns the right child of a node.
*/
int Backend::rightChild(int index)
{
  return ((2*index) + 2);
}
