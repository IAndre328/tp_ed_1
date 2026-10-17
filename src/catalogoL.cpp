#include "catalogo.h"

namespace tads
{
    catalogoL::catalogoL() : 
        tamanho(0),
        comparacoes(0), 
        deslocamentos(0), 
        percorridas(0) {}

    catalogoL::catalogoL(const lib::vetor<Mod>& vetor_mods) {
        cabecas_coluna.limpar();
        cabecas_linha.limpar();
        tamanho = 0;

        for (int i = 0; i < vetor_mods.getTamanho(); i++) {
            Mod m = vetor_mods.getById(i); 
            definirCelula(m.getIdItem(), m.getIdAtributo(), m.getValor());
        }
    }


    int catalogoL::consultarCelula(int item, int atributo) const{
        if (cabecas_linha.isEmpty()) return 0;
        NoCruzado* atual = cabecas_linha.getById(item);

        while (atual != nullptr){
            if (atual->mod.getIdAtributo() == atributo){
                return atual->mod.getValor();
            }
            if (atual->mod.getIdAtributo() > atributo){
                break;
            }

            atual = atual->proximo_linha;
        }
        return 0;
    }

    void catalogoL::acharAtual(int item, int atributo, NoCruzado*& saida){
        saida = nullptr;
        if (cabecas_linha.isEmpty()) return;

        NoCruzado* atual = cabecas_linha.getById(item);

        while (atual != nullptr){
            if (atual->mod.getIdAtributo() == atributo){
                saida = atual;
            }
            if (atual->mod.getIdAtributo() > atributo){
                return;
            }

            atual = atual->proximo_linha;
        }
        return;
    }

    void catalogoL::acharApontadores(int item, int atributo, NoCruzado*& l_ant, NoCruzado*& c_ant) {
        l_ant = nullptr;
        c_ant = nullptr;

        
        if (item < cabecas_linha.getTamanho()) {
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

        if (atributo < cabecas_coluna.getTamanho()) {
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

    bool catalogoL::removerCelula(int item, int atributo){
        if (consultarCelula(item, atributo) == 0) return false;

        NoCruzado* anteriorLinha, *anteriorColuna, *aSerDeletado;
        acharApontadores(item, atributo, anteriorLinha, anteriorColuna);
        acharAtual(item, atributo, aSerDeletado);

        if (aSerDeletado->proximo_coluna == nullptr &&
             aSerDeletado->proximo_linha == nullptr &&
             cabecas_linha.getById(item) == aSerDeletado &&
             cabecas_coluna.getById(atributo) == aSerDeletado 
            ){
                cabecas_linha.getById(item) = nullptr;
                cabecas_coluna.getById(atributo) = nullptr;
                delete aSerDeletado;
                tamanho--;
                return true;
        } 
        if (cabecas_linha.getById(item) == aSerDeletado) {
            cabecas_linha.getById(item) = aSerDeletado->proximo_linha;
        } else {
            anteriorLinha->proximo_linha = aSerDeletado->proximo_linha;
        }

        if (cabecas_coluna.getById(atributo) == aSerDeletado) {
            cabecas_coluna.getById(atributo) = aSerDeletado->proximo_coluna;
        } else {
            anteriorColuna->proximo_coluna = aSerDeletado->proximo_coluna;
        }

        delete aSerDeletado;
        tamanho--;
        return true;
    }

    void catalogoL::inserirCelula(int item, int atributo, int valor) {
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

    void catalogoL::definirCelula(int item, int atributo, int valor){
        if (valor == 0) {
            removerCelula(item, atributo);
        }

        NoCruzado* aSerAtualizado = nullptr;
        acharAtual(item, atributo, aSerAtualizado);

        if (aSerAtualizado != nullptr) {
            aSerAtualizado->mod.setValor(valor);
        }

        inserirCelula(item, atributo, valor);
    }

    int catalogoL::percorrerLinha(int item, lib::vetor<Mod>& saida){
        saida.limpar();

        int t_percorridas = 0;

        NoCruzado* atual = cabecas_linha.getById(item);

        while (atual != nullptr){
            saida.add_no_fim(atual->mod);

            t_percorridas++;
            percorridas++;
        }
        return t_percorridas;
    }

    int catalogoL::percorrerColuna(int atributo, lib::vetor<Mod>& saida){
        saida.limpar();

        int t_percorridas = 0;

        NoCruzado* atual = cabecas_coluna.getById(atributo);

        while (atual != nullptr){
            saida.add_no_fim(atual->mod);

            t_percorridas++;
            percorridas++;
        }
        return t_percorridas;
    }

    void catalogoL::entregarTodas(lib::vetor<Mod>& saida) const{
        saida.limpar();

        for (int i = 0; i < cabecas_linha.getTamanho(); i++){
            NoCruzado* atual = cabecas_coluna.getById(i);

            while (atual != nullptr){
                saida.add_no_fim(atual->mod);
            }
        }
    }

    void catalogoL::zerarContadores(){
        comparacoes = 0;
        deslocamentos = 0;
        percorridas = 0;
    }

    int catalogoL::getTamanho() const { return tamanho; }

    long long catalogoL::getComparacoes() const { return comparacoes; }
    long long catalogoL::getDeslocamentos() const { return deslocamentos; }
    long long catalogoL::getPercorridas() const { return percorridas; }
    
    void catalogoL::limpar(){

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

        zerarContadores();

    }
    
    catalogoL::~catalogoL() {
        limpar(); 
    }
    

}
