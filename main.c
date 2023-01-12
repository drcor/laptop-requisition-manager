#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <limits.h>
#include "include/generic.h"
#include "include/laptops.h"
#include "include/breakdowns.h"
#include "include/requests.h"

/* Initialize and save the vectors data in binary files */
void initialize_data(typeLaptop **laptops, unsigned int *numberLaptops, typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeRequest **requests, unsigned int *numberRequests);
void save_data(typeLaptop *laptops, unsigned int numberLaptops, typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeRequest *requests, unsigned int numberRequests);
void save_request_to_log(typeRequest *requests, unsigned int numberRequests, typeLaptop *laptops, unsigned int numberLaptops, int pos);
/* Options menus */
int menu(typeRequest *requests, unsigned int numberRequests, typeLaptop *laptops, unsigned int numberLaptops);
void menu_laptops(typeLaptop **laptops, unsigned int *numberLaptops, typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeRequest *requests, unsigned int numberRequests);
void menu_requests(typeRequest **requests, unsigned int *numberRequests, typeLaptop *laptops, unsigned int numberLaptops);
void menu_breakdowns(typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops);
void menu_statistics(typeLaptop *laptops, unsigned int numberLaptops, typeRequest *requests, unsigned int numberRequests);
/* Declaration of menus functionalities */
void register_breakdown(typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops);
void register_repair(typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops);
void register_devolution(typeRequest *requests, unsigned int numberRequests, typeLaptop *laptops, unsigned int numberLaptops);
void register_request(typeRequest **requests, unsigned int *numberRequests, typeLaptop *laptops, unsigned int numberLaptops);
void renovate_request(typeRequest *requests, unsigned int numberRequests);
void list_breakdowns(typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops);
void list_laptops(typeLaptop *laptops, unsigned int numberLaptops, typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeRequest *requests, unsigned int numberRequests);
void list_one_request(typeRequest *requests, unsigned int numberRequests, typeLaptop *laptops, unsigned int numberLaptops);

int main(void)
{
    unsigned int numberLaptops = 0;
    unsigned int numberBreakdowns = 0;
    unsigned int numberRequests = 0;
    typeLaptop *laptops = NULL;
    typeBreakdown *breakdowns = NULL;
    typeRequest *requests = NULL;
    int opcao;

    // Set locale for Portuguese
    setlocale(LC_ALL, "Portuguese");

    // Initialize vectors with data
    initialize_data(&laptops, &numberLaptops, &breakdowns, &numberBreakdowns, &requests, &numberRequests);

    // Show main menu
    do
    {
        opcao = menu(requests, numberRequests, laptops, numberLaptops);
        switch (opcao)
        {
        case 0:
            break;
        case 1:
            menu_laptops(&laptops, &numberLaptops, breakdowns, numberBreakdowns, requests, numberRequests);
            break;
        case 2:
            menu_requests(&requests, &numberRequests, laptops, numberLaptops);
            break;
        case 3:
            menu_breakdowns(&breakdowns, &numberBreakdowns, laptops, numberLaptops);
            break;
        case 4:
            menu_statistics(laptops, numberLaptops, requests, numberRequests);
            break;
        default:
            printf("\nATENCAO: Insira uma opcao valida\n");
            break;
        }
    }
    while(opcao != 0);

    save_data(laptops, numberLaptops, breakdowns, numberBreakdowns, requests, numberRequests);

    free(laptops);
    free(breakdowns);
    free(requests);

    return 0;
}

/**
 * @brief Initialize vectors from the binary files data
 * 
 * @param laptops 
 * @param numberLaptops 
 * @param breakdowns 
 * @param numberBreakdowns 
 * @param requests 
 * @param numberRequests 
 */
