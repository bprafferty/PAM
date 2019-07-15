Brian Rafferty -- cssc0852 -- redID: 816988452
---------------------
CS 570 Operating Systems, Summer 2019
---------------------
Program Assignment #2, PAM
---------------------
README.md
---------------------
Manifest:
    README.md
    pam.cpp
    pam.h
    checker.cpp
    checker.h
    tokenizer.cpp
    tokenizer.h
    test.cpp
    test2.cpp
    test3.cpp
    Makefile
----------------------
Compiling executable:
    make
----------------------
Running executable:
    pam 
----------------------
*** Must enter ./ before every executable for PAM to recognize it.
Example inputs:
    cssc0852% ./test
    cssc0852% ./test arg
    cssc0852% ./test | ./test2
----------------------
List/description of novel/significant design decisions:
Added a classifier to label each input, 0 -- random argument,
1 -- executable, 2 -- pipe symbol. If the order of the integers
were incorrect, the program throws an error and prompts the user.
----------------------
List/description of any extra features/algorithms/functionality 
you included which were not required:
I added error checks throughout to make sure that all fork(), 
pipe(), and execvp() system calls operated correctly.
----------------------
List/description of all known deficiencies or bugs:
Only piping between two executables is functional,
it will run with more than 2, but it is not optimal
behavior for a pipe. Also, executables must be entered
with ./ before their filename when using the PAM.
----------------------
Lessons Learned:
Pipes are difficult to work with, and finding the
correct ways to implement them proved to be a challenge.
I learned to treat pipes like streams, always making sure
to close them after using.