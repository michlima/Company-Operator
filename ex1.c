#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ajudantes.h"

typedef struct Cal {
    int dia;
    int mes;
    int ano;
    int tipo;
} Calendario;

typedef struct func {
    int id;
    char nome[50];
    long cpf;
    Calendario data;
} tFuncionario;

typedef struct CPF {
    long CPF;
    int valido;
} CPFValidade;


//Interface
void interface(int id, char * Nome, long cpf, int dia, int mes, int ano, int i);
void alinharDados(char * espaco, char * nome, int len);
void imprimirEspaco(char * espaco, int tamDeEspaco, int n);


//Dados
void pegarCPF(long * cpf, int * cpfValido, int * cpfZerou);
int pegarDatas (int * dia, int * mes, int * ano);
void pegarNome(char *  nome);

//
void rodarPrograma(int opcao, int * id, char * nome, long * cpf, int * dia, int * mes, int * ano);

void mainMenu();

//Dados Universais
int running = 1;
int numDF = 0;
int cpfValido[5] = { 1,1,1,1,1};



int main(){
    printf("\n\n\n\t\t\t\t*FUNCIONARIOS SIRIUS CYBERNETICS CORP*\n\n\n\n");
    while(running){
        mainMenu();
    }
    
    return 0;
}

void mainMenu(){
    int editando, num = 0, buscaID = 0;
    char navegar;
    
    tFuncionario dados[5];
    tFuncionario busca[5];
    int localizarF;

    int opcao;
    printf(
           "\n\n(1) Inserir Dados Dos Funcionario\t"
           "(2) Lista de Funcionarios\t"
           "(3) Sair Do Programa\n\n\n\n");
    
    scanf(" %d", &opcao);
    getchar();
    
    switch (opcao) {
        case 1:
            editando = 1;
            while(editando){
                if(numDF < 5){
                rodarPrograma(opcao,
                              &dados[numDF].id,
                              dados[numDF].nome,
                              &dados[numDF].cpf,
                              &dados[numDF].data.dia,
                              &dados[numDF].data.mes,
                              &dados[numDF].data.ano
                              );
                } else {
                    printf("\n\n\t\t\t\t\t >>COMPANIA JA ESTA CHEIA<< \n\n");
                    break;
                }
                int loop = 1;
                while (loop) {
                    printf("DESEJA ADICIONAR MAIS FUNCIONARIOS ? (s) sim (n) nao\n");
                    scanf(" %c", &navegar);
                    getchar();
                    if(navegar == 'n'){
                        editando = 0;
                        loop--;
                    }
                    else if (navegar != 's')
                        printf("\n'%c' NAO EH UMA OPCAO, DIGITE DE NOVO\n\n", navegar);
                    else
                        loop--;
                }
            }
            break;
        case 2:
            if(numDF == 0)
                num = 1;
            else
                num = numDF;
            for (int i = 0; i < num; i++) {
                interface(
                          dados[i].id,
                          dados[i].nome,
                          dados[i].cpf,
                          dados[i].data.dia,
                          dados[i].data.mes,
                          dados[i].data.ano,
                          i
                          );
            }
            
            
            opcao = 1;
            while(opcao != 2){
                printf(
                       "\n\n(1) Buscar Dados\t"
                       "(2) Voltar Para Menu Principal\n\n\n\n");
                scanf("%d", &opcao);
                getchar();
                if (opcao == 1) {
                    printf("Digite ID do funcionario\n\n");
                    scanf("%d", &buscaID);
                    getchar();
                    for(int i = 0; i < numDF; i++) {
                        printf("\n\n\n \t\t\t\t\t>>>>>>Busca: %d    ID : %d \n\n", buscaID, dados[i].id);
                        if(dados[0].id == buscaID) {
                            busca[0].id = dados[i].id;
                            busca[0].cpf = dados[i].cpf;
                            busca[0].data.dia = dados[i].data.dia;
                            busca[0].data.mes = dados[i].data.mes;
                            busca[0].data.ano = dados[i].data.ano;
                            
                            int len = strlen(dados[i].nome);
                            for ( int j = 0; j < len; j++){
                                busca[0].nome[j] = dados[j].nome[j];
                            }
                            printf("\n\n\n \t\t\t\t\t>>>>>>Nome: %s \n\n", busca[i].nome);


                        }
                    }
                    interface(
                              busca[0].id,
                              busca[0].nome,
                              busca[0].cpf,
                              busca[0].data.dia,
                              busca[0].data.mes,
                              busca[0].data.ano,
                              0
                              );
                    }
                }
            }
            break;
        case 3:
            running = 0;
            break;
        default:
//            printf("\n\n\n\n\t\t\t\t\t'%c' NAO EH UMA OPCAO\n\n", opcao);
            break;
    }
   
}

