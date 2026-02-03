# PRO2 – Prácticas y proyectos (C++)

Repositorio con ejercicios y proyectos de la asignatura PRO2. Incluye el programa final, un examen final, documentación generada y conjuntos de pruebas organizados por tema.

## Estructura

- [Examen final](Examen%20final) — Implementación y casos de prueba del examen.
- [Programa final](Programa%20final) — Versión final + documentación Doxygen (DOC/ y html/).
- [pro2-casos-de-prueba](pro2-casos-de-prueba) — Juegos de prueba organizados por tema.
- [docs](docs) — PDFs de enunciados y material.
- [samples](samples) — Ejemplos de entrada/salida.

## Explicación detallada del código

Este proyecto simula un clúster de procesadores que ejecuta procesos con restricciones de memoria, además de un área de espera con prioridades. El sistema se organiza en cuatro clases principales y un programa que procesa comandos.

### Modelo central

- `Proceso` modela un trabajo con `identificador`, memoria requerida y tiempo restante. Puede decrementar su tiempo y consultar sus campos.
- `Procesador` modela una CPU con memoria fija. Guarda procesos por posición de memoria y mantiene huecos libres para asignación eficiente.
- `Cluster` modela el conjunto de procesadores organizado en un árbol binario. Mantiene la estructura del árbol y el mapa de procesadores por id.
- `Espera` modela el área de espera con varias prioridades; cada prioridad almacena una lista de procesos y contadores de colocados/rechazados.

### Gestión de memoria en un procesador

`Procesador` usa tres estructuras:

- `map_posicion`: procesos ordenados por posición de memoria.
- `map_identificador`: id del proceso a posición para consultas en $O(\log n)$.
- `map_huecos`: tamaño del hueco → conjunto de posiciones, lo que permite *best‑fit* usando `lower_bound`.

Al eliminar un proceso se fusionan huecos adyacentes para reducir fragmentación. La operación `compactar_memoria` desplaza procesos hacia el inicio y reconstruye los huecos.

### Política de planificación en el clúster

Para colocar un proceso, `Cluster::enviar_procesos` recorre el árbol y evalúa cada procesador que no tenga ya ese id. La heurística es:

1. **Hueco mínimo** que permita el proceso.
2. En empate, **mayor memoria libre** total.
3. En empate, **menor profundidad** en el árbol (más cerca de la raíz).

Esto prioriza un empaquetado ajustado y luego procesa con menor profundidad.

### Reconfiguración del clúster

Se puede reemplazar un procesador hoja por un subárbol de otro clúster. La modificación falla si:

- el procesador no existe,
- tiene procesos ejecutándose,
- o no es hoja (tiene hijos auxiliares en el árbol).

### Comportamiento del área de espera

`Espera` mantiene las prioridades ordenadas (por clave del mapa). Al enviar $n$ procesos, recorre prioridades en orden y trata de colocar procesos en el clúster. Si un proceso no cabe, se mueve al final de su lista y se cuenta como rechazado; si se coloca, se elimina de la lista y se cuenta como colocado.

### Flujo del programa

El programa lee una configuración inicial de clúster y prioridades, y luego ejecuta comandos hasta `fin`. Hay comandos para:

- Configurar/modificar el clúster.
- Alta/baja de procesos en un procesador.
- Enviar procesos desde espera al clúster.
- Avanzar el tiempo y liberar procesos terminados.
- Imprimir procesadores, estructura del clúster y área de espera.
- Compactar memoria a nivel de procesador o clúster.

Ver [Programa final/program.cc](Programa%20final/program.cc) para el bucle de comandos y [Programa final](Programa%20final) para las implementaciones.

### Comandos disponibles

#### Configuración del clúster
- `cc` / `configurar_cluster` — Configura el clúster inicial desde entrada.
- `mc <proc>` / `modificar_cluster <proc>` — Reemplaza un procesador hoja por un subárbol.

#### Gestión de prioridades
- `ap <prio>` / `alta_prioridad <prio>` — Crea una nueva prioridad.
- `bp <prio>` / `baja_prioridad <prio>` — Elimina una prioridad (debe estar vacía).

#### Gestión de procesos en área de espera
- `ape <prio> <id> <mem> <time>` / `alta_proceso_espera` — Añade proceso a espera.
- `epc <n>` / `enviar_procesos_cluster <n>` — Envía hasta *n* procesos a clúster.

#### Gestión de procesos en procesadores
- `app <proc> <id> <mem> <time>` / `alta_proceso_procesador` — Añade proceso a procesador.
- `bpp <proc> <id>` / `baja_proceso_procesador` — Elimina proceso de procesador.

#### Tiempo y simulación
- `at <t>` / `avanzar_tiempo <t>` — Avanza tiempo *t* unidades; procesos finalizan si se agota.

#### Comandos de salida
- `ipri <prio>` / `imprimir_prioridad <prio>` — Imprime procesos de una prioridad.
- `iae` / `imprimir_area_espera` — Imprime todas las prioridades y procesos.
- `ipro <proc>` / `imprimir_procesador <proc>` — Imprime procesos de un procesador.
- `ipc` / `imprimir_procesadores_cluster` — Imprime IDs de procesadores.
- `iec` / `imprimir_estructura_cluster` — Imprime estructura del árbol del clúster.

#### Gestión de memoria
- `cmp <proc>` / `compactar_memoria_procesador <proc>` — Compacta memoria de procesador.
- `cmc` / `compactar_memoria_cluster` — Compacta memoria de todos los procesadores.

#### Salida
- `fin` — Finaliza el programa.

## Compilación y ejecución

Desde cualquiera de las carpetas con Makefile:

```
cd "Examen final"
make
./program.exe < sample.inp > output.cor
```

Para limpiar binarios:

```
make clean
```

## Documentación

Para ver la documentación del código:

1. Genérala localmente:
   ```bash
   cd "Programa final"
   doxygen Doxyfile
   ```
2. Abre `DOC/html/index.html` en tu navegador.

La documentación incluye:
- Jerarquías de clases y relaciones
- Firmas de métodos y descripciones detalladas
- Dependencias de archivos y estructura de módulos
- Documentación de miembros de datos

## Requisitos

- g++ con soporte de C++11
- make
