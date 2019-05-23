
#include "Sentiment_Classifier.h"

void Sentiment_Classifier::document_parser(char* file1, char* file2) {
    //This function is the first parsing function of
    //the Sentiment_Classifier class.
    //This function may prove useful later on,
    //but for now, it is mainly a function
    //that demonstrates the reliability of the
    //parsing mechanism using custom built string class

    ifstream input_data(file1);
    ifstream input_target(file2);

    string temp1, temp2;
    //Get rid of the first line in each file
    getline(input_data, temp1);
    getline(input_target, temp2);
    cout << temp1 <<endl;
    cout << temp2 << endl;
    int i = 0;
    while(!input_data.eof()) {

        string number;
        string number2;
        string classifier;
        string id, id2;
        string user;
        string tweet;

        getline(input_data, number, ',');
        getline(input_data, id, ',');
        getline(input_data, user, ',');
        getline(input_data, tweet);

        getline(input_target, number2, ',');
        getline(input_target, classifier, ',');
        getline(input_target, id2);

        if(classifier[0] == '0') {
            //negative tweet
            Data_Set neg;
            neg.set_number(number);
            neg.set_id_number(id);
            neg.set_classifier(classifier);
            neg.set_user(user);
            neg.set_tweet(tweet);
            negative_classifier.push_back(neg);
            cout << id << ": " << tweet << endl;
        }
        else {
            //positive tweet
            Data_Set pos;
            pos.set_number(number);
            pos.set_id_number(id);
            pos.set_classifier(classifier);
            pos.set_user(user);
            pos.set_tweet(tweet);
            positive_classifier.push_back(pos);
            cout << id << ": " << tweet << endl;
        }
    }//end while
}//end document_parser()

void Sentiment_Classifier::word_parser(char* file1, char* file2) {

    ifstream input(file1);
    ifstream input2(file2);

    string text;
    string number;
    string classifier;
    string id;
    while(input >> text) {
        //parse words in the following format:
        //Word  id  classifier \n
        if(check_start_of_tweet(text)) {

            number = "";
            classifier = "";
            id = "";

            getline(input2, number, ',');
            getline(input2, classifier, ',');
            getline(input2, id);
        }
        else {
            if(remove_at(text) && remove_href(text) && remove_threewords(text) && remove_tenwords(text)) {

                if(classifier[0] == '0') {//neg
                    string temp = check_first_letter(text);
                    Word word(temp, 0, 1);
                    indexer(word);
                } else {
                    string temp = check_first_letter(text);
                    Word word(temp, 1, 0);
                    indexer(word);
                }
            }//end nesting if
        }//end else

    }//end while:
}

//Index:

void Sentiment_Classifier::indexer(Word w) {
    bool flag = true;
    for(int i = 0; i < (int) word_vector.size(); i++) {
        if(w.getWord() == word_vector[i].getWord()) {
            word_vector[i].setPositive(w.getPositive() + word_vector[i].getPositive());
            word_vector[i].setNegative(w.getNegative() + word_vector[i].getNegative());
            flag = false;
            break;
        }
    }//end for
    if(flag) {
        word_vector.push_back(w);
    }
}

//ACCESSOR FUNCTIONS:

vector<Data_Set> Sentiment_Classifier::get_positive_vector() {
    return positive_classifier;
}

vector<Data_Set> Sentiment_Classifier::get_negative_vector() {
    return negative_classifier;
}

vector<string> Sentiment_Classifier::get_word_parser_test() {
    return word_parser_test;
}

vector<Word>& Sentiment_Classifier::get_word() {
    return word_vector;
}

//Functionalities:

