#ifndef LOGISTICA_EXCEPTION_H
#define LOGISTICA_EXCEPTION_H

#include <exception>
#include <cstring>

class LogisticaException : public std::exception {
private:
    char mensagem[200];
    
public:
    LogisticaException(const char* msg);
    const char* what() const noexcept override;
};

#endif