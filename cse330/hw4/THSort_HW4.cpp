// THSort_HW4.cpp
// comparing the performance of TreeSort vs. HeapSort
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include "Random.h"
#include "TreeSortHeapSort.h"
using namespace std;
int main()
{
 vector<int> tosort1;
 vector<int> comps1;
 vector<int> comps2;
 int sum1;
 int sum2;
 int numdata = 25;

 rand_seed();
 for (numdata = 10; numdata <= 50; numdata+=5)
 {
 sum1 = 0;
 sum2 = 0;
 for (int i = 1; i <= 25; i++)
{
 tosort1 = rand_int_vector(numdata,1,1000);
 vector<int> tosort2(tosort1);
 int k1,k2;
 
 TreeSort(tosort1,k1);
 assert(tosort1.size() == numdata);

 HeapSort(tosort2,k2);
 assert(tosort2.size() == numdata);
 comps1.push_back(k1);
 comps2.push_back(k2);
 sum1 += k1;
 sum2 += k2;
}
 cout << endl;
 double nlogn = numdata* log10(numdata)/log10(2);
 int nn = numdata * numdata;
 double avg1 = (double)sum1 / 25;
 double avg2 = (double)sum2 / 25;

 cout << numdata << ", " << (int)avg1 << ", "
 << (int)avg2 << ", " << (int)nlogn
 << ", " << nn << endl;
 }

 return 0;
}
