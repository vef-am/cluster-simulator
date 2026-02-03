/** @file Cluster.cc
    @brief Código de la clase Cluster
*/

#include "Cluster.hh"

Cluster::Cluster(){
    a = BinTree<string>();
}

void Cluster::configurar_cluster(){
    if (not m.empty()){
        m.erase (m.begin(), m.end());
    }
    
    leer_arbol_cluster(a);
}

int Cluster::modificar_cluster(const string& p, Cluster& c){
    map<string, Procesador>::iterator it = m.find(p);

    if(it == m.end()) return -1;

    if((*it).second.tiene_procesos() == -1) return -2;

    if(editar_arbol_cluster(a, c.a, p) == -1) return -3;

    m.erase(p);
    for(map<string, Procesador>::iterator it = c.m.begin(); it != c.m.end(); ++it){
        m.insert(make_pair((*it).first, (*it).second));
    }

    return 0;
}

int Cluster::alta_proceso_procesador(const string& p, const Proceso& proc){
    map<string, Procesador>::iterator it = m.find(p);

    if(it == m.end()) return -1;

    int resultado = (*it).second.alta_proceso(proc);
    if(resultado == -1) return -2;
    if(resultado == -2) return -3;

    return 0;
}

int Cluster::baja_proceso_procesador(const string& p, int proceso){
    map<string, Procesador>::iterator it = m.find(p);

    if(it == m.end()) return -1;

    int resultado = (*it).second.baja_proceso(proceso);
    if(resultado == -1) return -2;

    return 0;
}

int Cluster::enviar_procesos(const Proceso& proc){
    int hueco = -1, memoria_libre = 0, profundidad = 0;
    string p;

    enviar_procesos_arbol(a, proc, hueco, memoria_libre, profundidad, 0, p);

    if(hueco != -1){
        alta_proceso_procesador(p, proc);
        return 0;
    }

    return -1;
}

void Cluster::avanzar_tiempo(int t){
    for(map<string, Procesador>::iterator it = m.begin(); it != m.end(); ++it){
        (*it).second.avanzar_tiempo(t);
    }
}

int Cluster::compactar_memoria_procesador(const string& p){
    map<string, Procesador>::iterator it = m.find(p);

    if(it == m.end()) return -1;

    (*it).second.compactar_memoria();

    return 0;
}

void Cluster::compactar_memoria_cluster(){
    for(map<string, Procesador>::iterator it = m.begin(); it != m.end(); ++it){
        (*it).second.compactar_memoria();
    }
}

int Cluster::imprimir_procesador(const string& p) const{
    map<string, Procesador>::const_iterator it = m.find(p);
    if(it == m.end()) return -1;
    (*it).second.escribir();
    return 0;
}

void Cluster::imprimir_procesadores_cluster() const{
    for(map<string, Procesador>::const_iterator it = m.begin(); it != m.end(); ++it){
        cout << (*it).first << endl;
        (*it).second.escribir();
    }
}

void Cluster::imprimir_estructura_cluster() const{
    escribir_arbol_cluster(a);
    cout << endl;
}

void Cluster::leer_arbol_cluster(BinTree<string>& a){
    BinTree<string> left, right;
    string p;
    Procesador procesador;
    cin >> p;
    if(p != "*"){
        procesador.leer();
        m.insert(pair<string,Procesador>(p, procesador));
        leer_arbol_cluster(left);
        leer_arbol_cluster(right);
        a = BinTree<string>(p, left, right);
    }
}

void Cluster::escribir_arbol_cluster(const BinTree<string>& a){
    if(a.empty()){
        cout << ' ';
    }
    else{
        cout << '(';
        cout << a.value();
        escribir_arbol_cluster(a.left());
        escribir_arbol_cluster(a.right());
        cout << ')';
    }
}

