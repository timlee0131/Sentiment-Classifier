#ifndef DATA_SET_H
#define DATA_SET_H

#include <string>
using namespace std;

class Data_Set {
private:
    string number;
    string user;
    string classifier;
    string id_number;
    string tweet;
public:
    //Accessors:
    string get_number();
    string get_classifier();
    string get_id_number();
    string get_user();
    string get_tweet();
    //Mutators:
    void set_number(string n);
    void set_classifier(string n);
    void set_id_number(string id);
    void set_user(string u);
    void set_tweet(string t);
};

#endif // DATA_SET_H
