#ifndef SISTEMA_H
#define SISTEMA_H

#include <iostream>
#include "Laberinto.h"
#include "Robot.h"

using namespace std;

class Sistema {
private:
    bool salir;
    Laberinto lab;
    Robot robot;
public:
    virtual ~Sistema();

public:
    Sistema();
    void cargarLaberinto();
    void configuracionInicial();
    void resultados();
    void menuPrincipal();
};

#endif // SISTEMA_H
