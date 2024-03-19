#include<mutex>
#include<vector>
#include<iostream>
#include<ctime>

//! Revision
class MyClass {
public: 
	void func();		// it has a hidden parameter, void func(MyClass *)
	void foo()const;	// void func(const MyClass *)
};

int main()
{
	MyClass m;
	m.func();	// sends the address of 'm' object as a parameter to the func() function

	m.foo();

	const MyClass n;
	n.foo();	
}


//! Example

class MyClass2 {
public:
	void func();
	void foo()const;
	int mx;
};

void f(MyClass2* p)
{
	p->mx = 5;	// ok
}

void f2(const MyClass2* p)
{
	p->mx = 5;	// syntax error : expression must be a modifiable lvalue
}

//! Example

class Fighter {
public:
	void print()const
	{
		m_call_count++;		// print() is a const function, syntax-error
		mtx.lock();			// no more a syntax error after adding 'mutable'

		mtx.unlock();
	}
	
private:
	int m_age;
	int m_power;
	//
	// int m_call_count;
	mutable int m_call_count;

	// internal synchronization (using mutex) to make it thread-safe
	// std::mutex mtx;
	mutable std::mutex mtx;
};

//! Example
class Fighter2 {
public:
	
	void func()const;	// const Fighter2 *
	void func();		// function overloading
};

// same as this const overloading
void foo(Fighter2*);
void foo(const Fighter2*);

//! Example
class Eni {
public:
	void func()const;
	void func();
};

int main() {
	const Eni myen;
	myen.func();	// void func()const; will be called for const objects
}

//! Example
using namespace std;

int main()
{
	vector<int> vec{ 3,6,8,1 };
	vec.at(2) = 5;			// legal
	auto val = vec.at(1);	// legal

	const vector<int> cvec{ 3,6,8,1 };
	cvec.at(2) = 5;			// expression must be a modifiable lvalue
	auto val = cvec.at(1);	// legal
	// 'at' function was overloaded that is why
}
class Vector {
public:
	int& at(std::size_t n);
	const int& at(std::size_t n)const;
};

//! Example
class Nex {
public: 
	void foo()const;	// accesser
	void bar();			// mutator
};

int main() 
{
	Nex mynex;
	
	mynex.foo();

	const Nex mynec;
	mynec.bar();		// syntax-error
	// Error 'void MyClass::bar(void)': cannot convert 'this' pointer from 'const MyClass' to 'MyClass &'
}

/*! 'this' keyword pointer */
// used only for non-static class members
// this : value category : PR Value Expression
class MyClass4 {
public:
	void func();
	void foo();
private:
	int mx;
	int my;
};

void MyClass4::func()		// func(MyClass4 *this)
{
	// no difference in meaning between these three
	this->mx = 4;
	mx = 4;
	MyClass4::mx = 4;

	// no difference in meaning between these three
	foo();
	this->foo();
	MyClass4::foo();
}

//! Example
// Usage of 'this'
class MyClass5 {
public:
	void func();
	void foo();
private:
	int mx;
	int my;
};

void f(MyClass5*);
void g(MyClass5&);

void MyClass5::func()
{
	f(this);
	g(*this);
}


//! Example
// Usage of 'this'
// Fluent API 

class MyClass6 {
public:
	MyClass6& foo();
	MyClass6& bar();
	MyClass6& baz();
private:
};

MyClass6& MyClass6::foo()
{

	return *this;
}

MyClass6& MyClass6::bar()
{

	return *this;
}

MyClass6& MyClass6::baz()
{

	return *this;
}

int main() {

	MyClass6 m;
	m.foo().bar().baz();
}


//! Example
// Usage of 'this'
class MyClass5 {
public:
	void func();
	void foo();
private:
	int mx;
	int my;
};

void f(MyClass5*);
void g(MyClass5&);

void MyClass5::func()
{
	f(this);
	g(*this);
}


//! Example

class MyClass7 {
public:
	MyClass7* foo();
	MyClass7* bar();
	MyClass7* baz();
private:
};

MyClass7* MyClass7::foo()
{

	return this;
}

MyClass7* MyClass7::bar()
{

	return this;
}

MyClass7* MyClass7::baz()
{

	return this;
}

int main() {

	MyClass7 m;
	auto p = &m;

	p->foo()->bar()->baz();
}


//! Example

int main() {

	int x = 5;
	int y = 6;
	double z = 4.5;

	cout << x << y << z << endl;
	cout.operator<<(x).operator<<(y).operator<<(z).operator<<(endl);
}

//! Example

class MyClass8 {
public:
	void foo();
	void bar()const;
};

void MyClass8::bar()const {

	*this; 
}

/*! ODR - One Definition Rule */

/*
	Not a Syntax-Error but ILL-FORMED:

furkan.cpp :

	void foo(int x)
	{

	}

bora.cpp :

	void foo(int x)
	{

	}
*/

// Functions, Global Variables, Classes 

// violation of ODR
int x = 5;
int x = 5;

// violation of ODR
class MyClass {

};

class MyClass {

};

//! Example

// source1.h
class Nec {
	int foo(int);
	int bar(double);
};

// source2.h
class Nec {
	int foo(int);
	int bar(double);
};

//! Example
//! Violation of ODR, undefined-behavior
// source1.cpp
class Nec {
	int foo(double);
	int bar(double);
};

// source2.cpp
class Nec {
	int foo(int);
	int bar(double);
};

