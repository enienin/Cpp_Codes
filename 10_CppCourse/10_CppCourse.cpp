#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<vector>
#include<string>
#include<cstdlib>
#include<cstring>
/*! SPECIAL MEMBER FUNCTIONS */


//! COPY CONSTRUCTOR
// A class object comes to life by taking its value from another class object of the same type.

//! Scenario 1
/*
class Nec
{
public:
	Nec(const Nec& other)     // const lvalue reference, Nec& reference to x, 'other' is to y.
	{

	}
};
*/
// Nec y;
// Nec x = y;   copy constructor gets called for this


//! Scenario 2
// Nec x2(y);   these two come to life through copy constructor
// Nec x3{y};


//! Scenario 3
// auto x = y;  same thing, copy constructor
// auto x2(y);   
// auto x3{y};


//! Scenario 4
class ex_class1
{
	// ...
};

void foo(ex_class1 x)   // the parameter is of type 'ex_class1' , copy constructor will be called 
{
	//...
}

int main()
{
	ex_class1 ex;
	foo(ex);
}


//! Scenario 5
class ex_class2
{
	// ...
};

ex_class2 bar()   // the parameter is of type 'ex_class1' , copy constructor will be called 
{
	//..
	return ex;
}

int main()
{
	ex_class2 myclass = bar();  // copy constructor will be called 

}

// Code of Copy ctor can be written by the compiler, because it is a special member function.

//! Example
class ex_class3 {
public:
	ex_class3()
	{
		std::cout << "ex_class3 default ctor this : " << this << '\n';
	}

	~ex_class3()
	{
		std::cout << "ex_class3 dtor this : " << this << '\n';
	}
};

int main()
{
	ex_class3 ex;
}
/*
Output:
ex_class3 default ctor this : 000000B6E7B9FB24
ex_class3 dtor this : 000000B6E7B9FB24          (address of ctor and dtor is the same)
*/

//! Example
class ex_class4 {
public:
	ex_class4()
	{
		std::cout << "ex_class4 default ctor this : " << this << '\n';
	}

	~ex_class4()
	{
		std::cout << "ex_class4 dtor this : " << this << '\n';
	}
};

int main()
{
	ex_class4 ex;

	{
		ex_class4 ey = ex;
	}   // destructor for 'ey' is called 

	std::cout << "Main continues..." << '\n';
	(void)getchar();
}       // destructor for 'ex' is called 
/*
Output:
ex_class4 default ctor this : 0000007EA76FFC34  ( default ctor called for 'ex')
ex_class4 dtor this : 0000007EA76FFC54          ( notice how the address of ctor and dtor is different)
Main continues...

ex_class4 dtor this : 0000007EA76FFC34          ( dtor called for 'ex')
*/


//! Example
class ex_class5 {
public:
	ex_class5()
	{
		std::cout << "ex_class5 default ctor this : " << this << '\n';
	}

	ex_class5(const ex_class5& other)
	{
		std::cout << "ex_class5 copy ctor this : " << this << '\n';
	}

	~ex_class5()
	{
		std::cout << "ex_class5 dtor this : " << this << '\n';
	}
};

int main()
{
	ex_class5 ex;

	{
		ex_class5 ey = ex;
	}

	std::cout << "Main continues..." << '\n';
	(void)getchar();
}
/*
Output:
ex_class5 default ctor this : 000000678F8FFC94
ex_class5 copy ctor this : 000000678F8FFCB4
ex_class5 dtor this : 000000678F8FFCB4
Main continues...
ex_class5 dtor this : 000000678F8FFC94
*/


//! Example
class ex_class6 {
public:
	ex_class6()
	{
		std::cout << "ex_class6 default ctor this : " << this << '\n';
	}

	ex_class6(const ex_class6& other)
	{
		std::cout << "ex_class6 copy ctor this : " << this << '\n';
	}

	~ex_class6()
	{
		std::cout << "ex_class6 dtor this : " << this << '\n';
	}
};

