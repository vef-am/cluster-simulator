/** @file Cluster.hh
    @brief Especificación de la clase Cluster
*/

#ifndef CLUSTER_HH
#define CLUSTER_HH

#ifndef NO_DIAGRAM
#include <iostream>
#include <map>
#include "BinTree.hh"
#endif

#include "Procesador.hh"

/** @class Cluster
    @brief Representa el cluster. 

    Dispone de un número de procesadores variable, distribuidos en forma de árbol binario, con identificadores únicos.
*/
class Cluster {

private:

/** @brief Estructura del cluster */
BinTree<string> a;


/** @brief Procesadores del cluster ordenadas por identificador */
map<string, Procesador> m;

public:

    //Constructores

/** @brief Creadora por defecto.
        Se ejecuta automáticamente al declarar un cluster.
        \pre <em>cierto</em>
        \post El resultado es un  cluster vacío.
*/
    Cluster();

    //Modificadores

/** @brief Configura el cluster.

      \pre <em>cierto</em>
      \post El resultado es un cluster configurado.
*/
    void configurar_cluster();

/** @brief Modifica el cluster.

      \pre Un identificador de procesador.
      \post El resultado es un cluster modificado.
*/
    int modificar_cluster(const string& p, Cluster& c);

/** @brief Poda el cluster.

      \pre <em>cierto</em>
      \post El resultado es un cluster podado.
*/
    int podar_cluster(int k);

/** @brief Envia un proceso al mejor procesador del cluster si es posible. 

      \pre Un proceso.
      \post El mejor procesador posible con un nuevo proceso.
*/
    int enviar_procesos(const Proceso& proc);

/** @brief Da de alta un proceso.

      \pre Un identificador de procesador y un proceso.
      \post El resultado es un proceso nuevo en un procesador en el cluster.
*/
    int alta_proceso_procesador(const string& p, const Proceso& proc);

/** @brief Da de baja un proceso.

      \pre Un identificador de procesador y un identificador de proceso.
      \post El resultado es un proceso menos en un procesador en el cluster.
*/
    int baja_proceso_procesador(const string& p, int proceso);

/** @brief Avanza el tiempo en el cluster. 

      \pre Un entero t > 0.
      \post El resultado es el cluster con el tiempo avanzado.
*/
    void avanzar_tiempo(int t);

/** @brief Compacta la memoria de un procesador del cluster. 

      \pre Un identificador p.
      \post Un procesador de identificador p con la memoria compactada.
*/
    int compactar_memoria_procesador(const string& p);

/** @brief Compacta la memoria del cluster. 

      \pre <em>cierto</em>
      \post Un cluster con la memoria compactada.
*/
    void compactar_memoria_cluster();

    //Escritura

/** @brief Imprime un procesador del cluster. 

      \pre Un identificador p.
      \post Escribe el contenido del parámetro implícito por el canal estándar de salida.
*/
    int imprimir_procesador(const string& p) const;

/** @brief Imprime los procesadores del cluster. 

      \pre <em>cierto</em>
      \post Escribe el contenido del parámetro implícito por el canal estándar de salida.
*/
    void imprimir_procesadores_cluster() const;

/** @brief Imprime la estructura del cluster. 

      \pre <em>cierto</em>
      \post Escribe el contenido del parámetro implícito por el canal estándar de salida.
*/
    void imprimir_estructura_cluster() const;

private:

/** @brief Operación de lectura de un árbol de identificadores de procesadores.

      \pre Un árbol a.
      \post a contiene el árbol de procesadores leído de la entrada.
*/
    void leer_arbol_cluster(BinTree<string>& a);

/** @brief Operación de escritura de un árbol de identificadores de procesadores.

      \pre Un árbol a.
      \post Se ha escrito a por el canal estándar de salida.
*/
    static void escribir_arbol_cluster(const BinTree<string>& a);

/** @brief Operación de modificación de un árbol de identificadores de procesadores.

      \pre Dos árboles a y b y un identificador de un proceso.
      \post En caso de que se haya hecho la modificación: Un árbol a donde a.value() = p entonces a.value() = b.
            Si no, se devuelve un número que indica que no se ha podido completar la modificación porque a.value() = p, not a.left().empty() y/o not a.right().empty().
*/
    static int editar_arbol_cluster(BinTree<string>& a, const BinTree<string>& b, const string& p);

/** @brief Operación de envío de procesos a un árbol de identificadores de procesadores.

      \pre Un árbol, un proceso, su profundidad en el momento y los elementos a comparar (hueco, memoria libre y profundidad) del mejor procesador posible actual (identificador p).
      \post El mejor procesador posible para un proceso.
*/
    void enviar_procesos_arbol(const BinTree<string>& a, const Proceso& proc, int& hueco, int& memoria_libre, int& profundidad, int pr_actual,  string& p);

/** @brief Comparador de procesadores.

      \pre Los elementos a comparar (hueco, memoria libre y profundidad) de ambos procesadores (identificadores).
      \post El mejor procesador posible de los 2 y sus elementos.
*/
    static void cmp(int& mejor_hueco, int& mejor_memoria, int& profundidad, string& mejor_procesador, const int& hr, const int& mr, const int& profundidadr, const string& pr);

    int podar_cluster_recursivo(BinTree<string>& a, int k);

    int podar_descendientes(const BinTree<string>& a);
};
#endif
