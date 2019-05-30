
#include "Sentiment_Classifier.h"

//Index:
void Sentiment_Classifier::parse_add(char* file1, char* file2) {
    ifstream input(file1);
    ifstream input2(file2);

    //Remove the first line
    string temp, temp2;
    getline(input, temp);
    getline(input2, temp2);

    string num, id_data, usrname, sentiment_score, id_target;
    string word;
    while(!input.eof() && !input2.eof()) {
        //get-lining one whole line from input1
        getline(input, num, ',');
        getline(input, id_data, ',');
        getline(input, usrname, ',');
        getline(input, word);

        //get-lining one whole line from input2
        getline(input2, num, ',');
        getline(input2, sentiment_score, ',');
        getline(input2, id_target);

        stringstream ss;
        string temp_word;
        ss << word;
        while(ss >> temp_word) {

            //Before adding the word in, perform a number of surgical operations to clean/stem each word.
            //if(is_stopword(temp_word))  continue;
            if(!remove_threewords(temp_word))   continue;
            if(!remove_tenwords(temp_word))     continue;
            if(!remove_at(temp_word))           continue;
            if(!remove_href(temp_word))         continue;
            remove_punc(temp_word);
            //Stop and Stem
            stem_word(temp_word);

            if(id_data == id_target) {
                if(train_map.find(temp_word) == train_map.end()) {
                    //If there is no key value pair matching this particular word, temp_word,
                    if(sentiment_score[0] == '4') {
                        //Positive tweet
                        train_map[temp_word] = make_pair(1, 0);
                    } else if(sentiment_score[0] == '0') {
                        //Negative tweet
                        train_map[temp_word] = make_pair(0,1);
                    } else {
                        //Unrecognizable character
                        cout << "insertion failed. Root cause may be error in parsing or storing the value 'sentiment_score'" << endl;
                    }//end nested if chain
                } else {
                    //If a given word already exists
                    if(sentiment_score[0] == '4') {
                        //Positive tweet
                        train_map[temp_word].first++;
                    } else if(sentiment_score[0] == '0') {
                        //Negative tweet
                        train_map[temp_word].second++;
                    } else {
                        //Unrecognizable character
                        cout << "insertion failed. Root cause may be error in parsing or storing the value 'sentiment_score'" << endl;
                    }//end nested if chain
                }//end nesting if chain
            } else {
                cout << "id_data and id_target mismatch. Potential problem in parsing and processing..." << endl;
            }
        }//end nested while
    }//end nesting while
}

//Currently not in use. Takes up too much time.
bool Sentiment_Classifier::is_stopword(string some_string) {
    ifstream input("stopwords.txt");
    list<string> stopwords;
    while(!input.eof()) {
        string temp;
        input >> temp;
        stopwords.push_back(temp);
    }//end while

    for(list<string>::iterator it=stopwords.begin(); it != stopwords.end(); ++it) {
        if(some_string == *it)
            return true; 
    }//end for
    return false;
}

string& Sentiment_Classifier::stem_word(string& some_string) {
    word_adjuster.stemWord(some_string);
    return some_string;
}

//Functionalities:

bool Sentiment_Classifier::remove_at(string& word) {
    if(word[0] == '@') {
        return false;
    }
    return true;
}
bool Sentiment_Classifier::remove_href(string& word) {
    //check for www.
    int count = 0;
    for(int i = 0; i < 3; i++) {
        if(word[i] == 'w')
            count++;
    }
    if(word[3] == '.')
        count++;
    if(count == 4)
        return false;
    
    //check for http
    if(word[0] == 'h' && word[1] == 't' && word[2] == 't' && word[3] == 'p') 
        return false;
    return true;
}

bool Sentiment_Classifier::remove_threewords(string& word) {
    if(word.size() < 3)
        return false;
    return true;
}
bool Sentiment_Classifier::remove_tenwords(string& word) {
    if(word.size() > 9)
        return false;
    return true;
}

void Sentiment_Classifier::remove_punc(string& some_string) {
    //check length 0
    if(!isalpha(some_string[0])) {
        some_string.erase(0);
    } else if(!isalpha(some_string[some_string.size() - 1])) {
        some_string.erase(some_string.size() - 1);
    }
}

unordered_map<string, pair<int,int>> Sentiment_Classifier::get_map() {return train_map;}

//Testing functions

void Sentiment_Classifier::display_map() {
    int word_count = 0;
    int word_unique = 0;
    unordered_map<string, pair<int, int> >::iterator iter;
    for(iter = train_map.begin(); iter != train_map.end(); iter++) {
        cout << "Key: " << iter  ->first << endl;
        cout << "Value: <" << iter ->second.first  << " , " << iter ->second.second << ">" << endl;
        word_count += iter -> second.first;
        word_count += iter -> second.second;
        word_unique++;
    }
    cout << endl;
    cout << "Number of total words: " << word_count << endl;
    cout << "Number of unique words: " << word_unique << endl;
    cout << "Unique word to total word count ratio: " << (double)word_unique / word_count << endl;
}