int main()
{
	ex_class6 ex;
	std::cout << "ex = " << &ex << '\n';

	{
		ex_class6 ey = ex;
		std::cout << "ey = " << &ey << '\n';
	}

	std::cout << "Main continues..." << '\n';
	(void)getchar();
}
/*
Output:
ex_class6 default ctor this : 000000757AD2F734
ex = 000000757AD2F734
ex_class6 copy ctor this : 000000757AD2F754
ey = 000000757AD2F754
ex_class6 dtor this : 000000757AD2F754
Main continues...

ex_class6 dtor this : 000000757AD2F734
*/


//! Example
class ex_class7 {
public:
	ex_class7()
	{
		std::cout << "ex_class7 default ctor this : " << this << '\n';
	}

	ex_class7(const ex_class7& other)
	{
		std::cout << "ex_class7 copy ctor this : " << this << '\n';
		std::cout << "&other = " << &other << '\n';
	}

	~ex_class7()
	{
		std::cout << "ex_class7 dtor this : " << this << '\n';
	}
};

int main()
{
	ex_class7 ex;
	std::cout << "ex = " << &ex << '\n';

	{
		ex_class7 ey = ex;
		std::cout << "ey = " << &ey << '\n';
	}

	std::cout << "Main continues..." << '\n';
	(void)getchar();
}
/*
Output:
ex_class7 default ctor this : 00000020182FF784
ex = 00000020182FF784
ex_class7 copy ctor this : 00000020182FF7A4
&other = 00000020182FF784
ey = 00000020182FF7A4
ex_class7 dtor this : 00000020182FF7A4
Main continues...

ex_class7 dtor this : 00000020182FF784
*/

/////////////////////////////////////

/*
class MyClass {
public:
	MyClass() : tx(), ux(), wx() {}

private:
	T tx;
	U ux;
	W wx;
};

The default copy ctor that the compiler writes is a public, non-static, inline member function.
*/

//! If a situation that violates the rules of the language (syntax error) occurs 
//!		when the compiler attempts to implicitly declare 
//!			and define a special member function of a class, 
//!				the compiler will declare the default special member function as deleted.

// What syntax error can occur?
//		- elements cannot be default initialized
//		- one of the elements is const or reference
//		- one of the elements is initialized as default and there is no default constructor
//		- the default constructor of one of the elements is private
//		- the default constructor of one of the elements was deleted

//! Example 1

// there is no syntax error in this code
// default constructor is deleted
//! implicitly declared deleted
class ex_class8 {

	const int x;
};

// there will be syntax error when this deleted function is called
// In C++, a constant member variable must be initialized when it is declared, or through a constructor initializer list.
int main() {
	ex_class8 ex;	// the default ctor of "ex_class8" cannot be referenced - it is a deleted function
}


//! Example 2

// default constructor is deleted
//! implicitly declared deleted
class ex_class9 {

	int& r;
};

// there will be syntax error when this deleted function is called

// Similar to const members, reference members must be initialized when an object is created. 
// This requirement exists because references in C++ must refer to an object,
// they cannot be null and they cannot be re-assigned to refer to a different object after initialization.
int main() {
	ex_class9 ex;	// the default ctor of "ex_class9" cannot be referenced - it is a deleted function
}


//! Example 3

/*
The error in the provided code stems from the inability to implicitly instantiate the ex_class10 member mc within ex_class11
due to the lack of a default constructor in ex_class10.
The ex_class10 class only defines a constructor that takes an int parameter,
and since C++ requires an object to be initialized upon creation,
the compiler looks for a default constructor when attempting to instantiate mc within ex_class11.
Since no such constructor exists for ex_class10,
and ex_class11 does not explicitly initialize mc in its initialization list, the compiler will generate an error.

*/
class ex_class10 {
public:
	ex_class10(int);	// ex_class10::ex_class10(void) function definition not found
	// no default constructor
};

class ex_class11 {

	ex_class10 mc;
};

int main()
{
	ex_class11 m;	// the default constructor of "ex_class11" cannot be referenced -- it is a deleted function
}



//! Example 4
// okay
class ex_class12 {
public:
	ex_class12();
};

class ex_class13 {

	ex_class12 mc;
};

int main()
{
	ex_class13 m;
}


//! Example 5
// syntax error, because the default constructor of "ex_class14" is private
class ex_class14 {
	ex_class14();
};

class ex_class15 {

	ex_class14 mc;
};

int main()
{
	ex_class15 m;	// the default constructor of "ex_class15" cannot be referenced -- it is a deleted function
}


