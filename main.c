#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>

int menu();
int lerInteiro (char msg[], int limMin, int limMax);
void limparBuffer(void);

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
    
    return 0;
}

int menu(){
    int opcao, opcao2;
    
        do{
            printf("\u2554\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2557\n");
            printf("\u2551                MENU                 \u2551\n");
            printf("\u2560\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2563\n");
            printf("\u2551  [1] Portáteis                      \u2551\n");
            printf("\u2551  [2] Requisições                    \u2551\n");
            printf("\u2551  [3] Avarias                        \u2551\n");
            printf("\u2551  [4] Dados Estatísticos             \u2551\n");
            printf("\u2551  [0] Sair                           \u2551\n");
            printf("\u255A\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u255D\n");
            opcao = lerInteiro("Opcão: ", 0, 4);

        
            switch(opcao){
                case 1:
                    printf("\u2554\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2557\n");
                    printf("\u2551                Portáteis                 \u2551\n");
                    printf("\u2560\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2563\n");
                    printf("\u2551  [1] Inserir Portáteis                   \u2551\n");
                    printf("\u2551  [2] Listar Portáteis                    \u2551\n");
                    printf("\u2551  [3] Alterar Localização do Portátil     \u2551\n");
                    printf("\u2551  [0] Anterior                            \u2551\n");
                    printf("\u255A\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u255D\n");
                    opcao2 = lerInteiro("Opcão", 0, 3);
                    switch(opcao2){
                        case 0:
                            break;
                    }
                    break;
                case 2:
                    printf("\u2554\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2557\n");
                    printf("\u2551                 Requisições               \u2551\n");
                    printf("\u2560\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2563\n");
                    printf("\u2551  [1] Requisitar Portátil                   \u2551\n");
                    printf("\u2551  [2] Listar Requisições                    \u2551\n");
                    printf("\u2551  [3] Mostrar Requisição                    \u2551\n");
                    printf("\u2551  [4] Devolução de Portátil Requisitado     \u2551\n");
                    printf("\u2551  [5] Renovar Requisição                    \u2551\n");
                    printf("\u2551  [0] Anterior                            \u2551\n");
                    printf("\u255A\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u255D\n");
                    opcao2 = lerInteiro("Opcão", 0, 5);
                    switch(opcao2){
                        case 0:
                            break;
                    }
                    break;
                case 3:
                    printf("\u2554\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2557\n");
                    printf("\u2551                Avarias                 \u2551\n");
                    printf("\u2560\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2563\n");
                    printf("\u2551  [1] Registar Avaria                   \u2551\n");
                    printf("\u2551  [2] Registar Reparação                \u2551\n");
                    printf("\u2551  [0] Anterior                          \u2551\n");
                    printf("\u255A\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u255D\n");
                    opcao2 = lerInteiro("Opcão", 0, 2);
                    switch(opcao2){
                        case 0:
                            break;
                    }
                    break;
                    case 0:
                        break;
            }
        }while(opcao != 0);



    
    
    
   
    return opcao;
}


int lerInteiro (char msg[], int limMin, int limMax)
{
    int num, controlo;

    do
    {
        printf("%s [%d, %d]: ", msg, limMin, limMax);
        controlo = scanf("%d", &num);
        limparBuffer();

        if (controlo != 1) // significa que não fez atribuição à variável num
        {
            printf("ERRO: O valor inserido não é numérico!\n");
        }
        else
        {
            if (num < limMin || num > limMax)
            {
                printf("ERRO: O número nao pertence ao intervalo!\n");
            }
        }
    }
    while (controlo != 1 || num < limMin || num > limMax);

    return num;
}


void limparBuffer(void)
{
    char letra;

    do
    {
        letra = getchar();
    }
    while (letra != '\n' && letra != EOF);
}