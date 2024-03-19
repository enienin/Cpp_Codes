#include <iostream>
#include <chrono>
#include <algorithm>
#include <vector>

//! NAMESPACE
// un-name namespace
namespace {

}

namespace nc {
	int x;
	namespace eni {		// nested namespace

	}
}

//! Example
namespace nc1 {
	int x;
}

int main()
{
	nc1::x;	// searched inside the namespace
}

//! Example

// it this case, the compiler merges them 
// namespace nc2 {
//	int x;
//	int y;
// }
namespace nc2 {
	int x;
}

namespace nc2 {
	int y;
}

//! Example
int main() {
	// std::cut
	// std::vector
}

//! Example

//array.h

namespace nc3 {

	class Array {

	};

	bool foo(Array);
	//
}

//! Example

namespace ns4 {
	void func4();

	void bar4()
	{
		func4();
		baz4();			// syntax error, compiler searches inside bar4 func then on scope from namespace to bar4
		ns4::baz4();	// still syntax error
	}

	void baz4();
	int y = 34;
}

//! Example
namespace ns5 {

	namespace ns6 {
		int x;
	}

	namespace ns7 {
		int 7;
	}
}

int main()
{
	ns5::ns6::x;	// it should be done like this
	ns5::ns7::y;
}

//! Example
// before nested namespaces should be done like this
namespace ns8 {
	namespace ns9 {
		namespace ns10 {
			int x;
		}
	}
}

// on C++17
namespace ns11::ns12::ns13 {
	int x;
}

int main()
{
	ns11::ns12::ns13::x = 4;
}

//! Example

namespace Enc {
	void foo(int)
	{
		std::cout << "enc::foo(int)\n";
	}

	namespace nested {
		void foo()
		{

			std::cout << "enc::nested::foo()\n";
		}

		void func()
		{
			foo(3);	// syntax error : fuction does not take 1 argument
			// name lookup inside nested namespace first
			// finds 'foo'

			foo();	// legal
			Enc::foo(2);	//legal
		}
	}
}

int main()
{
	Enc::foo(1);
	Enc::nested::foo();
	Enc::nested::func();
}

//! Using declaration
//! Using namespace directive
//! ADL (argument dependent look-up)

//! Using declaration
using fptr = int(*)(int);
enum class color { blue, red, green };
void func()
{
	using enum color;
	blue;

	using color::blue;
	blue;
}

using std::cout;	// using declaration
using std::vector;
using std::string;

using std::cout, std::vector, std::string;	// added to modern c++
void func()
{
	using std::cout;	// scope is just inside the block
	cout;
}

// add explanation from screenshots
// 
// add example for sc

//! Example
namespace ns13
{
	int x;
}

namespace ns14
{

}

int main()
{
	ns14::x = 5;	// syntax error
}

//! Example
namespace ns13
{
	int x;
}

namespace ns14
{
	using ns13::x;	// 'x' is enjected to this scope
}

int main()
{
	ns14::x = 5;	// legal
}

//! Example

void f();

namespace A {
	void g();
}

namespace X {
	using ::f;
	using A::g;
}

int main()
{
	X::f();	// legal
	X::g(); // legal
}

//! Example

using std::cout;
auto ptr = &cout;

void foo()
{
	cout.put('a');	// legal
}

void bar()
{
	cout.put('a');	// legal
}

int main()
{

}

//! Example

// example.h

using std::cout;	// never put inside a heade file


//! Example

namespace nec {
	namespace erg {
		namespace details {
			void foo();
		}
	}
}
namespace can {
	using nec::erg::details::foo();
}

int main()
{
	using nec::erg::details::foo();

	foo();	// legal

	can::foo();
}


//! Example

namespace ns16 {
	class Date {

	};
}

namespace ns17 {
	class Date { };
}

int main()
{
	Date x; // syntax error
	ns16::Date x;
	ns17::Date x;
}

//! Example

namespace ns18 {
	class Date {

	};
}

namespace ns19 {
	class Date { };
}

int main()
{
	using ns19::Date;
	Date x;	// legal
}


//! Using namespace directive
//! Using namespace directive declaration
//! Using namespace declaration
//! Using directive

using namespace std;	// it has a scope

//! Example
namespace nec {
	int x, y, z;
	void foo();
}

int main()
{
	using nec::x;
	using nec::y;
	x = 5;
	y = 5;
}


//! Example

// what using namespace directive does is similiar to putting them in global namespace (there is no enjection like on prev exp )
// int x, y, z;
// void f17();
namespace ns17 {
	int x, y, z;
	void f17();
}

int main()
{
	using namespace ns17;
	x;
	y;
	f17();
}

//! Example

