//============================================================================
// Name        : main.cpp
// Author      : Pedro Costa Calazans
// Version     :
// Copyright   : Your copyright notice
//============================================================================

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdbool.h>

#define MAX 2

#ifdef WIN
	#define CLEAR system("cls");
	#define PAUSE system("pause");
#else
	#ifdef NIX
		#define CLEAR cout << "\x1b[2J"; cout << "\x1b[1;1H";
		#define PAUSE system("read a");
	#else
		#error Especificar -DWIN ou -DNIX na compilação
	#endif
#endif

using namespace std;

/**---------------
 * Classe 'Pessoa'
 * ---------------
 */
class Pessoa {
protected:
	string nome;

	int diaNascimento,
		mesNascimento;

public:
	// Construtor default
	Pessoa() {
		nome = "";
		diaNascimento = 0;
		mesNascimento = 0;
	}

	// Construtor parametrizado
	Pessoa(string _nome, int _diaNascimento, int _mesNascimento) {
		nome = _nome;
		diaNascimento = _diaNascimento;
		mesNascimento = _mesNascimento;
	}

	// Destrutor
	~Pessoa() {}

	/**------------------------------
	 * Gets e Sets da classe 'Pessoa'
	 * ------------------------------
	 */
	string getNome() {
		return nome;
	}

	int getDia() {
		return diaNascimento;
	}

	int getMes() {
		return mesNascimento;
	}

	void setNome(string _nome) {
		nome = _nome;
	}

	void setDia(int _diaNascimento) {
		diaNascimento = _diaNascimento;
	}

	void setMes(int _mesNascimento) {
		mesNascimento = _mesNascimento;
	}

	bool aniversarianteMes(int _mes) {
		if(mesNascimento == _mes) {
			return true;
		}
		return false;
	}

	/**----------------
	 * Métodos virtuais
	 * ----------------
	 */
	virtual void le() {}

	virtual void escreve() {
		cout << "\n\t==================== Resultado da pesquisa ========================" << endl;
		cout << "\tNome: " << nome << endl;
		cout << "\tDia do Nascimento: " << diaNascimento << endl;
		cout << "\tMês do nascimento: " << mesNascimento << "\n";
		cout << "\t===================================================================" << endl;
	}
};

/**----------------
 * Classe 'Cliente'
 * ----------------
 */
class Cliente : public Pessoa {
private:
	double limiteCredito;

public:
	// Variável estática qtde de instâncias da classe 'Cliente'
	static int quantidade;

	// Construtor default
	Cliente() : Pessoa() {
		limiteCredito = 0.0;
	}

	// Construtor parametrizado
	Cliente(string _nome, int _diaNascimento, int _mesNascimento, double _limiteCredito) : Pessoa(_nome, _diaNascimento, _mesNascimento) {
		limiteCredito = _limiteCredito;
	}

	// Destrutor
	~Cliente() {}

	/**-------------------------------
	 * Gets e Sets da classe 'Cliente'
	 * -------------------------------
	 */

	double getLimite() {
		return limiteCredito;
	}

	void setLimite(double _limiteCredito) {
		limiteCredito = _limiteCredito;
	}

	void le() {
		cout << "\n\t==================== Dados Cliente ========================" << endl;
		cout << "\n\tNome: ";
		cin.ignore();
		getline( cin, nome );

		cout << "\tDia do nascimento: "; cin >> diaNascimento;

		if ( diaNascimento < 1 || diaNascimento > 31 ) {
			diaNascimento = 0;
		}

		cout << "\tMes do nascimento: "; cin >> mesNascimento;

		if ( mesNascimento < 1 || mesNascimento > 12 ) {
			mesNascimento = 0;
		}

		cout << "\tLimite de crédito: "; cin >> limiteCredito;
		this->quantidade++;
	}

	void escreve(int i) {
		cout << "\n\t"
			 << i
			 << " -> "
			 << nome
			 << " -> "
			 << "Limite de crédito: "
			 << limiteCredito
			 << endl;
	}

	bool creditoAprovado(double valorCompra) {
		if(valorCompra <= limiteCredito) {
			return true;
		}
		return false;
	}

