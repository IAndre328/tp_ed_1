#ifndef RECOMENDACAO_H
#define RECOMENDACAO_H

#include <string>

#include "lib.h"
#include "tads.h"
#include "catalogo.h"

namespace tads {

    enum Metrica { PODER = 0, EQUILIBRIO = 1, SINERGIA = 2 };

    // Converte o peso ("3.00") em centésimos (300) sem usar ponto flutuante
    long long pesoParaCentesimos(const std::string& texto);

    // Responde às consultas Q. Mantém os vetores de trabalho entre as consultas
    // para não alocar memória a cada Q (só cresce quando N cresce).
    class recomendador
    {
    private:
        lib::vetor<long long> chaves[3];   // valor de cada métrica (x 1.000.000, arredondado) por item
        lib::vetor<long long> pontos;      // pontuação final (em centésimos) por item
        lib::vetor<int> ordem;             // ids dos itens, para ordenar
        lib::vetor<int> aux;               // vetor auxiliar da ordenação
        lib::vetor<long long> build;       // vetor da build do aventureiro (tamanho T)
        lib::vetor<char> equipado;         // 1 se o item está equipado
        lib::vetor<Mod> linha;             // linha do item que está sendo lida

        long long comparacoes;             // comparações feitas nas ordenações

        // true se o item a vem antes do item b: chave maior primeiro, empate pelo id
        bool antes(int a, int b, const lib::vetor<long long>& chave);

        // Ordena ordem[ini, fim) pela chave (merge sort)
        void ordenar(int ini, int fim, const lib::vetor<long long>& chave);

    public:
        recomendador();

        // Preenche 'ids' e 'scores' (pontuação em centésimos) com os melhores
        // itens e devolve quantos são
        int consultar(catalogo& cat, const Aventureiro& av, int N, int T, int n,
                      const lib::vetor<int>& metricas,
                      const lib::vetor<long long>& pesos,
                      lib::vetor<int>& ids,
                      lib::vetor<long long>& scores);

        long long getComparacoes() const;
        void zerarContadores();
    };
}

#endif