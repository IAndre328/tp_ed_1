#include "catalogo.h"

namespace tads {

// ---------- catalogoT ----------

catalogoT::catalogoT() : comparacoes(0), deslocamentos(0), percorridas(0) {}

int catalogoT::posicao(int item, int atributo) const {
    // TODO: busca binária em 'celulas' pelo par (item, atributo)
    //   - compara primeiro o item, depois o atributo
    //   - incrementa 'comparacoes' a cada comparação
    //   - devolve a primeira posição com par >= (item, atributo)
    (void)item; (void)atributo;
    return 0;
}

void catalogoT::definirCelula(int item, int atributo, int valor) {
    // TODO:
    //   1. pos = posicao(item, atributo); existe = (pos < tamanho e par igual)
    //   2. existe e valor != 0 -> sobrescrever o valor
    //   3. existe e valor == 0 -> remover (chamar removerCelula)
    //   4. não existe e valor != 0 -> inserir em 'pos' (empurrar os seguintes,
    //      somando em 'deslocamentos')
    //   5. não existe e valor == 0 -> nada
    (void)item; (void)atributo; (void)valor;
}

bool catalogoT::removerCelula(int item, int atributo) {
    // TODO: achar a posição; se existe, fechar o buraco empurrando os seguintes
    //       (somar em 'deslocamentos') e devolver true; senão false
    (void)item; (void)atributo;
    return false;
}

int catalogoT::consultarCelula(int item, int atributo) const {
    // TODO: pos = posicao(...); se o par existe devolve o valor, senão 0
    (void)item; (void)atributo;
    return 0;
}

int catalogoT::percorrerLinha(int item, lib::vetor<Mod>& saida) {
    // TODO:
    //   - esvaziar 'saida'
    //   - pos = posicao(item, 0); andar enquanto o item for o mesmo,
    //     copiando cada Mod para 'saida'
    //   - somar em 'percorridas' e devolver quantas foram visitadas
    (void)item; (void)saida;
    return 0;
}

int catalogoT::percorrerColuna(int atributo, lib::vetor<Mod>& saida) {
    // TODO:
    //   - esvaziar 'saida'
    //   - varrer o vetor inteiro (o ponto fraco do modo T) copiando as
    //     células com esse atributo; ficam em ordem crescente de item
    //   - somar em 'percorridas' e devolver quantas foram visitadas
    (void)atributo; (void)saida;
    return 0;
}

void catalogoT::entregarTodas(lib::vetor<Mod>& saida) const {
    // TODO: esvaziar 'saida' e copiar todas as células, na ordem em que estão
    (void)saida;
}

void catalogoT::limpar() {
    // TODO: esvaziar 'celulas'
}

int catalogoT::getTamanho() const { return celulas.getTamanho(); }

long long catalogoT::getComparacoes() const { return comparacoes; }
long long catalogoT::getDeslocamentos() const { return deslocamentos; }
long long catalogoT::getPercorridas() const { return percorridas; }

void catalogoT::zerarContadores() {
    comparacoes = 0;
    deslocamentos = 0;
    percorridas = 0;
}

// ---------- produto interno ----------

long long produtoInterno(const lib::vetor<Mod>& a, const lib::vetor<Mod>& b) {
    // TODO: intercalar as duas linhas (dois índices, i e j):
    //   - atributos iguais   -> soma valor_a * valor_b e avança os dois
    //   - atributo de a menor -> avança i
    //   - atributo de b menor -> avança j
    //   - usar long long para não estourar
    (void)a; (void)b;
    return 0;
}

}  // namespace tads