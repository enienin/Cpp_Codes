#include <iostream>
#include<string>
#include<vector>
#include<list>
#include<string>
#include<fstream>
#include<memory>
#include<mutex>


class MyClass {

public:
	// copy ctor
	MyClass(const MyClass& other) : tx(other.tx), ux(other.tx) {}

	// move ctor
	MyClass(MyClass&& other) : tx(std::move(other.tx)), ux(std::move(other.ux)) {}

	// copy assignment
	MyClass& operator=(const MyClass& other)
	{
		tx = other.tx;
		ux = other.ux;
		return *this;
	}

	// move assignment
	MyClass& operator=(MyClass&& other)
	{
		tx = std::move(other.tx);
		ux = std::move(other.ux);
		return *this;
	}
private:
	T tx;
	U ux;
};


//! Example

class Any {
	//..
};

void foo(Any&& r)	// takes an rvalue reference to an 'Any' object as its parameter
{

}

int main()
{
	Any any;
	foo(std::move(any));	// a reference to object 'any' is passed to the function.
	// by using std::move(any), we're indicating that foo is allowed to "move" from 'any', or take over its resources
}


//! Example
class Any {
	//..
};

void foo(Any&& r)	// takes an rvalue reference to an 'Any' object as its parameter
{
	Any any_x = std::move(r);	// move ctor is called in this case
}

int main()
{
	Any any;
	foo(std::move(any));	// a reference to object 'any' is passed to the function.
}

//! Example
class Any {
	//..
};

void foo(Any&& r)	// takes an rvalue reference to an 'Any' object as its parameter
{
	Any any_x;
	any_x = std::move(r);	// move assignment is called in this case
}

int main()
{
	Any any;
	foo(std::move(any));	// a reference to object 'any' is passed to the function.
}

//

// L value	- it refers to objects that *persist* beyond a single expression.
//			- it implies that the expression identifies a specific object or function in memory, 
//			  and thus, it has the potential to be used or modified later

// R value	- typically used to describe values that do not have a persistent reference, 
//			  often because they are temporary in nature.


//! Example
void func(const std::string& other)
{
	std::string sval = other;	// copy ctor is called
}

int main()
{
	// func(R value);		// doesn't take over the resources of sval

}

/*
The parameter 'other' is a const lvalue reference to a std::string.
When you pass an argument to 'func', regardless of whether it's an lvalue or rvalue,
the const std::string& can bind to both.
However, because 'other' is declared as const, it cannot be modified inside 'func'.
This constness implies that the function promises not to change the original object,
which aligns with the semantics of copying rather than moving.
Moving from an object generally modifies it (by transferring ownership of resources),
which would violate the contract established by the const qualifier.
*/

//! Move Overload
//! Example

void func(const std::string& other)
{
	std::string sval = other;	// copy ctor is called
	// doesn't take over the resources, just copies them
}

void func(std::string&& other)
{
	std::string sval = std::move(other);	// move ctor is called, takes over the resources
}

int main()
{
	// func(R value);		// function overload resolution, the func that takes R value expr as parameter gets called

}

//! Example

// vector : dynamic array
int main()
{
	// push_back(const T&);
	// push_back(T&& r)

	// vec.push_back(arg);
	// if agr is lvalue expression : push_back(const T&)	is called
	// if agr is rvalue expression : push_back(T&&)		is called

}


//! Example

// compiler can write all member functions
class exClass1 {
private:
	std::vector<int> mvec;
	std::list<int> mlist;
	std::string mstr;
};


//! Example

//!  There is no cost difference between the move constructor and the copy constructor 
// because both operations involve element-wise copying of the arrays.
// the resources managed (the arrays ar and d) are not pointers or handles that can simply be reassigned; 
// they are part of the object's storage. 
// Since C++ does not provide a built-in mechanism to "move" an array's contents in memory 
// (the way it does for dynamic allocations by transferring pointers), 
// the move constructor for exClass1 will have the same behavior and cost as the copy constructor.
class exClass1 {
private:
	int ar[400];
	double d[200];
};


