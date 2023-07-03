#ifndef LABERINTO_H
#define LABERINTO_H

#include <string>
#include <vector>
using namespace std;
class Laberinto {
private:
    static const int FILAS = 10;
    static const int COLUMNAS = 10;
    char matriz[FILAS][COLUMNAS];
public:
    Laberinto();


    bool esCamino(int fila, int columna) const;

    static const int getFilas();

    static const int getColumnas();

    void imprimirLaberinto();

    virtual ~Laberinto();

    void load_file(string archivo);

    char getContenido(int fila, int columna);
};
#endif // LABERINTO_H
