//Ejercicio7.cpp: Transformada Rápida de Fourier (FFT) paralelizada con OpenMP

#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <omp.h>

using namespace std;

const double PI = acos(-1);

typedef complex<double> Complex;

//Función para calcular la Transformada Rápida de Fourier (FFT)
void fft(vector<Complex>& a, bool invert) {
    int n = a.size();
    
    if (n == 1) return;

    //Divide el vector en partes pares e impares
    vector<Complex> a0(n / 2), a1(n / 2);
    
    for (int i = 0; i < n / 2; i++) {
        a0[i] = a[i * 2];
        a1[i] = a[i * 2 + 1];
    }

    //Llamadas recursivas para calcular la FFT de las subpartes
    fft(a0, invert);
    fft(a1, invert);

    //Calcula los factores de rotación (Raíces de la unidad)
    double angle = 2 * PI / n * (invert ? -1 : 1);
    Complex w(1), wn(cos(angle), sin(angle));

    //Fusiona los resultados de las partes pares e impares
#pragma omp parallel for shared(a, a0, a1, w, wn) default(none) firstprivate(n)
    for (int i = 0; i < n / 2; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        
        if (invert) {
            //Normaliza si es la transformada inversa
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
        
        w *= wn;
    }
}

int main() {
    //Lee el tamaño de la señal (Debe ser potencia de 2)
    int n;
    cout << "Introduce el tamanio de la senal (Potencia de 2): " << endl;
    cin >> n;

    //Crea e inicializa el vector de números complejos
    vector<Complex> signal(n);

    //Inicializa la señal con valores aleatorios en la parte real (Parte imaginaria = 0)
#pragma omp parallel for shared(signal) default(none) firstprivate(n)
    for (int i = 0; i < n; i++) {
        signal[i] = Complex(rand() % 100, 0);
    }

    //Muestra la señal original
    cout << "Senal original:" << endl;
    for (int i = 0; i < n; i++) {
        cout << signal[i] << " ";
    }
    cout << endl;

    //Calcula la FFT
    double timeIni = omp_get_wtime();
    fft(signal, false);
    double timeFin = omp_get_wtime();

    //Muestra los resultados de la FFT
    cout << "Transformada de Fourier (FFT):" << endl;
    for (int i = 0; i < n; i++) {
        cout << signal[i] << " ";
    }
    cout << endl;

    //Muestra el tiempo de ejecución
    cout << "Tiempo de ejecucion de la FFT: " << (timeFin - timeIni) << " segundos" << endl;

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
