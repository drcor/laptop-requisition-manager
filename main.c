#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <fcntl.h>
#include "include/generic.h"
#include "include/laptops.h"

int menu(void);
void menuPortateis(int *opcao, typeLaptop **laptops, unsigned int *sizeLaptops);
void menuRequisicoes(int*);
void menuAvarias(int*);
void menuDados(int*);


int main(void){
	// Configure support for UTF-16 characters
#if _WIN32
	_setmode(_fileno(stdout), _O_U16TEXT);
#endif	// _WIN32
	setlocale(LC_CTYPE, "");

	unsigned int sizeLaptops = 0;
	typeLaptop *laptops = NULL;

	int opcao;
	
	do { 
		opcao = menu();
		switch (opcao) {
			case 0:
				break;
			case 1:
				menuPortateis(&opcao, &laptops, &sizeLaptops);
				break;
			case 2:
				menuRequisicoes(&opcao);
				break;
			case 3:
				menuAvarias(&opcao);
				break;
			case 4:
				menuDados(&opcao);
				break;
	   }
	} while(opcao != 0);
	
	return 0;
}

int menu(void) {
	int opcao;
			
	// This is the main menu
	wprintf(L"╔══════════════════════════════════════════╗\n");
	wprintf(L"║                   MENU                   ║\n");
	wprintf(L"╠══════════════════════════════════════════╣\n");
	wprintf(L"║  [1] Portáteis                           ║\n");
	wprintf(L"║  [2] Requisições                         ║\n");
	wprintf(L"║  [3] Avarias                             ║\n");
	wprintf(L"║  [4] Dados Estatísticos                  ║\n");
	wprintf(L"║  [0] Sair                                ║\n");
	wprintf(L"╚══════════════════════════════════════════╝\n");
	opcao = lerInteiro(L"Opcão: ", 0, 4);

	return opcao;  
}

void menuPortateis(int *op, typeLaptop **laptops, unsigned int *sizeLaptops) {
	int opcao2;
	// If he chooses laptops this shows up
	wprintf(L"╔══════════════════════════════════════════╗\n");
	wprintf(L"║                Portáteis                 ║\n");
	wprintf(L"╠══════════════════════════════════════════╣\n");                
	wprintf(L"║  [1] Inserir Portáteis                   ║\n");
	wprintf(L"║  [2] Listar Portáteis                    ║\n");
	wprintf(L"║  [3] Alterar Localização do Portátil     ║\n");
	wprintf(L"║  [0] Anterior                            ║\n");
	wprintf(L"╚══════════════════════════════════════════╝\n");
	opcao2 = lerInteiro(L"Opcão", 0, 3);

	switch(opcao2) {
		case 1:
			insert_laptop(laptops, sizeLaptops);
			break;
		case 2:
			list_laptops(*laptops, *sizeLaptops);
			break;
		case 3:
			update_laptop_location(laptops, *sizeLaptops);
			break;
		case 0:
			wprintf(L"\n\nteste 0000\n");
			break;
	}
}

void menuRequisicoes(int *op) {
	int opcao2;
	wprintf(L"╔══════════════════════════════════════════╗\n");
	wprintf(L"║               Requisições                ║\n");
	wprintf(L"╠══════════════════════════════════════════╣\n");
	wprintf(L"║  [1] Requisitar Portátil                 ║\n");
	wprintf(L"║  [2] Listar Requisições                  ║\n");
	wprintf(L"║  [3] Mostrar Requisição                  ║\n");
	wprintf(L"║  [4] Devolução de Portátil Requisitado   ║\n");
	wprintf(L"║  [5] Renovar Requisição                  ║\n");
	wprintf(L"║  [0] Anterior                            ║\n");
	wprintf(L"╚══════════════════════════════════════════╝\n");
	opcao2 = lerInteiro(L"Opcão", 0, 5);

	switch (opcao2) {
		case 1:
			wprintf(L"\nteste\n\n");
			*op = lerInteiro(L"Deseja continuar no programa? Não/Sim", 0, 1);  // Asks if the user wants to coninue the program               
			break;
		case 0:
			break;
	}      
}

void menuAvarias(int *op) {
	int opcao2;
	wprintf(L"╔══════════════════════════════════════════╗\n");
	wprintf(L"║                  Avarias                 ║\n");
	wprintf(L"╠══════════════════════════════════════════╣\n");
	wprintf(L"║  [1] Registar Avaria                     ║\n");
	wprintf(L"║  [2] Registar Reparação                  ║\n");
	wprintf(L"║  [0] Anterior                            ║\n");
	wprintf(L"╚══════════════════════════════════════════╝\n");
	opcao2 = lerInteiro(L"Opcão", 0, 2);

	switch (opcao2) {
		case 1:

			break;
		case 0:
			break;
	}
}

void menuDados(int *op) {

}
