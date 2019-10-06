#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <map>
#include <string>
	using namespace std;	
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

	FILE * arq_entrada;
	FILE * arq_saida;
	int j= 0;


//-----------------------------------------------------------------------------
//	Prototipo das Funcoes
//-----------------------------------------------------------------------------
	map <int, string> palavras;
	void compressao();
	void descompressao(char * argumento);
	void abertura(char * argumento, char * action);
	void ler_arq();
	void gravar_arq();
	void cabecalho();
//-----------------------------------------------------------------------------
//	Funcao Principal - MAIN
//-----------------------------------------------------------------------------7

int main (int argc, char * argv[]){	

	// Variaveis de controle
	string comprimir= "-c";
	string descompressao = "-d";

	if(argc != 3) {
		// Nao possui numero minimo de argumentos
		printf("Faltando argumentos\n");
	}
	else if(argv[1]== comprimir) {
		// Chamada funcao de compressao
		abertura(argv[2], ".cmp");
		while(!feof(arq_entrada)) {
			ler_arq();
			cabecalho();
			compressao();	
			gravar_arq();
		}
	} 
	else if(argv[1]== descompressao) {
		// Chamada funcao de descompressao
		abertura(argv[1], "");
		//descompressao(argv[2]);
	} else {
			//Parametro invalido
			printf("Argumento invalido!\n");
		}
return 0;	
}

//-----------------------------------------------------------------------------
//	Funcoes - Compressao e Descompressao  (Prontas)
//-----------------------------------------------------------------------------	
void abertura(char * argumento, char * action) {
	arq_entrada = fopen(argumento, "r");
	if (arq_entrada == NULL)
    {
		printf("%s", argumento);
        printf("Cannot open file!\n");
        exit(0);
    }
	strcat(argumento, action);
	arq_saida = fopen(argumento, "w");
}

void ler_arq() {
	char palavra_aux[50];
	int tam_aux=0;
	int tam_string = 0 ; 
	while(tam_aux < 4096 && !feof(arq_entrada)){
		fscanf(arq_entrada,"%s",&palavra_aux);
		tam_string =  strlen(palavra_aux);	
			palavras[j]= palavra_aux;
				j++;
	}
}

void cabecalho (){
	int tam;

	for(int i=0; i<palavras.size(); i++){
		for(int j=0; j<palavras.size(); j++){
			int tam_aux = palavras[i].length();
			if( tam_aux <= 3){
				
				break;
			}
			if(palavras[i] == palavras[j]  ){
				if(j>i || j==i ){
				tam++;
			
				}
				break;
			}
		}
	}
	printf("(0) (%d)", tam);

	
}

//-----------------------------------------------------------------------------
//	Funcoes - Compressao e Descompressao
//-----------------------------------------------------------------------------	
void gravar_arq(){
	int i=0;
	
	//fprintf(arq_saida,"%s",palavra);
	//while(matriz_dados[50][i] !=NULL){
	
	//}
}

void compressao(){

	for(int i=0; i<palavras.size(); i++){
		for(int j=0; j<palavras.size(); j++){
			int tam_aux = palavras[i].length();
			if( tam_aux <= 3){
				
				break;
			}
			if(palavras[i] == palavras[j]  ){
				if(j>i || j==i ){
			
				cout << palavras[i] <<",";
				}
				break;
			}
		}
	}


	for(int i=0; i<palavras.size(); i++){
		for(int j=0; j<palavras.size(); j++){
			int tam_aux = palavras[i].length();
			if( tam_aux <= 3){
				cout << "" <<palavras[i];
				break;
			}
			if(palavras[i] == palavras[j]){	
				printf("(255)(%d)",j);
				break;
			}

		}


	}
	

}

void descompressao(char * argumento) {
	// Teste
	printf("%s\n", argumento);
	printf("Funcao Descompressao\n");
}




