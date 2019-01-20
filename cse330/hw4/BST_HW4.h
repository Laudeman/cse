// BST_HW4.h 
// KV May 2018, based on
// KV replaced exceptions with assert statements;

// version of BST_HW3 that keeps track of insertion and
// iteratation costs;


#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

//#include "dsexceptions.h"
#include <cassert>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

int CLUMSY_COUNT = 0;

template <typename C>
class BinarySearchTree
{
 private:
  struct BinaryNode
  {
    C element;
    BinaryNode *left;
    BinaryNode *right;
    BinaryNode *parent;
  BinaryNode(const C & elem, BinaryNode *lt,
	     BinaryNode *rt,
	     BinaryNode *par)
  : element(elem), left(lt), right(rt), parent(par)
    {}
  };

 public:
  //struct BinaryNode;
  class iterator
  {public:
  iterator() : current{nullptr}
    {}

  iterator(BinaryNode * t) : current(t)
    {}

    
    C & operator *() const
      {
	return current->element;
      }

    bool operator ==(iterator other) const
    {
      return current == other.current;
    }

    bool operator != (iterator other) const
    {
      return current != other.current;
    }

    iterator & operator ++()
      {
	if (is_root(current))
	  current = leftmost(current->right);
	else if (is_left_child(current))
	  {
	    if (current->left == nullptr && current->right
		== nullptr)
	      {
		current = current->parent;
		CLUMSY_COUNT++;
	      }
	    else if (current->right != nullptr)
	      current = leftmost(current->right);
	    else
	      {
		//; // should not happen
		current = current->parent; // NEW!!
		CLUMSY_COUNT++;
	      }
	  }
	else if (is_right_child(current))
	  {
	    if (current->right != nullptr)
	      current = leftmost(current->right);else
	      current = follow_parent_until_leftchild(current);
	  }
	return *this;
      }

    iterator & operator++(int)
      {
	iterator old(*this);
	++(*this);
	return old;
      }

  protected:

    BinaryNode * current;

    /*
    bool is_right_child(BinaryNode * t)
    {
      return (t != nullptr && t->parent == nullptr);
    }
    */

    bool is_root(BinaryNode *t)
    {
      return (t != nullptr && t->parent == nullptr);
    }
    
    bool is_left_child(BinaryNode *t)
    {
      assert(t != nullptr);
      if (t->parent != nullptr && t->parent->left == t)
	return true;
      else
	return false;
    }

    bool is_right_child(BinaryNode *t)
    {
      assert(t != nullptr);
      if (t->parent != nullptr && t->parent->right ==
	  t)
	return true;
      else
	return false;
    }

    BinaryNode * leftmost(BinaryNode *t)
    {
      if (t == nullptr)
	return nullptr;
      CLUMSY_COUNT++;
      if (t->left == nullptr)
	return t;
      return leftmost(t->left);
    }
    BinaryNode * follow_parent_until_leftchild(BinaryNode *t)
    {
      if (is_root(t))
	return nullptr;
      CLUMSY_COUNT++;
      if (is_left_child(t))
	return t->parent;
      return follow_parent_until_leftchild(t->parent);
    }

    friend class BinarySearchTree<C>;
  };

 public:

 BinarySearchTree( ) : root{ nullptr }
  {
  }

 BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
  {
    root = clone( rhs.root);
  }

 BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
  {
    rhs.root = nullptr;
  }

  ~BinarySearchTree( )
     {
       makeEmpty( );
     }

  BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
      BinarySearchTree copy = rhs;
      std::swap( *this, copy );
      return *this;
    }

  BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
      std::swap( root, rhs.root );
      return *this;
    }

  const C & findMin( ) const
  {
    assert(!isEmpty());
    return findMin( root )->element;
  }

  const C & findMax( ) const
  {
    assert(!isEmpty());
    return findMax( root )->element;
  }

  bool contains( const C & x ) const
  {
    return contains( x, root );

  }

  bool isEmpty( ) const
  {
    return root == nullptr;
  }

  void printTree( ostream & out = cout ) const
  {
    if( isEmpty( ) )
      out << "Empty tree" << endl;
    else
      printTree( root, out );
  }

  void printInternal()
  {
    printInternal(root,0);
  }

  void makeEmpty( )
  {
    makeEmpty( root );
  }

  iterator insert( const C & x )
  {
    return insert( x, root, root);
  }

  iterator insert( C && x )
  {
    return insert( std::move( x ), root, root);
    
  }

  void remove( const C & x )
      {
	remove( x, root );
      }

