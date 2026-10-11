#include "tads.h"

tads::Mod::Mod() : id_item(-1), id_atributo(-1), nome("") {}
tads::Mod::Mod(std::string nome) : id_item(-1), id_atributo(-1), nome(nome) {}
tads::Mod::Mod(std::string nome, int id_item, int id_atributo)
    : id_item(id_item), id_atributo(id_atributo), nome(nome) {}

int tads::Mod::getIdItem() const { return id_item; }
int tads::Mod::getIdAtributo() const { return id_atributo; }
const std::string& tads::Mod::getNome() const { return nome; }


bool tads::Mod::isEmpty() { return (id_item == -1 || id_atributo == -1 || nome == ""); }

void tads::Mod::imprimirLista(lib::vetor<Mod> &v){
    for (int i = 0; i < v.getTamanho(); i++){
        auto t = v.getById(i);
        std::cout << "M " << t.getIdItem() << " " << t.getIdAtributo() << "\n";
    }
}