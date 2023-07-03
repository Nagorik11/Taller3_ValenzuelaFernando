//
// Created by nagorik on 21-06-23.
//

#ifndef _CLION_T3_VALENZUELAFERNANDO_ROBOT_H
#define _CLION_T3_VALENZUELAFERNANDO_ROBOT_H

#include "Laberinto.h"
#include <mutex>
#include <vector>

class Robot {
private:
    Laberinto& laberinto;
    int x_actual;
    int y_actual;
    int start_x;
    int start_y;
    int end_x;
    int end_y;
    mutex mtx;

public:
    Laberinto &getLaberinto() const;

    bool ValidarMovimiento(int x, int y);
    void setLaberinto(Laberinto &laberinto);

    int getXActual() const;
    void setXActual(int xActual);
    int getYActual() const;
    void setYActual(int yActual);
    int getInicioFila() const;
    void setInicioFila(int inicioFila);
    int getInicioColumna() const;
    void setInicioColumna(int inicioColumna);
    int getTerminoFila() const;
    virtual ~Robot();
    void setTerminoFila(int terminoFila);
    int getTerminoColumna() const;
    void setTerminoColumna(int terminoColumna);
    const mutex &getMtx() const;
    void setMtx(mutex &mtx);
    Robot(Laberinto& lab);
    void explorarLaberinto();
    void explorarCamino(int fila, int columna, std::vector<std::pair<int, int>> camino);
    void ingresarCoordenadas();
    bool isPositionVisited(int fila, int columna, const vector<pair<int, int>> &camino);
};

#endif //_CLION_T3_VALENZUELAFERNANDO_ROBOT_H
