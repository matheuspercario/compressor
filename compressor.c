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
 *
 */

//-----------------------------------------------------------------------------
//	Prototipo das Funcoes
//-----------------------------------------------------------------------------
	void compressao(char * argumento);
	void descompressao(char * argumento);

	
//-----------------------------------------------------------------------------
//	Funcao Principal - MAIN
//-----------------------------------------------------------------------------
int main (int argc, char * argv[])
{	
	// Variaveis de controle
	char * comprimir = "-c";
	char * descomprimir = "-d";
	

	if(argc != 3)
	{
		// Nao possui numero minimo de argumentos
		printf("Faltando argumentos\n");
	}
	else if(strcmp(argv[1], comprimir) == 0)
	{
		// Chamada função de compressao
		printf("Funcao Compressao\n");
		compressao(argv[2]);
	} 
	else if(strcmp(argv[1], descomprimir) == 0)
	{
		// Chamada função de descompressao
		printf("Funcao Descompressao\n");
		descompressao(argv[2]);
	} else
		{
			//Parametro invalido
			printf("Argumento invalido!\n");
		}
	

	return 0;	
}


//-----------------------------------------------------------------------------
//	Funcoes - Compressao e Descompressao
//-----------------------------------------------------------------------------	
void compressao(char * argumento)
{
	// Teste
	printf("%s\n", argumento);
}

void descompressao(char * argumento)
{
	// Teste
	printf("%s\n", argumento);
}