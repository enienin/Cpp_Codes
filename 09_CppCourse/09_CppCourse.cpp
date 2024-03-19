#include <iostream>
#include<string>
#include<cstdio>

//! Name Mangling
/*
C++ supports function overloading, i.e., there can be more than one function with the same name but,
different parameters. How does the C++ compiler distinguish between different functions when
it generates object code – it changes names by adding information about arguments.
This technique of adding additional information to function names is called Name Mangling.

*/


//! Linkage Error  in C++
//! Error	LNK2019	unresolved external symbol "int __cdecl foo(int)" (? foo@@YAHH@Z)
// The compiler can compile this code without errors because it sees the declaration 
// of foo(int) and assumes you will link the definition of foo(int) provided elsewhere. 
// However, during the linking phase, the linker cannot find a definition for foo(int), 
// resulting in a linkage error.

//! Example
int foo(int);

int main()
{
	int x = 6;
	auto y = foo(x);
	std::cout << "y = " << y << '/n';
}



//! How to solve this?

extern "C"
{
	int foo(int);		// asumme this function was defined in a .c file and compiled with c compiler
}

int main()
{
	int x = 6;
	auto y = foo(x);
	std::cout << "y = " << y << '/n';
}

//! Conditional Compiling

//! Example

#ifdef __cplusplus
int foo(int);
#endif

int main() {
	auto x = foo(3);
}

// eni.h (will be compiled in c)
// i want to use this functions in both .c and .cpp projects

#ifdef __cplusplus
extern "C" {
#endif

	int f1(int);
	int f2(int);
	int f3(int);
	int f4(int);
	int f5(int);

#ifdef __cplusplus
}
#endif

//! Function Deletion
// delete - keyword
// there is a function that returns int and takes one int parameter
// but calling this function causes syntax error

int foo(int) = delete;

int main()
{
	foo(3);		// error : attempting to reference a deleted function
}


//! Example

int foo2(int) = delete;
int foo2(unsigned);

int main()
{
	foo2(2.5);		// ambiguity
}



//! Example

int foo(float) = delete;
int foo(double) = delete;
int foo(long double) = delete;
int foo(int);

int main()
{
	foo(2.3);	// Error	C2280	'int foo(double)': attempting to reference a deleted function

}



//! Example

//int foo(float) = delete;
//int foo(double) = delete;
//int foo(long double) = delete;
int foo(int);

int main()
{
	foo(2.3);	// legal but there will be narrowing conversion
}



//! Example

class Nec {
public:
	void func(int) = delete;
	void func(double);
};

int main()
{
	Nec mynec;
	mynec.func(23.45);	// valid
	mynec.func(23);		// invalid
}


///////////////////////////////////////////////////////////////////////////////

//! Constructors & Destructors

//! Constructor
 /*The Constructor is a non-static member function.
 The Constructor of a class must have the same name as the class.
 The Constructor is a function that has no 'concept' of return value.
 The Constructor cannot be a free function (global function).
 The Constructor cannot be a static member function or const member function.
 'this' can be used in its definition.
 Can be public, private, protected.
 Constructor can be overloaded.
 cannot be called using . or -> operators*/

class Fighter {

private:
	std::string m_name;	// Constructors initialize the non-static member variables of a class
	int m_age;
	int m_power;
	//
};

//! Example

class Eni {
public:
	Eni(int);
	//void Eni(int);		syntax error

	Eni(int)
	{
		this
	}
};

//! Example

class Eni2 {
private:
	Eni2(int);
};

int main() {
	Eni2 myeni(4);	// cannot access private member declared in class Eni2
}

//! Example

class ex_class_1 {
private:
	ex_class_1(int);

	void func()
	{
		ex_class_1 ex_class(12);	// valid
	}
};

//! Example
// The constructor has 5 overloads.
class ex_class_2 {
private:
	ex_class_2();
	ex_class_2(int);
	ex_class_2(double);
	ex_class_2(int, int);
	ex_class_2(int, int, int);
};

//! Default Constructor
// A class that has no parameter variable
//		or
// that takes all parameters as default arguments.
// Can be called without sending a argument.

