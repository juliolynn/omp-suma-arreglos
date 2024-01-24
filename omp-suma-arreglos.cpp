// omp-suma-arreglos.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <omp.h>

void imprimirArreglo(float* d, int inicio, int longitud);

int main()
{
	const int N = 1000;
	const int chunkSize = 100;
	float a[N]{}, b[N]{}, c[N]{};
	int i = 0;


	// Inicializar los arreglos
	for (int i = 0; i < N; ++i) {
		a[i] = i;
		b[i] = i * 2;
	}
	
	// For paralelo que divide el trabajo en chunks
	// y asigna cada chunk a un thread disponible
	#pragma omp parallel for \
	shared(a, b, c, chunkSize) private(i) \
	schedule(static, chunkSize)
	for (i = 0; i < N; i++) {
		// Suma de los valores en los arreglos a y b. 
		c[i] = a[i] + b[i];

		if (i % chunkSize == 0) {
			// Comprobando que cada chunk se procesa en distintos threads
			int pTid = omp_get_thread_num();
			std::cout << "Trabajando el indice " << i << " en el thread: " << pTid << std::endl;
		}
	}

	std::cout << std::endl << std::endl;


	// Pedirle los valores al usuario para delimitar los datos a mostrar
	std::cout << "Indique los valores de los arreglos que desea visualizar." << std::endl;

	int inicio;
	std::cout << "inicio: ";
	std::cin >> inicio;

	int longitud;
	std::cout << "longitud: ";
	std::cin >> longitud;

	std::cout << std::endl << std::endl;
	
	// Se imprimen los rangos seleccionados de cada arreglo
	std::cout << "Imprimiendo valores del arreglo a: " << std::endl;
	imprimirArreglo(a, inicio, longitud);

	std::cout << "Imprimiendo valores del arreglo del arreglo b: " << std::endl;
	imprimirArreglo(b, inicio, longitud);

	std::cout << "Imprimiendo valores del arreglo del arreglo c: " << std::endl;
	imprimirArreglo(c, inicio, longitud);
}

void imprimirArreglo(float* d, int inicio, int longitud)
{
	// Imprimir los valores seleccionados del arreglo
	for (int i = inicio; i < inicio + longitud; i++) {
		std::cout << d[i] << " - ";
	}
	std::cout << std::endl << std::endl;
}
