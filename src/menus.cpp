#include "Menus.h"
#include <iostream>

void exibirMenu() {
    std::cout << "\n=== SISTEMA DE LOGISTICA ===\n";
    std::cout << "1. Cadastro de Locais\n";
    std::cout << "2. Cadastro de Veiculos\n";
    std::cout << "3. Cadastro de Pedidos\n";
    std::cout << "4. Listar Locais\n";
    std::cout << "5. Listar Veiculos\n";
    std::cout << "6. Listar Pedidos\n";
    std::cout << "7. Calcular Rota de Entrega\n";
    std::cout << "8. Fazer Backup de Dados\n";
    std::cout << "9. Restaurar Dados\n";
    std::cout << "10. Gerenciar entregas em rota\n";
    std::cout << "0. Sair\n";
    std::cout << "Escolha uma opcao: ";
}

void menuLocais(SistemaLogistica& sistema) {
    int opcao;
    do {
        std::cout << "\n=== CADASTRO DE LOCAIS ===\n";
        std::cout << "1. Adicionar Local\n";
        std::cout << "2. Editar Local\n";
        std::cout << "3. Remover Local\n";
        std::cout << "4. Listar Locais\n";
        std::cout << "0. Voltar\n";
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;
        
        try {
            switch (opcao) {
                case 1: {
                    char nome[100];
                    float x, y;
                    std::cout << "Nome do local: ";
                    std::cin.ignore();
                    std::cin.getline(nome, 100);
                    std::cout << "Coordenada X: ";
                    std::cin >> x;
                    std::cout << "Coordenada Y: ";
                    std::cin >> y;
                    sistema.adicionarLocal(Local(nome, x, y));
                    break;
                }
                case 2: {
                    int id;
                    char nome[100];
                    float x, y;
                    sistema.listarLocais();
                    std::cout << "ID do local a editar: ";
                    std::cin >> id;
                    std::cout << "Novo nome: ";
                    std::cin.ignore();
                    std::cin.getline(nome, 100);
                    std::cout << "Nova coordenada X: ";
                    std::cin >> x;
                    std::cout << "Nova coordenada Y: ";
                    std::cin >> y;
                    sistema.editarLocal(id, nome, x, y);
                    break;
                }
                case 3: {
                    int id;
                    sistema.listarLocais();
                    std::cout << "ID do local a remover: ";
                    std::cin >> id;
                    sistema.removerLocal(id);
                    break;
                }
                case 4:
                    sistema.listarLocais();
                    break;
            }
        } catch (const LogisticaException& e) {
            std::cerr << "Erro: " << e.what() << "\n";
        }
    } while (opcao != 0);
}

void menuVeiculos(SistemaLogistica& sistema) {
    int opcao;
    do {
        std::cout << "\n=== CADASTRO DE VEICULOS ===\n";
        std::cout << "1. Adicionar Veiculo\n";
        std::cout << "2. Editar Veiculo\n";
        std::cout << "3. Remover Veiculo\n";
        std::cout << "4. Listar Veiculos\n";
        std::cout << "0. Voltar\n";
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;
        
        try {
            switch (opcao) {
                case 1: {
                    char placa[20], modelo[50];
                    int local;
                    
                    std::cout << "Placa: ";
                    std::cin.ignore();
                    std::cin.getline(placa, 20);
                    
                    std::cout << "Modelo: ";
                    std::cin.getline(modelo, 50);
                    
                    sistema.listarLocais();
                    std::cout << "ID do local atual: ";
                    std::cin >> local;
                    
                    sistema.adicionarVeiculo(Veiculo(placa, modelo, local));
                    break;
                }
                case 2: {
                    int id, local;
                    char placa[20], modelo[50];
                    
                    sistema.listarVeiculos();
                    std::cout << "ID do veiculo a editar: ";
                    std::cin >> id;
                    
                    std::cout << "Nova placa: ";
                    std::cin.ignore();
                    std::cin.getline(placa, 20);
                    
                    std::cout << "Novo modelo: ";
                    std::cin.getline(modelo, 50);
                    
                    sistema.listarLocais();
                    std::cout << "Novo local atual: ";
                    std::cin >> local;
                    
                    sistema.editarVeiculo(id, placa, modelo, local);
                    break;
                }
                case 3: {
                    int id;
                    sistema.listarVeiculos();
                    std::cout << "ID do veiculo a remover: ";
                    std::cin >> id;
                    sistema.removerVeiculo(id);
                    break;
                }
                case 4:
                    sistema.listarVeiculos();
                    break;
            }
        } catch (const LogisticaException& e) {
            std::cerr << "Erro: " << e.what() << "\n";
        }
    } while (opcao != 0);
}

void menuPedidos(SistemaLogistica& sistema) {
    int opcao;
    do {
        std::cout << "\n=== CADASTRO DE PEDIDOS ===\n";
        std::cout << "1. Adicionar Pedido\n";
        std::cout << "2. Editar Pedido\n";
        std::cout << "3. Remover Pedido\n";
        std::cout << "4. Listar Pedidos\n";
        std::cout << "0. Voltar\n";
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;
        
        try {
            switch (opcao) {
                case 1: {
                    int origem, destino;
                    float peso;
                    
                    sistema.listarLocais();
                    std::cout << "ID do local de origem: ";
                    std::cin >> origem;
                    
                    std::cout << "ID do local de destino: ";
                    std::cin >> destino;
                    
                    std::cout << "Peso do item (kg): ";
                    std::cin >> peso;
                    
                    sistema.adicionarPedido(origem, destino, peso);
                    break;
                }
                case 2: {
                    int id, origem, destino;
                    float peso;
                    
                    sistema.listarPedidos();
                    std::cout << "ID do pedido a editar: ";
                    std::cin >> id;
                    
                    sistema.listarLocais();
                    std::cout << "Novo ID de origem: ";
                    std::cin >> origem;
                    
                    std::cout << "Novo ID de destino: ";
                    std::cin >> destino;
                    
                    std::cout << "Novo peso (kg): ";
                    std::cin >> peso;
                    
                    sistema.editarPedido(id, origem, destino, peso);
                    break;
                }
                case 3: {
                    int id;
                    sistema.listarPedidos();
                    std::cout << "ID do pedido a remover: ";
                    std::cin >> id;
                    sistema.removerPedido(id);
                    break;
                }
                case 4:
                    sistema.listarPedidos();
                    break;
            }
        } catch (const LogisticaException& e) {
            std::cerr << "Erro: " << e.what() << "\n";
        }
    } while (opcao != 0);
}