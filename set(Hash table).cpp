
#include "set.h"

size_t case_insensitive::hash( const std::string& s )
{
	std::string cpy = s;
	
	for (size_t i = 0; cpy[i]; i++)
	{
		cpy[i] = tolower(cpy[i]);
	}
	

	size_t fin = 0; // final value
	
	for (size_t i = 0; cpy[i]; i++)
	{
		
		size_t mult = cpy[i];
		
		for (size_t k = 0; k < (cpy.size() - i - 1); k++)
		{
			mult = mult * 31;
		}
		
		fin = fin + mult;
	}
	return fin;
}

bool case_insensitive::equal( const std::string& s1, const std::string& s2 )
{
	std::string cpy1 = s1;
	std::string cpy2 = s2;


	for (size_t i = 0; cpy1[i]; i++)
	{
		cpy1[i] = tolower(cpy1[i]);
	}
	
	for (size_t i = 0; cpy2[i]; i++)
	{
		cpy2[i] = tolower(cpy2[i]);
	}
	
	if (cpy1 == cpy2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool set::insert_norehash( const std::string& s )
{
	size_t hash = case_insensitive::hash(s);
	hash = hash % buckets.size();
	
	
	for ( auto it = buckets[hash]. begin( ); it != buckets[hash]. end( ); ++ it )
	{
		if (case_insensitive::equal(s, *it))
		{
			return false;
		}
	}
	
	set_size++;
	buckets[hash].push_back(s);
	return true;
}

void set::consider_rehash( )
{
	set q(3);
	q.set_size = set_size;
	
	size_t load = q.set_size / q.buckets.size();
	
	if (load > q.max_load_factor)
	{
		size_t i = 0;
		while (load > q.max_load_factor)
		{
			i++;
			q.buckets.resize(8<<i);
			load = q.set_size / q.buckets.size();
		}
		
		
		for (size_t i = 0; i < buckets.size(); i++)
		{
			for( auto it = buckets[i]. begin( ); it != buckets[i]. end( ); ++ it)
			{
				q.insert_norehash(*it);
			}
		}
		q.set_size = set_size;
		*this = q;
	}
}

set::set( std::initializer_list< std::string > init,
          double max_load_factor )
   : max_load_factor( max_load_factor ),
   buckets( std::vector< buckettype > (8) ),
   set_size(0)
{
	for (std::string str : init)
	{
		insert(str);
	}
}

bool set::contains( const std::string& s ) const
{
	size_t hash = case_insensitive::hash(s);
	hash = hash % buckets.size();
	
	
	for ( auto it = buckets[hash]. begin( ); it != buckets[hash]. end( ); ++ it )
	{
		if (case_insensitive::equal(s, *it))
		{
			return true;
		}
	}
	return false;
}

bool set::insert( const std::string& s )
{
	if (insert_norehash(s) == true)
	{
		consider_rehash();
		return true;
	}
	else
	{
		return false;
	}
}

bool set::remove( const std::string& s )
{
	size_t hash = case_insensitive::hash(s);
	hash = hash % buckets.size();
	
	
	for ( auto it = buckets[hash]. begin( ); it != buckets[hash]. end( ); ++ it )
	{
		if (case_insensitive::equal(s, *it))
		{
			buckets[hash].erase(it);
			set_size--;
			return true;
		}
	}
		return false;
}

size_t set::size( ) const
{
	return set_size;
}

bool set::empty( ) const
{
	if (set_size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void set::clear( )
{
	for (size_t i = 0; i < buckets.size(); i++)
	{
		buckets[i].clear();
	}
	set_size = 0;
}

void set::print( std::ostream& out ) const
{
	for (size_t i = 0; i < buckets.size(); i++)
	{
		out << "bucket[" << i << "]:\t{ ";
		size_t k = 0;
		for( auto it = buckets[i]. begin( ); it != buckets[i]. end( ); ++ it)
		{
			k++;
			
			if (k == (buckets[i].size()))
			{
				out << *it;
			}
			else
			{
				out << *it << ", ";
			}
		}
		out << " }\n";
	}
}
