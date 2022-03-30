#include <vector>

#define LIMIT 25000

class Simulacion
{
    private:
        int     R;                                  //numero de filas
        int     C;                                  //numero de columnas
        std::vector<std::vector<int>> tablero;      //tablero
        int     ri;                                 //posicion fila actual (inicial)
        int     ci;                                 //posicion columna actual (inicial)
        int     steps;                              //numero de movimientos
        int     empty;                              //numero de casillas vacias
        bool    end_flag;                           //indica si se llego al limite antes de cubrir todas las casillas
    public:
        int     get_R(void); 
        void    set_R(int r);
        int     get_C(void);
        void    set_C(int c);
        int     get_ri(void);     
        void    set_ri(int r);      
        int     get_ci(void);     
        void    set_ci(int c);      
        int     get_steps(void);  
        void    set_steps(int steps);
        void    incrementar_steps();
        int     get_empty(void);
        void    set_empty(int empty);
        void    decrementar_empty();
        void    inicializar_tablero();
        void    imprimir_tablero();
        void    simular();
        std::vector<int> movimientos_posibles();
        void    guardar_datos();
        void    guardar_datos(int r0, int c0);
    
    Simulacion(int _R, int _C, int _ri, int _ci){
        if(_R < 2 || _R >= 41){
            throw std::invalid_argument("El valor de las filas debe estar en el rango (2, 41)");
        }
        if (_C < 2 || _C >= 21){
            throw std::invalid_argument("El valor de las columnas debe estar en el rango (2, 21)");
        }
        set_R(_R);
        set_C(_C);
        set_ri(_ri);
        set_ci(_ci);
        set_steps(0);
        set_empty( _R * _C);
        inicializar_tablero();
        end_flag = true;                // si termino antes de los 25000 pasos, cambia a false
    }
    ~Simulacion(){
        for(int row = 0; row < tablero.size() ; row++){
            tablero[row].clear();
        }
    }
};
