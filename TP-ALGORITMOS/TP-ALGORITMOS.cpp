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

jugador validarPuntos(jugador arrayJugador[]) {
	jugador ganador;
	ganador = arrayJugador[0]; //Le asignamos el primer elemento del array

	for (int i = 0; i < 5; i++) {
		if (arrayJugador[i].puntos > ganador.puntos) {
			ganador.puntos = arrayJugador[i].puntos;
			strcpy(ganador.nombre, arrayJugador[i].nombre);
			
		}
	}
	
	return ganador;
}
int validarTurnos(jugador arrayJugador[]) {
	int turnosRestantes = 0;	
	//Para saber si todos los jugadores completaron sus turnos
		for (int h = 0; h < 5; h++) {
			if (arrayJugador[h].turnosRestantes == 0) {
				turnosRestantes++;
			}
		}
		return turnosRestantes;
}

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

	//Esto que vendria a ser? i no lo usas para el jugador? Aparte mas abajo, en la linea 94 haces lo mismo.
	arrayCategoria[categoriaRandom].arrayPreguntas[i].respondida = true;

	if (strcmp(arrayCategoria[categoriaRandom].arrayPreguntas[preg].respuestaCorrecta, arrayTurno[i].respuestaUsuario) == 0) {
		cout << "Su respuesta es correcta!" << endl;
		cout << arrayJugador[i].nombre << " suma 1 punto!" << endl;
		arrayJugador[i].puntos++;
	}
	else {
		cout << "Respuesta incorrecta" << endl;
		cout << arrayJugador[i].nombre << "no suma ningun punto." << endl;
	}
	preg++;
	arrayJugador[i].turnosRestantes--;
	arrayCategoria[categoriaRandom].arrayPreguntas[preg].respondida = true;
	cout << "Turnos restantes: " << arrayJugador[i].turnosRestantes << endl;
	cout << "TABLA DE PUNTOS "<<endl;
	for(int j = 0; j<5; j++){
		cout << arrayJugador[j].nombre<<": "<< arrayJugador[j].puntos << endl;
	}
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
		
		int empateDeTurnos = validarTurnos(arrayJugador);
		
		//if (empateDeTurnos == 5 &&) { empateJuego(arrayJugador, i, arrayCategoria, preg); }
		//Condicion cuando un jugador se queda sin turnos
		if (arrayJugador[i].turnosRestantes == 0) { i++; }
		juego(arrayCategoria, arrayTurno, arrayJugador, i, preg);
		//Una vez que haya jugado el ultimo jugador, se resetea para que vuelva a empezar
		if (i == 4) { i = -1; }
	}
}
  
