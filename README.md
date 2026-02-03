# PRO2 – Practices and projects (C++)

Repository with exercises and projects from the PRO2 course. It includes the final program, a final exam, generated documentation, and organized test sets.

Spanish version: [README_ES.md](README_ES.md)

## Structure

- [Examen final](Examen%20final) — Exam implementation and test cases.
- [Programa final](Programa%20final) — Final version + Doxygen docs (DOC/ and html/).
- [pro2-casos-de-prueba](pro2-casos-de-prueba) — Test suites organized by topic.
- [docs](docs) — PDF statements and handouts.
- [samples](samples) — Sample inputs/outputs.

## Detailed explanation of the code

This project simulates a computing cluster that executes processes with memory constraints and a waiting area with priorities. The system is organized around four core classes and a command-driven main program.

### Core model

- `Proceso` models a job with an `identificador`, memory requirement, and remaining time. It can decrement its time and report its fields.
- `Procesador` models a CPU with a fixed memory size. It stores running processes in memory positions and keeps explicit free-memory holes to support fast allocation and deallocation.
- `Cluster` models a set of processors arranged in a binary tree. It owns the tree structure and a map of processors by identifier.
- `Espera` models a waiting area with multiple priorities. Each priority holds a list of pending processes and counters of placed and rejected processes.

### Memory management inside a processor

`Procesador` uses three structures to represent memory state:

- `map_posicion`: ordered by memory position, used to iterate processes in address order.
- `map_identificador`: maps process id to its start position for $O(\log n)$ lookup.
- `map_huecos`: maps hole size to a set of starting positions, allowing a *best‑fit* allocation by taking the smallest hole that can fit the process (`lower_bound`).

When a process finishes or is removed, adjacent holes are merged so fragmentation is reduced. The `compactar_memoria` operation shifts processes left to eliminate fragmentation in one pass and rebuilds hole metadata.

### Cluster scheduling policy

To place a process in the cluster, `Cluster::enviar_procesos` traverses the binary tree and evaluates every processor that does not already contain the same process id. The selection heuristic is:

1. **Smallest hole that fits** the process.
2. If tied, **most free memory** in the processor.
3. If tied, **lowest depth** in the tree (closer to the root).

This produces a deterministic choice that favors tight packing while also balancing toward higher‑level processors.

### Cluster reconfiguration

The cluster can be reconfigured by replacing a leaf processor with an entire subtree from a new cluster. The modification fails if:

- the target processor id does not exist,
- the processor still has running processes,
- or the processor is not a leaf (has auxiliary children in the tree).

### Waiting area behavior

`Espera` maintains priorities ordered by their identifier (map order). When sending $n$ processes, it scans priorities in order and tries to place each process into the cluster. If a process does not fit anywhere, it is moved to the end of its priority list and counted as rejected; otherwise it is removed from the list and counted as placed.

### Program flow (main)

The program reads an initial cluster configuration and the initial set of priorities, then executes commands until `fin`. Commands support:

- Cluster configuration and modification.
- Adding/removing processes in a specific processor.
- Moving processes from waiting area to the cluster.
- Advancing time and freeing completed processes.
- Printing processors, the cluster structure, and waiting area contents.
- Memory compaction at processor or cluster level.

See [Programa final/program.cc](Programa%20final/program.cc) for the command loop and [Programa final](Programa%20final) for class implementations.

### Available commands

#### Cluster configuration
- `cc` / `configurar_cluster` — Configure initial cluster from input.
- `mc <proc>` / `modificar_cluster <proc>` — Replace a leaf processor with a new subtree.

#### Priority management  
- `ap <prio>` / `alta_prioridad <prio>` — Create a new priority level.
- `bp <prio>` / `baja_prioridad <prio>` — Delete a priority (must be empty).

#### Process management in waiting area
- `ape <prio> <id> <mem> <time>` / `alta_proceso_espera` — Add process to waiting area.
- `epc <n>` / `enviar_procesos_cluster <n>` — Send up to *n* processes from waiting area to cluster.

#### Process management in processors
- `app <proc> <id> <mem> <time>` / `alta_proceso_procesador` — Add process to specific processor.
- `bpp <proc> <id>` / `baja_proceso_procesador` — Remove process from processor.

#### Time and simulation
- `at <t>` / `avanzar_tiempo <t>` — Advance time by *t* units; processes finish if time runs out.

#### Output commands
- `ipri <prio>` / `imprimir_prioridad <prio>` — Print all processes in a priority queue.
- `iae` / `imprimir_area_espera` — Print all priorities and their processes.
- `ipro <proc>` / `imprimir_procesador <proc>` — Print all processes in a processor.
- `ipc` / `imprimir_procesadores_cluster` — Print all processor IDs.
- `iec` / `imprimir_estructura_cluster` — Print cluster tree structure.

#### Memory management
- `cmp <proc>` / `compactar_memoria_procesador <proc>` — Compact a processor's memory.
- `cmc` / `compactar_memoria_cluster` — Compact all processors' memory.

#### Exit
- `fin` — End the program.

## Build and run

From any folder with a Makefile:

```
cd "Examen final"
make
./program.exe < sample.inp > output.cor
```

To clean binaries:

```
make clean
```

## Documentation

The Doxygen-generated documentation is included in the repository at [Programa final/html](Programa%20final/html). To view it:

1. Open [Programa final/html/index.html](Programa%20final/html/index.html) in your browser, or
2. View it on GitHub by navigating to the html folder.

The documentation includes:
- Class hierarchies and relationships
- Method signatures and detailed descriptions
- File dependencies and module structure
- Data member documentation

To regenerate the documentation locally:

```bash
cd "Programa final"
doxygen Doxyfile
```

This will create updated `html/` and `DOC/` folders.

## Requirements

- g++ with C++11 support
- make
