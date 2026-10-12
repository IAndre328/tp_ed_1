#ifndef TADS_H
#define TADS_H

#include "lib.h"
#include <string>

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

        bool isEmpty();
        static void imprimirLista(lib::vetor<Mod> &v);
    };

    class Aventureiro
    {
    private:
        int id;
        std::string nome;
    public:
        Aventureiro();
        Aventureiro(int id, std::string nome);
    
    
    };
    
 
    

}
#endif