#include <iostream>
#include <fstream>
#include <string>
#include <vector>


//Split function I found at https://stackoverflow.com/questions/289347/using-strtok-with-a-stdstring
//i dont really understand this so i dont really like it. I need to understand this before i continue
void split(const string& str, const string& delim, vector<string>& parts) {
  size_t start, end = 0;
  while (end < str.size()) {
    start = end;
    while (start < str.size() && (delim.find(str[start]) != string::npos)) {
      start++;  // skip initial whitespace
    }
    end = start;
    while (end < str.size() && (delim.find(str[end]) == string::npos)) {
      end++; // skip to end of word
    }
    if (end-start != 0) {  // just ignore zero-length strings.
      parts.push_back(string(str, start, end-start));
    }
  }
}


int main(int argc, char* argv[]){

    string arg1 = argv[1];

    //this is a class. It is for each person
    //planning on keeping a vector (arraylist) of people in memory after reading entire file
    struct Person {
        string firstName;
        string lastName;
        int age;
        string instagram;
        string twitter;
        string phone;
        string email;
    };

//TODO lets read our file and create our vector of people objects first before worrying abt args, so we can have them in mem either way
//@TODO this


    //if the first arg is the find keyword
    if(arg1 == "find") {

        //there must be four total args if this is the case
        if(argc != 4) {
            std::cerr << "invalid number of args for find keyword (should be 4)" << std::endl;
            return 1;
        }
        else {
            //@TODO get here and were good. Lets print some stuff.
        }
    }
    else if(arg1 == "add") {

        //there must be ten args now
        if(argc != 10) {
            std::cerr << "invalid number of args for add keyword (should be 10)" << std::endl;
            return 1;
        }
        else {
            //@TODO once again get here and we can start doing stuff.
        }
    }
    else {
        cerr << "invalid keyword at argv index 1" << endl;
        return 1;
    }
    

}