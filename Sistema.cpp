//
// Created by nagorik on 05-07-23.
//

#include "Sistema.h"


using namespace std;
/**
 * Constructor de la clase Sistema
 */
Sistema::Sistema() : salir(false), lab(), robot(lab) {}

    void Sistema::cargarLaberinto() {
        cout << "A continuación se cargará el laberinto desde el archivo laberinto.txt" << endl;

        try {
            cout << "Cargando laberinto..." << endl;
            lab.load_file("laberinto.txt");
            lab.imprimirLaberinto();
            cout << "Laberinto cargado exitosamente." << endl;
            cout << endl;
        } catch (const exception &e) {
            cout << "!Error¡ No se encuentra el archivo: " << e.what() << endl;
            cout << "Saliendo del programa" << endl;
            salir = true;
        }
    }
/**
 * Método que solicita al usuario las coordenadas de inicio y termino del robot.
 */
    void Sistema::configuracionInicial() {
        robot.ingresarCoordenadas();
    }

    void Sistema::resultados(){

        try {
            robot.explorarLaberinto();
            if(lab.getContenido(robot.getInicioFila(),robot.getInicioColumna()) == '#' ){
                cout << "No es posible realizar el recorrido desde la coordenada ("<<robot.getInicioFila()<<","<<robot.getInicioColumna()<<") hasta la coordenada ("<<robot.getTerminoFila()<<","<<robot.getTerminoColumna()<<")"<<endl;
                salir = true;
            }
        }
        catch (const exception& e) {
            cout << "!Error¡ no se han definido las coordenadas de inicio y termino del robot.: " << e.what() << endl;
            cout << "Saliendo del programa" << endl;
            salir = true;

        }

    }


/**
 * Método que muestra el menú principal del programa.
 */
    void Sistema::menuPrincipal() {
        while (!salir) {
            cout << "----- Menú principal -----" << endl;
            cout << "1. Lectura del Tablero..." << endl;
            cout << "2. Configuración Inicial." << endl;
            cout << "3. Resultados." << endl;
            cout << "4. Salir." << endl;
            cout << "---------------------------" << endl;
            cout << "Ingrese una opción: ";

            string entrada;
            cin >> entrada;

            try {
                int opcion = stoi(entrada);
                switch (opcion) {
                    case 1:
                        cargarLaberinto();
                        break;
                    case 2:
                        configuracionInicial();
                        break;
                    case 3:
                        resultados();
                        break;
                    case 4:
                        Sistema::~Sistema();
                        salir = true;
                        break;
                    default:
                        cout << "Opción inválida. Por favor, seleccione una opción válida." << endl;
                        break;
                }
            } catch (const invalid_argument &e) {
                cout << "Opción inválida. Por favor, ingrese un número válido." << endl;
                cin.clear();
            }
            cout << endl;
        }
    }
/**
 * Destructor de la clase Sistema
 */
Sistema::~Sistema() {
    delete &lab;
    delete &robot;
}

