# Memory Compaction Tests

Test cases focused on the memory compaction algorithm at processor and cluster levels.

## Files

- **entrada_compactar_memoria.txt** — Input test case (with comments in Spanish).
- **salida_compactar_memoria.txt** — Expected output.
- **entrada_comentada_compactar_memoria.txt** — Annotated input explaining each step.
- **salida_comentada_compactar_memoria.txt** — Annotated output with explanations.

## What is tested

- Fragmented memory state creation through multiple allocations and deallocations.
- `cmp <proc>` / `compactar_memoria_procesador` — Defragment a single processor.
- `cmc` / `compactar_memoria_cluster` — Defragment all processors.
- Verification that processes are contiguous after compaction.
- No data loss or corruption during the operation.

## Key scenarios

The test creates fragmentation in processor `proc0` by:
1. Allocating several processes of different sizes.
2. Removing processes from the middle (creating holes).
3. Reallocating in the freed holes.
4. Calling compaction to reorganize memory.

---

# Pruebas de Compactación de Memoria

Casos de prueba enfocados en el algoritmo de compactación de memoria a nivel de procesador y clúster.

## Archivos

- **entrada_compactar_memoria.txt** — Caso de prueba de entrada.
- **salida_compactar_memoria.txt** — Salida esperada.
- **entrada_comentada_compactar_memoria.txt** — Entrada anotada explicando cada paso.
- **salida_comentada_compactar_memoria.txt** — Salida anotada con explicaciones.

## Qué se prueba

- Creación de estado de memoria fragmentada a través de múltiples asignaciones y liberaciones.
- `cmp <proc>` / `compactar_memoria_procesador` — Desfragmentación de un procesador.
- `cmc` / `compactar_memoria_cluster` — Desfragmentación de todos los procesadores.
- Verificación de que los procesos están contiguos después de compactación.
- Sin pérdida ni corrupción de datos durante la operación.

## Escenarios clave

La prueba crea fragmentación en el procesador `proc0` mediante:
1. Asignación de varios procesos de diferentes tamaños.
2. Eliminación de procesos desde el medio (creando huecos).
3. Reasignación en los huecos liberados.
4. Invocación de compactación para reorganizar la memoria.
