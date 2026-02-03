/** @file Procesador.hh
    @brief Especificación de la clase Procesador
*/

#ifndef PROCESADOR_HH
#define PROCESADOR_HH

#ifndef NO_DIAGRAM
#include <iostream>
#include <map>
#include <set>
#endif
using namespace std;

#include "Proceso.hh"

/** @class Procesador
    @brief Representa un procesador. 

    Dispone de una memoria donde guarda y ejecuta los procesos. La memoria tiene una cantidad de posiciones iniciadas en 0.
*/
class Procesador {

private:

/** @brief Identificadores de procesos ordenadas crecientemente asociadas a su posicón en la memoria */
map<int, int> map_identificador;    //int = identificador, int = posición del proceso

/** @brief Posición de los procesos en la memoria del procesador ordenados crecientemente */
map<int, Proceso> map_posicion;     //int = Posición del proceso

/** @brief Tamaños de huecos en la memoria ordenadas crecientemente y sus posiciones asociadas */
map<int, set<int>> map_huecos;      //int = tamaño del hueco, set<int> = posiciones de huecos con ese tamaño (de menor a mayor)  //lower_bound(int) = busca <= a ese int

/** @brief Memoria máxima del procesador */
int memoria_max;

/** @brief Memoria libre del procesador */
int memoria_libre;

public:

    //Constructores

    /** @brief Creadora por defecto. 

      Se ejecuta automáticamente al declarar un procesador.
      \pre <em>cierto</em>
      \post El resultado es un procesador con tamaño de memoria vacío.
*/  
    Procesador();

/** @brief Creadora con valores concretos. 

      \pre Un entero m > 0.
      \post El resultado es un procesador con memoria de tamaño m.
*/  
    Procesador(int m);

    //Modificadores

/** @brief Da de alta un proceso.

      \pre Un procesador.
      \post El resultado es un procesador con un nuevo proceso.
*/  
    int alta_proceso(const Proceso& proc);

/** @brief Da de baja un proceso. 

      \pre Un identificador int de un proceso.
      \post El resultado es un procesador con un proceso menos.
*/  
    int baja_proceso(int proceso);

/** @brief Avanza el tiempo en un procesador. 

      \pre Un entero t > 0
      \post El resultado es un procesador con el tiempo avanzado.
*/
    void avanzar_tiempo(int t);

/** @brief Compacta la memoria en un procesador. 

      \pre <em>cierto</em>
      \post El resultado es un procesador con su memoria compactada.
*/  
    void compactar_memoria();

    //Consultoras

/** @brief Consulta si existe el proceso en el procesador. 

      \pre Un identificador int de un proceso.
      \post Dice si el proceso existe en el procesador, en caso de que exista, indica su posición.
*/
    int existe_proceso(int proceso) const;

/** @brief Consulta si el procesador contiene procesos. 

      \pre <em>cierto</em>
      \post Dice si el procesador contiene procesos.
*/
    int tiene_procesos() const;

/** @brief Consulta cuanta memoria libre tiene el procesador. 

      \pre <em>cierto</em>
      \post Dice la memoria libre del procesador.
*/
    int espacio_libre() const;

/** @brief Consulta si el proceso cabe en el procesador y su mejor hueco. 

      \pre Un proceso.
      \post Devuelve el tamaño del mejor hueco para el proceso.
*/
    int mejor_hueco(const Proceso& proc) const;

    //Lectura

/** @brief Lee un procesador. 

      \pre <em>cierto</em>
      \post Lee el contenido del parámetro implícito.
*/ 
    void leer();
    
    //Escritura

/** @brief Escribe un procesador. 

      \pre <em>cierto</em>
      \post Escribe el contenido del parámetro implícito por el canal estándar de salida.
*/ 
    void escribir() const;

private:

/** @brief Da de baja un proceso. 

      \pre El identificador y posición del proceso al que estamos dando de baja.
      \post El resultado es un hueco nuevo en la memoria del procesador.
*/
    void i_baja_proceso(int id, int lugar);

/** @brief Comprueba si hay un hueco antes del proceso. 

      \pre El identificador y posición del proceso al que estamos dando de baja y su iterador.
      \post El resultado es un tamaño de hueco mayor y una posición más cercana al inicio.
*/
    void i_baja_anterior(map<int, Proceso>::iterator it, int& memoria, int& posicion);

/** @brief Comprueba si hay un hueco después del proceso. 

      \pre El identificador y posición del proceso al que estamos dando de baja y su iterador.
      \post El resultado es un tamaño de hueco mayor.
*/
    void i_baja_siguiente(map<int, Proceso>::iterator it, int& memoria, int posicion);
};
#endif
