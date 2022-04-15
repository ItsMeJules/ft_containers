#include <iostream>
#include <vector>
#include <typeinfo>
#include "vector.hpp"
#include "map.hpp"
#include "utils/utility.hpp"

#define C_YELLOW "\e[33m"
#define C_RESET "\e[0m"

template <typename T>
typename ft::enable_if<ft::is_integral<T>::value, bool>::type is_odd(T i) {
	return bool(i % 2);
}

bool mypredicate(int i, int j) {
	return i == j;
}

bool mycomp(char c1, char c2) {
	return std::tolower(c1) < std::tolower(c2);
}

bool fncomp(char lhs, char rhs) {
	return lhs < rhs;
}

bool fncomp(int lhs, int rhs) {
	return lhs < rhs;
}

struct classcomp {
  	bool operator()(const char& lhs, const char& rhs) const {
		return lhs < rhs;
	}

  	bool operator()(const int& lhs, const int& rhs) const {
		return lhs < rhs;
	}
};

int main() {
	std::cout << std::endl << C_YELLOW << "\t\tVECTOR TESTS" << C_RESET << std::endl;
	{
		std::cout << std::endl << C_YELLOW << "VECTOR CONSTRUCTORS" << C_RESET << std::endl;
		{
  			ft::vector<int> first;                                // empty vector of ints
  			ft::vector<int> second (4,100);                       // four ints with value 100
  			ft::vector<int> third (second.begin(),second.end());  // iterating through second
  			ft::vector<int> fourth (third);                       // a copy of third

  			int myints[] = {16,2,77,29};
 			ft::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int) );
  			std::cout << "The contents of fifth are:";
  			for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
   				std::cout << ' ' << *it;
  			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::ASSIGN" << C_RESET << std::endl;
		{
			ft::vector<int> first;
		  	ft::vector<int> second;
		  	ft::vector<int> third;

			first.assign (7,100);             // 7 ints with a value of 100
	  		ft::vector<int>::iterator it;
	  		it=first.begin()+1;
  			second.assign (it,first.end()-1); // the 5 central values of first
  			int myints[] = {1776,7,4};
  			third.assign (myints,myints+3);   // assigning from array.
  			std::cout << "Size of first: " << int (first.size()) << '\n';
  			std::cout << "Size of second: " << int (second.size()) << '\n';
  			std::cout << "Size of third: " << int (third.size()) << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::AT" << C_RESET << std::endl;
		{
			ft::vector<int> myvector (10);   // 10 zero-initialized ints

  			for (unsigned i=0; i<myvector.size(); i++)
  				myvector.at(i)=i;
			std::cout << "myvector contains:";
  			for (unsigned i=0; i<myvector.size(); i++)
    			std::cout << ' ' << myvector.at(i);
  			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::BACK" << C_RESET << std::endl;
		{
			ft::vector<int> myvector;

 			myvector.push_back(10);
			while (myvector.back() != 0)
  				myvector.push_back ( myvector.back() -1 );
  			std::cout << "myvector contains:";
  			for (unsigned i=0; i<myvector.size() ; i++)
    			std::cout << ' ' << myvector[i];
  			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::FRONT" << C_RESET << std::endl;
		{
			ft::vector<int> myvector;

			myvector.push_back(78);
 			std::cout << "myvector.front() is " << myvector.front() << '\n';
			myvector.push_back(16);
			myvector.front() -= myvector.back();
 			std::cout << "myvector.front() is now " << myvector.front() << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::BEGIN" << C_RESET << std::endl;
		{
			ft::vector<int> myvector;

 			myvector.push_back(10);
  			while (myvector.back() != 0)
  				myvector.push_back(myvector.back() -1);
  			std::cout << "myvector contains:";
  			for (unsigned i = 0; i < myvector.size() ; i++)
  				std::cout << ' ' << myvector[i];
  			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::END" << C_RESET << std::endl;
		{
			ft::vector<int> myvector;

			for (int i=1; i<=5; i++)
				myvector.push_back(i);
			std::cout << "myvector contains:";
			for (ft::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::RBEGIN" << C_RESET << std::endl;
		{
			ft::vector<int> myvector (5);  // 5 default-constructed ints

			int i=0;
			ft::vector<int>::reverse_iterator rit = myvector.rbegin();
			for (; rit != myvector.rend(); ++rit)
				*rit = ++i;
			std::cout << "myvector contains:";
			for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::REND" << C_RESET << std::endl;
		{
			ft::vector<int> myvector (5);  // 5 default-constructed ints

			ft::vector<int>::reverse_iterator rit = myvector.rbegin();
			int i=0;
			for (rit = myvector.rbegin(); rit!= myvector.rend(); ++rit)
				*rit = ++i;
			std::cout << "myvector contains:";
			for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::CAPACITY VECTOR::SIZE VECTOR::MAX_SIZE" << C_RESET << std::endl;
		{
			ft::vector<int> myvector;

  			for (int i=0; i<100; i++)
			  	myvector.push_back(i);
  			std::cout << "size: " << (int) myvector.size() << '\n';
  			std::cout << "capacity: " << (int) myvector.capacity() << '\n';
  			std::cout << "max_size: " << (int) myvector.max_size() << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::CLEAR" << C_RESET << std::endl;
		{
			ft::vector<int> myvector;
			myvector.push_back (100);
			myvector.push_back (200);
			myvector.push_back (300);

			std::cout << "myvector contains before clear:";
			for (unsigned i=0; i<myvector.size(); i++)
				std::cout << ' ' << myvector[i];
			std::cout << '\n';
			myvector.clear();
			std::cout << "myvector contains after clear:";
			for (unsigned i=0; i<myvector.size(); i++)
				std::cout << ' ' << myvector[i];
			std::cout << '\n';
			myvector.push_back (1101);
			myvector.push_back (2202);
			std::cout << "myvector contains:";
			for (unsigned i=0; i<myvector.size(); i++)
				std::cout << ' ' << myvector[i];
			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::EMPTY" << C_RESET << std::endl;
		{
			ft::vector<int> myvector;
  			int sum(0);

			std::cout << std::boolalpha;
			std::cout << myvector.empty() << std::endl;
			for (int i=1;i<=10;i++)
				myvector.push_back(i);
			while (!myvector.empty())
			{
				sum += myvector.back();
				myvector.pop_back();
			}
			std::cout << "total: " << sum << '\n';
			std::cout << myvector.empty() << std::endl;
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::ERASE" << C_RESET << std::endl;
		{
			ft::vector<int> myvector;

			for (int i=1; i<=10; i++)
				myvector.push_back(i);
			std::cout << "myvector contains before erase:";
			for (unsigned i=0; i<myvector.size(); ++i)
				std::cout << ' ' << myvector[i];
			std::cout << '\n';
			myvector.erase (myvector.begin()+5);
			myvector.erase (myvector.begin(),myvector.begin()+3);
			std::cout << "myvector contains after erase:";
			for (unsigned i=0; i<myvector.size(); ++i)
				std::cout << ' ' << myvector[i];
			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::GET_ALLOCATOR" << C_RESET << std::endl;
		{
			ft::vector<int> myvector;
			int * p;
			unsigned int i;

			p = myvector.get_allocator().allocate(5);
			for (i=0; i<5; i++)
				myvector.get_allocator().construct(&p[i],i);
			std::cout << "The allocated array contains:";
			for (i=0; i<5; i++)
				std::cout << ' ' << p[i];
			std::cout << '\n';
			for (i=0; i<5; i++)
				myvector.get_allocator().destroy(&p[i]);
			myvector.get_allocator().deallocate(p,5);
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::INSERT" << C_RESET << std::endl;
		{
			ft::vector<int> myvector (3,100);
			ft::vector<int>::iterator it;

			it = myvector.begin();
			it = myvector.insert( it , 200 );
			myvector.insert(it,2,300);
			it = myvector.begin();
			ft::vector<int> anothervector (2,400);
			myvector.insert(it+2,anothervector.begin(),anothervector.end());
			int myarray [] = { 501,502,503 };
			myvector.insert(myvector.begin(), myarray, myarray+3);
			std::cout << "myvector contains:";
			for (it=myvector.begin(); it<myvector.end(); it++)
				std::cout << ' ' << *it;
			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::OPERATOR=" << C_RESET << std::endl;
		{
			ft::vector<int> foo (3,0);
			ft::vector<int> bar (5,0);

			bar = foo;
			foo = ft::vector<int>();
			std::cout << "Size of foo: " << int(foo.size()) << '\n';
			std::cout << "Size of bar: " << int(bar.size()) << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::OPERATOR[]" << C_RESET << std::endl;
		{
			ft::vector<int> myvector (10);   // 10 zero-initialized elements
			ft::vector<int>::size_type sz = myvector.size();

			for (unsigned i=0; i<sz; i++)
				myvector[i]=i;
			for (unsigned i=0; i<sz/2; i++)
			{
				int temp;
				temp = myvector[sz-1-i];
				myvector[sz-1-i]=myvector[i];
				myvector[i]=temp;
			}
			std::cout << "myvector contains:";
			for (unsigned i=0; i<sz; i++)
				std::cout << ' ' << myvector[i];
			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::PUSH_BACK VECTOR::POP_BACK" << C_RESET << std::endl;
		{
			ft::vector<int> myvector;
			int sum (0);

			myvector.push_back (100);
			myvector.push_back (200);
			myvector.push_back (300);
			while (!myvector.empty())
			{
				sum += myvector.back();
				myvector.pop_back();
			}
			std::cout << "The elements of myvector add up to " << sum << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::RESERVE" << C_RESET << std::endl;
		{
			ft::vector<int>::size_type sz;
			ft::vector<int> bar;

			ft::vector<int> foo;
			sz = foo.capacity();
			std::cout << "making foo grow:\n";
			for (int i=0; i<100; ++i)
			{
				foo.push_back(i);
				if (sz!=foo.capacity())
				{
					sz = foo.capacity();
					std::cout << "capacity changed: " << sz << '\n';
				}
			}
			sz = bar.capacity();
			bar.reserve(100);
			std::cout << "making bar grow:\n";
			for (int i=0; i<100; ++i)
			{
				bar.push_back(i);
				if (sz!=bar.capacity())
				{
					sz = bar.capacity();
					std::cout << "capacity changed: " << sz << '\n';
				}
  			}
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::RESIZE" << C_RESET << std::endl;
		{
			ft::vector<int> myvector;

			for (int i=1;i<10;i++)
				myvector.push_back(i);
			myvector.resize(5);
			myvector.resize(8,100);
			myvector.resize(12);
			std::cout << "myvector contains:";
			for (size_t i=0;i<myvector.size();i++)
				std::cout << ' ' << myvector[i];
			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::SWAP" << C_RESET << std::endl;
		{
			ft::vector<int> foo (3,100);
			ft::vector<int> bar (5,200);

			foo.swap(bar);
			std::cout << "foo contains:";
			for (unsigned i=0; i<foo.size(); i++)
				std::cout << ' ' << foo[i];
			std::cout << '\n';
			std::cout << "bar contains:";
			for (unsigned i=0; i<bar.size(); i++)
				std::cout << ' ' << bar[i];
			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::SWAP (NON MEMBER)" << C_RESET << std::endl;
		{
			ft::vector<int> foo (3,100);   // three ints with a value of 100
			ft::vector<int> bar (5,200);   // five ints with a value of 200

			ft::swap(bar, foo);
			std::cout << "foo contains:";
			for (ft::vector<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';
			std::cout << "bar contains:";
			for (ft::vector<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';
		}
		std::cout << std::endl << C_YELLOW << "VECTOR::RELATIONNAL_OP" << C_RESET << std::endl;
		{
			ft::vector<int> foo (3,100);   // three ints with a value of 100
  			ft::vector<int> bar (2,200);   // two ints with a value of 200

			if (foo==bar) std::cout << "foo and bar are equal\n";
			if (foo!=bar) std::cout << "foo and bar are not equal\n";
			if (foo < bar) std::cout << "foo is less than bar\n";
			if (foo> bar) std::cout << "foo is greater than bar\n";
			if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
			if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
		}
	}
	std::cout << std::endl << C_YELLOW << "\t\tMAP TESTS" << C_RESET << std::endl;
	{
		std::cout << std::endl << C_YELLOW << "MAP CONSTRUCTORS" << C_RESET << std::endl;
		{
			ft::map<char,int> first;

			first['a']=10;
			first['b']=30;
			first['c']=50;
			first['d']=70;

			ft::map<char,int> second (first.begin(),first.end());

			ft::map<char,int> third (second);

			ft::map<char,int,classcomp> fourth;                 // class as Compare

			bool(*fn_pt)(char,char) = fncomp;
			ft::map<char,int,bool(*)(char,char)> fifth (fn_pt);
		}
		std::cout << std::endl << C_YELLOW << "MAP::begin && Map::end" << C_RESET << std::endl;
		{
			ft::map<char,int> mymap;

			mymap['b'] = 100;
			mymap['a'] = 200;
			mymap['c'] = 300;

			for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';
		}
		std::cout << std::endl << C_YELLOW << "MAP::rbegin && MAP::rend" << C_RESET << std::endl;
		{
			ft::map<char,int> mymap;

			mymap['x'] = 100;
			mymap['y'] = 200;
			mymap['z'] = 300;

			// show content:
			ft::map<char,int>::reverse_iterator rit;
			for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
				std::cout << rit->first << " => " << rit->second << '\n';		
		}
		std::cout << std::endl << C_YELLOW << "MAP::clear" << C_RESET << std::endl;
		{
			ft::map<char,int> mymap;

			mymap['x']=100;
			mymap['y']=200;
			mymap['z']=300;

			std::cout << "mymap contains:\n";
			for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';

			mymap.clear();
			mymap['a']=1101;
			mymap['b']=2202;

			std::cout << "mymap contains:\n";
			for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';
		}
		std::cout << std::endl << C_YELLOW << "MAP::count" << C_RESET << std::endl;
		{
			ft::map<char,int> mymap;
			char c;

			mymap ['a']=101;
			mymap ['c']=202;
			mymap ['f']=303;

			for (c='a'; c<'h'; c++)
			{
				std::cout << c;
				if (mymap.count(c)>0)
				std::cout << " is an element of mymap.\n";
				else 
				std::cout << " is not an element of mymap.\n";
			}
		}
		std::cout << std::endl << C_YELLOW << "MAP::empty" << C_RESET << std::endl;
		{
			ft::map<char,int> mymap;

			mymap['a']=10;
			mymap['b']=20;
			mymap['c']=30;

			while (!mymap.empty())
			{
				std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
				mymap.erase(mymap.begin());
 			}
		}
		std::cout << std::endl << C_YELLOW << "MAP::equal_range" << C_RESET << std::endl;
		{
			ft::map<char,int> mymap;

			mymap['a']=10;
			mymap['b']=20;
			mymap['c']=30;

			ft::pair<ft::map<char,int>::iterator,ft::map<char,int>::iterator> ret;
			ret = mymap.equal_range('b');

			std::cout << "lower bound points to: ";
			std::cout << ret.first->first << " => " << ret.first->second << '\n';

			std::cout << "upper bound points to: ";
			std::cout << ret.second->first << " => " << ret.second->second << '\n';
		}
		std::cout << std::endl << C_YELLOW << "MAP::erase" << C_RESET << std::endl;
		{
			ft::map<char,int> mymap;
			ft::map<char,int>::iterator it;

			// insert some values:
			mymap['a']=10;
			mymap['b']=20;
			mymap['c']=30;
			mymap['d']=40;
			mymap['e']=50;
			mymap['f']=60;

			it=mymap.find('b');
			mymap.erase (it);                   // erasing by iterator

			mymap.erase ('c');                  // erasing by key

			it=mymap.find ('e');
			mymap.erase ( it, mymap.end() );    // erasing by range

			// show content:
			for (it=mymap.begin(); it!=mymap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';
		}
		std::cout << std::endl << C_YELLOW << "MAP::find" << C_RESET << std::endl;
		{
			ft::map<char,int> mymap;
			ft::map<char,int>::iterator it;

			mymap['a']=50;
			mymap['b']=100;
			mymap['c']=150;
			mymap['d']=200;

			it = mymap.find('b');
			if (it != mymap.end())
				mymap.erase (it);

			// print content:
			std::cout << "elements in mymap:" << '\n';
			std::cout << "a => " << mymap.find('a')->second << '\n';
			std::cout << "c => " << mymap.find('c')->second << '\n';
			std::cout << "d => " << mymap.find('d')->second << '\n';
		}
		std::cout << std::endl << C_YELLOW << "MAP::get_allocator" << C_RESET << std::endl;
		{
			int psize;
			ft::map<char,int> mymap;
			ft::pair<const char,int>* p;

			// allocate an array of 5 elements using mymap's allocator:
			p=mymap.get_allocator().allocate(5);

			// assign some values to array
			psize = sizeof(ft::map<char,int>::value_type)*5;

			std::cout << "The allocated array has a size of " << psize << " bytes.\n";

			mymap.get_allocator().deallocate(p,5);		
		}
		std::cout << std::endl << C_YELLOW << "MAP::insert" << C_RESET << std::endl;
		{
			ft::map<char,int> mymap;

			// first insert function version (single parameter):
			mymap.insert ( ft::pair<char,int>('a',100) );
			mymap.insert ( ft::pair<char,int>('z',200) );

			ft::pair<ft::map<char,int>::iterator,bool> ret;
			ret = mymap.insert ( ft::pair<char,int>('z',500) );
			if (ret.second==false) {
				std::cout << "element 'z' already existed";
				std::cout << " with a value of " << ret.first->second << '\n';
			}

			// second insert function version (with hint position):
			ft::map<char,int>::iterator it = mymap.begin();
			mymap.insert (it, ft::pair<char,int>('b',300));  // max efficiency inserting
			mymap.insert (it, ft::pair<char,int>('c',400));  // no max efficiency inserting

			// third insert function version (range insertion):
			ft::map<char,int> anothermap;
			anothermap.insert(mymap.begin(),mymap.find('c'));

			// showing contents:
			std::cout << "mymap contains:\n";
			for (it=mymap.begin(); it!=mymap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';

			std::cout << "anothermap contains:\n";
			for (it=anothermap.begin(); it!=anothermap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';		
		}
		std::cout << std::endl << C_YELLOW << "MAP::key_comp" << C_RESET << std::endl;
		{
			ft::map<char,int> mymap;

			ft::map<char,int>::key_compare mycomp = mymap.key_comp();

			mymap['a']=100;
			mymap['b']=200;
			mymap['c']=300;

			std::cout << "mymap contains:\n";

			char highest = mymap.rbegin()->first;     // key value of last element

			ft::map<char,int>::iterator it = mymap.begin();
			do {
				std::cout << it->first << " => " << it->second << '\n';
			} while ( mycomp((*it++).first, highest) );

			std::cout << '\n';		
		}
		std::cout << std::endl << C_YELLOW << "MAP::lower_bound && MAP::upper_bound" << C_RESET << std::endl;
		{
			ft::map<char,int> mymap;
			ft::map<char,int>::iterator itlow,itup;

			mymap['a']=20;
			mymap['b']=40;
			mymap['c']=60;
			mymap['d']=80;
			mymap['e']=100;

			itlow=mymap.lower_bound ('b');  // itlow points to b
			itup=mymap.upper_bound ('d');   // itup points to e (not d!)

			mymap.erase(itlow,itup);        // erases [itlow,itup)

			// print content:
			for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';		
		}
		std::cout << std::endl << C_YELLOW << "MAP::max_size" << C_RESET << std::endl;
		{
			int i;
			ft::map<int,int> mymap;

			if (mymap.max_size()>1000)
			{
				for (i=0; i<1000; i++) mymap[i]=0;
				std::cout << "The map contains 1000 elements.\n";
			}
 			 else std::cout << "The map could not hold 1000 elements.\n";		
		}
		std::cout << std::endl << C_YELLOW << "MAP::operator=" << C_RESET << std::endl;
		{
			ft::map<char,int> first;
			ft::map<char,int> second;

			first['x']=8;
			first['y']=16;
			first['z']=32;

			second=first;                // second now contains 3 ints
			first=ft::map<char,int>();  // and first is now empty

			std::cout << "Size of first: " << first.size() << '\n';
			std::cout << "Size of second: " << second.size() << '\n';		
		}
		std::cout << std::endl << C_YELLOW << "MAP::operator[]" << C_RESET << std::endl;
		{
			ft::map<char,std::string> mymap;

			mymap['a']="an element";
			mymap['b']="another element";
			mymap['c']=mymap['b'];

			std::cout << "mymap['a'] is " << mymap['a'] << '\n';
			std::cout << "mymap['b'] is " << mymap['b'] << '\n';
			std::cout << "mymap['c'] is " << mymap['c'] << '\n';
			std::cout << "mymap['d'] is " << mymap['d'] << '\n';

 			 std::cout << "mymap now contains " << mymap.size() << " elements.\n";
		}
		std::cout << std::endl << C_YELLOW << "MAP::size" << C_RESET << std::endl;
		{
			ft::map<char,int> mymap;
			mymap['a']=101;
			mymap['b']=202;
			mymap['c']=302;

			std::cout << "mymap.size() is " << mymap.size() << '\n';
		}
		std::cout << std::endl << C_YELLOW << "MAP::swap" << C_RESET << std::endl;
		{
			ft::map<char,int> foo,bar;

			foo['x']=100;
			foo['y']=200;

			bar['a']=11;
			bar['b']=22;
			bar['c']=33;

			foo.swap(bar);

			std::cout << "foo contains:\n";
			for (ft::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';

			std::cout << "bar contains:\n";
			for (ft::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';	
		}
		std::cout << std::endl << C_YELLOW << "MAP::value_comp" << C_RESET << std::endl;
		{
			ft::map<char,int> mymap;

			mymap['x']=1001;
			mymap['y']=2002;
			mymap['z']=3003;

			std::cout << "mymap contains:\n";

			ft::pair<char,int> highest = *mymap.rbegin();          // last element

			ft::map<char,int>::iterator it = mymap.begin();
			do {
				std::cout << it->first << " => " << it->second << '\n';
 			} while ( mymap.value_comp()(*it++, highest) );
		}
		std::cout << std::endl << C_YELLOW << "Map relationnals operators" << C_RESET << std::endl;
		{
			ft::map<char,int> foo,bar;
			foo['a']=100;
			foo['b']=200;
			bar['a']=10;
			bar['z']=1000;

			// foo ({{a,100},{b,200}}) vs bar ({a,10},{z,1000}}):
			if (foo == bar) std::cout << "foo and bar are equal\n";
			if (foo != bar) std::cout << "foo and bar are not equal\n";
			if (foo < bar) std::cout << "foo is less than bar\n";
			if (foo > bar) std::cout << "foo is greater than bar\n";
			if (foo <= bar) std::cout << "foo is less than or equal to bar\n";
			if (foo >= bar) std::cout << "foo is greater than or equal to bar\n";	
		}
	}
}