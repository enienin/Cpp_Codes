#include<stdio.h>
#include<stdlib.h>
                /*! Differences between C and C++ */

// in C language this is a valid code
//? warning : 'foo' undefined; assuming extern returning int
// not a valid rule in C++
int main()
{
    foo();      //! default function declaration, assumes 'extern int foo();'
    foo(2,5);
}

//! Function Prototypes
// in C there is a difference between these two declarations
void foo();         // not the same as writing 'void' inside the parantheses
// doesn't mean the function takes no parameters
// it just gives no information about the parameters

void bar(void);     // means the function declaration has no parameters 

void baz(void) {

    foo(1, 2, 3, 4);    // in C: ok, no error
    bar(1, 2, 3, 4);    // warning 'bar' : declared with 'void' parameter list
}

// in C++ there is no difference between these two, means the function takes no parameters
void foo();
void bar(void);

//////////////////////////////////////////////////////////////////////////////////////

//! Difference between C89 and C99

void foo(void) {

    int x = 10;
    ++x;        // the executable statement
    int y = 34; // used to be a syntax error in C89 Standard because it is placed after an executable statement
    // no more an error in C99

}

/////////////////////////////////////////////////////////////////////////////////////

void foo(void) {

    for (int i = 0; i < 10; ++i) {
        int i = 56;         // legal in C, illegal in C++
        printf("%d", i);
    }                       // in C++, the scope of 'i' finishes here
}

