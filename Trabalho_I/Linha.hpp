#ifndef LINHA_HPP
#define LINHA_HPP
#include "Coordenada.hpp"
#include "Objeto.hpp"

class Linha: public Objeto{

public:
    Coordenada coord1;
    Coordenada coord2;

    Linha();
    Linha(QString nome, Coordenada coord1, Coordenada coord2);

    Linha::Linha(QString nome, Coordenada coord1, Coordenada coord2)
{
    this->nome = nome;
    this->coord1 = coord1;
    this->coord2 = coord2;
    pontos = ListaEnc<Coordenada>;
    pontos.adicionaNoInicio(coord1);
    pontos.adicionaNoInicio(coord2);
}


};

#endif // RETA_HPP
