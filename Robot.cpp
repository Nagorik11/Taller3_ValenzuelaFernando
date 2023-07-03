#include "Robot.h"
#include <iostream>
#include <thread>
#include <mutex>

/**
 *Constructor de la clase Robot.
 * @param lab
 */
Robot::Robot(Laberinto& lab) : laberinto(lab) {
    // Inicializar las variables miembro
    start_x = 0;
    start_y = 0;
    end_x = 0;
    end_y = 0;
    x_actual = 0;
    y_actual = 0;
}
/**
 * Explora caminos recursivamente
 */
void Robot::explorarLaberinto() {

        explorarCamino(start_x, start_y, {});

}
/**
 * Verifica si una posición ya fue visitada.
 * @param fila posición en la fila.
 * @param columna posición en la columna.
 * @param camino vector con las posiciones visitadas.
 */
void Robot::explorarCamino(int fila, int columna, vector<pair<int, int>> camino) {

    if (fila == end_x && columna == end_y) {
        mtx.lock();
        static int rutaCount = 1; // Contador de rutas encontradas
        cout << "Ruta " << rutaCount++ << ":" << endl;

        for (const auto& p : camino) {
            cout << "(" << p.first << "," << p.second << ")" << endl;
        }
        cout << "(" << end_x << "," << end_y << ") -> Fin" << endl;
        mtx.unlock();
        return;
    }
    mtx.unlock();

    if (!laberinto.esCamino(fila, columna) || laberinto.getContenido(fila, columna) != ' '
        || isPositionVisited(fila, columna, camino)) {
        return;

    }


    camino.push_back(std::make_pair(fila, columna));
    mtx.unlock();
    thread t1(&Robot::explorarCamino, this, fila + 1, columna, camino);
    thread t2(&Robot::explorarCamino, this, fila - 1, columna, camino);
    thread t3(&Robot::explorarCamino, this, fila, columna + 1, camino);
    thread t4(&Robot::explorarCamino, this, fila, columna - 1, camino);



    t1.join();
    t2.join();
    t3.join();
    t4.join();
}

/**
 * Verificar si la posición actual ya ha sido visitada
 * @param fila
 * @param columna
 * @param camino
 * @return
 */
bool Robot::isPositionVisited(int fila, int columna, const vector<pair<int, int>>& camino) {
    for (const auto& p : camino) {
        if (p.first == fila && p.second == columna) {
            return true;
        }
    }
    return false;
}
/**
 * Ingresar las coordenadas de inicio y término del robot
 */
void Robot::ingresarCoordenadas() {
    try {
        cout << "Ingrese fila de inicio (0-9)\nx1_i: ";
        cin >> start_x;
        if (start_x < 0 || start_x > 10) {
            throw out_of_range("Fila de inicio inválida. Debe estar entre 0 y 9.");
        }

        cout << "Ingrese columna de inicio (0-9)\ny1_f: ";
        cin >> start_y;
        if (start_y < 0 || start_y > 10) {
            throw out_of_range("Columna de inicio inválida. Debe estar entre 0 y 9.");
        }
        cout << "\nCoordenadas de inicio: " << "(" << start_x << "," << start_y << ")" << endl;

        cout << "Ingrese fila de término (0-9)\nx2_i:: ";
        cin >> end_x;
        if (end_x < 0 || end_x > 10) {
            throw out_of_range("Fila de término inválida. Debe estar entre 0 y 9.");
        }

        cout << "Ingrese columna de término (0-9)\ny2_f:: ";
        cin >> end_y;
        if (end_y < 0 || end_y > 10) {
            throw out_of_range("Columna de término inválida. Debe estar entre 0 y 9.");
        } else if (start_x == end_x && start_y == end_y) {
            throw out_of_range("\nCoordenadas de inicio y término no pueden ser iguales.");
        }
        cout << "\nCoordenadas de Término: " << "(" << end_x << "," << end_y << ")" << endl;
    } catch (const std::exception& e) {
        cerr << "Error: " << e.what() << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        ingresarCoordenadas();
    }
}
/*
 * getters y  setters
 */

Laberinto& Robot::getLaberinto() const {
    return laberinto;
}

void Robot::setLaberinto(Laberinto& laberinto) {
    Robot::laberinto = laberinto;
}

int Robot::getXActual() const {
    return x_actual;
}

void Robot::setXActual(int xActual) {
    x_actual = xActual;
}

int Robot::getYActual() const {
    return y_actual;
}

void Robot::setYActual(int yActual) {
    y_actual = yActual;
}

int Robot::getInicioFila() const {
    return start_x;
}

void Robot::setInicioFila(int inicioFila) {
    start_x = inicioFila;
}

int Robot::getInicioColumna() const {
    return start_y;
}

void Robot::setInicioColumna(int inicioColumna) {
    start_y = inicioColumna;
}

int Robot::getTerminoFila() const {
    return end_x;
}

void Robot::setTerminoFila(int terminoFila) {
    end_x = terminoFila;
}

int Robot::getTerminoColumna() const {
    return end_y;
}

void Robot::setTerminoColumna(int terminoColumna) {
    end_y = terminoColumna;
}

const mutex& Robot::getMtx() const {
    return mtx;
}

/**
 *
 * @param x
 * @param y
 * @return
 */
bool Robot::ValidarMovimiento(int x, int y) {
    if (x < 0 || x >= laberinto.getFilas() || y < 0 || y >= laberinto.getColumnas()) {
        return false;
    }

    if (laberinto.getContenido(x, y) != ' ') {
        return false;
    }

    int dx = abs(x - start_x);
    int dy = abs(y - start_y);

    if ((dx == 1 && dy == 0) || (dx == 0 && dy == 1)) {
        return true;
    }

    return false;
}
/**
 * Destructor
 */
Robot::~Robot() {
    delete[] this;

}
