#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <bitset>

//! Example
int main()
{
	using namespace std;

	vector vec{ 1,5,7,9,1,4,3,6,1 };
	//..
	vector<int>::iterator iter = find(vec.begin(), vec.end(), 9);

	if (iter != vec.end()) {
		std::cout << "found..." << *iter << '\n';
		// std::cout << "found..." << iter.operator* << '\n';
	}
	else {
		std::cout << "not found..." << '\n';
	}
}
// Output : found...9


//! Example
//! string::npos
// It is a constant static member value with the highest possible value for an element of type size_t.
// It actually means until the end of the string.
// It is used as the value for a length parameter in the string’s member functions.
// As a return value, it is usually used to indicate no matches.
int main()
{
	using namespace std;

	cout << string::npos << '\n';	// 18446744073709551615
}


//! Example
int main()
{
	using namespace std;
	int x = -1;
	unsigned y = -1;
	cout << "x = " << x << "\n";	// 'x = -1'
	cout << "y = " << y << "\n";	// y = 4294967295

	cout << bitset<32>(-1);					// 1111111111111111111111111111111111111111111111111111111111111111
	cout << bitset<32>(string::npos);		// 11111111111111111111111111111111
}

//! Example
int main()
{
	using namespace std;
	string str;
	std::cout << "enter some text : ";
	getline(cin, str);
	std::cout << "[" << str << "]";

}

//! Example
int main()
{
	using namespace std;

	string str;
	std::cout << "enter some text : ";
	getline(cin, str);
	std::cout << "[" << str << "]" << '\n';

	// find() function has 5 overloads
	// string::size_type idx = str.find('a');
	// size_t idx = str.find('a');
	auto idx = str.find('a');

	if (idx != string::npos) {
		std::cout << "found idx = " << idx << " " << str[idx] << '\n';
	}
	else {
		std::cout << "not found\n";
	}

}


//! Scope Leakage
int main()
{
	using namespace std;

	string str;
	std::cout << "enter some text : ";
	getline(cin, str);
	std::cout << "[" << str << "]" << '\n';

	{	// nested block
		auto idx = str.find('a');

		if (idx != string::npos) {
			std::cout << "found idx = " << idx << " " << str[idx] << '\n';
		}
		else {
			std::cout << "not found\n";
		}
	}
}

//! If statement with Initializer
// if ( int x = foo() ; x > 10) { }

int foo();

int main()
{
	using namespace std;

	int x = foo();
	if (x > 10) {
		x++;
		//..
	}
	else {
		x--;
	}

	x = 5;
}

//! Instead you can do this...
int main()
{
	if (int x = foo(); x > 10) {	//C++17
		x++;
		//..
	}
	else if (x > 20) {
		x--;
	}
	else {
		x--;
	}	// scope of 'x' finishes here

	x = 5;	// syntax error

}

//! Example of If statement with Initializer
int main()
{
	using namespace std;

	string str;
	std::cout << "enter some text : ";
	getline(cin, str);
	std::cout << "[" << str << "]" << '\n';

	if (auto idx = str.find('a'); idx != string::npos) {
		std::cout << "found idx = " << idx << " " << str[idx] << '\n';
	}
	else {
		std::cout << "not found\n";
	}

	++idx;	// syntax error
}


//! Example

int foo2();

int main()
{
	using namespace std;

	if (int x = foo2()) {	// C++98
		//..
		++x;
	}
	else {
		//..
		--x;
	}

}

//! Example

int* foo3();

int main()
{
	using namespace std;

	if (int* p = foo3()) {		// legal
		cout << *p;
	}

}

//! Example

int* foo4();

int main()
{
	using namespace std;

	while (int* p = foo4()) {	// legal
		cout << *p;
	}

	// loop finished when the return value of foo() is nullptr

}

//! Example

int foo5();
void bar(int);
void baz(int);
void bom(int);

int main()
{
	using namespace std;

	switch (int x = foo())	// legal
	{
	case 1: bar(x); break;
	case 2: baz(x); break;
	default: bom(x); break;
	}

}

