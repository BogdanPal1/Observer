#include "exceptions/exceptions.h"

Exception::Exception(std::string error) : _error(error)
{
}

const char *Exception::what() const noexcept
{ 
    return _error.c_str(); 
}
