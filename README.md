# Tera
## A base-3 cpu simulator
Jordan "Jorb" Dehmel, 2023 - present

jdehmel@outlook.com

github.com/jorbDehmel/tera.git

## Overview: Tera, Terace, Tricat and Deco

Tera is a base-3 CPU simulator. It runs .tera files which are
compiled by Terace, the Tera assembler. Terace takes in .tasl
(ternary assembly language) files. Deco is the Tera decompiler,
which takes .tera files and outputs a possible .tasl
source. Tricat echos the raw trytes of a ternary file.

Tera - TERnAry cpu
Terace - TERA ASSembler (Abbreviation works verbally)
Deco - DECOmpiler
Tricat - Ternary Cat (As in the UNIX command cat)

## Use

To compile the Tera source code:

`make`

To make these executables callable from anywhere (Linux only):

`make install`

To remove Tera binaries from your system (Linux only):

`make uninstall`

To compile some .tasl file into .tera:

`bin/terace.out /PATH/TO/TASL/FILE.tasl /PATH/TO/OUTPUT/TERA/FILE.tera`

To run some .tera file:

`bin/tera.out /PATH/TO/TERA/FILE.tera`

To decompile some .tera file:

`bin/deco.out /PATH/TO/TERA/FILE.tera`
(this prints the .tasl)

`bin/deco.out /PATH/TO/TERA/FILE.tera /PATH/TO/OUTPUT/FILE.tasl` (this writes the .tasl to a new file)

To see the raw trytes of some file:

`bin/tricat.out /PATH/TO/FILE.tera`

## .tasl symbol meanings

\* - Access base scope variable (*VARNAME)

\+ - Access superscope variable (+VARNAME)

\. - Variable declaration (.VAR 1)

\~ - Stack pop (~VAR)

\_ - Base 27 literal (_0qf)

\- - Char literal