namespace ns18 {
	int x, y, z;
	void f17();
}

int main()
{
	using namespace ns18;
	int x = 245;
	++x;	// local 'x' used
}

//! Example

namespace ns19 {
	int x, y, z;
	void func19();
}

using namespace ns19;	// put below 'int a = x;' , inside func19() to see the change
int a = x;

void func19()
{
	x = 5;

}

void bar19()
{
	y = 3;
}

void baz19()
{
	z = 1;
}


//! Example

using namespace std;	// not good idea to put in global namespace

int main()
{

}

//! Example
// 
namespace ns20 {
	int x;
	void foo(int);
}

namespace ns21 {
	int x;
	void foo(double);

}

using namespace ns20;
using namespace ns21;

int main()
{
	x = 5;		// ambiguity
	foo(5);		// void foo(int)		called
	foo(2.4);	// void foo(double)	called
}

//! Example

namespace ns22 {
	int x;
}

using namespace ns22;
int x = 5;

int main()
{
	::x = 5;	// legal
	x = 5;	// synax error
}



//! ADL
namespace ns23 {
	class MyClass {};
	void func(MyClass)
	{
		std::cout << "nec::func(MyClass)\n";
	}
	void func23(int);
}

int main()
{
	ns23::MyClass m;
	func(m);	// How?
	func23(12);	// syntax error
}
// Eðer fonksiyona gönderilen argümanlardan biri
//		bir namespace'de bildirilen bir türe iliþkin ise
//			
/*
Output:
	nec::func(MyClass)
*/

//! Example
namespace nec {
	class MyClass {};
	void func(std::vector<MyClass>)
	{

	}
}

int main()
{
	std::vector<nec::MyClass> vec;
	func(vec);	// legal
}

//! Example
namespace ns24 {
	class MyClass {};

	void func24(ns24::MyClass);

}
void func24(ns24::MyClass);	// different functions

int main()
{
	ns24::MyClass mx;
	func24(mx);			// syntax error
	// ambiguity
	// found using argument-dependent lookup
}

//! argument-dependent lookup
//! Example on argument-dependent lookup
int main()
{
	std::cout << "aaa bbb";		// oparator << : argument-dependent lookup

	operator<<(std::cout, "aaa bbb");
}


//! Example on argument-dependent lookup

int main()
{
	std::vector{ 1,2,3,8,5,4,7 };
	std::sort(std::begin(vec), std::end(vec));

	sort(begin(vec), end(vec));

	std::vector <int>::iterator iter1 = begin(vec);
	std::vector <int>::iterator iter2 = end(vec);
	sort(iter1, iter2);

}

//! Example

int main()
{
	// here, endl is the argument of the function called of ostream class
	std::cout << endl;	// identifier 'endl' is undefined
	std::cout.operator<<(endl);


	endl(std::cout);
	// std::endl is ostream manipular
}


//! Example

std::ostream& mendl(std::ostream& os)
{
	os.put('\n');
	os.flush();

	return os;
}

// these two are very different
// cout << endl;
// cout << '\n';

//! Example
//! 
class Ostream {
public:
	Ostream& operator<<(int);
	Ostream& operator<<(double);
	Ostream& operator<<(long);
	Ostream& operator<<(Ostream& (*fp)(Ostream&))		// parameter is a function pointer
	{
		return fp(*this);
	}
};

Ostream& mendl(Ostream& os)
{
	//
	return os;
}

int main()
{
	std::cout << 1;
	std::cout.operator<<(1L);

	Ostream mycout;
	mycout << mendl;	// because mendl is a function name, thus Ostream& operator<<(Ostream& (*)(Ostream&)); is called
	mycout.operator<<(mendl);
	mendl(mycout);
}

//! Example

std::ostream& mendl(std::ostream& os)
{
	os.put('\n');
	os.flush();
	return os;
}

int main()
{
	using namespace std;

	cout << 12 << mendl << 2.3 << mendl << 56L;		// flush function is also called, instead of just going to a new line
	cout << 12 << endl << 2.3 << endl << 56L;		// const of flush function is high
}

//! Example

std::ostream& ps(std::ostream& os)
{
	return os << '\n******************************\n';
}

int main()
{
	using namespace std;

	cout << 12 << ps << 2.3 << ps << 34L << ps;
}

//

int main()
{
	// these two very different from each other
	std::cout << endl;		// endl is not a called function, it is a parameter
	endl(std::cout);		// end is called function
}

//! Example

class exClass1 {
	friend void foo(exClass1);
};

int main()
{
	exClass1 m;
	foo(m);
}

//! Examples on screenshots
// add example from sc
// add example from sc
// add example from sc