void initialize_data(typeLaptop **laptops, unsigned int *numberLaptops, typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeRequest **requests, unsigned int *numberRequests)
{
    // Initialize vector with data from files
    FILE *laptopsFile;
    FILE *breakdownsFile;
    FILE *requestsFile;
    // Open data files
    laptopsFile = fopen("laptops.bin", "rb");
    breakdownsFile = fopen("breakdowns.bin", "rb");
    requestsFile = fopen("requests.bin", "rb");
    // Read data
    if (laptopsFile != NULL)
    {
        if (read_laptop_from_file(laptops, numberLaptops, laptopsFile) == -1)
        {
            printf("ERRO: Falha a importar laptops\n");
        }
        fclose(laptopsFile);
    }
    if (breakdownsFile != NULL)
    {
        if (read_breakdown_from_file(breakdowns, numberBreakdowns, breakdownsFile) == -1)
        {
            printf("ERRO: Falha a importar avarias\n");
        }
        fclose(breakdownsFile);
    }
    if (requestsFile != NULL)
    {
        if (read_request_from_file(requests, numberRequests, requestsFile) == -1)
        {
            printf("ERRO: Falha a importar requisicoes\n");
        }
        fclose(requestsFile);
    }
}

/**
 * @brief Save vectors to binary files
 * 
 * @param laptops 
 * @param numberLaptops 
 * @param breakdowns 
 * @param numberBreakdowns 
 * @param requests 
 * @param numberRequests 
 */
void save_data(typeLaptop *laptops, unsigned int numberLaptops, typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeRequest *requests, unsigned int numberRequests)
{
    // Save vector data to files
    FILE *laptopsFile;
    FILE *breakdownsFile;
    FILE *requestsFile;
    // Open data files
    laptopsFile = fopen("laptops.bin", "wb");
    breakdownsFile = fopen("breakdowns.bin", "wb");
    requestsFile = fopen("requests.bin", "wb");
    // Read data
    write_laptop_to_file(laptops, numberLaptops, laptopsFile);
    write_breakdown_to_file(breakdowns, numberBreakdowns, breakdownsFile);
    write_request_to_file(requests, numberRequests, requestsFile);
    // Close files
    fclose(laptopsFile);
    fclose(breakdownsFile);
    fclose(requestsFile);
}

/**
 * @brief Save a request to a log file
 *
 * @param requests
 * @param numberRequests
 * @param laptops
 * @param numberLaptops
 */
void save_request_to_log(typeRequest *requests, unsigned int numberRequests, typeLaptop *laptops, unsigned int numberLaptops, int pos)
{
    FILE *logFile;
    int laptopPos;

    if (requests != NULL && numberRequests > 0 && laptops != NULL && numberLaptops > 0)
    {
        logFile = fopen("requests.log", "a");
        if (logFile != NULL)
        {
            // Print devolution date
            fprintf(logFile, "%02d/%02d/%04d\t", requests[pos].devolution_date.day, requests[pos].devolution_date.month, requests[pos].devolution_date.year);
            fprintf(logFile, "Codigo:%s\t IDportatil:%d\t", requests[pos].code, requests[pos].laptop_id);
            // Print type of user
            fprintf(logFile, "TipoCliente:");
            switch (requests[pos].user_type)
            {
            case STUDENT:
                fprintf(logFile, "Estudante             \t");
                break;
            case TEACHER:
                fprintf(logFile, "Docente               \t");
                break;
            case ADMNISTRATIVE:
                fprintf(logFile, "Tecnico Administrativo\t");
            }

            fprintf(logFile, "Prazo:%2d\t", requests[pos].deadline);
            fprintf(logFile, "Estado:Concluido\t");
            fprintf(logFile, "DataRequisicao:%02d/%02d/%04d\t", requests[pos].requisition_date.day, requests[pos].requisition_date.month, requests[pos].requisition_date.year);

            fprintf(logFile, "Local de devolucao:");
            switch (requests[pos].devolution_local)
            {
            case NONE:
                fprintf(logFile, "----\t");
                break;
            case RESIDENCES:
                fprintf(logFile, "Residencias\t");
                break;
            case CAMPUS1:
                fprintf(logFile, "Campus 1   \t");
                break;
            case CAMPUS2:
                fprintf(logFile, "Campus 2   \t");
                break;
            case CAMPUS5:
                fprintf(logFile, "Campus 5   \t");
                break;
            }
            fprintf(logFile, "Multa:%5.2f\t", requests[pos].price);
            // Print laptop data
            laptopPos = search_laptop_id(laptops, numberLaptops, requests[pos].laptop_id);
            fprintf(logFile, "Processador:i%d\t", laptops[laptopPos].cpu);
            fprintf(logFile, "MemoriaRAM:%dGB\t", laptops[laptopPos].memory);
            fprintf(logFile, "NomeUtilizador:%s\t\n", requests[pos].user_name);

            fclose(logFile);
        }

    }
}

