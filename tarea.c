#include "tdas/extra.h"
#include "tdas/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TIEMPO 10

typedef struct {
  char nombre[50] ;
  int valor ;
  int peso ;
} Item;

typedef struct Escenario {
  int id ;
  char nombre[50] ;
  char descripcion[200] ;
  List * items ;
  int arriba ;
  int abajo ;
  int izquierda ;
  int derecha ;
  int es_final ;
} Escenario;

typedef struct {
  Escenario* escenario_actual ;
  List *inventario ;
  int tiempo ;
} Jugador;

List* escenarios ;

void leer_escenarios() {
  FILE *archivo = fopen("data/graphquest.csv", "r");
  if (archivo == NULL) {
    perror(
        "Error al abrir el archivo");
    return;
  }

  char **campos;
  campos = leer_linea_csv(archivo, ',');

  while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
    printf("ID: %d\n", atoi(campos[0]));
    printf("Nombre: %s\n", campos[1]);
    printf("Descripción: %s\n", campos[2]);

    List* items = split_string(campos[3], ";");

    printf("Items: \n");
    for(char *item = list_first(items); item != NULL; 
          item = list_next(items)){

        List* values = split_string(item, ",");
        char* item_name = list_first(values);
        int item_value = atoi(list_next(values));
        int item_weight = atoi(list_next(values));
        printf("  - %s (%d pts, %d kg)\n", item_name, item_value, item_weight);
        list_clean(values);
        free(values);
    }

    int arriba = atoi(campos[4]);
    int abajo = atoi(campos[5]);
    int izquierda = atoi(campos[6]);
    int derecha = atoi(campos[7]);

    if (arriba != -1) printf("Arriba: %d\n", arriba);
    if (abajo != -1) printf("Abajo: %d\n", abajo);
    if (izquierda != -1) printf("Izquierda: %d\n", izquierda);
    if (derecha != -1) printf("Derecha: %d\n", derecha);

    
    int is_final = atoi(campos[8]);
    if (is_final) printf("Es final\n");

    list_clean(items);
    free(items);
    
  }
  fclose(archivo);

}


int main() {
  int opcion ;
  while (1) { 
    printf("\n=== GraphQuest ===\n1. Cargar Laberinto\n2. Iniciar Partida\n3. Salir\nOpcion: ") ;
    scanf("%d", &opcion) ;
    if (opcion == 1) 
        leer_escenarios() ;
    //else if (opcion == 2)     iniciar_partida() ;
    else if (opcion == 3) break ;
    else printf("Opcion invalida.\n") ;
  }
  return 0 ;
}