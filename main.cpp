#include <iostream>

using namespace std;
#include "Session.h"
#include "FiveRuleTester.cpp"

int main(int argc, char** argv){
    std::cout << "Starting tests..." << std::endl;


    FiveRuleTestTree<MaxRankTree>();
    FiveRuleTestTree<RootTree>();

    /*Tester tester(argv[1]);

    tester.run_tests();*/

    return 0;
}
