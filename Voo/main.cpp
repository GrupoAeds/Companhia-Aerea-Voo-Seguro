#include "Pessoa.h"
#include "Passageiro.h"
#include "Tripulante.h"
#include "Assento.h"
#include "Voo.h"
#include "Reserva.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

int main() {
    vector<Passageiro> passageiros = Passageiro::carregarPassageiros("passageiros.txt");
    vector<Tripulante> tripulantes = Tripulante::carregarTripulantes("tripulantes.txt");;
    vector<Voo> voos = Voo::carregarVoo("voos.txt");
    int escolha = 0;

    while (true) {
        cout << "Seja bem-vindo a Companhia Aérea Voo Seguro. O que deseja?\n\n"
            << "1 - Cadastrar Passageiro\n"
            << "2 - Cadastrar Tripulação\n"
            << "3 - Cadastrar Voos\n"
            << "4 - Cadastrar Assentos\n"
            << "5 - Realizar uma reserva\n"
            << "6 - Realizar a baixa de uma reserva\n"
            << "7 - Pesquisar\n"
            << "8 - Sair\n";

        cin >> escolha;

        cin.ignore();

        if (cin.fail()) {
            cin.clear(); // Limpa o erro de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora o restante da linha
            cout << "Entrada inválida. Tente novamente.\n";
            continue;
        }

        switch (escolha) {
            case 1: {
                Passageiro Individuo = Passageiro::cadastrarNovaPessoa();
                Individuo.imprimirInformacoes();
                passageiros.push_back(Individuo);
                break;
            }

            case 2: {
                Tripulante novoTripulante = Tripulante::cadastrarNovaPessoa();
                novoTripulante.imprimirInformacoes();
                tripulantes.push_back(novoTripulante);
                break;
            }

            case 3: {
                Voo novoVoo = Voo::cadastrarVoo(tripulantes);
                novoVoo.exibirInformacoes();
                voos.push_back(novoVoo);
                break;
            }

            case 4: {
                // Criando um vetor de ponteiros para os voos
                vector<Voo*> voosPtr;
                for (auto& voo : voos) {
                    voosPtr.push_back(&voo); // Adiciona o endereço de cada voo
                }

                // Passando o vetor de ponteiros para cadastrarAssento
                Assento novoAssento = Assento::cadastrarAssento(voosPtr);
                novoAssento.exibirInformacoes();
                break;
            }

            case 5: {
                int codigo_passageiro;
                cout << "Informe o código do passageiro para realizar a reserva: ";
                cin >> codigo_passageiro;

                // Busca o passageiro pelo código
                auto passageiroIt = find_if(passageiros.begin(), passageiros.end(), [codigo_passageiro](const Passageiro& passageiro) {
                    return passageiro.getCodigo() == codigo_passageiro;
                });

                if (passageiroIt != passageiros.end()) {
                    passageiroIt->reservar(voos);
                } else {
                    cout << "Passageiro não encontrado.\n";
                }
                break;
            }

            case 6: {
                int codigo_passageiro;
                cout << "Informe o código do passageiro para realizar a baixa da reserva: ";
                cin >> codigo_passageiro;

                // Busca o passageiro pelo código
                auto passageiroIt = find_if(passageiros.begin(), passageiros.end(), [codigo_passageiro](const Passageiro& passageiro) {
                    return passageiro.getCodigo() == codigo_passageiro;
                });

                if (passageiroIt != passageiros.end()) {
                    passageiroIt->baixarReserva(voos);
                } else {
                    cout << "Passageiro não encontrado.\n";
                }
                break;
            }

            case 7: {
                int menu;
                cout << "1 - Passageiro\n"
                    << "2 - Tripulante\n"
                    << "3 - Reservas\n";
                cin >> menu;
                switch (menu) {
                    case 1: {
                        vector<Passageiro*> passageirosPtr;
                        for (auto& passageiro : passageiros) {
                            passageirosPtr.push_back(&passageiro); // Adiciona o ponteiro de cada Passageiro ao vetor
                        }

                        // Debug: Verificar tamanho do vetor antes de chamar a função
                        cout << "Pesquisando Passageiros: " << passageirosPtr.size() << " passageiros encontrados.\n";

                        // Agora, passe o vetor de ponteiros para a função
                        Reserva::PesquisarPassageiro(passageirosPtr);
                        break;
                    }

                    case 2: {
                        vector<Tripulante*> tripulantesPtr;
                        for (auto& tripulante : tripulantes) {
                            tripulantesPtr.push_back(&tripulante); // Adiciona o ponteiro de cada Tripulante
                        }

                        // Debug: Verificar tamanho do vetor antes de chamar a função
                        cout << "Pesquisando Tripulantes: " << tripulantesPtr.size() << " tripulantes encontrados.\n";

                        // Agora, passe o vetor de ponteiros para a função
                        Reserva::PesquisarTripulante(tripulantesPtr);
                        break;
                    }

                    case 3: {
                        vector<Passageiro*> passageirosPtr;
                        for (auto& passageiro : passageiros) {
                            passageirosPtr.push_back(&passageiro); // Adiciona o ponteiro de cada Passageiro ao vetor
                        }

                        vector<Voo*> voosPtr;
                        for (auto& voo : voos) {
                            voosPtr.push_back(&voo);
                        }

                        // Debug: Verificar tamanho do vetor antes de chamar a função
                        cout << "Pesquisando Reservas: " << passageirosPtr.size() << " passageiros e " << voosPtr.size() << " voos encontrados.\n";

                        // Agora, passe o vetor de ponteiros para a função
                        Reserva::PesquisarReservas(passageirosPtr, voosPtr);
                        break;
                    }

                    default:
                        break;
                }
                break;
            }

            case 8: {
                Tripulante::salvarTripulantes(tripulantes, "tripulantes.txt");
                Passageiro::salvarPassageiros(passageiros,"passageiros.txt");
                Voo::salvarVoo(voos, "voos.txt");
                cout << "Bye Bye!";
                return 0;
            }

            default: {
                cout << "Opção inválida\n";
                break;
            }
        }
    }

    return 1;
}
