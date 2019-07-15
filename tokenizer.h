/************************************************************
 Name: Brian Rafferty -- cssc0852 -- redID: 816988452
 Class: CS 570, Summer 2019
 Project: Program Assignment #2 -- PAM
 File: tokenizer.h
 Notes: Header file for tokenizer.cpp, and functions by instantiating
        all methods that are used within the source code.
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
#include "checker.cpp"
#include "tokenizer.cpp"
using namespace std;

#ifndef TOKENIZER_H
#define TOKENIZER_H

int inputSplit(char *currentChar, char **argPointer);

#endif

/***********************[ EOF: tokenizer.h ]*********************/