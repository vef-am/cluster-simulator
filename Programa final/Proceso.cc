/** @file Proceso.cc
    @brief Código de la clase Proceso
*/

#include "Proceso.hh"
using namespace std;

Proceso::Proceso(){
    identificador = 0;
    memoria = 0;
    tiempo = 0;
}

int Proceso::avanzar_tiempo(int t){
    tiempo -= t;
    if(tiempo <= 0){
        return -1;
    }

    return 0;
}

int Proceso::consultar_memoria() const{
    return memoria;
}

int Proceso::consultar_tiempo() const{
    return tiempo;
}

int Proceso::consultar_identificador() const{
    return identificador;
}

void Proceso::leer(){
    cin >> identificador >> memoria >> tiempo;
}

void Proceso::escribir() const{
    cout << identificador << " " << memoria << " " << tiempo << endl;
}