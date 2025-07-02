#ifndef PEDIDO_H
#define PEDIDO_H

class Pedido {
private:
    int id;
    int idOrigem;
    int idDestino;
    float peso;
    bool entregue;
    
public:
    Pedido();
    Pedido(int i, int orig, int dest, float p);
    
    int getId() const;
    int getOrigem() const;
    int getDestino() const;
    float getPeso() const;
    bool isEntregue() const;
    
    void setEntregue(bool ent);
    
    void exibir() const;
};

#endif