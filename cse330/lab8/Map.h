#ifndef MAP_H_
#define MAP_H_

#include "Pair.h"
#include "Set.h"
using namespace std;

template <typename K, typename V>
class Map
{

	public:
		Map() {}

		void printMap() const
		{
			typename Set<Pair<K,V> >::iterator itr = themap.begin();
			for (; itr != themap.end(); ++itr)
			{
				cout << (*itr).first << ":" << (*itr).second << endl;
			}

			return;
		}

		V & operator [](K index)
		{
			typename Set<Pair<K,V> >::iterator here;
			Pair<K,V> probe(index, V());
			here = themap.insert(probe);
			return (*here).second;
		}

		void remove(K & key)
		{
			Pair<K,V> probe;
			probe.first = key;
			themap.remove(probe);
			return;
		}

	private:
		Set<Pair<K,V> > themap;
};

#endif
