#ifndef ajudantes_h
#define ajudantes_h

void letarMaiusculas(char * str);

int charToLong(char * cpfChar, long listaCPF, long * cpf);
void verificarCPF(char * cpfChar);

int verificarCalendario(char * calendario, int * data);
int validarData(int * data);

void organizarCPF(long cpf, long * orgCpf);
    


#endif
