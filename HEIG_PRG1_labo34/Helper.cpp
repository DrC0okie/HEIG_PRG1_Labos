// File:        Helper.cpp
// Author:      Timothee Van Hove
// Date:        28.01.2022
// Description: Implementation of the Helper functions that can be used anywhere

#include "Helper.hpp"
#include <sstream>
#include <cstring>

const char BSLASH = '\\';

std::string details(const std::string &msg)
{
    std::stringstream ss;
    ss << std::endl << "Exception thrown, ";

    if (msg.length() > 0)
        ss << "error: " << msg << std::endl;
    else
        ss << "no details" << std::endl;

    return ss.str();
}

std::string details(const std::string &msg, int line)
{
    std::stringstream ss;
    ss << details(msg);

    if (line != -1)
        ss << "Line: " << line << std::endl;
    else
        ss << "Unknown line" << std::endl;

    return ss.str();
}

std::string details(const std::string &msg, int line, const char *func)
{
    std::stringstream ss;
    ss << details(msg, line);

    if (std::strlen(func) > 0)
        ss << "Function: " << std::string(func) << std::endl;
    else
        ss << "Unknown function" << std::endl;

    return ss.str();
}

std::string details(const std::string &msg, int line, const char *func,
                          const char *path)
{
    std:: string file = std::string(path)
                            .erase(0, std::string(path)
                            .find_last_of(BSLASH) + 1);      
    std::stringstream ss;
    ss << details(msg, line, func);

    if (std::strlen(path) > 0)
        ss << "File: " << file << std::endl;
    else
        ss << "Unknown file" << std::endl;

    return ss.str();
}