#include <iostream>
#include <string>
#include <vector>

//! Example
class MyClass {
	class Eni;
};

class Eni {
	// this is the definition of another class
};

class MyClass :Eni {
	// this is definition of the nested type
};

//! Pimpl Idiom  (Pointer to IMPLementation)
// (Opaque Pinter Idiom, Handle Body Idiom)
// It is a technique used for separating implementation from the interface.
// It minimizes header exposure and helps programmers to reduce build dependencies
// by moving the private data members in a separate class and accessing them through an opaque pointer.

// ABI (Abstract Binary Interface) 

//! Example

// we need to include headers if public, this increases compile time
#include "tlib.h"
#include "ulib.h"
#include "zlib.h"

class MyClass2 {

public:
	T tx;
	U ux;
	z zx;

};

// no need to include headers if private
class MyClass2 {

private:
	T tx;
	U ux;
	z zx;
};


//! Example on Pimpl Idiom

//
class A {}; // these can't be incomplete types
class B {};
class C {};

// myclass.h
class MyClass3 {

private:
	A ax;
	B bx;
	C cx;
	int mx, my;
};


//! Example

// myclass.h
class MyClass4 {
public:
	MyClass4();
	void foo();
	void bar();
private:
	struct Pimpl; //	 nested incomplete type
	Pimpl* mp;
};


// myclass.cpp
// #include myclass.h"

class A {};
class B {};
class C {};

struct MyClass4::Pimpl
{
	A ax;
	B bx;
	C cx;
	int mx, my;
};

// this has high cost, because everytime an object of MyClass4 is created, a Pimpl Object with dynamic lifespan is created
// dynamic allocation is costly
MyClass4::MyClass4() : mp{ new Pimpl }
{
	//
}

void MyClass4::foo()
{
	mp->ax;
}

//

//! Containers
//		sequence containers
//				vector, deque, string, array, list, forward_list
//		associative containers
//		unordered associative containers


//! Dynamic Array 
// add screenshots
//! Small Buffer Optimization (SBO) 
//! Small String Optimization


//! String Class

template <typename C, typename T = std::char_traits<C>, typename A = std::allocator<C>>
class BasicString {

};

int main()
{
	using namespace std;

	basic_string <char, char_traits<char>, allocator<char>> str;
	basic_string<char> str;
}

using String = std::basic_string<char>;

//! Example
int main()
{
	using namespace std;
	string str{ "hello world" };
}

// NTBS - Null Terminated Byte-String 
// cstring - means it has null character in the end
// 




//! string::size_type
// 1) length of text
// 2) index value
//		- index interface		         : 'find' functions return size_type
//		- iterator interface
// 3) this many of this character		: str.assign(n, 'x');

int main()
{
	using namespace std;

	string str;
	string::size_type len = str.length();
	size_t len = str.length();
	auto len = str.length();

	auto len = str.size();
	// both 'size' and 'length' functions return the size of the text
	// no difference btw the two

}

//! Parameter Patterns

// .func(const std::string &)		function wants string as parameter		(lvalue expression argument)
// .func(std::string &&)			function wants string as parameter		(rvalue expression argument)

//! substring parameter
// .func(const std::string &str, size_type idx)		function wants string and the start idex as parameter
//  if first parameter is enishkrepi, second parameter is 2 then the function holds 'shkrepi'

// .func(const std::string &str, size_type idx, size_type n)		function wants string, the start idex and number of characters as parameter
//  if first parameter is enishkrepi, second parameter is 2, third parameter is 2 then the function holds 'sh'

// .func(char);

//! fill parameter
// .func(string::size_type, char);		this many of this character

// .func(const char*);			starting from const 'char address' till NULL character (it must be cstring - NTBS)
//							if i pass the address but there is no NULL character in the text in that address -> Undefined Behavior  

//! data parameter
// .func(const char*, string::size_type);	starting from 'const char address', 'string::size_type' many characters
//										is the string has a sie of 20, but second parameter is 21 -> undefined behavior

//! range parameter
// .func(const char* ps, const char* pe)		from 'ps' address to 'pe' address 
// char str[] = "helloworld";
// if we pass to the function 'str' and 'str + 3' as parameters -> 'hell'

//! initializer list parameter
// ::func(std::initializer_list<char>)
// we can pass this {'a','t','r'} as parameter


// ! String Class Constructors

