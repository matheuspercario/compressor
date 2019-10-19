#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <map>
#include <string>
#include <bits/stdc++.h>

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
map < int, string > palavras;
map < int, string > palavras_certas;
map < int, string > palavras_corretas;
map < int, string > ::iterator pos;
int flag = 0;

//-----------------------------------------------------------------------------
//	Prototipo das Funcoes
//-----------------------------------------------------------------------------

void compressao();
void descompressao(char * argumento);
void abertura(char * argumento, char * action);
void ler_arq();
void gravar_arq();
void cabecalho();
void print_testes();

//-----------------------------------------------------------------------------
//	Funcao Principal - MAIN
//-----------------------------------------------------------------------------
int main(int argc, char * argv[]) {

    // Variaveis de controle
    string comprimir = "-c";
    string descomprimir = "-d";

    if (argc != 3) {
        // Nao possui numero minimo de argumentos
        printf("Faltando argumentos\n");
    } else if (argv[1] == comprimir) {
        // Chamada funcao de compressao
        abertura(argv[2], ".cmp");
        while (!feof(arq_entrada)) {
            ler_arq();
            cabecalho();
            compressao();
            gravar_arq();
            print_testes();
        }
    } else if (argv[1] == descomprimir) {
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
    if (arq_entrada == NULL) {
        cout << "arq_entrada = Cannot open file!" << endl;
        exit(0);
    }
    strcat(argumento, action);
    arq_saida = fopen(argumento, "w");
    if (arq_saida == NULL) {
        cout << "arq_saida = Cannot open file!" << endl;
        exit(0);
    }
}

void ler_arq() {
    char palavra_aux[50];
    int tam_aux = 0;
    int tam_string = 0;
    while (tam_aux < 4096 && !feof(arq_entrada)) {
        fscanf(arq_entrada, "%s", & palavra_aux);
        //cout << palavra_aux;
        tam_string = strlen(palavra_aux);
        palavras[flag] = palavra_aux;
        flag++;
    }
}

void cabecalho() {
    int tam;
    for (int i = 0; i < palavras.size(); i++) {
        for (int j = 0; j < palavras.size(); j++) {
            int tam_aux = palavras[i].length();
            if (tam_aux <= 3) {
                break;
            }
            if (palavras[i] == palavras[j]) {
                if (j > i || j == i) {
                    tam++;
                }
                break;
            }
        }
    }
    //	cout << "[0 " << tam << "]";	
}

//-----------------------------------------------------------------------------
//	Funcoes - Compressao e Descompressao
//-----------------------------------------------------------------------------	
void gravar_arq() {
    int i = 0;

    //fprintf(arq_saida,"%s",palavra);
    //while(matriz_dados[50][i] !=NULL){

    //}
}

void compressao() {
    int k;
    string palavra_aux;
    for (int i = 0; i < palavras.size(); i++) {
        for (int j = 0; j < palavras.size(); j++) {
            int tam_aux = palavras[i].length();
            if (tam_aux <= 3) {
                break;
            }
            if (palavras[i] == palavras[j]) {
                if (j > i || j == i) {

                    palavra_aux = palavras[i];

                    if (palavra_aux[tam_aux - 1] != ',' && palavra_aux[tam_aux - 1] != '.' && 
                        palavra_aux[tam_aux - 1] != '?' && palavra_aux[tam_aux - 1] != '!' &&
                        palavra_aux[tam_aux - 1] != ';' && palavra_aux[tam_aux - 1] != ':') { //palavras normais

                            palavras_certas[i] = palavras[j];

                    } else { //tratamento de virgula
                        palavras[j] = "";
                        for (k = 0; k < tam_aux - 1; k++) {
                            palavras[j] += palavra_aux[k];
                        }
                        palavras_certas[i] = palavras[j];
                    }
                }

                break;
            }
        }
    }
    int aux = 0;
    for (int i = 0; i < palavras_certas.size(); i++) {
        if (palavras_certas[i].length() > 3) {
            palavras_corretas[aux] = palavras_certas[i];
            aux++;
        }
    }
    cout << "[0 " << palavras_corretas.size() << "]";
    for (int i = 0; i < palavras_corretas.size(); i++) //PRINTA SÓ AS PALAVRAS CORRETAS
        cout << palavras_corretas[i] << ",";
    int flag = 0;
    for (int j = 0; j < palavras.size(); j++) {
        flag = 0;
        for (int i = 0; i < palavras_corretas.size(); i++) {
            int tam_aux = palavras[j].length();
            if (tam_aux <= 3 && flag == 0) {
                flag = 1;
                cout << "" << palavras[j];
            }
            if (palavras_corretas[i] == palavras[j] && flag == 0) {
                flag = 1;
                pos = palavras_corretas.find(i);
                cout << "[255 " << pos->first << "]";
            }
        }
    }
}

void descompressao(char * argumento) {
    printf("%s\n", argumento);
    printf("Funcao Descompressao\n");
}

void print_testes() {
    //	cout << "\n IMPRIMIR PALAVRAS_CERTAS \n" ;
    //	for(int i=0; i<palavras_certas.size(); i++)
    //			cout << " " << palavras_certas[i] << " " << i;
    //		
    //	cout << "\n" << "palavras corretas \n";
    //	for(int i=0; i<palavras_corretas.size(); i++)
    //			cout << " " << palavras_corretas[i] << " " << i ;
    //	
    //
    //	cout << "\n" << palavras_corretas.size() ;
}