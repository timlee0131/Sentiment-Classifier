#include <iostream>
#include <vector>
#include <ctime>
#include "Test_Classifier.h"

using namespace std;

int main(int argc, char* argv[]) {
    clock_t begin = clock();
    //----------------------------------------------------------------------------

    Test_Classifier Tc;
    Tc.load_map(argv[1], argv[2]);
    cout << "Loading map with testing data finished..." << endl;
    Tc.parse_link(argv[3], argv[4]);
    cout << "Parsing all four files finished..." << endl;
    Tc.score_tester();

    //----------------------------------------------------------------------------
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "TIME: " << elapsed_secs << endl;
    return 0;
}