//! Default Ctor
int main()
{
	using namespace std;

	// default ctor is called in the two cases below (empty string is created)
	string s1;		// default initialization
	string s2{};	// value init

	cout << "s1.length() = " << s1.length() << '\n';
	cout << "s2.length() = " << s2.length() << '\n';
	cout << "s2.sizw() = " << s2.size() << '\n';

	// empty() function returns a 'bool'
	cout << "is empty? " << boolalpha << s1.empty() << '\n';
	s1 = "hey";
	cout << "is empty? " << boolalpha << s1.empty() << '\n';

}

/*
Output:
	s1.length() = 0
	s2.length() = 0
	s2.sizw() = 0
	is empty? true
	is empty? false
*/


//! Cstring param Ctor

int main()
{
	using namespace std;

	string s1{ "hello" };
	cout << s1;
	operator<<(cout, s1);
	// Output: hellohello
}

//! Example
// default ctor is not explicit
void func(std::string);

std::string foo()
{
	return "hey";	// legal
}

std::string foo2()
{
	return {};		// legal
}

void bar(std::string);

int main()
{
	using namespace std;

	std::string str = {};	// legal, default ctor is called

	func("hello");	// legal
	//  constructor allows for the implicit conversion of string literals (which are of type const char[N], 
	// where N is the size of the string including the null terminator) to std::string objects.

	bar({});		// legal
}

//! Example

int main()
{
	using namespace std;

	string s('a');	// syntax error : there is no ctor that takes 'char' as parametere
}

//! Example

int main()
{
	using namespace std;

	string s{ 'a' ,'l','i' };			// initializer list ctor is called
	cout << "s = " << s << '\n';		// s = ali
}

//! Uniform Initialization

class MyClass5 {
public:
	MyClass5(int);
};
int main()
{
	using namespace std;
	MyClass5 m1 = 12;	// copy init
	MyClass5 m2(12);	// direct init
	MyClass5 m3{ 12 };	// direct list init
	// the only difference is that in 'direct list init' narrowing conversion is syntax error
}

//! Example
class MyClass6 {
public:
	MyClass6(std::initializer_list<int> list)
	{
		std::cout << "MyClass6(std::initializer_list<int>\n";
		std::cout << "size = " << list.size() << '\n';
		for (auto i : list)
			std::cout << i << ' ';
		std::cout << '\n';
	}
};

int main()
{
	using namespace std;
	int ival = 453;
	MyClass6 m1{ 12,45,67,98 ,9,12, ival };		// legal

	//MyClass6 m2 = { 12,45,67,98 };	// legal
	//MyClass6 m3{ 12 };				// legal

	// for a string is also the same case:
	string str{ 'e','n','i' };
	// there is 'std::initializer_list<char> list' as parameter in ctor
}
/*
Output:
	MyClass6(std::initializer_list<int>
	size = 7
	12 45 67 98 9 12 453
*/

//! Example
class MyClass7 {
public:
	MyClass7(std::initializer_list<int> list)
	{
		std::cout << "MyClass7(std::initializer_list<int>\n";
		std::cout << "size = " << list.size() << '\n';
		for (auto i : list)
			std::cout << i << ' ';
		std::cout << '\n';
	}

	MyClass7(int x)
	{
		std::cout << "MyClass7(int x) x = " << x << '\n';
	};
};

int main()
{
	using namespace std;

	MyClass7 m1(25);		// legal
	// Output : MyClass7(int x) x = 25

	MyClass7 m2{ 25 };	// legal, initializer list ctor called
	/*
	Output:
	MyClass7(std::initializer_list<int>
	size = 1
	25
	*/
}

//! Example
int main()
{
	using namespace std;

	string str{ 'A' };	// legal
	string str('A');	// syntax error

	string str{ 'A','K' };	// legal, output : AK

	// A is 97 in ASCII, it will print out 97 Ks
	string str('A', 'K');	// legal, field ctor called
	// Output: KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK

	string str{ 34,'A' };
	// Output : "A
}


//! Example
int main()
{
	using namespace std;

	string s1{ 'A' };
	string s2(1, 'A');
	string s3("A");

	cout << s1 << s2 << s3;		// Ouput: AAA
}


//! Copy Ctor
int main()
{
	using namespace std;

	string str = "today is march 16th";
	// copy ctor called
	auto s1 = str;
	auto s2(str);
	auto s3{ str };
}


//! Move Ctor
int main()
{
	using namespace std;

	string str = "today is march 16th";
	// move ctor called
	string s2 = std::move(str);
}

