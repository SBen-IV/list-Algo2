#include <stdio.h>
#include <stdlib.h>
#include "testing.h"
#include "lista.h"

#define TAM 50
#define COEFICIENTE_MULTIPLICACION 3

void inicializar_vector(int* numeros, int tope){

	for(int i = 0; i < tope; i++){
		numeros[i] = i*COEFICIENTE_MULTIPLICACION;
	}
}

bool insertar_primero_iterado(lista_t* lista, int* numeros, int tope){

	for(int i = 0; i < tope; i++){
		if(!lista_insertar_primero(lista, &numeros[i])){
			return false;
		}
		if(*(int*)lista_ver_primero(lista) != numeros[i]){
			return false;
		}
		if(lista_ver_primero(lista) != &numeros[i]){
			return false;
		}
	}

	return true;
}

bool insertar_ultimo_iterado(lista_t* lista, int* numeros, int tope){

	for(int i = 0; i < tope; i++){
		if(!lista_insertar_ultimo(lista, &numeros[i])){
			return false;
		}
		if(*(int*)lista_ver_ultimo(lista) != numeros[i]){
			return false;
		}
		if(lista_ver_ultimo(lista) != &numeros[i]){
			return false;
		}
	}

	return true;
}

bool prueba_borrar_primero_iterado(lista_t* lista, int numeros[], int tope){

	for(int i = tope-1; i > 0; i--){
		if(!(lista_borrar_primero(lista) == &numeros[i])){
			return false;
		}
		if(!(lista_ver_primero(lista) == &numeros[i-1])){
			return false;
		}
		if(!(*(int*)lista_ver_primero(lista) == numeros[i-1])){
			return false;
		}
	}

	if(!(lista_borrar_primero(lista) == &numeros[0])){
		return false;
	}
	if(lista_largo(lista) != 0){
		return false;
	}

	return true;
}

bool prueba_borrar_ultimo_iterado(lista_t* lista, int numeros[], int tope){

	for(int i = 0; i < tope-1; i++){
		if(!(lista_borrar_primero(lista) == &numeros[i])){
			return false;
		}
		if(!(lista_ver_primero(lista) == &numeros[i+1])){
			return false;
		}
		if(!(*(int*)lista_ver_primero(lista) == numeros[i+1])){
			return false;
		}
	}

	if(!(lista_borrar_primero(lista) == &numeros[tope-1])){
		return false;
	}
	if(lista_largo(lista) != 0){
		return false;
	}

	return true;
}

bool prueba_insertar_null(lista_t* lista){

	for(int i = 0; i < TAM/2; i++){
		if(!lista_insertar_primero(lista, NULL)){
			return false;
		}
		if(!(lista_ver_primero(lista) == NULL)){
			return false;
		}
		if(!lista_insertar_ultimo(lista, NULL)){
			return false;
		}
		if(!(lista_ver_ultimo(lista) == NULL)){
			return false;
		}
	}

	return true;
}

bool prueba_borrar_null(lista_t* lista){

	for(int i = 0; i < TAM; i++){
		if(!(lista_borrar_primero(lista) == NULL)){
			return false;
		}
	}

	return true;
}

void prueba_insertar_y_borrar_iterado(lista_t* lista){

	int numeros[TAM];
	int tope = TAM/2;

	inicializar_vector(numeros, tope);

	print_test("Se insertó primero iterado (25)", insertar_primero_iterado(lista, numeros, tope));
	print_test("Ver ultimo", lista_ver_ultimo(lista) == &numeros[0]);
	print_test("Se borró iterado", prueba_borrar_primero_iterado(lista, numeros, tope));
	print_test("Se insertó ultimo iterado (25)", insertar_ultimo_iterado(lista, numeros, tope));
	print_test("Ver primero", lista_ver_primero(lista) == &numeros[0]);
	print_test("Se borró iterado", prueba_borrar_ultimo_iterado(lista, numeros, tope));
}

