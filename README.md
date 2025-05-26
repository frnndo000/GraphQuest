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