//! Sub-string param
int main()
{
	using namespace std;
	string s1 = "march16th";
	// sub-string param
	string s2(s1, 2);		// Output : [rch16th]
	cout << '[' << s2 << ']';

	string s3(s1, 2, 3);	// Output : [rch]
	cout << '[' << s3 << ']';

}

//! Data Ctor
int main()
{
	using namespace std;

	char str[] = "hello world";
	string s1{ str };
	string s2{ str,6 };
	string s3{ str + 3,3 };
	string s4{ str + 7,9 };	// undefined behavior

	cout << '[' << s1 << ']' << '\n';
	cout << '[' << s2 << ']' << '\n';
	cout << '[' << s3 << ']' << '\n';
	cout << '[' << s4 << ']' << '\n';

	/*
	Output:
		[hello world]
		[hello ]
		[lo ]
		[orld╠╠╠╠]
	*/

}

//! Range Ctor
int main()
{
	using namespace std;

	char str[] = "im tired";
	string str1{ str,str + 4 };
	string str2(str, str + 4);

	std::cout << '[' << str1 << ']' << '\n';
	std::cout << '[' << str2 << ']' << '\n';

	/*
	Output:
		[im t]
		[im t]
	*/

}

//! Example
// #include <vector>
int main()
{
	using namespace std;
	vector cvec{ 'a','s','l','a','n' };

	string str{ cvec.begin(),cvec.end() };
	cout << str << '\n';
	// Output: aslan
}

//! Capacity Function

int main()
{
	using namespace std;
	string str{ "hello world" };
	str += str;
	str += "its march already";

	cout << "str.length() = " << str.length() << '\n';		// 39
	cout << "str.capath() = " << str.capacity() << '\n';	// 47 thus there is room for 8 more characters so that the compiler doesnt do re-allocation

	str += "12345678";
	cout << "str.length() = " << str.length() << '\n';
	cout << "str.capacity() = " << str.capacity() << '\n';

	cout << static_cast<void*>(str.data()) << "\n";

	str += "hey again";
	cout << "str.length() = " << str.length() << '\n';
	cout << "str.capacity() = " << str.capacity() << '\n';	// capacity increased
	cout << static_cast<void*>(str.data()) << "\n";			// address will be different because reallocation occured
}
/*
Output:
	str.length() = 39
	str.capath() = 47
	str.length() = 47
	str.capacity() = 47
	000001B2138C19E0
	str.length() = 56
	str.capacity() = 70
	000001B2138BC220
*/

//! Reallocation takes time.
//! Reallocation invalidates pointers.

//! Why is Capacity important?
//		- determines when reallocation shall occur
//		- .reserve()

int main()
{
	using namespace std;

	string str{ "hello world" };
	auto cap = str.capacity();
	int cnt{};

	// instead of doing this, we can reserve capacity in the beginning
	for (int i = 0; i < 1'000'000; ++i)
	{
		str += 'a';
		if (str.capacity() != cap) {
			std::cout << ++cnt << ".reallocation new capacity is " << str.capacity() << '\n';
			cap = str.capacity();
		}
	}
}
/*
Output:
	1.reallocation new capacity is 31
	2.reallocation new capacity is 47
	3.reallocation new capacity is 70
	4.reallocation new capacity is 105
	5.reallocation new capacity is 157
	6.reallocation new capacity is 235
	7.reallocation new capacity is 352
	8.reallocation new capacity is 528
	9.reallocation new capacity is 792
	10.reallocation new capacity is 1188
	11.reallocation new capacity is 1782
	12.reallocation new capacity is 2673
	13.reallocation new capacity is 4009
	14.reallocation new capacity is 6013
	15.reallocation new capacity is 9019
	16.reallocation new capacity is 13528
	17.reallocation new capacity is 20292
	18.reallocation new capacity is 30438
	19.reallocation new capacity is 45657
	20.reallocation new capacity is 68485
	21.reallocation new capacity is 102727
	22.reallocation new capacity is 154090
	23.reallocation new capacity is 231135
	24.reallocation new capacity is 346702
	25.reallocation new capacity is 520053
	26.reallocation new capacity is 780079
	27.reallocation new capacity is 1170118
*/

//! Example

