#include "Menus.h"
#include "SistemaLogistica.h"
#include <iostream>

int main() {
    SistemaLogistica sistema;
    int opcao;
    
    do {
        exibirMenu();
        std::cin >> opcao;
        
        try {
            switch (opcao) {
                case 1:
                    menuLocais(sistema);
                    break;
                case 2:
                    menuVeiculos(sistema);
                    break;
                case 3:
                    menuPedidos(sistema);
                    break;
                case 4:
                    sistema.listarLocais();
                    break;
                case 5:
                    sistema.listarVeiculos();
                    break;
                case 6:
                    sistema.listarPedidos();
                    break;
                case 7: {
                    int idPedido;
                    sistema.listarPedidos();
                    std::cout << "ID do pedido para calcular rota: ";
                    std::cin >> idPedido;
                    sistema.calcularRotaEntrega(idPedido);
                    break;
                }
                case 8:
                    sistema.fazerBackup();
                    break;
                case 9:
                    sistema.restaurarDados();
                    break;
                case 10:
                    sistema.listarEntregasEmRota();
                    break;
                case 0:
                    std::cout << "Saindo do sistema...\n";
                    break;
                default:
                    std::cout << "Opção inválida!\n";
            }
        } catch (const LogisticaException& e) {
            std::cerr << "Erro: " << e.what() << "\n";
        } catch (...) {
            std::cerr << "Erro desconhecido!\n";
        }
        
    } while (opcao != 0);
    
    return 0;
}