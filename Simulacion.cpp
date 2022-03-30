#include <iostream>
#include <vector>
#include <fstream>
#include "Simulacion.hpp"

int     Simulacion::get_R(void){ return R; }
void    Simulacion::set_R(int r){ R = r; }
int     Simulacion::get_C(void){ return C; }
void    Simulacion::set_C(int c){ C = c; }
int     Simulacion::get_ri(void){ return ri; }
void    Simulacion::set_ri(int r){ ri = r; }
int     Simulacion::get_ci(void){ return ci; }
void    Simulacion::set_ci(int c){ ci = c; }
int     Simulacion::get_steps(void){ return steps; }
void    Simulacion::set_steps(int steps_){ steps = steps_; }
void    Simulacion::incrementar_steps(){ steps++; }
int     Simulacion::get_empty(void){ return empty; }
void    Simulacion::set_empty(int empty_){ empty = empty_; }
void    Simulacion::decrementar_empty(){ empty--; }

void Simulacion::inicializar_tablero(){
    for(int r = 0; r < R; r++){
        std::vector<int> row;
        for(int c = 0; c < C; c++){
            row.push_back(0);
        }
        tablero.push_back(row);
    }
}

void Simulacion::imprimir_tablero(){
    for(int r = 0; r < R; r++){
        for(int c = 0; c < C; c++){
            if(r == ri && c == ci){
                std::cout << (tablero[r][c] >= 10? " :_": " :_ ");
                std::cout << (tablero[r][c] == 0 ? "-" : std::to_string(tablero[r][c]));
            }else if(r == ri && c == ci + 1){
                std::cout << (tablero[r][c] >= 10? "_: ": "_:  ");
                std::cout << (tablero[r][c] == 0 ? "-" : std::to_string(tablero[r][c]));
            }else{
                std::cout << (tablero[r][c] >= 10? " | ": " |  ");
                std::cout << (tablero[r][c] == 0 ? "-" : std::to_string(tablero[r][c]));
            }
        }
        std::cout << "|" << std::endl;
    }
}

void Simulacion::simular(){
    while(steps < LIMIT){
        // imprimir el tablero
        if(steps % 2000 == 1){
            std::cout << std::endl << "============================================" << std::endl;
            std::cout << "PASO " << this->steps << std::endl;
            this->imprimir_tablero();
        }
        // controlar si la celda actual esta vacia
        tablero[ri][ci] == 0 ? decrementar_empty() : void() ;       //decrementar el numero de celdas vacias si aplica
        // incrementar los pasos en la celda actual
        tablero[ri][ci] = tablero[ri][ci] + 1;
        // cortar el ciclo si el tablero esta completo
        if(empty == 0){
            // imprimir el estado final
            std::cout << std::endl << "============================================" << std::endl;
            std::cout << "PASO FINAL " << this->steps << std::endl;
            this->imprimir_tablero();
            this->end_flag = false;
            break;
        }
        // pasar alsiguiente paso
        incrementar_steps();
        // preparar el siguiente movimiento
        std::vector<int> m_pos = movimientos_posibles();
        int m = m_pos[ rand() % m_pos.size() ];
        if(m == 1){
            ri -= 1;
            ci -= 1;
        }else if(m == 2){
            ri -= 1;
        }else if(m==3){
            ri -= 1;
            ci += 1;
        }else if(m==4){
            ci -= 1;
        }else if(m==5){
            ci += 1;
        }else if(m==6){
            ri += 1;
            ci -= 1;
        }else if(m==7){
            ri += 1;
        }else if(m==8){
            ri += 1;
            ci += 1;
        }
    }
    if(this->steps == 25000 && this->end_flag == true){
        std::cout << std::endl << "El programa finalizo antes de cubrir todas las celdas" << std::endl;
    }
}

std::vector<int> Simulacion::movimientos_posibles(){
    std::vector<int> opt;
    opt.reserve(8*sizeof(int));
    // 
    if(ri > 0 && ri < R-1){
        if(ci > 0 && ci < C -1){
        opt = {1,2,3,4,5,6,7,8};    //centro
        }else if(ci == 0){
        opt = {2,3,5,7,8};          //borde ESTE
        }else if(ci == C-1){
        opt = {1,2,4,6,7};          //borde OESTE
        }
    } else if(ri == 0){
        if(ci > 0 && ci < C-1){
        opt = {4,5,6,7,8};          //borde NORTE
        }else if(ci == 0){
        opt = {5,7,8};              //esquina NORESTE
        }else if(ci == C-1){
        opt = {4,6,7};              //esquina NOROESTE
        }
    } else if(ri == R-1){
        if(ci > 0 && ci < C-1){
        opt = {1,2,3,4,5};          //borde SUR
        }else if(ci == 0){
        opt = {2,3,5};              //esquina SURESTE
        }else if(ci == C-1){
        opt = {1,2,4};              //esquina SUROESTE
        }
    }
    opt.shrink_to_fit();            //
    return opt;
}

void Simulacion::guardar_datos(){
    std::ofstream file;
    file.open("data.csv", std::ios::app);
    file << this->R <<"," << this->C << "," << this->steps << "," << this->end_flag << std::endl;
}
void Simulacion::guardar_datos(int r0, int c0){
    std::ofstream file;
    file.open("data_" + std::to_string(this->R) + "_" + std::to_string(this->C) + ".csv", std::ios::app);
    file << r0 << "," << c0 << ",";
    file << this->R << "," << this->C << "," << this->steps << "," << this->end_flag << std::endl;
}