void prueba_insertar_distinto_static(lista_t* lista){

	int num = 1, num2 = 42, num3 = 80;
	double num4 = 3.14;
	char letra = 'B', letra2 = 'k', caracter = '#';
	char* palabra = "World";

	print_test("Se insertó num primero", lista_insertar_primero(lista, &num) && lista_ver_primero(lista) == &num);
	print_test("Se insertó caracter primero", lista_insertar_primero(lista, &caracter) && lista_ver_primero(lista) == &caracter);
	print_test("Se insertó num2 primero", lista_insertar_primero(lista, &num2) && lista_ver_primero(lista) == &num2);
	print_test("Se insertó palabra primero", lista_insertar_primero(lista, palabra) && lista_ver_primero(lista) == palabra);
	print_test("Se insertó num3 ultimo", lista_insertar_ultimo(lista, &num3) && lista_ver_ultimo(lista) == &num3);
	print_test("Se insertó letra ultimo", lista_insertar_ultimo(lista, &letra) && lista_ver_ultimo(lista) == &letra);
	print_test("Se insertó num4 ultimo", lista_insertar_ultimo(lista, &num4) && lista_ver_ultimo(lista) == &num4);
	print_test("Se insertó letra2 ultimo", lista_insertar_ultimo(lista, &letra2) && lista_ver_ultimo(lista) == &letra2);
}

void prueba_insertar_distinto_dynamic(lista_t* lista){

	int* num = malloc(sizeof(int));

	if(!num) return;

	char* letra = malloc(sizeof(char));

	if(!letra){
		free(num);
		return;
	}

	double* num2 = malloc(sizeof(double));

	if(!num2){
		free(num);
		free(letra);
		return;
	}

	(*num) = 60;
	(*letra) = 'p';
	(*num2) = 6.78;

	print_test("Se insertó letra primero", lista_insertar_primero(lista, letra) && lista_ver_primero(lista) == letra);
	print_test("Se insertó num2 ultimo", lista_insertar_ultimo(lista, num2) && lista_ver_ultimo(lista) == num2);
	print_test("Se insertó num primero", lista_insertar_primero(lista, num) && lista_ver_primero(lista) == num);
}

void prueba_insertar_y_borrar_null(lista_t* lista){

	print_test("Se insertó NULL (50)", prueba_insertar_null(lista));
	print_test("Se borró NULL", prueba_borrar_null(lista));
}

void pruebas_crear_y_destruir(){

	lista_t* lista_vacia = lista_crear();
	lista_t* lista_nueva = lista_crear();	//INSERTAR Y BORRAR ITERADO
	lista_t* lista_nueva2 = lista_crear();	//INSERTAR DISTINTOS STATIC
	lista_t* lista_nueva3 = lista_crear();	//INSERTAR DISTINTOS DYNAMIC
	lista_t* lista_nueva4 = lista_crear();	//INSERTAR Y BORRAR NULL
	lista_t* lista_nueva5 = lista_crear();	//PRUEBAS INVALIDAS

	printf("\tPRUEBA CREAR\n");
	print_test("Se creó lista_vacia", lista_vacia != NULL);
	print_test("Se creó lista_nueva", lista_nueva != NULL);
	print_test("Se creó lista_nueva2", lista_nueva2 != NULL);
	print_test("Se creó lista_nueva3", lista_nueva3 != NULL);
	print_test("Se creó lista_nueva4", lista_nueva4 != NULL);
	print_test("Se creó lista_nueva5", lista_nueva5 != NULL);

	printf("\tPRUEBA INSERTAR Y BORRAR\n");
	printf("\tPrueba insertar y borrar iterado.\n");
	prueba_insertar_y_borrar_iterado(lista_nueva);
	printf("\tPrueba insertar distinto static.\n");
	prueba_insertar_distinto_static(lista_nueva2);
	printf("\tPrueba insertar distinto dynamic.\n");
	prueba_insertar_distinto_dynamic(lista_nueva3);
	printf("\tPrueba insertar y borrar NULL\n");
	prueba_insertar_y_borrar_null(lista_nueva4);

	printf("\tPRUEBAS INVALIDAS\n");
	print_test("Prueba ver primero devuelve NULL", lista_ver_primero(lista_nueva5) == NULL);
	print_test("Prueba ver ultimo devuelve NULL", lista_ver_ultimo(lista_nueva5) == NULL);
	print_test("Prueba borrar primero devuelve NULL", lista_borrar_primero(lista_nueva5) == NULL);

	printf("\tPRUEBA ESTA VACIA\n");
	print_test("lista_vacia está vacía", lista_esta_vacia(lista_vacia));
	print_test("lista_nueva está vacía", lista_esta_vacia(lista_nueva));
	print_test("lista_nueva2 NO está vacía", !lista_esta_vacia(lista_nueva2));
	print_test("lista_nueva3 NO está vacía", !lista_esta_vacia(lista_nueva3));
	print_test("lista_nueva4 está vacía", lista_esta_vacia(lista_nueva4));
	print_test("lista_nueva5 está vacía", lista_esta_vacia(lista_nueva5));

	printf("\tPRUEBA DESTRUIR\n");
	lista_destruir(lista_vacia, NULL);
	print_test("Se destruyó lista_vacia", true);
	lista_destruir(lista_nueva, NULL);
	print_test("Se destruyó lista_nueva", true);
	lista_destruir(lista_nueva2, NULL);
	print_test("Se destruyó lista_nueva2", true);
	lista_destruir(lista_nueva3, free);
	print_test("Se destruyó lista_nueva3", true);
	lista_destruir(lista_nueva4, NULL);
	print_test("Se destruyó lista_nueva4", true);
	lista_destruir(lista_nueva5, NULL);
	print_test("Se destruyó lista_nueva5", true);
}

