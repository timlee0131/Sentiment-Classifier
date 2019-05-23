#define CATCH_CONFIG_RUNNER
#include <iostream>
#include <vector>
#include "DSString.h"
#include "Sentiment_Classifier.h"
#include "Word.h"
#include "catch.hpp"

using namespace std;

int runCatchTests(int argc, char* const argv[]) {
    return Catch::Session().run(argc, argv);
}

int main(int argc, char* argv[])
{
    if(argc == 1) {
        return runCatchTests(argc, argv);
    }

    Sentiment_Classifier clas;
    clas.word_parser(argv[1], argv[2]);
    clas.test_data(argv[3], argv[3], argv[4]);

    return 0;
}
