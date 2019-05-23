#ifndef WORD_H
#define WORD_H

#include <string>

class Word {
private:
    string sWord;
    int positive;
    int negative;
public:
    Word(string&, int, int);
//Accessors:
    string& getWord();
    int getPositive();
    int getNegative();
//Mutators:
    void setWord(string&);
    void setPositive(int );
    void setNegative(int );
};

#endif
