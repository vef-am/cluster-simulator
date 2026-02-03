/** @file Espera.cc
    @brief Código de la clase Espera
*/

#include "Espera.hh"
using namespace std;

Espera::Espera(){}

int Espera::alta_prioridad(const string& prioridad){
    map<string, Prioridad>::const_iterator it = m.find(prioridad);

    if(it != m.end()) return -1;
    
    Prioridad p;
    
    p.colocados = 0;
    p.rechazados = 0;

    m.insert(make_pair(prioridad, p));

    return 0;
}

int Espera::baja_prioridad(const string& prioridad){
    map<string, Prioridad>::iterator it = m.find(prioridad);

    if(it == m.end()) return -1;

    if(not (*it).second.lista_proceso.empty()) return -2;

    m.erase(it);
    return 0;
}

int Espera::alta_proceso_espera(const Proceso& p, const string& prioridad){
    map<string, Prioridad>::iterator it = m.find(prioridad);

    if(it == m.end()) return -1;

    list <Proceso>::iterator it1 = (*it).second.lista_proceso.begin();
    while(it1 != (*it).second.lista_proceso.end()){
        if((*it1).consultar_identificador() == p.consultar_identificador()) return -2;
        ++it1;
    }

    (*it).second.lista_proceso.insert(it1, p);
    return 0;
}

void Espera::enviar_procesos_cluster(int n, Cluster &c){
    map<string, Prioridad>::iterator it = m.begin();
    while(it != m.end() and n != 0){
        list <Proceso> rechazos;
        list <Proceso>::iterator it1 = (*it).second.lista_proceso.begin();
        while(it1 != (*it).second.lista_proceso.end() and n != 0){
            if(c.enviar_procesos((*it1)) == -1){
                ++(*it).second.rechazados;
                rechazos.insert(rechazos.end(), (*it1));
                it1 = (*it).second.lista_proceso.erase(it1);
            }

            else{
                ++(*it).second.colocados;
                it1 = (*it).second.lista_proceso.erase(it1);
                --n;
            }
        }

        (*it).second.lista_proceso.insert((*it).second.lista_proceso.end(), rechazos.begin(), rechazos.end());

        ++it;
    }
}

void Espera::leer(){
    int n;
    cin >> n;
    Prioridad p;
    
    p.colocados = 0;
    p.rechazados = 0;

    while(n != 0){
        string prioridad;
        cin >> prioridad;
        m.insert(make_pair(prioridad, p));
        --n;
    }
}

int Espera::imprimir_prioridad(const string& prioridad) const{
    map<string, Prioridad>::const_iterator it = m.find(prioridad);
    if(it == m.end()) return -1;

    imprimir_procesos(it);
    return 0;
}

void Espera::imprimir_area_espera() const{
    for(map<string, Prioridad>::const_iterator it = m.begin(); it != m.end(); ++it){
        cout << (*it).first << endl;
        imprimir_procesos(it);
    }
}

void Espera::imprimir_procesos(map<string, Prioridad>::const_iterator it){
    for(list <Proceso>::const_iterator it1 = (*it).second.lista_proceso.begin(); it1 != (*it).second.lista_proceso.end(); ++it1){
        (*it1).escribir();
    }

    cout << (*it).second.colocados << " " << (*it).second.rechazados << endl;
}