//! Example

// neco.h

void foo(int x)
{
	// wrong, undefined-behavior, violation of ODR (if neco.h is included in several files)
}

//! Example

//!!!!!!!! Inline Expansion
int foo(int x, int y)
{
	return x * x + y * y;
}

int bar(int a, int b)
{
	return foo(a,b);
}

// zero-cost abstraction
int main()
{
	int x = 45;
	int y = 34;
	auto a = bar(x, y);	// what compiler sees : auto a = x * x + y * y;
	
}
/* When does the compiler make in-line expansion:
	1. compiler analysis	
	2. depended on the compiler
	3. compiler switch 
	
*/

/*! INLINE FUNCTION */
inline int foo(int x, int y)
{
	return x * x + y * y;
}

//! Example
// serhat.h
int func(int x, int y)
{
	// if i do this i show the compiler the code but i violate ODR 
}

inline int func(int x, int y)
{
	// if i put 'inline', it wont violate ODR
	// only one instance is created of func function when 'serhat.h' is included
}

// if i include serhat.h in these files
// pelin.cpp
// #include "serhat.h"
void pel_func()
{
	auto fp = &func;
}

// bora.cpp
// #include "serhat.h"
void bora_func()
{
	auto fp = &func;		// &func is gonna be the same in both files
}

//! Example

// bora.h

int foo(int, int);
inline int foo(int x, int y)
{
	// if we put inline in declaration or definition is ok
}

//! Example
// OK
class Bora {
public:
	void set(int a, int b);

private:
	int mx, my;
};

inline void Bora::set(int a, int b)
{
	mx = a;
	my = b;
}

//! Example
// OK
class Bora {
public:
	inline void set(int a, int b);

private:
	int mx, my;
};

void Bora::set(int a, int b)
{
	mx = a;
	my = b;
}

//! Example
// Violates ODR
class Bora {
public:
	void set(int a, int b);

private:
	int mx, my;
};

void Bora::set(int a, int b)
{
	mx = a;
	my = b;
}

//! Example
class Bora {
public:
	void set(int a, int b)		// if a static or non-static member function's definition is inside the class -> inline
	{
		mx = a;
		my = b;
	}

private:
	int mx, my;
};

//! Example
class Bora {
public:
	inline void set(int a, int b)		// ok, no syntax-error, redundancy
	{
		mx = a;
		my = b;
	}

private:
	int mx, my;
};

//! Example
// bora.h
int foo(int x, int y)			// not an inline function, ODR violation
{
	return x * y + 4;
}

constexpr foo(int x, int y)		// implicitly inline function, doesn't violate ODR
{
	return x * y + 4;
}

//! Example

class MyClass10 {
public:
	void set(int x)
	{
		mx = x;
	}
	int get()const 
	{
		return mx;
	}
private:
	int mx;
};

bool is_equal(const MyClass10& m1, const MyClass10& m2)
{
	return m1.mx == m2.mx;			// private access
	return m1.get() == m2.get();	// ok but violates ODR
}

//! Example
// header file

static int foo(int x, int y)		// doesn't violate ODR but not same as writing 'inline'
{									// everywhere included 'foo' will have different address
	return x * y + 5;
}

inline int foo(int x, int y)		
{
	return x * y + 5;
}

//! Example
// bora.h

int x = 5;			// ODR violation
extern int x;		// declaration, so not an ODR violation
static int x = 5;	// not ODR violation, internal linkage

//! Example
// C++17
inline int& foo()
{
	static int x = 5;
	return x;
}

//! Why not use in-line functions?
// 1 - Code exposion
// 2 - Code Size increases
// ...

class MyClass;	// class declaration, forward declaration

class MyClass {	// class definition

};

class Nec;		// incomplete type
class Can;
class Frk;

Nec foo(Can, Frk);		// ok
Nec* bar(Can&, Frk&&);	// ok

int main() {
	Nec* p;		// ok
}

//! Example
class Nec;
Nec* foo1();
Nec* bar(Nec*);
Nec& baz();

int main()
{
	// all legal 
	Nec* p1 = foo1();
	auto p2 = bar(p1);
	Nec& r = baz();
	bar(&r);
}

//! Example

class Eni;
// all ok
typedef Eni* EniPtr;
using ppnec = Eni**;

//! Example

class Eni2;
// all ok
extern Eni2 geni;
extern Eni2 ar[];

//! Example
class Eni3;

class Eni4 {
	
	Eni3 mx;	// syntax error, incomplete type is not allowed
};

//! Example
class Eni4;

Eni4* foo();
Eni4* bar(Eni4*);

int main()
{
	Eni4* p = foo();
	p = bar(p);

}


//! Example

class Eni6;
class Eni5 {
	Eni5 mx;			// illegal
	Eni5* mx;			// ok

	static Eni5 mx;		// ok
	Eni6 nx;			// illegal
	static Eni6 nx;		// ok
};

//! Example

int main() 
{
	class MyClass* p{};	// ok, even without declaration, it is itself accepted as incomplete type declaration
}

//! Example
int main()
{
	void x;		// incomplete type, error
}

//! Example
int main()
{
	int[]; 
}

//! Example
// Hidding 'private' part of the classes
// pimpl : pointer implementation
// cheshire cat
// opaque pointer
// compiler firewall
// handle body
/*
class MyClass11 {

private:
	T x, y;
	U z;
};
*/