#include "tads.h"

tads::Aventureiro::Aventureiro() : id(-1), nome("nome") {}
tads::Aventureiro::Aventureiro(int id, std::string nome) : id(id), nome(nome) {}

void tads::Aventureiro::equipar(int id_item)   { build.empilhar(id_item); }
int tads::Aventureiro::ultimoEquipado() const { 
    if (!build.isEmpty()) return build.getTopo();
    else return -1;
 }
void tads::Aventureiro::desequipar() { build.desempilhar(); }
bool tads::Aventureiro::semItens() const { return build.isEmpty(); }
int tads::Aventureiro::qtdEquipados() { return build.getTamanho(); }

int tads::Aventureiro::getId() const { return id; }
const std::string& tads::Aventureiro::getNome() const { return nome; }