//! .find() function overloads
int main()
{
	using namespace std;

	string str;
	std::cout << "enter some text : ";
	getline(cin, str);
	std::cout << "[" << str << "]" << '\n';

	string name{ "eni" };

	auto idx = str.find('e');
	auto idx = str.find("efe");
	auto idx = str.find("efe", 5);
	auto idx = str.find(name);
	//...

	if (idx != string::npos) {
		std::cout << "found idx = " << idx << " " << str[idx] << '\n';
	}
	else {
		std::cout << "not found\n";
	}

}

//! .rfind()
int main()
{
	using namespace std;

	string str;
	std::cout << "enter some text : ";
	getline(cin, str);
	std::cout << "[" << str << "]" << '\n';		// [ankara]

	string name{ "eni" };

	// search is done starting from the end
	auto idx = str.rfind('a');
	if (idx != string::npos) {
		std::cout << "found idx = " << idx << " " << str[idx] << '\n';	// idx = 5
	}
	else {
		std::cout << "not found\n";
	}
}


//! .find_first_of()
int main()
{
	using namespace std;

	string str;
	std::cout << "enter some text : ";
	getline(cin, str);
	std::cout << "[" << str << "]" << '\n';	// mahir

	string name{ "eni" };

	// 
	if (auto idx = str.find_first_of("eiou"); idx != string::npos) {
		std::cout << "found idx = " << idx << " " << '\n';		// idx = 3 (finds 'i' first)
	}
	else {
		std::cout << "not found\n";
	}
}

//! .find_first_not_of()
int main()
{
	using namespace std;

	string str;
	std::cout << "enter some text : ";
	getline(cin, str);
	std::cout << "[" << str << "]" << '\n';

	string name{ "eni" };

	// 
	if (auto idx = str.find_first_not_of("eiou"); idx != string::npos) {
		std::cout << "found idx = " << idx << " " << '\n';
	}
	else {
		std::cout << "not found\n";
	}
}
/*
enter some text : eeeiiiooonecati
[eeeiiiooonecati]
found idx = 9
*/

//! .find_last_of()
int main()
{
	using namespace std;

	string str;
	std::cout << "enter some text : ";
	getline(cin, str);
	std::cout << "[" << str << "]" << '\n';

	string name{ "eni" };

	// 
	if (auto idx = str.find_last_of("eiou"); idx != string::npos) {
		std::cout << "found idx = " << idx << " " << '\n';
	}
	else {
		std::cout << "not found\n";
	}
}
/*
enter some text : eiouuutrseeolks
[eiouuutrseeolks]
found idx = 11		(index of 'o')
*/


//! .find_last_not_of()
int main()
{
	using namespace std;

	string str;
	std::cout << "enter some text : ";
	getline(cin, str);
	std::cout << "[" << str << "]" << '\n';

	string name{ "eni" };

	// 
	if (auto idx = str.find_last_not_of("eiou"); idx != string::npos) {
		std::cout << "found idx = " << idx << " " << '\n';
	}
	else {
		std::cout << "not found\n";
	}
}
/*
enter some text : eeeoouupi
[eeeoouupi]
found idx = 7		(index of 'p')
*/


