#include "SistemaLogistica.h"
#include <map>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <cmath>
#include <cstring>

std::map<int, int> pedidosEmRota;

// Construtor
SistemaLogistica::SistemaLogistica() : proximoIdPedido(1) {}

// Metodos para Locais
void SistemaLogistica::adicionarLocal(const Local& local) {
    for (const auto& l : locais) {
        if (strcmp(l.getNome(), local.getNome()) == 0) {
            throw LogisticaException("Local com este nome ja existe");
        }
    }
    locais.push_back(local);
}

void SistemaLogistica::editarLocal(int id, const char* novoNome, float x, float y) {
    if (id < 0 || static_cast<size_t>(id) >= locais.size()) {
        throw LogisticaException("ID de local invalido");
    }
    locais[id].setNome(novoNome);
    locais[id].setCoordenadas(x, y);
}

void SistemaLogistica::removerLocal(int id) {
    if (id < 0 || static_cast<size_t>(id) >= locais.size()) {
        throw LogisticaException("ID de local invalido");
    }
    locais.erase(locais.begin() + id);
}

void SistemaLogistica::listarLocais() const {
    if (locais.empty()) {
        std::cout << "Nenhum local cadastrado.\n";
        return;
    }
    for (size_t i = 0; i < locais.size(); ++i) {
        std::cout << "ID: " << i << " - ";
        locais[i].exibir();
        std::cout << "\n";
    }
}

// Métodos para Veiculos
void SistemaLogistica::adicionarVeiculo(const Veiculo& veiculo) {
    for (const auto& v : veiculos) {
        if (strcmp(v.getPlaca(), veiculo.getPlaca()) == 0) {
            throw LogisticaException("Veiculo com esta placa ja existe");
        }
    }
    veiculos.push_back(veiculo);
}

void SistemaLogistica::editarVeiculo(int id, const char* novaPlaca, const char* novoModelo, int novoLocal) {
    if (id < 0 || static_cast<size_t>(id) >= veiculos.size()) {
        throw LogisticaException("ID de veiculo invalido");
    }
    for (size_t i = 0; i < veiculos.size(); ++i) {
        if (i != static_cast<size_t>(id) && strcmp(veiculos[i].getPlaca(), novaPlaca) == 0) {
            throw LogisticaException("Placa ja existe em outro veiculo");
        }
    }
    veiculos[id] = Veiculo(novaPlaca, novoModelo, novoLocal);
    veiculos[id].setDisponivel(veiculos[id].isDisponivel());
}

void SistemaLogistica::removerVeiculo(int id) {
    if (id < 0 || static_cast<size_t>(id) >= veiculos.size()) {
        throw LogisticaException("ID de veiculo invalido");
    }
    if (!veiculos[id].isDisponivel()) {
        throw LogisticaException("Nao e possivel remover veiculo em uso");
    }
    veiculos.erase(veiculos.begin() + id);
}

void SistemaLogistica::listarVeiculos() const {
    if (veiculos.empty()) {
        std::cout << "Nenhum veiculo cadastrado.\n";
        return;
    }
    for (size_t i = 0; i < veiculos.size(); ++i) {
        std::cout << "ID: " << i << " - ";
        veiculos[i].exibir();
        std::cout << "\n";
    }
}

// Metodos para Pedidos
void SistemaLogistica::adicionarPedido(int origem, int destino, float peso) {
    if (origem < 0 || static_cast<size_t>(origem) >= locais.size() || destino < 0 || static_cast<size_t>(destino) >= locais.size()) {
        throw LogisticaException("Local de origem ou destino invalido");
    }
    pedidos.emplace_back(proximoIdPedido++, origem, destino, peso);
}

void SistemaLogistica::editarPedido(int id, int novaOrigem, int novoDestino, float novoPeso) {
    if (id < 1 || id >= proximoIdPedido) {
        throw LogisticaException("ID de pedido invalido");
    }
    for (auto& p : pedidos) {
        if (p.getId() == id) {
            if (p.isEntregue()) {
                throw LogisticaException("Nao e possivel editar pedido ja entregue");
            }
            if (novaOrigem < 0 || static_cast<size_t>(novaOrigem) >= locais.size() || 
                novoDestino < 0 || static_cast<size_t>(novoDestino) >= locais.size()) {
                throw LogisticaException("Local de origem ou destino invalido");
            }
            p = Pedido(id, novaOrigem, novoDestino, novoPeso);
            return;
        }
    }
    throw LogisticaException("Pedido nao encontrado");
}