void rodarPrograma(int opcao, int * id, char * nome, long * cpf, int * dia, int * mes, int * ano) {
    int cpfZerou = 0;
    int valido = 0;
    
    //Leitura dos dados
    
    pegarNome(nome);
    pegarCPF(cpf, cpfValido, &cpfZerou);
    valido = pegarDatas(dia, mes, ano);
                    
    *id = numDF;
    numDF++;
            
    if(valido == 2){
        cpfValido[cpfZerou] = 1;
        numDF--;
    
    }
}

void pegarNome(char * nome) {
    int len;
    printf("\nDigite o nome do funcionario: ");
    scanf("%[^\n]", nome);
    len = strlen(nome);
    if(len > 50){
        nome[50] = '\0';
    }
    
    letarMaiusculas(nome);
        
    
    
}

int pegarDatas (int * dia, int * mes, int * ano) {
    char calendario[20];
    int data[3], valido = 0;
    for (int i = 0; i < 3; i++){
        data[i] = 0;
    }
    
    printf("Digite Aniversario (Ex: dia/mes/ano): ");
    

    while(valido == 0){
        scanf(" %s", calendario);
        valido = verificarCalendario(calendario, data);
        if(!valido) {
            for (int i = 0; i < 3; i++){
                data[i] = 0;
            }
        }
    }
    *dia = data[0];
    *mes = data[1];
    *ano = data[2];
    
    return valido;
}

void pegarCPF(long * cpf, int * cpfValido, int * cpfZerou) {
    char cpfChar[50];
    CPFValidade cpfExistentes[5];
    int valido = 0, cpfExiste = 0;
    
    cpfExistentes[0].CPF = 37087462874;
    cpfExistentes[0].valido = cpfValido[0];
    cpfExistentes[1].CPF = 37087462873;
    cpfExistentes[1].valido = cpfValido[1];
    cpfExistentes[2].CPF = 37087462872;
    cpfExistentes[2].valido = cpfValido[2];
    cpfExistentes[3].CPF = 37087462871;
    cpfExistentes[3].valido = cpfValido[3];
    cpfExistentes[4].CPF = 37087462870;
    cpfExistentes[4].valido = cpfValido[4];
    
    while (!cpfExiste){
    verificarCPF(cpfChar);
        for (int i = 0; i < 5; i++){
            cpfExiste = charToLong(cpfChar,cpfExistentes[i].CPF,cpf);

            if(cpfExiste){
                if(cpfExistentes[i].valido){
                    cpfValido[i] = 0;
                    *cpfZerou = i;
                    break;
                } else {
                    printf("\nCPF JA CADASTRADO!\n");
                    cpfExiste = 0;
                    break;
                }
            }
            
            if(!cpfExiste && i == 4){
                printf("\nCPF NAO EXISTE!\n");
            }
        }
    }
    
}

/*----------------------------------------------------------------- Comeco Interface --------------------------------------------------------------------------------------------*/
void alinharDados(char * espaco, char * nome, int len) {
    int tamDeEspaco = 0;
    
    tamDeEspaco = 55 - len;
    imprimirEspaco(espaco, tamDeEspaco, 0);
}
void imprimirEspaco(char * espaco, int tamDeEspaco, int n){
    for (int i = 0; i < tamDeEspaco; i++){
        espaco[i] = ' ';
    }
    espaco[tamDeEspaco] = '\0';
}

void interface(int id, char * Nome, long cpf, int dia, int mes, int ano, int i) {
    long orgCpf[5];
    char nome[50], espaco[90];
    int len = strlen(Nome);
    
    
    for (int i = 0; i < len; i++){
        nome[i] = Nome[i];
    }
    
    alinharDados(espaco,nome, len);
    organizarCPF(cpf,orgCpf);
    nome[len] = '\0';
    if(numDF == 0){
        printf(
               "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
               "ID       NOME                                                    CPF               DATA DE NASCIMENTO\n"
               "-------------------------------------------------------------------------------------------------------"
               "\n\n"
               "                            ERRO!!: NAO HA NEM UM DADOS DE FUNCIONARIOS\n\n"
               "-------------------------------------------------------------------------------------------------------\n"
               "-------------------------------------------------------------------------------------------------------"
);
    }
    else {
        if(i == 0){
            printf(
                   "ID       NOME                                                    CPF               DATA DE NASCIMENTO\n"
                   "-------------------------------------------------------------------------------------------------------");
        }
        if(mes < 10){
            printf("\n\%d        %s %s%ld.%ld.%ld-%ld    %d/0%d/%d          \n",
                   id,
                   nome,
                   espaco,
                   orgCpf[0],orgCpf[1],orgCpf[2],orgCpf[3],
                   dia, mes, ano);
        } else {
            printf("\n\%d        %s %s%ld.%ld.%ld-%ld    %d/%d/%d          \n",
                   id,
                   nome,
                   espaco,
                   orgCpf[0],orgCpf[1],orgCpf[2],orgCpf[3],
                   dia, mes, ano);
        }
    }
    
    if(i == numDF - 1){
        printf(
               "-------------------------------------------------------------------------------------------------------");
    }
}
/*-------------------------------------------------------------------- Fim Interface --------------------------------------------------------------------------------------------*/


