#include <iostream>
#include "Session.h"

int main(int argc, char** argv){
    std::cout << "Welcome my lord." << std::endl;

    if(argc != 2){
        std::cout << "usage cTrace <config_path>" << std::endl;
        return 0;
    }
    Session sess(argv[1]);
    sess.simulate();
    return 0;
}
