//including things
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


//should only accept two args, input file and output file
int main(int argc, char* argv[]){

    //make a struct for each person so that printing is easier and then i can make a tostring method??
    //is this the best way to do it? Prob not but it seems intuative
    struct student {
        std::string name;
        std::string letterGrade;
        int grade;
    };

    //storing the input and output file names
    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    //some helper methods that i am keeping within the main class cause scope
    int readData(ifstream inFile(inputFile)){ //why the fuck is this upset fix this
        //do when home
    }
    int writeData(ofstream outFile(outputFile))){ //and of course this shit is fine and the other one isnt even tho its the fucking same
        //do when home
    }

}


//and some more methods that do not need to be in scope
std::string calculateGrade(int grade) {
    if(grade >= 90){
        return "A"; //grade is an a
    }
    else if(grade >= 80) {
        return "B"; //grade is a b
    }
    else if(grade >= 70){
        return "C"; //grade is a c
    }
    else if(grade >= 60){
        return "D"; //grade is a d
    }
    else{
        return "F"; //YOU FAILED
    }
}
    int highestScore(){
        //need to do this
    }