/**
 * @brief Show main menu
 * 
 * @param requests 
 * @param numberRequests 
 * @param laptops 
 * @param numberLaptops 
 * @return int 
 */
int menu(typeRequest *requests, unsigned int numberRequests, typeLaptop *laptops, unsigned int numberLaptops)
{
    int opcao, activeRequests, availableLaptops;

    availableLaptops = count_laptops_availale(laptops, numberLaptops);
    activeRequests = count_requests_active(requests, numberRequests);

    printf("\n +----------------------------------------------------+\n");
    printf(" |                        MENU                        |\n");
    printf(" +----------------------------------------------------+\n");
    printf(" | N. portateis:   %3d  N. portateis disponiveis: %3d |\n", numberLaptops, availableLaptops);
    printf(" | N. requisicoes: %3d  N. requisicoes ativas:    %3d |\n", numberRequests, activeRequests);
    printf(" +----------------------------------------------------+\n");
    printf(" |  [1] Portateis                                     |\n");
    printf(" |  [2] Requisicoes                                   |\n");
    printf(" |  [3] Avarias                                       |\n");
    printf(" |  [4] Dados Estatisticos                            |\n");
    printf(" |  [0] Sair                                          |\n");
    printf(" +----------------------------------------------------+\n");
    opcao = read_integer("Opcao: ", 0, 4);

    return opcao;
}

/**
 * @brief Show laptops menu
 * 
 * @param laptops 
 * @param numberLaptops 
 * @param breakdowns 
 * @param numberBreakdowns 
 * @param requests 
 * @param numberRequests 
 */
void menu_laptops(typeLaptop **laptops, unsigned int *numberLaptops, typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeRequest *requests, unsigned int numberRequests)
{
    int opcao2;
    printf("\n +------------------------------------------+\n");
    printf(" |                Portateis                 |\n");
    printf(" +------------------------------------------+\n");
    printf(" |  [1] Inserir Portateis                   |\n");
    printf(" |  [2] Listar Portateis                    |\n");
    printf(" |  [3] Alterar localizacao do Portatil     |\n");
    printf(" |  [0] Anterior                            |\n");
    printf(" +------------------------------------------+\n");
    opcao2 = read_integer("Opcao", 0, 3);

    switch(opcao2)
    {
    case 1:
        printf("\nRegistar Portatil:\n");
        insert_laptop(laptops, numberLaptops);
        break;
    case 2:
        printf("\nLista de Portateis:\n");
        list_laptops(*laptops, *numberLaptops, breakdowns, numberBreakdowns, requests, numberRequests);
        printf("\n");
        break;
    case 3:
        printf("\nAtualizar localizacao:\n");
        update_laptop_location(*laptops, *numberLaptops);
        break;
    }
}

/**
 * @brief Show requests menu
 * 
 * @param requests 
 * @param numberRequests 
 * @param laptops 
 * @param numberLaptops 
 */