//! Example

std::string foo();

int main()
{
	auto str = foo();	//! move sematics come into play 
	// foo() is a PR value expression
	// thus, move ctor is called
	// str takes over the resources of 'foo' functions return value
}


//! Example

std::string foo();

int main()
{
	auto str{ std::string(300'000, 'A') };
	// move ctor called
}

//! Example

int main()
{
	std::string str(300'000, 'a');


	//std::string s(str);	// copy ctor called because 'str' is l value expression
	std::string s(std::move(str));	// move ctor called because std::move(str) is R value
	//! what about when dtor is called?
	// dtor is written in the way that it understands it had its resources stolen, and doesn't free the memory

	// str still alive
	//! moved-from state ( state where it has had its resources stolen )

	//! valid state
	// In C++, the term "valid state" refers to an object being in a condition where it satisfies all class invariants, 
	// and its data members are in a state that allows the class's member functions 
	// to execute as designed without causing undefined behavior, errors, or data corruption.
	// invariant holds
}

//! Example

int main()
{
	std::ifstream ifs{ "folder.txt" };
	// control

	std::string str;
	std::vector<std::string> svec;
	//..

	while (ifs >> str)	// no undefined-behavior, because moved-from state is a valid but unspecified state
	{
		svec.push_back(std::move(str));
		// str moved-from state
		// This means that while the exact contents or state of the object after it has been moved from are not defined, 
		// the object itself must still be usable in a way that does not lead to undefined behavior. 
	}
}

//

//! In which cases does the compiler implicitly defaults a special member function?


//! Scenario 1
// no special member function is declared
class Eni {

};

// how it comes out of the compiler's hands
class CEni {
	CEni() = default;
	~CEni() = default;
	CEni(const CEni&) = default;
	CEni(CEni&&) = default;
	CEni& operator = (const CEni&) = default;
	CEni& operator = (CEni&&) = default;
};


//! Scenario 2
class Eni {
public:
	Eni(int);
};

// how it comes out of the compiler's hands
class CEni {
	~CEni() = default;
	CEni(const CEni&) = default;
	CEni(CEni&&) = default;
	CEni& operator = (const CEni&) = default;
	CEni& operator = (CEni&&) = default;
};

//! Scenario 3
class Eni {
public:
	~Eni();
};

// how it comes out of the compiler's hands
class CEni {
	CEni() = default;
	~CEni();
	CEni(const CEni&) = default;
	CEni(CEni&&) = default;
	// move ctor and move assignment not declared
};

//! Scenario 4
class Eni {
public:
	Eni(const Eni&);
};

// how it comes out of the compiler's hands
class CEni {
	// default ctor not declared
	~CEni() = default;

	// copy assignment defaulted
	CEni& operator = (const CEni&) = default;

	// move members not declared
};

//...

//! Caution
// If we declare one of these functions : dtor, copy ctor, copy assignment, then:
//	a) compiler doesn't declare move members (not-declared)

// If we declare a move member :
//		a) compiler deletes copy members
//		b) the non-declared move member is on not declared state


//! Example
class Eni {
public:
	Eni(const Eni&) = default;
	// default ctor is not-declared
	// dtor is implicitly declared
	// copy assignment implicitly declared
	// move ctor and assignment not declared
};

//! Example

class MyClass {
public:
	~MyClass();
};

int main()
{
	MyClass m1;
	MyClass m2;

	m1 = std::move(m2);	// valid even tho the class has no move assignment, instead of move assignment, copy assignment is called
	// if the class has no move members, copy members will be called
}

//

//! Move-Only Types
// A move-only type is a value that can be moved but not copied.
//		unique_ptr
//		ostream
//		std::thread
//		unique_lock
//		std::future
//		std:promise

// Classes : copyable & movable
// Move-Only Type : non-copyable but movable
//				: non-copyable non-movable


//! Example on Move-Only Types
int main()
{
	using namespace std;

	unique_ptr<int> x(new int);

	auto y = x;	// syntax error, cannot be copied
	auto y = move(x);	// valid, because copy members deleted but move members exist
}

//! Example on Move-Only Types

class exClass1 {
public:
	//
	exClass1(const exClass1&) = delete;				// copy ctor deleted
	exClass1& operator=(const exClass1&) = delete;	// copy assignment deleted

	// move members not-declared if copy members deleted
	// we declare move members

	exClass1(exClass1&&);
	exClass1& operator=(exClass1&&);
	// now it is a move-only type
};


class exClass2 {
public:
	// exClass1 is same as exClass2
	// because move members are declared, the copy members will be deleted
	exClass2(exClass2&&);
	exClass2& operator=(exClass2&&);

};

//! Example on non-movable and non-copyable types

int main()
{
	using namespace std;

	mutex mtx;

	mutex mx = mtx;			// syntax error, closed to copying
	mutex x = move(mtx);	// syntax error, closed to moving
}


//! Example on movable and copyable

int main()
{
	using namespace std;

	string s;

	auto s1 = s;		// okay
	auto s2 = move(s);	// okay

}

//! Example

struct MyClass {
	// this class closed to both moving and copying
	MyClass(const MyClass&) = delete;
	MyClass& operator=(const MyClass&) = delete;
	// move members not-declared
};

//! Caution: Never delete Move Members!!

// Common mistake, deleting move members and keeping copy members.
// 
struct MyClass {
	MyClass(const MyClass&);
	MyClass& operator=(const MyClass&);

	MyClass(MyClass&&) = delete;
	MyClass& operator=(MyClass&&) = delete;
	// Since the move constructor is deleted, the compiler will not fallback to using the copy constructor as an alternative in this context.
};

int main()
{
	MyClass myclass;
	MyClass other = std::move(myclass);	// syntax error : MyClass::MyClass(MyClass &&) cannot be referenced - it is a deleted function
}

//

//! Example

class exClass3 {
public:
	// Move-Only Type
	exClass3() = default;
	exClass3(exClass3&&);
	exClass3& operator = (exClass3&&);
};

exClass3 ex_func()
{
	exClass3 mx;

	return mx;
	// when you return a move-only object from a function, C++ uses RVO or move semantics to efficiently handle the object transfer 
	// without resorting to copying.
}

//

//! Temporary Object
// A temporary object (or temporary) is an unnamed object created as an intermediate result of an expression. 
// Temporaries are created by the compiler during the evaluation of expressions, 
// especially when an operation needs to produce an object that is not bound to a named variable.

// MyClass()		: PR value expression
// MyClass{}		: PR value expression
// MyClass{12}	: PR value expression


class MyClass {

};

int main()
{
	MyClass& r = MyClass{};	// syntax error : initial value of reference to non-const must be an lvalue
	// temporary objects (rvalues) cannot be bound to non-const lvalue references. 
	const MyClass& r = MyClass{};		// legal
	MyClass&& r = MyClass{};			// legal, rvalue expression rvalue reference
}


//! Example

class exClass4 {

};

void foo(exClass4);
void bar(const exClass4&);
void baz(exClass4&&);
void funcc(exClass4&);

int main()
{
	foo(exClass4{});	// legal
	bar(exClass4{});	// legal
	baz(exClass4{});	// legal

	funcc(exClass4{});	// syntax error, 
}

//! Example

void func_2(const std::string& s)
{

}

int main()
{
	std::string s{ "hello world" };		// writing it like this gives the idea that we are going to use 's' in several places
	func_2(s);							// but we will only use 's' only once in our code
}


//! A better alternative is this:
void func_3(const std::string& s)
{
	//..
}

int main()
{
	func_3(std::string{ "hello world" });
	// at this point the life of 'std::string{ "hello world" }' has finished
}

//! Example on Temporary Objects
class exClass5 {
public:
	exClass5() { std::cout << "exClass5 default ctor" << '\n'; }
	~exClass5() { std::cout << "exClass5 dtor" << '\n'; }
};

// it would be legal even if it were : void func_4(exClass5&&)
void func_4(const exClass5&)	// parameter of the function is 'const lvalue reference'
{
	//..
}

int main()
{
	std::cout << "main started" << '\n';
	func_4(exClass5{});
	// life of the object ends here
	std::cout << "main continues" << '\n';
}
/*
Output:
	main started
	exClass5 default ctor
	exClass5 dtor
	main continues
*/


//! Example on Temporary Objects
class exClass6 {
public:
	exClass6() = default;

	exClass6& operator = (const exClass6&)
	{
		std::cout << "copy assignment" << '\n';
		return *this;
	}

	exClass6& operator = (exClass6&&)
	{
		std::cout << "move assignment" << '\n';
		return *this;
	}

	~exClass6() { std::cout << "exClass6 dtor" << '\n'; }
};

int main()
{
	exClass6 ex;
	ex = exClass6{};	//! move assignment will be called because the temporary object is a 'PR value expression', thus 'R value expression'
	std::cout << "main continues" << '\n';
	(void)getchar();
}
/*
Output:
	move assignment
	exClass6 dtor
	main continues

	exClass6 dtor
*/


//! Example on Temporary Objects
class exClass7 {
public:
	exClass7() = default;

	~exClass7() { std::cout << "exClass7 dtor" << '\n'; }
};

int main()
{
	exClass7 ex;

	std::cout << "main [1]\n";
	{
		const exClass7& r = exClass7{};		// 
		// The lifetime of this temporary object is extended to the lifetime of the reference 'r' because it is bound to a 'const reference'. 
		// This is a key behavior in C++: binding a temporary to a const reference extends the temporary's lifetime to match that of the reference.
		std::cout << "main [2]\n";
	}
	std::cout << "main [3]\n";

}
/*
Output:
		main [1]
		exClass7 dtor		(?) different on different compilers
		main [2]
		exClass7 dtor
		main [3]
		exClass7 dtor
*/



//! Example on Temporary Objects
//! The use of an rvalue reference to extend the lifetime of a temporary object
class exClass8 {
public:
	exClass8() = default;

	~exClass8() { std::cout << "exClass8 dtor" << '\n'; }
};

int main()
{
	exClass8 ex;

	std::cout << "main [1]\n";
	{
		exClass8&& r = exClass8{};		// temporary object : rvalue 
		// This syntax directly binds the temporary object (rvalue reference) to the rvalue reference r.
		std::cout << "main [2]\n";
	}
	std::cout << "main [3]\n";

}
/*
Output:
	main [1]
	exClass8 dtor		(?)
	main [2]
	exClass8 dtor
	main [3]
	exClass8 dtor
*/


//! Example on Temporary Objects
//! Life Extension
class exClass9 {
public:
	exClass9() = default;

	~exClass9() { std::cout << "exClass9 dtor" << '\n'; }
};

exClass9 func_2();

int main()
{
	const exClass9& r = func_2();
	// const lvalue referene , temporary object returned from func_2 is R value 
	// In C++, binding a temporary object to a const lvalue reference extends the lifetime of the temporary to the lifetime of the reference. 
}

//

//! Mandatory Copy Elision
// Mandatory copy elision reduces overhead by minimizing unnecessary constructions and destructions, 
// particularly in cases where objects are passed by value or returned from functions. 

//! Example
class exClass10 {
public:
	exClass10()
	{
		std::cout << "default ctor\n";
	}

	exClass10(const exClass10&)
	{
		std::cout << "copy ctor\n";
	}

	~exClass10()
	{
		std::cout << "dtor\n";
	}
};

void func_5(exClass10 x)
{
	std::cout << "func()\n";
}

int main()
{
	func_5(exClass10{});	// copy ctor not called !!
	// The compiler directly constructs the argument x in place for the function call to func_5, 
	// without creating a separate temporary object that would then need to be copied or moved.
	// This means the exClass10 object is constructed directly in the memory location where x is expected to be, 
	// effectively bypassing the need for invoking the copy constructor.
}
/*
Output:
	default ctor
	func()
	dtor
*/

//! Example (delete copy ctor)
class exClass11 {
public:
	exClass11()
	{
		std::cout << "default ctor\n";
	}

	exClass11(const exClass11&) = delete;

	~exClass11()
	{
		std::cout << "dtor\n";
	}
};

void func_5(exClass11 x)
{
	std::cout << "func()\n";
}

int main()
{
	func_5(exClass11{});	// syntax error C++14 because copy ctor deleted (C++14)
	// works fine on C++17 and after
	// Temporary Materialization
}

// With C++17, PR value espression is not an object.
//! Temporary Materialization
// In C++, applications of temporary materialization are mentioned below :
//		Prvalue(pure rvalue) expressions are passed to a function or operator that expects an lvalue reference.
//		Objects that are returned from a function by value.
//		Objects that are initialized using an initializer list.


//! Example on Temporary Materialization
class exClass12 {
public:
	exClass12()
	{
		std::cout << "default ctor\n";
	}

	exClass12(const exClass12&)
	{
		std::cout << "copy ctor\n";
	}

	~exClass12()
	{
		std::cout << "dtor\n";
	}
};

exClass12 func_6()
{
	return exClass12{};
}

int main()
{
	exClass12 m = func_6();
}

/*
Output:
	default ctor
	dtor
*/


//! Example on Temporary Materialization
class exClass13 {
public:
	exClass13()
	{
		std::cout << "default ctor\n";
	}

	exClass13(const exClass13&)
	{
		std::cout << "copy ctor\n";
	}

	~exClass13()
	{
		std::cout << "dtor\n";
	}
};

exClass13 func_7()
{
	return exClass13{};
}

int main()
{
	const exClass13& m = func_7();
}

/*
Output:
	default ctor
	dtor
*/

//! Example on Temporary Materialization
class exClass14 {
public:
	exClass14()
	{
		std::cout << "default ctor\n";
	}

	exClass14(const exClass14&)
	{
		std::cout << "copy ctor\n";
	}

	~exClass14()
	{
		std::cout << "dtor\n";
	}
};

void func_8(exClass14)
{

}

int main()
{
	func_8(exClass14{ exClass14 {exClass14{}} });
	// Prvalue expression inside the parantheses
}
/*
Output:
	default ctor
	dtor
*/


//! Example on Temporary Materialization
class exClass15 {
public:
	exClass15()
	{
		std::cout << "default ctor\n";
	}

	exClass15(const exClass15&)
	{
		std::cout << "copy ctor\n";
	}

	~exClass15()
	{
		std::cout << "dtor\n";
	}
};

int main()
{
	exClass15{};

}
/*
Output:
	default ctor
	dtor
*/

//! Example on Mandatory Copy Elision
//! Return Value Optimization (RVO)
class exClass15 {
public:
	exClass15()
	{
		std::cout << "default ctor\n";
	}

	exClass15(const exClass15&) = delete;

	~exClass15()
	{
		std::cout << "dtor\n";
	}
};

void func_9(exClass15);

// Return Value Optimization (RVO)

exClass15 func_10()
{
	return exClass15{};
}

int main()
{
	exClass15 m = func_10();	// copy elision
}

/*
Output (C++17) :
	default ctor
	dtor
*/


//! Example on Mandatory Copy Elision
//! Named Return Value Optimization (NRVO)
class exClass16 {
public:
	void set(int x)
	{
		mx = x;
	}

	void print()const
	{
		std::cout << "mx = " << mx << '\n';
	}

	exClass16() : mx{ 10 }
	{
		std::cout << "default ctor\n";
	}

	exClass16(const exClass16& other) : mx{ other.mx }
	{
		std::cout << "copy ctor\n";
	}

	~exClass16()
	{
		std::cout << "dtor\n";
	}
private:
	int mx;
};

int main()
{
	exClass16 x;
	x.print();
	x.set(45);
	x.print();
}

/*
Output (C++17) :
	default ctor
	mx = 10
	mx = 45
	dtor
*/


//! Example
//! Named Return Value Optimization
class exClass17 {
public:
	void set(int x)
	{
		mx = x;
	}

	void print()const
	{
		std::cout << "mx = " << mx << '\n';
	}

	exClass17() : mx{ 10 }
	{
		std::cout << "default ctor\n";
	}

	exClass17(const exClass17& other) : mx{ other.mx }
	{
		std::cout << "copy ctor\n";
	}

	~exClass17()
	{
		std::cout << "dtor\n";
	}
private:
	int mx;
};

// Named Return Value Optimization
exClass17 func_11()
{
	exClass17 x;

	x.set(67);

	return x;
}

int main()
{
	exClass17 x = func_11();	// copy ctor not called for x

	x.print();
}

/*
Output (C++17) :
	default ctor
	mx = 67
	dtor
*/



//! Example
//! Named Return Value Optimization ( there is a named object )
// there must be a copy ctr function that can be called (even tho it is not called)
std::string get_str()
{
	std::string str;

	return str;
}

int main()
{
	auto s = get_str();	// no move, no copy ctor called
}


//! Why is Named Return Value Optimization important?
//		- cost benefits are much more than those of move or copy operations

// This optimization is not mandatory.
// Sometimes the compiler may not do this optimization.

// example
class exClass18 {
	// cost reduced for these two since pointers are also copied
	std::string s;
	std::vector<int> v;

	// no cost reduction for array
	int ar[100];

};

exClass18 fucnt()
{
	exClass18 m;
	return m;
}

int main()
{
	exClass18 x = fucnt();	// if the compiler doesn't do the optimization then 'move ctor' is called for x
}


//! Example

class exClass19 {
public:
	char buf[100]{};
};

exClass19 func_12()
{
	exClass19 m;
	std::cout << "&m = " << &m << "\n";
	return m;
}

int main()
{
	exClass19 x = func_12();
	std::cout << "&x = " << &x << "\n";
}

/*
Output (Visual Studio):
	&m = 000000A410F7F8D8
	&x = 000000A410F7F700
*/

/*
Output (Onlinegdb):
	&m = 0x7ffd9fd5ed90
	&x = 0x7ffd9fd5ed90
*/

//! Example

class exClass20 {
public:
	exClass20(int x)
	{
		std::cout << "exClass20(int)\n";
	}

	exClass20(const exClass20&)
	{
		std::cout << "copy ctor\n";
	}
};

exClass20 func_13()
{
	exClass20 x(34);
	std::cout << "&x = " << &x << "\n";

	return x;
}

int main()
{
	exClass20 y = func_13();

	std::cout << "&y = " << &y << "\n";

}
/*
Output:
	exClass20(int)
	&x = 00000040E28FF804
	&y = 00000040E28FF804
*/

//

//! Conversion Constructor

//! Example on Conversion Constructor
class exClass21 {


};

int main()
{
	int ival = 10;

	exClass21 m;

	m = ival;	// syntax error, no implicit conversion from int to exClass21 type
	// type mis-match
}


//! Example on Conversion Constructor
//! User-Defined Conversion
class exClass22 {
public:
	exClass22() {}
	exClass22(int x)
	{
		std::cout << "exClass22(int x) x = " << x << "\n";
	}
};

int main()
{
	int ival = 10;

	exClass22 m;

	m = ival;
	// what the compiler does:
	// exClass22 temp{ival};	
	// m = temp;

	// Since there's no direct way to assign an int to an object of exClass22, 
	// the compiler looks for ways to make the assignment work. 
	// It finds that exClass22 has a constructor that takes an int, 
	// so it uses that constructor to implicitly create a temporary exClass22 object initialized with ival.
}

/*
Output:
	exClass22(int x) x = 10
*/

//! Example on Conversion Constructor
//! User-Defined Conversion
class exClass23 {
public:
	exClass23() {}
	exClass23(int x)
	{
		std::cout << "exClass23(int x) x = " << x << "\n";
	}
	~exClass23()
	{
		std::cout << "exClass23 dtor this = " << this << "\n";

	}
};

int main()
{
	int ival = 10;

	exClass23 m;

	m = ival;
	// destructor of the temporary object the compiler creates is called
	(void)getchar();

}

/*
Output:
	exClass23(int x) x = 10
	exClass23 dtor this = 00000003FBAFF994

	exClass23 dtor this = 00000003FBAFF8B4
*/



//! Example on Conversion Constructor
//! User-Defined Conversion
class exClass24 {
public:
	exClass24() {}
	exClass24(int x)
	{
		std::cout << "exClass24(int x) x = " << x << "\n";
		std::cout << "exClass24(int x) ctor this = " << this << "\n";
	}
	~exClass24()
	{
		std::cout << "exClass24 dtor this = " << this << "\n";

	}
};

int main()
{
	int ival = 10;

	exClass24 m;

	m = ival;
	// destructor of the temporary object the compiler creates is called
	(void)getchar();

}

/*
Output:
	exClass24(int x) x = 10
	exClass24(int x) ctor this = 00000097EF0FF644
	exClass24 dtor this = 00000097EF0FF644

	exClass24 dtor this = 00000097EF0FF564
*/

//! Example on Conversion Constructor

class exClass25 {
public:
	exClass25()
	{
		std::cout << "default ctor\n";
	}
	exClass25(int x)
	{
		std::cout << "exClass25(int x) x = " << x << "\n";
	}
	~exClass25()
	{
		std::cout << "exClass25 dtor\n";

	}

	exClass25(const exClass25&)
	{
		std::cout << "Copy ctor\n";
	}

	exClass25& operator=(const exClass25&)
	{
		std::cout << "Copy assignment\n";
		return *this;
	}

	exClass25& operator=(exClass25&&)
	{
		std::cout << "Move assignment\n";
		return *this;
	}
};

int main()
{
	int ival = 10;

	exClass25 m;

	m = ival;	// move assignment called because the compiler creates a temporary object which is an rvalue reference

}

/*
Output:
	default ctor
	exClass25(int x) x = 10
	Move assignment
	exClass25 dtor
	exClass25 dtor
*/

//! Example on Conversion Constructor

class exClass26 {
public:
	exClass26();

	exClass26(int);
};

void func_14(exClass26);

exClass26 func_15()
{
	int i = 5;

	// say, we return 'i' by mistake
	return i;	// the compiler performs implicit conversion
}

void func_16(const exClass26&);

int main()
{
	exClass26 m;
	m = 5;
	int mi = 567;
	// say we make a mistake and instead of 'm' we give 'mi' as parameter to the function
	func_14(mi);	// compiler calls this ctor exClass26(int)

	func_16(mi);	// legal, the temporary object (pr value) can be connected to a const lvalue reference (or rvalue)
}


//! Example on Conversion Constructor

class exClass27 {
public:
	exClass27();

	exClass27(int);
};


int main()
{
	exClass27 m;

	// all legal
	// Standard Conversion necessary
	m = true;
	m = 3.4;
	m = 'A';
}

//! Rule :
//		If the implicit conversion should be done as in the cases below :
//				std con + udc		or		udc + std con
//		then, the compiler must do it.

//! Rule : 
// 		If the implicit conversion should be done as in the cases below :
//				udc + udc
//		then, the compiler does NOT do it.

//! Example
class A {
public:
	A();
	A(int);
};

class B {
public:
	B() = default;
	B(A);
};

int main()
{
	B bx;
	bx = 6;	// error, because it needs two udc
}


//! Example

class String {
public:
	String();
	String(const char*);
};

int main()
{
	String s;
	s = "Eni";
}


//! Example

int main()
{
	using namespace std;

	int ival(456000);

	vector<int> vec;

	vec = ival;		// why?
	//! Explicit Constructor
}