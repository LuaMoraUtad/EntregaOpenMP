//Ejercicio6.cpp: Juego de la Vida de Conway paralelizado con OpenMP

#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

//Función para contar los vecinos vivos alrededor de una célula
int contarVecinosVivos(const vector<vector<int>>& tablero, int fila, int columna, int filas, int columnas) {
    int vecinos = 0;
    
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            
            int nuevaFila = (fila + i + filas) % filas;
            int nuevaColumna = (columna + j + columnas) % columnas;
            vecinos += tablero[nuevaFila][nuevaColumna];
        }
    }
    
    return vecinos;
}

//Evoluciona el tablero una generación según las reglas del Juego de la Vida
void evolucionarTablero(vector<vector<int>>& tablero, vector<vector<int>>& nuevoTablero, int filas, int columnas) {
    //Paraleliza el cálculo de la próxima generación
#pragma omp parallel for collapse(2) shared(tablero, nuevoTablero) default(none) firstprivate(filas, columnas)
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            int vecinosVivos = contarVecinosVivos(tablero, i, j, filas, columnas);
            
            if (tablero[i][j] == 1) {
                //Célula viva: Sobrevive si tiene 2 o 3 vecinos vivos
                nuevoTablero[i][j] = (vecinosVivos == 2 || vecinosVivos == 3) ? 1 : 0;
            }
            else {
                //Célula muerta: Revive si tiene exactamente 3 vecinos vivos
                nuevoTablero[i][j] = (vecinosVivos == 3) ? 1 : 0;
            }
        }
    }
}

int main() {
    //Lee las dimensiones del tablero y el número de generaciones
    int filas, columnas, generaciones;
    cout << "Introduce el numero de filas, columnas y generaciones: " << endl;
    cout << "Filas: ";
    cin >> filas;
    cout << "Columnas: ";
    cin >> columnas;
    cout << "Generaciones: ";
    cin >> generaciones;

    //Inicializa el tablero actual y el tablero para la próxima generación
    vector<vector<int>> tablero(filas, vector<int>(columnas));
    vector<vector<int>> nuevoTablero(filas, vector<int>(columnas));

    //Inicialización aleatoria del tablero actual. Paraleliza la inicialización para grandes dimensiones
#pragma omp parallel for collapse(2) shared(tablero) default(none) firstprivate(filas, columnas)
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            tablero[i][j] = rand() % 2;
        }
    }

    //Muestra el tablero inicial
    cout << "Tablero inicial:" << endl;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cout << (tablero[i][j] ? "#" : ".") << " ";
        }
        cout << endl;
    }

    //Evolución del tablero por el número especificado de generaciones
    for (int gen = 0; gen < generaciones; gen++) {
        evolucionarTablero(tablero, nuevoTablero, filas, columnas);
        tablero.swap(nuevoTablero);

        //Muestra el tablero actual
        cout << "Generacion " << gen + 1 << ":" << endl;
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                cout << (tablero[i][j] ? "#" : ".") << " ";
            }
            cout << endl;
        }
    }

    return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
