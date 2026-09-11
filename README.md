# CASH
The Certainly Amazing Shell.

CASH is a non-POSIX and non-sh clone shell-scripting language written for [RadishOS](https://github.com/wither16x/radish_os).

## Features
* Clean syntax
* Arithmetic expressions
* Variables and constants
* REPL (Read-Execute-Print Loop)
* Strings
* Booleans
* Comparison operators
* Run programs with arguments

## Building
CASH is mainly written for RadishOS. To build it for this platform, run
```sh
make -f radish.mk
```
To build it for Linux, run
```sh
make -f linux.mk
```
Both commands should generate an executable named `cash`.

## How to use it
Run a program:
```cash
path/to/the/program arguments
```
For example:
```cash
I:/bin/echo Hello world!
```
Evaluate an expression:
```cash
3 + 4
48 * (492 / (-1) + 11) * 2
```
Variables and constants:
```cash
const NAME = "John Doe"
var age = 42
I:/bin/echo My name is NAME and I am age years old.
age = 18
```
You can also use variables and constants in expressions.

Booleans:
```cash
var bool1 = true
var bool2 = false

I:/bin/echo bool1 and bool2
I:/bin/echo bool1 or bool2
I:/bin/echo bool1 xor bool2
I:/bin/echo not bool1
```
Comparisons:
```cash
var x = 8
var y = 5

I:/bin/echo x == y
I:/bin/echo x != y
I:/bin/echo x < y
I:/bin/echo x > y
I:/bin/echo x <= y
I:/bin/echo x >= y
```