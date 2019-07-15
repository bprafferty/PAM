/************************************************************
 Name: Brian Rafferty -- cssc0852 -- redID: 816988452
 Class: CS 570, Summer 2019
 Project: Program Assignment #2 -- PAM
 File: pam.cpp
 Notes: This is the source code for a program that provides
        the PAM with the ability to check if arguments entered
        on the microshell are valid. Must be exe, exe arg, exe
        | exe, or exe | exe | ... | exe
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
 FUNCTION: checkExe
 DESCRIPTION: Receives the current token being evaluated and
                cements it as a const char. A buffer is created
                and the status of the token is determined. If 
                stat() is less than 0, then it is not an exe.
                If the token is not an exe, then it is checked
                to see if it is a pipe or just a regular arg.
                Next the buffer's filetype is determined with
                st_mode and compared to the exe type with the
                & logical operator.
 I/O:   Input: string
        Output: int
*************************************************************/
int checkExe(string token){
    struct stat buffer;
    const char *userExe = token.c_str();
    //if token is not an exe
    if (stat(userExe, &buffer) < 0) {
        //check token for pipe
        if (token == "|"){
            return 2;
        }
        //else token is other argument
        return 0;
    }
    //if token is not exe
    if ((S_IEXEC & buffer.st_mode) == 0) {
        return 0;
    }
    //else token is exe
    return 1;
    
}

/***********************[ EOF: checker.cpp ]*********************/