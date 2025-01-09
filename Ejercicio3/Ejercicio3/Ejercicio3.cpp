//Ejercicio3.cpp: Aproximación de Pi con OpenMP y la Regla del Trapecio

#include <iostream>
#include <omp.h>
#include <cmath>

using namespace std;

int main() {
    //Declara la cantidad de trapecios para la aproximación
    unsigned int num_trapecios;
    cout << "Introduce el numero de trapecios para aproximar pi: " << endl;
    cin >> num_trapecios;

    //Inicializa variables para la suma y el ancho de cada trapecio
    double suma = 0.0;
    double ancho = 1.0 / num_trapecios;

    //Cálculo paralelo de la aproximación de pi
#pragma omp parallel for reduction(+:suma) default(none) firstprivate(num_trapecios, ancho)
    for (unsigned int i = 0; i < num_trapecios; i++) {
        double x_i = i * ancho;
        double x_next = (i + 1) * ancho;

        //Evalua la función en los extremos del trapecio
        double f_i = 4.0 / (1.0 + x_i * x_i);
        double f_next = 4.0 / (1.0 + x_next * x_next);

        //Calcula el área del trapecio y acumularla en la suma
        suma += (f_i + f_next) * ancho / 2.0;
    }

    //Muestra el resultado de la aproximación
    cout << "El valor aproximado de pi es: " << suma << endl;

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
