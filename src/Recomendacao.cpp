#include <cmath>

#include "recomendacao.h"

namespace tads {

    namespace {
        template <typename T>
        void preencher(lib::vetor<T>& v, int n, const T& valor) {
            while (!v.isEmpty()) v.rem_no_fim();
            for (int i = 0; i < n; i++) v.add_no_fim(valor);
        }

        void esvaziar(lib::vetor<int>& v) {
            while (!v.isEmpty()) v.rem_no_fim();
        }

        void esvaziar(lib::vetor<long long>& v) {
            while (!v.isEmpty()) v.rem_no_fim();
        }
    }

    long long pesoParaCentesimos(const std::string& texto) {
        long long inteiro = 0;
        long long fracao = 0;
        int casas = 0;
        bool depoisDoPonto = false;

        for (std::size_t i = 0; i < texto.size(); i++) {
            char c = texto[i];
            if (c == '.') { depoisDoPonto = true; continue; }
            if (c < '0' || c > '9') continue;

            if (!depoisDoPonto) inteiro = inteiro * 10 + (c - '0');
            else if (casas < 2) { fracao = fracao * 10 + (c - '0'); casas++; }
        }
        while (casas < 2) { fracao *= 10; casas++; }

        return inteiro * 100 + fracao;
    }

    recomendador::recomendador() : comparacoes(0) {}

    bool recomendador::antes(int a, int b, const lib::vetor<long long>& chave) {
        comparacoes++;
        long long ka = chave.getById(a);
        long long kb = chave.getById(b);

        if (ka != kb) return ka > kb;   // maior primeiro
        return a < b;                   // empate: menor id primeiro
    }

    void recomendador::ordenar(int ini, int fim, const lib::vetor<long long>& chave) {
        if (fim - ini < 2) return;

        int meio = ini + (fim - ini) / 2;
        ordenar(ini, meio, chave);
        ordenar(meio, fim, chave);

        int i = ini, j = meio, k = ini;
        while (i < meio && j < fim) {
            if (antes(ordem.getById(j), ordem.getById(i), chave)) aux.getById(k++) = ordem.getById(j++);
            else aux.getById(k++) = ordem.getById(i++);
        }
        while (i < meio) aux.getById(k++) = ordem.getById(i++);
        while (j < fim) aux.getById(k++) = ordem.getById(j++);

        for (int p = ini; p < fim; p++) ordem.getById(p) = aux.getById(p);
    }

    int recomendador::consultar(catalogo& cat, const Aventureiro& av, int N, int T, int n,
                                const lib::vetor<int>& metricas,
                                const lib::vetor<long long>& pesos,
                                lib::vetor<int>& ids,
                                lib::vetor<long long>& scores) {
        esvaziar(ids);
        esvaziar(scores);

        
        for (int m = 0; m < 3; m++) preencher(chaves[m], N, 0LL);
        preencher(pontos, N, 0LL);
        preencher(ordem, N, 0);
        preencher(aux, N, 0);
        preencher(equipado, N, (char)0);
        preencher(build, T, 0LL);

        
        for (int b = 0; b < av.getTamanhoBuild(); b++) {
            int item = av.getBuildIdItem(b);
            equipado.getById(item) = 1;

            cat.percorrerLinha(item, linha);
            for (int j = 0; j < linha.getTamanho(); j++) {
                build.getById(linha.getById(j).getIdAtributo()) += linha.getById(j).getValor();
            }
        }

        long long somaQuadBuild = 0;
        for (int a = 0; a < T; a++) somaQuadBuild += build.getById(a) * build.getById(a);
        double normaBuild = std::sqrt((double)somaQuadBuild);

        for (int i = 0; i < N; i++) {
            cat.percorrerLinha(i, linha);

            long long soma = 0, somaQuad = 0, produto = 0;
            for (int j = 0; j < linha.getTamanho(); j++) {
                long long v = linha.getById(j).getValor();
                soma += v;
                somaQuad += v * v;
                produto += v * build.getById(linha.getById(j).getIdAtributo());
            }

            // PODER (inteiro, exato)
            chaves[PODER].getById(i) = soma * 1000000LL;

            // EQUILIBRIO: desvio populacional sobre os T atributos (zeros incluídos).
            // T * somaQuad - soma^2 = T^2 * variância, calculado só com inteiros
            double valorEquilibrio = 1.0;
            if (T > 0) {
                long long t2var = (long long)T * somaQuad - soma * soma;
                if (t2var < 0) t2var = 0;
                double sigma = std::sqrt((double)t2var) / T;
                valorEquilibrio = 1.0 / (1.0 + sigma);
            }
            chaves[EQUILIBRIO].getById(i) = std::llround(valorEquilibrio * 1000000.0);

            // SINERGIA: cosseno entre a linha do item e a build
            double normaItem = std::sqrt((double)somaQuad);
            double valorSinergia = 0.0;
            if (normaItem > 0.0 && normaBuild > 0.0) {
                valorSinergia = (double)produto / (normaItem * normaBuild);
            }
            chaves[SINERGIA].getById(i) = std::llround(valorSinergia * 1000000.0);
        }

        
        for (int p = 0; p < metricas.getTamanho(); p++) {
            const lib::vetor<long long>& chave = chaves[metricas.getById(p)];
            long long peso = pesos.getById(p);

            for (int i = 0; i < N; i++) ordem.getById(i) = i;
            ordenar(0, N, chave);

            for (int pos = 0; pos < N; pos++) {
                pontos.getById(ordem.getById(pos)) += (long long)(N - pos) * peso;
            }
        }

        
        esvaziar(ordem);
        for (int i = 0; i < N; i++) {
            if (equipado.getById(i) == 0) ordem.add_no_fim(i);
        }
        int candidatos = ordem.getTamanho();
        ordenar(0, candidatos, pontos);

        int k = (n < candidatos) ? n : candidatos;
        for (int p = 0; p < k; p++) {
            int item = ordem.getById(p);
            ids.add_no_fim(item);
            scores.add_no_fim(pontos.getById(item));
        }
        return k;
    }

    long long recomendador::getComparacoes() const { return comparacoes; }
    void recomendador::zerarContadores() { comparacoes = 0; }
}