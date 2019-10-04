#include <stdio.h>
#include <string.h>

/*
 *		Disciplina ST562 - Estrutura de Arquivos
 *		Professor: Celmar Guimaraes da Silva
 *
 *
 * 		Projeto - Compressor
 *
 *		Desenvolvedores:
 *			Arthur Guedes
 *			Kevin Barrios
 *			Matheus Bruder
 *
 */

	FILE * arq_entrada, arq_saida;
	char palavra[4096];

//-----------------------------------------------------------------------------
//	Prototipo das Funcoes
//-----------------------------------------------------------------------------
	void compressao(char * argumento);
	void descompressao(char * argumento);

	
//-----------------------------------------------------------------------------
//	Funcao Principal - MAIN
//-----------------------------------------------------------------------------
int main (int argc, char * argv[]) {	
	// Variaveis de controle
	char * comprimir = "-c";
	char * descomprimir = "-d";
	

	if(argc != 3) {
		// Nao possui numero minimo de argumentos
		printf("Faltando argumentos\n");
	}
	else if(strcmp(argv[1], comprimir) == 0) {
		// Chamada funcao de compressao
		abertura(argv[1], ".cmp");
		while(!feof(arq_entrada)) {
			ler_arq();
			compressao(argv[2]);
			gravar_arq();
		}
	} 
	else if(strcmp(argv[1], descomprimir) == 0) {
		// Chamada funcao de descompressao
		abertura(argv[1], "");
		descompressao(argv[2]);
	} else {
			//Parametro invalido
			printf("Argumento invalido!\n");
		}
	
	return 0;	
}


//-----------------------------------------------------------------------------
//	Funcoes - Compressao e Descompressao
//-----------------------------------------------------------------------------	
void abertura(char * argumento, char * action) {
	arq_entrada = fopen(argumento, "r");
	if (arq_entrada == NULL)
    {
        printf("Cannot open file!\n");
        exit(0);
    }
	strcat(argumento, action);
	arq_saida = fopen(argumento, "w");
}

void ler_arq() {
	fread(&palavra, sizeof(palavra), 1, arq_entrada);
}

void grava_arq() {
	fwrite(&palavra, sizeof(palavra), 1, arq_saida);
}




void compressao(char * argumento) {
	// Teste
	printf("%s\n", argumento);
	printf("Funcao Compressao\n");
}

void descompressao(char * argumento) {
	// Teste
	printf("%s\n", argumento);
	printf("Funcao Descompressao\n");
}