int Cluster::editar_arbol_cluster(BinTree<string>& a, const BinTree<string>& b, const string& p){
    if(a.empty()){
        return -2;
    }

    else{
        if(a.value() == p and a.left().empty() and a.right().empty()){
            a = BinTree<string>(b.value(), b.left(), b.right());
            return 0;
        }

        if(a.value() == p) return -1;

        BinTree<string> left = a.left();
        BinTree<string> right = a.right();
        int resultado_l = editar_arbol_cluster(left, b, p);
        a = BinTree<string>(a.value(), left, right);
        if(resultado_l == 0) return 0;
        if(resultado_l == -1) return -1;
        if(resultado_l == -2){
            int resultado_r = editar_arbol_cluster(right, b, p);
            a = BinTree<string>(a.value(), left, right);
            return resultado_r;
        }

        return -2;
    }
}

void Cluster::enviar_procesos_arbol(const BinTree<string>& a, const Proceso& proc, int& hueco, int& memoria_libre, int& profundidad, int pr_actual,  string& p){
    if(not a.empty()){
        
        enviar_procesos_arbol(a.left(), proc, hueco, memoria_libre, profundidad, pr_actual+1, p);
        enviar_procesos_arbol(a.right(), proc, hueco, memoria_libre, profundidad, pr_actual+1, p);
        
        int hueco_raiz = -1, memoria_raiz = 0;
        map<string, Procesador>::const_iterator it = m.find(a.value());
        if((*it).second.existe_proceso(proc.consultar_identificador()) == -1){
            hueco_raiz = (*it).second.mejor_hueco(proc);
            memoria_raiz = (*it).second.espacio_libre();
        }

        cmp(hueco, memoria_libre, profundidad, p, hueco_raiz, memoria_raiz, pr_actual, a.value());
    }
}

void Cluster::cmp(int& mejor_hueco, int& mejor_memoria, int& profundidad, string& mejor_procesador, const int& hr, const int& mr, const int& profundidadr, const string& pr){
    if(hr != -1){
        if(mejor_hueco == -1){
            mejor_hueco = hr;
            mejor_memoria = mr;
            mejor_procesador = pr;
            profundidad = profundidadr;
        }
        
        else if(mejor_hueco < hr){
            mejor_hueco = hr;
            mejor_memoria = mr;
            mejor_procesador = pr;
            profundidad = profundidadr;
        }

        else if(mejor_hueco == hr and mejor_memoria < mr){
            mejor_hueco = hr;
            mejor_memoria = mr;
            mejor_procesador = pr;
            profundidad = profundidadr;
        }
        
        else if(mejor_hueco == hr and mejor_memoria == mr and profundidad > profundidadr){
            mejor_hueco = hr;
            mejor_memoria = mr;
            mejor_procesador = pr;
            profundidad = profundidadr;
        }
    }
}




int Cluster::podar_cluster(int k){
    map<string, Procesador>::const_iterator it = m.find(a.value());
    if((*it).second.cantidad_procesos() < k) return -1;

    BinTree<string> left = a.left();
    int poda_left = podar_cluster_recursivo(left, k);

    BinTree<string> right = a.right();
    int poda_right = podar_cluster_recursivo(right, k);

    a = BinTree<string>(a.value(), left, right);

    return poda_left + poda_right;
}

int Cluster::podar_cluster_recursivo(BinTree<string>& a, int k){
    if(a.empty()){
        return 0;
    }
    else{
        BinTree<string> left = a.left();
        BinTree<string> right = a.right();

        map<string, Procesador>::const_iterator it = m.find(a.value());
        if((*it).second.cantidad_procesos() < k){
            int poda_left = podar_descendientes(left);
            int poda_right = podar_descendientes(right);

            a = BinTree<string>();
            m.erase(it);

            return poda_left + poda_right + 1;
        }
        else{
            int poda_left = podar_cluster_recursivo(left, k);
            int poda_right = podar_cluster_recursivo(right, k);

            a = BinTree<string>(a.value(), left, right);

            return poda_left + poda_right;
        }
    }
}

int Cluster::podar_descendientes(const BinTree<string>& a){
    if(a.empty()){
        return 0;
    }
    else{
        int poda_left = podar_descendientes(a.left());
        int poda_right = podar_descendientes(a.right());

        map<string, Procesador>::const_iterator it = m.find(a.value());
        m.erase(it);

        return poda_left + poda_right + 1;
    }
}