//! Examples of Default Constructor

class ex_class_3 {
private:
	ex_class_3();	// defalt constructor
};

class ex_class_4 {
private:
	ex_class_4(int x);	// not a defalt constructor
};

class ex_class_5 {
private:
	ex_class_5(int x = 10);	// defalt constructor
};




//! Example

// if i include this header in 10 files, ODR is not violated
// necati.h
class ex_class_6 {
private:
	void func(int x)
	{
		//
	}
};




//! Example

// if i include this header in 2 files, ODR is violated
// necati.h
class ex_class_7 {
private:
	void func(int x);
};

void ex_class_7::func(int)
{
	//
}




//! Example

// if i include this header in 2 files, ODR is not violated
// necati.h
class ex_class_8 {
private:
	inline void func(int x);
};


void ex_class_8::func(int)	// or inline void ex_class_8::func(int)
{
	//
}


//! Example

// necati.h
class ex_class_9 {
private:
	ex_class_9(int);		// constructor declaration
};

// necati.cpp
// #include <necati.h>
ex_class_9::ex_class_9(int x)		// constructor definition
{
	//..
}


//! Special Member Functions
//		- default ctor
//		- destructor
//		- copy ctor
//		- move ctor			C++11
//		- copy assignment
//		- move assignment		C++11

// The codes of these functions (when certain conditions are met) can be written by the compiler.


//! Destructor
 //Used to end the life of the object of a class.
 //The Destructor is a non-static member function.
 //The Destructor of a class must have the same name as the class but ~ is put in front of the function.
 //The Destructor is a function that has no 'concept' of return value.
 //The Destructor cannot be a free function (global function).
 //The Destructor cannot be a static member function or const member function.
 //'this' can be used in its definition.
 //Can be public, private, protected.
 //Destructor CANNOT be overloaded.
 //Destructor must have a 'void' parameter list
 //can be called using . or -> operators


//! Example
class ex_class_10 {
private:
	ex_class_10(int x);
	~ex_class_10();		// destructor
};

//! Example
class ex_class_11 {
private:
	ex_class_11(int x) = delete;	// ok
	~ex_class_11() = delete;		// ok
};


//! Example
class ex_class_12 {
public:
	ex_class_12();
	ex_class_12(int x);
	void foo();
};

int main()
{
	ex_class_12 myclass;
	myclass.foo();	// ok
	myclass.ex_class_12(12);	// error, cannot call ctor with . operator
	myclass.~ex_class_12();		// ok, can call dtor with . operator but it is not very common 
}

//! Storage Classes
//		static storage class
//		automatic storage class
//		dynamic storage class
//		thread-local storage class

/*  The following classes have static life-span:
		- global variables
		- static local variables
		- static data members of a class
		*/

		//! Example

class ex_class_13 {
public:
	ex_class_13()
	{
		std::cout << "ex_class_13() this = " << this << '\n';
	}

	~ex_class_13()
	{
		std::cout << "ex_class_13 destructor this = " << this << '\n';
	}
};

ex_class_13 gex_class;

int main()
{
	std::cout << "main starting\n";
	std::cout << "&gex_class = " << &gex_class << "\n";
	std::cout << "main continuing\n";
	std::cout << "main ending\n";
}

/*
Output:
ex_class_13() this = 00007FF6267A1180
main starting
&gex_class = 00007FF6267A1180
main continuing
main ending
ex_class_13 destructor this = 00007FF6267A1180
*/




//! Example

class ex_class_14 {
public:
	ex_class_14()
	{
		std::cout << "ex_class_14() this = " << this << '\n';
	}

	~ex_class_14()
	{
		std::cout << "ex_class_14 destructor this = " << this << '\n';
	}
	void foo()
	{

	}

	void bar()
	{

	}

	int main()
	{
		std::cout << &ex_class_14::foo << '\n';		// these functions also have an address
		std::cout << &ex_class_14::bar << '\n';
	}
}



//! Example
/*
When a class has multiple constructors, the specific constructor called during object creation
depends on the arguments provided when the object is instantiated.
*/

