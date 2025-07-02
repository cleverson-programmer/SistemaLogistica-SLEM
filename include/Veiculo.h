#ifndef VEICULO_H
#define VEICULO_H

class Veiculo {
private:
    char placa[20];
    char modelo[50];
    bool disponivel;
    int idLocalAtual;
    
public:
    Veiculo();
    Veiculo(const char* p, const char* m, int local);
    
    const char* getPlaca() const;
    const char* getModelo() const;
    bool isDisponivel() const;
    int getLocalAtual() const;
    
    void setDisponivel(bool disp);
    void setLocalAtual(int local);
    
    void exibir() const;
};

#endif