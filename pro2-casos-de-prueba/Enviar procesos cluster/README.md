# Process Sending Tests

Test cases focused on the process sending mechanism from the waiting area to the cluster with priority queues.

## Files

- **entrada_enviar_procesos.txt** — Input test case.
- **salida_enviar_procesos.txt** — Expected output.
- **entrada_comentada_enviar_procesos.txt** — Annotated input explaining each step.
- **salida_comentada_enviar_procesos.txt** — Annotated output with explanations.

## What is tested

- Adding processes to different priority levels in the waiting area.
- `epc <n>` / `enviar_procesos_cluster <n>` — Send up to *n* processes from waiting area to cluster.
- **Best-fit allocation**: Processes are placed in the processor with the smallest hole that fits.
- **Free memory tiebreaker**: If two processors have the same minimum hole size, the one with more total free memory is preferred.
- **Tree depth tiebreaker**: If free memory is also equal, the processor closer to the root is preferred.
- **Priority order**: Processes are sent from higher-priority queues first (in map order).
- **Rejected process tracking**: Processes that cannot fit are moved to the end of their priority queue and marked as rejected.

## Key scenarios

The test demonstrates:
1. Multiple priorities with different process characteristics.
2. Processes with varying memory requirements (some too large for any processor).
3. Watching how processes migrate through the waiting area based on allocation failures.
4. Validating that placement statistics (colocados/rechazados) are tracked correctly.

---

# Pruebas de Envío de Procesos

Casos de prueba enfocados en el mecanismo de envío de procesos desde el área de espera al clúster con colas de prioridad.

## Archivos

- **entrada_enviar_procesos.txt** — Caso de prueba de entrada.
- **salida_enviar_procesos.txt** — Salida esperada.
- **entrada_comentada_enviar_procesos.txt** — Entrada anotada explicando cada paso.
- **salida_comentada_enviar_procesos.txt** — Salida anotada con explicaciones.

## Qué se prueba

- Añadir procesos a diferentes niveles de prioridad en el área de espera.
- `epc <n>` / `enviar_procesos_cluster <n>` — Envía hasta *n* procesos del área de espera al clúster.
- **Asignación best-fit**: Los procesos se colocan en el procesador con el hueco más pequeño que quepa.
- **Desempate de memoria libre**: Si dos procesadores tienen el mismo tamaño mínimo de hueco, se prefiere el que tiene más memoria libre total.
- **Desempate de profundidad del árbol**: Si la memoria libre también es igual, se prefiere el procesador más cercano a la raíz.
- **Orden de prioridad**: Los procesos se envían de las colas de mayor prioridad primero (orden de mapa).
- **Seguimiento de procesos rechazados**: Los procesos que no caben se mueven al final de su cola de prioridad y se marcan como rechazados.

## Escenarios clave

La prueba demuestra:
1. Múltiples prioridades con características diferentes de procesos.
2. Procesos con requisitos de memoria variados (algunos demasiado grandes para cualquier procesador).
3. Cómo los procesos migran a través del área de espera basándose en fallos de asignación.
4. Validación de que las estadísticas de colocación (colocados/rechazados) se rastrean correctamente.
