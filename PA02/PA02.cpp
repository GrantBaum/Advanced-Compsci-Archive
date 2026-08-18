#include <iostream>
#include <fstream>
#include <string>

//this sets default namespace to std (the one for iostream) so that i dont have to type it every time
//a namespace is how you desginate which header file functions to use in case they are overloaded. STD is the one for iostream which is the one i want to use.
using namespace std;



int main(int argc, char* argv[]){
    //declaring vars
    int counts[10] = {0};
    int digit;

    //if there are no other args, the file name will be the only one
    //therefore checking argc (number of args) can tell us if we have enough
    if(argc < 2){
        //so if its less than two then user did not include file name
        cerr << "Invalid amt of args, please include filename" << endl;
        //returning 1 ends main func and signals error
        return 1;
    }

    //not totally sure if this is gonna work, i didnt look this up i am just extrapolating from above
    string fileName = argv[1];
    ifstream inFile(fileName);

    //because the operators are kinda dual purpose, this being false means didnt work so i can just slap it in an if
    if(!inFile){
        cerr << "file at " + fileName + " failed to open for some reason" << endl;
        return 1;
    }

    //getting here means the file ran successfully
    while(inFile >> digit){
        counts[digit]++;
    }

    //once that is done it will eval to false and we can just print what we got on lines
    //was gonna used enhanced for loop but this is actually easier because i have to identify the digit before printing the count
    for (int i = 0; i < 10; i++) {
        cout << i << " " << counts[i] << endl;
    }

    //exited happily
    return 0;
}