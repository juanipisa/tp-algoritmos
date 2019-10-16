#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <chrono>
#include <list>

using namespace std;

struct pregunta {
	char nombrePregunta[50];
	char respuestaCorrecta[30];
	bool respondida;
};

struct categoria {
	char nombre[20];
	bool habilitada;
	pregunta arrayPreguntas[6];
};

struct turno {
	int numero;
	char nombreJugador[20];
	char nombrePregunta[50];
	char respuestaUsuario[30];
};

struct jugador {
	char nombre[20];
	int puntos;
	int turnosRestantes;
};

int validarPregunta(categoria arrayCategoria[], int categoriaRandom, int preg) {
	if (arrayCategoria[categoriaRandom].arrayPreguntas[preg].respondida == true) {
		preg++;
	}
	return preg;
}

int validarCategoria(categoria arrayCategoria[], int categoriaRandom) {
	if (arrayCategoria[categoriaRandom].habilitada == false) {
		categoriaRandom = rand() % 7;
	}
	return categoriaRandom;
}

int validarJugador(jugador arrayJugador[], int i) {
	if (arrayJugador[i].turnosRestantes == 0) {
		i++;
	}
	return i;

}

void juego(categoria arrayCategoria[], turno arrayTurno[], jugador arrayJugador[], int i, int &preg) {

	srand(time(0));
	int categoriaRandom = rand() % 7;

	preg = validarPregunta(arrayCategoria, categoriaRandom, preg);
	i = validarJugador(arrayJugador, i);
	categoriaRandom = validarCategoria(arrayCategoria, categoriaRandom);

	cout << preg << endl;
	strcpy(arrayTurno[i].nombreJugador, arrayJugador[i].nombre);
	strcpy(arrayTurno[i].nombrePregunta, arrayCategoria[categoriaRandom].arrayPreguntas[preg].nombrePregunta);
	strcpy(arrayTurno[i].respuestaUsuario, " ");

	cout << arrayTurno[i].nombreJugador << " es tu turno!" << endl;
	this_thread::sleep_for(chrono::milliseconds(1000));

	cout << "Categoria: " << arrayCategoria[categoriaRandom].nombre<<endl;
	cout << "Pregunta: " << arrayCategoria[categoriaRandom].arrayPreguntas[preg].nombrePregunta << endl;
	cout << "Tu respuesta: "<< arrayCategoria[categoriaRandom].arrayPreguntas[preg].respuestaCorrecta<<endl;  
	cin >> arrayTurno[i].respuestaUsuario;

	arrayCategoria[categoriaRandom].arrayPreguntas[i].respondida = true;

	if (strcmp(arrayCategoria[categoriaRandom].arrayPreguntas[preg].respuestaCorrecta, arrayTurno[i].respuestaUsuario) == 0) {
		cout << "Su respuesta es correcta!" << endl;
		arrayJugador[i].puntos++;
	}
	else {
		cout << "Respuesta incorrecta" << endl;
	}

	preg++;
	arrayJugador[i].turnosRestantes--;
	arrayCategoria[categoriaRandom].arrayPreguntas[preg].respondida = true;
	cout << "Turnos restantes: " << arrayJugador[i].turnosRestantes << endl;
	cout << "Puntos: " << arrayJugador[i].puntos << "\n" << endl;
	i++;

}

int main()
{
	FILE* archivoCategorias = fopen("categorias.dat", "rb");
	FILE* archivoJugadores = fopen("jugadores.dat", "rb");
	FILE* archivoTurnos = fopen("turnos.dat", "rb");

	categoria arrayCategoria[7] = {};
	// EL ARRAY DE TURNO DESPUES LO CAMBIAMSO POR UNA PILOVICH
	jugador arrayJugador[5] = {	/*{"jugador1", 0, 5},
								{"jugador2", 0, 5},
								{"jugador3", 0, 5},
								{"jugador4", 0, 5},
								{"jugador5", 0, 5}*/};

	turno arrayTurno[42] = { /*{0, "pepe", "pepito", "pepardo"}*/ };
	
	for(int i=0;i<7;i++){
		fread(&arrayCategoria[i], sizeof(categoria), 1, archivoCategorias);
	}
	fclose(archivoCategorias);

	for(int i=0;i<5;i++){
		fread(&arrayJugador[i], sizeof(jugador), 1, archivoJugadores);
		//cout << arrayJugador[i].nombre << " " << arrayJugador[i].puntos << " " << arrayJugador[i].turnosRestantes << endl;
	}
	fclose(archivoJugadores);

	int j = 0;
	while (!feof(archivoTurnos)) {
		fread(&arrayTurno[j], sizeof(turno), 1, archivoTurnos);
		j++;
	}
	fclose(archivoTurnos);
	
	//cout << arrayTurno[0].numero << " " << arrayTurno[0].nombreJugador << " " << arrayTurno[0].nombrePregunta << " " <<arrayTurno[0].respuestaUsuario;
	
	int preg = 0;
	for(int i=0;i<5;i++){
	juego(arrayCategoria, arrayTurno, arrayJugador, i, preg);
	}
}
  
