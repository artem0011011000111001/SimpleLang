Launch project:
1. Create new .txt file.
2. Create new .cpp file.
3. Include "Simple.h" and "fstream".
4. Read code from file, and call function "compile" from namespace Simple, and pass the source code as parameters.
5. Launch .cpp file.

Language syntax:
Variable declaration
```
var = 10;       // var = 10
var = 15;       // var = 15
var = "String"; // var = "String"
var2 = "Hello"; // var2 = "Hello"
var2 = "World"; // var2 = "World"
var2 = 5;       // var2 = 5
var3 = 2 < 5;   // var3 = true(1)
```
Const variable declaration
```
const var = 10;       // var = 15
var = 15;             // error "var" is const
const var2 = "Hello"; // var2 = "Hello"
var2 = "World";       // error "var2" is const
const var3 = 2 < 5;   // var3 = true(1)
var3 = false;         // error "var3" is const
// Also available
var4 = 16;            // var4 is not const
const var3 = var3;    // var4 is const
var4 = "Hi";          // error "var4" is const
```
Expressions
```
a = 2 + 3 ** 2;                   // a = 11
a = "Hello" + " world!";         // a = "Hello world!"
a = 3 * "ab";                    // a = "ababab"
a = 2 < 5 && !(5 > 10) || 9 > 6; // a = true(1)
```
Shortened arithmetic operations
```
a = 10;  // a = 10
a += 5;  // a = 15
a++;     // a = 16
--a;     // a = 15
a /= 5;  // a = 3
```
Standart functions
```
print("Hello world!"); // output to console expression
```
Statement if-else
```
if (2 < 5) {
  print("if");
}
else if (2 == 5) {
  print("else if");
}
else {
  print("else");
}
```
Statement while
```
a = 0;
while (a < 10) {
   print(a, "\n");
   ++a;
}
// Also available
// keyword break and continue
```
Statement do-while
```
a = 0
do {
  print(a, "\n");
  ++a;
} while(a < 10)
// Also available
// keyword break and continue
```
Statement for
```
for(i = 0; i < 10; ++i) {
   print(i, "\n");
}
// Also available
// keyword break and continue
```
Blocks
```
// For blocks from one statement
{
   print("Hello");
}
// You can
print("Hello");

// Example
if (true)
  print("Hello");

// Also there is scopes
if (true) 
   a = 10;

print(a); // error "a" not defined
```
Statement switch
```
switch(2 + 2) {
   case 3 {
      print("First case");
      break;
   }
   case 4
      print("Second case");
   default {
      print("Default");
   }
}
// Important
// Switch does not support short blocks, case and default is support

// Also available
// keyword break
```
Function declaration
```
func test_function_without_args() {
   print("Hello");
}

test_function_without_args(); // output Hello

func test_function_with_args(a, b) {
   return a + b;
}

print(test_function_with_args(2 + 3)); // output 5

// Also available
func test_function_with_constant_arg(const a, b) {
   a = 10; // error "a" is const
   b = 15; // good
}
// Also available
func test_function_with_short_block(x)
   print(x);

test_function_with_short_block("Hello"); // output Hello
```
Statement import
```
import Math;

print(PI);
```
Standart libs:
Math
```
// include
import Math

// Variables
const PI = 3.14159265...;
const E  = 2.71828182...;

// Functions
sin(arg)   // return sin of arg
cos(arg)   // return cos of arg
tan(arg)   // return tan of arg
sqrt(arg)  // return ²√ of arg
cbrt(arg)  // return ³√ of arg
floor(arg) // return math [] of arg
round(arg) // return round of arg
log(arg)   // return log of arg
```
Stream
```
// include
import Stream;

// Variables
const endl = "\n";

// Functions
output(args...)  // output to console args
outputln(args...) // output to console args who will split "\n"
input(arg = "")  // return user input with output arg
```
Type
```
// include
import Type;

// Variables
// None

// Functions
cast_number(arg) // try cast arg to number
cast_string(arg) // try cast arg to string
typeof(arg)      // return type name of arg
is_const(arg)    // return is there a variable name from the passed string is constant
```
Time
```
// include
import Time;

// Variables
// None

// Functions
now()      // return now time measured relative to internal epochal time
sleep(arg) // stops the thread at arg milliseconds 
```
