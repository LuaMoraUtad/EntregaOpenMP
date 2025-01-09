#EntregaOpenMP

#Ejercicio 1: Paralelización del cálculo de vectores con OpenMP
##Descripción del ejercicio
El objetivo es comparar el rendimiento de una implementación paralela y secuencial del cálculo de dos vectores utilizando OpenMP.

###Código Paralelo
El código utiliza OpenMP para paralelizar un bucle que calcula los valores de dos vectores ('x' e 'y'). Este enfoque permite distribuir las iteraciones entre múltiples hilos, reduciendo el tiempo de ejecución para tamaños de vectores grandes.

###Código Secuencial
En la versión secuencial, el mismo cálculo se realiza sin paralelización, ejecutando las iteraciones de forma consecutiva.
Se midió el tiempo de ejecución para ambas versiones usando 'omp_get_wtime()'.

##Análisis de rendimiento
###Observaciones
-"Speedup": El "speedup" mejora significativamente para tamaños grandes de vectores.
-"Overhead": Para tamaños pequeños, el "overhead" de crear y sincronizar hilos limita los beneficios del paralelismo.
-"Eficiencia": La paralelización se beneficia de un número adecuado de iteraciones que justifiquen el uso de múltiples hilos.

##Conclusiones
-La paralelización con OpenMP es efectiva para problemas con grandes volúmenes de datos, donde el trabajo puede distribuirse entre múltiples núcleos.
-Para tamaños pequeños de datos, la versión secuencial es preferible debido al overhead de la paralelización.
-Este ejercicio demuestra cómo el uso de OpenMP puede mejorar el rendimiento computacional de manera significativa en tareas intensivas.

#----------------------------------------------------------------------------------------------------

#Ejercicio 2: Cálculo de la media de una matriz con OpenMP
##Descripción del ejercicio
El objetivo es calcular la media de los valores de una matriz bidimensional utilizando OpenMP para paralelizar los cálculos y comparar el rendimiento frente a la solución secuencial.

###Código Paralelo
El cálculo se paralelizó usando OpenMP con directivas que permiten distribuir las iteraciones de los bucles entre varios hilos. La inicialización de la matriz y la acumulación de la suma se realizan en paralelo.

###Código Secuencial
La versión secuencial realiza las mismas operaciones sin paralelización, ejecutando los bucles de manera consecutiva:

##Análisis de rendimiento
###Observaciones
-"Speedup": El rendimiento paralelo mejora significativamente a medida que aumenta el tamaño de la matriz.
-"Overhead": Para tamaños pequeños, el overhead de crear y sincronizar hilos reduce los beneficios del paralelismo.
-"Eficiencia": La paralelización es más eficiente para tamaños grandes, donde el tiempo de cálculo domina el overhead.

##Conclusiones
-La paralelización con OpenMP muestra ventajas claras para matrices grandes debido a la distribución del trabajo entre múltiples núcleos.
-Para matrices pequeñas, la versión secuencial puede ser más rápida debido al bajo overhead.
-Este ejercicio demuestra cómo OpenMP puede aprovechar el hardware subyacente para reducir los tiempos de ejecución en tareas computacionalmente intensivas.

#----------------------------------------------------------------------------------------------------

#Ejercicio 3: Aproximación de Pi con OpenMP y la Regla del Trapecio
##Descripción del ejercicio
El objetivo es aproximar el valor de π utilizando la regla del trapecio. Se implementaron dos versiones del cálculo:
-"Versión secuencial": Se ejecuta un bucle de manera consecutiva para sumar las áreas de los trapecios.
-"Versión paralela": Utiliza OpenMP para distribuir las iteraciones del bucle entre varios hilos.

###Código Paralelo
La versión paralela usa OpenMP con la directiva '#pragma omp parallel for'. La acumulación de áreas se realiza de manera segura utilizando la cláusula 'reduction(+:suma)'.

###Código Secuencial
El mismo cálculo se realiza sin paralelización.

##Análisis de rendimiento
###Observaciones
-"Speedup": La paralelización con OpenMP muestra mejoras significativas, especialmente para un número grande de trapecios.
-"Overhead": Para un número pequeño de trapecios, el tiempo adicional necesario para crear y sincronizar los hilos reduce la eficiencia.
-"Eficiencia": La versión paralela es más efectiva cuando el número de trapecios es alto, aprovechando mejor los núcleos del procesador.

##Conclusiones
- OpenMP es una herramienta eficaz para mejorar el rendimiento en tareas que involucran cálculos repetitivos, como la regla del trapecio.
- La paralelización muestra beneficios claros para números grandes de iteraciones, pero introduce overhead para números pequeños.
- Este ejercicio demuestra cómo el uso eficiente de los recursos de hardware puede reducir significativamente los tiempos de ejecución.

#----------------------------------------------------------------------------------------------------

#Ejercicio 4: Ordenación con Merge Sort paralelo usando OpenMP
##Descripción del ejercicio
El objetivo es implementar y evaluar una versión paralela del algoritmo Merge Sort utilizando OpenMP. Se comparó el rendimiento frente a la versión secuencial, midiendo los tiempos de ejecución y el speedup.

###Código Paralelo
La versión paralela utiliza OpenMP para dividir las tareas entre múltiples hilos, aplicando '#pragma omp parallel sections' en las llamadas recursivas de 'parallelMergeSort'.

