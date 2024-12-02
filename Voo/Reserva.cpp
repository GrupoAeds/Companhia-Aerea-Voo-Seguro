#include "Reserva.h"
#include "Voo.h"
#include "Passageiro.h"
#include "Tripulante.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

Reserva::Reserva(int numero_assento, int codigo_voo, int codigo_passageiro){
    this->numero_assento = numero_assento;
    this->codigo_voo = codigo_voo;
    this->codigo_passageiro = codigo_passageiro;
}

void Reserva::setCodigo_voo(const int codigo_voo) {
    this->codigo_voo = codigo_voo;
}
int Reserva::getCodigo_voo() const{
    return codigo_voo;
}

void Reserva::setNumero_assento(const int numero_assento) {
    this->numero_assento = numero_assento;
}
int Reserva::getNumero_assento() const{
    return numero_assento;
}

void Reserva::setCodigo_passageiro(const int codigo_passageiro) {
    this->codigo_passageiro = codigo_passageiro;
}
int Reserva::getCodigo_passageiro() const{
    return codigo_passageiro;
}

void Reserva::imprimirReserva(const vector<Voo*>& voos, const Passageiro* passageiro) const {

    // Buscar o voo pelo código
    const Voo* vooEncontrado = nullptr;
    for (const auto* voo : voos) {
        if (voo && voo->getCodigo_voo() == codigo_voo) {
            vooEncontrado = voo;
            break;
        }
    }

    if (!vooEncontrado) {
        cout << "Erro: Voo não encontrado para o código " << codigo_voo << endl;
        return;
    }


    // Imprimir os dados da reserva
    cout << "Informações da Reserva:" << endl;
    cout << "Nome do Passageiro: " << passageiro->getNome() << endl;
    cout << "Assento: " << numero_assento << endl;
    cout << "Origem: " << vooEncontrado->getOrigem() << endl;
    cout << "Destino: " << vooEncontrado->getDestino() << endl;
    cout << "Data: " << vooEncontrado->getData().dia <<"/" << vooEncontrado->getData().mes << "/" << vooEncontrado->getData().ano << endl;
    cout << "Horas: " << vooEncontrado->getHora().horas << ":" << vooEncontrado->getHora().minutos << endl;
}

void Reserva::PesquisarPassageiro(const vector<Passageiro*>& passageiros){
    int menu;
    cout << "1-Por codigo\n2-Por nome";
    cin >> menu;
    if(menu==1){
        int codigo;
        cout << "Informe o código do passageiro: ";
        cin >> codigo;

        bool encontrado = false;
        for (const auto* passageiro : passageiros) {
            if (passageiro && passageiro->getCodigo() == codigo) {
                passageiro->imprimirInformacoes();
                encontrado = true;
                break;
            }
        }

        if (!encontrado) {
            cout << "Passageiro não encontrado com o código " << codigo << endl;
        }
    } else if(menu==2){
        // Buscar por nome
        string nome;
        cout << "Informe o nome do passageiro: ";
        cin.ignore(); // Para limpar o buffer do cin antes de pegar o nome
        getline(cin, nome);

        bool encontrado = false;
        for (const auto* passageiro : passageiros) {
            if (passageiro && passageiro->getNome() == nome) {
                passageiro->imprimirInformacoes();
                encontrado = true;
                break;
            }
        }

        if (!encontrado) {
            cout << "Passageiro não encontrado com o nome " << nome << endl;
        }
    }else{
        cout << "Opção inválida";
    }
}


void Reserva::PesquisarTripulante(const vector<Tripulante*>& tripulantes){
    int menu;
    cout << "1-Por codigo\n2-Por nome";
    cin >> menu;
    if(menu==1){
        int codigo;
        cout << "Informe o código do tripulante: ";
        cin >> codigo;

        bool encontrado = false;
        for (const auto* tripulante : tripulantes) {
            if (tripulante && tripulante->getCodigo() == codigo) {
                tripulante->imprimirInformacoes();
                encontrado = true;
                break;
            }
        }

        if (!encontrado) {
            cout << "tripulante não encontrado com o código " << codigo << endl;
        }
    } else if(menu==2){
        // Buscar por nome
        string nome;
        cout << "Informe o nome do tripulante: ";
        cin.ignore(); // Para limpar o buffer do cin antes de pegar o nome
        getline(cin, nome);

        bool encontrado = false;
        for (const auto* tripulante : tripulantes) {
            if (tripulante && tripulante->getNome() == nome) {
                tripulante->imprimirInformacoes();
                encontrado = true;
                break;
            }
        }

        if (!encontrado) {
            cout << "Tripulante não encontrado com o nome " << nome << endl;
        }
    }else{
        cout << "Opção inválida";
    }
}

void Reserva::PesquisarReservas(const vector<Passageiro*>& passageiros, vector <Voo*>& voos){
    int codigo;
    cout << "Informe o código do passageiro: ";
    cin >> codigo;

    bool encontrado = false;
    for (const auto* passageiro : passageiros) {
        if (passageiro && passageiro->getCodigo() == codigo) {
            passageiro->imprimirReservas(voos);  // Exibe as informações do passageiro
            encontrado = true;
            break;  // Se encontrou, sai do loop
        }
    }

    if (!encontrado) {
        cout << "Passageiro não encontrado com o código " << codigo << endl;
    }
}
