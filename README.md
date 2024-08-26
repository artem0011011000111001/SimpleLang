Launch project:
1. Create new .simple file.
2. Create new .cpp file.
3. Include "Simple.h".
4. Call "ReadCodeFromFile" from namespace Simple pass the path to the file as an argument and pass the resulting result to "compile" from namespace Simple
5. Launch .cpp file.

Convenient and practical IDE for Simple - [Script Studio](https://github.com/denis557/Script-Studio).

Language syntax:
Variable declaration
```
a = 10;       // a = 10
a = 15;       // a = 15
a = "String"; // a = "String"
b = "Hello";  // b = "Hello"
b = "World";  // b = "World"
b = 5;        // b = 5
c = 2 < 5;    // c = true(1)
```
Const variable declaration
```
const a = 10;       // a = 15
a = 15;             // error "a" is const
const b = "Hello";  // b = "Hello"
b = "World";        // error "b" is const
const c = 2 < 5;    // c = true(1)
c = false;          // error "c" is const
```
Array declaration
```
arr = {1, "Nick", 2.5};       // arr = {1, "Nick", 2.5}
// or
arr2 = Array(1, "Nick", 2.5); // arr = {1, "Nick", 2.5}
```
Expressions
```
a = 2 + 3 ** 2;                  // a = 11
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

// Also avaible
a = 100% // a = 100%
```
Ternary operator
```
b = 10;

a = b > 10 ? true : false // a = false
```
Standart functions
```
print(args*);                           // output to console args
println(args*);                         // output to console args who will split "\n"
input(msg)                              // return input of user
input()                                 // calling input("")
mod(val1, val2)                         // return module val1 of val2
str(val)                                // cast to string val
num(val)                                // cast to string num
Array(args);                            // return array filled with args
print_array(arr, start, separator, end) // output to console arr taking into account the passed arguments
print_array(arr)                        // calling print_array(arr, "[", ", ", "]")
push(arr, val);                         // adds val to the end arr
push(arr, val, pos);                    // adds a value to a pos in the arr
pop(arr);                               // removes the last element of the arr
pop(arr, pos);                          // removes an element by pos in an arr
split(str, separator);                  // splits a str by separator and return this in the array view
map(arr, func);                         // takes each element of the arr, passes it to the func and returns a new array
clear();                                // return empty array
empty(arr);                             // return checks if the arr is empty and returns the result
join(arr, separator)                    // return a string with arr elements cast to string separated by a separator
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
} while (a < 10)
// Also available
// keyword break and continue
```
Statement for
```
for (i = 0; i < 10; ++i) {
   print(i, "\n");
}
// Also available
// keyword break and continue
```
Statement foreach
```
arr = Array(1, "Nick", 2.5);

foreach (el : arr) {
   print(el);
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
Statement try-catch, throw
```
try {
  throw "This is a thrown error";
}
catch(ex:str) {
  print(ex);
}
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

// Also available
func test_function_with_default_values_of_args(x = 5)
   print(x);

test_function_with_default_values_of_args(,)  // will substitute the default value
test_function_with_default_values_of_args(10) // the passed value will be supplied

// Also available
func test_function_with_same_name(x)
   print(x);

func test_function_with_same_name(x, y)
   print(x ** y);

test_function_with_same_name(5);    // calling first function
test_function_with_same_name(5, 3); // calling second function

// Also available
func test_function_with_unlimited_count_of_arguments(msgs*) {
    foreach(msg : msgs)
        println(msg);
}

test_function_with_unlimited_count_ofarguments("Hello", 6.41, 15); // you can pass an unlimited number of arguments

// Also avaible

func func_square(x) return x ** 2;

var_square = func_square;
print(var_square(3)); // output 9

inside_func_square = func(x) { return x ** 2; };
print(inside_func_square(3)); // output 9

```
Struct declaration
```
struct MyStruct {

  field x: num;
  field y: num;
  /*
  // Also avaible
    field x: num = 10;      // default value of x = 10
    field immutable x: num; // it will be possible to get the value of x, but if you try to change it, it will remain the same
    */


  func constructor(x, y, z) {
    this.x = x;
    this.y = y;
    this.z = z;
  }
  // Also avaible
  field z: num;
}

Struct_test = MyStruct(2, 3, 9);

print(Struct_test.x); // output 2

// Also avaible

destruct x, y, z = Struct_test; // Also works with objects
print(y) // output 3

```
Object declaration
```
test_object {
  name: "Nick"
  age: 15
}
print("Name = ", test_object.name, ", Age = ", test_object.age); // output Name = Nick, Age = 15
```
Statement import
```
import Math; // import libs

print(PI);

import "file.simple";

some_function_from_imported_file();

```
Standart libs:
Math
```
// include
import Math

// Variables
const PI = 3.14159265...
const E  = 2.71828182...

// Functions
sin(arg)          // return sin of arg
cos(arg)          // return cos of arg
tan(arg)          // return tan of arg
asin(arg)         // return asin of arg
acos(arg)         // return acos of arg
atan(arg)         // return atan of arg
atan2(arg)        // return atan of arg
sinh(arg)         // return sin of arg
cosh(arg)         // return cos of arg
tanh(arg)         // return tan of arg
power(arg)        // return power of arg
sqrt(arg)         // return ²√ of arg
cbrt(arg)         // return ³√ of arg
abs(arg)          // retuurn absolute value of arg
round(arg)        // return round of arg
ceil(arg)         // return ceil of arg
floor(arg)        // return math [] of arg
exp(arg)          // return exponent of arg
log(arg)          // return log of arg
log10(arg)        // return log10 of arg
factorial(arg)    // return factorial of arg
comb(args...)     // return combination of args
perm(args...)     // return permutation of args
mean(args...)     // return mean of args
median(args...)   // return median of args
std_dev(args...)  // return standart deviation of args
variance(args...) // return variance of args
is_prime(arg)     // return is prime arg
is_even(arg)      // return is even arg
is_odd(arg)       // return is odd arg
```
Type
```
// include
import Type;

// Variables
// None

// Functions
instanseof(arg1, arg2) // returns whether the types are equal to each other
is_const(arg)    // return is there a variable name from the passed string is constant

// Structures
typeof(value)  // fields: name: str, category: str, fields_count: num
// Example
println(typeof("Hello").name, typeof("Hello").category, typeof("Hello").fields_count) // output str, Primitive, 0
is_exist(name) // fields: _var: bool, _func: bool, _struct: bool
// Example
func foo() {}
a = 10;
println(is_exist("a")._var, is_exist("foo")._func, is_exist("test")._struct) // output 1, 1, 0
```
Time
```
// include
import Time;

// Variables
// None

// Functions
now()      // return now time measured relative to internal epochal time
system_now() // return struct Date with system date
sleep(arg) // stops the thread at arg milliseconds

// Structures
Date(year, month, day, hour, minute, second) // fields: year: num, month: num, day: num, hour: num, minute: num, second: num
```
Exception
```
// include
import Exception;

// Variables
// None

// Functions
error(error_text) // gives error

// Structures
TypeError(error_text, type) // fields: error_text: str, type: typeof
ValueError(error_text) // fields: error_text: str
```
System
```
// include
import System;

// Variables
// None

// Functions
file_exists(file_path)           // return whether the file exists
create_file(path)                // creates a file in the specified path
delete_file(path)                // deletes a file in the specified path
write(file_path, content)        // erases past content and writes new
write_append(file_path, content) // adds new content to old
read(file_path)                  // return content from a file
run(command)                     // return the result of the passed command

// Structures
FileError(error_text) // fields: error: str
file_info(file_patj)  // fields: path: str, name: str, extension: str, content: str, size: num
```
