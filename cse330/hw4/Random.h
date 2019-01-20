// Random.h
// KV, June 2018

// some random number generating utilities

#ifndef RANDOM_H_
#define RANDOM_H_

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <set>

using namespace std;

template <typename Cont>
void rand_permute(Cont&);


void rand_seed()
{
  int seed = static_cast<int>(time(0));
  srand(seed);
}

int rand_int(int a, int b)
{
  return a + rand() % (b - a + 1);
}

vector<int> rand_int_vector(int k, int a, int b)
{
  set<int> set_of_k;
  vector<int> rvec;

  while (set_of_k.size() < k)
    {
      int rv = rand_int(a,b);
      set_of_k.insert(rv);
    }
  // will produce vector without duplicate values;
  set<int>::iterator itr  = set_of_k.begin();
  for (; itr != set_of_k.end(); ++itr)
    rvec.push_back(*itr);

  rand_permute(rvec);
  
  return rvec;
}

template <typename Cont>
void rand_permute(Cont& vals)
{
  for (int i = 1; i <= vals.size()*3; i++)
    {
      int r1 = rand_int(0,vals.size()-1);
      int r2 = rand_int(0,vals.size()-1);

      typename Cont::iterator itr1 = vals.begin();
      typename Cont::iterator itr2 = vals.begin();
      for (int i = 1; i <= r1; i++) ++itr1;
      for (int i = 2; i <= r2; i++) ++itr2;

      std::swap(*itr1,*itr2);
    }
  return;
}

#endif