//! Example 6

class ex_class16 {
public:
	ex_class16() = delete;
};

class ex_class17 {

	ex_class16 mc;
};

int main()
{
	ex_class17 m;	// the default constructor of "ex_class17" cannot be referenced -- it is a deleted function
}

//////
//! IMPORTANT RULE
//! If you declare any constructor to the class, the compiler does not declare a default constructor.
class ex_class18 {
public:
	ex_class18(int);
};

//

class A {
public:
	A(int);		// doesn't have default constructor, default constructor not declared
};

//

class B {
public:
	B(const B&);	// copy constructor
	//! this class has no default ctor, it is NOT implicitly declared
};

// 

//! Is there a difference between writing "C() = default;" and not declaring the ctor at all ?
// Yes, there is. Not, on the code written by the compiler, but on the status of ctor.
class C {
public:
	C() = default;	// ctor is user declared 
};

class D {
public:
	// ctor is implicitly declared
};

//! Example

class ex_class18 {
public:
	ex_class18();	// also, user declared ctor and the definition should be written by us
};

int main()
{
	ex_class18 ex;	//! linkage error
	// function definition for "ex_class18" not found.
}


//! Example
class ex_class19 {
public:
	ex_class19() = default;	 // okay, user declared defaulted
};

int main()
{
	ex_class19 ex;
}


//! Example
class ex_class20 {
public:
	ex_class20() {};	 // okay, user declared defined 
};

int main()
{
	ex_class20 ex;
}

//! Example
class ex_class21 {
public:
	ex_class21() = delete;	// user declared deleted
};

int main()
{
	ex_class21 ex;	// compile time error
}

//
// back to copy ctor

//! How the compiler writes copy ctor?
//			
/*
class ex_class22 {
public:
	ex_class22(const ex_class22& other) : tx(other.tx), ux(other.ux), wx(other.wx) {}
private:
	T tx;
	U ux;
	W wx;
};
*/

//

//! Rule of Zero
// If a class does not manage resources directly
// (i.e., it does not perform custom actions in its destructor, 
// copy constructor, move constructor, copy assignment operator, 
// or move assignment operator), 
// it should not explicitly define these special member functions.

class Student {
private:
	std::string name;
	std::vector<int> grades;
};
// compiler writes the ctor
// compiler default initializes name and grades as empty str and empty vector

//

//! Value Type
// Every object has its own value.

// T x = y;		there is no connection between 'x' and 'y' after initialization (if T is value type)
// later if i change 'x' , 'y' won't change and vice versa

// std::str		value type
// std::vector	value type
// int			value type


//! Example
class ex_class23 {
public:
	ex_class23(int day, int mon, int year) : day_(day), month_(mon), year_(year) {}
	//
	void print()const
	{
		std::cout << day_ << '-' << month_ << '-' << year_ << '\n';
	}
private:
	int day_;
	int month_;
	int year_;
};

int main()
{
	ex_class23 dx{ 11,2,2024 };
	ex_class23 dy = dx;		// copy ctor is called for 'dy'
	dx.print();
	dy.print();
}

// it is not necessary to write the copy constructor ourselves
// there is nothing wrong with the copy ctor the compiler writes

/*
Output:
	11-2-2024
	11-2-2024
*/


//! Example
class ex_class24 {
public:
	ex_class24(int day, int mon, int year) : day_(day), month_(mon), year_(year) {}

	// copy ctor
	ex_class24(const ex_class24& other) : day_(other.day_), month_(other.month_), year_(other.year_) {};

	void print()const
	{
		std::cout << day_ << '-' << month_ << '-' << year_ << '\n';
	}
private:
	int day_;
	int month_;
	int year_;
};

int main()
{
	ex_class24 dx{ 11,2,2024 };
	ex_class24 dy = dx;		// copy ctor is called for 'dy'
	dx.print();
	dy.print();
}

//

// string

int main() {

	std::string str{ "necati ergin c++ egitimi veriyor" };

	std::string s2 = str;
}

// shallow copy  both the original and the copied object will point to the same memory locations for their pointer members.
// deep copy :  any dynamically allocated memory or resources held by the original object are also allocated a new and copied over for the new object.

//! Example