###Código Secuencial
La versión secuencial sigue el mismo enfoque, pero sin paralelización.

##Análisis de rendimiento
###Observaciones
-"Speedup": El rendimiento paralelo mejora significativamente para tamaños grandes de vectores, con un speedup promedio de '2.43' en este caso.
-"Overhead": Para tamaños pequeños, el overhead de crear y sincronizar hilos reduce los beneficios del paralelismo.
-"Eficiencia": La paralelización es más efectiva para tamaños grandes, donde las operaciones de fusión y partición dominan el tiempo de ejecución.

##Conclusiones
- OpenMP mejora significativamente el rendimiento en tareas de ordenación para conjuntos de datos grandes.
- El overhead limita los beneficios en vectores pequeños; para esos casos, la versión secuencial puede ser preferible.
- Este ejercicio demuestra cómo aprovechar el hardware subyacente para reducir los tiempos de ejecución en algoritmos recursivos.

#----------------------------------------------------------------------------------------------------

#Ejercicio 5: Resolución de sistemas de ecuaciones con el método de Gauss-Seidel paralelo usando OpenMP
##Descripción del ejercicio
Se implementa el método de Gauss-Seidel para resolver sistemas de ecuaciones lineales de la forma '\(Ax = b\)'. Se comparó una versión paralela usando OpenMP con una versión secuencial para evaluar el impacto de la paralelización en el rendimiento.

###Código Paralelo
La versión paralela distribuye las actualizaciones de las componentes de '\(x\)' y el cálculo del error entre varios hilos utilizando OpenMP.

###Código Secuencial
El cálculo se realiza de manera consecutiva.

##Análisis de rendimiento
###Observaciones
-"Speedup": El rendimiento paralelo mejora significativamente con sistemas más grandes, donde el número de iteraciones es mayor.
-"Overhead": En sistemas pequeños, el overhead de la creación y sincronización de hilos disminuye los beneficios de la paralelización.
-"Eficiencia": La paralelización no afecta el criterio de convergencia, ya que los cálculos están correctamente sincronizados.

##Conclusiones
-OpenMP mejora considerablemente el rendimiento del método de Gauss-Seidel para sistemas grandes, logrando un speedup promedio de '2.16' en este caso.
-Para sistemas pequeños, el tiempo adicional requerido para paralelizar supera los beneficios.
-Este ejercicio demuestra cómo aprovechar múltiples núcleos del procesador puede reducir los tiempos de ejecución de algoritmos iterativos.

#----------------------------------------------------------------------------------------------------

#Ejercicio 6: Juego de la Vida de Conway paralelizado con OpenMP
##Descripción del ejercicio
Se implementa el Juego de la Vida de Conway utilizando OpenMP para paralelizar la evolución de las generaciones. La solución paralela se compara con una versión secuencial para evaluar el impacto del paralelismo en el rendimiento.

###Código Paralelo
La versión paralela utiliza OpenMP para distribuir el cálculo de cada generación entre múltiples hilos.

###Código Secuencial
La misma lógica se aplica sin paralelización.

##Análisis de rendimiento
###Observaciones
-"Speedup": El rendimiento paralelo mejora notablemente para tableros más grandes, con un promedio de speedup de '2.55'.
-"Overhead": Para tableros pequeños, el tiempo adicional para crear y sincronizar hilos reduce los beneficios de la paralelización.
-"Eficiencia": La paralelización se escala bien con tableros grandes, especialmente cuando el número de generaciones es alto.

##Conclusiones
-OpenMP ofrece beneficios significativos en tareas computacionalmente intensivas como el Juego de la Vida, especialmente para tableros grandes.
-El overhead de la paralelización se minimiza a medida que aumenta el tamaño del problema.
-Este ejercicio demuestra cómo OpenMP puede utilizar eficientemente los recursos del hardware para reducir los tiempos de ejecución en simulaciones iterativas.

#----------------------------------------------------------------------------------------------------

#Ejercicio 7: Transformada Rápida de Fourier (FFT) paralelizada con OpenMP
##Descripción del ejercicio
Se implementa la Transformada Rápida de Fourier (FFT) utilizando OpenMP para paralelizar los cálculos. La solución paralela se compara con una versión secuencial para evaluar el impacto de la paralelización en el rendimiento.

###Código Paralelo
La versión paralela utiliza OpenMP para dividir el cálculo de la FFT en múltiples hilos durante el proceso de combinación de resultados.

###Código Secuencial
La versión secuencial aplica la misma lógica, pero sin paralelización.

##Análisis de rendimiento
###Observaciones
-"Speedup": La paralelización con OpenMP mejora notablemente el rendimiento para señales grandes, logrando un speedup promedio de '2.31'.
-"Overhead": Para señales pequeñas '(\(n = 1024\))', el overhead de la paralelización reduce la eficiencia.
-"Eficiencia": La paralelización escala bien a medida que aumenta el tamaño de la señal, aprovechando eficientemente los recursos del hardware.

##Conclusiones
-La Transformada Rápida de Fourier se beneficia significativamente de la paralelización en señales grandes.
-El overhead asociado a la creación y sincronización de hilos limita los beneficios en señales pequeñas.
-Este ejercicio demuestra cómo OpenMP puede mejorar el rendimiento en algoritmos recursivos y computacionalmente intensivos.