void SistemaLogistica::removerPedido(int id) {
    if (id < 1 || id >= proximoIdPedido) {
        throw LogisticaException("ID de pedido invalido");
    }
    for (auto it = pedidos.begin(); it != pedidos.end(); ++it) {
        if (it->getId() == id) {
            if (it->isEntregue()) {
                throw LogisticaException("Nao e possivel remover pedido ja entregue");
            }
            pedidos.erase(it);
            return;
        }
    }
    throw LogisticaException("Pedido nao encontrado");
}

void SistemaLogistica::listarPedidos() const {
    if (pedidos.empty()) {
        std::cout << "Nenhum pedido cadastrado.\n";
        return;
    }
    for (const auto& p : pedidos) {
        p.exibir();
        std::cout << "\n";
    }
}

// Cálculo de rota
void SistemaLogistica::calcularRotaEntrega(int idPedido) {
    Pedido* pedido = nullptr;
    for (auto& p : pedidos) {
        if (p.getId() == idPedido && !p.isEntregue() && pedidosEmRota.count(p.getId()) == 0) {
            pedido = &p;
            break;
        }
    }
    if (!pedido) {
        throw LogisticaException("Pedido nao encontrado, ja entregue ou ja em rota.");
    }

    int idVeiculo = -1;
    float menorDistancia = std::numeric_limits<float>::max();
    for (size_t i = 0; i < veiculos.size(); ++i) {
        if (veiculos[i].isDisponivel()) {
            float dist = calcularDistancia(veiculos[i].getLocalAtual(), pedido->getOrigem());
            if (dist < menorDistancia) {
                menorDistancia = dist;
                idVeiculo = i;
            }
        }
    }
    if (idVeiculo == -1) {
        throw LogisticaException("Nenhum veiculo disponivel");
    }

    float distOrigemDestino = calcularDistancia(pedido->getOrigem(), pedido->getDestino());
    float distTotal = menorDistancia + distOrigemDestino;
    veiculos[idVeiculo].setDisponivel(false);

    // Associa pedido ao veiculo
    pedidosEmRota[pedido->getId()] = idVeiculo;

    std::cout << "\n=== ROTA CALCULADA ===\n";
    std::cout << "Pedido ID: " << pedido->getId() << "\n";
    std::cout << "Veiculo designado: " << veiculos[idVeiculo].getPlaca() << "\n";
    std::cout << "Distancia total: " << distTotal << " unidades\n";
    std::cout << "O pedido esta agora em rota. Confirme ou cancele a entrega pelo menu de entregas em rota.\n";
}

void SistemaLogistica::listarEntregasEmRota() {
    bool encontrou = false;
    std::cout << "\n=== PEDIDOS EM ROTA ===\n";
    for (const auto& par : pedidosEmRota) {
        int idPedido = par.first;
        int idVeiculo = par.second;
        auto it = std::find_if(pedidos.begin(), pedidos.end(), [idPedido](const Pedido& p){ return p.getId() == idPedido; });
        if (it != pedidos.end() && !it->isEntregue()) {
            it->exibir();
            std::cout << " | Veiculo: " << veiculos[idVeiculo].getPlaca() << "\n";
            encontrou = true;
        }
    }
    if (!encontrou) {
        std::cout << "Nenhum pedido em rota.\n";
        return;
    }

    std::cout << "Digite o ID do pedido para gerenciar (ou -1 para voltar): ";
    int idPedido;
    std::cin >> idPedido;
    if (idPedido == -1) return;

    auto it = pedidosEmRota.find(idPedido);
    if (it == pedidosEmRota.end()) {
        std::cout << "Pedido nao esta em rota.\n";
        return;
    }
    int idVeiculo = it->second;

    std::cout << "\n1. Confirmar entrega\n2. Cancelar entrega\nEscolha: ";
    int opcao;
    std::cin >> opcao;

    auto pedidoIt = std::find_if(pedidos.begin(), pedidos.end(), [idPedido](const Pedido& p){ return p.getId() == idPedido; });
    if (pedidoIt == pedidos.end()) {
        std::cout << "Pedido nao encontrado.\n";
        return;
    }
    Pedido& pedido = *pedidoIt;

    if (opcao == 1) {
        pedido.setEntregue(true);
        veiculos[idVeiculo].setLocalAtual(pedido.getDestino());
        veiculos[idVeiculo].setDisponivel(true);
        pedidosEmRota.erase(idPedido);
        std::cout << "Entrega confirmada.\n";
    } else if (opcao == 2) {
        veiculos[idVeiculo].setDisponivel(true);
        pedidosEmRota.erase(idPedido);
        std::cout << "Entrega cancelada. Pedido permanece pendente.\n";
    } else {
        std::cout << "Opção inválida.\n";
    }
}

