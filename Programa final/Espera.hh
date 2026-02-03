/** @file Espera.hh
    @brief Especificación de la clase Espera
*/

#ifndef ESPERA_HH
#define ESPERA_HH

#ifndef NO_DIAGRAM
#include <iostream>
#include <map>
#include <list>
#endif

#include "Proceso.hh"
#include "Cluster.hh"

/** @class Espera
    @brief Representa el área de espera de los procesos. 

    Dispone de una cantidad de procesos con distinta prioridad.
*/
class Espera {

private:

/** @brief Estructura de las prioridades */
struct Prioridad{
    list<Proceso> lista_proceso;
    int colocados;
    int rechazados;
};

/** @brief Prioridades de la espera ordenadas por identificador */
map<string, Prioridad> m;

public:

    //Constructores

/** @brief Creadora por defecto. 

      Se ejecuta automáticamente al declarar un área de espera.
      \pre <em>cierto</em>
      \post El resultado es un área de espera vacío.
*/  
    Espera();

    //Modificadores

/** @brief Da de alta una prioridad.

      \pre Un identificador de prioridad.
      \post El resultado es una prioridad nueva en el área de espera.
*/
    int alta_prioridad(const string& prioridad);

/** @brief Da de baja una prioridad.

      \pre Un identificador de prioridad.
      \post El resultado es una prioridad menos en el área de espera.
*/
    int baja_prioridad(const string& prioridad);

/** @brief Da de alta un proceso.

      \pre Un proceso y un identificador de prioridad.
      \post El resultado es un proceso nuevo en una prioridad en el área de espera.
*/
    int alta_proceso_espera(const Proceso& p, const string& prioridad);

/** @brief Envia procesos al cluster.

      \pre Un int n > 0 y un cluster.
      \post El resultado es un cluster con los procesos pendientes del área de espera que se hayan podido añadir.
*/
    void enviar_procesos_cluster(int n, Cluster &c);

    //Lectura

/** @brief Lee un área de espera. 

      \pre <em>cierto</em>
      \post Lee el contenido del parámetro implícito.
*/ 
    void leer();

    //Escritura

/** @brief Imprime una prioridad. 

      \pre Un indentificador de una prioridad.
      \post Escribe el contenido del parámetro implícito por el canal estándar de salida.
*/ 
    int imprimir_prioridad(const string& prioridad) const;

/** @brief Imprime un área de espera. 

      \pre <em>cierto</em>
      \post Escribe el contenido del parámetro implícito por el canal estándar de salida.
*/
    void imprimir_area_espera() const;

private:

/** @brief Imprime los procesos de la prioridad. 

      \pre Un iterador que indica la prioridad a la que estamos mirando.
      \post Escribe el contenido por el canal estándar de salida.
*/
    static void imprimir_procesos(map<string, Prioridad>::const_iterator it);
};
#endif
