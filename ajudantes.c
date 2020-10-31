#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "ajudantes.h"

typedef struct Cal {
    int dia;
    int mes;
    int ano;
    int tipo;
} Calendario;

void letarMaiusculas(char * str) {
    int len,strNum,alfNum;
    int maiusculo = 0, espacoBranco = 0;
    char alfabeto[27][1] = {
        " ", "A" , "B" , "C" , "D" , "E" ,
        "F" , "G" , "H" , "I" , "J" ,
        "K" , "L" , "M" , "N" , "O" ,
        "P" , "Q" , "R" , "S" , "T" ,
        "U" , "V" , "W" , "X" , "Y", "Z"
    };
    len = strlen(str);
    for (int i = 0; i < len; i++){
        for (int j = 0; j < 26; j++){
            strNum = str[i];
            alfNum = alfabeto[j][0];
            if(j != 0){
                if (strNum == alfNum)
                    maiusculo++;
            }
            else {
                if(str[i] == ' ')
                    espacoBranco++;
            }
        }
    }
            
    if (maiusculo != len) {
        for (int i = 0; i < len; i++)
            str[i] = toupper(str[i]);
    }
}

/*----------------------------------------------------------------- Comeco CPF ----------------------------------------------------------------------------------------------*/
void verificarCPF(char * cpfChar) {
    int valido = 0, somenteNumeros = 1;
    int len = 0;
    int lenCPF = 1;
     
    
    while(len != lenCPF) {
        printf("Digite CPF:  ");
        scanf(" %s", cpfChar);
        len = strlen(cpfChar);
        for(int i = 0; i < 15;i++)
            if (cpfChar[i] == '.' || cpfChar[i] == '-')
                somenteNumeros = 0;
        
        if(somenteNumeros)
            lenCPF = 11;
        else
            lenCPF = 14;

        if(len > lenCPF)
            printf("CPF INVALIDO: cpf muito grande\n\n");
        if(len < lenCPF)
            printf("CPF INVALIDO: cpf muito pequeno\n");
    }
    
    char isNumber[12][1] = {
        "1","2","3","4","5" ,"6" ,"7" ,"8" ,"9" ,"0" ,"." ,"-"
    };
    for(int j = 0; j < lenCPF; j++){
        for(int i = 0; i < 12; i ++){
            if(cpfChar[j] == isNumber[i][0]){
                valido = 1;
                break;
            }
        }
    }
    if (!somenteNumeros) {
        for(int i = 3; i < 6; i ++){
            cpfChar[i] = cpfChar[i + 1];
        }
        int j = 1;
        for(int i = 6; i < 9; i ++){
            cpfChar[i] = cpfChar[i + 2];
        }
        
        cpfChar[9] = cpfChar[12];
        cpfChar[10] = cpfChar[13];
        cpfChar[11] = '\0';
    }
    if(!valido){
        verificarCPF(cpfChar);
    }
}

int charToLong(char * cpfChar, long listaCPF, long * cpf) {
    int skip = 3;
    long convercao = 0;

    for (int i = 0; i < 11; i++)
        convercao = convercao * 10 + (cpfChar[i] - '0');
    
    
    if(convercao == listaCPF) {
        *cpf = convercao;
        return 1;
    } else {
        return 0;
    }
}
/*---------------------------------------------------------------------- Fim CPF ------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------- Comeco Datas --------------------------------------------------------------------------------------------*/

int verificarCalendario(char * calendario, int * data) {
    int local  = 0;
    int valido = 0;

    int len = strlen(calendario);

    calendario[len] = '/';
    calendario[len + 1] = '\0';
    
    for(int j = 0; j < 3; j++){
        for (int i = local; i < 10; i ++){
            if (calendario[i] != '/'){
                data[j] = data[j] * 10 + (calendario[i] - '0');
                local++;
            }
            else {
                local++;
                break;
            }
        }
    }
    valido = validarData(data);
    
    return valido;
}

int validarData(int * data) {
    int valido = 0;
    int mes = 0;
    
    Calendario calendario[13];
    calendario[1].dia = 31; calendario[2].dia  = 28; calendario[3].dia  = 31; calendario[4].dia = 30;
    calendario[5].dia = 31; calendario[6].dia  = 30; calendario[7].dia  = 31; calendario[8].dia = 31;
    calendario[9].dia = 30; calendario[10].dia = 31; calendario[11].dia = 30; calendario[12].dia = 31;
    
    for (int i = 1; i < 13; i++){
        calendario[i].mes = i;
    }
    //Verificar mes
    for(int i = 1; i < 13; i++){

        if(data[1] == calendario[i].mes){
            valido++;
            mes = calendario[i].mes;
            break;
        }
    }
    if(!valido){
        printf("\nMes invalido!\nDigite Data Novamente : ");
        return 0;
    }
    //Verificar dia
    valido = 0;
    if(calendario[mes].dia >= data[0] && data[0] > 0)
        valido++;
        
    if(!valido){
        printf("\nDia invalido!\nDigite Data Novamente : ");
        return 0;
    }
    //Verificar ano

    if(data[1] < 10 || data[2] > 2002){
        printf("\n\n\n\nNAO CONTRATAMOS MENORES DE IDADE!!!\n\n\n");
        return 2;
    }
    if(data[2] < 1950){
        printf("\n\n\n\nFUNCIONARIO MUITO ANTIGO PARA SER CONTRATATO\n\n\n");
        return 2;
    }
    
    
    return valido;
    
}
/*------------------------------------------------------------------- Fim Datas ---------------------------------------------------------------------------------------------*/

void organizarCPF(long cpf, long * orgCpf) {
    long aux = 0;
    int organizador = 8;
    
    for(int i = 0; i < 3;i++){
        cpf = cpf - aux;
        aux = cpf;
        for (int j = 0; j < organizador; j++){
            aux = aux / 10;
        }
        
        aux = floor(aux);
        orgCpf[i] = aux;
        for (int i = 0; i < organizador; i++) {
            aux = aux * 10;
        }
        if (organizador > 3){
            organizador = organizador - 3;
        }
    }
    cpf = cpf - aux;
    aux = cpf;
    orgCpf[3] = aux;
}
