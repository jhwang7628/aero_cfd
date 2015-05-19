#ifndef AUXFUNC_H
#define AUXFUNC_H

#include <string> 
#include <iostream>
#include <sstream>

/* 
 * to_string method c++11 
 */
template <typename T>
std::string to_string(T value)
{
    std::ostringstream os ;
    os << value ;
    return os.str() ;
}


#endif