void menu_requests(typeRequest **requests, unsigned int *numberRequests, typeLaptop *laptops, unsigned int numberLaptops)
{
    int opcao2;

    printf("\n +------------------------------------------+\n");
    printf(" |               Requisicoes                |\n");
    printf(" +------------------------------------------+\n");
    printf(" |  [1] Requisitar portatil                 |\n");
    printf(" |  [2] Listar Requisicoes                  |\n");
    printf(" |  [3] Mostrar uma Requisicao              |\n");
    printf(" |  [4] Renovar Requisicao                  |\n");
    printf(" |  [5] Devolucao de portatil Requisitado   |\n");
    printf(" |  [0] Anterior                            |\n");
    printf(" +------------------------------------------+\n");
    opcao2 = read_integer("Opcao", 0, 5);

    switch (opcao2)
    {
    case 1:
        printf("\nRegistar Requisicao:\n");
        register_request(requests, numberRequests, laptops, numberLaptops);
        break;
    case 2:
        printf("\nLista de requisicoes:\n");
        list_request(*requests, *numberRequests);
        break;
    case 3:
        printf("\nMostrar informacoes de uma requisicao:\n");
        list_one_request(*requests, *numberRequests, laptops, numberLaptops);
        break;
    case 4:
        printf("\nRenovar Requisicao:\n");
        renovate_request(*requests, *numberRequests);
        break;
    case 5:
        printf("\nRegistar Devolucao:\n");
        register_devolution(*requests, *numberRequests, laptops, numberLaptops);
        break;
    }
}

/**
 * @brief Show breakdowns menu
 * 
 * @param breakdowns 
 * @param numberBreakdowns 
 * @param laptops 
 * @param numberLaptops 
 */
void menu_breakdowns(typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops)
{
    int opcao2;
    printf("\n +------------------------------------------+\n");
    printf(" |                  Avarias                 |\n");
    printf(" +------------------------------------------+\n");
    printf(" |  [1] Registar Avaria                     |\n");
    printf(" |  [2] Registar Reparacao                  |\n");
    printf(" |  [3] Listar Avarias                      |\n");
    printf(" |  [0] Anterior                            |\n");
    printf(" +------------------------------------------+\n");
    opcao2 = read_integer("Opcao", 0, 3);

    switch (opcao2)
    {
    case 1:
        printf("\nRegistar Avaria:\n");
        register_breakdown(breakdowns, numberBreakdowns, laptops, numberLaptops);
        break;
    case 2:
        printf("\nRegistar Reparacao:\n");
        register_repair(*breakdowns, *numberBreakdowns, laptops, numberLaptops);
        break;
    case 3:
        printf("\nLista de Avarias:\n");
        list_breakdowns(*breakdowns, *numberBreakdowns, laptops, numberLaptops);
        break;
    }
}

/**
 * @brief Show the statistics data
 * 
 * @param laptops 
 * @param numberLaptops 
 * @param requests 
 * @param numberRequests 
 */
void menu_statistics(typeLaptop *laptops, unsigned int numberLaptops, typeRequest *requests, unsigned int numberRequests)
{
    float medCoast=0, perI3=0, perI5=0, perI7=0;
    unsigned int pos, counter=0, numStudents=0, numTeachers=0, numAdministratives=0, min;
    typeDate maxDate = {0,0,0};
    typeDate zeroDate = {0,0,0};

    printf("\nDados estatisticos:\n");
    // - [ ]  percentagem de portateis com cada tipo de processador
    for (pos = 0; pos < numberLaptops; pos++)
    {
        switch (laptops[pos].cpu)
        {
        case I3:
            perI3++;
            break;
        case I5:
            perI5++;
            break;
        case I7:
            perI7++;
            break;
        }
    }

    perI3 = perI3 * 100 / numberLaptops;
    perI5 = perI5 * 100 / numberLaptops;
    perI7 = perI7 * 100 / numberLaptops;
    printf(" Percentagem de CPUs em portateis:\n\tI3=%3.1f%%   I5=%3.1f%%   I7=%3.1f%%\n", perI3, perI5, perI7);

    // Calculate medium coast of payed fines
    for (pos = 0; pos < numberRequests; pos++)
    {
        if (requests[pos].price > 0.0)  	// sum only if bigger than 0
        {
            medCoast += requests[pos].price;
            counter++;
        }
    }
    medCoast = (float)medCoast / counter;
    printf("\n Custo medio de multas pagas: %.2f $\n", medCoast);

    // Type of users with smaller number of requests
    for (pos = 0; pos < numberRequests; pos++)
    {
        switch (requests[pos].user_type)
        {
        case STUDENT:
            numStudents++;
            break;
        case TEACHER:
            numTeachers++;
            break;
        case ADMNISTRATIVE:
            numAdministratives++;
            break;
        }
        // Calculate most recent date
        if (compare_date(maxDate, requests[pos].devolution_date) == 1 && requests[pos].requisition_state == DONE)  	// if devolution_date is more recent than maxDate
        {
            maxDate = requests[pos].devolution_date;
        }
    }
    min = numStudents;
    if (min > numTeachers)
    {
        min = numTeachers;
    }
    else
    {
        if (min > numAdministratives)
        {
            min = numAdministratives;
        }
    }

    printf("\n Tipo(s) de utente(s) com a menor quantidade de requisicoes efetuadas:\n");
    if (min == numStudents)
    {
        printf("  - Alunos\n");
    }
    if (min == numTeachers)
    {
        printf("  - Docentes\n");
    }
    if (min == numAdministratives)
    {
        printf("  - Tecnicos Administrativos\n");
    }

    // Print most recent dates equal to maxDate
    if (compare_date(maxDate, zeroDate) == -1)   // if exists devolutions
    {
        printf("\n As devolucoes mais recentes tem o codigo:\n");
        for (pos = 0; pos < numberRequests; pos++)
        {
            if (compare_date(maxDate, requests[pos].devolution_date) == 0)
            {
                printf("  - %s\n", requests[pos].code);
            }
        }
    }
    else
    {
        printf("\n Ainda nao existem devolucoes registadas\n");
    }

}


