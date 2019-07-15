#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]){
    string input;
    while(getline(cin, input)){
        cout << "Final Output: " << input << endl;
    }
    return 0;
}