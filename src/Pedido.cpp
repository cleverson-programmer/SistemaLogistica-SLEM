#include "Pedido.h"
#include <iostream>

Pedido::Pedido() : id(-1), idOrigem(-1), idDestino(-1), peso(0), entregue(false) {}

Pedido::Pedido(int i, int orig, int dest, float p) : 
    id(i), idOrigem(orig), idDestino(dest), peso(p), entregue(false) {}

int Pedido::getId() const { return id; }
int Pedido::getOrigem() const { return idOrigem; }
int Pedido::getDestino() const { return idDestino; }
float Pedido::getPeso() const { return peso; }
bool Pedido::isEntregue() const { return entregue; }

void Pedido::setEntregue(bool ent) { entregue = ent; }

void Pedido::exibir() const {
    std::cout << "Pedido ID: " << id << " - Peso: " << peso << "kg - ";
    std::cout << (entregue ? "Entregue" : "Pendente");
    std::cout << " - Origem ID: " << idOrigem << " -> Destino ID: " << idDestino;
}