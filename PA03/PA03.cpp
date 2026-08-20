//including things
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//make a struct for each person so that printing is easier and then i can make a tostring method??
//is this the best way to do it? Prob not but it seems intuative
struct student {

    //struct instance vars
    std::string name;
    std::string letterGrade;
    int grade;
};

//vector of students
std::vector<student> studentsVec;

//some helper methods
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

int readData(std::ifstream& inFile){

    //needed vars
    int num;
    std::string name;

    while(inFile >> name >> num){ //i need to make sure this will parse with whitespace in between names

        //will grab the next number grade down the line
        //i could then make a vector of the people struct and go down the line initializing names and grades
        student s;
        s.name = name;
        s.grade = num;
        s.letterGrade = calculateGrade(num);

        //this gets the initialized student and creates the vector. SO after reading the file, it is now all in the vector
        studentsVec.push_back(s);
    }

    return 0;

}

int writeData(std::ofstream& outFile){ 

    for(student s: studentsVec){
        //needed tostring to concatonate string and int values. Noted.
        outFile << s.name + " " + std::to_string(s.grade) + " " + s.letterGrade << std::endl;
    }

    return 0;
}

int highestScore(){
       int temp = 0;

       for(student s : studentsVec) {
        //if the most recent student score is higher, then they replace the temp
            if(s.grade > temp){
                temp = s.grade;
            }
       }

       //once loop terminates return highest score
       return temp;
}


//should only accept two args, input file and output file
int main(int argc, char* argv[]){

    //storing the input and output file names
    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    //starting the input file streams
    std::ifstream inFile(inputFile);
    std::ofstream outFile(outputFile);

    if(argc != 3){
        //this means invalid number of args
        std::cerr << "Invalid number of arguments" << std::endl;
        return 1;
    }
    else{
        
        //we good lets start doing some stuff
        if(inFile) {
            //read data
            readData(inFile); //this is simple
            //write data
            if(outFile){
                writeData(outFile); //this is easy
            }
            else {
                //couldnt open output file
                std::cerr << "failed to open output file" << std::endl;
                return 1;
            }
            //print highest score
            std::cout << highestScore() << std::endl;
        }
        else {
            //couldnt open input file
            std::cerr << "failed to open input file" << std::endl;
            return 1;
        }
    }

}

