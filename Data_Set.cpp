#include "Data_Set.h"

//Accessors:
string Data_Set::get_number() {return number;}
string Data_Set::get_classifier() {return classifier;}
string Data_Set::get_id_number() {return id_number;}
string Data_Set::get_user() {return user;}
string Data_Set::get_tweet() {return tweet;}

//Mutators:
void Data_Set::set_number(string n) {number = n;}
void Data_Set::set_classifier(string n) {classifier = n;}
void Data_Set::set_id_number(string id) {id_number = id;}
void Data_Set::set_user(string u) {user = u;}
void Data_Set::set_tweet(string t) {tweet = t;}