class ex_class_15 {
public:
	ex_class_15()
	{
		std::cout << "ex_class_15() this = " << this << '\n';
	}

	ex_class_15(int)
	{
		std::cout << "ex_class_15(int) this = " << this << '\n';
	}

	~ex_class_15()
	{
		std::cout << "ex_class_15 destructor this = " << this << '\n';
	}
};

ex_class_15 gex_class;

int main()
{
	std::cout << "main starting\n";
	std::cout << "&gex_class = " << &gex_class << "\n";
	std::cout << "main continuing\n";
	std::cout << "main ending\n";
}

/*
Output:
ex_class_15() this = 00007FF792701200
main starting
&gex_class = 00007FF792701200
main continuing
main ending
ex_class_15 destructor this = 00007FF792701200
*/



//! Example

class ex_class_16 {
public:
	ex_class_16()
	{
		std::cout << "ex_class_16() this = " << this << '\n';
	}

	ex_class_16(int)
	{
		std::cout << "ex_class_16(int) this = " << this << '\n';
	}

	~ex_class_16()
	{
		std::cout << "ex_class_16 destructor this = " << this << '\n';
	}
};

ex_class_16 gex_class(5);

int main()
{
	std::cout << "main starting\n";
	std::cout << "&gex_class = " << &gex_class << "\n";
	std::cout << "main continuing\n";
	std::cout << "main ending\n";
}

/*
Output:
ex_class_16(int) this = 00007FF6BFC11200
main starting
&gex_class = 00007FF6BFC11200
main continuing
main ending
ex_class_16 destructor this = 00007FF6BFC11200

*/


//! Example

class ex_class_17 {
public:
	ex_class_17()
	{
		std::cout << "ex_class_17() this = " << this << '\n';
	}

	~ex_class_17()
	{
		std::cout << "ex_class_17 destructor this = " << this << '\n';
	}
};

void foo()
{
	static ex_class_17 x;

}

int main()
{
	std::cout << "main starting\n";
	foo();
	std::cout << "main ending\n";
}

/*
Output:
	main starting
	ex_class_17() this = 00007FF7746D0200
	main ending
	ex_class_17 destructor this = 00007FF7746D0200
*/


//! Example

class ex_class_18 {
public:
	ex_class_18()
	{
		std::cout << "ex_class_18() this = " << this << '\n';
	}

	~ex_class_18()
	{
		std::cout << "ex_class_18 destructor this = " << this << '\n';
	}
};

void foo()
{
	std::cout << "foo called\n";
	static ex_class_18 x;
}

int main()
{
	std::cout << "main starting\n";
	foo();		// constructor is called only once
	foo();
	foo();
	foo();
	foo();
	std::cout << "main ending\n";
}

/*
Output:
	main starting
	foo called
	ex_class_18() this = 00007FF65B530200
	foo called
	foo called
	foo called
	foo called
	main ending
	ex_class_18 destructor this = 00007FF65B530200
*/



//! Example

class ex_class_19 {
public:
	ex_class_19()
	{
		std::cout << "ex_class_19() this = " << this << '\n';
	}

	~ex_class_19()
	{
		std::cout << "ex_class_19 destructor this = " << this << '\n';
	}
	char buf[256]{};
};

ex_class_19 ar[16];

int main()
{
	std::cout << "main starting\n";
	std::cout << "main ending\n";
}

