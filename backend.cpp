#include"backend.hpp"
using namespace std;
//constructor
Backend::Backend(int size){
  currentSize=0;
  maxSize=size;
  Arr= new Node[size];
}
Backend::Backend(){
  currentSize=0;
  maxSize=50;
  Node *Arr[50];
}
//destructor
Backend::~Backend(){
  delete [] Arr;
}
void swap(Node *a, Node *b)
{
  Node *temp = a;
  a = b;
  b = temp;
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
        ReHeap(arr,largest);
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
void Backend::ChangeValues(preferences pref)
{
  int iter =0;
  while(iter< currentSize){
    for(int i=0;i<Arr[iter].ingrediants.size();i++){
      for(int z=0;z<pref.positiveIngredients.size();z++){
        if(pref.positiveIngredients[z]==Arr[iter].ingrediants[i]){
          Arr[iter].value+=1;
        }
      }
      for(int x=0;pref.negativeIngredients.size();x++){
        if(pref.negativeIngredients[x]==Arr[iter].ingrediants[i]){
            Arr[iter].value-=pref.negativeIngredientsWeight[x];
        }
      }
      if(Arr[iter].ingrediants[i]==pref.foodStylePositive){
        Arr[iter].value++;
      }
      if(Arr[iter].ingrediants[i]==pref.foodStyleNegative){
        Arr[iter].value--;
      }
      if(Arr[iter].ingrediants[i]==pref.regionPositive){
        Arr[iter].value++;
      }
      if(Arr[iter].ingrediants[i]==pref.regionNegative){
        Arr[iter].value--;
      }
      }
    }
  }

void Backend::PrintHeap()//prints the heap in the form name value
{
  int iter = 0;
  while(iter < currentSize)
  {
    cout<<Arr[iter].name<<" ";
    cout<<Arr[iter].value<<" ";
    iter = iter + 1;
  }
  cout<<endl;
}
void Backend::addToHeap(Node recipie){
  if(currentSize == maxSize)
  {
    cout<<"Maximum heap size reached. Cannot insert anymore"<<endl;
    return;
  }
  currentSize = currentSize + 1;
  int index = currentSize - 1;
  Arr[index] = recipie;
}
  Node* Backend::removeFromHeap()
  {
    if (currentSize == 1)
    {
        currentSize--;
        return &Arr[0];
    }

    Node *minimum;
    minimum= new Node;
    *minimum=Arr[0];
    currentSize--;
    Arr[0]=Arr[currentSize];
    ReHeap(&Arr,0);
    return minimum;

  }
  vector<string> Backend::GetHeap(){
    vector<string> temp;
    for(int i=0;i<currentSize;i++){
      temp.push_back(Arr[i].name);
    }
    return temp;
  }
