#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

class SymbolizerException : public std::exception {
public:
    SymbolizerException(const std::string &str)
        : str(str)
    {}
    
    virtual const char *what() const noexcept {
        return str.c_str();
    }

private:
    std::string str;
};

#endif // EXCEPTION_H