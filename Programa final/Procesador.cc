/** @file Procesador.cc
    @brief Código de la clase Procesador
*/

#include "Procesador.hh"
using namespace std;

Procesador::Procesador(){
    memoria_max = 0;
}

Procesador::Procesador(int m){
    memoria_max = m;
}

int Procesador::alta_proceso(const Proceso& proc){
    int existe = existe_proceso(proc.consultar_identificador());
    if(existe != -1) return -1;

    int espacio = mejor_hueco(proc);
    if(espacio == -1) return -2;

    int lugar = (*map_huecos[espacio].begin());
    map_huecos[espacio].erase(lugar);
    if(map_huecos[espacio].empty()) map_huecos.erase(espacio);
    memoria_libre -= espacio;

    int nuevo_hueco = espacio - proc.consultar_memoria();
    int posicion = lugar + proc.consultar_memoria();

    if(nuevo_hueco > 0){
        map_huecos[nuevo_hueco].insert(posicion);
        memoria_libre += nuevo_hueco;
    }

    map_identificador.insert(make_pair(proc.consultar_identificador(), lugar));
    map_posicion.insert(make_pair(lugar, proc));

    return 0;
}

int Procesador::baja_proceso(int proceso){
    int lugar = existe_proceso(proceso);
    if(lugar == -1) return -1;

    i_baja_proceso(proceso, lugar);

    return 0;
}

void Procesador::i_baja_proceso(int id, int lugar){
    map<int, Proceso>::iterator it = map_posicion.find(lugar);
    map_identificador.erase(id);

    int memoria = (*it).second.consultar_memoria();
    int posicion = (*it).first;
    memoria_libre += memoria;

    i_baja_siguiente(it, memoria, posicion);

    i_baja_anterior(it, memoria, posicion);

    map_posicion.erase(it);
    map_huecos[memoria].insert(posicion);
}

void Procesador::i_baja_anterior(map<int, Proceso>::iterator it, int& memoria, int& posicion){
    if(it != map_posicion.begin()){
        --it;
        int ini = (*it).first;

        int hueco = posicion - (ini + (*it).second.consultar_memoria());
        posicion -= hueco;

        if(hueco != 0){
            map<int, set<int>>::iterator it1 = map_huecos.find(hueco);

            (*it1).second.erase(posicion);
            if((*it1).second.empty()) map_huecos.erase(it1);

            memoria += hueco;
        }
    }
    
    else if (posicion != 0){
        map<int, set<int>>::iterator it1 = map_huecos.find(posicion);

        memoria += posicion;
        posicion -= posicion;

        (*it1).second.erase(posicion);
        if((*it1).second.empty()) map_huecos.erase(it1);
    }
}

void Procesador::i_baja_siguiente(map<int, Proceso>::iterator it, int& memoria, int posicion){
    ++it;
    if(it != map_posicion.end()){
        int ini = (*it).first;
        int hueco = ini - (posicion + memoria);
        posicion += memoria;
        
        if(hueco != 0){
            map<int, set<int>>::iterator it1 = map_huecos.find(hueco);

            (*it1).second.erase(posicion);
            if((*it1).second.empty()) map_huecos.erase(it1);

            memoria += hueco;
        }
    }

    else if(memoria_max - (memoria + posicion) > 0){
        posicion += memoria;
        int nueva_memor = memoria_max - posicion;

        map<int, set<int>>::iterator it1 = map_huecos.find(nueva_memor);

        memoria += nueva_memor;

        (*it1).second.erase(posicion);
        if((*it1).second.empty()) map_huecos.erase(it1);
    }
}

void Procesador::avanzar_tiempo(int t){
    map<int, Proceso>::iterator it = map_posicion.begin();
    while(it != map_posicion.end()){
        int resultado = (*it).second.avanzar_tiempo(t);
        if(resultado == -1) {
            int id = (*it).second.consultar_identificador();
            int posicion = (*it).first;
            ++it;
            i_baja_proceso(id, posicion);
        }

        else ++it;
    }
}

void Procesador::compactar_memoria(){
    map<int, Proceso>::iterator it = map_posicion.begin();

    if(it != map_posicion.end()){
        map_huecos.clear();
        map_identificador.clear();

        int pos = (*it).first;
        int sig_pos;

        if(pos != 0){
            Proceso proc = (*it).second;
            it = map_posicion.erase(it);
            map_posicion.insert(make_pair(0, proc));
            map_identificador.insert(make_pair(proc.consultar_identificador(), 0));
            sig_pos = 0 + proc.consultar_memoria();
        }
        else{
            map_identificador.insert(make_pair((*it).second.consultar_identificador(), pos));
            sig_pos = pos + (*it).second.consultar_memoria();
            ++it;
        }

        while(it != map_posicion.end()){
            if(sig_pos == (*it).first){
                map_identificador.insert(make_pair((*it).second.consultar_identificador(), sig_pos));
                sig_pos = sig_pos + (*it).second.consultar_memoria();
                ++it;
            }

            else{
                Proceso proc = (*it).second;
                it = map_posicion.erase(it);
                map_posicion.insert(make_pair(sig_pos, proc));
                map_identificador.insert(make_pair(proc.consultar_identificador(), sig_pos));
                sig_pos = sig_pos + proc.consultar_memoria();
            }
        }

        map_huecos[memoria_libre].insert(sig_pos);
    }
}

int Procesador::existe_proceso(int proceso) const{
    map<int, int>::const_iterator it = map_identificador.find(proceso);
    if(it != map_identificador.end()) return (*it).second;
    return -1;
}

int Procesador::tiene_procesos() const{
    if(map_posicion.empty()) return 0;
    return -1;
}

int Procesador::espacio_libre() const{
    return memoria_libre;
}

int Procesador::mejor_hueco(const Proceso& proc) const{
    map<int, set<int>>::const_iterator it = map_huecos.lower_bound(proc.consultar_memoria());
    if (it != map_huecos.end()) return (*it).first;
    return -1;
}

void Procesador::leer(){
    cin >> memoria_max;
    map_huecos[memoria_max].insert(0);
    memoria_libre = memoria_max;
}
    
void Procesador::escribir() const{
    for(map<int, Proceso>::const_iterator it = map_posicion.begin(); it != map_posicion.end(); ++it){
        cout << (*it).first << " ";
        (*it).second.escribir();
    }
}