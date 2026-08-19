//including things
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//make a struct for each person so that printing is easier and then i can make a tostring method??
//is this the best way to do it? Prob not but it seems intuative
struct student {
    std::string name;
    std::string letterGrade;
    int grade;
};

//some helper methods 
int readData(std::ifstream& inFile){
    int num;
    while(inFile >> num){
        //will grab the next number grade down the line
        //i could then make a vector of the people struct and go down the line initializing names and grades
    }
}
int writeData(std::ofstream& outFile){ 
}

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


//should only accept two args, input file and output file
int main(int argc, char* argv[]){

    //storing the input and output file names
    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    //starting the input file streams
    std::ifstream inFile(inputFile);
    std::ofstream outFile(outputFile);

}

