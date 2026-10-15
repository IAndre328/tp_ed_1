#ifndef CATALOGO_H
#define CATALOGO_H

#include "tads.h"

namespace tads{

   class catalogoT
    {
    private:
        lib::vetor<Mod> celulas;
 
        // Contadores para a análise experimental
        mutable long long comparacoes;      // comparações da busca binária
        long long deslocamentos;            // elementos empurrados em inserção/remoção
        long long percorridas;              // células visitadas em percursos
 
        // Busca binária pelo par (item, atributo).
        // Devolve a primeira posição cujo par é >= ao pedido
        // (se for igual, a célula existe; senão, é o ponto de inserção).
        int posicao(int item, int atributo) const;
 
    public:
        catalogoT();
 
        // Regra do zero: valor 0 remove; célula existente é substituída; senão insere
        void definirCelula(int item, int atributo, int valor);
 
        // true se existia e foi removida
        bool removerCelula(int item, int atributo);
 
        // Valor da célula, ou 0 se não existe
        int consultarCelula(int item, int atributo) const;
 
        // Preenchem 'saida' (limpando antes) em ordem crescente e devolvem
        // quantas células foram percorridas
        int percorrerLinha(int item, lib::vetor<Mod>& saida);
        int percorrerColuna(int atributo, lib::vetor<Mod>& saida);
 
        // Usados na migração entre modos
        void entregarTodas(lib::vetor<Mod>& saida) const;
 
        int getTamanho() const;
 
        // Leitura dos contadores
        long long getComparacoes() const;
        long long getDeslocamentos() const;
        long long getPercorridas() const;
        void zerarContadores();

        void limpar();
        ~catalogoT();
    };


    struct NoCruzado {
        int id_item;
        int id_atributo;
        int valor;
        NoCruzado* proximo_linha;   // Próximo na mesma linha (mesmo item)
        NoCruzado* proximo_coluna;  // Próximo na mesma coluna (mesmo atributo)

        NoCruzado(int item, int atrib, int val)
            : id_item(item), id_atributo(atrib), valor(val),
              proximo_linha(nullptr), proximo_coluna(nullptr) {}
    };

    class catalogoL
    {
    private:
        lib::vetor<NoCruzado*> cabecas_linha;
        lib::vetor<NoCruzado*> cabecas_coluna;
    public:
        catalogoL(const std::string& modo);

        void definirCelula(const tads::Mod& mod);
        tads::Mod& consultarCelula(const tads::Mod& mod);

        void percorrerLinha();
        void percorrerColuna();

        void produtoInterno();

        void migrar();

        int getTamanho() const;

        void limpar();
        ~catalogoL() = default;
    };


    class catalogo
    {
    private:
        std::string modo;
        int tamanho;
        catalogoT T;
        catalogoL L;

    public:
        catalogo(const std::string& modo);

        void definirCelula(const tads::Mod& mod);
        tads::Mod& consultarCelula(const tads::Mod& mod);
        
        void percorrerLinha();
        void percorrerColuna();

        void produtoInterno();

        void migrar();

        int getTamanho() const;

        void limpar();
        ~catalogo() = default;
    };
    

}




#endif