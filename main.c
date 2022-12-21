#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <fcntl.h>
#include "include\generic.h"

int menu(void);
void menuPortateis(int*);
void menuRequisicoes(int*);
void menuAvarias(int*);
void menuDados(int*);


int main(void){
    // Configure support for UTF-16 characters
#if _WIN32
	_setmode(_fileno(stdout), _O_U16TEXT);
#endif	// _WIN32
    setlocale(LC_CTYPE, "");

    int opcao;
    
    do { 
        opcao = menu();
        switch (opcao) {
            case 0:
                break;
            case 1:
                menuPortateis(&opcao);
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
    wprintf(L"\u2554\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2557\n");
    wprintf(L"\u2551                MENU                 \u2551\n");
    wprintf(L"\u2560\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2563\n");
    wprintf(L"\u2551  [1] Portáteis                      \u2551\n");
    wprintf(L"\u2551  [2] Requisições                    \u2551\n");
    wprintf(L"\u2551  [3] Avarias                        \u2551\n");
    wprintf(L"\u2551  [4] Dados Estatísticos             \u2551\n");
    wprintf(L"\u2551  [0] Sair                           \u2551\n");
    wprintf(L"\u255A\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u255D\n");
    opcao = lerInteiro("Opcão: ", 0, 4);

    return opcao;  
}

void menuPortateis(int *op) {
    int opcao2;
    // If he chooses laptops this shows up
    wprintf(L"\u2554\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2557\n");
    wprintf(L"\u2551                Portáteis                 \u2551\n");
    wprintf(L"\u2560\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2563\n");                
    wprintf(L"\u2551  [1] Inserir Portáteis                   \u2551\n");
    wprintf(L"\u2551  [2] Listar Portáteis                    \u2551\n");
    wprintf(L"\u2551  [3] Alterar Localização do Portátil     \u2551\n");
    wprintf(L"\u2551  [0] Anterior                            \u2551\n");
    wprintf(L"\u255A\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u255D\n");
    opcao2 = lerInteiro("Opcão", 0, 3);

    switch(opcao2) {
        case 1:
            wprintf(L"\nteste\n\n");
            *op = lerInteiro("Deseja continuar no programa? Não/Sim", 0, 1);  // Asks if the user wants to coninue the program               
            break;
        case 0:
            wprintf(L"\n\nteste 0000\n");
            break;
    }
}

void menuRequisicoes(int *op) {
    int opcao2;
    wprintf(L"\u2554\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2557\n");
    wprintf(L"\u2551                 Requisições              \u2551\n");
    wprintf(L"\u2560\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2563\n");
    wprintf(L"\u2551  [1] Requisitar Portátil                 \u2551\n");
    wprintf(L"\u2551  [2] Listar Requisições                  \u2551\n");
    wprintf(L"\u2551  [3] Mostrar Requisição                  \u2551\n");
    wprintf(L"\u2551  [4] Devolução de Portátil Requisitado   \u2551\n");
    wprintf(L"\u2551  [5] Renovar Requisição                  \u2551\n");
    wprintf(L"\u2551  [0] Anterior                            \u2551\n");
    wprintf(L"\u255A\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u255D\n");
    opcao2 = lerInteiro("Opcão", 0, 5);

    switch(opcao2) {
        case 1:
            wprintf(L"\nteste\n\n");
            *op = lerInteiro("Deseja continuar no programa? Não/Sim", 0, 1);  // Asks if the user wants to coninue the program               
            break;
        case 0:
            break;
    }      
}

void menuAvarias(int *op){
    int opcao2;
    wprintf(L"\u2554\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2557\n");
    wprintf(L"\u2551                Avarias                 \u2551\n");
    wprintf(L"\u2560\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2563\n");
    wprintf(L"\u2551  [1] Registar Avaria                   \u2551\n");
    wprintf(L"\u2551  [2] Registar Reparação                \u2551\n");
    wprintf(L"\u2551  [0] Anterior                          \u2551\n");
    wprintf(L"\u255A\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u255D\n");
    opcao2 = lerInteiro("Opcão", 0, 2);

    switch(opcao2){
        case 1:
            wprintf(L"\nteste\n\n");
            *op = lerInteiro("Deseja continuar no programa? Não/Sim", 0, 1);  // Asks if the user wants to coninue the program               
            break;
        case 0:
            break;
    }
}

void menuDados(int *op){

}
