#include "catalogo.h"

namespace tads {

catalogoT::catalogoT() : comparacoes(0), deslocamentos(0), percorridas(0) {}

catalogoT::catalogoT(const lib::vetor<Mod>& vetor_mods) {
    celulas.limpar();

    for (int i = 0; i < vetor_mods.getTamanho(); i++) {
        Mod m = vetor_mods.getById(i);
        
        definirCelula(m.getIdItem(), m.getIdAtributo(), m.getValor());
    }
}

int catalogoT::posicao(int item, int atributo) const {
    int inicio = 0;
    int fim = celulas.getTamanho() - 1;
    int resposta = celulas.getTamanho();
    // Se não achar retorna o final

    while (inicio <= fim){
        int meio = inicio + (fim-inicio) / 2;

        comparacoes++;

        const auto& atual = celulas.getById(meio);

        if ((atual.getIdItem() > item) || 
        (atual.getIdItem() == item && atual.getIdAtributo() >= atributo)){
            resposta = meio;
            fim = meio -1;
        } else {
            inicio = meio + 1;
        }
    }
    
    return resposta;
}

void catalogoT::definirCelula(int item, int atributo, int valor) {
    int pos = posicao(item, atributo);

    bool existe = (pos < celulas.getTamanho() && 
                   celulas.getById(pos).getIdItem() == item && 
                   celulas.getById(pos).getIdAtributo() == atributo);

                
    if (valor == 0){
        if (existe == true){
            celulas.remover_da_posicao(pos);
            deslocamentos += celulas.getTamanho() - 1 - pos;
        }
    } else {
        if (existe == true){
            celulas.getById(pos).setValor(valor);
        } else{
            Mod novoMod(item, atributo, valor);
            celulas.inserir_na_posicao(pos, novoMod);
            deslocamentos += getTamanho() - pos;
        }
    }

}


int catalogoT::consultarCelula(int item, int atributo) const {
    int pos = posicao(item, atributo);
    if (pos != celulas.getTamanho()) return celulas.getById(pos).getValor();
    else return 0;
}

int catalogoT::percorrerLinha(int item, lib::vetor<Mod>& saida) {
    while (!saida.isEmpty()) saida.rem_no_fim();
    
    int t_percorridas = 0;
    int pos = posicao(item, 0);
    if (pos >= celulas.getTamanho()){
        return t_percorridas; 
    }

    while (celulas.getById(pos).getIdItem() == item){
        t_percorridas++;
        saida.add_no_fim(celulas.getById(pos));
        pos++;
    }
    
        
    percorridas += t_percorridas;
    return t_percorridas;
}

int catalogoT::percorrerColuna(int atributo, lib::vetor<Mod>& saida) {
    while (!saida.isEmpty()) saida.rem_no_fim();
    
    int t_percorridas = 0;
   
    for (int i = 0; i < celulas.getTamanho(); i++) {
        percorridas++;
        t_percorridas++;
        const auto& cel = celulas.getById(i);
        if (cel.getIdAtributo() == atributo) {
            saida.add_no_fim(cel);
        }
    }

    return t_percorridas;
}

void catalogoT::entregarTodas(lib::vetor<Mod>& saida) const {
    for (int i = 0; i < celulas.getTamanho(); i++)
        saida.add_no_fim(celulas.getById(i));
}

void catalogoT::zerarContadores() {
    comparacoes = 0;
    deslocamentos = 0;
    percorridas = 0;
}

void catalogoT::limpar() {
    celulas.limpar();
    zerarContadores();
}

catalogoT::~catalogoT(){
    limpar();
}

int catalogoT::getTamanho() const { return celulas.getTamanho(); }

long long catalogoT::getComparacoes() const { return comparacoes; }
long long catalogoT::getDeslocamentos() const { return deslocamentos; }
long long catalogoT::getPercorridas() const { return percorridas; }



long long produtoInterno(const lib::vetor<Mod>& a, const lib::vetor<Mod>& b) {
    // TODO: intercalar as duas linhas (dois índices, i e j):
    //   - atributos iguais   -> soma valor_a * valor_b e avança os dois
    //   - atributo de a menor -> avança i
    //   - atributo de b menor -> avança j
    //   - usar long long para não estourar
    (void)a; (void)b;
    return 0;
}




}