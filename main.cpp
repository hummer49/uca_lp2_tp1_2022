#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>
#include "Simulacion.hpp"

int main() {
    srand(time(NULL));
    try{
        Simulacion S1(15, 15, 10, 10);
        Simulacion S2(40, 20, 1, 1);

        S1.simular();
        // S1.guardar_datos(10, 10);       // guarda datos, agregar en la primera fila : r0,c0,rows,columns,steps,flag_end 

        S2.simular();
        // S2.guardar_datos(1,1);

    } catch(std::exception e){
        std::cout << "Error : " << e.what() << std::endl;
    }
    return 0;
}