// compiler can write copy ctor 
class Person {
private:
	std::string name;
	std::string surname;
	std::string address;
};

// compiler shouldn't write copy ctor
/*
The compiler-generated versions simply copy the values of each member,
including pointer values. This means that after a copy,
both the original and the copied Person2 objects
will have pointers (pname, psurname, paddress) pointing to the same memory locations.
*/
class Person2 {

private:
	char* pname;
	char* psurname;
	char* paddress;
};

//! Example (where the programmer should write the copy ctor)
// cstring - NTBS (null terminated byte stream)
class Sentence {
public:
	Sentence(const char* p) : mlen(std::strlen(p)),
		mp(static_cast<char*>(std::malloc(mlen + 1)))
	{
		if (!mp) {
			std::cerr << "not enough memory\n";
			std::exit(EXIT_FAILURE);
		}
		std::strcpy(mp, p);
	}

	~Sentence()
	{
		if (mp)
			std::free(mp);
	}

	void print()const
	{
		std::cout << '[' << mp << ']' << '\n';
	}

	std::size_t length()const
	{
		return mlen;
	}

private:
	std::size_t mlen;	// length of sentence
	char* mp;	// will hold the address of the sentence
};

int main()
{
	Sentence s1{ "Today is 1st of February." };
	s1.print();
	auto len = s1.length();

	std::cout << "length = " << len << '\n';
	//...
}

/*
Output:
	[Today is 1st of February.]
	length = 25
*/

//! Example

class Sentence2 {
public:
	Sentence2(const char* p) : mlen(std::strlen(p)),
		mp(static_cast<char*>(std::malloc(mlen + 1)))
	{
		if (!mp) {
			std::cerr << "not enough memory\n";
			std::exit(EXIT_FAILURE);
		}
		std::strcpy(mp, p);
	}

	~Sentence2()
	{
		if (mp)
			std::free(mp);
	}

	void print()const
	{
		std::cout << '[' << mp << ']' << '\n';
	}

	std::size_t length()const
	{
		return mlen;
	}

private:
	std::size_t mlen;	// length of sentence
	char* mp;	// will hold the address of the sentence
};

void sfunc(Sentence2 s)		// shallow copy is performed from default copy ctor
{
	s.print();
	std::cout << "length = " << s.length() << '\n';
}	// at this point the destrctor has been called and memory has been freed so mp is a dangling pointer

int main()
{
	Sentence2 s{ "Today is 1st of February." };
	sfunc(s);
	(void)getchar();

	s.print();	// here we are trying to use a dangling pointer
}

//! Example
class Sentence3 {
public:
	Sentence3(const char* p) : mlen(std::strlen(p)),
		mp(static_cast<char*>(std::malloc(mlen + 1)))
	{
		if (!mp) {
			std::cerr << "not enough memory\n";
			std::exit(EXIT_FAILURE);
		}
		std::strcpy(mp, p);
	}

	~Sentence3()
	{
		if (mp)
			std::free(mp);
	}
	void reverse()
	{
		_strrev(mp);
	}

	void print()const
	{
		std::cout << '[' << mp << ']' << '\n';
	}

	std::size_t length()const
	{
		return mlen;
	}

private:
	std::size_t mlen;	// length of sentence
	char* mp;	// will hold the address of the sentence
};

int main()
{
	Sentence3 s{ "Today is 1st of February." };

	auto s2 = s;	// shallow copy
	(void)getchar();

	s.reverse();
	s.print();
	s2.print();

	(void)getchar();

}

/*
Output:
	[.yraurbeF fo ts1 si yadoT]
	[.yraurbeF fo ts1 si yadoT]
*/

//! What is the copy ctor the compiler writes in this case?

class Sentence3 {
public:
	Sentence3(const char* p) : mlen(std::strlen(p)),
		mp(static_cast<char*>(std::malloc(mlen + 1)))
	{
		if (!mp) {
			std::cerr << "not enough memory\n";
			std::exit(EXIT_FAILURE);
		}
		std::strcpy(mp, p);
	}

	// this is the copy ctor the compiler writes
	// Sentence3(const Sentence3& other) : mlen(other.mlen), mp(other.mp) {}

