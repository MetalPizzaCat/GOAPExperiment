/*
* This file contains worse kind of loging system, which is done by using macros
*/

#pragma once

#include <iostream>
#include <termcolor/termcolor.hpp>

#define PRINT(color,text) std::cout << color << text
#define PRINT_LINE(color,text) std::cout << color << text << termcolor::reset << std::endl
#define RESET_COLOR() std::cout << termcolor::reset << std::endl
#define SCREEN_CLEAR() cout << "\033[2J\033[1;1H"

