#include "SistemaLogistica.h"
#include <cassert>
#include <fstream>
#include <iostream>

void testPersistenciaVeiculo() {
    // Preparação
    SistemaLogistica sistema;
    sistema.adicionarLocal(Local("Base", 0.0f, 0.0f));
    sistema.adicionarVeiculo(Veiculo("ABC1234", "Fiat Ducato", 0));
    
    // Teste 1: Backup de veículos
    sistema.fazerBackup();
    
    // Verifica se o arquivo foi criado
    std::ifstream arquivo("veiculos.bin", std::ios::binary);
    assert(arquivo.good());
    arquivo.close();
    
    // Teste 2: Restauração de veículos
    SistemaLogistica sistema2;
    sistema2.restaurarDados();
    
    // Verifica se os dados foram restaurados corretamente
    std::ifstream arq("veiculos.bin", std::ios::binary);
    size_t numVeiculos;
    arq.read(reinterpret_cast<char*>(&numVeiculos), sizeof(numVeiculos));
    assert(numVeiculos == 1);
    arq.close();
    
    // Limpeza
    remove("locais.bin");
    remove("veiculos.bin");
    remove("pedidos.bin");
    remove("id_pedido.bin");
    
    std::cout << "Testes de persistencia de Veículos passaram!\n";
}

int main() {
    testPersistenciaVeiculo();
    return 0;
}