#include <stdio.h>
int main()
{
	/*! Undefined Behavior in C and C++ */

	//! Division by zero
	int val = 5;
	return val / 0;			// undefined behavior

	//! Memory accesses outside of array bounds
	int arr[4] = { 1,2,3,4 };
	return arr[5];			// undefined behavior

	//! Signed integer overflow
	int x = INT_MAX;		// maximum possible integer
	printf("%d", x + 1);	// undefined behavior

	//! Null pointer dereference
	val = 0;
	int ptr = *val;			// undefined behavior

	//! Modification of a string literal
	char* s = "eni";		// stored in read-only section of memory
	s[0] = 'e';				// undefined behavior

	//! Accessing a NULL pointer
	int* ptr;
	printf("%d", *ptr);		// undefined behavior

	//! Misuse of the delete operator with an array allocated using new[]
	// When you allocate an array with new[], you must deallocate it with delete[]. 
	// Using delete on an array can lead to partial deallocation of the array, potentially causing a memory leak.
	auto p = new int[n];	// dynamically allocates memory for an array of 'n' integers
	delete p;				// undefined behavior, 

	//! Undefined behavior in bitwise shifting 
	// Shifting more bits than size of type.
	// Shifting a 32-bit integer by 32 or more bits is undefined behavior.
	// Shifting by a Negative amount is undefined behavior.
	// Left-shifting a negative value is undefined behavior.
	// Shifting into the sign bit is undefined behavior.
	a = x << b;

	//? Dead Code
	//? Inline Optimization

	/* Unspecified Behavior */

	//! Evaluation order of function arguments
	x = fun1() + fun2();		// the compiler can choose to implement it from left-to-right or right-to-left
	a = fun1() + fun2() * 5;

	//! Implementation - Defined
	// One compiler can execute the code always at the same way, but another compiler may do it differently

	//! Arithmetic vs Logical Shifting
	// The main difference lies in how the sign bit is treated, especially in right shifts. 
	// Logical shifts do not consider the sign bit and always fill with zeroes, 
	// while arithmetic right shifts fill with the sign bit to preserve the number's sign.

/*! Types of Char */
//	1. signed char
//	2. unsigned char
//	3. char				(depended on the compiler if it is signed or unsigned)
	char x = 5;


	/*! Type Systems */

		/*
		Dynamic Typing : type checking is performed at runtime.
		For example, Python is a dynamically typed language.
		It means that the type of a variable is allowed to change over its lifetime.

		Static Typing : type checking is performed during compile time. (C, C++, C#, Java)
		It means that the type of a variable is known at compile time.
		With Static Typing, variables generally are not allowed to change types.

		Duck Typing : the type or the class of an object is less important than the method it defines.
		Using Duck Typing, we do not check types at all.
		Instead we check for the presence of a given method or attribute.
		*/

		// Örtülü Dönüþüm - Implicit Conversion

		/*! Differences between C and C++ */

			// Conversions in C++ are more strict.
	int x = 10;
	int* p = x;		// Legal in C, Syntax error in C++

	// C makes it easy to shoot yourself in the foot. C++ makes it harder, 
	// but when you do it, it blows your whole leg off.

	/*
	'A' : character constant
	'A' : type of expression : signed int ( in C)
							 char (in C++)
	*/

	int* p = malloc(n * sizeof(int));
	// malloc returns a 'void*'
	// legal in C, Syntax Error in C++
	// in C++ there is no implicit conversion void* ---> int*

	char str[4] = "Mert";
	// legal in C, we can't be sure if it is null '\0' terminated byte-stream
	// Syntax Error in C++

	char str[] = "emir";		// 'emir' not saved in FLASH
	const char* p = "emir";		// 2 variables, 'emir\0' which is saved in FLASH and 'p'

	unsigned x = 5;
	// valid in both C and C++ , accepted as default 'unsigned int'
}

func(int x)
{
	return x + 5;
	// in C : implicint 'int' 
	// in C++ : implicing 'int' is not supported
}

// Old-style function definition in C
// Syntax Error in C++
double foo(a, b, c);
double a, b, c;
{
	return (a + b + c) / 3;
}