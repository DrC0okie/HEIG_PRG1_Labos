// File:        Helper.hpp
// Author:      Timothee Van Hove
// Date:        28.01.2022
// Description: Header of the Helper functions

#ifndef HELPERS_HPP
#define HELPERS_HPP
#include <string>

/** @brief Helper function that formats detials of an event (e.g exceptions)
 * @param msg The custom message to provide
 * @return Formatted string containing details about the event */
std::string details(const std::string &msg);

/** @brief Helper function that formats detials of an event (e.g exceptions)
 * @param msg The custom message to provide
 * @param line The line event occured
 * @return Formatted string containing details about the event */
std::string details(const std::string &msg, int line);

/** @brief Helper function that formats detials of an event (e.g exceptions)
 * @param msg The custom message to provide
 * @param line The line event occured
 * @param func The function in which the event occured
 * @return Formatted string containing details about the event */
std::string details(const std::string &msg, int line, const char *func);

/** @brief Helper function that formats detials of an event (e.g exceptions)
 * @param msg The custom message to provide
 * @param line The line event occured
 * @param func The function in which the event occured
 * @param path The path of the file in which the event occured
 * @return Formatted string containing details about the event */
std::string details(
    const std::string &msg, int line, const char *func, const char *path);
#endif