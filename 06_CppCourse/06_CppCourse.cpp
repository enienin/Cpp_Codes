#include <iostream>
#include <vector>

/*! nodiscard attribute */
// Adds [[nodiscard]] attributes (introduced in C++17) to member functions 
// in order to highlight at compile time which return values should not be ignored.

[[nodiscard]] int foo()
{
	return 1;
}

int main() {

	foo();				// warning here
	int a = foo();		// ok
}

/*! Function Overloading */
// More than one function has the same name in same scope but different parameters.
// in C, you can't give more than one function the same name.
// during compilation, the compiler decides to which function to bind
// Compile Time	- static binding		(early binding)
// Run Time		- dynamic binding		(late binding)

// Function overload resolution
void func(int, int, int);
func(1, 2);		// Syntax Error in C

//! Default Argument (Varsayýlan Argüman)
// Why is Default Argument mechanism needed?
void funct(int, int, int = 0);
int main()
{
	funct(1, 2); // ok
}

void func(int, int = 5, int);	// error
// the compiler expects all the arguments on the right of the default argument to be default arguments

int main()
{
	int x = 10;
	int y = 50;
	int z = x++ + y;	//! maximum munch rule
}

void func(const char *= "error");	//? error
void func(const char* = "error");	//! okay


//! example
void foo(int = 1, int = 2, int = 3);

int main()
{
	foo(50, 60, 70);
	foo(50, 60);
	foo(50);
	foo();
}
void foo(int x, int y, int z)
{
	std::cout <<
}


//! example
int foo(int = 1);
void bar(int x, int y = foo());	// int y = foo(1)
int main()
{
	bar(10);
}


//! example
func(3, , 7);	// error


//! example
int x = 10;
void func(int = ++x)
{

}
int main()
{
	func();	// func(++x)
	func();	// func(++x)
	func();	// func(++x)
	func();	// func(++x)

	std::cout << "x = " << x << '\n';	// 13
}


//! exmaple
// syntax error
void foo(int, int, int = 3);
void foo(int, int, int = 3);


//! example

//pelin.h
void func(int, int, int);

// caner.cpp
// #include "<pelin.h>"
void func(int, int, int = 5);	// ok, no syntax error

//! example

//pelin.h
void func(int, int, int = 10);

// caner.cpp
// #include "<pelin.h>"
void func(int, int = 20, int);	// ok

int main()
{
	func(8);	// func(8, 20, 10)
}


//! example

//pelin.h
void func(int x, int y, int z);
void call_func(int x, int z, int y = 0)		// maliyeti yokturr because the compiler makes optimization
{
	func(x, y, z);
}
int main()
{
	call_func(10, 20);		// func(10, 0, 20);
}

//! example
void func(int, int, int* = nullptr);
void enroll_student(int day, int month, int year = -1);
int main()
{
	enroll_student(2, 3, 2012);
	enroll_student(2, 3);		// current year ??

	int x{};
	func(1, 2, &x);
	func(1, 2);

}

void func(int x, int y, int* ptr)
{
	if (!ptr)
		...
}


//! example
void print_enrollment_date(int day = -1, int mon = -1, int year = -1);
void print_enrollment_date(int day, )
{
	if (year == -1) {
		std::time_t sec{};
		std::time(&sec);
		auto tp = std::localtime(&sec);
		year = tp->tm_year + 1900;
		if (mon == -1) {
			mon = tp->tm_mon + 1;
			if (day == -1) {
				day = tp->tm_mday;
			}
		}
	}
}

/* Function Overloading */
int foo(int, int);
int main() {

	double foo(int); // no fucntion overloading because they are not on the same scope

}

//! Function Signature
// these two have same signature
int foo(int, int);
double bar(int, int);

int foo(double);			// this one has a difference signature from the other two
int foo(int, int = 0);		// different signature from all the others

// For Function Overloading:
//	1. name is the same
//	2. scope is the same
//	3. signature is different

// Here we have 3 function overloading
int foo(int, int);
int foo(double);
int foo(int, int = 0);

//! Redeclaration
int foo(int, int);
int foo(int, int);

//! Syntax Error
// Type mismatch in redeclaration
int foo(int, int);
double foo(int, int);

//! Redeclaration
// Redeclaration is not syntax error, but redifinition is syntax error
int foo(int*);
int foo(const int*);

int foo(int*)
{
	return 1;
}
int foo(const int*)	// 'int foo already has a buddy' error
{
	return 1;
}

//! Function (Const) Overloading
// int foo(T *)
// nt foo(const T *)
int foo(int*);
int foo(const int*);

//! Function (Const) Overloading
// int foo(T &)
// nt foo(const T &)
int foo(int&);
int foo(const int&);

//! Function Overloading
int foo(int, int = 1);
int foo(int);

//! Redeclaration
void func(int* p);
void func(int* const p);

//! Depends on the compiler, Implementation defined
void func(int32_t);
void func(int);

//! Redeclaration
using Dollar = double;
void foo(double);
void foo(Dollar);

//! Function Overloading
void fun(int (*)(int));
void fun(double (*)(int));

// 
void func(int*);
void func(int[]);
void func(int[20]);
void func(int[40]);

//! there are 3 Function Overloads
void func(int**);
void func(int*);
void func(int***);

//! Redeclaration
void func(int());
void func(int(*)());

//! Redeclaration
void func(int(int));
void func(int(*)(int));

//! there are 4 Function Overloads
void func(int(*p)[10]);
void func(int(*p)[11]);
void func(int(*p)[12]);
void func(int(*p)[13]);

//! there are 4 Function Overloads
void func(int(&p)[10]);
void func(int(&p)[11]);
void func(int(&p)[12]);
void func(int(&p)[13]);

//! there are 3 Function Overloads
void func(int*);
void func(int&);
void func(int);

//! there are 3 Function Overloads
void func(char);
void func(signed char);
void func(unsigned char);

//! there are 4 Function Overloads
void func(int*);
void func(double*);
void func(void*);
void func(std::nullptr_t);

// The parameter of a function cannot be an array!!
// The return value of a function cannot be an array!!
void foo(int[20]);	// int[20] is a pointer, not array
// void foo(int *)

//! Redeclaration
void foo(int* []);
void foo(int* [40]);
void foo(int**);


void foo(int(*)[20]);	// this
void foo(int**);
void foo(int[][20]);	// and this redeclarations

// ambiguity
void foo(int);
void foo(long double);
int main() {
	foo(2.5);		// there are two legal selections, syntax error
}


enum color { red, blue, yellow };
void foo(int*);
void foo(void*);
void foo(bool);
void foo(int (*)(int));
void foo(color);

int main() {
	foo(3);
}