int main()
{
	using namespace std;

	string str{ "hello world" };
	auto cap = str.capacity();
	int cnt{};

	str.reserve(800'000u);
	for (int i = 0; i < 1'000'000; ++i)
	{
		str += 'a';
		if (str.capacity() != cap) {
			std::cout << ++cnt << ".reallocation new capacity is " << str.capacity() << '\n';
			cap = str.capacity();
		}
	}
}
/*
Output:
	1.reallocation new capacity is 800015
	2.reallocation new capacity is 1200022
*/


//! Example
int main()
{
	using namespace std;

	string str{ "hello world what is going on here" };

	auto ptr = str.data();
	str.append(1000, 'a');
	cout << ptr << '\n';	// undefined behavior because ptr is dangling pointer

}
/*
Output:
	¦¦¦¦¦¦¦¦¦¦¦¦¦
*/

//! Small Buffer Optimization
void* operator new(std::size_t sz)
{
	std::cout << "operator new called for size of : " << sz << "\n";

	if (sz == 0)
		++sz;

	if (void* ptr = std::malloc(sz))
		return ptr;

	throw std::bad_alloc{};
}

void operator delete(void* ptr) noexcept
{
	std::cout << "operator delete called for the address of : " << ptr << '\n';
	std::free(ptr);
}

int main()
{
	using namespace std;

	string str1(10, 'A');		// operator new doesnt get called because of small buffer optimization (depends on compiler)
	string str2(16, 'A');		// operator new gets called
}


//! Example
int main()
{
	using namespace std;

	string str = "Hello World";

	for (size_t i{}; i < str.size(); ++i)
	{
		cout << str[i] << ' ';
	}
}
// Output: H e l l o   W o r l d

//! Example
int main()
{
	using namespace std;

	string str = "Hello World";
	cout << str << '\n';
	str[0] = 'W';
	str[2] = 'L';

	cout << str << '\n';
}
// Output:	Hello World
//			WeLlo World

//! Example
int main()
{
	using namespace std;

	const string str = "Hello World";
	str[0] = 'W';	// syntax error

}

//! Example
int main()
{
	using namespace std;

	string str = "Hello World";
	auto n = str[72];
	cout << n << '\n';	// undefined behavior
}

//! Example
int main()
{
	using namespace std;

	const string str = "Hello World";

	try {
		auto n = str[72];
	}
	catch (const std::exception& ex) {
		std::cout << "exception caught: " << ex.what() << '\n';		// no exception caught
	}
}

//! Example
int main()
{
	using namespace std;

	const string str = "Hello World";

	try {
		auto n = str.at(72);
		// std::out_of_range exception
	}
	catch (const std::exception& ex) {
		std::cout << "exception caught: " << ex.what() << '\n';		// exception caught: invalid string position
	}

}

//! Example
int main()
{
	using namespace std;

	const string str = "Hello World";

	for (auto iter = str.cbegin(); iter != str.cend(); ++iter) {
		cout << *iter << "\n";
	}

}

/*
Output:
H
e
l
l
o

W
o
r
l
d
*/


//! Example
int main()
{
	using namespace std;

	string str = "Hello World";

	//! Range Based For Loop
	for (char c : str) {	// no change in str because c is local variable
		++c;
	}
	cout << str << '\n';
}

/*
Output:
		Hello World
*/

//! Example
int main()
{
	using namespace std;

	string str = "Hello World";

	//! Range Based For Loop
	for (char& c : str) {	// str changes
		++c;
	}
	cout << str << '\n';
}

/*
Output:
		Ifmmp!Xpsme
*/

//! Example
int main()
{
	using namespace std;

	string str = "Hello World";

	//! Reverse String
	for (auto iter = str.rbegin(); iter != str.rend(); ++iter) {
		cout << *iter;
	}
}
/*
Output:
		dlroW olleH
*/

//! Example
int main()
{
	using namespace std;

	string str = "Hello";
	cout << str << '\n';

	str.front() = 'd';
	str.back() = 'i';

	cout << str << '\n';
}
/*
Output:
		Hello
		delli
*/

//! Other Classes :
//		string_view
//		std::regex

//! Example
int main()
{
	using namespace std;

	string str(100000, 'A');

	cout << "str.length() = " << str.length() << '\n';
	cout << "str.capacity() = " << str.capacity() << '\n';

	str.erase(1);	// erases all characters except from 1
	cout << "str.length() = " << str.length() << '\n';
	cout << "str.capacity() = " << str.capacity() << '\n';	// capacity stays the same

	str.shrink_to_fit();
	cout << "str.capacity() = " << str.capacity() << '\n';
}
/*
Output:
	str.length() = 100000
	str.capacity() = 100015
	str.length() = 1
	str.capacity() = 100015
	str.capacity() = 15
*/

