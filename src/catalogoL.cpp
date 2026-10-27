#include "catalogo.h"

namespace tads
{
    catalogoL::catalogoL() :
        tamanho(0),
        comparacoes(0),
        deslocamentos(0),
        percorridas(0) {}

    void catalogoL::receberMigracao(const lib::vetor<Mod>& vetor_mods) {
        limpar();

        for (int i = 0; i < vetor_mods.getTamanho(); i++) {
            Mod m = vetor_mods.getById(i);
            definirCelula(m.getIdItem(), m.getIdAtributo(), m.getValor());
        }
    }

    int catalogoL::consultarCelula(int item, int atributo) const {
        if (item < 0 || item >= cabecas_linha.getTamanho()) return 0;

        NoCruzado* atual = cabecas_linha.getById(item);

        while (atual != nullptr) {
            if (atual->mod.getIdAtributo() == atributo) {
                return atual->mod.getValor();
            }
            if (atual->mod.getIdAtributo() > atributo) {
                break;
            }
            atual = atual->proximo_linha;
        }
        return 0;
    }

    
    void catalogoL::acharAtual(int item, int atributo, NoCruzado*& saida) {
        saida = nullptr;
        if (item < 0 || item >= cabecas_linha.getTamanho()) return;

        NoCruzado* atual = cabecas_linha.getById(item);

        while (atual != nullptr) {
            if (atual->mod.getIdAtributo() == atributo) {
                saida = atual;
                return;
            }
            if (atual->mod.getIdAtributo() > atributo) {
                return;
            }
            atual = atual->proximo_linha;
        }
    }

    // l_ant: nó anterior na linha; c_ant: nó anterior na coluna
    // (nullptr significa "o nó fica na cabeça da lista")
    void catalogoL::acharApontadores(int item, int atributo, NoCruzado*& l_ant, NoCruzado*& c_ant) {
        l_ant = nullptr;
        c_ant = nullptr;

        if (item >= 0 && item < cabecas_linha.getTamanho()) {
            NoCruzado* anterior = nullptr;
            NoCruzado* atual = cabecas_linha.getById(item);

            while (atual != nullptr) {
                if (atual->mod.getIdAtributo() >= atributo) {
                    break;
                }
                anterior = atual;
                atual = atual->proximo_linha;
            }
            l_ant = anterior;
        }

        if (atributo >= 0 && atributo < cabecas_coluna.getTamanho()) {
            NoCruzado* anterior = nullptr;
            NoCruzado* atual = cabecas_coluna.getById(atributo);

            while (atual != nullptr) {
                if (atual->mod.getIdItem() >= item) {
                    break;
                }
                anterior = atual;
                atual = atual->proximo_coluna;
            }
            c_ant = anterior;
        }
    }

    bool catalogoL::removerCelula(int item, int atributo) {
        NoCruzado* alvo = nullptr;
        acharAtual(item, atributo, alvo);
        if (alvo == nullptr) return false;

        NoCruzado* anteriorLinha = nullptr;
        NoCruzado* anteriorColuna = nullptr;
        acharApontadores(item, atributo, anteriorLinha, anteriorColuna);

        
        if (anteriorLinha == nullptr) {
            cabecas_linha.getById(item) = alvo->proximo_linha;
        } else {
            anteriorLinha->proximo_linha = alvo->proximo_linha;
        }

        
        if (anteriorColuna == nullptr) {
            cabecas_coluna.getById(atributo) = alvo->proximo_coluna;
        } else {
            anteriorColuna->proximo_coluna = alvo->proximo_coluna;
        }

        delete alvo;
        tamanho--;
        return true;
    }

    // Só chamar quando a célula ainda NÃO existe
    void catalogoL::inserirCelula(int item, int atributo, int valor) {
        
        while (cabecas_linha.getTamanho() <= item) cabecas_linha.add_no_fim(nullptr);
        while (cabecas_coluna.getTamanho() <= atributo) cabecas_coluna.add_no_fim(nullptr);

        NoCruzado* anteriorLinha = nullptr;
        NoCruzado* anteriorColuna = nullptr;
        acharApontadores(item, atributo, anteriorLinha, anteriorColuna);

        NoCruzado* novoNo = new NoCruzado(item, atributo, valor);

        if (anteriorLinha == nullptr) {
            novoNo->proximo_linha = cabecas_linha.getById(item);
            cabecas_linha.getById(item) = novoNo;
        } else {
            novoNo->proximo_linha = anteriorLinha->proximo_linha;
            anteriorLinha->proximo_linha = novoNo;
        }

        if (anteriorColuna == nullptr) {
            novoNo->proximo_coluna = cabecas_coluna.getById(atributo);
            cabecas_coluna.getById(atributo) = novoNo;
        } else {
            novoNo->proximo_coluna = anteriorColuna->proximo_coluna;
            anteriorColuna->proximo_coluna = novoNo;
        }

        tamanho++;
    }

    void catalogoL::definirCelula(int item, int atributo, int valor) {
        if (valor == 0) {
            removerCelula(item, atributo);
            return;
        }

        NoCruzado* existente = nullptr;
        acharAtual(item, atributo, existente);

        if (existente != nullptr) {
            existente->mod.setValor(valor);
        } else {
            inserirCelula(item, atributo, valor);
        }
    }

    int catalogoL::percorrerLinha(int item, lib::vetor<Mod>& saida) {
        while (!saida.isEmpty()) saida.rem_no_fim();
        int t_percorridas = 0;

        if (item < 0 || item >= cabecas_linha.getTamanho()) return 0;

        NoCruzado* atual = cabecas_linha.getById(item);

        while (atual != nullptr) {
            saida.add_no_fim(atual->mod);
            t_percorridas++;
            percorridas++;
            atual = atual->proximo_linha;
        }
        return t_percorridas;
    }

    int catalogoL::percorrerColuna(int atributo, lib::vetor<Mod>& saida) {
        while (!saida.isEmpty()) saida.rem_no_fim();
        int t_percorridas = 0;

        if (atributo < 0 || atributo >= cabecas_coluna.getTamanho()) return 0;

        NoCruzado* atual = cabecas_coluna.getById(atributo);

        while (atual != nullptr) {
            saida.add_no_fim(atual->mod);
            t_percorridas++;
            percorridas++;
            atual = atual->proximo_coluna;
        }
        return t_percorridas;
    }

    
    void catalogoL::entregarTodas(lib::vetor<Mod>& saida) const {
        saida.limpar();

        for (int i = 0; i < cabecas_linha.getTamanho(); i++) {
            NoCruzado* atual = cabecas_linha.getById(i);

            while (atual != nullptr) {
                saida.add_no_fim(atual->mod);
                atual = atual->proximo_linha;
            }
        }
    }

    void catalogoL::zerarContadores() {
        comparacoes = 0;
        deslocamentos = 0;
        percorridas = 0;
    }

    int catalogoL::getTamanho() const { return tamanho; }

    long long catalogoL::getComparacoes() const { return comparacoes; }
    long long catalogoL::getDeslocamentos() const { return deslocamentos; }
    long long catalogoL::getPercorridas() const { return percorridas; }

    void catalogoL::limpar() {
        
        for (int i = 0; i < cabecas_linha.getTamanho(); i++) {
            NoCruzado* atual = cabecas_linha.getById(i);

            while (atual != nullptr) {
                NoCruzado* proximo = atual->proximo_linha;
                delete atual;
                atual = proximo;
            }
        }

        cabecas_linha.limpar();
        cabecas_coluna.limpar();
        tamanho = 0;

        zerarContadores();
    }

    catalogoL::~catalogoL() {
        limpar();
    }
}
