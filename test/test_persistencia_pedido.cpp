#include "SistemaLogistica.h"
#include <cassert>
#include <fstream>
#include <iostream>

void testPersistenciaPedido() {
    // Preparação
    SistemaLogistica sistema;
    sistema.adicionarLocal(Local("Origem", 10.0f, 10.0f));
    sistema.adicionarLocal(Local("Destino", 20.0f, 20.0f));
    sistema.adicionarPedido(0, 1, 5.5f);
    
    // Teste 1: Backup de pedidos
    sistema.fazerBackup();
    
    // Verifica se o arquivo foi criado
    std::ifstream arquivo("pedidos.bin", std::ios::binary);
    assert(arquivo.good());
    arquivo.close();
    
    // Teste 2: Restauração de pedidos
    SistemaLogistica sistema2;
    sistema2.restaurarDados();
    
    // Verifica se os dados foram restaurados corretamente
    std::ifstream arq("pedidos.bin", std::ios::binary);
    size_t numPedidos;
    arq.read(reinterpret_cast<char*>(&numPedidos), sizeof(numPedidos));
    assert(numPedidos == 1);
    arq.close();
    
    // Teste 3: Verifica o próximo ID
    std::ifstream arqId("id_pedido.bin", std::ios::binary);
    int proximoId;
    arqId.read(reinterpret_cast<char*>(&proximoId), sizeof(proximoId));
    assert(proximoId == 2);
    arqId.close();
    
    // Limpeza
    remove("locais.bin");
    remove("veiculos.bin");
    remove("pedidos.bin");
    remove("id_pedido.bin");
    
    std::cout << "Testes de persistência de Pedidos passaram!\n";
}

int main() {
    testPersistenciaPedido();
    return 0;
}