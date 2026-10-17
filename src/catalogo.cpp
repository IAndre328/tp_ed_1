#include "catalogo.h"

namespace tads {
    catalogo::catalogo(const std::string& modo) :
        modo(modo) {}

    void catalogo::definirCelula(const tads::Mod& mod){
        if (modo == "T") T.definirCelula(mod.getIdItem(), mod.getIdAtributo(), mod.getValor());
        else if (modo == "L") L.definirCelula(mod.getIdItem(), mod.getIdAtributo(), mod.getValor());
        else throw "Erro, modo inesperado";
    }

    

    void catalogo::percorrerLinha(int item, lib::vetor<Mod>& saida){
        saida.limpar();

        if (modo == "T") T.percorrerLinha(item, saida);
        else if (modo == "L") L.percorrerLinha(item, saida);
        else throw "Erro, modo inesperado";

    }

    void catalogo::percorrerColuna(int atributo, lib::vetor<Mod>& saida){
        saida.limpar();

        if (modo == "T") T.percorrerColuna(atributo, saida);
        else if (modo == "L") L.percorrerColuna(atributo, saida);
        else throw "Erro, modo inesperado";

    }

    void catalogo::migrarPara(std::string newModo){
        if (newModo == modo) return;

        lib::vetor<Mod> todas;
 
        if (modo == "T") {
            T.entregarTodas(todas);
            L.receberMigracao(todas);
            T.limpar();
        }
        else if (modo == "L") {
            L.entregarTodas(todas);
            T.receberMigracao(todas);
            L.limpar();
        }
        else throw "Erro, modo inesperado";
 
        modo = newModo;
    }


    int catalogo::getTamanho() const {
        if (modo == "T") return T.getTamanho();
        else if (modo == "L") return L.getTamanho();
        else throw "Erro, modo inesperado";

    }

    void catalogo::limpar() {
        if (modo == "T") T.limpar();
        else if (modo == "L") L.limpar();
        else throw "Erro, modo inesperado";
    }
}