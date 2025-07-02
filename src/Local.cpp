#include "Local.h"
#include <iostream>
#include <cstring>

Local::Local() {}

Local::Local(const char* n, float x, float y) {
    strncpy(nome, n, sizeof(nome) - 1);
    nome[sizeof(nome) - 1] = '\0';
    coordenadaX = x;
    coordenadaY = y;
}

const char* Local::getNome() const { return nome; }
float Local::getX() const { return coordenadaX; }
float Local::getY() const { return coordenadaY; }

void Local::setNome(const char* n) {
    strncpy(nome, n, sizeof(nome) - 1);
    nome[sizeof(nome) - 1] = '\0';
}

void Local::setCoordenadas(float x, float y) {
    coordenadaX = x;
    coordenadaY = y;
}

void Local::exibir() const {
    std::cout << "Local: " << nome << " (X: " << coordenadaX << ", Y: " << coordenadaY << ")";
}