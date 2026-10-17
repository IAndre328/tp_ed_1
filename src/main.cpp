#include "main.h"
#include "lib.h"
#include "tads.h"
#include "catalogo.h"


int main()
{
    std::string cmd;
    std::string modo;

    lib::vetor<tads::Atributo> atributos;
    lib::vetor<tads::Item> itens;
    lib::vetor<tads::Aventureiro> aventureiros;
    tads::fila forja;
    tads::catalogo catalogo("T");
    

    while (std::cin >> cmd){

        if (cmd == "E") {
            std::cin >> modo;
            std::cout << "E " << modo << "\n";

            catalogo.migrarPara(modo);
        }
        else if (cmd == "A"){
            std::string nome;
            std::cin >> nome;
            
            tads::Atributo temp(nome, atributos.getTamanho());
            atributos.add_no_fim(temp);

            std::cout << "A " << temp.getId() << "\n";
        }
        else if (cmd == "I"){
            std::string nome;
            std::cin >> nome;
            
            tads::Item temp(nome, itens.getTamanho());
            itens.add_no_fim(temp);

            std::cout << "I " << temp.getId() << "\n";
        }
        else if (cmd == "M"){
           int id_item, id_atributo, valor;
           std::cin >> id_item; 
           std::cin >> id_atributo;
           std::cin >> valor;

           tads::Mod t_mod(id_item, id_atributo, valor);

            std::cout << "M " << itens.getById(id_item).getNome() << " "
                << atributos.getById(id_atributo).getNome() << " "
                << valor << "\n";

            
            catalogo.definirCelula(t_mod);
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
        }
        else if (cmd == "Z"){
            int turnos;
            std::cin >> turnos;
            
            if (turnos > forja.getTamanho()) turnos = forja.getTamanho();
            std::cout << "Z " << turnos << "\n";

            if (turnos == 0) continue;

            for (int i = 0; i < turnos; i++){
                tads::Encomenda enc_atual = forja.desenfileira();
                tads::Aventureiro& av_atual = aventureiros.getById(enc_atual.getIdAv());
                av_atual.equipar(enc_atual.getIdI());

                if (i > 0) std::cout << " ";
                std::cout << "encomenda_" << i+1
                    << " " << enc_atual.getIdAv()
                    << " " << enc_atual.getIdI();

            }
            std::cout << "\n";
        }
        else if (cmd == "D"){
            int id_aventureiro;
            std::cin >> id_aventureiro;

            tads::Aventureiro& t_av = aventureiros.getById(id_aventureiro); 
            const std::string& t_nome = t_av.getNome();
            
            std::cout << "D " << t_nome << " ";

            if (t_av.semItens()) std::cout << "VAZIO" << "\n";
            else{
                int id_item_remov = t_av.ultimoEquipado();
                const tads::Item& item_remov = itens.getById(id_item_remov);

                std::cout << item_remov.getNome() << "\n";
                t_av.desequipar();
            }

        }
        else if (cmd == "LI"){
            int id_item;
            std::cin >> id_item;

            lib::vetor<tads::Mod> saida;
            catalogo.percorrerLinha(id_item, saida);

            std::cout << "LI " << itens.getById(id_item).getNome() << " ";

            if (saida.isEmpty()){
                std::cout << "VAZIO" << "\n";
            }
            else {
                for (int i = 0; i < saida.getTamanho() -1; i++){
                    std:: cout << "atributo_" << i+1 
                    << " " << saida.getById(i).getIdAtributo()
                    << " " << saida.getById(i).getValor()
                    << " ";
                }
                std:: cout << "atributo_" << saida.getTamanho() 
                    << " " << saida.getById(saida.getTamanho() -1).getIdAtributo()
                    << " " << saida.getById(saida.getTamanho() -1).getValor()
                    << "\n";
            }
        }
        else if (cmd == "LA"){
            int id_atributo;
            std::cin >> id_atributo;

            lib::vetor<tads::Mod> saida;
            catalogo.percorrerColuna(id_atributo, saida);

            std::cout << "LA " << atributos.getById(id_atributo).getNome() << " ";

            if (saida.isEmpty()){
                std::cout << "VAZIO" << "\n";
            }
            else {
                for (int i = 0; i < saida.getTamanho() -1; i++){
                    std:: cout << "item_" << i+1 
                    << " " << saida.getById(i).getIdItem()
                    << " " << saida.getById(i).getValor()
                    << " ";
                }
                std:: cout << "item_" << saida.getTamanho() 
                    << " " << saida.getById(saida.getTamanho() -1).getIdItem()
                    << " " << saida.getById(saida.getTamanho() -1).getValor()
                    << "\n";
            }

        }
        else if (cmd == "LH"){
            int id_aventureiro;
            std::cin >> id_aventureiro;
            const tads::Aventureiro& av_atual = aventureiros.getById(id_aventureiro);

            if (av_atual.semItens()){
                std::cout << av_atual.getNome() 
                    << " " << "VAZIO" << "\n";
            }
            else {
                tads::Aventureiro av_atual = aventureiros.getById(id_aventureiro);
                int matriz_atributo[atributos.getTamanho()] = {0};

                for (int i = 0; i < av_atual.getTamanhoBuild(); i++){
                    lib::vetor<tads::Mod> saida;
                    catalogo.percorrerLinha(av_atual.getBuildIdItem(i), saida);
                    for (int j = 0; j < saida.getTamanho(); j++){
                        matriz_atributo[saida.getById(j).getIdAtributo()] += saida.getById(j).getValor();
                    }
                }

                bool isEmpty = true;
                std::cout << "LH " << av_atual.getNome();

                for (int i = 0; i < atributos.getTamanho(); i++){
                    if (matriz_atributo[i] != 0){
                        isEmpty = false;
                        std::cout << " atributo_" << i+1 
                            << i << " " << matriz_atributo[i];
                    }
                }
                
                if (isEmpty == true) {
                    std::cout << " VAZIO";
                }
                
                std::cout << "\n";
            }


            
        }   
        else if (cmd == "Q"){
            
        }
    }

    /* code */
    return 0;
}