/**
 * @brief Register a new breakdown
 *
 * @param breakdowns
 * @param numberBreakdowns
 * @param laptops
 * @param numberLaptops
 */
void register_breakdown(typeBreakdown **breakdowns, unsigned int *numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops)
{
    int pos, control, id;
    typeDate date;
    // Check if exist laptops and breakdowns
    if (breakdowns != NULL && laptops != NULL && numberLaptops > 0)
    {
        // Read id
        do
        {
            id = read_integer("Insira o ID do portatil avariado", 1, MAX_LAPTOPS);
            pos = search_laptop_id(laptops, numberLaptops, id);
            if (pos == -1 || laptops[pos].state != AVAILABLE)  	// if laptop ID dont exist or is not available
            {
                printf("ATENCAO: Insira o ID de um laptop existente e disponivel\n");
            }
        }
        while (pos == -1 || laptops[pos].state != AVAILABLE);	// while laptop ID dont exist or is not available

        // Get request date
        do
        {
            read_date("Insira a data de avaria", &(date));

            control = compare_date(laptops[pos].date, date);

            if (control == -1)  	// if date is smaller than laptop date
            {
                printf("\nATENCAO: A data tem de ser igual ou superior a data de aquisicao do portatil\n");
            }
        }
        while (control == -1);	// while date is smaller than laptop date

        control = insert_breakdown(breakdowns, numberBreakdowns, id, date);
        if (control == 0)
        {
            laptops[pos].state = BROKEN;
            printf("Registo de avaria concluido com sucesso\n");
        }
        else
        {
            printf("ERRO: Falha a registar a avaria\n");
        }

    }
    else
    {
        printf("ATENCAO: Nao existe nenhum avaria registada!\n");
    }
}

/**
 * @brief Register a repair
 *
 * @param breakdowns
 * @param numberBreakdowns
 * @param laptops
 * @param numberLaptops
 */
void register_repair(typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops)
{
    int pos, control, id;
    // Check if exist breakdowns and laptops
    if (breakdowns != NULL && numberBreakdowns > 0 && laptops != NULL && numberLaptops > 0)
    {
        // Get breakdown id
        do
        {
            id = read_integer("Insira o ID da avaria", 1, INT_MAX);
            pos = search_breakdown_id(breakdowns, numberBreakdowns, id);
            if (pos == -1)
            {
                printf("\nATENCAO: Tem de inserir um ID existente\n");
            }
            if (breakdowns[pos].duration != 0)
            {
                printf("ATENCAO: Insira o ID de uma avaria ainda nao reparada\n");
            }
        }
        while (pos == -1 || breakdowns[pos].duration != 0);

        // Set laptop available for requisition and set duration of reparation
        breakdowns[pos].duration = read_integer("Insira a duracao da reparacao", 1, 90);
        control = search_laptop_id(laptops, numberLaptops, breakdowns[pos].laptop_id);
        laptops[control].state = AVAILABLE;

        printf("Registo de reparacao concluido com sucesso\n");
    }
    else
    {
        printf("ATENCAO: Nao existe nenhuma avaria registada!\n");
    }
}