bool prueba_recorrer_y_comparar(lista_t* lista){

	int numeros[TAM];
	int tope = TAM/2;

	inicializar_vector(numeros, tope);

	if(!insertar_primero_iterado(lista, numeros, tope)){
		return false;
	}

	lista_iter_t* iter = lista_iter_crear(lista);
	print_test("Se creó iter_nuevo", iter != NULL);

	for(int i = tope-1; i >= 0; i--){
		if(!(lista_iter_ver_actual(iter) == &numeros[i])){
			return false;
		}
		if(!(*(int*)lista_iter_ver_actual(iter) == numeros[i])){
			return false;
		}
		if(!lista_iter_avanzar(iter)){
			return false;
		}
	}

	lista_iter_destruir(iter);
	print_test("Se destruyó iter_nuevo", true);

	return true;
}

bool prueba_iter_insertar(lista_t* lista){

	int numeros[TAM];
	int tope = TAM/2;

	inicializar_vector(numeros, tope);

	if(!insertar_ultimo_iterado(lista, numeros, tope)){
		return false;
	}

	lista_iter_t* iter = lista_iter_crear(lista);

	print_test("Se creó iter", iter != NULL);

	double num = 63.1;

	print_test("Se insertó primero num", lista_iter_insertar(iter, &num));
	print_test("Ver actual: num", lista_iter_ver_actual(iter) == &num);

	if(!lista_iter_avanzar(iter)){
		return false;
	}

	for(int i = 0; i < tope/2; i++){
		if(!(lista_iter_ver_actual(iter) == &numeros[i])){
			return false;
		}
		if(!(*(int*)lista_iter_ver_actual(iter) == numeros[i])){
			return false;
		}
		if(!lista_iter_avanzar(iter)){
			return false;
		}
	}

	char letra = 'I';

	print_test("Se insertó letra", lista_iter_insertar(iter, &letra));
	print_test("Ver actual: letra", lista_iter_ver_actual(iter) == &letra);

	if(!lista_iter_avanzar(iter)){
		return false;
	}

	for(int i = tope/2; i < tope; i++){
		if(!(lista_iter_ver_actual(iter) == &numeros[i])){
			return false;
		}
		if(!(*(int*)lista_iter_ver_actual(iter) == numeros[i])){
			return false;
		}
		if(!lista_iter_avanzar(iter)){
			return false;
		}
	}

	char* palabra = "carta";

	print_test("Se insertó ultimo palabra", lista_iter_insertar(iter, palabra));
	print_test("Ver actual: palabra", lista_iter_ver_actual(iter) == palabra);

	if(!lista_iter_avanzar(iter)){
		return false;
	}
	
	print_test("Lista iter al final", lista_iter_al_final(iter));

	lista_iter_destruir(iter);
	print_test("Se destruyó iter", true);

	return true;
}

bool prueba_iter_borrar(lista_t* lista){

	int numeros[TAM];
	int tope = 10;

	inicializar_vector(numeros, tope);

	if(!insertar_ultimo_iterado(lista, numeros, tope)){
		return false;
	}

	lista_iter_t* iter = lista_iter_crear(lista);

	print_test("Se creó iter", iter != NULL);

	bool cambio = true;

	for(int i = 0; i < tope; i++){
		if(cambio){
			if(!(lista_iter_borrar(iter) == &numeros[i])){
				return false;
			}
			cambio = false;
		}else{
			if(!(lista_iter_ver_actual(iter) == &numeros[i])){
				return false;
			}
			if(!lista_iter_avanzar(iter)){
				return false;
			}
			cambio = true;
		}
	}

	print_test("Lista iter al final", lista_iter_al_final(iter));

	lista_iter_destruir(iter);
	print_test("Se destruyó iter", true);

	return true;
}

