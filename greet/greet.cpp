
#include "greet.h"

#include <algorithm>
#include <iostream>
#include <string>

#include <boost/algorithm/string.hpp>

void greet::say_greeting(const char* name)
{
    std::cout << "Hello, " << name << "!" << std::endl;
}

void greet::shout_greeting(const char* name)
{
    std::string tmp(name);
    boost::to_upper(tmp);

    std::cout << "HELLO, " << tmp << "!" << std::endl;
}
