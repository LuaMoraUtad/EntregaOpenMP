//Ejercicio5.cpp: Resolución de sistemas de ecuaciones con el método de Gauss-Seidel paralelo usando OpenMP

#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

using namespace std;

//Método de Gauss-Seidel para resolver Ax = b
void gaussSeidel(const vector<vector<double>>& A, const vector<double>& b, vector<double>& x, int maxIter, double tol) {
    int n = A.size();
    vector<double> x_old(n);

    for (int iter = 0; iter < maxIter; iter++) {
        x_old = x;

        //Actualización de cada componente de x en paralelo
#pragma omp parallel for shared(A, b, x, x_old) default(none) firstprivate(n)
        for (int i = 0; i < n; i++) {
            double sum = 0.0;
            
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sum += A[i][j] * x[j];
                }
            }
            
            x[i] = (b[i] - sum) / A[i][i];
        }

        //Comprueba convergencia calculando el error absoluto
        double error = 0.0;
#pragma omp parallel for reduction(+:error) shared(x, x_old) default(none) firstprivate(n)
        for (int i = 0; i < n; i++) {
            error += fabs(x[i] - x_old[i]);
        }

        //Si el error es menor que la tolerancia, se considera convergencia
        if (error < tol) {
            cout << "Convergencia alcanzada en iteracion " << iter + 1 << endl;
            
            return;
        }
    }
    
    cout << "No se alcanzo la convergencia despues de " << maxIter << " iteraciones." << endl;
}

int main() {
    //Lee el tamaño del sistema (n x n)
    int n;
    cout << "Introduce el tamanio del sistema (n x n): " << endl;
    cin >> n;

    //Declara la matriz de coeficientes A y los vectores b y x
    vector<vector<double>> A(n, vector<double>(n));
    vector<double> b(n), x(n, 0.0);

    //Inicialización de A y b. A es una matriz diagonal dominante para garantizar la convergencia
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = (i == j) ? 10.0 : 1.0;
        }
        
        b[i] = n + i;
    }

    //Parámetros para el método de Gauss-Seidel
    int maxIter = 1000;
    double tol = 1e-6;

    //Mide el tiempo de ejecución
    double timeIni = omp_get_wtime();
    gaussSeidel(A, b, x, maxIter, tol);
    double timeFin = omp_get_wtime();

    //Muestra el tiempo de ejecución
    cout << "Tiempo de ejecucion: " << (timeFin - timeIni) << " segundos" << endl;

    //Muestra la solución obtenida
    cout << "Solucion obtenida: " << endl;
    for (int i = 0; i < n; i++) {
        cout << "x[" << i << "] = " << x[i] << endl;
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