bool Sentiment_Classifier::check_start_of_tweet(string& some_string) {
    //Build pre-cursor detection:
    if(some_string.size() < 13)
        return false;
    int pos_first_comma = 0;
    int pos_second_comma = 0;
    for(int i = 0; i < some_string.size(); i++) {
        if(some_string[i] == ',') {
            pos_first_comma = i;
            break;
        }
    }
    if(pos_first_comma == 0)
        return false;
    for(int j = pos_first_comma + 1; j < some_string.size(); j++) {
        if(some_string[j] == ',') {
            pos_second_comma = j;
            break;
        }
    }
    if(pos_second_comma == 0)
        return false;
    for(int k = pos_first_comma + 1; k < pos_second_comma; k++) {
        if(!isdigit(some_string[k]))
            return false;
    }

    return true;
}

bool Sentiment_Classifier::check_alphabet(string& some_string) {
    char some_char = some_string[1];
    if(isalpha(some_char))
        return true;
    else
        return false;
}
/*
bool Sentiment_Classifier::remove_non_alpha(String& some_string) {
    if(isalpha(some_string[0]) && isalpha(some_string[some_string.len() - 1])) {
        return true;
    }else {
        if(!isalpha(some_string[0])) {
            String temp = some_string;
            some_string = "";
            for(int i = 1; i < temp.len(); i++) {
                some_string += temp[i];
            }
        }//end nested if
        if(!isalpha(some_string[some_string.len() - 1])) {
            String temp = some_string;
            some_string = "";
            for(int i = 0; i < temp.len() - 1; i++) {
                some_string += temp[i];
            }
        }
        return false;
    }//end nesting else
}
*/
void Sentiment_Classifier::clean_non_alphabet(vector<string>& some_vector) {
    for(int i = 0; i < (int) some_vector.size(); i++) {
        if(!isalpha(some_vector[i][0])) {
            some_vector.erase(some_vector.begin() + i);
        }
    }
}
/*
String& Sentiment_Classifier::optimize_word(String& word) {
    //lowercase

    //get rid of @ words



    //get rid of all periods, commas, and apostrophes in a word.

    //if the first word is not a letter, get rid of the first letter function]

    //get rid of apostrophes

    //identify negating words.

    //get rid of commas

    //discard hrefs
}*/

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
string& Sentiment_Classifier::check_first_letter(string& word) {
    if (!isalpha(word[0])) {
            string temp;
            for(int i = 1; i < word.size(); i++) {
                temp += word[i];
            }
            word = temp;
            return word;
        }
        return word;
}
string& Sentiment_Classifier::remove_nonalpha(string& word) {
    string temp;
    for(int i = 0; i < word.size(); i++) {
        if(isalpha(word[i])) {
            temp += word[i];
        }//end if
    }//end for
    word = temp;

    return word;
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

void Sentiment_Classifier::test_data(char* file2, char* file3, char* file4) {
    ifstream input(file3);
    ifstream input2(file2);
    ofstream output(file4);

    string t, t2;
    getline(input, t);
    getline(input2, t2);
    string text;
    string number;
    string classifier;
    string id;
    string tweet;
    int tweet_count = 0;
    int totalscore = 0;
    int my_score = 0;
    int i = 0;
    while(i++ < 5000) {
        input >> text;
        if(check_start_of_tweet(text)) {

            if(!isblank(id[0])) {
                char temp;
                if(tweet_count < 0)
                    temp = '0';
                else
                    temp = '4';

              output<< id << "," << temp << endl;
            }

            tweet_count = 0;
            number = "";
            classifier = "";
            id = "";
            tweet = "";

            getline(input2, number, ',');
            getline(input2, id, ',');
            getline(input2, classifier, ',');
            getline(input2, tweet);
        }
        else {
            for(int i = 0; i < (int) word_vector.size(); i++) {
                if(text == word_vector[i].getWord()) {
                    tweet_count += word_vector[i].getPositive();
                    tweet_count -= word_vector[i].getNegative();
                }
            }
        }//end else
    }//end while:
    cout << "Total score: " << my_score << "/" << totalscore << endl;
}
/*
bool Sentiment_Classifier::identify_negation(String& word) {

}*/
