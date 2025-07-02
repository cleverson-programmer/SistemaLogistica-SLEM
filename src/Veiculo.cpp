#include "Veiculo.h"
#include <iostream>
#include <cstring>

Veiculo::Veiculo() : disponivel(true), idLocalAtual(-1) {}

Veiculo::Veiculo(const char* p, const char* m, int local) {
    strncpy(placa, p, sizeof(placa) - 1);
    placa[sizeof(placa) - 1] = '\0';
    strncpy(modelo, m, sizeof(modelo) - 1);
    modelo[sizeof(modelo) - 1] = '\0';
    disponivel = true;
    idLocalAtual = local;
}

const char* Veiculo::getPlaca() const { return placa; }
const char* Veiculo::getModelo() const { return modelo; }
bool Veiculo::isDisponivel() const { return disponivel; }
int Veiculo::getLocalAtual() const { return idLocalAtual; }

void Veiculo::setDisponivel(bool disp) { disponivel = disp; }
void Veiculo::setLocalAtual(int local) { idLocalAtual = local; }

void Veiculo::exibir() const {
    std::cout << "Veiculo: " << modelo << " (Placa: " << placa << ") - ";
    std::cout << (disponivel ? "Disponivel" : "Ocupado");
    std::cout << " - Local atual ID: " << idLocalAtual;
}