// 
//! Example
static int x; // internal linkage, only this file can use 'x'
static int foo(int);

//! Un-named namespace
// internal linkage
namespace {
	int x;
	int foo(int);
}

namespace {
	int y;
	int bar(int);
}

int main()
{
	x = 6;
	y = 5;
	//
}

//! Example
// ex.cpp
namespace {
	class MyClass {

	};
}

//! Namespace Alias

namespace nec_erg_project {
	//
	int x;
}

int main()
{
	namespace nec = nec_erg_project;
	nec::x;
	nec_erg_project::x;
}


//! Example

namespace chron = std::chrono;

int main()
{
	chron::duration;
}

//! Example

namespace nec {
	namespace erg {
		namespace proj {
			void foo();
		}
	}
}

namespace proj = nec::erg::proj;

int main()
{
	nec::erg::proj::foo();
	proj::foo();
}

//! Inline Namespace

namespace ns25 {
	namespace ns26 {
		int x;
	}
}

int main()
{
	ns25::x;		// synatx error
	ns25::ns26::x;
}

//! Example 

namespace ns27 {
	inline namespace ns28 {
		int x;
	}
}

int main()
{
	ns27::x;	// now, legal

}

//! Example 

namespace ns29 {
	inline namespace ns30 {
		int x;
	}

	inline namespace ns31 {
		int x;
	}
}

int main()
{
ns29:x;	// ambiguity
}

//! Example 

namespace ns32 {
	inline namespace ns33 {
		class MyClass {};
	}

	namespace ns34 {
		class MyClass {};
	}
}

int main()
{
	ns32::MyClass m1;	// uses MyClass on ns3 namespace
}



//! Example 

inline namespace A {
	inline namespace B {
		inline namespace C {
			int x;
		}
	}
}

int main()
{
	// all legal
	A::B::C::x = 4;
	A::B::x = 5;
	A::x = 1;
	x = 7;
}

//! Example

// added on C++20
namespace A::B:: inline C {
	int x;
}

int main()
{
	A::B::x;	// legal
}

//! Example

namespace E {
	namespace F {
		class MyClass {};
	}

	using namespace F;
}

namespace E {
	inline namespace F {
		class MyClass {};
	}
}

//

//! Nested Types

// Type Members
// Member Types

struct Data {
	struct Nested {
		// in C, Nested has the scope of the enclosing scope
	};
};

//! Example
struct exStruct {
	typedef int Mint;
	using fptr = int(*)(int);
	enum Color { white, black };
	enum class Pos { on, off, hold };

	class Eni {

	};
};

int main()
{
	exStruct::Mint a;
	exStruct::fptr b;
	exStruct::Color c = exStruct::white;
	exStruct::Pos d = exStruct::Pos::off;
}

//! Example

class Enc {
public:
	class Nested {
		//friend class Enc;
		void foo();
	};
	void bar()
	{
		Nested x;
		x.foo();	// inaccessible because foo() is private
	}
};

int main()
{

}

//! Example

class Encl {
	class Nested {};
public:
	static Nested foo();
};

int main()
{
	//Encl::Nested x = Encl::foo();		// inaccessible
	auto x = Enc::foo();	// ???
}


//! Example

class Encl {
	void foo();
	class MyClass {

	};
	static void bar();

	class Nested {
	public:
		void func()
		{
			Encl::MyClass m;
			Encl e;			// can access the private part of the enclosing type 
			e.foo();
			Encl::bar();
		}
	};
};

//! Example
//! 
class Enc {
	using Mint = int;
	Mint foo();
};

class Enc {
	Mint foo();	// syntax error
	using Mint = int;
};

//! Exmaple

class Encl {
	void foo()
	{
		Mint x;	 // legal
	}

	using Mint = int;
};

//! Example

// ex.h
class A {
	class B {
		B();
		void foo(int);
	};

	// we cant define foo(int) here
	void B::foo(int) {

	}
};

// ex.cpp

void A::B::foo(int)
{

}

A::B::B()
{

}

//! Example

class MyClass2 {
public:
	class Nested {

	};
	void foo(Nested);
};

void MyClass2::foo(Nested x)	// void MyClass2::foo(MyClass2::Nested x)
{								// {
	Nested x;					// MyClass2::Nested x;
}								// }


//! Example

class MyClass3 {
public:
	class Nested {

	};
	Nested foo(Nested);
};

Nested MyClass3::foo(Nested)	// syntax error, should be MyClass3::Nested
{

}

// what if :

using Nested = int;
Nested MyClass3::foo(Nested)	// declaration is incompatible
{

}

//! Example
class MyClass4 {
	class Nested;
};

class MyClass4::Nested {

};
