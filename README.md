Compiler
-------
This was a compiler project that I designed while in college. The requirements were to build a lexer, parser and code generator without using any pre-packaged tools like (f)lex and yacc/bison. 
The language used as source was C-like, and the output was for a made-up stack based architecture. The code is very old, and I was inexperienced when I wrote it. I'm not sure the value, but
I'm releasing it in case it's useful for someone.

Below is the documentation for the project as required by my class.

Problem Statement 
=================
Code must be generated after the code has been parsed.  The code must maintain a symbol table to keep track of variables.
Instructions for using my compiler

My compiler should run on either a Windows or a UNIX system.  It has been tested on a Linux system with 2.6.9 kernel, gcc 3.3.4 and glibc version 2.3.  Unfortunely due to time limitations (and the fact that I don't have a Windows system), I was unable to test it on a Windows system.  It should compile without any external libraries using a recent version of gcc.

The compiler will use the first argument as the input file, and will produce the list of tokens as standard output.  Any errors are written to the standard error stream, so they will still be displayed if the standard output is redirected.
On a Windows system:
Compile using gcc or another standard C compiler.  Open a command line and run: compiler.exe infile > outfile
On a Linux or UNIX  system:
Compile on your system by running GNU make (gmake on many systems) from within the working directory of the source.  Then run it using ./compiler infile > outfile.

Program Design
==============
The program is designed to analyze a bottom-up parse of a program in a C-like language.  It does this by first bulid a parse tree, and then traversing each node, and calling other traversal functions based on the children of the node currently be processed.
It uses an array as the symbol table.  For each symbol lookup, it uses a linear search.  When inserting symbols, new symbols are placed at the end of the symbol table.  A global variable is used to assign memory addresses to newly declared variables.

Limitations 
===========
The input file must be ASCII, Unicode is not supported.  The symbol table is limited to 100 symbols.  The parser is limited to 1000 stack elements.

Tests
=====
Three tests taken from http://faculty.fullerton.edu/wmaloles/.  The input is given in files test1.c, test2.c, and test3.c.  The output is in test1.out, test2.out, and test3.out.  All of them appear to run as expected.