\/ - Comment (/ foo or // foobar)

\{ - Begin function ({FNNAME ...)

\} - End function and return (... })

\! - Update call stack and call function (!FNNAME)

\^ - Pointer arithmatic (^VARNAME.-12)

\$ - Size in trytes of a variable ($VARNAME)

\# - Call a macro (#print yada yada yada)

## Macros

Macros are pre-compilation CPP functions which take arguments
and expand into corrosponding .tasl code. Below is a list of
macros and examples of their use.

**#print ARG**

Prints the following string directly to the CPU's output stream.

> #print Hello, World!

**#println ARG**

Does the same as #print and prints a newline.

> #println Hello,
> #println  World!

**#req ARG_1 ARG_2 ... ARG_N**

Ensures that all passed arguments are the names of variables in
the current scope.

> #req VAR1 VAR2
> / some operation using VAR1 and VAR2

**#cpy FROM TO**

Copy each tryte in one variable to its relative position in
another.

> .VAR 9
> put ^VAR.3 -Y
> .CLONE 9
> #cpy VAR CLONE

**#zero VAR**

> .VAR 9
> #zero VAR

Set every tryte within VAR to zero. This is important as
memory is not reset when a variable is freed from the stack.

## Useful information for my definition of a tryte

After finishing the majority of this project, I discovered
that the definitions I made up are not universal. For the
purposes of this project, I will be asserting that I am
right and everyone else is wrong. Here are my definitions.

1 trit = A zero, one or two

1 tribble = Three trits (3 make a tryte)

1 tryte = 9 trits (19'683 states)

1 kilotryte = 3^9 trytes

1 gigatryte = 3^18 trytes

## Instruction layout

A full instruction consists of a 1 tryte instruction, a 1
tryte address, and a 1 tryte literal.

**Example**: Put "456" into memory position 123

> put 123 456

## Buffers

0 - instrPointer

Pointer to the current instruction.

1 - controlBuffer

Holds either 0 or non-zero. Controls all if statements.

2 - returnPointer

Where to jump back to after completing a function call.

## Misc

Minimum working memory (1 sector):

19'683 trytes = 1 kilotryte ~= 1400 kb

Maximum working memory (27 sectors):

531'441 trytes = 27 kilotryte ~= 40 mb

.tasl file: Ternary ASsembly Language file

.tera file: TERnAry file (following BINary's .bin, and adding an a to be cool)

## Instruction set

> kill (unused unused)

End the current program.

> put ADDRESS LITERAL

Put the given literal at the given memory address.

> cpy FROM_ADDRESS TO_ADDRESS

Copy from one memory address to another.

> incr ADDRESS LITERAL

Increment a memory address by a literal.

> decr ADDRESS LITERAL

Decrement a memory address by a literal

> jump ADDRESS LITERAL

If LITERAL is non-zero, jump forward by that many instructions.
Otherwise, go to ADDRESS.

> jumpBack ADDRESS LITERAL

Same as jump, but jumps backwards.

> ifControl (unused unused)

If the control is zero, jump past the corrosponding endif.

> endif (unused unused)

Terminates an if statement.

> andEqV ADDRESS_1 ADDRESS_2

The control buffer is set to one if it is one and the thing at
the first address matches the thing at the second address.
Otherwise, it is set to zero.

> andNeqV ADDRESS_1 ADDRESS_2

The control buffer is set to one if it is one and the thing at
the first address does not match the thing at the second.
Otherwise, it is set to zero.

> andLessV ADDRESS_1 ADDRESS_2

The control buffer is set to one if it is one and the thing at
the first address is less than the thing at the second one.
Otherwise, it is set to zero.

> andGreaterV ADDRESS_1 ADDRESS_2

The control buffer is set to one if it is one and the thing at
the first address is greater than the second. Otherwise, it is set
to zero.

> orEqV ADDRESS_1 ADDRESS_2

The control buffer is set to one if the thing at the first address
is equal to the second.

> orNeqV ADDRESS_1 ADDRESS_2

The control buffer is set to one if the thing at the first address
is not equal to the second.

> orLessV ADDRESS_1 ADDRESS_2

The control buffer is set to one if the thing at the first address
is less than the second.

> orGreaterV ADDRESS_1 ADDRESS_2

The control buffer is set to one if the thing at the first address
is greater than the second.

> out ADDRESS LITERAL

Outputs the values of LITERAL trytes starting at ADDRESS.

> inp ADDRESS LITERAL

Inputs to the values of LITERAL trytes starting at ADDRESS.

> sector ADDRESS (unused)

Switch the current memory sector. If ADDRESS is zero, switch
to the default memory sector. Otherwise, switch to the specified
one.

> addV TO FROM

The value in TO is equal to the value in TO plus the value in FROM.

> subtractV TO FROM

The value in TO is equal to the value in TO minus the value in FROM.

> multV TO FROM

The value in TO is equal to the value in TO times the value in FROM.

> divV TO FROM

The value in TO is equal to the value in TO divided the value in FROM.

> modV TO FROM

The value in TO is equal to the value in TO modulo the value in FROM.

> ifNever (unused unused)

Skip to the next endif, no matter what.

## Base-27 (triternary)

Just as one hexadecimal character is equivolent to 4 bits (1 *nibble*),
1 triternary character is equivolent to 1 **tribble** (3 of which make
up a tryte). Below is a triternary conversion table.

| Decimal | Triternary | Tribble |
| ------- | ---------- | ------- |
| 0       | 0          | 000     |
| 1       | 1          | 001     |
| 2       | 2          | 002     |
| 3       | 3          | 010     |
| 4       | 4          | 011     |
| 5       | 5          | 012     |
| 6       | 6          | 020     |
| 7       | 7          | 021     |
| 8       | 8          | 022     |
| 9       | 9          | 100     |
| 10      | a          | 101     |
| 11      | b          | 102     |
| 12      | c          | 110     |
| 13      | d          | 111     |
| 14      | e          | 112     |
| 15      | f          | 120     |
| 16      | g          | 121     |
| 17      | h          | 122     |
| 18      | i          | 200     |
| 19      | j          | 201     |
| 20      | k          | 202     |
| 21      | l          | 210     |
| 22      | m          | 211     |
| 23      | n          | 212     |
| 24      | o          | 220     |
| 25      | p          | 221     |
| 26      | q          | 222     |

## Tryte file encoding

A tryte is encoded as 3 characters, each representing 3 trits (a tribble).
Thus, in a file stored on a (binary) computer, each tryte will take up 3
bytes (note that this is reduced to 2 bytes once it enters memory). Each
byte holds a value between 0 and 27. This is **not** the same as base-27,
although if you shifted this value up some amount it would translate 1 to
1.

## Character and integer printing

When outputting a tryte to the CPU output stream, the following definitions
are used.

If the tryte has a 0 in the largest trit, it is outputted as a positive
integer. This is followed by a newline.

If the tryte has a 1 in the largest trit, it is outputted as a negative
integer (just a minus followed by its value, leading to -0). This is
followed by a newline.

If the tryte has a 2 in the largest trit, it is outputted as a C++ char.

## Memory sectors

These are not extensively tested, but they allow for memory size upgrades
from 1 kilotryte to 27. A wrapper program could also link them to files
or drives and the CPU could use them accordingly with little modification.
