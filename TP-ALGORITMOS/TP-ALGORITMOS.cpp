#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <chrono>

using namespace std;

struct pregunta {
	char nombrePregunta[50];
	bool respondida;
	char respuesta[30];
	pregunta * sgt;
};

struct categoria {
	char nombre[20];
	pregunta arrayPreguntas[6];
};

struct nodoJugadores {
	char nombre[20];
	int puntos;
	int turno;
};


void juego(categoria arrayCategoria[]) {

	int categoriaRandom = rand() % 7;
	int i = 0;
	char respuestaJugadorActual[30];
	while (arrayCategoria[categoriaRandom].arrayPreguntas[i].respondida == true) {
		i++;
	}

	cout << "Cargando categoria.";
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	cout << " . ";
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	cout << ". ";
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	cout << "Categoria: " << arrayCategoria[categoriaRandom].nombre<<endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	cout << arrayCategoria[categoriaRandom].arrayPreguntas[i].nombrePregunta << endl;
	cout << "Respuesta: "; cin >> respuestaJugadorActual;

	if (respuestaJugadorActual == arrayCategoria[categoriaRandom].arrayPreguntas[i].respuesta) {
		cout << "Su respuesta es correcta!" << endl;
	}

	arrayCategoria[categoriaRandom].arrayPreguntas[i].respondida = true;


}
// Funcion donde se van a leer los Arhivos una vez que se inicie el programa
void cargarJuego(categoria arrayCategoria[]) {

	FILE* archivoCategorias = fopen("categorias.dat", "rb");
	//FILE* archivoJugadores = fopen("jugadores.dat", "rb");

	fread(&arrayCategoria[0], sizeof(categoria), 1, archivoCategorias);
	
	juego(arrayCategoria);
}
// Funcion que se llama por primera vez para crear el juego
void crearJuego() {
	srand(time(0));
	categoria arrayCategoria[7] = {};

	strcpy(arrayCategoria[0].nombre, "Ciencia");
	strcpy(arrayCategoria[0].arrayPreguntas[0].nombrePregunta, "Cual es el radio de tu ano?");
	arrayCategoria[0].arrayPreguntas[0].respondida = false;
	strcpy(arrayCategoria[0].arrayPreguntas[0].respuesta, "15");

	strcpy(arrayCategoria[1].nombre, "Deportes");
	strcpy(arrayCategoria[1].arrayPreguntas[0].nombrePregunta, "Cual es el radio de tu ano?");
	arrayCategoria[0].arrayPreguntas[0].respondida = false;
	strcpy(arrayCategoria[0].arrayPreguntas[0].respuesta, "15");

	strcpy(arrayCategoria[2].nombre, "Arte");
	strcpy(arrayCategoria[2].arrayPreguntas[0].nombrePregunta, "Cual es el radio de tu ano?");
	arrayCategoria[0].arrayPreguntas[0].respondida = false;
	strcpy(arrayCategoria[0].arrayPreguntas[0].respuesta, "15");

	strcpy(arrayCategoria[3].nombre, "Historia");
	strcpy(arrayCategoria[3].arrayPreguntas[0].nombrePregunta, "Cual es el radio de tu ano?");
	arrayCategoria[0].arrayPreguntas[0].respondida = false;
	strcpy(arrayCategoria[0].arrayPreguntas[0].respuesta, "15");

	strcpy(arrayCategoria[4].nombre, "Entretenimiento");
	strcpy(arrayCategoria[4].arrayPreguntas[0].nombrePregunta, "Cual es el radio de tu ano?");
	arrayCategoria[0].arrayPreguntas[0].respondida = false;
	strcpy(arrayCategoria[0].arrayPreguntas[0].respuesta, "15");

	strcpy(arrayCategoria[5].nombre, "Geografia");
	strcpy(arrayCategoria[5].arrayPreguntas[0].nombrePregunta, "Cual es el radio de tu ano?");
	arrayCategoria[0].arrayPreguntas[0].respondida = false;
	strcpy(arrayCategoria[0].arrayPreguntas[0].respuesta, "15");

	strcpy(arrayCategoria[6].nombre, "Zaraza");
	strcpy(arrayCategoria[6].arrayPreguntas[0].nombrePregunta, "Cual es el radio de tu ano?");
	arrayCategoria[0].arrayPreguntas[0].respondida = false;
	strcpy(arrayCategoria[0].arrayPreguntas[0].respuesta, "15");

	FILE* archivoCategoria = fopen("categorias.dat", "wb");

	for (int i = 0; i < 2; i++) {
		fwrite(&arrayCategoria[i], sizeof(categoria), 1, archivoCategoria);
	}
	cargarJuego(arrayCategoria);
}

int main()
{
	crearJuego();
}

