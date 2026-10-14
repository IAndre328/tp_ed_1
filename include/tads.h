#ifndef TADS_H
#define TADS_H

#include "lib.h"
#include <string>
#include <iostream>

namespace tads{

    class Atributo
    {
    private:
        int id;
        std::string nome;
    public:
        Atributo();
        Atributo(std::string nome);
        Atributo(std::string nome, int id);

        int getId() const;
        const std::string& getNome() const;

        bool isEmpty();
        static void imprimirLista(lib::vetor<Atributo> &v);
    };
    
    class Item
    {
    private:
        int id;
        std::string nome;
    public:
        Item();
        Item(std::string nome);
        Item(std::string nome, int id);

        int getId() const;
        const std::string& getNome() const;

        bool isEmpty();
        static void imprimirLista(lib::vetor<Item> &v);
    };

    class Mod
    {
    private:
        int id_item;
        int id_atributo;
        int valor;
    public:
        Mod();
        Mod(int id_item, int id_atributo, int valor);

        int getIdItem() const;
        int getIdAtributo() const;
        int getValor() const;

        bool isEmpty() const;
        static void imprimirLista(lib::vetor<Mod> &v);
    };

    class Aventureiro
    {
    private:
        int id;
        std::string nome;
        lib::pilha build;
    public:
        Aventureiro();
        Aventureiro(int id, std::string nome);
    
        void equipar(int id_item);
        void desequipar();
        int ultimoEquipado() const;
        bool semItens() const;
        int qtdEquipados();

        int getId() const;
        const std::string& getNome() const;
    };

    class Encomenda
    {
    private:
        int id_av;
        int id_i;
        Encomenda* prox;
    public:
        Encomenda();
        Encomenda(int id_av, int id_i);

        void setProx(tads::Encomenda* p);

        Encomenda* getProx() const;
        int getIdAv() const;
        int getIdI() const;
    };
    
    class fila
    {
    private:
        int tamanho;
        tads::Encomenda* inicio;
        tads::Encomenda* fim;
    public:
        fila() : tamanho(0), inicio(nullptr), fim(nullptr) {}
        

        void enfileira(const tads::Encomenda& item){
            tads::Encomenda* novo = new tads::Encomenda(item.getIdAv(), item.getIdI());
            if (tamanho == 0){
                inicio = novo;
                fim = novo;
            }
            else {
                fim->setProx(novo);
            }
            fim = novo;
            tamanho++;
        }

        tads::Encomenda desenfileira(){
            if (tamanho == 0) return tads::Encomenda();

            tads::Encomenda* atual = inicio;
            tads::Encomenda removido = *atual;   // copia antes de apagar
            inicio = atual->getProx();
            delete atual;
            if (inicio == nullptr) fim = nullptr;
            tamanho--;
            return removido;
        }


        void limpa() {
            while (inicio != nullptr) {
                tads::Encomenda* atual = inicio;
                inicio = inicio->getProx();
                delete atual;
            }
            fim = nullptr;
            tamanho = 0;
        }

        int getTamanho() const { return tamanho; }
        bool isEmpty() const { return tamanho == 0; }

        ~fila() { limpa(); }
    };
    
    
 
    

}
#endif