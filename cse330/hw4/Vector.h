#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;

template <typename T>
class Vector
{
    public:

	void erase (int k)
	{
		if (k == (theSize + 1))
		{
			pop_back();	
		}
			    
		else 
		{
			for (int i = k; i < theSize; i++)
		    	{
				objects[i] = objects[i+1];
	
		    	}
			--theSize;
		}
	
	    

	}

	void insert (int k, T x)
	{
		if (k == (theSize + 2))
		{
			push_back(x);	
		}
			    
		else 
		{
			push_back(objects[theSize + 1]);			
			for (int i = theSize + 1; i > k; i--)
		    	{
				objects[i] = objects[i - 1];
				
	
		    	}
			objects[k] = x;
		}

	}
        Vector ( int initsize = 0 )
            :   theSize( initsize ),
                theCapacity( initsize + SPARE_CAPACITY )
            { objects = new T[ theCapacity ]; }

        Vector ( const Vector & rhs )
            :   theSize( rhs.theSize ),
                theCapacity( rhs.theCapacity ), objects ( 0 )
            { 
                objects = new T[ theCapacity ]; 
                for ( int k = 0; k < theSize; ++k )
                    objects[ k ] = rhs.objects[ k ];
            }
        Vector & operator= ( const Vector & rhs )
            {
                //Vector copy = rhs;
                Vector copy(rhs);
                std::swap( *this, copy );
                return *this;
            }

        ~Vector( )
        {
            delete [ ] objects;
        }

        Vector( Vector && rhs )
            :  theSize( rhs.theSize ),
               theCapacity(rhs.theCapacity),
               objects{ rhs.objects }
        {
            rhs.objects = nullptr;
            rhs.theSize = 0;
            rhs.theCapacity = 0;
        }

        Vector & operator= ( Vector && rhs )
        {
            std::swap ( theSize, rhs.theSize );
            std::swap ( theCapacity, rhs.theCapacity );
            std::swap ( objects, rhs.objects );

            return *this;
        }

        bool empty( ) const
            { return size ( ) == 0; }

        int size( ) const
            { return theSize; }
        
        int capacity( ) const
            { return theCapacity; }

        T & operator[] ( int index )
        {
            assert (index >= 0 && index < theSize);
            return objects[ index ];
        }

        void resize ( int newSize )
        {
            if ( newSize > theCapacity )
                reserve( newSize * 2 );
            theSize = newSize;
        }

        void reserve ( int newCapacity )
        {
            if( newCapacity < theSize )
                return;
            
            T *newArray = new T[ newCapacity ];

            for( int k = 0; k < theSize; k++ )
                newArray[ k ] = std::move(objects[k]);

            theCapacity = newCapacity;
            std::swap ( objects, newArray );
            delete [ ] newArray;
        }

        void push_back( const T & x)
        {
            if( theSize == theCapacity )
                reserve( 2 * theCapacity + 1 );

            objects[ theSize++ ] = x;
        }

        void push_back( T && x )
        {
            if( theSize == theCapacity )
                reserve( 2 * theCapacity + 1 );
            
            objects[ theSize++ ] = std::move( x );
        }

        void pop_back( )
        {
                assert(!empty());
            --theSize;
        }

        const T & back ( ) const
        {
                assert(!empty());
            return objects[ theSize - 1 ];
        }

        const T & front () const
        {
            assert(!empty());
            return objects[0];
        }

        static const int SPARE_CAPACITY = 2;

    private:
        int theSize;
        int theCapacity;

        T * objects;



};

#endif
