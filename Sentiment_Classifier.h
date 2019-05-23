#ifndef SENTIMENT_CLASSIFIER_H
#define SENTIMENT_CLASSIFIER_H

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#include "Data_Set.h"
#include "Word.h"
using namespace std;

class Sentiment_Classifier {
private:
    vector<Data_Set> positive_classifier;
    vector<Data_Set> negative_classifier;
    vector<string> word_parser_test;
    vector<Word> word_vector;
public:
    void document_parser(char*, char*);
    void word_parser(char*, char*);

    vector<Data_Set> get_positive_vector();
    vector<Data_Set> get_negative_vector();
    vector<string> get_word_parser_test();
    vector<Word>& get_word();

    //more complex classification
    //functions, training data set

    void clean_non_alphabet(vector<string>&);
    bool check_start_of_tweet(string&);
    bool check_alphabet(string&);
    //bool remove_non_alpha(String&);
    void indexer(Word w);
    string& optimize_word(string&);
    //lowercase

    //get rid of @ words
    bool remove_at(string&);
  
    //get rid of all periods, commas, and apostrophes in a word.
    string& remove_periods(string&);

    //if the first word is not a letter, get rid of the first letter function]
    string& check_first_letter(string&);
    //get rid of apostrophes
    string& remove_nonalpha(string&);
    //identify negating words.
    bool identify_negation(string&);
    //get rid of commas

    //discard hrefs
    bool remove_href(string&);
    bool remove_threewords(string&);
    bool remove_tenwords(string&);
    void test_data(char*, char*, char*);
};
#endif // SENTIMENT_CLASSIFIER_H

