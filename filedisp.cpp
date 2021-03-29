// filedsp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<iostream>
#include<stdlib.h> 
#include<string.h>
#include<string>
#include <fstream>


using namespace std;

int main(int argc, char* argv[])
{
    string input;

 
    if (argc != 2) {
       cout << "error: invalid number of arguments" << endl;
       cout << "usage: filedisp option" << endl;
       return -1;
    }

    while (getline(cin, input, '\n')) {
        if (strcmp(argv[1], "-d") == 0  && input.find("directories") != -1) {
            cout << input << endl;
        }
        else if (strcmp(argv[1], "-b") == 0 && input.find("bytes") != -1) {
            cout << input<< endl;
        }
        else if (strcmp(argv[1], "-f") == 0 && input.find("files") != -1 && input.find("bytes") == -1)
            cout << input<< endl;
    }
}

