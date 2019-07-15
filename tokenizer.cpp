/************************************************************
 Name: Brian Rafferty -- cssc0852 -- redID: 816988452
 Class: CS 570, Summer 2019
 Project: Program Assignment #2 -- PAM
 File: pam.cpp
 Notes: This is the source code for a program that tokenizes
        the input written to the PAM. It does so by iterating
        through the given input line and replaces all whitespace
        with zeros. Each time a whitespace is encountered, a pointer
        to the start of the next token is set. This code returns
        the number of arguments as well, as it creates arguments
        that mimic int argc and char* argv[].
*************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>
#include <vector>
using namespace std;

/************************************************************
 FUNCTION: inputSplit
 DESCRIPTION: The input is received and iterated through via
                currentChar. Each time the input yields a whitespace,
                it is replaced by a zero and the address of the token
                is recorded with argPointer. Once the end of the input
                is reached, the total number of arguments encountered
                and recorded is returned as an int value.
 I/O:   Input: char*, char**
        Output: int
*************************************************************/
int inputSplit(char *currentChar, char **argPointer) {
    int argNum = 0;
    //loop until end of line
    while (*currentChar != '\0') { 
        //replace all whitespace with 0
        while (*currentChar == '\n' || *currentChar == '\t' || *currentChar == ' ') {
            *currentChar++ = '\0';
        }
        argNum++;
        //set argument pointer to start of next token following whitespace
        *argPointer++ = currentChar;
        //iterate pointer if no whitespace at current index
        while (*currentChar != '\n' && *currentChar != '\t' && *currentChar != ' ' && *currentChar != '\0') {
            currentChar++;
        }
    }
    //add null terminator to end of line
    *argPointer = '\0';
    return argNum;
}

/***********************[ EOF: tokenizer.cpp ]*********************/