	// the correct copy ctor that should be written
	Sentence3(const Sentence3& other) : mlen(other.mlen),
		mp(static_cast<char*>(std::malloc(mlen + 1)))
	{
		//...
		std::strcpy(mp, other.mp);
	}


	~Sentence3()
	{
		if (mp)
			std::free(mp);
	}
	void reverse()
	{
		_strrev(mp);
	}

	void print()const
	{
		std::cout << '[' << mp << ']' << '\n';
	}

	std::size_t length()const
	{
		return mlen;
	}

private:
	std::size_t mlen;	// length of sentence
	char* mp;	// will hold the address of the sentence
};

int main()
{
	Sentence3 s{ "Today is 1st of February." };

	auto s2 = s;	// shallow copy
	(void)getchar();

	s.reverse();
	s.print();
	s2.print();

	(void)getchar();

}
/*
Output:
	[.yraurbeF fo ts1 si yadoT]
	[Today is 1st of February.]
*/


//! Example

class Sentence4 {
public:
	Sentence4(const char* p) : mlen(std::strlen(p)),
		mp(static_cast<char*>(std::malloc(mlen + 1)))
	{
		if (!mp) {
			std::cerr << "not enough memory\n";
			std::exit(EXIT_FAILURE);
		}
		std::strcpy(mp, p);
	}

	Sentence4(const Sentence4& other) : mlen(other.mlen),
		mp(static_cast<char*>(std::malloc(mlen + 1)))
	{
		//...
		std::strcpy(mp, other.mp);
	}


	~Sentence4()
	{
		if (mp)
			std::free(mp);
	}
	void reverse()
	{
		_strrev(mp);
	}

	void print()const
	{
		std::cout << '[' << mp << ']' << '\n';
	}

	std::size_t length()const
	{
		return mlen;
	}

private:
	std::size_t mlen;	// length of sentence
	char* mp;	// will hold the address of the sentence
};

int main()
{
	Sentence4 s{ "Today is 1st of February." };

	auto s2 = s;	// shallow copy
	(void)getchar();

	s.reverse();
	s.print();
	s2.print();

	(void)getchar();
}

//! Copy Assignment 

/*
	class Eni {

	};

	Eni x;
	Eni y;
	x = y;	this is not initialization, this is assignment

	x.operator = (y);
	to this, the compiler calls a special member function : copy assignment

*/

//! Example
using namespace std;

int main()
{
	string name1{ "pelin uzun" };
	string name2{ "mehmet aksu" };

	cout << "name1 = " << name1 << '\n';
	cout << "name2 = " << name2 << '\n';

	name2 = name1;	// copy assignment 
	//name2.operator= (name1);	// same as this
	cout << "name2 = " << name2 << '\n';

	name1 = "eni shkrepi";

	cout << "name2 = " << name2 << '\n';
}

/*
Output:
	name1 = pelin uzun
	name2 = mehmet aksu
	name2 = pelin uzun
	name2 = pelin uzun
*/

/*
class MyClass {
public:
	MyClass() : tx(), ux(), wx() {}
	MyClass(const MyClass& other) : tx(other.tx), ux(other.ux), wx(other.wx) {}
	MyClass& operator = (const MyClass& other)
	{
		tx = other.tx;
		ux = other.ux;
		wx = other.wx;

		return *this;
	}
private:
	T tx;
	U ux;
	W wx;
};

*/

//! Example
x = y = z = t;
x.operator=(y.operator=(z.operator=(t)));



//! Example
class Date {
public:
	Date(int day, int mon, int year) : day_(day), month_(mon), year_(year) {}

	// copy ctor
	Date(const Date& other) : day_(other.day_), month_(other.month_), year_(other.year_) {};

	void print()const
	{
		std::cout << day_ << '-' << month_ << '-' << year_ << '\n';
	}
private:
	int day_;
	int month_;
	int year_;
};

int main()
{
	Date dx{ 11,2,2024 };
	Date dy{ 1,1,1999 };

	dx.print();
	dy.print();

	dy = dx;	// compiler wrote copy assignment

	dy.print();
}

/*
Output:
	11-2-2024
	1-1-1999
	11-2-2024
*/


//! Example
class Date_ {
public:
	Date_(int day, int mon, int year) : day_(day), month_(mon), year_(year) {}

