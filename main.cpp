#include <iostream>
#include <string>

#include "mdf/mdfreader.h"

int main()
{
    std::cout << "hello mdfplot" << std::endl;
    std::string mdfpath = "";
    mdf::MdfReader reader(mdfpath); 
    return 0;
}