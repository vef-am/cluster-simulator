/** @file program.cc
    @brief Programa principal
*/

#include "Cluster.hh"
#include "Espera.hh"
using namespace std;

int main(){
    Cluster c;
    Espera e;
    c.configurar_cluster();
    e.leer(); 


    string comando;
    cin >> comando;

    while (comando != "fin"){
        if(comando == "cc" or comando == "configurar_cluster"){
            cout << "#" << comando << endl;
            
            c.configurar_cluster();
        }
        
        if(comando == "mc" or comando == "modificar_cluster"){
            string p;
            cin >> p;
            Cluster c1;
            c1.configurar_cluster();
            cout << "#" << comando << ' ' << p << endl;
            int resultado = c.modificar_cluster(p, c1);
            if (resultado == -1) cout << "error: no existe procesador" << endl;
            else if (resultado == -2) cout << "error: procesador con procesos" << endl;
            else if (resultado == -3) cout << "error: procesador con auxiliares" << endl;
        }
        
        if(comando == "ap" or comando == "alta_prioridad"){
            string prioridad;
            cin >> prioridad;
            cout << "#" << comando << " " << prioridad << endl;
            if(e.alta_prioridad(prioridad) == -1) cout << "error: ya existe prioridad" << endl;
        }

        if(comando == "bp" or comando == "baja_prioridad"){
            string prioridad;
            cin >> prioridad;
            cout << "#" << comando << " " << prioridad << endl;
            int resultado = e.baja_prioridad(prioridad);
            if (resultado == -1) cout << "error: no existe prioridad" << endl;
            else if (resultado == -2) cout << "error: prioridad con procesos" << endl;
        }
        
        if(comando == "ape" or comando == "alta_proceso_espera"){
            string prioridad;
            cin >> prioridad;
            Proceso proc;
            proc.leer();
            cout << "#" << comando << " " << prioridad << " " << proc.consultar_identificador() << endl;
            int resultado = e.alta_proceso_espera(proc, prioridad);
            if (resultado == -1) cout << "error: no existe prioridad" << endl;
            else if(resultado == -2) cout << "error: ya existe proceso" << endl;
        }
        
        if(comando == "app" or comando == "alta_proceso_procesador"){
            string p;
            cin >> p;
            Proceso proc;
            proc.leer();
            cout << "#" << comando << " " << p << " " << proc.consultar_identificador() << endl;
            int resultado = c.alta_proceso_procesador(p, proc);
            if(resultado == -1) cout << "error: no existe procesador" << endl;
            else if(resultado == -2) cout << "error: ya existe proceso" << endl;
            else if(resultado == -3) cout << "error: no cabe proceso" << endl;
        }
        
        if(comando == "bpp" or comando == "baja_proceso_procesador"){
            string p;
            int proceso;
            cin >> p >> proceso;
            cout << "#" << comando << " " << p << " " << proceso << endl;
            int resultado = c.baja_proceso_procesador(p, proceso);
            if(resultado == -1) cout << "error: no existe procesador" << endl;
            else if(resultado == -2) cout << "error: no existe proceso" << endl;
        }
        
        if(comando == "epc" or comando == "enviar_procesos_cluster"){
            int n;
            cin >> n;
            cout << "#" << comando << " " << n << endl;
            e.enviar_procesos_cluster(n,c);
        }
        
        if(comando == "at" or comando == "avanzar_tiempo"){
            int t;
            cin >> t;
            cout << "#" << comando << " " << t << endl;
            c.avanzar_tiempo(t);
        }
        
        if(comando == "ipri" or comando == "imprimir_prioridad"){
            string prioridad;
            cin >> prioridad;
            cout << "#" << comando << " " << prioridad << endl;
            if(e.imprimir_prioridad(prioridad) == -1) cout << "error: no existe prioridad" << endl;
        }
        
        if(comando == "iae" or comando == "imprimir_area_espera"){
            cout << "#" << comando << endl;
            e.imprimir_area_espera();
        }
        
        if(comando == "ipro" or comando == "imprimir_procesador"){
            string p;
            cin >> p;
            cout << "#" << comando << " " << p << endl;
            if(c.imprimir_procesador(p) == -1) cout << "error: no existe procesador" << endl;
        }
        
        if(comando == "ipc" or comando == "imprimir_procesadores_cluster"){
            cout << "#" << comando << endl;
            c.imprimir_procesadores_cluster();
        }
        
        if(comando == "iec" or comando == "imprimir_estructura_cluster"){
            cout << "#" << comando << endl;
            c.imprimir_estructura_cluster();
        }
        
        if(comando == "cmp" or comando == "compactar_memoria_procesador"){
            string p;
            cin >> p;
            cout << "#" << comando << ' ' << p << endl;
            if(c.compactar_memoria_procesador(p) == -1) cout << "error: no existe procesador" << endl;
        }
        
        if(comando == "cmc" or comando == "compactar_memoria_cluster"){
            cout << "#" << comando << endl;
            c.compactar_memoria_cluster();
        }

        cin >> comando;
    }
}
