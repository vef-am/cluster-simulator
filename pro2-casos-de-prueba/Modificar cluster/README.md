# Cluster Reconfiguration Tests

Test cases focused on the cluster reconfiguration mechanism, where processors can be replaced by new subtrees.

## Files

- **entrada_modificar_cluster.txt** — Input test case.
- **salida_modificar_cluster.txt** — Expected output.
- **entrada_comentada_modificar_cluster.txt** — Annotated input explaining each step.
- **salida_comentada_modificar_cluster.txt** — Annotated output with explanations.

## What is tested

- `mc <proc>` / `modificar_cluster <proc>` — Replace a leaf processor with a new subtree.
- **Validation checks**:
  - Processor must exist in the cluster.
  - Processor must not have running processes.
  - Processor must not have children (must be a leaf in the tree).
- **Tree structure update**: After replacement, the tree structure changes and new processors are available.
- **Memory map update**: The new processors are added to the cluster's processor map.
- **Error handling**: Proper error codes for invalid operations.

## Key scenarios

The test demonstrates:
1. Reading a new cluster configuration from input for a replacement.
2. Attempting to replace non-existent processors (error).
3. Attempting to replace processors with running processes (error).
4. Attempting to replace processors that are not leaves (error).
5. Successfully replacing a valid leaf processor.
6. Verifying the updated cluster structure and new processor availability.

---

# Pruebas de Reconfiguración del Clúster

Casos de prueba enfocados en el mecanismo de reconfiguración del clúster, donde los procesadores pueden ser reemplazados por nuevos subárboles.

## Archivos

- **entrada_modificar_cluster.txt** — Caso de prueba de entrada.
- **salida_modificar_cluster.txt** — Salida esperada.
- **entrada_comentada_modificar_cluster.txt** — Entrada anotada explicando cada paso.
- **salida_comentada_modificar_cluster.txt** — Salida anotada con explicaciones.

## Qué se prueba

- `mc <proc>` / `modificar_cluster <proc>` — Reemplaza un procesador hoja por un nuevo subárbol.
- **Validaciones**:
  - El procesador debe existir en el clúster.
  - El procesador no debe tener procesos en ejecución.
  - El procesador no debe tener hijos (debe ser una hoja en el árbol).
- **Actualización de estructura de árbol**: Después del reemplazo, la estructura del árbol cambia y nuevos procesadores están disponibles.
- **Actualización de mapa de memoria**: Los nuevos procesadores se añaden al mapa de procesadores del clúster.
- **Manejo de errores**: Códigos de error apropiados para operaciones inválidas.

## Escenarios clave

La prueba demuestra:
1. Lectura de una nueva configuración de clúster desde entrada para reemplazo.
2. Intento de reemplazar procesadores inexistentes (error).
3. Intento de reemplazar procesadores con procesos en ejecución (error).
4. Intento de reemplazar procesadores que no son hojas (error).
5. Reemplazo exitoso de un procesador hoja válido.
6. Verificación de la estructura de clúster actualizada y disponibilidad de nuevos procesadores.
