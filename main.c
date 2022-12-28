#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <fcntl.h>
#include "include\generic.h"
#include "include/laptops.h"
#include "include/breakdowns.h"

int menu(void);
void menuPortateis(int *opcao, typeLaptop **laptops, unsigned int *sizeLaptops);
void menuRequisicoes(int*);
void menuAvarias(int *op, typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops);
void menuDados(int*);
void registaAvaria(typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops);
void listaAvarias(typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops);

int main(void){
	// Configure support for UTF-16 characters
#if _WIN32
	_setmode(_fileno(stdout), _O_U16TEXT);
#endif	// _WIN32
	setlocale(LC_CTYPE, "");

	unsigned int sizeLaptops = 0;
	typeLaptop *laptops = NULL;
	unsigned int sizeBreakdowns = 0;
	typeBreakdown *breakdowns = NULL;

	int opcao;
	
	// Apresenta o menu principal de opções
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
				menuAvarias(&opcao, &breakdowns, &sizeBreakdowns, laptops, sizeLaptops);
				break;
			case 4:
				menuDados(&opcao);
				break;
			default:
				wprintf(L"ATENÇÃO: Insira uma opção válida\n");
				break;
	   }
	} while(opcao != 0);
	
	return 0;
}

// Mostra o menu principal e retorna uma opção
int menu(void) {
	int opcao;
			
	wprintf(L"╔══════════════════════════════════════════╗\n");
	wprintf(L"║                   MENU                   ║\n");
	wprintf(L"╠══════════════════════════════════════════╣\n");
	wprintf(L"║  [1] Portáteis                           ║\n");
	wprintf(L"║  [2] Requisições                         ║\n");
	wprintf(L"║  [3] Avarias                             ║\n");
	wprintf(L"║  [4] Dados Estatísticos                  ║\n");
	wprintf(L"║  [0] Sair                                ║\n");
	wprintf(L"╚══════════════════════════════════════════╝\n");
	opcao = lerInteiro(L"Opcão", 0, 4);

	return opcao;  
}

// Mostra o menu de opções dos portáteis
void menuPortateis(int *op, typeLaptop **laptops, unsigned int *sizeLaptops) {
	int opcao2;
	
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
	}
}

// Mostra o menu de opções das requisições
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

	switch(opcao2) {
		case 1:
			wprintf(L"\nteste\n\n");
			*op = lerInteiro(L"Deseja continuar no programa? Não/Sim", 0, 1);  // Asks if the user wants to coninue the program               
			break;
		}
}

// Mostra o menu de opções das avarias
void menuAvarias(int *op, typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops) {
	int opcao2;

	wprintf(L"╔══════════════════════════════════════════╗\n");
	wprintf(L"║                  Avarias                 ║\n");
	wprintf(L"╠══════════════════════════════════════════╣\n");
	wprintf(L"║  [1] Registar Avaria                     ║\n");
	wprintf(L"║  [2] Registar Reparação                  ║\n");
	wprintf(L"║  [3] Listar Avarias                      ║\n");
	wprintf(L"║  [0] Anterior                            ║\n");
	wprintf(L"╚══════════════════════════════════════════╝\n");
	
	opcao2 = lerInteiro(L"Opcão", 0, 3);

	switch(opcao2){
		case 1:
			registaAvaria(breakdowns, numberBreakdowns, laptops, numberLaptops);
			break;
		case 3:
			listaAvarias(*breakdowns, *numberBreakdowns, laptops, numberLaptops);
			break;
	}
}

// Mostra o menu de opções das estatísticas
void menuDados(int *op) {

}

/**
 * @brief Regista uma Avaria
 * 
 * @param breakdowns 
 * @param numberBreakdowns 
 * @param laptops 
 * @param numberLaptops 
 */
void registaAvaria(typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops) {
	int pos, control, id;
	// Check if exist laptops and breakdowns
	if (breakdowns != NULL && numberBreakdowns > 0 && laptops != NULL && numberLaptops > 0) {
		// Read id
		do {
			id = lerInteiro(L"Insira o ID do portátil avariado", 1, MAX_LAPTOPS);
			pos = search_laptop_id(laptops, numberLaptops, id);	// TODO: search_breakdown_id()
			if (pos == -1) {
				wprintf(L"ATENÇÃO: Tem de inserir um ID existente\n");
			}
		} while (pos == -1);

		control = insert_breakdown(breakdowns, numberBreakdowns, id);
		if (control == 0) {
			laptops[pos].state = BROKEN;
		}
	}
} 

/**
 * @brief Mostra os dados do portátil e das avarias juntos
 * 
 * @param breakdowns 
 * @param numberBreakdowns 
 * @param laptops 
 * @param numberLaptops 
 */
void listaAvarias(typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops) {
	int pos;
	// Check if exist laptops and breakdowns
	if (breakdowns != NULL && numberBreakdowns > 0) {
		wprintf(L"ID\tCPU\tMem.\tEstado\tLocal\tMulta\tTipo\tDuração\tData\t\tDescrição\n");

		for (unsigned int i = 0; i < numberBreakdowns; i++) {	// Get breakdow by breakdown
			// Get position of laptop in vector of laptops
			pos = search_laptop_id(laptops, numberLaptops, breakdowns[i].laptop_id);
			wprintf(L"%d\ti%d\t%dGB\t", laptops[pos].id, laptops[pos].cpu, laptops[pos].memory);
			wprintf(L"%d\t%d\t", laptops[pos].state, laptops[pos].location);
			wprintf(L"%.2f\t%d\t", laptops[pos].price, breakdowns[i].break_type);
			wprintf(L"%d\t", breakdowns[i].duration);
			print_date(breakdowns[i].date);
			wprintf(L"\t%s\n", breakdowns[i].duration, laptops[pos].description);
		}
	} else {
		wprintf(L"ATENÇÃO: Não existe nenhuma avaria registada!\n");
	}
}