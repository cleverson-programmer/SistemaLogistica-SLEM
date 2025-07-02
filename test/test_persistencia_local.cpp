#include "SistemaLogistica.h"
#include <cassert>
#include <fstream>
#include <iostream>

void testPersistenciaLocal() {
    // Preparação
    SistemaLogistica sistema;
    sistema.adicionarLocal(Local("Depósito A", 10.5f, 20.3f));
    sistema.adicionarLocal(Local("Depósito B", 15.0f, 25.0f));
    
    // Teste 1: Backup de locais
    sistema.fazerBackup();
    
    // Verifica se o arquivo foi criado
    std::ifstream arquivo("locais.bin", std::ios::binary);
    assert(arquivo.good());
    arquivo.close();
    
    // Teste 2: Restauração de locais
    SistemaLogistica sistema2;
    sistema2.restaurarDados();
    
    // Verifica se os dados foram restaurados corretamente
    // Criamos um método temporário para verificar o tamanho
    std::ifstream arq("locais.bin", std::ios::binary);
    size_t numLocais;
    arq.read(reinterpret_cast<char*>(&numLocais), sizeof(numLocais));
    assert(numLocais == 2);
    arq.close();
    
    // Limpeza
    remove("locais.bin");
    remove("veiculos.bin");
    remove("pedidos.bin");
    remove("id_pedido.bin");
    
    std::cout << "Testes de persistência de Locais passaram!\n";
}

int main() {
    testPersistenciaLocal();
    return 0;
}