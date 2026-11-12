#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <stack>

//collection of the things i wanna look for
std::unordered_set<char> delims = {'(', ')','{','}','[',']','/'};
//stuff the program has to remember
std::string text_; //the char
size_t pos_ = 0; //position

enum class Tok{
    OPEN, CLOSE, COMMENT, //for the things
    INVALID //invalid token
};
struct Token{
    char txt;
    Tok type = Tok::INVALID;
};

std::vector<Token> toks;

//helpers
bool atEnd() {
    if(pos_ >= text_.size()){
        return true;
    }
    else return false;
}
//look at current char WITHOUT MOVING
char peek() {
    if(atEnd()){
        return '\0';
    }
    else {
        return text_[pos_];
    }
}
//look at the char one ahead of current position
char peekNext() {
    if(pos_ + 1 >= text_.size()){
        return '\0';
    }
    else {
        return text_[pos_ + 1];
    }
}
//look at current char and then step forward, in that order
char advance() {
    char temp = peek();
    pos_++;
    return temp;
}

//THE BIG ONE
bool expect(){
    std::stack<char> opens;
    for(const Token& t : toks){
        if(t.type == Tok::OPEN){
            opens.push(t.txt);
        }
        else if(t.type == Tok::CLOSE){
            //closing with nothing open, or the wrong type is open
            if(opens.empty() || opens.top() != t.txt){
                return false;
            }
            opens.pop();
        }
    }
    //anything left open was never closed
    return opens.empty();
}
//linker for debugging
  //inline says to the linker that this will always be the same and it can just pick whatever one it wants
    inline std::string tokName(Tok t) {
    // switch on t, return a string for each case
    switch(t){
        case Tok::OPEN:
            return "OPEN";
        case Tok::CLOSE:
            return "CLOSE";
        case Tok::INVALID:
            return "INVALID";
        case Tok::COMMENT:
            return "COMMENT";
    }
    return "?";
}

int main(int argc, char* argv[]){
    
    //getting the text
    if(argc < 2){
        std::cerr << "usage: ./PA08 <filename>" << std::endl;
        return 1;
    }
    std::ifstream file(argv[1]);
        if(!file){
            std::cerr << "couldn't open file" << std::endl;
            return 1;
        }
    std::stringstream buffer;
    buffer << file.rdbuf();   //dump the whole file into the stringstream
    text_ = buffer.str();     //now works with peek and advance

    //get the vector of tokens in its entirety before deciding if this is valid
    while(!atEnd()){
        if(delims.find(peek()) == delims.end()){
            advance(); //this char is not a delim
        }
        //a lone '/' (like division) is not a comment, skip it
        if(peek() == '/' && peekNext() != '/' && peekNext() != '*'){
            advance();
        }
        //handling tokenization for comments
        if(peek() == '/' && peekNext() == '/'){
            while(!atEnd() && peek() != '\n'){
                advance();
            }
            //std::cout << "SINGLE LINE COMMENT (WARN: NOT INCLUDED IN VECTOR)" << std::endl;

        }
        if(peek() == '/' && peekNext() == '*'){
            advance(); //step past the "/*" so "/*/" doesn't count as closed
            while(true){

                advance(); //absorb everything

                if(atEnd()) break; //comment never closed

                if(peek() == '*' && peekNext() == '/'){
                    advance();
                    advance();

                    break; //because we found the end
                }
            }
            //std::cout << "MULTI LINE COMMENT (WARN: NOT INCLUDED IN VECTOR)" << std::endl;
        }
        //handling the tokenization for the actual brackets
        if(peek() == '{' || peek() == '(' || peek() == '[' ){
            Token t;
            t.type = Tok::OPEN;
            t.txt = peek();

            toks.push_back(t);
            //std::cout << "OPEN ";
            //std::cout << t.txt << std::endl;
            advance();
        }
        if(peek() == '}' || peek() == ')' || peek() == ']'){
            Token t;
            t.type = Tok::CLOSE;

            //cheating a little bit so i can use equals comparison later
            if(peek() == '}') t.txt = '{';
            if(peek() == ')') t.txt = '(';
            if(peek() == ']') t.txt = '[';

            toks.push_back(t);
            //std::cout << "CLOSE ";
            //std::cout << t.txt << std::endl;
            advance();
        }
    }

    //this all needs to go into some true or false method so that i can return when i need to. For now it is unencapsulated
    //now parse the vector in its entirety.


    /*
    if something opens
        either
        something else has to open next  OR  something of same type must close next

    if something closes
        something of same type opened before  AND  no unclosed pairs remain in between
        */
    if(expect()){
        std::cout << "valid" << std::endl;
    }
    else {
        std::cout << "invalid" << std::endl;
    }
    return 0;
}
