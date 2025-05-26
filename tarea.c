#include "tdas/extra.h"
#include "tdas/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_TIEMPO 10

// ======== ESTRUCTURAS ========

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

// ======== FUNCIONES ========

Escenario* buscar_escenario_por_id(int id) {
  Escenario* e = list_first(escenarios) ;
  for (e ; e != NULL ; e = list_next(escenarios)) {
    if (e->id == id) return e ;
  }
  return NULL ;
}

// Carga los escenarios desde un archivo CSV y construye el grafo
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

// Muestra el estado actual del jugador
void mostrar_estado(Jugador *jugador) {
  Escenario *e = jugador->escenario_actual ;
  printf("\n== %s ==\n%s\n", e->nombre, e->descripcion) ;
  printf("\nItems disponibles:\n") ;

  Item* item = list_first(e->items) ;
  for (item ; item != NULL; item = list_next(e->items))
    printf("- %s (%d pts, %d kg)\n", item->nombre, item->valor, item->peso) ;

  printf("Tiempo restante: %d\n", jugador->tiempo) ;
  printf("Inventario:\n") ;

  int peso = 0 ; 
  int puntaje = 0 ;
  
  for (Item *item = list_first(jugador->inventario); item != NULL; item = list_next(jugador->inventario)) {
    printf("- %s (%d pts, %d kg)\n", item->nombre, item->valor, item->peso) ;
    peso += item->peso ;
    puntaje += item->valor ;
  }
  printf("Peso total: %d kg | Puntaje: %d\n", peso, puntaje) ;

  printf("\nOpciones de movimiento:\n") ;
  if (e->arriba != -1) 
    printf("1. Arriba\n") ;
  if (e->abajo != -1) 
    printf("2. Abajo\n") ;
  if (e->izquierda != -1) 
    printf("3. Izquierda\n") ;
  if (e->derecha != -1) 
    printf("4. Derecha\n") ;
}

// Permite recoger un ítem del escenario actual
void recoger_items(Jugador *jugador) {
  char nombre[50] ;
  printf("Nombre del item a recoger: ") ;
  getchar() ; 
  fgets(nombre, sizeof(nombre), stdin) ;
  nombre[strcspn(nombre, "\n")] = '\0' ;

  List* items = jugador->escenario_actual->items ;
  Item *item = list_first(items) ;
  for (item ; item != NULL ; item = list_next(items)) {
    if (strcmp(item->nombre, nombre) == 0) {
      list_pushBack(jugador->inventario, item) ;
      list_popCurrent(items) ;
      jugador->tiempo-- ;
      printf("%s agregado al inventario.\n", nombre) ;
      return ;
    }
  }
  printf("Item no encontrado.\n") ;
}

// Permite descartar un ítem del inventario
void descartar_items(Jugador *jugador) {
  char nombre[50] ;
  printf("Nombre del item a descartar: ") ;
  getchar() ;
  fgets(nombre, sizeof(nombre), stdin) ;
  nombre[strcspn(nombre, "\n")] = '\0' ;

  Item *item = list_first(jugador->inventario) ;
  for (item ; item != NULL; item = list_next(jugador->inventario)) {
    if (strcmp(item->nombre, nombre) == 0) {
      free(list_popCurrent(jugador->inventario)) ;
      jugador->tiempo-- ;
      printf("%s descartado del inventario.\n", nombre) ;
      return ;
    }
  }
  printf("Item no encontrado.\n") ;
}

// Calcula el tiempo que cuesta moverse, en función del peso del inventario 
int calcular_tiempo_movimiento(Jugador *jugador) {
  int peso_total = 0 ;
  Item *item = list_first(jugador->inventario) ;
  for (item ; item != NULL ; item = list_next(jugador->inventario)) {
    peso_total += item->peso ;
  }
    
  return (int)ceil((peso_total + 1) / 10.0) ;
}

// Mueve al jugador en una dirección válida
void mover(Jugador *jugador, int direccion) {
  Escenario* e = jugador->escenario_actual ;
  int sig_id = -1 ;
  if (direccion == 1) sig_id = e->arriba ;
  else if (direccion == 2) sig_id = e->abajo ;
  else if (direccion == 3) sig_id = e->izquierda ;
  else if (direccion == 4) sig_id = e->derecha ;

  if (sig_id == -1) {
    printf("Movimiento invalido.\n");
    return;
  }
  int costo = calcular_tiempo_movimiento(jugador) ;
  jugador->tiempo -= costo ;
  jugador->escenario_actual = buscar_escenario_por_id(sig_id) ;
  printf("Te has movido a %s. (-%d tiempo)\n", jugador->escenario_actual->nombre, costo) ;
}

// Funcion principal de la aplicacion
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
      mostrar_estado(&jugador) ; break ;
    }

    mostrar_estado(&jugador) ;

    printf("\n1. Recoger item\n2. Descartar item\n3. Mover\n4. Reiniciar\n5. Salir\nOpcion: ") ;
    int opcion ;
    scanf("%d", &opcion) ;

    if (opcion == 1) recoger_items(&jugador) ;
    else if (opcion == 2) descartar_items(&jugador) ;
    else if (opcion == 3) {
      printf("Direccion (1. Arriba, 2. Abajo, 3. Izquierda, 4. Derecha): ");
      int direccion;
      scanf("%d", &direccion) ;
      mover(&jugador, direccion) ;
    } else if (opcion == 4) {
      list_clean(jugador.inventario) ;
      free(jugador.inventario) ;
      iniciar_partida() ;
      return ;
    } else if (opcion == 5) break ;
    else printf("Opción invalida.\n");
  }
}

// Menú principal de la aplicación
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