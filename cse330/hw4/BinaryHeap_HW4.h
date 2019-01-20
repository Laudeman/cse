// BinaryHeap_HW4.h
// KV, May 2018, after Weiss, Data Structures textbook

// KV: version for HW4; counts comps for insert and  deleteMin;

#ifndef BINARYHEAP_
#define BINARYHEAP_H_

#include <cassert>
#include "Vector.h"
using namespace std;

extern int CLUMSY_COUNT;

template <typename C>
class BinaryHeap
{
 public: 
  BinaryHeap()
  : heap(100), currentSize(0)
  {}

  BinaryHeap(int capacity)
    : heap(capacity), currentSize(0)
    {}
  
  BinaryHeap(Vector<C>&);

  bool isEmpty() const
  {
    return currentSize == 0;
  }

  int size() const
  {
    return currentSize;
  }
  
  const C & findMin() const
  {
    return heap[1];
  }

  void insert(const C &);
  void insert(C &&);

  void deleteMin();
  void deleteMin(C &);
  void makeEmpty()
  {
    while (!heap.isEmpty())
      heap.pop_back();
    currentSize = 0;
  }

  void printHeap() const
  {
    printHeap(1,0);
  }
  
  void buildHeap()
  {
    for (int i = currentSize/2; i > 0; i--)
      percolateDown(i);
  }
  
 private:
  int currentSize;
  Vector<C> heap;
  
  void percolateDown(int);

  void printHeap(int,int) const;
};



template <typename C>
BinaryHeap<C>::BinaryHeap(Vector<C>& items)
: heap(items.size() + 10), currentSize(items.size())
{
  for (int i = 0; i < items.size(); i++)
    heap[i + 1] = items[i];
  buildHeap();
}

template <typename C>
void BinaryHeap<C>::insert(const C& x)
{
  if (currentSize == heap.size()-1)
    heap.resize(heap.size()*2);

  int hole = ++currentSize;
  C copy = x;

  heap[0] = std::move(copy);
  
  for (; x < heap[hole/2]; hole /= 2)
    {
      CLUMSY_COUNT++;
      heap[hole] = std::move(heap[hole/2]);
    }
  heap[hole] = std::move(heap[0]);
}

template <typename C>
void BinaryHeap<C>::insert(C&& x)
{
  if (currentSize == heap.size()-1)
    heap.resize(heap.size()*2);

  int hole = ++currentSize;
  C copy = x;

  heap[0] = std::move(copy);

  for (; x < heap[hole/2]; hole /= 2)
    heap[hole] = std::move(heap[hole/2]);
  heap[hole] = std::move(heap[0]);
}

			   
template <typename C>
void BinaryHeap<C>::deleteMin()
{
  assert(!isEmpty());
  
  heap[1] = std::move(heap[currentSize--]);
  percolateDown(1);
}

template <typename C>
void BinaryHeap<C>::deleteMin(C & minItem)
{
  assert(!isEmpty());

  minItem = std::move(heap[1]);

  heap[1] = std::move(heap[currentSize--]);
  percolateDown(1);
}	

template <typename C>
void BinaryHeap<C>::percolateDown(int hole)
{
  int child;
  C tmp = std::move(heap[hole]);

  for (; hole * 2 <= currentSize; hole = child)
    {
      CLUMSY_COUNT++;
      child  = hole * 2;


      if (child != currentSize && heap[child + 1] < heap[child])
	child++;

      if (heap[child] < tmp)
	heap[hole] = std::move(heap[child]);
      else
	break;
    }
  heap[hole] = std::move(tmp);
}

template <typename C>
void BinaryHeap<C>::printHeap(int index, int offset) const
{
  if (index  > currentSize)
    return;
  
  for (int i = 1; i <= offset; i++)
    cout << "..";
  cout << heap[index] << endl;

  printHeap(2*index, offset + 1);
  printHeap(2*index+1, offset + 1);
  return;
}
      
#endif

      
