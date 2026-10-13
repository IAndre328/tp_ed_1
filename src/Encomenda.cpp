#include "tads.h"

tads::Encomenda::Encomenda() 
    : id_av(-1), id_i(-1) , prox(nullptr) {}
tads::Encomenda::Encomenda(int id_av, int id_i)
    : id_av(id_av), id_i(id_i), prox(nullptr) {}

void tads::Encomenda::setProx(tads::Encomenda* p){
    prox = p;
}

tads::Encomenda* tads::Encomenda::getProx() { return prox; }
int tads::Encomenda::getIdAv() const { return id_av; }
int tads::Encomenda::getIdI() const { return id_i; }