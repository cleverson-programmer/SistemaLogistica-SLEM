#include <iostream>

void testPersistenciaLocal();
void testPersistenciaVeiculo();
void testPersistenciaPedido();

int main() {
    std::cout << "=== INICIANDO TESTES ===" << std::endl;
    
    testPersistenciaLocal();
    testPersistenciaVeiculo();
    testPersistenciaPedido();
    
    std::cout << "=== TESTES CONCLUÍDOS ===" << std::endl;
    return 0;
}