	// copy ctor
	Date_(const Date_& other) : day_(other.day_), month_(other.month_), year_(other.year_) {};

	void print()const
	{
		std::cout << day_ << '-' << month_ << '-' << year_ << '\n';
	}
private:
	int day_;
	int month_;
	int year_;
};

int main()
{
	Date_ dx{ 11,2,2024 };
	Date_ dy{ 1,1,1999 };

	(dy = dx).print();
	// an assignment operation can be chained with another operation 
	// due to the fact that the assignment operator returns a reference to the object. 

	// According to C++ rules, the assignment operator = returns a reference 
	// to the left-hand side object after the assignment. 
	// Thus, dy = dx returns a reference to dy, now holding the same date as dx.
}

/*
Output:
	11-2-2024
*/

//! Example
class Date_ {
public:
	Date_(int day, int mon, int year) : day_(day), month_(mon), year_(year) {}

	// copy ctor
	Date_(const Date_& other) : day_(other.day_), month_(other.month_), year_(other.year_) {};

	void print()const
	{
		std::cout << day_ << '-' << month_ << '-' << year_ << '\n';
	}
private:
	int day_;
	int month_;
	int year_;
};

int main()
{
	Date_ d1{ 11,2,2024 };
	Date_ d2{ 5,1,1999 };
	Date_ d3{ 7,1,1999 };
	Date_ d4{ 15,1,1999 };

	d4 = d3 = d2 = d1;

	d1.print();
	d2.print();
	d3.print();
	d4.print();
}

/*
Output:
	11-2-2024
	11-2-2024
	11-2-2024
	11-2-2024
*/


//! Example

class Sentence_ {
public:
	Sentence_(const char* p) : mlen(std::strlen(p)),
		mp(static_cast<char*>(std::malloc(mlen + 1)))
	{
		if (!mp) {
			std::cerr << "not enough memory\n";
			std::exit(EXIT_FAILURE);
		}
		std::strcpy(mp, p);
	}

	Sentence_(const Sentence_& other) : mlen(other.mlen),
		mp(static_cast<char*>(std::malloc(mlen + 1)))
	{
		//...
		std::strcpy(mp, other.mp);
	}


	~Sentence_()
	{
		if (mp)
			std::free(mp);
	}
	void reverse()
	{
		_strrev(mp);
	}

	void print()const
	{
		std::cout << '[' << mp << ']' << '\n';
	}

	std::size_t length()const
	{
		return mlen;
	}

private:
	std::size_t mlen;
	char* mp;
};

int main()
{
	Sentence_ s1{ "Eni Shkrepi C++ dersi dinliyor.\n" };
	s1.print();

	if (1)
	{
		Sentence_ s2{ "Necati Ergin anlatıyor.\n" };
		s2.print();

		s2 = s1;

		s2.print();
	}	// life of s2 finishes here, destructor called and memory freed

	(void)getchar();
	s1.print();		// dangling pointer
	// the copy assignment the compiler writes performs shallow copy
}

//! Let's fix this...
class Sentence_ {
public:
	Sentence_(const char* p) : mlen(std::strlen(p)),
		mp(static_cast<char*>(std::malloc(mlen + 1)))
	{
		if (!mp) {
			std::cerr << "not enough memory\n";
			std::exit(EXIT_FAILURE);
		}
		std::strcpy(mp, p);
	}

	Sentence_(const Sentence_& other) : mlen(other.mlen),
		mp(static_cast<char*>(std::malloc(mlen + 1)))
	{
		//...
		std::strcpy(mp, other.mp);
	}

	Sentence_& operator=(const Sentence_& other)
	{
		/*
		* The Copy Assignment the compiler writes:
		mlen = other.mlen;
		mp = other.mp;
		return *this;
		*/

		// firstly, free its own memory
		std::free(mp);

		// perform deep copy
		mlen = other.mlen;
		mp = static_cast<char*>(std::malloc(mlen + 1));
		if (!mp) {
			std::cerr << "not enough memory\n";
			std::exit(EXIT_FAILURE);
		}
		std::strcpy(mp, other.mp);

		return *this;

	}

	~Sentence_()
	{
		if (mp)
			std::free(mp);
	}
	void reverse()
	{
		_strrev(mp);
	}

