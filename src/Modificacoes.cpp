#include "tads.h"

tads::Mod::Mod() : id_item(-1), id_atributo(-1), valor(0) {}
tads::Mod::Mod(int id_item, int id_atributo, int valor)
    : id_item(id_item), id_atributo(id_atributo), valor(valor) {}

int tads::Mod::getIdItem() const { return id_item; }
int tads::Mod::getIdAtributo() const { return id_atributo; }
int tads::Mod::getValor() const { return valor; }

void tads::Mod::setValor(int v) { valor = v; }

bool tads::Mod::isEmpty() const { return (id_item == -1 || id_atributo == -1 || valor == 0); }

void tads::Mod::imprimirLista(lib::vetor<Mod> &v){
    for (int i = 0; i < v.getTamanho(); i++){
        const auto& t = v.getById(i);
        std::cout << "M " << t.getIdItem() << " " 
            << t.getIdAtributo() << " "
            << t.getValor() << "\n";
    }
}