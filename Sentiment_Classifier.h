#ifndef SENTIMENT_CLASSIFIER_H
#define SENTIMENT_CLASSIFIER_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <list>

#include "stemandstopwords.h"
using namespace std;

class Sentiment_Classifier {
private:
    unordered_map< string, pair<int, int> > train_map;
    StemAndStopWords word_adjuster;
public:

    //Parsing and word polishing functions
    void parse_add(char*, char*);
    bool is_stopword(string);
    string& stem_word(string&);

    //Functionalities for additional word processing
    bool remove_at(string&);
    bool remove_href(string&);
    bool remove_threewords(string&);
    bool remove_tenwords(string&);
    void remove_punc(string&);

    //Other functionalities
    unordered_map<string, pair<int,int>> get_map();

    //Testing functions
    void display_map();
};
#endif // SENTIMENT_CLASSIFIER_H

