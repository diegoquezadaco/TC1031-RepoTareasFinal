/*
 * sorts.h
 *
 *  Created on: 06/09/2023
 *      Author: Diego Quezada Colorado
 *      Matricula A01710024
 */

#ifndef SORTS_H_
#define SORTS_H_
using namespace std;


template <class T>
class Sorts{
    public:
        /*
         *Función swap
         *es una función auxiliar que nos va a estar ayudando en las funciones
         *que ordenan arreglos, simplemente cambia de lugar 2 elementos de un
         *mismo vector
         *Recibe como parámetros el vector del que se cambiaran los elementos,
         * y las posiciones del vector que contienen los datos a intercambiar
         */
        void swap(vector<T> &v, int i, int j) {
            T aux = v[i];
            v[i] = v[j];
            v[j] = aux;
        }
        /*
         *Función ordenaSeleccion
         *Ordena un vector de menor a mayor utilizando el algoritmo de selección
         *Recorre el vector y busca el elemento más pequeño en la lista y este
         lo intercambia con el elemento en la posición i, y así sucesivamente 
         hasta que el vector esté ordenado
            *Recibe como parámetro el vector a ordenar
        */
        void ordenaSeleccion(vector<T> &v) {
            for (int i=0; i<v.size(); i++){
                int m=i;
                for (int j=i;j<v.size();j++){
                    if (v[j]<v[m]){
                        m=j;
                    }
                }
                swap(v, i, m);
            }
        }
        /*
         *Función ordenaBurbuja
         *Ordena un vector de menor a mayor 
         *Recorre el vector y compara el elemento en la posición i con el elemento
         *en la posición i+1, si el elemento en la posición i es mayor que el elemento
         *en la posición i+1, los intercambia, y así sucesivamente hasta que el vector
         *esté ordenado, empuja el elemento más grande hasta el final del vector
            *Recibe como parámetro el vector a ordenar
        */
        void ordenaBurbuja(vector<T> &v) {
            for (int i=v.size()-1; i>0; i--){
                for (int j=0;j<i;j++){
                    if (v[j]>v[j+1]){
                        swap(v,j,j+1);
                    }
                }

            }
        }
        /*
         *Función ordenaMerge
         *Ordena un vector de menor a mayor utilizando el algoritmo de merge
         *Divide el vector en 2 partes, y las ordena de forma recursiva, y después
         *las va uniendo en un solo vector ordenado
            *Recibe como parámetro el vector a ordenar
         
        */
        void ordenaMerge(vector<T> &v) {
            vector<T> tmp(v.size());
            mergeSplit(v, tmp, 0, v.size() - 1);
        }
        /*
         *Función mergeArray
         *Función auxiliar de ordenaMerge
         *Une 2 vectores ordenados en un solo vector ordenado
            *Recibe como parámetros el vector a ordenar, un vector auxiliar, y los
            índices de los vectores a unir
         */
        void mergeArray(vector<T> &A,vector<T> &B, int low, int mid, int high){
            int i, j, k;
            i = low;
            j = mid + 1;
            k = low;
            while (i <= mid &&j <= high) {
                if (A[i] < A[j]) {
                    B[k] = A[i];
                    i++;
                } else {
                    B[k] = A[j];
                    j++;
                }
                k++;
            }
            if (i > mid) {
                for (; j <= high; j++) {
                    B[k++] = A[j];
                }
            } else {
                for (; i <= mid; i++) {
                    B[k++] = A[i];
                }
            }
            for (int i = low; i <= high; i++) {
                A[i] = B[i];
            }
        }
        /*
         *Función mergeSplit
            *Función auxiliar de ordenaMerge
            *Es una función recursica que divide el vector en 2 partes, y las ordena
            *de forma recursiva, y después las va uniendo en un solo vector ordenado
            *Recibe como parámetros el vector a ordenar, un vector auxiliar, y los
            índices de los vectores a unir
            *Es la función máscara que hace las llamadas recursivas para 
            llevar a cabo ordenaMerge
         */
        void mergeSplit(vector<T> &A,vector<T> &B, int low, int high){
            int mid;
            if ( (high - low) < 1 ) {
                return;
            }
            mid = (high + low) / 2;
            mergeSplit(A, B, low, mid);
            mergeSplit(A, B, mid + 1, high);
            mergeArray(A, B, low, mid, high);
        }
        /*
         *Función busqSecuencial
         *Busca un elemento en un vector de forma secuencial
         *Recorre el vector y compara el elemento en la posición i con el elemento
         *que se busca, si son iguales regresa la posición en la que se encuentra
         *el elemento, si no, regresa -1
            *Recibe como parámetros el vector en el que se va a buscar el elemento
            *y el elemento que se busca
        */
        int busqSecuencial(const vector<T> &v, int s) {
            for (int i=0; i<v.size(); i++){
                if (v[i]==s){
                    return i;
                }
            }
            return -1;
        }
        /*
         *Función busqBinaria
         *Busca un elemento en un vector de forma binaria
         *Divide el vector en 2 partes, y busca el elemento en la parte en la que
         *se encuentra, si el elemento es menor que el elemento en la posición mid,
         *busca en la parte izquierda, si es mayor, busca en la parte derecha, y así
         *sucesivamente hasta encontrar el elemento, si no lo encuentra regresa -1
            *Recibe como parámetros el vector en el que se va a buscar el elemento
            *y el elemento que se busca
        */
        int busqBinaria(const vector<T> &v, int s) {
            int low=0;
            int high = v.size();            
            int p = aux_busqBinaria(v, low, high, s);
            if (s==v[p]){
                return p;
            }
            return -1;
        }
        /*
         *Función aux_busqBinaria
         *Función auxiliar de busqBinaria
            *Es una función recursica que divide el vector en 2 partes, y busca el elemento
            *en la parte en la que se encuentra, si el elemento es menor que el elemento
            *en la posición mid, busca en la parte izquierda, si es mayor, busca en la parte
            derecha, y así sucesivamente hasta encontrar el elemento, si no lo encuentra
            regresa la posición en la que debería de estar el elemento
            *Recibe como parámetros el vector en el que se va a buscar el elemento, los
            índices del vector en el que se va a buscar el elemento, y el elemento que se busca
        */
        int aux_busqBinaria(const vector<T> &v,int low, int high, int val){
            int mid;
            if (low <= high) {
                mid = (high + low) / 2;
                if (val == v[mid]) {
                    return mid;
                } else if (val < v[mid]) {
                    return aux_busqBinaria(v, low, mid - 1, val);
                } else if (val > v[mid]) {
                    return aux_busqBinaria(v, mid + 1, high, val);
                }
            }
            return low;

        }

    
};

#endif