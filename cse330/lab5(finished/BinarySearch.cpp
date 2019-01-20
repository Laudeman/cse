#include "Vector.h"
#include "BinarySearch.h"
#include "List.h"
using namespace std;

int binary_search(int x, Vector<int>& vec, int& steps)
{
    int low = 0;
    int high = vec.size() - 1;
    steps = 0;
    
    while (low <= high)
    {
        int mid = (low + high) / 2;
        
        steps++;
        
        if (vec[mid] < x)
            low = mid + 1;
        else if (vec[mid] > x)
            high = mid - 1;
        else
            return mid;
    }
    return -1; //not found
}


int binary_search_list(int x, List<int>& vec, int& steps)
{
	int low = 0;
	int high = 
}


int nth(int k, int& steps) const
{
	steps = 0;
	if (k < 0 || k >= theSize)
		return -1;

	const_iterator itr = begin();
	if (k == 0)
	{
		steps++;
		return *itr;
	}

	for (int i = 1; i <= k; i++)
	{
		itr++;
		steps++;
	}
	return *itr;

}

