#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>

int menu();

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int opcao;

    opcao = menu();
    do{
        switch(opcao){
            case 0:
                break;
        }
    }while(opcao != 0);
    
}

int menu(){
    int opcao;
    printf("---------------------------------------------------\n");
    printf("                      MENU                      \n");
    printf("---------------------------------------------------\n");
    printf("(C)      Teste");
    printf("\n(C)      Teste");
    printf("\n(C)      Teste");
    printf("\n(C)      Teste");
    printf("\n\n\n");
    printf("\u2554\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2557\n");
    printf("\u2551                MENU                 \u2551\n");
    printf("\u2560\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2563\n");
    printf("\u2551  [1] Teste                          \u2551\n");
    printf("\u2551  [2] Teste                          \u2551\n");
    printf("\u2551  [3] Teste                          \u2551\n");
    printf("\u2551  [4] Teste                          \u2551\n");
    printf("\u2551  [0] Sair                           \u2551\n");
    printf("\u255A\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u255D\n");
    scanf("%d", &opcao);
   
    return opcao;
}