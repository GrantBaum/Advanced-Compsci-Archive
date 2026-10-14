#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>

//stuff the program has to remember
std::string text_; //the char
size_t pos_ = 0; //position
int line_ = 1; //what line im on
enum class Tok{
    OPEN, CLOSE, //for the things
    INVALID //invalid token
};
struct Token{
    char thing;
    Tok type = Tok::INVALID;
    int line = 1; //for error messages
};

std::vector<Token> toks();

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


int main(int argc, char* argv[]){
    //main method
}

