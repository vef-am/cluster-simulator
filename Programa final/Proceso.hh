/** @file Proceso.hh
    @brief Especificación de la clase Proceso
*/

#ifndef PROCESO_HH
#define PROCESO_HH

#ifndef NO_DIAGRAM
#include <iostream>
#endif


/** @class Proceso
    @brief Representa un proceso. 

    Dispone de un identificador, la cantidad de memoria estimada para ejecutarse y el tiempo de ejecución.
*/
class Proceso {

private:

/** @brief Identificador del proceso */
int identificador;

/** @brief Memoria que ocupa el proceso */
int memoria;

/** @brief Tiempo que dura el proceso */
int tiempo;

public:

    //Constructores

/** @brief Creadora por defecto. 

      Se ejecuta automáticamente al declarar un procesador.
      \pre <em>cierto</em>
      \post El resultado es un proceso vacío.
*/  
    Proceso();

    //Modificadores
    
/** @brief Avanza el tiempo en un proceso. 

      \pre Un entero t > 0
      \post El resultado es un proceso con el tiempo avanzado.
*/
    int avanzar_tiempo(int t); //retorna el tiempo restante, si es <= 0, el proceso debe eliminarse del procesador

    //Consultores

/** @brief Consulta el espacio de memoria que ocupa. 

      \pre <em>cierto</em>
      \post Dice la memoria que ocupa.
*/
    int consultar_memoria() const;

/** @brief Consulta el tiempo del proceso. 

      \pre <em>cierto</em>
      \post Dice el tiempo restante del proceso.
*/
    int consultar_tiempo() const;

/** @brief Consulta el identificador del proceso. 

      \pre <em>cierto</em>
      \post Indica el identificador del proceso.
*/
    int consultar_identificador() const;

    //Leer

/** @brief Lee un proceso. 

      \pre <em>cierto</em>
      \post Lee el contenido del parámetro implícito.
*/ 
    void leer();

    //Escritura

/** @brief Escribe un proceso. 

      \pre <em>cierto</em>
      \post Escribe el contenido del parámetro implícito por el canal estándar de salida.
*/
    void escribir() const;
};
#endif