/*
Output:
	ex_class_19() this = 00007FF6660C1200
	ex_class_19() this = 00007FF6660C1300
	ex_class_19() this = 00007FF6660C1400
	ex_class_19() this = 00007FF6660C1500
	ex_class_19() this = 00007FF6660C1600
	ex_class_19() this = 00007FF6660C1700
	ex_class_19() this = 00007FF6660C1800
	ex_class_19() this = 00007FF6660C1900
	ex_class_19() this = 00007FF6660C1A00
	ex_class_19() this = 00007FF6660C1B00
	ex_class_19() this = 00007FF6660C1C00
	ex_class_19() this = 00007FF6660C1D00
	ex_class_19() this = 00007FF6660C1E00
	ex_class_19() this = 00007FF6660C1F00
	ex_class_19() this = 00007FF6660C2000
	ex_class_19() this = 00007FF6660C2100
	main starting
	main ending
	ex_class_19 destructor this = 00007FF6660C2100
	ex_class_19 destructor this = 00007FF6660C2000
	ex_class_19 destructor this = 00007FF6660C1F00
	ex_class_19 destructor this = 00007FF6660C1E00
	ex_class_19 destructor this = 00007FF6660C1D00
	ex_class_19 destructor this = 00007FF6660C1C00
	ex_class_19 destructor this = 00007FF6660C1B00
	ex_class_19 destructor this = 00007FF6660C1A00
	ex_class_19 destructor this = 00007FF6660C1900
	ex_class_19 destructor this = 00007FF6660C1800
	ex_class_19 destructor this = 00007FF6660C1700
	ex_class_19 destructor this = 00007FF6660C1600
	ex_class_19 destructor this = 00007FF6660C1500
	ex_class_19 destructor this = 00007FF6660C1400
	ex_class_19 destructor this = 00007FF6660C1300
	ex_class_19 destructor this = 00007FF6660C1200
*/


//! Automatic storage class

//! Example

class ex_class_20 {
public:
	ex_class_20()
	{
		std::cout << "ex_class_20() this = " << this << '\n';
	}

	~ex_class_20()
	{
		std::cout << "ex_class_20 destructor this = " << this << '\n';
	}
	char buf[256]{};
};

void foo()
{
	ex_class_20 x;
}		// because x  is automatic storage class, the life of the object ends here so destructor is called

int main()
{
	std::cout << "main starting\n";
	foo();
	std::cout << "main ending\n";
}

/*
Output:
	main starting
	ex_class_20() this = 0000001DC90FF6B0
	ex_class_20 destructor this = 0000001DC90FF6B0
	main ending
*/





//! Example

class ex_class_21 {
public:
	ex_class_21()
	{
		std::cout << "ex_class_21() this = " << this << '\n';
	}

	~ex_class_21()
	{
		std::cout << "ex_class_21 destructor this = " << this << '\n';
	}
	char buf[256]{};
};

void foo()
{
	ex_class_21 x;
}		// because x  is automatic storage class, the life of the object ends here so destructor is called

int main()
{
	std::cout << "main starting\n";
	foo();
	foo();
	foo();
	std::cout << "main ending\n";
}

/*
Output:
	main starting
	ex_class_21() this = 000000B26155F6A0
	ex_class_21 destructor this = 000000B26155F6A0
	ex_class_21() this = 000000B26155F6A0
	ex_class_21 destructor this = 000000B26155F6A0
	ex_class_21() this = 000000B26155F6A0
	ex_class_21 destructor this = 000000B26155F6A0
	main ending
*/




//! Example

class ex_class_22 {
public:
	ex_class_22()
	{
		std::cout << "ex_class_22() this = " << this << '\n';
	}

	~ex_class_22()
	{
		std::cout << "ex_class_22 destructor this = " << this << '\n';
	}
};

int main()
{
	std::cout << "main starting\n";
	for (int i = 0; i < 10; ++i)
	{
		ex_class_22 myclass;	// ctor and dtor will be called 10 times
	}
	std::cout << "main ending\n";
}

/*
Output:
	main starting
	ex_class_22() this = 000000F1045BF934
	ex_class_22 destructor this = 000000F1045BF934
	ex_class_22() this = 000000F1045BF934
	ex_class_22 destructor this = 000000F1045BF934
	ex_class_22() this = 000000F1045BF934
	ex_class_22 destructor this = 000000F1045BF934
	ex_class_22() this = 000000F1045BF934
	ex_class_22 destructor this = 000000F1045BF934
	ex_class_22() this = 000000F1045BF934
	ex_class_22 destructor this = 000000F1045BF934
	ex_class_22() this = 000000F1045BF934
	ex_class_22 destructor this = 000000F1045BF934
	ex_class_22() this = 000000F1045BF934
	ex_class_22 destructor this = 000000F1045BF934
	ex_class_22() this = 000000F1045BF934
	ex_class_22 destructor this = 000000F1045BF934
	ex_class_22() this = 000000F1045BF934
	ex_class_22 destructor this = 000000F1045BF934
	ex_class_22() this = 000000F1045BF934
	ex_class_22 destructor this = 000000F1045BF934
	main ending
*/




