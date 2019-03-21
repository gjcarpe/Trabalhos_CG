#ifndef POLIGONO_HPP
#define POLIGONO_HPP
#include "Objeto.hpp"

class Poligono : public Objeto
{
public:
    Poligono();
    Poligono(QString nome);
    Poligono(QString nome, Coordenada coord);


    void adicionarPonto(Coordenada ponto);
    void adicionarNome(QString nome);


    Poligono::Poligono()
    {
        this->pontos = ListaEnc<Coordenada>;
    }

    Poligono::Poligono(QString vnome)
    {
        this->nome = vnome;
        this->pontos = ListaEnc<Coordenada>;
    }

    Poligono::Poligono(QString vnome, Coordenada coord)
    {
        this->nome = vnome;
        this->pontos = ListaEnc<Coordenada>;
        this->adicionarPonto(coord);
    }

    void Poligono::adicionarPonto(Coordenada vponto){
        pontos.adicionaNoInicio(vponto);
    }

    void Poligono::adicionarNome(QString vnome){
        nome = vnome;
    }
};

#endif // POLIGONO_HPP