bool prueba_borrar_e_insertar(lista_t* lista){

	int numeros[TAM];
	int tope = TAM/2;

	inicializar_vector(numeros, tope);

	if(!insertar_ultimo_iterado(lista, numeros, tope)){
		return false;
	}

	lista_iter_t* iter = lista_iter_crear(lista);

	print_test("Se creó iter", iter != NULL);

	for(int i = 0; i < tope; i++){
		if(!(lista_iter_borrar(iter) == &numeros[i])){
			return false;
		}
		if(!lista_iter_insertar(iter, NULL)){
			return false;
		}
		if(!(lista_iter_ver_actual(iter) == NULL)){
			return false;
		}
		if(!lista_iter_avanzar(iter)){
			return false;
		}
	}

	print_test("Largo de lista (25)", lista_largo(lista) == tope);
	print_test("Lista iter al final", lista_iter_al_final(iter));

	lista_iter_destruir(iter);
	print_test("Se destruyó iter", true);

	return true;
}

void pruebas_iter_externo(){

	lista_t* lista_vacia = lista_crear();
	lista_t* lista_nueva = lista_crear();
	lista_t* lista_nueva2 = lista_crear();
	lista_t* lista_nueva3 = lista_crear();
	lista_t* lista_nueva4 = lista_crear();

	lista_iter_t* iter = lista_iter_crear(lista_vacia);

	printf("\n\tPRUEBAS ITER EXTERNO\n");

	print_test("Se creó iter", iter != NULL);

	printf("\n\tPRUEBAS INVALIDAS\n");
	print_test("Lista iter ver actual devuelve NULL", lista_iter_ver_actual(iter) == NULL);
	print_test("Lista iter avanzar devuelve false", !lista_iter_avanzar(iter));
	print_test("Lista iter borrar devuelve NULL", lista_iter_borrar(iter) == NULL);

	lista_iter_destruir(iter);
	print_test("Se destruyó iter", true);

	printf("\n\tPRUEBA RECORRER, COMPARAR, BORRAR E INSERTAR\n\n");
	print_test("Prueba avanzar y comparar", prueba_recorrer_y_comparar(lista_nueva));
	printf("\n");
	print_test("Prueba insertar", prueba_iter_insertar(lista_nueva2));
	printf("\n");
	print_test("Prueba borrar", prueba_iter_borrar(lista_nueva3));
	printf("\n");
	print_test("Prueba borrar e insertar", prueba_borrar_e_insertar(lista_nueva4));

	lista_destruir(lista_vacia, NULL);
	lista_destruir(lista_nueva, NULL);
	lista_destruir(lista_nueva2, NULL);
	lista_destruir(lista_nueva3, NULL);
	lista_destruir(lista_nueva4, NULL);
}

bool imprimir_numeros(void* dato, void* extra){

	int* numero = dato;

	printf(" %d ", (*numero));

	if(extra == NULL){
		return true;
	}

	return false;
}

bool prueba_imprimir(){

	lista_t* lista = lista_crear();

	if(!lista) return false;

	int numeros[TAM];
	int tope = TAM/2;

	inicializar_vector(numeros, tope);

	if(!insertar_ultimo_iterado(lista, numeros, tope)){
		return false;
	}

	int num = 1;

	printf("Imprimir todos los numeros:");
	lista_iterar(lista, imprimir_numeros, NULL);
	printf("\nImprimir primer numero:");
	lista_iterar(lista, imprimir_numeros, &num);

	lista_destruir(lista, NULL);

	return true;
}

bool sumar_numeros(void* dato, void* extra){

	int* total = extra;

	(*total) += *(int*)dato;

	return true;
}

bool prueba_sumar(){

	lista_t* lista = lista_crear();

	if(!lista) return false;

	int numeros[TAM];
	int tope = TAM/2;

	inicializar_vector(numeros, tope);

	if(!insertar_ultimo_iterado(lista, numeros, tope)){
		return false;
	}

	int total = 0;

	lista_iterar(lista, sumar_numeros, &total);

	printf("Total: %d.\n", total);

	lista_destruir(lista, NULL);

	return true;
}

void pruebas_iter_interno(){

	printf("\n\tPRUEBA ITER INTERNO\n");
	print_test("\nPrueba imprimir", prueba_imprimir());
	print_test("Prueba sumar", prueba_sumar());
}

void pruebas_lista_alumno(){

	pruebas_crear_y_destruir();
	pruebas_iter_externo();
	pruebas_iter_interno();
}