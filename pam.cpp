/************************************************************
 Name: Brian Rafferty -- cssc0852 -- redID: 816988452
 Class: CS 570, Summer 2019
 Project: Program Assignment #2 -- PAM
 File: pam.cpp
 Notes: This is the source code for the driver program that 
        facilitates the function of the PAM. It creates an
        endless loop that can only be broken by entering
        exit as the first microshell argument. The input entered
        each iteration is tokenized, error checked, and executed
        based upon the specifications of the entry. This PAM supports
        execution of single executables as well as the creation of
        pipes between executables for redirected execution.
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

int statusValue;
pid_t leftChild;
pid_t rightChild;

/************************************************************
 FUNCTION: runExe
 DESCRIPTION: Receives the argument list from the driver and
                attempts to launch the executable given. It does
                so by forking off a child process from the parent,
                before running the first command line argument with
                execvp. Any errors are accounted for and the parent
                process allows all execution of the child process to
                finish before closing.
 I/O:   Input: char**
        Output: void
*************************************************************/
void runExe(char **argv) {

    //child process
    leftChild = fork();
    //if unsuccessful fork
    if (leftChild < 0) {
        perror("fork error");
        exit(0);
    }
    //if fork worked
    else if (leftChild == 0) {
        //run exe
        leftChild = execvp(*argv,argv);
        //if exe failed to run
        if (leftChild < 0) {     
            perror("exe error");
            exit(0);
        }
    }
    //parent process
    else {
        //wait until child process finishes
        while (wait(&statusValue) != leftChild);
    }
}

/************************************************************
 FUNCTION: createPipe
 DESCRIPTION: Receives the argument list and current iteration
                from the driver program. Will start by creating
                a pipe with one end for reading and another for
                writing. Each child process is responsible for
                one end of the pipe, and will read or write one
                at a time. Once both child processes are done 
                reading/writing, they will execute. The parent
                process is responsible for closing the ends of 
                the pipes after execution and making sure that
                both child processes had the chance to completely
                stop running before closing.
 I/O:   Input: char**, int
        Output: void
*************************************************************/
void createPipe(char **argv, int i) {
    
    int pipeArray[2];
    
    //create pipe
    if (pipe(pipeArray)) {
        perror("pipe error");
        exit(0);
    }

    //child process #1
    leftChild = fork();
    //if unsuccessful fork
    if (leftChild < 0) {
        perror("fork error");
        exit(0);
    }
    //if fork worked
    else if (leftChild == 0) {
        close(1);
        dup(pipeArray[1]);
        close(pipeArray[0]);
        close(pipeArray[1]);
        int errorNo = execvp(argv[i*2],argv);
        if (errorNo != 0){
            perror("exe error");
            exit(0);
        }
    }

    //child process #2
    rightChild = fork();
    //if unsuccessful fork
    if (rightChild < 0) {
        perror("fork error");
        exit(0);
    }
    //if fork worked
    else if (rightChild == 0) {
        close(0);
        dup(pipeArray[0]);
        close(pipeArray[1]);
        close(pipeArray[0]);
        int errorNo = execvp(argv[(i*2)+2],argv);
        if (errorNo != 0){
            perror("exe error");
            exit(0);
        }
    }

    //parent process
    else {
        
        //safely close pipes
        close(pipeArray[0]);
        close(pipeArray[1]);
        
            
        //let child processes finish
        rightChild = waitpid(rightChild, &statusValue, 0);
        if (rightChild < 0) {
            perror("right pipe error");
            exit(0);
        }
        leftChild = waitpid(leftChild, &statusValue, 0);
        if (leftChild < 0) {
            perror("left pipe error");
            exit(0);
        }
    }

}

/************************************************************
 FUNCTION: main
 DESCRIPTION: Driver for PAM which begins by starting an endless
                loop. The only way out of this loop is by entering
                exit as the first argument of the microshell input.
                Every line begins with the same prompt and will
                collect any input entered by the user. Errors will
                be accounted for and reported accordingly. If 
                tokenization, error checking, and sequence verification
                were all successful, then the PAM will continue by 
                running the executables entered.
 I/O:   Input: int, char*
        Output: int
*************************************************************/
int main(int argc, char* argv[]) {

    //endless loop for microshell interface
    while(1){
        
        bool incorrect = false;
        bool containsPipe = false;
        int pipeCount = 0;
        char input[1024];
        char *args[64];
        int argNum;
        vector<int> argTypes;

        //display username & wait for user input
        cout << "cssc0852% ";

        //collect user input
        cin.getline(input,1024);

        //tokenize input & record number of args
        argNum = inputSplit(input,args);

        //if first arg of microshell is exit
        if (strcmp(args[0], "exit") == 0) {
            cout << "Terminating Process" << endl;
            exit(0);
        }

        //iterate to determine type of each token
        for (int i = 0; i < argNum; i++){
            argTypes.push_back(checkExe(args[i]));
            if (argTypes[i] == 2) {
                containsPipe = true;
                pipeCount++;
            }
        }

        //check for incorrect sequence of tokens
        for (int i = 0; i < argNum; i++){
            if ((argTypes[i] == 2 && i == argNum-1)|| argTypes[0] != 1 || (i >= 2 && argTypes[i] == 0)) {
                cout << "Error: invalid argument: " << args[i] << endl;
                incorrect = true;
                break;
            }
        }

        //if pipe found within microshell input
        if (incorrect == false && containsPipe == true) {
            //iterate if multiple pipes
            for (int i = 0; i < pipeCount; i++) {
                createPipe(args,i);
            }
        }

        //if no pipe is found, just run exe
        if (incorrect == false && containsPipe == false) {
            runExe(args);
        }
    }
    return 0;
}

/***********************[ EOF: pam.cpp ]*********************/