/**
 * @brief Register a new request
 * 
 * @param requests 
 * @param numberRequests 
 * @param laptops 
 * @param numberLaptops 
 */
void register_request(typeRequest **requests, unsigned int *numberRequests, typeLaptop *laptops, unsigned int numberLaptops)
{
    int control, laptopId, pos;
    typeDate requisitionDate;
    // Check if exists requests and laptops
    if (requests != NULL && laptops != NULL && numberLaptops > 0)
    {
        do
        {
            laptopId = read_integer("Insira o id do laptop que deseja requisitar:", 1, MAX_LAPTOPS);
            pos = search_laptop_id(laptops, numberLaptops, laptopId);

            if (pos == -1 || laptops[pos].state != AVAILABLE)
            {
                printf("\nATENCAO: Insira o ID de um laptop existente e disponivel\n");
            }
        }
        while (pos == -1 || laptops[pos].state != AVAILABLE);

        // Get request date
        do
        {
            read_date("Insira a data de requisicao", &(requisitionDate));

            control = compare_date(laptops[pos].date, requisitionDate);

            if (control == -1)  	// if date is smaller than laptop date
            {
                printf("\nATENCAO: A data tem de ser igual ou superior a data de aquisicao do portatil\n");
            }
        }
        while (control == -1);	// while date is smaller than laptop date

        control = insert_request(requests, numberRequests, laptopId, requisitionDate);
        if (control == 0)
        {
            // Set laptop state to taken
            laptops[pos].state = TAKEN;
            printf("Registo de requisicao concluido com sucesso\n");
        }
        else
        {
            printf("ERRO: Falha a registar o a requisicao\n");
        }
    }
}

/**
 * @brief Register a laptop devolution
 * 
 * @param requests 
 * @param numberRequests 
 * @param laptops 
 * @param numberLaptops 
 */
void register_devolution(typeRequest *requests, unsigned int numberRequests, typeLaptop *laptops, unsigned int numberLaptops)
{
    char code[CODE_SIZE];
    int pos, control, tmp, holdedDays;
    typeDate devolutionDate;
    enum typeLocal devolutionLocal;

    // Check if exist breakdowns
    if (requests != NULL && numberRequests > 0)
    {
        do  	// Get request code
        {
            read_string("Insira o codigo da requisicao", code, CODE_SIZE-1);
            pos = search_request_by_code(requests, numberRequests, code);
            if (pos == -1)
            {
                printf("ATENCAO: Tem de inserir o codigo de uma requisicao existente\n");
            }
            if (requests[pos].requisition_state == DONE)
            {
                printf("ATENCAO: Insira o codigo de uma requisicao ainda nao concluida\n");
            }
        }
        while (pos == -1 || requests[pos].requisition_state == DONE);

        do  	// Read devolution date
        {
            read_date("Insira a data de devolucao do portatil", &devolutionDate);
            control = compare_date(requests[pos].requisition_date, devolutionDate);
            if (control == -1)  	// if devolutionDate is smaller than requisition_date
            {
                printf("ATENCAO: Insira uma data igual ou superior a data de requisicao\n");
            }
        }
        while (control == -1);	// while devolutionDate is smaller than requisition_date
        requests[pos].devolution_date = devolutionDate;

        do  	// Read location of devolution
        {
            tmp = read_integer("Insira a localizacao do portatil\n\t0 - Residencias\n\t1 - Campus 1\n\t2 - Campus 2\n\t5 - Campus 5\n", 0, 5);
            control = set_typeLocal(&devolutionLocal, tmp);

            if (control != 0)  	// If not valid
            {
                printf("\nATENCAO: Insira uma localizacao valida\n");
            }
        }
        while (control != 0);
        requests[pos].devolution_local = devolutionLocal;

        // Calculate fine
        holdedDays = diff_date(requests[pos].requisition_date, devolutionDate);
        tmp = holdedDays - requests[pos].deadline;
        if (tmp >= 0)
        {
            requests[pos].price = tmp * 10;
            printf("\nMULTA: %.2f $\n", requests[pos].price);
        }

        // Set request as done
        requests[pos].requisition_state = DONE;

        // Set laptop available
        control = search_laptop_id(laptops, numberLaptops, requests[pos].laptop_id);
        laptops[control].state = AVAILABLE;
        // Set new laptop location
        laptops[control].location = devolutionLocal;

        save_request_to_log(requests, numberRequests, laptops, numberLaptops, pos);

        printf("Registo de devolucao concluido com sucesso\n");
    }
    else
    {
        printf("ATENCAO: Nao existe nenhuma requisicao registada!\n");
    }
}

