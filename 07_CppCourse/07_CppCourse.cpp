#include <iostream>

void foo(const* T);
void foo(T*);

void bar(const T&);
void bar(T&);


//! Example
void func(int*);
void func(double);
int main()
{
	func(0);		// syntax error, ambiguity
	func(nullptr);	// ok
}

void func(std::nullptr_t);

/*! Function Overloading */
struct Data {
	//..
};
void foo(int&) {		// L value reference

	std::cout << "foo(int&)\n";
}
void foo(int&&) {		// R value reference
	std::cout << "foo(int&&)\n";
}
int main() {
	int x = 10;
	foo(x);				// calls 'void foo(int &){}' because both L value
	foo(89);			// calls 'void foo(int&&) {}'
}

//! Move Overload
void baz(const T&);
void baz(T&&);
//! call with L value, calls L value
//! call with R value, calls R value


//! Example
void foo(const int&) { std::cout << "foo(int&&)\n"; }
void foo(int&&) {
std::cout << "foo(int&&)\n";
void foo(int&) {
std::cout << "foo(int&)\n";

int main() {

	int x = 10;
	const int y = 43;
	foo(x);		// foo(int &)
	foo(y);		// foo(const int&)
	foo(45);	// foo(int &&)
}

//!

int main() {
	int x = 10;
	// 'x'				L value expression
	// (x)				L value expression
	// (((((((x))))))		L value expression
}

int main() {
	int x = 10;
	int* ptr = &x;

	decltype(*ptr);		// int& type
	// value category PR		T
	// value category L		T&
	// value category X		T&&

	decltype(x + 4);		// PR value, int type
	decltype(foo());	// 'X' value, int && type
}

//! Reference Collapsing
using lref = int&;

int main() {
	int x = 10;
	lref& r = 30;	// int& type, int &r = 30
}

//! Exception
// There is no ambiguity in this case, it is an exception, 'void foo1(void*)' get called
void foo1(void*);
void foo2(bool);

int main() {
	int x = 10;

	foo1(&x);	// ok there is implicit conversion
	foo2(&x);	// ok
}

//! Exception
// all overloads
void foo(int, double, long);
void foo(char, int, float);
void foo(char, int, double);

// for one function to be selected:
//		- at least one parameter will come over the others
//		- ???????

//! Example
void foo(int, double, long);
void foo(char, int, float);
void foo(long, float, long long);
void foo(float, float, float);
int main() {

	foo(4.5L, 4.5, 43);		// no ambiguity
	foo(4.5L, 4.5, 43LL);	// 1,3 ambiguity

	foo(10., 'A', 34);		// 2nd function called
	foo(2.3f, 4.5f, 45);	// last one called
}

		/*! CLASSES */
// user - defined type
// complete type
// incomplete type

struct Data;	// declaration, incomplete type
class myClass;	// declaration, forward declaration, incomplete type

int foo(int);	// declaration
int foo(int) {}	// both a declaration and definition
int x;			// both a declaration and definition
extern int x;	// just declaration

// data abstraction

// ODR : One-Definition Rule
// class scope

// class memebers:
//		- data members :				static and non-static
//		- member functions :			static and non-static
//		- member types (nested types, type members)

class myClass {
	int mx;			// Data Member 
	void foo(int);	// Member Function
	class Nec {		//
	};
	using Word = int;	// Nested Type
};

int main() {
	myClass m;
	m.mx;		// cannot access private member declared in class
}

// name lookup
//		context control
//			access control

//! Access Specifier
// public
// private	: only class can access
// protected	: connected to inheritance 

class myClass {
	int mx, my;		// private by default
};

struct myClass
{
	int x;			// public by default
};

class Data {
	// private by default
private:
	// private
public:
	// public
protected:
	// protected
};

// Member Selection
//		A.y
//		ptr->a
//		Myclass::x

class Data {
	// all on the same scope
	int x;
public:
	int y;
};

// in C in Structures, all members are public

class Data {
	int x, y, z;
	void foo(int);		// member function
};
void func();			// free function

// Creating an object of a class : instantiate
// memory is allocated only when we create an object of the class, not when we define the class

//! What is a 'member function' ?

struct Nec {
	int x, y, z;
};

void func(Nec * p)
{
	// (*p).x
	// p->x;
}
int main()
{
	Nec mynec;
	func(&mynec);
}


//! Example
class Nec {
	int x, y, z;
public:
	void func();	//! it has a hidden parameter
	void foo(int);	//! member functions don't effect the size of class ot its need for storage
	void bar(int, int);
}

int main()
{
	Nec mynec;
	mynec.func();	//! we send the address of the object as a hidden parameter

	Nec* p{ &mynec };
	p->func();
}

//! Example
class Nec2 {
	int x, y, z;
public:
	void func();
	void foo();
	void bar();
};

void Nec2::foo()
{
	x = 5;		// ok
}

void func(Nec2 * p) {
	p->x;		// syntax error
}

//! Example
class Nec3 {
	int x, y, z;
public:
	void func();
	void foo();
	void bar();
};

class Erg {
	int x, y, z;
public:
	void func();
	void foo();		// different scope from foo function on Nec3 class
	void bar();
};

void foo(Nec3*);
void bar(Nec3*);

int main() {
}

//! Example
class Nec4 {
public:
	void foo(double);	// there is function overloading
	void foo(int);
};

//! Example
class Nec5 {
public:
	void foo(double);	// there is still function overloading
private:
	void foo(int);
};

//! Example
class Nec6 {
public:

};

void foo(double);		// redeclaration
void foo(double);

//! Example
class Nec7 {
public:
	void foo(double);	// syntax-error because there is no redeclaration for function memebers
	void foo(double);
};

//! Example
class Nec8 {
public:
	void foo(double);			// syntax-error
	void foo(const double);
};

//! Example
class Nec9 {
public:
	void foo(double);			// function overloading
	void foo(int);
	void foo(int, int);
	void foo(long);
};

int main()
{
	Nec mynec;
	mynec.foo(2.3);
	mynec.foo(2);
}

//! Example
class Nec {
public:
	void foo(int);			// non-static public member function, has a hidden parameter
	// function of the object

	static void bar(int);	// has no hidden parameter, function of the class
};

//! Example

// myclass.h
class MyClass5 {
public:
	int func();
private:
	int mx, my;
};

int foo(int, int);

// myclass.c"pp
// #include "myclass.h">"
int MyClass5::func()
{
	{
		mx = 5;	// name lookup: in block, then enclosing block, the class scope
	}
}

int foo(int x, int y)
{
	//
	return x * y;
}

//! Example
class MyClass5 {
public:
	int func();
private:
	int mx, my;
};
int MyClass5::func()
{
	int mx = 5;
	mx++;				// block scope mx

	MyClass5::mx = 5;	// class scope
}

//!Example
class MyClass6 {
public:
	int func();
private:
	int mx, my;
};

MyClass6 g;		// global variable

int MyClass6::func()
{
	MyClass6 m;
	m.mx = 13;	// legal

	mx = 5;		// legal
	g.mx = 5;	// legal	 :o
}

// Example

class Eni {
	void foo();
	int a;
};

int a;

void Eni::foo()
{
	int a = 5;

	a = 1;		// block scope 'a'

	::a = a + Eni::a;	// ok
	// ::a will be called only in namescope

	a = a + a;	// block scope 'a'
}


//Example

class Eni2 {
	void foo();
	int a;
};

void foo(int);

void Eni2::foo()
{
	foo(5);		// syntax error
	foo();		// recursive

	::foo(354);		// global namespace scope
}

//! Example

struct Data {

	void foo();		// non-static member functions, have hidden parameters
	void bar();
	int a, b, c;
};

void foo(struct Data* p)
{

}

void bar(struct Data* p)
{
	foo(p);
}

int main() {

	struct Data mydata = { 5,7,8 };
	bar(&mydata);
}

//! Example

struct Data2 {

	void foo();		// non-static member functions, have hidden parameters
	void bar();
	int a, b, c;
};

void Data2::foo(/* Data* p */)
{
	bar();	// bar will be called for the same object foo() was called
}

void Data2::bar()
{

}

int main() {

	Data2 mydata;

	mydata.foo();
}

//! Example

struct Data2 {

	void foo()
		void foo(int);
	void foo(double);
};

int main() {

	Data2 mydata;

	mydata.foo();
	mydata.foo(6);
	mydata.foo(7.);
}

//! Example

struct Data2 {

	void foo()
		void foo(int);
	void foo(double);
};

void Data2::foo()
{
	// all legal
	foo();		// recursive call
	foo(2);		// void foo(int); will be called
	foo(3.4);	// void foo(double); will be called

	Data::foo();	// same thing as foo();

	// example
	int foo = 5;
	foo(3.4);			// illegal because of contex control
	Data::foo(3.4);		// okay
}

void Data2::foo(int)
{

}

void Data2::foo(double)
{

}

int main() {

	Data2 mydata;

	mydata.foo();
	mydata.foo(6);
	mydata.foo(7.);
}

//! Example

// in C a struct should have elements, else illegal
class Eni4 {

private:
	void func(double);
public:
	void func(int);

	void bar();
};

int main() {
	Eni4 eni;

	eni.func(4.65);		// name lookup : ok
	// access control : error

	eni.func(4);		// ok

}


//! Example
class Eni5 {

private:
	void func(double);
public:
	void func(int);

	void bar();
};

void Eni5::bar()
{
	func(2);		// Function Overload Resolution
	func(2.4);
}

//! Example

class Eni6 {
private:
	int mx;
public:
	void foo(int x)
	{
		mx = x;
	}
};

// inline expansion	(optimization)
// inline function
// ODR

// Example

struct Eni7 {
	int x, y, z, ;

};

void foo(Eni7*);		// mutator
void bar(const Eni7*);	// no intention of changing

void baz(Eni7&);		// has intention of changing, mutator
void bom(const Eni7&);

int main() {
	Eni7 eni{};
	const Eni7 ceni{};
	// .. ?
}

// Example

class MyClass9 {
public:
	void func(int);			// mutator,		void func(Myclass *, int);
	// accesser,		void func(const Myclass *, int);
	void foo(int)const;		// const member functions
private:
	int mx;
};

void MyClass9::func(int x)
{
	mx = x;
}

void MyClass9::foo(int x)const
{
	mx++;		// syntax error
}
// syntactic
// semantic

//! Example
class MyClass10 {
public:
	void func();
	void foo()const;
private:
	int mx;
};

void MyClass10::func() {

	foo();	// legal
}

void MyClass10::foo()const {

	func();		// illegal
}

int main() {
	MyClass10 m;

	// both legal
	m.func();
	m.foo();

	const MyClass10 m2;

	// implicit conversion const -> non-const is syntax error
	m2.func();	// syntax error
	m2.foo();

	MyClass10 m3;
	MyClass10* p = &m3;
	p->func();	//illegal
}