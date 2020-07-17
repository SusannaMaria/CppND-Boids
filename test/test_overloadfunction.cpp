#include "gtest/gtest.h"
#include "boidconfig.hpp"
#include <cstdio>
#include <cassert>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <string>

std::string get_file_string(std::string file){
    std::ifstream ifs(file.c_str());
    return std::string((std::istreambuf_iterator<char>(ifs)),
                  (std::istreambuf_iterator<char>()));
}

TEST(boidconfig, printvalueint)
{
    BoidConfig bc;

    freopen("redir.txt", "w", stdout);
    bc.printValue(100);
    freopen("/dev/tty", "w", stdout);
    auto str =get_file_string("redir.txt");
    ASSERT_STREQ("string value of integer value is :100\n", str.c_str());

}

TEST(boidconfig, printvaluefloat)
{
    BoidConfig bc;
    freopen("redir.txt", "w", stdout);
    bc.printValue(0.1234f);
    freopen("/dev/tty", "w", stdout);
    auto str =get_file_string("redir.txt");
    ASSERT_STREQ("string value of float value is :0.123400\n", str.c_str());

}

TEST(boidconfig, printvaluechr)
{
    BoidConfig bc;
    freopen("redir.txt", "w", stdout);
    bc.printValue("C++ is great");
    freopen("/dev/tty", "w", stdout);
    auto str =get_file_string("redir.txt");
    ASSERT_STREQ("string value is :C++ is great\n", str.c_str());

}

TEST(boidconfig, printvaluestr)
{
    BoidConfig bc;
    freopen("redir.txt", "w", stdout);
    std::string val("C++ is much greater");
    bc.printValue(val);
    freopen("/dev/tty", "w", stdout);
    auto str =get_file_string("redir.txt");
    ASSERT_STREQ("string value is :C++ is much greater\n", str.c_str());

}