void foo(void) {
    for (int i = 0; i < 10; ++i) {
        {
            int i = 56;         // how the C compiler sees it
            printf("%d", i);    // 56 56 56 56 56 56 ...
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////

//!              NAME LOOKUP and SCOPE

//! SCOPE 
//      - is linked to compile time
//      - is linked to names not variables

/*  Types of Scopes in C:
            1. function scope,
            2. file scope,
            3. block scope,
            4. function prototype scope
*/

/*   Types of Scopes in C++:
            1. function scope,
            2. namespace scope,
            3. block scope,
            4. function prototype scope
            5. class scope
*/

//! NAME LOOKUP 
//         - either finishes successfully or unsuccessfully 
//         - unsuccessfully :  compiler can't find the name and we get syntax error
//         - successfully   :  when the compiler comes across the definition or declaration of the name it is searching

//! INTERVIEW QUESTION
int main(void)
{
    int printf = 10;
    printf("merhaba dunya");    // compiler makes name lookup for 'printf' in main function first
    // if compiler doesn't find 'printf' in main, then it searches in global scope
    //! Name Lookup finishes successfully
    //! Syntax Error

    x = 5;   //! 'x' : undeclared identifier
}

// in C++, NAME LOOKUP finishes unsuccessfully :
//          1. if it finds the name in several places and it can't choose between those two "ambiguity" 
//          2. if it can't find the name at all

// NAME LOOKUP - is done only once, if found it finishes
//             - is done on a specific row

//! Example
int x = 10;
void foo() {
    int x();    // compiler doesn't search for the name because it is a declaration itself

    x++;        // compiler searches for this name
    // the 'x' name belongs to the 'foo' function not global 'x' declaration
    //! first name lookup and then contex control
    // name lookup in done ONLY ONCE, and finishes once found
}

//! Example
int x = 56;
int main()
{
    int x = 13;
    x = 6;
}

//! Scope Resolution Operator 
// unary: '::x'  - name lookup in global scope
// binary: a::b

//! Enclosing Block
int x = 56;
int main()
{
    int x = 56;
    {
        int x = 13;
    }
}

// name lookup                  - both in C and C++
//     contex control           - both in C and C++
//          access control      - not done ( during compile time ) in C


//! INTERVIEW QUESTION
int x = 10;
int main() {

    //! Undefined Behavior
    int x = x;              // 'int x' is not looked-up, 'x' is looked-up    
                            // Garbage Value
    
    int x = ::x;            // this is not undefined behavior        
    printf("x = %d\n", x);

}

//! Example
void func1(void) {

    // recursive
    func1();
}

//! Example
void func2(int);
void func2(int x)
{
    func2(x);        // no syntax error 
}

//! Example
void func(int func)     // no syntax error because they are in different scopes
{
    ++func;
}

//! Example
void func(int func)
{
    func(10);           // will search in block scope first and find 'int func'
                        //! contex control error
}

//! Example
void func(int func)
{
    ::func(func);       //! recursive call
                        // automatically searches in global scope (NOT IN THE OUTER SCOPE)
}

////////////////////////////////////////////////////////////////////////////////////////////////

// legality is not morality :D
// C :      weak type control
// C++ :    strict type control

/*!  Expression (ifade) vs Statement (deyim) */ 

int main() {

    int x = 4;

    // ' x + 4 '     expression
    // ' x + 4; '   statement, 'expression statement'
    // printf       expression

    //! Expressions have: 
    //      - data type, 
    //      - value,
    //      - value category

    // 12u      expression of type unsigned int
    // 12L      expression of type long
    // 12.L     expression of type long double 
    // 12.F     expression of type float
    // 12LL     expression of type long long
    
    // 'A'      C : int,    C++ : char
    
    // 10 > 5   in C :      expression of type int ,    value is 1
    //          in C++ :    expression of type bool ,   value is TRUE

    // "pelin"  C :     expression of type char[6]
    //          C++ :   expression of type const char[6]

    char c = 4;
    // c + c        expression of type int
    //! Integral Promotion Rule !!!!!!!!!!!!!!!!!!!!!!!!
    // When evaluating c + c, each char operand is first promoted to int before the addition takes place. 
    // This is due to the integral promotion rule, 
    // which states that smaller integer types (like char) are converted to int in most expressions.

    //! Type Conversions
    int ival = 5;
    // ival + 3     expression of type int
    // ival + 3L    expression of type long
    // ival + 3.    expression of type double
    // ival + 3.f   expression of type float
    // ival + 3.F   expression of type float
    // 12.f + 5.    expression of type double

    int x = 5;     // this is not an expression so we can't talk about value category
    // 'x'          lvalue expression
}

//! An EXPRESSION has
//      data type
//      value
//      value category  : in C  : L value or R value
//                      : in C++: L value, PR value, X value

///////////////////////////////////////////////////////////////////////////

void func(void) {

    char* p = "mert";   // legal in C, in C++ it is a const char[]
    *p = 's';           // undefined behavior

    // 'A'      in C :      character constant, type is signed int
    //          in C++ :    character literal, type is char
}

/*! _Bool */
// in C : _Bool     (doesn't exist in C++ )
// in C : #include <stdbool.h>

int main()
{
    bool flag = true;       // what the compiler in C sees: _Bool flag = 1 defined in stdbool.h
                            //  _Bool type doesn't exist in C++

    flag = false;           // what the compiler in C sees: flag = 0

    bool b = true;          //! in C++ : there is implicit conversion from bool--> other arithmetic int/real numbers
    b = false;

    int x = b;              // legal in C++, implicit conversion

    //! Example
    int x = 435;
    int y = 0;
    bool b1 = x;            // legal in C++, thus b1 will be True (for any non-zero value)
    b1 = y;                 // b1 will be false

    //! Bool is generally 1 byte
 
    bool b = true;          //! &b :  expression of type bool* (a pointer to the type of the variable)
    int x = 10;             //! &x :  expression of type int* (pointer to int)

    //! Example
    int x = 10;
    bool b;
    b = &x;                 // valid, value of b is True, there is implicit conversion from pointer type -> bool type

    int* p = nullptr;
    bool b;
    b = p;                  // valid, value of b is False

}

/*! Zero Initialization in C++: */

int x;                  // initialized as 0
bool b;                 // initialized as false
int* ptr;               // initialized as nullptr

void func() {

    static int x;       // initialized as 0       

    int y = x;          // value of 'x' is 0

    //! these is no implicit conversion from bool type --> pointer type
    bool b = false;
    int* p = b;         // syntax error
}

/*! Logical and Comparison Operators */
int main()
{
    // 10 > 4             expression of type 'bool' in C++, 'int' in C

    bool b = false;
    ++b;                // illegal in C++, legal in C

    int x(5);           // invalid in C, valid in C++
    int x{ 3 };         // invalid in C, valid in C++
    int x{};            // invalid in C, valid in C++

    /*! TYPE CASTING */

    //! in C :       there is implicit conversion between different pointer types 
    //! in C++ :     there is no implicit conversion 

    int x = 5;
    char* p = &x;              // legal in C, compiler gives a warning
    char* p = (char*)&x;       // legal in C

    int x = 5;
    char* p = &x;              // illegal in C++, you should use type casting operators
    char* p = (char*)&x;       // C style cast

    int x = 5;
    int* p = x;                // legal in C
    p = x;                     // legal in C

    int x = 10;
    int y;
    int* p;
    p = x;      // legal in C but wrong, error in C++
    p = &x;     // legal in both
    y = p;      // legal in C, illegal in C++

    
    //! Compatible Types
    int x = 10;
    char* p = (char*)&x;      // legal and not wrong

    int x = 10;
    float* p = (float*)&x;    // legal but wrong because int* is not compatible with float*
}

/*! DECLARATOR vs OPERATOR */

int main() {

    int x = 10, * p = &x;       // * - declarator, & - operator
    *p = 576;                   // * - operator
    int& r = x;                 // & - declarator
    int* p = &x;
    int** ptr = &p;
    ++**ptr;            // expression , 3 operators
    // in *ptr  -   '*' dereferencing operator
    // in **ptr -   the first * is also dereferencing operator
    // '++'     -   pre-increment operator

}

/*! COMMA OPERATOR */

int main()
{
    int x;
    int y = 5;
    int z = 7;
    x = (y, z);             // perfectly legal in C++ , x = 7

}

//! Example
void func3(int a, int b, int c);
void foo(int);

int main() {

    int x = 5, y = 6, z = 12;
    func3(x, y, z);         // comma is not an operator here

    foo((x, y, z));         // there are 2 comma operators, z
}

/*! CONSTNESS */
// The constants in C are the read-only variables whose values cannot be 
// modified once they are declared in the C program.

int main() {

    const int x = 5;

    // Why immutable (changable) variables?
    //      1. intent
    //      2. const correctness

    const int ar[] = { 2,3,5,7,11,13,17,19 };
    // intent of array is understandable
}

//! Example
void print_array1(int* p, size_t size);            // may change the *p unintentionally
void print_array2(const int* p, size_t size);     // more correct to explain intent of function

//! Example
int main()
{
    const int a[] = { 43 , 6, 8, 9 };
    print_array1(a,4);  // illegal in C++ because there is no conversion from 'const int*' to 'int*'
                        // legal in C
      
    const int x;        // legal in C, illegal in C++
                        //! 'const' variables don't get default initialized in C++
}

/*! LINKAGE */
int x = 10;             // external linkage because global
static int x = 10;      // internal linkage
void foo(int);          // external linkage
static void foo(int);   // internal linkage
const int x = 5;        // external linkage in C, internal linkage in C++ because of 'const'
extern const int x = 5; // use 'extern' in C++ if your want 'const' variables to have ''external' linkage

//! Example
int main()
{
    const int x = 5;
    int* p = (int*)&x;
    *p = 78;        // undefined behavior
    //! The C++/C standard forbids modifying a constant value. 
    // Even though you cast away the const-ness with (int*)&x and try to modify 
    // the value pointed by p, the behavior of the program becomes unpredictable.

    /*! CONSTANT POINTERS */
   
    int x = 10;
    int y = 23;

    // top-level const  OR  right-const
    int* const p = &x;      // const pointer to int, pointer is a const itself
    p = &x;                 // syntax error
    *p = 56;                // correct, '*p' is of type 'int'

    // low-level const  OR  left-const
    const int* ptr = &x;    // pointer to const int, same thing as: int const* p = &x;
    *ptr = 30;              // syntax error
    ptr = &y;               // correct

    const int* const pointer = &x;    // const pointer to const int
    pointer = &y;           // syntax error
    *pointer = &y;          // syntax error

    //! Examples
    const int x = 5;
    x = 5;          // syntax error
    const int x;    // syntax error
    const int* x;   // valid
    int* const x;   // syntax error
}

/*! TYPE ALIAS */
typedef int* IPTR;  // IPTR is of type int* (pointer to int)

int main()
{
    IPTR p1, p2, p3;        //! all three are of type 'pointer to int'
    int* p1, p2, p3;        //! only p1 is 'pointer to int'
    int* p1, * p2, * p3;    //! all are 'pointer to int'

    //! INTERVIEW QUESTION
    int x = 10;
    const IPTR p = &x;   // int *const p = &x 
    // means it is a top-level const
    *p = 76;
    p = &y;     // syntax error
}

int x, y, z, t;
int main()
{
    //! Example
    const int* p[] = { &x,&y,&z,&t };     // pointer array
    // 'p' is declared as an array of pointers to 'const int'
    // each element of the array is initialized to point to the address of one of the integers
    p[3] = &y;
    *p[5] = 56; // syntax error

    //! VOID POINTERS
    int x = 10;
    double d = 2.31;
    char str[] = "veysel";

    void* vptr = &x;
    // all valid in C and C++ because there is implicit conversion 'any other type' -> 'void pointer'  
    vptr = &d;
    vptr = str;
    vptr = &vptr;

    //! Example
    void* vptr = x; // legal in C but wrong, syntax error in C++

    int x = 10;
    int* p = &x;
    void* vp = p;
    p = vp;         // legal in C and not wrong, syntax error in C++ must use type conversion

    //! Example
    char* p = malloc(10000);    // syntax error in C++
}

/*! ENUM TYPES */

//      |---> enum tag      |--> enumeration constant
//      |                   |
enum Color { Red, Blue, Orange, Purple };
enum Pos {Off,On,Hold};

// in C++ : Enum Class (Scoped Enum)

struct Nec {
    int x, y;
};

union Data {
    int x;
    double d;
};

int main() {

    enum Color mycolor;     // correct way in C
    struct Nec mynec;       // correct way in C

    // syntax error in C, right in C++
    Color myColor;
    Nec mynec;
    Data mydata;
    
    enum Color mycolor = Orange;    // legal in C
    mycolor = 4;                    // legal in C, syntax error in C++
    mycolor = Off;                  // legal in C
    // arithmetic to enum, enum to arithmetic conversion in C

    // arithmetic -> enum illegal in C++
    int ival;
    ival = mycolor;    // legal in C++, from enum -> arithmetic is legal
    ival = Purple;

    // to solve this problem: enum class Color {...}
}