/**
 * @brief Renovate a request
 *
 * @param requests
 * @param numberRequests
 */
void renovate_request(typeRequest *requests, unsigned int numberRequests)
{
    char code[CODE_SIZE];
    int pos;
    // Check if exist requests
    if (requests != NULL && numberRequests > 0)
    {
        do  	// Get request code
        {
            read_string("Insira o codigo da requisicao", code, CODE_SIZE-1);
            pos = search_request_by_code(requests, numberRequests, code);
            if (pos == -1)
            {
                printf("ATENCAO: Tem de inserir o codigo de uma requisicao existente\n");
            }
            if (requests[pos].requisition_state == DONE)
            {
                printf("ATENCAO: Insira o codigo de uma requisicao ainda nao concluida\n");
            }
        }
        while (pos == -1 || requests[pos].requisition_state == DONE);

        // Add 7 days to deadline
        requests[pos].deadline += 7;

        printf("Renovacao da requisicao concluida com sucesso\n");
    }
    else
    {
        printf("ATENCAO: Nao existe nenhuma requisicao registada!\n");
    }
}

/**
 * @brief Show breakdowns data
 *
 * @param breakdowns
 * @param numberBreakdowns
 * @param laptops
 * @param numberLaptops
 */
void list_breakdowns(typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeLaptop *laptops, unsigned int numberLaptops)
{
    unsigned int pos, laptopPos;
    // Check if exist laptops and breakdowns
    if (breakdowns != NULL && numberBreakdowns > 0)  	// If exist breakdowns then have to exist at least a laptop
    {
        printf("ID\tTipo avaria\tData avaria\tDurac.\tLID\tCPU\tMemor.\tEstado\t\tLocalizacao\tPreco\t\tDescricao\n");

        for (pos = 0; pos < numberBreakdowns; pos++)  	// Get breakdow by breakdown
        {
            // Get position of laptop in vector of laptops
            laptopPos = search_laptop_id(laptops, numberLaptops, breakdowns[pos].laptop_id);
            // Print breakdown data
            printf("%d\t", breakdowns[pos].id);
            print_typeBreak(breakdowns[pos].break_type);
            printf("\t");
            print_date(breakdowns[pos].date);
            printf("\t%d\t", breakdowns[pos].duration);
            // Print laptop data
            printf("%d\t", laptops[laptopPos].id);
            print_typeCPU(laptops[laptopPos].cpu);
            printf("\t%dGB\t", laptops[laptopPos].memory);
            print_typeState(laptops[laptopPos].state);
            printf("\t");
            print_typeLocal(laptops[pos].location);
            printf("\t  %5.2f $\t%s\n", laptops[pos].price, laptops[pos].description);
        }
    }
    else
    {
        printf("\nATENCAO: Nao existe nenhuma avaria registada!\n");
    }
}

/**
 * @brief Show laptops data
 *
 * @param laptops
 * @param numberLaptops
 * @param breakdowns
 * @param numberBreakdowns
 * @param requests
 * @param numberRequests
 */