	void print()const
	{
		std::cout << '[' << mp << ']' << '\n';
	}

	std::size_t length()const
	{
		return mlen;
	}

private:
	std::size_t mlen;
	char* mp;
};

int main()
{
	Sentence_ s1{ "Eni Shkrepi C++ dersi dinliyor." };
	s1.print();

	if (1)
	{
		Sentence_ s2{ "Necati Ergin anlatıyor." };
		s2.print();

		s2 = s1;

		s2.print();
	}	// life of s2 finishes here, destructor called and memory freed

	(void)getchar();
	s1.print();		// dangling pointer
}

/*
Output:
	[Eni Shkrepi C++ dersi dinliyor.]
	[Necati Ergin anlat²yor.]
	[Eni Shkrepi C++ dersi dinliyor.]

	[Eni Shkrepi C++ dersi dinliyor.]
*/


//! Another problem...

int main()
{
	int x = 67;

	// you don't do this in a healthy mental state
	x = x;	// legal
}

//! Example

class Sentence_ {
public:
	Sentence_(const char* p) : mlen(std::strlen(p)),
		mp(static_cast<char*>(std::malloc(mlen + 1)))
	{
		if (!mp) {
			std::cerr << "not enough memory\n";
			std::exit(EXIT_FAILURE);
		}
		std::strcpy(mp, p);
	}

	Sentence_(const Sentence_& other) : mlen(other.mlen),
		mp(static_cast<char*>(std::malloc(mlen + 1)))
	{
		//...
		std::strcpy(mp, other.mp);
	}

	Sentence_& operator=(const Sentence_& other)
	{
		/*
		* The Copy Assignment the compiler writes:
		mlen = other.mlen;
		mp = other.mp;
		return *this;
		*/

		// firstly, free its own memory
		std::free(mp);

		// perform deep copy
		mlen = other.mlen;
		mp = static_cast<char*>(std::malloc(mlen + 1));
		if (!mp) {
			std::cerr << "not enough memory\n";
			std::exit(EXIT_FAILURE);
		}
		std::strcpy(mp, other.mp);

		return *this;

	}

	~Sentence_()
	{
		if (mp)
			std::free(mp);
	}
	void reverse()
	{
		_strrev(mp);
	}

	void print()const
	{
		std::cout << '[' << mp << ']' << '\n';
	}

	std::size_t length()const
	{
		return mlen;
	}

private:
	std::size_t mlen;
	char* mp;
};

int main()
{
	Sentence_ s{ "The weather is sunny today!" };
	Sentence_* p1{ &s };
	auto p2 = &s;
	s.print();

	*p1 = *p2;	// self-assignment
	//same as : s = s;

	s.print();

}
/*
Output:
	[The weather is sunny today!]
	[════════════════════════════²²²²]
*/

// What happened, is that when i free the memory im using dangling pointer


//! Let's fix this...

class Sentence_ {
public:
	Sentence_(const char* p) : mlen(std::strlen(p)),
		mp(static_cast<char*>(std::malloc(mlen + 1)))
	{
		if (!mp) {
			std::cerr << "not enough memory\n";
			std::exit(EXIT_FAILURE);
		}
		std::strcpy(mp, p);
	}

	Sentence_(const Sentence_& other) : mlen(other.mlen),
		mp(static_cast<char*>(std::malloc(mlen + 1)))
	{
		//...
		std::strcpy(mp, other.mp);
	}

	Sentence_& operator=(const Sentence_& other)
	{
		if (this == &other)
			return *this;

		// firstly, free its own memory
		std::free(mp);

		// perform deep copy
		mlen = other.mlen;
		mp = static_cast<char*>(std::malloc(mlen + 1));
		if (!mp) {
			std::cerr << "not enough memory\n";
			std::exit(EXIT_FAILURE);
		}
		std::strcpy(mp, other.mp);

		return *this;

	}

	~Sentence_()
	{
		if (mp)
			std::free(mp);
	}
	void reverse()
	{
		_strrev(mp);
	}

	void print()const
	{
		std::cout << '[' << mp << ']' << '\n';
	}

	std::size_t length()const
	{
		return mlen;
	}

private:
	std::size_t mlen;
	char* mp;
};

