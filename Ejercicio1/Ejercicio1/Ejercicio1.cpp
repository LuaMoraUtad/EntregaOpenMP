//Ejercicio1.cpp: Paralelización del cálculo de vectores con OpenMP

#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main() {
    //Solicitar al usuario el tamaño del vector
    unsigned int N;
    cout << "Introduce el tamanio del vector: " << endl;
    cin >> N;

    //Variables para medir el tiempo de ejecución
    double timeIni, timeFin;

    //Declarar los vectores x e y
    vector<int> x(N), y(N);

    //Inicialización de los vectores
    for (int i = 0; i < N; i++) {
        x[i] = 0;
        y[i] = i;
    }

    //Registra el tiempo inicial
    timeIni = omp_get_wtime();

    //Directiva OpenMP para paralelizar el bucle
#pragma omp parallel for shared(x, y) default(none) firstprivate(N)
    for (int i = 1; i < N; i++) {
        x[i] = y[i - 1] * 2;
        y[i] = y[i] + i;
    }

    //Registra el tiempo final
    timeFin = omp_get_wtime();

    //Muestra el tiempo total de ejecución en paralelo
    cout << "Tiempo de ejecucion en paralelo: " << (timeFin - timeIni) << " segundos" << endl;

    //Muestra los primeros 10 elementos de los vectores resultantes
    cout << "Valores finales de los vectores (Parcial): " << endl;
    for (int i = 0; i < min(N, 10u); i++) {
        cout << "x[" << i << "] = " << x[i] << ", y[" << i << "] = " << y[i] << endl;
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
