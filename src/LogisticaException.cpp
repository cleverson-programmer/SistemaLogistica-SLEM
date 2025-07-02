#include "LogisticaException.h"

LogisticaException::LogisticaException(const char* msg) {
    strncpy(mensagem, msg, sizeof(mensagem) - 1);
    mensagem[sizeof(mensagem) - 1] = '\0';
}

const char* LogisticaException::what() const noexcept {
    return mensagem;
}