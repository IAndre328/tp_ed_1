#include "tads.h"

tads::Atributo::Atributo() : id(-1), nome("") {}
tads::Atributo::Atributo(std::string nome) : id(-1), nome(nome) {}
tads::Atributo::Atributo(std::string nome, int id): id(id), nome(nome) {}

int tads::Atributo::getId() const { return id; }
const std::string& tads::Atributo::getNome() const { return nome; }
bool tads::Atributo::isEmpty() { return (id == -1 && nome == ""); }

void tads::Atributo::imprimirLista(lib::vetor<Atributo> &v){
    for (int i = 0; i < v.getTamanho(); i++){
        const auto& t = v.getById(i);
        std::cout << "A " << t.getId() << "\n";
    }
}