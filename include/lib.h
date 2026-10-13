#ifndef LIB_H
#define LIB_H

#include <cassert>
#include <iostream>

namespace lib{

    template <typename T>
    class vetor
    {
    private:
        T* dados;        
        int tamanho;     
        int capacidade;

        void dobrar_capacidade(){
            T* temp = new T[capacidade * 2];
            for (int i = 0; i < tamanho; i++) temp[i] = dados[i];
            delete[] dados;
            dados = temp;
            capacidade = capacidade * 2;
        }

    public:
        // começo com 4 para não ter que realocar de cara
        vetor() : dados(new T[4]), tamanho(0), capacidade(4) {} 
        ~vetor() { delete[] dados; }

        vetor(const vetor& outro)
            : dados(new T[outro.capacidade]),
            tamanho(outro.tamanho),
            capacidade(outro.capacidade) {
            for (int i = 0; i < tamanho; i++) dados[i] = outro.dados[i];
        }

        vetor& operator=(const vetor& outro) {
            if (this != &outro) {
                T* novo = new T[outro.capacidade];
                for (int i = 0; i < outro.tamanho; i++) novo[i] = outro.dados[i];
                delete[] dados;
                dados = novo;
                tamanho = outro.tamanho;
                capacidade = outro.capacidade;
            }
            return *this;
        }
        

        void add_no_fim(const T& valor){
            if (tamanho == capacidade) dobrar_capacidade();
            dados[tamanho] = valor;
            tamanho++;
            //std::cout << "inseri" << "\n";
        }

        void rem_no_fim(){
            if (!isEmpty()){
                dados[tamanho-1] = T();
                tamanho--;   
            }
            
        }


        T& getById(int id){
            assert(id >= 0 && id < tamanho);
            return dados[id];
        }

        const T& getById(int id) const {
            assert(id >= 0 && id < tamanho);
            return dados[id];
        }

        int getTamanho() const { return tamanho; }
        bool isEmpty() const {
            return (tamanho == 0 || capacidade == 0);
        }
    };
    
    class pilha
    {
    private:
        vetor<int> dados;
    public:
        pilha() : dados() {} 

        void empilhar(int valor){ dados.add_no_fim(valor); }
        void desempilhar(){ dados.rem_no_fim(); }

        bool isEmpty() const { return dados.isEmpty(); }
        int getTamanho() { return dados.getTamanho(); }

        int getTopo() const {
            if (!isEmpty()) return dados.getById(dados.getTamanho() -1);
            else return -1;
        }
    };

    
    
        


}

#endif