void list_laptops(typeLaptop *laptops, unsigned int numberLaptops, typeBreakdown *breakdowns, unsigned int numberBreakdowns, typeRequest *requests, unsigned int numberRequests)
{
    int counted;
    unsigned int pos;
    // Check if exist laptops
    if (laptops != NULL && numberLaptops > 0)
    {
        printf("ID\tCPU\tMemor.\tEstado\t\tLocalizacao\tPreco\t\tData aquisi.\tN.Avar\tN.Requi\tDescricao\n");

        for (pos = 0; pos < numberLaptops; pos++)  	// Get laptop by laptop
        {
            // Print laptop data
            printf("%d\t", laptops[pos].id);
            print_typeCPU(laptops[pos].cpu);
            printf("\t%dGB\t", laptops[pos].memory);
            print_typeState(laptops[pos].state);
            printf("\t");
            print_typeLocal(laptops[pos].location);
            printf("\t  %5.2f $\t", laptops[pos].price);
            print_date(laptops[pos].date);

            counted = count_breakdowns_by_laptop_id(breakdowns, numberBreakdowns, laptops[pos].id);
            printf("\t%d\t", counted);
            counted = count_requests_by_laptop_id(requests, numberRequests, laptops[pos].id);
            printf("%d\t", counted);
            printf("%s\n", laptops[pos].description);

            // Print type of user and deadline for each request
            if (counted > 0)
            {
                printf("     +----\n");
                list_requests_by_laptop_id(requests, numberRequests, laptops[pos].id, "     | ");
                printf("\n");
            }
        }
    }
    else
    {
        printf("\nATENCAO: Nao existe nenhum portatil registado!\n");
    }
}

/**
 * @brief Show one requests selected by code
 * 
 * @param requests 
 * @param numberRequests 
 * @param laptops 
 * @param numberLaptops 
 */
void list_one_request(typeRequest *requests, unsigned int numberRequests, typeLaptop *laptops, unsigned int numberLaptops)
{
    int pos, days, laptopPos;
    typeRequest request;

    if (requests != NULL && numberRequests > 0)
    {
        do
        {
            read_string("Insira o codigo da requisicao", request.code, CODE_SIZE);
            pos = search_request_by_code(requests, numberRequests, request.code);

            if (pos == -1)
            {
                printf("\nATENCAO: Nao existe nenhuma requisicao com o codigo inserido\n");
            }
        }
        while (pos == -1);

        printf("\nCodigo:\t\t\t%s\nEstado da requisicao:\t", requests[pos].code);
        print_typeReqState(requests[pos].requisition_state);
        printf("\nPrazo da requisicao:\t%d\nLocal da devolucao:\t", requests[pos].deadline);
        print_typeLocal(requests[pos].devolution_local);
        printf("\nData da requisicao:\t");
        print_date(requests[pos].requisition_date);
        printf("\nData da devolucao:\t");
        // Print duration of requisition
        if (requests[pos].requisition_state == DONE)
        {
            print_date(requests[pos].devolution_date);
            days = diff_date(requests[pos].requisition_date, requests[pos].devolution_date);
            printf("\nDuracao da requisicao:\t%d\n", days);
        }
        else
        {
            printf("---\nDuracao da requisicao:\t---\n");
        }
        printf("Multa:\t\t\t%.2f $\n", requests[pos].price);
        printf("Tipo de cliente:\t");
        print_typeUser(requests[pos].user_type);
        printf("\nNome do cliente:\t%s\n", requests[pos].user_name);

        // Print laptop informations
        laptopPos = search_laptop_id(laptops, numberLaptops, requests[pos].laptop_id);
        printf("+-- Portatil --------\n");
        printf("| ID:\t\t%d\n", laptops[laptopPos].id);
        printf("| Estado:\t");
        print_typeState(laptops[laptopPos].state);
        printf("\n| Designacao:\t%s\n\n", laptops[laptopPos].description);
    }
    else
    {
        printf("\nATENCAO: Nao existe nenhuma requisicao registada!\n");
    }
}
