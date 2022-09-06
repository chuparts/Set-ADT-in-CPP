
#include "set.h"

const treenode* find( const treenode* n, const std::string& s )
{
	while (n != nullptr)
	{
	        if (n->value == s)
        	{
                	return n;
        	}

		if (n->value < s)
		{
			n = n->right;
		}
		else if (n->value > s)
		{
			n = n->left;
		}
	}

	return nullptr;

}

treenode** find( treenode** n, const std::string& s )
{
	treenode* x = *n;

        while (x != nullptr)
        {
                if (x->value == s)
                {
                	treenode** y = &x;
                       return y;
                }

		else if (x->value > s)
                {
			if (x->left == nullptr) 
			{
				return &(x->left);
                       }
                       x = x->left;
                }
                else if (x->value < s)
                {
			if (x->right == nullptr) 
			{
				return &(x->right);
                       }
                       x = x->right;
                }
        }
	treenode** y = &x;
	return y;
}

size_t size( const treenode* n )
{
	size_t sz = 1;
	if (n == nullptr)
	{
		return 0;
	}
	else
	{
		size_t left = size(n->left);
		size_t right = size(n->right);
		return sz + left + right;
	}
}

size_t height( const treenode* n )
{
	if (n == nullptr)
	{
		return 1;
	}
	else if (n != nullptr && n->right == nullptr && n->left == nullptr)
	{
		return 1;
	}
	else
	{
		size_t left = height(n->left);
		size_t right = height(n->right);

		if(left > right)
		{
			return left + 1;
		}
		else
		{
			return right + 1;
		}
	}
}

void deallocate( treenode* n )
{
	if (n != nullptr)
	{
		deallocate(n->left);
		treenode* l_trash;
		treenode* r_trash;
		if (n != nullptr)
		{
			l_trash = n;
		}
		else
		{
			l_trash = nullptr;
		}
		deallocate(n->right);
		if (n != nullptr)
		{
			r_trash = n;
		}
		else
		{
			r_trash = nullptr;
		}
		if (l_trash != nullptr && r_trash != nullptr)
		{
			if (l_trash == r_trash)
			{
				delete n;
			}
			else
			{
				delete l_trash, r_trash;
			}
		}
	}
	else
	{
		n = nullptr;
	}

}

treenode* makecopy( const treenode* n ) 
{	
	if (n)
	{
		treenode* cpy = new treenode(n->value, nullptr, nullptr);
                if (n != nullptr)
                {
                        cpy->value = n->value;
                }
                else
                {
                        delete cpy;
                }
		cpy->left = makecopy(n->left);
		cpy->right = makecopy(n->right);
		return cpy;
	}
	else
	{
		return nullptr;
	}
}



void print( std::ostream& out, const treenode* n, unsigned int indent )
{
   for( unsigned int i = 0; i != indent; ++ i )
      out << "|  "; 
   if(n)
   {
      out << ( n -> value ) << "\n";
      print( out, n -> left, indent + 1 );
      print( out, n -> right, indent + 1 ); 
   }
   else
      out << "#\n"; 
}


// Both the upperbound and the lowerbound are strict,
// we use pointers, so that they can be absent. 

void checkbetween( const treenode* n, 
                   const std::string* lowerbound, 
                   const std::string* upperbound ) 
{
   while(n) 
   {
      if( lowerbound && *lowerbound >= n -> value )
      {
         std::cout << "value " << ( n -> value );
         std::cout << " is not above lower bound " << *lowerbound << "\n";
         throw std::runtime_error( "tree not correct" ); 
      }

      if( upperbound && n -> value >= *upperbound )
      {
         std::cout << "value " << ( n -> value );
         std::cout << "is not below upperbound " << *upperbound << "\n";
         throw std::runtime_error( "tree not correct" );  
      }

      checkbetween( n -> left, lowerbound, &( n -> value ));
      lowerbound = & ( n -> value );
      n = n -> right;
   }
} 


unsigned int log_base2( size_t s )
{
	size_t i = 0, k = 1;
	for(i, k; k < s; i++)
	{
		k = k*2;
	}
	return i;
}

bool set::contains( const std::string& s ) const
{
	if (::find(tr, s) != nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

 
bool set::insert( const std::string& s) 
{

	treenode** x = &tr;
	x = ::find(x, s);

        if (*x == nullptr && tr != nullptr)
        {
		*x = new treenode(s, nullptr, nullptr);
		return true;
	}
	else if (tr == nullptr)
        {
                tr = new treenode(s, nullptr, nullptr);
                return true;
	}
	else
	{
		return false;
	}	
}

size_t set::size( ) const
{
	size_t sz = ::size(tr);
	return sz;
}

size_t set::height( ) const
{
	if (!tr)
	{
		return 0;
	}
	else
	{
		size_t height = ::height(tr);
		return height;
	}
}

bool set::empty( ) const
{
	if (tr == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

set:: ~set( )
{
	if (tr != nullptr && tr->right == nullptr && tr->left == nullptr)
	{
		delete tr;
	}
	else if (tr)
	{
		::deallocate(tr);
	}
}

void set::clear( )
{
	::deallocate(tr);
	tr = nullptr;	
}

set::set( const set& other )
{
	tr = ::makecopy(other.tr);
}


set& set::operator = ( const set& other )
{
	if (tr == other.tr)
	{
		return *this;
	}
	else
	{
		::deallocate(tr);
		tr = ::makecopy(other.tr);
		return *this;
	}
}



void set::checksorted( ) const
{
   ::checkbetween( tr, nullptr, nullptr );
}


void set::print( std::ostream& out, unsigned int indent ) const
{
   ::print( out, tr, indent );
}

