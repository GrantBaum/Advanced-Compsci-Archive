//including things
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception> //needed this for the try/catch

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

void readData(std::ifstream& inFile){
    //needed vars
    std::string line;

    //getline takes the WHOLE line so the spaces come along for the ride
    while(std::getline(inFile, line)){

        //if theres nothing but whitespace on this line just move on
        if(line.find_first_not_of(" \t\r") == std::string::npos){
            continue;
        }

        size_t end = line.find_last_not_of(" \t\r");
        line = line.substr(0, end + 1);
        
        //the name is the part thats a random length, the number is always last
        //so i split from the END instead of the front. this is the whole trick
        size_t split = line.find_last_of(" \t");
        if(split == std::string::npos){
            //no space at all means this line is junk
            std::cerr << "skipping malformed line: " << line << std::endl;
            continue;
        }
        std::string name = line.substr(0, split); //everything before the last space
        std::string gradeText = line.substr(split + 1); //everything after
        //stoi throws instead of failing quiet
        int num;
        try {
            num = std::stoi(gradeText);
        }
        catch(const std::exception&) {
            std::cerr << "skipping malformed line: " << line << std::endl;
            continue;
        }
        //same as before, build the student and shove it in the vector
        student s;
        s.name = name;
        s.grade = num;
        s.letterGrade = calculateGrade(num);
        studentsVec.push_back(s);
    }
}
void writeData(std::ofstream& outFile){
    //const student& instead of student so it stops copying the whole struct every loop
    for(const student& s: studentsVec){
        //thought i needed a tostring operator but this works too
        outFile << s.name << " " << s.grade << " " << s.letterGrade << std::endl;
    }
}
int highestScore(){
       int temp = 0;
       for(const student& s : studentsVec) {
            if(s.grade > temp){
                temp = s.grade;
            }
       }
       //once loop terminates return highest score
       return temp;
}
//should only accept two args, input file and output file
int main(int argc, char* argv[]){
    if(argc != 3){
        //this means invalid number of args
        std::cerr << "Invalid number of arguments" << std::endl;
        return 1;
    }
    //now its safe to touch these
    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    std::ifstream inFile(inputFile);
    if(!inFile) {
        //couldnt open input file
        std::cerr << "failed to open input file" << std::endl;
        return 1;
    }

    //check the output file up here too. no point parsing the whole thing
    //and THEN finding out i cant write anywhere
    std::ofstream outFile(outputFile);
    if(!outFile) {
        //couldnt open output file
        std::cerr << "failed to open output file" << std::endl;
        return 1;
    }

    //we good lets start doing some stuff
    //read data
    readData(inFile); //this is simple

    //if every single line was junk theres nothing to write
    if(studentsVec.empty()){
        std::cerr << "no valid records found in input file" << std::endl;
        return 1;
    }

    //write data
    writeData(outFile); //this is easy
    //print highest score
    std::cout << highestScore() << std::endl;
    return 0;
}