#ifndef SISTEMA_LOGISTICA_H
#define SISTEMA_LOGISTICA_H

#include <vector>
#include "Local.h"
#include "Veiculo.h"
#include "Pedido.h"
#include "LogisticaException.h"

class SistemaLogistica {
private:
    std::vector<Local> locais;
    std::vector<Veiculo> veiculos;
    std::vector<Pedido> pedidos;
    int proximoIdPedido;
    
    float calcularDistancia(int idLocal1, int idLocal2) const;
    
public:
    SistemaLogistica();
    
    // Métodos para Locais
    void adicionarLocal(const Local& local);
    void editarLocal(int id, const char* novoNome, float x, float y);
    void removerLocal(int id);
    void listarLocais() const;
    
    // Métodos para Veículos
    void adicionarVeiculo(const Veiculo& veiculo);
    void editarVeiculo(int id, const char* novaPlaca, const char* novoModelo, int novoLocal);
    void removerVeiculo(int id);
    void listarVeiculos() const;
    
    // Métodos para Pedidos
    void adicionarPedido(int origem, int destino, float peso);
    void editarPedido(int id, int novaOrigem, int novoDestino, float novoPeso);
    void removerPedido(int id);
    void listarPedidos() const;
    
    // Método para calcular rota de entrega
    void calcularRotaEntrega(int idPedido);
    void listarEntregasEmRota();
    
    // Métodos para backup e restauração
    void fazerBackup() const;
    void restaurarDados();
};

#endif