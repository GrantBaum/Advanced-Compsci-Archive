#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <unordered_set>

//collection of the things i wanna look for
std::unordered_set<char> delims = {'(', ')','{','}','[',']'};
//stuff the program has to remember
std::string text_; //the char
size_t pos_ = 0; //position

enum class Tok{
    OPEN, CLOSE, //for the things
    INVALID //invalid token
};
struct Token{
    char txt;
    Tok type = Tok::INVALID;
};

std::vector<Token> toks;

//some helper methods
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
    }
    return "?";
}

int main(int argc, char* argv[]){
    
    //get the vector of tokens in its entirety before deciding if this is valid
    while(!atEnd()){
        if(delims.find(peek()) == delims.end()){
            advance(); //this char is not a delim
        }
        if(peek() == '{' || peek() == '(' || peek() == '[' ){
            Token t;
            t.type = Tok::OPEN;
            t.txt = peek();

            toks.push_back(t);
            advance();
        }
        if(peek() == '}' || peek() == ')' || peek() == ']'){
            Token t;
            t.type = Tok::CLOSE;
            t.txt = peek();

            toks.push_back(t);
            advance();
        }
    }

    //now parse the vector in its entirety.
    /*
    while(not at end of vector list){
        if(token at pos 0 == close){
            return invalid;
        }
        if(token at pos 0 == open){
            expect another open
            or expect close of same type (this.txt == that.txt)

            while(true //can stop on return){
                if(next token == what is expected){
                    continue
                }
                else return with cerr
            }
            return true //because if we reach the end of the loop without cerr it is valid code
        }
    }
        */
}

