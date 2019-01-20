#include "Map.h"
using namespace std;

int main()
{

	Map<string, int> basket;
	string cheese = "cheese";	
	basket[cheese] = 10;
	basket["egg"] = 6;
	basket.printMap();
	cout << endl << endl;
	basket.remove(cheese);
	basket.printMap();
	cout << endl << endl;	
	basket["egg"] = 6;
	basket.printMap();	
	return 0;
}
