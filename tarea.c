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

Escenario* buscar_escenario_por_id(int id) {
  Escenario* e = list_first(escenarios) ;
  for (e ; e != NULL ; e = list_next(escenarios)) {
    if (e->id == id) return e ;
  }
  return NULL ;
}

void leer_escenarios() {
  escenarios = list_create() ;
  FILE *archivo = fopen("data/graphquest.csv", "r");
  if (archivo == NULL) {
    perror(
        "Error al abrir el archivo");
    return;
  }

  printf("Archivo abierto correctamente\n") ;

  char **campos ;
  while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
    Escenario* e = malloc(sizeof(Escenario)) ;
    e->id = atoi(campos[0]) ;
    strcpy(e->nombre, campos[1]) ;
    strcpy(e->descripcion, campos[2]) ;
    e->items = list_create() ;

    List* items_raw = split_string(campos[3], ";") ;
    char *item_str = list_first(items_raw) ;
    for (item_str ; item_str != NULL ; item_str = list_next(items_raw)) {
      List* item_data = split_string(item_str, ",") ;
      Item* item = malloc(sizeof(Item)) ;

      strcpy(item->nombre, list_first(item_data)) ;
      item->valor = atoi(list_next(item_data)) ;
      item->peso = atoi(list_next(item_data)) ;

      list_pushBack(e->items, item) ;
      list_clean(item_data) ;
      free(item_data) ;
    }
    list_clean(items_raw) ;
    free(items_raw) ;

    e->arriba = atoi(campos[4]) ;
    e->abajo = atoi(campos[5]) ;
    e->izquierda = atoi(campos[6]) ;
    e->derecha = atoi(campos[7]) ;
    e->es_final = strcmp(campos[8], "Si") == 0 ;

    list_pushBack(escenarios, e) ;
    free(campos) ;
  }
  fclose(archivo);
  printf("Escenarios cargados correctamente\n") ;

}

void iniciar_partida() {
  Jugador jugador ;
  jugador.tiempo = MAX_TIEMPO ;
  jugador.inventario = list_create() ;
  jugador.escenario_actual = buscar_escenario_por_id(1) ;
  
  while (1) {
    if (jugador.tiempo <= 0) {
      printf("\nSe acabo el tiempo. Has perdido.\n") ; break ;
    }
    if (jugador.escenario_actual->es_final) {
      printf("\nLlegaste al escenario final\n") ;
      //mostrar_estado(&jugador) ; break;
    }

    printf("\n1. Recoger item\n2. Descartar item\n3. Mover\n4. Reiniciar\n5. Salir\nOpcion: ") ;
    int opcion ;
    scanf("%d", &opcion) ;
    printf("%d", opcion) ;
    break ;
  }
}

int main() {
  char input[10];
  int opcion;

  while (1) {
    printf("\n=== GraphQuest ===\n1. Cargar Laberinto\n2. Iniciar Partida\n3. Salir\nOpcion: ") ;
    if (fgets(input, sizeof(input), stdin) == NULL) {
      printf("Error al leer entrada.\n") ;
      continue;
    }

    opcion = atoi(input) ;

    if (opcion == 1) {
      leer_escenarios() ;
    } else if (opcion == 2) {
      iniciar_partida() ;
    } else if (opcion == 3) {
      break ;
    } else {
      printf("Opcion invalida.\n") ;
    }
  }
  return 0 ;

}