#include "Word.h"
using namespace std;

Word::Word(string& some_string, int pos, int neg) {
    sWord = some_string;
    positive = pos;
    negative = neg;
}

string& Word::getWord() {return sWord;}
int Word::getPositive() {return positive;}
int Word::getNegative() {return negative;}

void Word::setWord(string& some_string) {sWord = some_string;}
void Word::setPositive(int p) {positive = p;}
void Word::setNegative(int n) {negative = n;}
