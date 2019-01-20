// Set.h
// KV May 2018, based on  BinarySearchTree, Weiss, textook

// KV replaced exceptions with assert statements;

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

//#include "dsexceptions.h"
#include <cassert>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;       


template <typename C>
class Set
{
 private:
  struct BinaryNode
  {
    C element;
    BinaryNode *left;
    BinaryNode *right;
    BinaryNode *parent;

    BinaryNode(const C & elem, BinaryNode *lt, BinaryNode *rt,
	       BinaryNode *par)
    : element(elem), left(lt), right(rt), parent(par) {}
  };
  
  public:

  //struct BinaryNode;

  class iterator
  {
  public:
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
	if (irt(current))
	  current = lm(current->right);
	else if (ilc(current))
	  {
	    if (current->left == nullptr && current->right == nullptr)
	      current = current->parent;
	    else if (current->right != nullptr)
	      current = lm(current->right);
	    else
	      ; // should not happen
	  }
	else if (irc(current))
	  {
	    if (current->right != nullptr)
	      current = lm(current->right);
	    else
	      current = fpul(current);
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

    bool irt(BinaryNode * t)
    {
      return (t != nullptr && t->parent == nullptr);
    }

    bool ilc(BinaryNode *t)
    {
      assert(t != nullptr);
      if (t->parent != nullptr && t->parent->left == t)
	return true;
      else
	return  false;
    }

    bool irc(BinaryNode *t)
    {
      assert(t != nullptr);
      if (t->parent != nullptr && t->parent->right == t)
	return true;
      else
	return false;
    }

    BinaryNode * lm(BinaryNode *t)
    {
      if (t == nullptr)
	return nullptr;
      if (t->left == nullptr)
	return t;
      return lm(t->left);
    }

    BinaryNode * fpul(BinaryNode *t)
    {
      if (irt(t))
	return nullptr;
      if (ilc(t))
	return t->parent;
      return fpul(t->parent);
    }

    friend class Set<C>;
  };

 public:
      
  
    Set( ) : root{ nullptr }
    {
    }

    Set( const Set & rhs ) : root{ nullptr }
    {
      root = clone( rhs.root);
    }

    Set( Set && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    

    ~Set( )
    {
        makeEmpty( );
    }


    Set & operator=( const Set & rhs )
    {
        Set copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        

    Set & operator=( Set && rhs )
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
      return insert( x, root, root   );
    }
     

    iterator insert( C && x )
    {
      return insert( std::move( x ), root, root   );
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
      return  theend;
    }

    iterator find(const C & x) const
    {
      return find(x, root);
    }

    int size() const
    {
      if (root == nullptr)
	return 0;
      return 1 + size(root->left) + size(root->right);
    }

 private:

    
    BinaryNode *root;


    iterator insert( const C & x, BinaryNode * & t, BinaryNode * & par )
    {
        if( t == nullptr )
	  {
	    t = new BinaryNode{ x, nullptr, nullptr, par };
	    return iterator(t);
	  }
        else if( x < t->element )
			return insert( x, t->left, t );
        else if( t->element < x )
			return insert( x, t->right, t );
        else
			return iterator(nullptr);  // Duplicate; do nothing
    }
    
    iterator insert( C && x, BinaryNode * & t, BinaryNode * & par )
    {
        if( t == nullptr )
	  {
	    t = new BinaryNode{ std::move( x ), nullptr, nullptr, par };
	    return iterator(t);
	  }
        else if( x < t->element )
			return insert( std::move( x ), t->left, t );
        else if( t->element < x )
			return insert( std::move( x ), t->right, t );
        else
			return iterator(nullptr);  // Duplicate; do nothing
    }

    void remove( const C & x, BinaryNode * & t )
    {
        if( t == nullptr )
            return;   // Item not found; do nothing
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else
        {
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

    iterator find(const C & x,  BinaryNode *t) const
    {
      if (t == nullptr)
	return iterator(nullptr);
      if (t->element == x)
	return iterator(t);
      if (x < t->element)
	return find(x, t->left);
      else
	return find(x, t->right);
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
            return true;    // Match
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


    void printTree( BinaryNode *t, ostream & out ) const
    {
        if( t != nullptr )
        {
            printTree( t->left, out );
            out << t->element << endl;
            printTree( t->right, out );
        }
    }

    void printInternal(BinaryNode* t, int offset)
    {
      if (t == nullptr)
	return;
      
      for(int i = 1; i <= offset; i++)
	cout << "..";
      cout <<  t->element << endl;

      printInternal(t->left, offset + 1);
      printInternal(t->right, offset + 1);
    }
    

    /*
    BinaryNode * clone( BinaryNode *t) const
    {
        if( t == nullptr )
            return nullptr;
        else
	  return new BinaryNode{ t->element, clone( t->left ),
	      clone( t->right )};
	      
    }
    */

    BinaryNode * clone1(BinaryNode *t)  const
    {
      if (t == nullptr)
	return nullptr;
      else
	return new BinaryNode(t->element, clone1(t->left),
			      clone1(t->right), nullptr);
    }

    void put_parents(BinaryNode * t, BinaryNode * par) const
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
	return  0;
      return 1 + size(t->left)  + size(t->right);
      
    }
};

#endif