// Backup e restauração
void SistemaLogistica::fazerBackup() const {
    std::ofstream arq("locais.bin", std::ios::binary);
    size_t n = locais.size();
    arq.write(reinterpret_cast<const char*>(&n), sizeof(n));
    arq.write(reinterpret_cast<const char*>(locais.data()), n * sizeof(Local));

    std::ofstream av("veiculos.bin", std::ios::binary);
    n = veiculos.size();
    av.write(reinterpret_cast<const char*>(&n), sizeof(n));
    av.write(reinterpret_cast<const char*>(veiculos.data()), n * sizeof(Veiculo));

    std::ofstream ap("pedidos.bin", std::ios::binary);
    n = pedidos.size();
    ap.write(reinterpret_cast<const char*>(&n), sizeof(n));
    ap.write(reinterpret_cast<const char*>(pedidos.data()), n * sizeof(Pedido));

    std::ofstream ai("id_pedido.bin", std::ios::binary);
    ai.write(reinterpret_cast<const char*>(&proximoIdPedido), sizeof(proximoIdPedido));

    std::cout << "Backup realizado com sucesso.\n";
}

void SistemaLogistica::restaurarDados() {
    std::ifstream arq("locais.bin", std::ios::binary);
    size_t n;
    arq.read(reinterpret_cast<char*>(&n), sizeof(n));
    locais.resize(n);
    arq.read(reinterpret_cast<char*>(locais.data()), n * sizeof(Local));

    std::ifstream av("veiculos.bin", std::ios::binary);
    av.read(reinterpret_cast<char*>(&n), sizeof(n));
    veiculos.resize(n);
    av.read(reinterpret_cast<char*>(veiculos.data()), n * sizeof(Veiculo));

    std::ifstream ap("pedidos.bin", std::ios::binary);
    ap.read(reinterpret_cast<char*>(&n), sizeof(n));
    pedidos.resize(n);
    ap.read(reinterpret_cast<char*>(pedidos.data()), n * sizeof(Pedido));

    std::ifstream ai("id_pedido.bin", std::ios::binary);
    if (ai)
        ai.read(reinterpret_cast<char*>(&proximoIdPedido), sizeof(proximoIdPedido));
    else {
        proximoIdPedido = 1;
        for (const auto& p : pedidos) {
            if (p.getId() >= proximoIdPedido)
                proximoIdPedido = p.getId() + 1;
        }
    }

    std::cout << "Dados restaurados com sucesso.\n";
}

// Função auxiliar
float SistemaLogistica::calcularDistancia(int idLocal1, int idLocal2) const {
    if (idLocal1 < 0 || static_cast<size_t>(idLocal1) >= locais.size() ||
        idLocal2 < 0 || static_cast<size_t>(idLocal2) >= locais.size()) {
        throw LogisticaException("Local invalido para cálculo de distancia");
    }

    float dx = locais[idLocal1].getX() - locais[idLocal2].getX();
    float dy = locais[idLocal1].getY() - locais[idLocal2].getY();
    return std::sqrt(dx * dx + dy * dy);
}