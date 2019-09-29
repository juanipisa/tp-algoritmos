#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

struct pregunta {
	char nombrePregunta[50];
	bool respondida;
	char respuesta[30];
};

struct categoria {
	char nombre[20];
	pregunta arrayPreguntas[6];
};

struct jugador {
	char nombre[20];
	int puntos;
	int turno;
	pregunta pregJugador;
};

void juego(categoria arrayCategoria[]) {

	FILE* archivoCategorias = fopen("categorias.dat", "rb");

	fread(&arrayCategoria[0], sizeof(categoria), 1, archivoCategorias);
	cout << arrayCategoria[0].arrayPreguntas[0].nombrePregunta << endl;

}
/*void push(nodo*& p, nodo* valor) {
	nodo* aux = new nodo();
	strcpy(aux->pregunta,valor->pregunta);
	aux->sgt = p;
	p = aux;
}

string pop(nodo*& p) {

	string v = p->pregunta;
	nodo* aux = p;
	p = p->sgt;

	delete aux;
	return v;
}*/
int main()
{
	categoria arrayCategoria[7] = {};
	strcpy(arrayCategoria[0].nombre, "ciencia");
	strcpy(arrayCategoria[0].arrayPreguntas[0].nombrePregunta, "Cual es el radio de tu ano?");
	arrayCategoria[0].arrayPreguntas[0].respondida = false;
	strcpy(arrayCategoria[0].arrayPreguntas[0].respuesta, "15 cm");

	FILE* archivoCategoria = fopen("categorias.dat", "wb");
	for (int i = 0; i < 2; i++) {
		fwrite(&arrayCategoria[i], sizeof(categoria), 1, archivoCategoria);
	}

	juego(arrayCategoria);

}

