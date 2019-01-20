#include <iostream>
#include <cstdlib>
#include <ctime>
#include "BinarySearch.h"

using namespace std;

void rand_seed()
{
	int seed = static_cast<int>(time(0));
	srand(seed);
	return;
}

int rand_int(int a, int b)
{
	return a+ rand() % (b - a + 1);
}

void random_vector_asc(int k, Vector<int>& vec)
{
	if (k <= 0)
		return;
	int rnum = rand_int(1, 9);

	vec.push_back(rnum);
	int prev = rnum;

	for (int i = 1; i <= k - 1; i++)
	{
		int next = prev + rand_int(1, 9);
		vec.push_back(next);
		prev = next;
	}

	return;

}


int main()
{
	Vector<int> asc_vec;
	int how_many;
	
	rand_seed();
	cout << "How many elements in vector?" << endl;
	cin >> how_many;
	cout << endl;

	random_vector_asc(how_many, asc_vec);

	for (int i = 0; i < asc_vec.size(); i++)
		cout << asc_vec[i] << endl;
	cout << endl;
	
	int target;
	cout << "Find: ";
	cin >> target;
	cout << endl;
	int cost;
	int found = binary_search(target, asc_vec, cost);
	if (found != -1)
		cout << "Found " << target << " at cost " << cost << endl;
	else 
		cout << "Target " << target << " not found at cost " << cost << endl;


	return 0;
		
}
