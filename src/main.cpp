#include "main.h"
#include "lib.h"
#include "tads.h"


int main()
{
    std::string cmd;
    std::string modo;

    lib::vetor<tads::Atributo> atributos;
    lib::vetor<tads::Item> itens;

    while (std::cin >> cmd){

        if (cmd == "E") std::cin >> modo;
        if (cmd == "A"){
            std::string nome;
            std::cin >> nome;
            
            tads::Atributo temp(nome, atributos.getTamanho());
            atributos.add_no_fim(temp);

            tads::Atributo::imprimirLista(atributos);
        }
        if (cmd == "I"){
            std::string nome;
            std::cin >> nome;
            
            tads::Item temp(nome, itens.getTamanho());
            itens.add_no_fim(temp);

            tads::Item::imprimirLista(itens);
        }
        if (cmd == "M"){
           int id_Mod, id_atributo, valor;
           std::cin >> id_Mod; 
           std::cin >> id_atributo;
           std::cin >> valor;
           // guardar isso
        }
        if (cmd == "H"){
            std::string nome;
            std::cin >> nome;
            // Guardar isso
        }
        if (cmd == "F"){
            int id_aventureiro, id_Mod;
            std::cin >> id_aventureiro;
            std::cin >> id_Mod;
            // fazer algo com isso
        }
        if (cmd == "Z"){
            int turnos;
            std::cin >> turnos;
        }
        if (cmd == "D"){
            int id_aventureiro;
            std::cin >> id_aventureiro;
        }
        if (cmd == "LI"){
            int id_Mod;
            std::cin >> id_Mod;
        }
        if (cmd == "LA"){
            int id_atributo;
            std::cin >> id_atributo;
        }
        if (cmd == "LH"){
            int id_aventureiro;
            std::cin >> id_aventureiro;
        }
    }   if (cmd == "Q"){
        
    }

    /* code */
    return 0;
}