	/**----------------------------------
	 * Método estático da classe 'Cliente'
	 * ----------------------------------
	 */
	static int total() {
		return quantidade;
	}

};

/**--------------------
 * Classe 'Funcionario'
 * --------------------
 */
class Funcionario : public Pessoa {
private:
	double salarioBruto;

public:
	// Variável estática qtde de instâncias da classe 'Funcionario'
	static int quantidade;

	// Construtor default
	Funcionario() : Pessoa() {
		salarioBruto = 0.0;
	}

	// Construtor parametrizado
	Funcionario(string _nome, int _diaNascimento, int _mesNascimento, double _salarioBruto) : Pessoa(_nome, _diaNascimento, _mesNascimento) {
		salarioBruto = _salarioBruto;
	}

	// Destrutor
	~Funcionario() {}

	/**-----------------------------------
	 * Gets e Sets da classe 'Funcionario'
	 * -----------------------------------
	 */
	void setSalarioBruto(double _salarioBruto) {
		salarioBruto = _salarioBruto;
	}

	double getSalarioBruto() {
		return salarioBruto;
	}

	void le() {
		cout << "\n\t==================== Dados Funcionário ========================" << endl;
		cout << "\n\tNome: ";
		cin.ignore();
		getline( cin, nome );

		cout << "\tDia do nascimento: "; cin >> diaNascimento;

		if (diaNascimento < 1 || diaNascimento > 31) {
			diaNascimento = 0;
		}

		cout << "\tMes do nascimento: "; cin >> mesNascimento;

		if (mesNascimento < 1 || mesNascimento > 12) {
			mesNascimento = 0;
		}

		cout << "\tSalário bruto: "; cin >> salarioBruto;

		this->quantidade++;
	}

	void escreve(int i) {
		cout << "\n\t"
			 << i
			 << " -> "
			 << nome
			 << " -> "
			 << "Salário bruto: "
			 << salarioBruto
			 << endl;
	}

	double salarioLiquido(int percentual = 8) {
		return salarioBruto - (salarioBruto * (1/(double) percentual));
	}

	/**---------------------------------------
	 * Método estático da classe 'Funcionario'
	 * ---------------------------------------
	 */
	static int total() {
		return quantidade;
	}

};

/**---------------------------------------------------------------------
 * Variáveis estáticas das classes acima colocadas aqui no escopo global
 * ---------------------------------------------------------------------
 */
int Cliente::quantidade = 0;
int Funcionario::quantidade = 0;

/**--------------
 * Menu de opções
 * --------------
 */
int opcao() {
	int resposta = 3;
	do {
		CLEAR
		cout << "\n\t============================= Menu ===============================" << endl;
		cout << "\t[0] - Sair do programa" << "\n\n";
		cout << "\t============================ Pessoa ==============================" << endl;
		cout << "\t[1] - Listar todas as pessoas" << endl;
		cout << "\t[2] - Pesquisar por aniversariante do mês" << "\n\n";
		cout << "\t============================ Cliente =============================" << endl;
		cout << "\t[3] - Cadastrar" << endl;
		cout << "\t[4] - Consultar aprovação" << endl;
		cout << "\t[5] - Listar todos os clientes" << "\n\n";
		cout << "\t========================== Funcionário ===========================" << endl;
		cout << "\t[6] - Cadastrar" << endl;
		cout << "\t[7] - Calcular salário" << endl;
		cout << "\t[8] - Listar todos os funcionários" << "\n\n";
		cout << "\n\tOpção: "; cin >> resposta;
	} while ( resposta < 0 || resposta > 8 );

	return resposta;
}

/**-------------
 * Função 'main'
 * -------------
 */
