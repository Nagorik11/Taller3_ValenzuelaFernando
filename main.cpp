#include <iostream>
#include "Laberinto.h"
#include "Robot.h"

using namespace std;

bool salir = false;

Laberinto lab = Laberinto();
Robot robot = Robot(lab);
/**
 * Opcion 1 del menu principal.
 * cargar laberinto
 * Instancia el laberinto y lo carga desde un archivo de texto usando los metodos contenidos en la clase Laberinto.
 */
void cargarLaberinto() {
    cout<<"A continuacion se cargara el laberinto desde el archivo laberinto.txt"<<endl;

    try {
        cout<<"Cargando laberinto..."<<endl;
        lab.load_file("laberinto.txt");
        lab.imprimirLaberinto();
        cout << "Laberinto cargado exitosamente." << endl;
        cout << endl;
    } catch (const exception& e) {
        cout << "!Error¡ no se encuentra el archivo.: " << e.what() << endl;
        cout << "Saliendo del programa" << endl;
        salir = true;
    }
}
/**
 * Opcion 2 del menu principal.
 * Configuracion inicial
 * contiene metodo de la clase Robot que permite ingresar las coordenadas de inicio y termino del robot.
 */
void configuracionInicial(){
    robot.ingresarCoordenadas();

}
/**
 * Opcion 3 del menu principal.
 * Resultados del recorrido, obtiene los caminos posibles y el camino mas corto.
 * solo se puede ejecutar si existen las coordenadas de inicio y termino bien definidas dentro del robot
 */
void resultados(){

    try {
        robot.explorarLaberinto();
        if(lab.getContenido(robot.getInicioFila(),robot.getInicioColumna()) == '#' ){//|| lab.getContenido(robot.getTerminoFila(),robot.getTerminoColumna()) == '#') ||(robot.getInicioFila() == robot.getTerminoFila() && robot.getInicioColumna() == robot.getTerminoColumna())){
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
 Menu principal del programa.
 * @return retorna la variable de estado que controla el loop.
 */
bool menuPrincipal() {
    bool salir = false;

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
                    salir = true;
                    break;
                default:
                    cout << "Opción inválida. Por favor, seleccione una opción válida." << endl;
                    break;
            }
        } catch (const invalid_argument& e) {
            cout << "Opción inválida. Por favor, ingrese un número válido." << endl;
            cin.clear();
        }
        cout << endl;
    }
    return salir;
}

/**
 * Main, ejecuta el menú principal haciendo uso de los métodos descritos anteriormente.
 * @return retorna 0 si el programa se ejecuta correctamente.
 */
int main() {
    cout<<"Bienvenido al programa de recorrido de laberintos"<<endl;
    while (!salir) {
        salir = menuPrincipal();
    }
    return 0;
}