//! Example
int main()
{
	using namespace std;

	string str;
	std::cout << "enter some text : ";
	getline(cin, str);
	std::cout << "[" << str << "]" << '\n';

	// as container
	if (auto iter = find(str.begin(), str.end(), 'a'; iter != str.end()) {

	}
}

//! string::npos can be used as end of the string


//! .contains()		C++23
int main()
{
	using namespace std;

	string str;
	std::cout << "enter some text : ";
	getline(cin, str);
	std::cout << "[" << str << "]" << '\n';

	// returns bool
	if (str.contains("burak"));
}


//! .starts_with() & .ends_with()	C++20
int main()
{
	using namespace std;

	string str;
	std::cout << "enter some text : ";
	getline(cin, str);
	std::cout << "[" << str << "]" << '\n';

	// returns bool
	str.starts_with("necati");
	str.ends_with("necati");
}


//! Mutator Functions

std::string foo6();
int main()
{
	using namespace std;

	string name{ "ahmet korkmaz" };
	string str{ "necati ergin" };

	str = name;			// copy assignment called
	str = move(name);	// move assignment called
	str = foo6();		// move assignment called

	str = 'A';			// legal

	char c1{ 'm' };
	char c2{ 'u' };
	char c3{ 's' };
	char c4{ 'a' };

	str = { c1,c2,c3,c4 };	// initializer list param
	str = { c2,c3,c1,c4 };	// legal

	str = "mehmet uckun";
}

//! .assign()
int main()
{
	using namespace std;

	string str{ "necati ergin" };
	cout << "[" << str << "]" << '\n';

	str.assign(10, 'f');				// 10 'f' characters
	cout << "[" << str << "]" << '\n';	// [ffffffffff]

	str.assign("pelin uzun");
	cout << "[" << str << "]" << '\n';	// [pelin uzun]

	string name = "mehmet kaygusuz";
	str.assign(name, 7);				// offset is 7
	cout << "[" << str << "]" << '\n';	// [kaygusuz]

	str.assign(name, 1, 2);
	cout << "[" << str << "]" << '\n';	// [eh]

	str.assign(name, 1, string::npos);
	cout << "[" << str << "]" << '\n';	// [ehmet kaygusuz]

}

//! .assign()
int main()
{
	using namespace std;

	string str{ "necati ergin" };
	char s[] = "turgut uyar";
	string name = "mehmet kaygusuz";

	str.assign(s);
	cout << "[" << str << "]" << '\n'; // [turgut uyar]

	str.assign(s, 6);
	cout << "[" << str << "]" << '\n'; // [turgut]

	str.assign(s, s + 6);
	cout << "[" << str << "]" << '\n'; // [turgut]

	str.assign(s + 2, s + 5);
	cout << "[" << str << "]" << '\n'; // [rgu]

}

//! Example
int main()
{
	using namespace std;
	vector cvec{ 'm','u','r','a','t' };
	string str;

	str = cvec;	// illegal, because there is no implicit conversion between different container types

	str.assign(cvec.begin(), cvec.end());	// legal
	cout << "[" << str << "]" << '\n'; // [murat]

}


//! .resize()
int main()
{
	using namespace std;

	vector vec{ 2,6,7,9,3,1,9 };

	cout << "vec.size() = " << vec.size() << '\n';
	vec.resize(17);		// zero-initialized because they come to life with list initialization
	cout << "vec.size() = " << vec.size() << '\n';

	for (auto i : vec) cout << i << " ";	// 2 6 7 9 3 1 9 0 0 0 0 0 0 0 0 0 0
}
/*
vec.size() = 7
vec.size() = 17
2 6 7 9 3 1 9 0 0 0 0 0 0 0 0 0 0
*/


//! .resize()
int main()
{
	using namespace std;

	vector vec{ 2,6,7,9,3,1,9 };

	cout << "vec.size() = " << vec.size() << '\n';
	vec.resize(17, 666);		// added values initialized as 666
	cout << "vec.size() = " << vec.size() << '\n';

	for (auto i : vec) cout << i << " ";	// 2 6 7 9 3 1 9 666 666 666 666 666 666 666 666 666 666
}
/*
vec.size() = 7
vec.size() = 17
2 6 7 9 3 1 9 666 666 666 666 666 666 666 666 666 666
*/


//! .resize()
int main()
{
	using namespace std;
	string str{ "alican" };

	std::cout << "length = " << str.length() << '\n';
	str.resize(10);		// added values initialized as null character
	std::cout << "length = " << str.length() << '\n';

	for (auto i : str) cout << "[" << i << "]" << " ";	// [a] [l] [i] [c] [a] [n] [] [] [] []
}
/*
length = 6
length = 10
[a] [l] [i] [c] [a] [n] [] [] [] []
*/


//! fill ctor
int main()
{
	using namespace std;

	string str(333, '\0');	// fill ctor called

}

//! .resize()
int main()
{
	using namespace std;

	string str{ "ahmet korkmaz" };
	cout << "[" << str << "]" << '\n';
	str.resize(20, '!');
	cout << "[" << str << "]" << '\n';

	str.resize(5);	// deletes elements
}


//! Append
//! .push_back()
int main()
{
	using namespace std;

	string str{ "neco" };

	cout << '[' << str << "]\n";

	str += "can";
	cout << '[' << str << "]\n";

	string s{ "oglu" };
	str += s;
	// cout << (str += s);				// legal
	// auto len = (str += s).length();	// legal
	cout << '[' << str << "]\n";

	str += 'm';
	cout << '[' << str << "]\n";

	str.push_back('!');
	cout << '[' << str << "]\n";

	str += {'1', '4', '7' };
	cout << '[' << str << "]\n";

}
/*
[neco]
[necocan]
[necocanoglu
[necocanoglum]
[necocanoglum!]
[necocanoglum!147]
*/


//! .append()
int main()
{
	using namespace std;

	string str{ "neco" };
	cout << '[' << str << "]\n";

	str.append(10, 'o');
	cout << '[' << str << "]\n";

}

//! .insert()
int main()
{
	using namespace std;

	string str{ "necati" };

	// this function returns *this
	// first parameter is index 
	str.insert(3, "XYZ");
	cout << '[' << str << "]\n";	// [necXYZati]

	str.insert(str.size(), "XYZ");
	cout << '[' << str << "]\n";	// [necXYZatiXYZ]

	str.insert(0, 20, 'A');
	cout << '[' << str << "]\n";	// [AAAAAAAAAAAAAAAAAAAAnecXYZatiXYZ]

}


//! .replace()
int main()
{
	using namespace std;

	string str{ "necati" };
	cout << '[' << str << "]\n";

	// first index
	// replace 3 characters
	// with 20 of 'X'
	str.replace(1, 3, 20, 'X');
	cout << '[' << str << "]\n";	// [nXXXXXXXXXXXXXXXXXXXXti]

}

//! All mutator functions return *this.

//! .erase()
int main()
{
	using namespace std;

	string str{ "necati ergin" };
	cout << '[' << str << "]\n";

	// erases everything from 3rd index to end
	str.erase(3);
	cout << '[' << str << "]\n";	// [nec]

	// erase 1 char starting from 3rd indec
	str.erase(3, 1);
	cout << '[' << str << "]\n";	// [necti ergin]

	// erase last char
	str.erase(str.size() - 1);
	cout << '[' << str << "]\n";	// [necati ergi]

}

//! .erase()
int main()
{
	using namespace std;

	string str{ "necatiergin" };
	cout << '[' << str << "]\n";

	str.erase(str.begin());
	cout << '[' << str << "]\n";	// [ecatiergin]

	str.erase(str.begin() + 1);
	cout << '[' << str << "]\n";	// [ncatiergin]

	str.erase(str.end());			// undefined behavior

	str.erase(prev(str.end()));
	cout << '[' << str << "]\n";	// // [necatiergi]

}
//! After 'erase', capacity doesn't 'shrink'.

//! .shrink_to_fit()
int main()
{
	using namespace std;

	string str(100'000, 'A');

	cout << "length = " << str.length() << " cap = " << str.capacity() << "\n";

	str.erase(40);
	// str.resize(40)
	cout << "length = " << str.length() << " cap = " << str.capacity() << "\n";

	str.shrink_to_fit();
	cout << "length = " << str.length() << " cap = " << str.capacity() << "\n";
}
/*
length = 100000 cap = 100015
length = 40 cap = 100015
length = 40 cap = 47
*/


//! .erase()
int main()
{
	using namespace std;

	string str{ "naciye" };
	str.erase(1, 3);	// index interface
	std::cout << str << '\n';	// nye

	str.erase(str.begin() + 1, str.begin() + 4);	// iterator interface
	std::cout << str << '\n';

	str.erase();	// same as : str.erase(0, std::string::npos);

}

//! .clear()
int main()
{
	using namespace std;

	string str{ "necati ergin" };
	std::cout << str << '\n';
	cout << "length = " << str.length() << " cap = " << str.capacity() << "\n";

	str.clear();

	std::cout << str << '\n';
	cout << "length = " << str.length() << " cap = " << str.capacity() << "\n";
}
/*
necati ergin
length = 12 cap = 15

length = 0 cap = 15
*/

//! All ways to erase a string
int main()
{
	using namespace std;

	string str{ "necati ergin" };

	str.clear();
	str.erase();
	str.erase(0);
	str.erase(0, string::npos);
	str = "";
	str.resize(0);
	str.erase(str.begin(), str.end());
	str = string{};
	str.assign(0, '\n');
	str.assign("");
	str = {};
	//..

	std::cout << str << '\n';
	cout << "size = " << str.size() << "\n";

}

//! .pop_back()
int main()
{
	using namespace std;

	string str{ "ahmet korkmaz" };

	while (!str.empty()) {
		std::cout << str << '\n';
		str.pop_back();

	}
}

/*
Output:
ahmet korkmaz
ahmet korkma
ahmet korkm
ahmet kork
ahmet kor
ahmet ko
ahmet k
ahmet
ahmet
ahme
ahm
ah
a
*/


//! 
int main()
{
	using namespace std;

	string str{ "ahmet korkmaz" };

	while (!str.empty()) {
		std::cout << str << '\n';
		str.erase(0, 1);
		// str.erase(str.begin());

	}
}
/*
Output:
ahmet korkmaz
hmet korkmaz
met korkmaz
et korkmaz
t korkmaz
 korkmaz
korkmaz
orkmaz
rkmaz
kmaz
maz
az
z
*/

//! .substr()
int main()
{
	using namespace std;
	string str{ "ahmet korkmaz" };

	auto s = str.substr(0, 3);
	std::cout << "[" << str << "]\n";	// [ahm]
}

//! .substr() is costly
int main()
{
	using namespace std;
	string str(100'000, 'A');

	// new allocation occurs
	auto s = str.substr(3000, 5000);

}

//! string_view
int main()
{
	using namespace std;
	// holds pointers to start and end of string
	string_view sv("murat can korkmaz");

}

//!
void strmpr(const char* p);
int main()
{
	using namespace std;

	string s{ "niyazi tastanoglu" };
	//..
	strmpr(s);			// syntax error, because there is no implicit conversion from string to const char*
	strmpr(s.c_str());	// c_str() gives the address where the text is places in memory, NTBS

	puts(s);			// syntax error
	puts(s.c_str());

	char ar[1000];
	strcpy(ar, s.c_str());

	puts(s.data());		// ??



}

//! Example
int main()
{
	using namespace std;
	string s{ "niyazi tastanoglu" };
	cout << "cap : " << s.capacity() << '\n';
	// c_str() returns const char*
	auto cptr = s.c_str();
	cout << cptr << '\n';

	s += "necati ergin oglu";
	cout << "cap : " << s.capacity() << '\n';	// capacity increases, reallocation occured
	cout << cptr << '\n';	// dangling pointer

}
/*
Output:
	cap : 31
	niyazi tastanoglu
	cap : 47
	¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦S
*/

//! Example
int main()
{
	using namespace std;
	string s{ "niyazi tastanoglu" };

	auto p1 = s.c_str();
	auto p2 = s.data();
	auto p3 = &s[0];
	// *s.begin();	char
	auto p4 = &*s.begin();	// address
	// s[0];		 returns reference

	cout << static_cast<const void*>(p1) << '\n';
	cout << static_cast<const void*>(p2) << '\n';
	cout << static_cast<const void*>(p3) << '\n';
	cout << static_cast<const void*>(p4) << '\n';

}
/*
00000172DA0DF9F0
00000172DA0DF9F0
00000172DA0DF9F0
00000172DA0DF9F0
*/
