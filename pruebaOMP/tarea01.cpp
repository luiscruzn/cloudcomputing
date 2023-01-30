#include "pch.h"
#include <iostream>
#include <omp.h>
#include <ctime>
#include <cstdlib>

int N;

void imprimeArreglo(int* d);

int main()
{
	// Inicializamos generador de números aleatorios
	srand(time(0));
	// Le pedimos al usuario que capture la longitud del arreglo
	std::cout << "Sumando Arreglos en Paralelo!\n";
	std::cout << "Introduce el número de elementos de los arreglos: ";
	std::cin >> N;

	int chunk = round(N % 10) + 1;
	
	// Dinámicamente reservamos memoria al arreglo, pero hay que recordar borrarlo para evitar un memory leak
	int* a = new int[N];
	int* b = new int[N];
	int* c = new int[N];

	int i;

	// Inicializamos arreglo con números random
	for (i = 0; i < N; i++) {
		a[i] = (rand() % N) + 1;
		b[i] = (rand() % N) + 1;
	}
	int pedazos = chunk;

	#pragma omp parallel for shared(a, b, c, pedazos) private(i) schedule(static, pedazos)
	for (i = 0; i < N; i++)
		c[i] = a[i] + b[i];

	std::cout << "Imprimiendo los valores del arreglo a: " << std::endl;
	imprimeArreglo(a);
	std::cout << "Imprimiendo los valores del arreglo b: " << std::endl;
	imprimeArreglo(b);
	std::cout << "Imprimiendo los valores del arreglo c: " << std::endl;
	imprimeArreglo(c);

	// Borramos los arreglos dinámicos para evitar un memory leak
	delete[] a;
	delete[] b;
	delete[] c;
}

void imprimeArreglo(int* d) {
	for (int x = 0; x < N; x++)
		std::cout << d[x] << " - ";
	std::cout << std::endl;
}