//! Example

class ex_class_23 {
public:
	ex_class_23()
	{
		std::cout << "ex_class_23() this = " << this << '\n';
	}

	~ex_class_23()
	{
		std::cout << "ex_class_23 destructor this = " << this << '\n';
	}
};

int main()
{
	std::cout << "main starting\n";
	for (int i = 0; i < 10; ++i)
	{
		std::cout << "i = " << i << '\n';

		static ex_class_23 myclass;		// ctor and dtor will be called once
	}
	std::cout << "main ending\n";
}

/*
Output:
	main starting
	i = 0
	ex_class_23() this = 00007FF6A16C0200
	i = 1
	i = 2
	i = 3
	i = 4
	i = 5
	i = 6
	i = 7
	i = 8
	i = 9
	main ending
	ex_class_23 destructor this = 00007FF6A16C0200
*/




//! Example

class ex_class_24 {
public:
	ex_class_24()
	{
		std::cout << "ex_class_24() this = " << this << '\n';
	}

	~ex_class_24()
	{
		std::cout << "ex_class_24 destructor this = " << this << '\n';
	}
};

int main()
{
	ex_class_24 myclass;		// constructor called only once
	ex_class_24* ptr = &myclass;
}


/*
Output:
	ex_class_24() this = 0000005C64CFF9B4
	ex_class_24 destructor this = 0000005C64CFF9B4
*/

//! Example

class ex_class_25 {
public:
	ex_class_25()
	{
		std::cout << "ex_class_25() this = " << this << '\n';
	}

	~ex_class_25()
	{
		std::cout << "ex_class_25 destructor this = " << this << '\n';
	}
};

int main()
{
	ex_class_25 myclass;		// only one object created
	ex_class_25& r1 = myclass;	// this doesn't create an object
	ex_class_25& r2 = myclass;
	ex_class_25& r3 = myclass;
	ex_class_25& r4 = myclass;
}
/*
Output:
ex_class_25() this = 00000037DBEFF804
ex_class_25 destructor this = 00000037DBEFF804
*/



//! Example

class ex_class_26 {
public:
	ex_class_26()
	{
		static int x = 0;
		std::cout << ++x << '/n';
	}
};

int main()
{
	ex_class_26 n1;
	ex_class_26 n2;
	ex_class_26 n3;
	ex_class_26 n4;
}

/*
Output:
1
2
3
4
*/




//! Example

class ex_class_26 {
public:
	ex_class_26()
	{
		static int x = 0;
		std::cout << ++x << '/n';
	}
};

int main()
{
	ex_class_26 arr[100];	// creates 100 objects of ex_class_26 class
}

/*
Output:
1
2
3
4
...
100
*/



//! Example

class Logger {
public:
	Logger()
	{
		mf = std::fopen("logger.txt", "w");
		///...
	}
	~Logger()
	{
		fclose(mf);
	}
	void foo()
	{
		std::fprintf(mf, "foo called\n");
	}

	void bar()
	{
		std::fprintf(mf, "bar called\n");
	}
private:
	FILE* mf;
};

void foo()
{
	Logger lg;	// file opens when the object is created

	lg.foo();
	lg.bar();
}				// life of object finishes here

int main()
{
	foo();
	// at this point, file is closed
}



//! Example

struct ex_class_27 {
	ex_class_27()
	{
		std::cout << "default ctor\n";
	}

	void print()const
	{
		std::cout << "mx = " << mx << "\n";
	}
	int mx;
};

int main()
{
	ex_class_27 myclass1;	// default initialization
	// default ctor is called for default initialized objects


	ex_class_27 myclass2{};	// value initialization
	// default ctor is called for value initialized objects


	myclass1.print();		// undefined behavior because mx has garbage value
	myclass2.print();		// zero-initialized, no undefined behavior here, mx = 0

}


//! Example

struct ex_class_28 {
	void print()const
	{
		std::cout << "mx = " << mx << "\n";
	}
	int mx;
};

