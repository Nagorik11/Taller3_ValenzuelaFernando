#include "Laberinto.h"
#include <fstream>
#include <iostream>
using namespace std;
/**
 * Constructor de la clase Laberinto.
 * Inicializa la matriz del laberinto con espacios en blanco.
 */
Laberinto::Laberinto() {
    for (int fila = 0; fila < FILAS; fila++) {
        for (int columna = 0; columna < COLUMNAS; columna++) {
            matriz[fila][columna] = ' ';
        }
    }
}
/**
 * Retorna el contenido de una posición de la matriz del laberinto.
 * si la fila es menor a 0 o mayor a FILAS o la columna es menor a 0 o mayor a COLUMNAS retorna un espacio en blanco.
 * @param fila posición en la fila.
 * @param columna posición en la columna.
 * @return
 */
bool Laberinto::esCamino (int fila, int columna) const {
    if ( fila < 0 || fila >= FILAS || columna < 0 || columna >= COLUMNAS ||  matriz[ fila ][ columna ] == '#') {
        return false;

    }
    return true;
}

/**
 * Retorna el número de filas del laberinto.
 * @return cantidad de filas.
 */
const int Laberinto::getFilas() {
    return FILAS;
}
/**
 * Retorna el número de columnas del laberinto.
 * @return cantidad de columnas.
 */
const int Laberinto::getColumnas() {
    return COLUMNAS;
}
/**
 * Imprime el laberinto en consola.
 */
void Laberinto::imprimirLaberinto() {
    for (int fila = 0; fila < FILAS; fila++) {
        for (int columna = 0; columna < COLUMNAS; columna++) {
            std::cout << matriz[fila][columna];
        }
        std::cout << std::endl;
    }

}

/**
 * Método que carga el laberinto desde un archivo de texto.
 * @param archivo nombre del archivo de texto que contiene el laberinto.
 */
void Laberinto::load_file(string archivo) {
    ifstream file(archivo);
    string line;
    int fila = 0;
    while (getline(file, line)) {
        vector<char> filaLaberinto;
        string caracter;
        for (char c : line) {
            if (c == ',') {
                if (!caracter.empty()) {
                    filaLaberinto.push_back(caracter[0]);
                    caracter.clear();
                }
            } else {
                caracter += c;
            }
        }
        if (!caracter.empty()) {
            filaLaberinto.push_back(caracter[0]);
        }
        if (fila < FILAS) {
            for (int columna = 0; columna < COLUMNAS && columna < filaLaberinto.size(); columna++) {
                matriz[fila][columna] = filaLaberinto[columna];
            }
            fila++;
        }
    }
    file.close();

}
/**
 * Obtiene el contenido de una coordenada presente dentro del laberinto.
 * @param fila objetivo a obtener.
 * @param columna objetivo a obtener.
 * @return Caracter contenido en la coordenada.
 */
char Laberinto::getContenido(int fila, int columna) {
    if (fila < 0 || fila >= FILAS || columna < 0 || columna >= COLUMNAS) {
        return '#';
    }
    return matriz[fila][columna];
}
/**
 * Destructor de la clase Laberinto.
 */
Laberinto::~Laberinto() {
delete this;
}
