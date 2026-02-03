# Sample Input/Output

This directory contains sample test cases demonstrating the cluster simulator in action.

## Intermediate sample

- **sample_intermedia.inp** — Basic test case with cluster configuration, process management, and simple time advancement.
- **sample_intermedia.cor** — Expected output showing error handling and state changes.

### Content overview

The intermediate sample tests:
- Cluster and waiting area initialization
- Adding processes to processors
- Error cases (non-existent processor, insufficient memory)
- Process removal
- Time advancement and process termination
- Memory states

## Complete sample

- **sample.inp** — Comprehensive test case covering all major features.
- **sample.cor** — Full expected output.
- **sample-completa.pdf** — Visual documentation of the test case.

### Content overview

The complete sample extensively tests:
- Cluster reconfiguration (tree modifications)
- Priority queue management
- Process sending from waiting area to cluster
- Complex memory allocations
- Multiple error scenarios
- All output commands

## How to use

Run either sample through the compiled program:

```bash
cd "Programa final"
make
./program.exe < ../samples/intermedia/sample_intermedia.inp > output.cor
diff output.cor ../samples/intermedia/sample_intermedia.cor
```

A successful run produces no diff output.

---

# Ejemplos de entrada/salida

Este directorio contiene casos de prueba que demuestran el simulador en acción.

## Ejemplo intermedio

- **sample_intermedia.inp** — Caso básico con configuración de clúster, gestión de procesos y avance de tiempo simple.
- **sample_intermedia.cor** — Salida esperada mostrando manejo de errores y cambios de estado.

### Vista general del contenido

El ejemplo intermedio prueba:
- Inicialización del clúster y área de espera
- Añadir procesos a procesadores
- Casos de error (procesador inexistente, memoria insuficiente)
- Eliminación de procesos
- Avance de tiempo y finalización de procesos
- Estados de memoria

## Ejemplo completo

- **sample.inp** — Caso de prueba exhaustivo que cubre todas las características principales.
- **sample.cor** — Salida esperada completa.
- **sample-completa.pdf** — Documentación visual del caso de prueba.

### Vista general del contenido

El ejemplo completo prueba exhaustivamente:
- Reconfiguración de clúster (modificaciones de árbol)
- Gestión de colas de prioridad
- Envío de procesos desde área de espera al clúster
- Asignaciones complejas de memoria
- Múltiples escenarios de error
- Todos los comandos de salida

## Cómo usar

Ejecuta cualquiera de los ejemplos a través del programa compilado:

```bash
cd "Programa final"
make
./program.exe < ../samples/intermedia/sample_intermedia.inp > output.cor
diff output.cor ../samples/intermedia/sample_intermedia.cor
```

Una ejecución exitosa no produce ninguna salida de diff.