int main(int argc, char **argv)
{
	int mes,
		percentual,
		opc,
		contCli = 0,
		contFun = 0,
		nCli = -1,
		nFun = -1;

	bool flag = false;

	double 	valorCompra = 0.0;

	string nome;

	// Definindo vector para Lista de pessoas
	vector<Pessoa> listaPessoas;

	Cliente cli[MAX];
	Funcionario fun[MAX];

	do {

		opc = opcao();

		switch ( opc ) {

		case 1: // Listar pessoas
			CLEAR

			cout << "\n\t============================= Pessoas cadatradas ===============================" << "\n\n";

			for (int i = 0; i < (contCli + contFun); i++) {
				listaPessoas[i].escreve();
				cout << "\t----------------------------------------------------------------------------" << endl;
			}

			PAUSE

			break;

		case 2: // Pesquisar por aniversariantes do mês
			CLEAR

			cout << "\n\tInforme o mês: "; cin >> mes;

			if(mes > 0 && mes < 13) {
				for(int i = 0; i < (contCli+contFun); i++) {
					if(listaPessoas[i].aniversarianteMes(mes)) {
						listaPessoas[i].escreve();
						flag = true;
					}
				}

			} else {
				cout << "\n\n\tMês incorreto!" << endl;
			}

			if(flag == false) {
				cout << "\nNão há aniversariantes para mês perguntado!" << endl;
			}

			flag = false;

			PAUSE

			break;

		case 3: // Cadastrar cliente
			CLEAR

			try {
				if (contCli >= MAX) throw "Foi excedido o limite de armazenamento de clientes!";

				cout << "\n\n";

				cli[contCli].le();

				listaPessoas.push_back(cli[contCli]);

				contCli++;

			} catch (const char* e){
				cerr << "\nErro: " << e << endl;
				PAUSE
			}

			break;

		case 4: // Consultar aprovação de crédito
			CLEAR

			cout << "\n\tInforme nº que identifica o cliente: "; cin >> nCli;

			cout << "\n\tInforme valor da compra: "; cin >> valorCompra;

			if(contCli != 0 && nCli != -1 && nCli < MAX) {
				if(cli[nCli].creditoAprovado(valorCompra)) {
					cout << "\n\tCrédito aprovado!\n\n";
				} else {
					cout << "\n\tCrédito NÃO aprovado!\n\n";
				}
			} else {
				cout << "\n\tNº que identifica cliente NÃO existe!" << endl;
			}

			PAUSE

			break;

		case 5: // Listar todos os clientes
			CLEAR

			cout << "\n\t============================= Clientes cadatrados ===============================" << "\n\n";

			for (int i = 0; i < contCli; i++) {
				cli[i].escreve(i);
				cout << "\t----------------------------------------------------------------------------" << endl;
			}

			PAUSE

			break;

		case 6: // Cadastrar funcionário
			CLEAR

			try {
				if(contFun >= MAX) throw "Foi excedido o limite de armazenamento de funcionários!";

				cout << "\n\n";

				fun[contFun].le();

				listaPessoas.push_back(fun[contFun]);

				contFun++;

			} catch (const char* e) {
				cerr << "\nErro: " << e << endl;
			}

			break;

		case 7: // Calcular salário
			CLEAR

			cout << "\n\tInforme nº que identifica o funcionário: "; cin >> nFun;

			cout << "\n\tInforme percentual do INSS ou 0 p/ 8%: "; cin >> percentual;

			if(contFun != 0 && nFun != -1 && nFun < MAX) {
				if(percentual != 0) {
					cout << "\n\tSalário líquido: " << fun[nFun].salarioLiquido(percentual) << "\n\n";
				} else {
					cout << "\n\tSalário líquido: " << fun[nFun].salarioLiquido() << "\n\n";
				}
			}

			break;

		case 8: // Listar todos os funcionários
			CLEAR

			cout << "\n\t============================= Funcionários cadatrados ===============================" << "\n\n";

			for (int i = 0; i < contFun; i++) {
				fun[i].escreve(i);
				cout << "\t----------------------------------------------------------------------------" << endl;
			}

			PAUSE

			break;

		case 0: // Sair
			CLEAR

			cout << "\n\tObrigado por utilizar o programa!" << endl;

			break;
		}

	} while( opc != 0 && contCli <= MAX && contFun <= MAX);

	cout << "\n\tQtde de instâncias da classe \'Cliente\': " << Cliente::total() << "\n\n";
	cout << "\n\tQtde de instâncias da classe \'Funcionario\': " << Funcionario::total() << "\n\n";

	return 0;
}
