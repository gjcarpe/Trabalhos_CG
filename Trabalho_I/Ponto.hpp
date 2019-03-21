#ifndef PONTO_HPP
#define PONTO_HPP
#include "Coordenada.hpp"
#include "Objeto.hpp"


class Ponto : public Objeto{

public:
    Coordenada coord1;

    Ponto(QString nome, Coordenada coord);
    Ponto(Coordenada coord);


    Ponto::Ponto(QString nome, Coordenada coord){
        this->nome = nome;
        this->coord1 = coord;
    }

    Ponto::Ponto(Coordenada coord){
        this->nome = "ponto_default";
        this->coord1 = coord;
    }
};

#endif // PONTO_HPP
