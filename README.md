# GraphQuest

## Descripción
GraphQuest es un juego desarrollado en lenguaje C que representa un laberinto mediante un grafo dirigido. Cada nodo del grafo es un escenario con descripción, items coleccionables y conexiones a otros escenarios en las direcciones arriba, abajo, izquierda y derecha. El jugador debe navegar por el laberinto, recoger items, gestionar un inventario y llegar al escenario final antes de que se acabe el tiempo.

## Funcionalidades principales
- Cargar el laberinto desde un archivo CSV con información de escenarios y conexiones.
- Visualizar la descripcion y los items disponibles en cada escenario
- Recoger y descartar items para gestionar el  inventario
- Moverse  entre escenarios en las direcciones arriba, abajo, izquierda y derecha
- Calcular el costo de tiempo de los movimientos segun el peso del inventario
- Condición de victoria al llegar al escenario final antes de agotarse el tiempo.
- Reiniciar la partida en cualquier momento.

## Cómo compilar y ejecutar

### Requisitos previos:
- Tener instalado un compilador de C (como `gcc`)
- El archivo de laberinto `graphquest.csv` debe estar en la carpeta `data/` dentro del directorio del proyecto.
    Descarga aqui: `https://drive.google.com/file/d/1Xu8du5BrdFG7hd1GW63gB4F5AgKRMbGZ/view.csv` .

### Pasos para compilar y ejecutar
1. Descarga el proyecto y descomprimelo en una carpeta en tu computador
2. Abre una terminal y busca la carpeta del proyecto.
3. Compila el codigo con el siguiente comando:

```bash
   gcc tdas/*.c tarea.c -Wno-unused-result -o tarea
```

### Pasos para ejecutar
Ejecutar el programa compilado:

```bash
./tarea
```

## 2. Opciones que funcionan correctamente y posibles problemas

### Opciones del menu principal:
- **1. Cargar Laberinto:**  
  Funciona correctamente. Carga los escenarios desde `data/graphquest.csv`.  
  **Problema posible:**  
  - Archivo no encontrado o mal formateado, el programa no cargara escenarios

- **2. Iniciar Partida:**  
  Funciona correctamente. Inicia el juego con el laberinto cargado.  
  **Posibles problemas:**  
  - Si no se ha cargado el laberinto previamente, puede fallar al no encontrar escenarios.  
  - La entrada de usuario debe ser valida (numeros para opciones y nombres exactos para items).

- **3. Salir:**  
  Funciona correctamente.

  ### Opciones durante la partida:
- Recoger items, descartar items y moverse funcionan correctamente
- Reiniciar la partida funciona correctamente.  
- Entrada invalida: el programa avisa y pide nueva opcion.

---

## 3. Ejemplo de interaccion con el juego desde que cargamos el laberinto, probando todas las opciones hasta salir del juego.

```plaintext
=== GraphQuest ===
1. Cargar Laberinto
2. Iniciar Partida
3. Salir
Opcion: 1
Archivo abierto correctamente
Escenarios cargados correctamente

=== GraphQuest ===
1. Cargar Laberinto
2. Iniciar Partida
3. Salir
Opcion: 2

== Entrada principal ==
Una puerta rechinante abre paso a esta mansion olvidada por los dioses y los conserjes. El aire huele a humedad y a misterios sin resolver.

Items disponibles:
Tiempo restante: 10
Inventario:
Peso total: 0 kg | Puntaje: 0

Opciones de movimiento:
2. Abajo

1. Recoger item
2. Descartar item
3. Mover
4. Reiniciar
5. Salir
Opcion: 3
Direccion (1. Arriba, 2. Abajo, 3. Izquierda, 4. Derecha): 2
Te has movido a Cocina. (-1 tiempo)

== Cocina ==
Restos de una batalla culinaria. Cuchillos por aqui, migajas por alla. Alguien cocinoÔÇª o fue cocinado.

Items disponibles:
- Cuchillo (3 pts, 1 kg)
- Pan (2 pts, 1 kg)
Tiempo restante: 9
Inventario:
Peso total: 0 kg | Puntaje: 0

Opciones de movimiento:
1. Arriba
2. Abajo
4. Derecha

1. Recoger item
2. Descartar item
3. Mover
4. Reiniciar
5. Salir
Opcion: 1
Nombre del item a recoger: Pan
Pan agregado al inventario.

== Cocina ==
Restos de una batalla culinaria. Cuchillos por aqui, migajas por alla. Alguien cocinoÔÇª o fue cocinado.

Items disponibles:
- Cuchillo (3 pts, 1 kg)
Tiempo restante: 8
Inventario:
- Pan (2 pts, 1 kg)
Peso total: 1 kg | Puntaje: 2

Opciones de movimiento:
1. Arriba
2. Abajo
4. Derecha

1. Recoger item
2. Descartar item
3. Mover
4. Reiniciar
5. Salir
Opcion: 3
Direccion (1. Arriba, 2. Abajo, 3. Izquierda, 4. Derecha): 4
Te has movido a Comedor. (-1 tiempo)

== Comedor ==
Una mesa elegante cubierta de polvo. Parece que nadie ha cenado aqui desde la ultima plaga. Al menos dejaron una copa.

Items disponibles:
- Copa dorada (8 pts, 3 kg)
Tiempo restante: 7
Inventario:
- Pan (2 pts, 1 kg)
Peso total: 1 kg | Puntaje: 2

Opciones de movimiento:
1. Arriba
2. Abajo
3. Izquierda
4. Derecha

1. Recoger item
2. Descartar item
3. Mover
4. Reiniciar
5. Salir
Opcion: 2
Nombre del item a descartar: Pan
Pan descartado del inventario.

== Comedor ==
Una mesa elegante cubierta de polvo. Parece que nadie ha cenado aqui desde la ultima plaga. Al menos dejaron una copa.

Items disponibles:
- Copa dorada (8 pts, 3 kg)
Tiempo restante: 6
Inventario:
Peso total: 0 kg | Puntaje: 0

Opciones de movimiento:
1. Arriba
2. Abajo
3. Izquierda
4. Derecha

1. Recoger item
2. Descartar item
3. Mover
4. Reiniciar
5. Salir
Opcion: 4

== Entrada principal ==
Una puerta rechinante abre paso a esta mansion olvidada por los dioses y los conserjes. El aire huele a humedad y a misterios sin resolver.

Items disponibles:
Tiempo restante: 10
Inventario:
Peso total: 0 kg | Puntaje: 0

Opciones de movimiento:
2. Abajo

1. Recoger item
2. Descartar item
3. Mover
4. Reiniciar
5. Salir
Opcion: 5

=== GraphQuest ===
1. Cargar Laberinto
2. Iniciar Partida
3. Salir
Opcion: Opcion invalida.

=== GraphQuest ===
1. Cargar Laberinto
2. Iniciar Partida
3. Salir
Opcion: 3
```

---

## 4. Contribuciones 

El codigo fue hecho unicamente por Fernando Lopez.