iterator begin() const
  {
    BinaryNode *t = root;
    while (t->left != nullptr)
      t = t->left;
    iterator beg(t);
    return beg;
  }

iterator end() const
  {
    iterator theend(nullptr);
    return theend;
  }

int size() const
  {
    if (root == nullptr)
      return 0;
    return 1 + size(root->left) + size(root->right);
  }

private:
  BinaryNode *root;

iterator insert( const C & x, BinaryNode * & t,
	       BinaryNode * & par )
  {
    if( t == nullptr )
      {
	t = new BinaryNode{ x, nullptr, nullptr, par };
	return iterator(t);
      }
    else if( x < t->element )
      {
	CLUMSY_COUNT++;
	return insert( x, t->left, t );
      }
    else if( t->element < x )
      {
	CLUMSY_COUNT++;
	return insert( x, t->right, t );
      }
    else
      return iterator(t); // Duplicate; do nothing
  }

iterator insert( C && x, BinaryNode * & t, BinaryNode *
	       & par )
  {
    if( t == nullptr )
      {
	t = new BinaryNode{ std::move( x ), nullptr,
			    nullptr, par };
	return iterator(t);
      }
    else if( x < t->element )
      return insert( std::move( x ), t->left, t );
    else if( t->element < x )
      return insert( std::move( x ), t->right, t );
    else
      return iterator(t); // Duplicate; do nothing
  }

void remove( const C & x, BinaryNode * & t )
  {
    if( t == nullptr )
      return;
    // Item not found; do nothing
    if( x < t->element )
      remove( x, t->left );
    else if( t->element < x )
      remove( x, t->right );
    else if( t->left != nullptr && t->right !=
	     nullptr ) // Two children
      {
	t->element = findMin( t->right )->element;
	remove( t->element, t->right );
      }
    else{
      BinaryNode *oldNode = t;
      if (t->left != nullptr)
	{
	  t->left->parent = t->parent;
	  t = t->left;
	}
      else
	{
	  if (t->right != 0)
	    t->right->parent = t->parent;
	  t = t->right;
	}
      delete oldNode;
    }
  }

  BinaryNode * findMin( BinaryNode *t ) const
  {
    if( t == nullptr )
      return nullptr;
    if( t->left == nullptr )
      return t;
    return findMin( t->left );
  }

BinaryNode * findMax( BinaryNode *t ) const
  {
    if( t != nullptr )
      while( t->right != nullptr )
	t = t->right;
    return t;
  }

bool contains( const C & x, BinaryNode *t ) const
  {
    if( t == nullptr )
      return false;
    else if( x < t->element )
      return contains( x, t->left );
    else if( t->element < x )
      return contains( x, t->right );
    else
      return true;
    // Match
  }

void makeEmpty( BinaryNode * & t )
  {
    if( t != nullptr )
      {
	makeEmpty( t->left );
	makeEmpty( t->right );
	delete t;
      }
    t = nullptr;
  }

void printTree( BinaryNode *t, ostream & out )
    const
  {
    if( t != nullptr )
      {
	printTree( t->left, out );out << t->element << endl;
	printTree( t->right, out );
      }
  }

void printInternal(BinaryNode* t, int offset)
  {
    for(int i = 1; i <= offset; i++)
      cout << "..";
    if (t == nullptr)
      {
	cout << "#" << endl;
	return;
      }
    cout << t->element << endl;
    printInternal(t->left, offset + 1);
    printInternal(t->right, offset + 1);
  }


BinaryNode * clone1(BinaryNode *t) const
  {
    if (t == nullptr)
      return nullptr;
    else
      return new BinaryNode(t->element, clone1(t->left),
			    clone1(t->right), nullptr);
  }

void put_parents(BinaryNode * t, BinaryNode * par)
     const
  {
    if (t == nullptr)
      return;
    t->parent = par;
    if (t->left != nullptr)
      put_parents(t->left, t);
    if (t->right != nullptr)
      put_parents(t->right, t);
  }

BinaryNode * clone(BinaryNode *t) const
  {
    BinaryNode * theclone = clone1(t);
    put_parents(theclone, nullptr);
    return theclone;
  }

int size(BinaryNode* t) const
  {
    if (t == nullptr)
      return 0;
    return 1 + size(t->left) + size(t->right);
  }
};
#endif
