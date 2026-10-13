#include "main.h"
#include "lib.h"
#include "tads.h"


int main()
{
    std::string cmd;
    std::string modo;

    lib::vetor<tads::Atributo> atributos;
    lib::vetor<tads::Item> itens;
    lib::vetor<tads::Aventureiro> aventureiros;
    tads::fila forja;

    lib::vetor<tads::Mod> mods;

    while (std::cin >> cmd){

        if (cmd == "E") std::cin >> modo;
        else if (cmd == "A"){
            std::string nome;
            std::cin >> nome;
            
            tads::Atributo temp(nome, atributos.getTamanho());
            atributos.add_no_fim(temp);

            std::cout << "A " << temp.getId() << "\n";
            //tads::Atributo::imprimirLista(atributos);
        }
        else if (cmd == "I"){
            std::string nome;
            std::cin >> nome;
            
            tads::Item temp(nome, itens.getTamanho());
            itens.add_no_fim(temp);

            std::cout << "I " << temp.getId() << "\n";
            //tads::Item::imprimirLista(itens);
        }
        else if (cmd == "M"){
           int id_item, id_atributo, valor;
           std::cin >> id_item; 
           std::cin >> id_atributo;
           std::cin >> valor;

           if (valor != 0){
                tads::Mod t_m(id_item, id_atributo, valor);

           }
           // guardar isso
        }
        else if (cmd == "H"){
            std::string nome;
            std::cin >> nome;
            
            tads::Aventureiro temp(aventureiros.getTamanho(), nome);
            aventureiros.add_no_fim(temp);

            std::cout << "H " << temp.getId() << "\n";
        }
        else if (cmd == "F"){
            int id_aventureiro, id_item;
            std::cin >> id_aventureiro;
            std::cin >> id_item;

            tads::Encomenda enc(id_aventureiro, id_item);
            forja.enfileira(enc);
            std::cout << "F " << forja.getTamanho() << "\n";
            // fazer algo com isso
        }
        else if (cmd == "Z"){
            int turnos;
            std::cin >> turnos;
        }
        else if (cmd == "D"){
            int id_aventureiro;
            std::cin >> id_aventureiro;

            tads::Aventureiro& t_av = aventureiros.getById(id_aventureiro); 
            const std::string& t_nome = t_av.getNome();
            

            std::cout << "D ";

            if (!t_av.semItens()){
                const std::string& i_nome = itens.getById(t_av.ultimoEquipado()).getNome();
                std::cout << i_nome << "\n";
            }
            else std::cout << "VAZIO" << "\n";

            t_av.desequipar();
        }
        else if (cmd == "LI"){
            int id_Mod;
            std::cin >> id_Mod;
        }
        else if (cmd == "LA"){
            int id_atributo;
            std::cin >> id_atributo;
        }
        else if (cmd == "LH"){
            int id_aventureiro;
            std::cin >> id_aventureiro;
        }   
        else if (cmd == "Q"){
            
        }
    }

    /* code */
    return 0;
}
