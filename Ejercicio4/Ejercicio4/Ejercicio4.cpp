//Ejercicio4.cpp: Ordenación con Merge Sort paralelo usando OpenMP

#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

//Función para fusionar dos mitades de un vector ordenado
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    //Crea sublistas temporales
    vector<int> L(n1), R(n2);

    //Copia datos a las sublistas
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];

    //Fusiona las sublistas de nuevo en arr
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        }
        else {
            arr[k++] = R[j++];
        }
    }

    //Copia los elementos restantes de L, si los hay
    while (i < n1) arr[k++] = L[i++];

    //Copia los elementos restantes de R, si los hay
    while (j < n2) arr[k++] = R[j++];
}

//Función recursiva para el algoritmo Merge Sort. Divide el vector en mitades, las ordena y luego las fusiona
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        //Ordena recursivamente las mitades
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        //Fusiona las mitades ordenadas
        merge(arr, left, mid, right);
    }
}

//Versión paralela del algoritmo Merge Sort. Divide las llamadas recursivas entre diferentes hilos usando OpenMP
void parallelMergeSort(vector<int>& arr, int left, int right, int depth) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        if (depth > 0) {
            //Divide tareas entre hilos usando OpenMP
#pragma omp parallel sections
            {
#pragma omp section
                parallelMergeSort(arr, left, mid, depth - 1);

#pragma omp section
                parallelMergeSort(arr, mid + 1, right, depth - 1);
            }
        }
        else {
            //Realiza ordenación secuencial si se alcanza el límite de profundidad
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
        }

        //Fusiona las mitades ordenadas
        merge(arr, left, mid, right);
    }
}

int main() {
    //Solicita el tamaño del vector
    unsigned int N;
    cout << "Introduce el tamanio del vector a ordenar: " << endl;
    cin >> N;

    //Crea e inicializa el vector con valores aleatorios
    vector<int> arr(N);
#pragma omp parallel for default(none) shared(arr, N)
    for (unsigned int i = 0; i < N; i++) {
        arr[i] = rand() % 100;
    }

    //Muestra el vector original
    cout << "Vector original: " << endl;
    for (unsigned int i = 0; i < min(N, 20u); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    //Ordena el vector usando la versión paralela de Merge Sort
    double timeIni = omp_get_wtime(); //Inicio del cronómetro
    parallelMergeSort(arr, 0, N - 1, omp_get_max_threads());
    double timeFin = omp_get_wtime(); //Fin del cronómetro

    //Muestra el vector ordenado
    cout << "Vector ordenado: " << endl;
    for (unsigned int i = 0; i < min(N, 20u); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    //Muestra el tiempo de ejecución
    cout << "Tiempo de ejecucion en paralelo: " << (timeFin - timeIni) << " segundos" << endl;

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
