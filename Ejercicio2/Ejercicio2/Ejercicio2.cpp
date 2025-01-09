//Ejercicio2.cpp: Cálculo de la media de una matriz con OpenMP

#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main() {
    //Declara el número de filas y columnas de la matriz
    unsigned int filas, columnas;
    cout << "Introduce el numero de filas y columnas de la matriz: " << endl;
    cout << "Filas: ";
    cin >> filas;
    cout << "Columnas: ";
    cin >> columnas;

    //Crea una matriz bidimensional (Vector de vectores)
    vector<vector<int>> matriz(filas, vector<int>(columnas));

    //Inicializa la matriz con la suma de los índices de fila y columna La directiva OpenMP paraleliza los bucles anidados
#pragma omp parallel for collapse(2) shared(matriz) default(none) firstprivate(filas, columnas)
    for (unsigned int i = 0; i < filas; i++) {
        for (unsigned int j = 0; j < columnas; j++) {
            matriz[i][j] = i + j;
        }
    }

    //Variable para acumular la suma de los valores de la matriz
    double suma = 0.0;
    unsigned int totalElementos = filas * columnas;

    //Calcula la suma de los elementos de la matriz en paralelo
#pragma omp parallel for reduction(+:suma) collapse(2) shared(matriz) default(none) firstprivate(filas, columnas)
    for (unsigned int i = 0; i < filas; i++) {
        for (unsigned int j = 0; j < columnas; j++) {
            suma += matriz[i][j];
        }
    }

    //Calcula la media dividiendo la suma por el número total de elementos
    double media = suma / totalElementos;

    //Muestra el resultado de la media
    cout << "La media de los valores de la matriz es: " << media << endl;

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
