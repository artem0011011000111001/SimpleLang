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
var4 = 16;         // var4 is not const
const var3 = var3; // var4 is const
var4 = "Hi";       // error "var4" is const
```
Expressions
```
a = 2 + 3; // a = 5
a = "Hello" + " world!"; // a = "Hello world!"
a = 3 * "ab"; // a = "ababab"
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
print("Hello world!"); // output expression
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


