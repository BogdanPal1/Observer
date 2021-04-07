#ifndef OBSERVER_EXCEPTIONS_H
#define OBSERVER_EXCEPTIONS_H

#include <exception>
#include <string>

/**
 * @brief The Exception class
 * 
 */
class Exception : public std::exception
{
public:
    /**
     * @brief Construct a new Exception object
     * 
     * @param error Error message
     */
    Exception(std::string error);

    /**
     * @brief return an error message
     * 
     * @return const char* error message
     */
    const char *what() const noexcept;

private:
    /**
     * @brief Error message
     * 
     */
    std::string _error; 
};

#endif // OBSERVER_EXCEPTIONS_H