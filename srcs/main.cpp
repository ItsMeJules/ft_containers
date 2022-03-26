#include <iostream>
#include <vector>
#include "vector.hpp"

#define C_YELLOW "\e[33m"
#define C_RESET "\e[0m"

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
 			ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );
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
			for (; rit!= myvector.rend(); ++rit)
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

			foo.swap(bar);
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
			if (foo< bar) std::cout << "foo is less than bar\n";
			if (foo> bar) std::cout << "foo is greater than bar\n";
			if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
			if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
		}
	}
}