#include "tads.h"

tads::Item::Item() : id(-1), nome("") {}
tads::Item::Item(std::string nome) : id(-1), nome(nome) {}
tads::Item::Item(std::string nome, int id): id(id), nome(nome) {}

int tads::Item::getId() const { return id; }
const std::string& tads::Item::getNome() const { return nome; }
bool tads::Item::isEmpty() { return (id == -1 && nome == ""); }

void tads::Item::imprimirLista(lib::vetor<Item> &v){
    for (int i = 0; i < v.getTamanho(); i++){
        auto t = v.getById(i);
        std::cout << "I " << t.getId() << "\n";
    }
}