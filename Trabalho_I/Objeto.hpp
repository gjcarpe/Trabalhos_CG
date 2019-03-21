#ifndef OBJETO_HPP
#define OBJETO_HPP

#include <string>
#include <iostream>
#include "ListaEnc.hpp"
#include "Coordenada.hpp"

using namespace std;


class Objeto // UM OBjeto pussui um nome e um lista encadeada de coordenadas
{
    public:
        QString nome;
        ListaEnc<Coordenada> pontos;

        QString toString();

        QString ObjetoGrafico::toString(){
        QString txt = "";
        for(int i=0;i<pontos.size();i++){
            txt += "( " + QString::number(pontos[i].getX()) + " , " + QString::number(pontos[i].getY()) + " )";
        }
        return txt;
    }
};

#endif
