#ifndef LOCAL_H
#define LOCAL_H

class Local {
private:
    char nome[100];
    float coordenadaX;
    float coordenadaY;
    
public:
    Local();
    Local(const char* n, float x, float y);
    
    const char* getNome() const;
    float getX() const;
    float getY() const;
    
    void setNome(const char* n);
    void setCoordenadas(float x, float y);
    
    void exibir() const;
};

#endif