ex_class_28 myclass;		// default initialization
// no undefined-behavior because the object has static life-span
//! static objects, before initialization, get zero-initialized
int main()
{
	myclass.print();
}


//! Example

struct ex_class_29 {
public:
	ex_class_29(int x)
	{
		std::cout << "ex_class_29(int x) x = " << x << "this = " << this << "\n";
	}
};

int main()
{
	ex_class_29 class1(45);		// direct initialization
	std::cout << "&class1 = " << &class1 << '\n';	// class1 and this have same address
}


//! Example

struct ex_class_30 {
public:
	ex_class_30(int x)
	{
		std::cout << "ex_class_30(int x) x = " << x << "this = " << this << "\n";
	}
};

int main()
{
	ex_class_30 class1{ 67 };		// direct list initialization
	std::cout << "&class1 = " << &class1 << '\n';
}


//! Example

struct ex_class_31 {
public:
	ex_class_31(int x)
	{
		std::cout << "ex_class_31(int x) x = " << x << "this = " << this << "\n";
	}
};

int main()
{
	ex_class_31 class1 = 10;	// copy initialization
}


//! Example

struct ex_class_32 {
public:
	ex_class_32()
	{
		std::cout << "ex_class_32 this = " << this << "\n";
	}

	ex_class_32(int x)
	{
		std::cout << "ex_class_32(int x) x = " << x << "this = " << this << "\n";
	}
};

int main()
{
	ex_class_32 class1;			// default initialization
	ex_class_32 class2{};		// value initialization
	ex_class_32 class3(12);		// direct initialization
	ex_class_32 class4{ 36 };		// direct list initialization
	ex_class_32 class5 = 65;	// copy initialization
}


//! Example

struct ex_class_33 {
public:
	ex_class_33()
	{
		std::cout << "ex_class_33 this = " << this << "\n";
	}

	ex_class_33(int x)
	{
		std::cout << "ex_class_33(int x) x = " << x << "this = " << this << "\n";
	}

	ex_class_33(double x)
	{
		std::cout << "ex_class_33(double x) x = " << x << "this = " << this << "\n";
	}

	ex_class_33(int x, int y)
	{
		std::cout << "ex_class_33(int x, int y) x = " << x << "y = " << y << "this = " << this << "\n";
	}
};

int main()
{
	ex_class_33 class1;			// default ctor called
	ex_class_33 class2(45);		// ex_class_33(int x) called
	ex_class_33 class3(4.5f);	// ex_class_33(double x) called
	ex_class_33 class4(4.5L);	// syntax error, ambiguity

	ex_class_33 class5 = { 3,5 };	// ex_class_33(int x, int y) called
}


//////////////////////////////////////////////////////////////////////////////7

//! Example
class ex_class_34 {

public:
	~ex_class_34()
	{
		std::cout << "destructor\n";
	}
};

int main() {
	ex_class_34 myclass;	// destructor gets called
	// what about constructor? :o
	// default constructor called which was written by compiler
}


//! Example
class ex_class_35 {

public:
	ex_class_35() = default;		// i ask the compiler to write the constructor
	~ex_class_35()
	{
		std::cout << "destructor\n";
	}
};

int main() {
	ex_class_35 myclass;
}


//! Example
class ex_class_36 {

public:
	ex_class_36(int) {};

};

int main() {
	ex_class_36 myclass;	// syntax error : no appropriate default constructor available
}


/////////////////////////////////////////////////////////////////////////////////////////


/*
Special member functions can be:
	1. user declared
		  - defined		MyClass();
		  - defaulted		MyClass() = default;
		  - deleted		MyClass() = delete;

	2. implicitly declared
		- defaulted
		- deleted

	3. not declared
*/

//! Example
class ex_class_37 {

public:
	ex_class_37();				// user declared

};

//! Example
class ex_class_38 {

public:
	ex_class_38() = default;	// user declared
	// i am declaring it, but the compiler will define it
};

//! Example
class ex_class_39 {

public:
	ex_class_39() = delete;	// user declared
	// i am declaring it, but calling this function is a syntax error
};

