// Arboles.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <stdlib.h>
#define getch() _getch()


using namespace std;

struct Nodo {
	int dato;
	Nodo* der;
	Nodo* izq;
	Nodo* padre;
};

void menu();
Nodo* CrearNodo(int, Nodo*);
void insertarNodo(Nodo*&, int, Nodo*);
void mostrarArbol(Nodo*, int);
bool buscar(Nodo*, int);
void eliminar(Nodo*, int);
void eliminarNodo(Nodo*);
Nodo* minimo(Nodo*);
void reemplazar(Nodo*, Nodo*);
void destruirNodo(Nodo*);
Nodo* arbol = NULL;

int main() {
	menu();

	//getch();
	return 0;
}

//funcion del menu
void menu() {
	int dato, opcion, contador = 0;
	do {
		cout << "\t.:MENU:." << endl;
		cout << "1. Insertar nuevo nodo" << endl;
		cout << "2. Mostrar arbol completo" << endl;
		cout << "3. Buscar un elemento en el arbol" << endl;
		cout << "4. Eliminar un nodo en el arbol" << endl;
		cout << "5. Salir" << endl;
		cout << "Opcion: ";
		cin >> opcion;

		switch (opcion) {
		case 1:cout << "\nDigite un numero:";
			cin >> dato;
			insertarNodo(arbol, dato, NULL); //ejecuta la funcion de insertar nodo
			cout << "\n";
			system("pause");
			break;

		case 2:cout << "\nDigite un numero:\n\n";
			mostrarArbol(arbol, contador);
			cout << "\n";
			system("pause");
			break;

		case 3:cout << "\nDigite el elemento que buscas: ";
			cin >> dato;
			if (buscar(arbol, dato) == true) {
				cout << "\nElemento " << dato << " a sido encontrado en el arbol";
			}
			else {
				cout << "\nElemento " << dato << " no a sido encontrado en el arbol";
			}
			cout << "\n";
			system("pause");
			break;
		case 4:cout << "\nDigite el numero a eliminar: ";
			cin >> dato;
			eliminar(arbol, dato);
			cout << "\n";
			system("pause");
			break;

		}
		system("cls");
	} while (opcion != 5);
}
//funcion para crear nodo

Nodo* crearNodo(int n, Nodo* padre) {
	Nodo* nuevo_nodo = new Nodo();
	nuevo_nodo->dato = n;
	nuevo_nodo->der = NULL;
	nuevo_nodo->izq = NULL;
	nuevo_nodo->padre = padre;

	return nuevo_nodo;
}

//funcion para insertar elementos en el arbol

void insertarNodo(Nodo*& arbol, int n, Nodo* padre) {
	if (arbol == NULL) {
		Nodo* nuevo_nodo = crearNodo(n, padre);
		arbol = nuevo_nodo;
	}
	else { //esto es si el arbol ya tiene un nodo, se va a la izq
		int valorRaiz = arbol->dato;
		if (n < valorRaiz) {
			insertarNodo(arbol->izq, n, arbol);
		}
		else {//si es mayor que la raiz, se va a la derecha
			insertarNodo(arbol->der, n, arbol);
		}

	}
}

//Funcion para mostrar arbol
void mostrarArbol(Nodo* arbol, int cont) {
	if (arbol == NULL) {
		return;
	}
	else {
		mostrarArbol(arbol->der, cont + 1);
		for (int i = 0;i < cont;i++) {
			cout << "   ";
		}
		cout << arbol->dato << endl;
		mostrarArbol(arbol->izq, cont + 1);

	}

}

//funcion para buscar elementos en el arbol
bool buscar(Nodo* arbol, int n) {
	if (arbol == NULL) {
		return false;
	}
	else if (arbol->dato == n) {
		return true;
	}
	else if (n < arbol->dato) {
		return buscar(arbol->izq, n);
	}
	else {
		return buscar(arbol->der, n);
	}
}

//funcion para encontrar  el nodo que vamos eliminar del arbol

void eliminar(Nodo* arbol, int n) {
	if (arbol == NULL) {
		return;
	}
	else if (n < arbol->dato) {
		eliminar(arbol->izq, n);
	}
	else if (n > arbol->dato) {
		eliminar(arbol->der, n);
	}
	else {
		eliminarNodo(arbol);
	}

}

//Funcion para determinar el nodo mas izquierdo posible
Nodo* minimo(Nodo* arbol) {
	if (arbol == NULL) {
		return NULL;
	}
	if (arbol->izq) {
		return minimo(arbol->izq);
	}
	else {
		return arbol;
	}
}

//funcion para reemplazar dos nodos
void reemplazar(Nodo* arbol, Nodo* nuevoNodo) {
	if (arbol->padre) { //para asignar nuevo hijo

		if (arbol->dato == arbol->padre->izq->dato) {
			arbol->padre->izq = nuevoNodo;
		}
		else if (arbol->dato == arbol->padre->der->dato) {
			arbol->padre->der = nuevoNodo;
		}
	}
	if (nuevoNodo) { //para asignar nuevo padre
		nuevoNodo->padre = arbol->padre;
	}

}

//Funcion destruir nodo
void destruirNodo(Nodo* nodo) {
	nodo->izq = NULL;
	nodo->der = NULL;
	delete nodo;

}

//funcion para eliminar el nodo encontrado
void eliminarNodo(Nodo* nodoEliminar) {
	if (nodoEliminar->izq && nodoEliminar->der) {
		Nodo* menor = minimo(nodoEliminar->der);
		nodoEliminar->dato = menor->dato;
		eliminarNodo(menor);
	}
	else if (nodoEliminar->izq) { //esta a la izquierda
		reemplazar(nodoEliminar, nodoEliminar->izq);
		destruirNodo(nodoEliminar);
	}
	else if (nodoEliminar->der) { //esta a la derecha
		reemplazar(nodoEliminar, nodoEliminar->der);
		destruirNodo(nodoEliminar);
	}
	else { //No tiene hijos
		reemplazar(nodoEliminar, NULL);
		destruirNodo(nodoEliminar);
	}

}