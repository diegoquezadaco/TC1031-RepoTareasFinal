/*
 * funciones.h
 *
 *  Created on: 17/08/2023
 *      Author: Diego Quezada Colorado
 *      Matricula A01710024
 */

#ifndef FUNCIONES_H_
#define FUNCIONES_H_

using namespace std;

class Funciones{
    public:
        /*
     *Función sumaIterativa
     * Utiliza un bucle for para sumar los números de 1 a n de forma iterativa
     * Guarda el resultado en la variable suma y el valor que se acomule será
     * el return de la función al final
     */
    int sumaIterativa(int n){
        int suma=0;
        for (int i=1;i<=n;i++){
            suma += i;
    }
    return suma;
    }
    /*
     * Función sumaRecursiva
     * Calcula la suma de los números de 1 a n de forma recursiva utilizando la
     * definición matemática de la suma, y su caso base es cuando el valor n
     * es igual a 0, parq que de ahí regrese y realice los returns correspondientes
     * de cada llamda recursiva.
     * */
    long sumaRecursiva(int n){
        if (n==0){
            return 0;
        }
        else{
            return n+sumaRecursiva(n-1);
        }
    }/*
     * Función sumaDirecta
     * Calcula la suma de los números de 1 a n de forma directa utilizando 
     * la fórmula de la suma de una progresión aritmética.
     * Calcula el valor directamente en el return con la fórmula antes 
     * mencionada
     * */
    int sumaDirecta(int n){
        return (n*(n+1))/2;
    }

};

#endif