//! Example
class ex_class_40 {
public:
	// this class has default constructor
	// has destructor
	// none is user declared
	// both are implicitly declared
};


//! Example
class ex_class_41 {
public:
	// the compiler declares and defines constructor and destructor
	// implicitly declared defaulted
};

int main()
{
	ex_class_41 m;
}


//! Example
class ex_class_42 {

	const int x;

	// this class has default constructor, it is implicitly declared
};

int main()
{
	ex_class_42 m;		// syntax error, the default constructor cannon be referenced - it is a deleted function
	// implicitly declared deleted
}

//! Example

struct ex_struct_1 {
	ex_struct_1(int);	// default constructor is NOT 'user declared'
	// default constructor is NOT 'implicitly declared'
	// default constructor is 'not declared'
};

int main()
{
	ex_struct_1 struct_1;	// error : no default constructor exists
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

//! Example
class ex_class_43 {
public:
	ex_class_43()
	{
		mx = 0;		// assignment, not initialization
		my = 0;		// when the program enters the constructor block, member variables have already been initialized
	}

private:
	int mx, my;
};


//! Example
class ex_class_44 {
public:
	ex_class_44()
	{

	}

private:
	int& r;			// syntax error, references do not get default initialized
	// references must be initialized

	const int x;	// const objects do not get default initialized
	// an object of const-qualified type must be initialized
};

/////////////////////////////////////////////////////////////////////////////////

/*! Constructor (Member) Initializer List */
//			Syntax that only constructors can use.


//! Example
class ex_class_45 {
public:
	ex_class_45();		// constructor user declared declaration
private:
	int mx;
	double my;
	//
};

ex_class_45::ex_class_45() : mx(5), my(7.5)		// valid syntax
{


}

ex_class_45::ex_class_45() : mx{ 5 }, my{ 7.5 }	// also valid syntax, but narrowing conversion will cause syntax error
{

}


//! Example
class ex_class_46 {
public:
	ex_class_46();
private:
	const int mx;
};

ex_class_46::ex_class_46()
{
	// syntax error : an object of const - qualified type must be initialized	
}

//! Example
class ex_class_47 {
public:
	ex_class_47();
private:
	int& r;
};

ex_class_47::ex_class_47()
{
	// syntax error : references do not get default initialized
}



//! Example
class ex_class_48 {
public:
	ex_class_48(int x) : mx(x) {}
private:
	int mx;
};

class ex_class_49 {
public:
	ex_class_49(int x)
	{
		mx = x;
	}
private:
	int mx;
};

/*
What's the difference between these two?
	//
*/


//! Example
class ex_class_50 {
public:
	ex_class_50(int a) : my(a), mx(my / 3) {}
	// undefined behavior
private:
	int mx, my;	// first mx, then my
	//  In C++, the order of initialization of class members is determined by the order of their declaration in the class, not by the order they are listed in the constructor's member initializer list.
};


//! Example
class ex_class_51 {
public:
	ex_class_51() :x(10) {}

	void print()const
	{
		std::cout << "x = " << x << '\n';
	}
private:
	int x;
};

int main()
{
	ex_class_51 ex;
	ex.print();

}
/*
Output:
x = 10
*/


//! Example
class ex_class_52 {
public:
	ex_class_52() {}

	void print()const
	{
		std::cout << "x = " << x << '\n';	// undefined behavior
	}
private:
	int x;
};

int main()
{
	ex_class_52 ex;
	ex.print();

}

//! Example
class ex_class_53 {
public:
	ex_class_53(int val) : x(val) {}

	void print()const
	{
		std::cout << "x = " << x << '\n';
	}
private:
	int x;
};

int main()
{
	ex_class_53 ex;	// syntax error, no default constructor exists for class ex_class_53
	ex.print();

}

//! Example
class ex_class_54 {
public:
	ex_class_54(int val) : x(val) {}

	void print()const
	{
		std::cout << "x = " << x << '\n';
	}
private:
	int x;
};

int main()
{
	ex_class_54 ex(45);
	ex.print();
}
/*
Output:
x = 45
*/


//! Example
class ex_class_55 {
public:
	ex_class_55(int x) : x(x) {}	// no problem, but ugly code
	// the first 'x' is searched in class scope
	// the 'x' inside the parantheses is searched as argument variable
	void print()const
	{
		std::cout << "x = " << x << '\n';
	}
private:
	int x;
};

int main()
{
	ex_class_55 ex(45);
	ex.print();
}
/*
Output:
x = 45
*/


//! Example
class ex_class_56 {
public:
	ex_class_56() : x(x) {}		// 'x' is initialized with its own garbage value
	void print()const
	{
		std::cout << "x = " << x << '\n';
	}
private:
	int x;
};


//! Example
class ex_class_57 {
public:
	ex_class_57(int x) : mx(x) {}
	void print()const
	{
		std::cout << "mx = " << mx << '\n';		// mx = 45
		std::cout << "my = " << my << '\n';		// garbage value
	}
private:
	int mx, my;
};

int main()
{
	ex_class_57 ex(45);
	ex.print();
}
/*
	Output:
	mx = 45
	my = -858993460 (garbage value)
*/

//! Default Member Initializer

// This feature provides a default value for a member that will be used unless an initializer is provided 
// at the point of object creation or in the constructor's member initializer list.

//! Example of Default Member Initializer
class ex_class_58 {
public:

private:
	int mx = 0;		// this syntax came with modern C++ ( C++11 )
	// Default Member Initializer
	// or In-Class Initializer
};


//! Example
class ex_class_59 {
public:

	ex_class_59()	// if i write the constructor like this, the compiler will put ' : mx(0) '
	{

	}

private:
	int mx = 0;

};


//! Example
class ex_class_60 {
public:

	ex_class_60() : mx(45)	 // okay, default member initializer not used
	{

	}

	void print()const
	{
		std::cout << "mx = " << mx << '\n';
	}

private:
	int mx = 0;

};

int main()
{
	ex_class_60 ex;
	ex.print();
}
/*
	Output:
	mx = 45
*/


//! Example
class ex_class_61 {
public:

	ex_class_61()
	{

	}

	void print()const
	{
		std::cout << "mx = " << mx << '\n';
	}

private:
	int mx{ 765 };	// legal
	//int mx( 765 );	// illegal
};

int main()
{
	ex_class_61 ex;
	ex.print();
}
/*
	Output:
	mx = 765
*/


//! Example
class Point {
public:
	void print() const
	{
		std::cout << mx << " " << my << " " << mz << '\n';	// undefined behavior
	}

private:
	int mx, my, mz;
};

int main()
{
	Point mypoint;		// constructer is implicitly declared defaulted
	myclass.print();
}


//! Example
class Point {
public:
	// The constructor the compiler writes: Point() : mx(0), my(0), mz(0) {}
	void print() const
	{
		std::cout << mx << " " << my << " " << mz << '\n';
	}

private:
	int mx = 0, my = 0, mz = 0;
};

int main()
{
	Point mypoint;		// constructer is implicitly declared defaulted
	myclass.print();
}
/*
	Output:
	0 0 0
*/


//! Example
class Point {
public:
	
	Point() {}
	
	void print() const
	{
		std::cout << mx << " " << my << " " << mz << '\n';
	}

private:
	int mx = 0, my = 0, mz = 0;
};

int main()
{
	Point mypoint;
	myclass.print();
}
/*
	Output:
	0 0 0
*/


//! Example
class Point {
public:
	
	Point() :mx(1), my(1), mz(1) {}
	
	void print() const
	{
		std::cout << mx << " " << my << " " << mz << '\n';
	}

private:
	int mx = 0, my = 0, mz = 0;
};

int main()
{
	Point mypoint;
	myclass.print();
}
/*
	Output:
	1 1 1
*/


//! Example
class Point {
public:
	
	Point() :mx(1){}	// default member initializer used for my and mz
	
	void print() const
	{
		std::cout << mx << " " << my << " " << mz << '\n';
	}

private:
	int mx = 0, my = 0, mz = 0;
};

int main()
{
	Point mypoint;
	myclass.print();
}
/*
	Output:
	1 0 0
*/