int main()
{
	Sentence_ s{ "The weather is sunny today!" };
	Sentence_* p1{ &s };
	auto p2 = &s;
	s.print();

	*p1 = *p2;	// self-assignment

	s.print();

}
/*
Output:
	[The weather is sunny today!]
	[The weather is sunny today!]
*/

//

class MyClass {
public:
	MyClass(const MyClass&);
	MyClass(MyClass&& other);

	MyClass& operator = (const MyClass&); // if L value
	MyClass& operator = (MyClass&& r);	// if R value
};

//! Example

class Sentence_ {
public:
	Sentence_(const char* p) : mlen(std::strlen(p)),
		mp(static_cast<char*>(std::malloc(mlen + 1)))
	{
		if (!mp) {
			std::cerr << "not enough memory\n";
			std::exit(EXIT_FAILURE);
		}
		std::strcpy(mp, p);
	}

	// copy ctor
	Sentence_(const Sentence_& other) : mlen(other.mlen),
		mp(static_cast<char*>(std::malloc(mlen + 1)))
	{
		//...
		std::strcpy(mp, other.mp);
	}

	// move ctor
	Sentence_(Sentence_&& other) : mlen(other.mlen), mp(other.mp)
	{
		other.mp = nullptr;	// thus, the destructor won't free the memory
	}

	// copy assignment
	Sentence_& operator=(const Sentence_& other)
	{
		if (this == &other)
			return *this;

		// firstly, free its own memory
		std::free(mp);

		// perform deep copy
		mlen = other.mlen;
		mp = static_cast<char*>(std::malloc(mlen + 1));
		if (!mp) {
			std::cerr << "not enough memory\n";
			std::exit(EXIT_FAILURE);
		}
		std::strcpy(mp, other.mp);

		return *this;

	}

	// move assignment
	Sentence_& operator=(Sentence_&& other)
	{
		if (this == &other)
			return *this;

		std::free(mp);
		mlen = other.mlen;
		mp = other.mp;
		other.mlen = 0;
		other.mp = nullptr;

		return *this;

	}

	~Sentence_()
	{
		if (mp)
			std::free(mp);
	}
	void reverse()
	{
		_strrev(mp);
	}

	void print()const
	{
		std::cout << '[' << mp << ']' << '\n';
	}

	std::size_t length()const
	{
		return mlen;
	}

private:
	std::size_t mlen;
	char* mp;
};

int main()
{
	Sentence_ s{ "The weather is sunny today!" };
	Sentence_* p1{ &s };
	auto p2 = &s;
	s.print();

	*p1 = *p2;	// self-assignment

	s.print();

}


//  If a class has only copy ctor and copy assignment, then for move ctor, copy ctor will be called.
// and for move assignment, move ctor will be called.

//! Example

int main()
{
	string s1(400'000, 'A');
	//cout << s1.length() << "\n";		// Output: 400000
	string s2 = s1;	// copy ctor will be called for s2
	// but assume i won't use s1 in my code anymore so i want s2 to steal the resource of s1
	// i do that by having move ctor called
	// i should change the value category of s1

	// changed the value category
	string s2 = static_cast<string&&>(s1);
}

//! Move doesn't move. :D

// what that function move(exp) does :
// L value -> R value
// R value -> R value
// 

//! Example
void func(std::string&& s)
{
	//
}
int main()
{
	string s(400'000, 'A');

	func(move(s));	// kaynağı çalınmamış oluyor
}

//! Example
void func(std::string&& s)
{
	string s = s;			// copy ctor is called, L value expression
}
int main()
{
	string s(400'000, 'A');

	func(move(s));			// kaynağı çalınmamış oluyor
}

//! Example
void func(std::string&& s)
{
	string s = move(s);		// move ctor is called, because now is it an R value expression
}
int main()
{
	string s(400'000, 'A');

	func(move(s));			// kaynağı çalınmış oluyor
}


//! Example
void func(std::string&& s)
{
	string str;
	str = s;				// copy assignment called
}
int main()
{
	string s(400'000, 'A');

	func(move(s));			// kaynağı çalınmamış oluyor
}

//! Example
void func(std::string&& s)
{
	string str;
	str = move(s);				// move assignment called
}
int main()
{
	string s(400'000, 'A');

	func(move(s));			// kaynağı çalınmış oluyor
}