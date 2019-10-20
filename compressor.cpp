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

int contador = 0;
int existe = 0;
//-----------------------------------------------------------------------------
//	Prototipo das Funcoes
//-----------------------------------------------------------------------------

void compressao();
void descompressao(char * argumento);
void abertura(char * argumento, char * action);
void ler_arq();
void gravar_arq();
void cabecalho();
void mostra_tela();

void ler_arq_comprimido();

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
            
            compressao();
			cabecalho(); //JA IMPRIME
            gravar_arq();
            mostra_tela();

            ler_arq_comprimido();
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
    //strcat(argumento, action);
    arq_saida = fopen("textoCOMPRIMIDO.bin", "wb");
    if (arq_saida == NULL) {
        cout << "arq_saida = Cannot open file!" << endl;
        exit(0);
    }
}

void ler_arq() {
    char palavra_original[50];
    int tam_aux1 = 0;
    
    while ((tam_aux1 < 4096) && (!feof(arq_entrada))) {
        fscanf(arq_entrada, "%s", &palavra_original);
		string palavra_aux = palavra_original;
        string palavra_aux1 = palavra_original;

        int tam_aux = palavra_aux.size() - 1;
        //cout << palavra_aux << endl;
        //cout << tam_aux << endl;
              
        switch(palavra_aux[tam_aux]){
            case ',':
                palavras[contador] = palavra_aux;
                contador++;
                palavras[contador] = ',';
                contador++;
                break;
            case '.':
                palavras[contador] = palavra_aux;
                contador++;
                palavras[contador] = '.';
                contador++;
                break;
            case '!':
                palavras[contador] = palavra_aux;
                contador++;
                palavras[contador] = '!';
                contador++;
                break;
            case ';':
                palavras[contador] = palavra_aux;
                contador++;
                palavras[contador] = ';';
                contador++;
                break;
            case ':':
                palavras[contador] = palavra_aux;
                contador++;
                palavras[contador] = ':';
                contador++;
                break;
            case '?':
                palavras[contador] = palavra_aux;
                contador++;
                palavras[contador] = '?';
                contador++;
                break;
            default:    
                palavras[contador] = palavra_aux;
                contador++;
        }
    }
}

void cabecalho() {
    int tamanho = palavras_corretas.size();
    fwrite(&tamanho, 2, 1, arq_saida);
    //cout << "(0 " << palavras_corretas.size() << ")";
}

void ler_arq_comprimido() {
    FILE * arq = fopen("textoCOMPRIMIDO.bin", "rb");
    fseek(arq, 0, SEEK_SET);
    if (arq == NULL) {
        cout << "arq_saida = Cannot open file!" << endl;
        exit(0);
    } else {
        unsigned char caractere;
        caractere = fgetc(arq);
        while (!feof(arq)) {
            //fscanf(arq, "%s", &palavra_orig);
            cout << caractere << endl;
            caractere = fgetc(arq);
        }
    }

}

void gravar_arq() {

    int d_palavras = 255;//delimitador de palavras
    char d_indice = ',';//delimitador de indice
    for (int i = 0; i < palavras_corretas.size(); i++) {
        //PRINTA SÓ AS PALAVRAS CORRETAS
        fwrite(&palavras_corretas[i], sizeof(palavras_corretas[i].length()), 1, arq_saida);
        fwrite(&d_indice, 1, 1, arq_saida);
    }
    //cout << palavras_corretas[i] << ',';
    int flag = 0;
    for (int j = 0; j < palavras.size(); j++) {
        flag = 0;
        for (int i = 0; i < palavras_corretas.size(); i++) {
            int tam_aux = palavras[j].length();
			if(flag == 1) {
				break;
			}
            //Printa na tela as palavras que sao menores que 3.
            if (tam_aux <= 3 && flag == 0) {
                flag = 1;
                fwrite(&palavras[j], sizeof(palavras[j].length()), 1, arq_saida);
                //cout << palavras[j];
            }
            //Printa na tela as palavras que sao maiores que tres, já comprimidas.
            if (palavras_corretas[i] == palavras[j] && flag == 0) {
                flag = 1;
                pos = palavras_corretas.find(i);

                // convertido = pos->first *256;
                int m = pos->first;
                fwrite(&d_palavras, 1, 1, arq_saida);
                fwrite(&m, 2, 1, arq_saida);
                //cout << d_palavras << pos->first;
            }
        }
    }
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
                    
                    // Nao alterar "-1", pois vai bugar a condicao "if (tam_aux <= 3)"
                    if (palavra_aux[tam_aux - 1] != ',' && palavra_aux[tam_aux - 1] != '.' && 
                        palavra_aux[tam_aux - 1] != '?' && palavra_aux[tam_aux - 1] != '!' &&
                        palavra_aux[tam_aux - 1] != ';' && palavra_aux[tam_aux - 1] != ':') { //palavras normais

                            palavras_certas[i] = palavras[j];

                    } else { //tratamento de virgula
                        palavras[j] = "";
                        for (k = 0; k < tam_aux - 1; k++) {
                            palavras[j] += palavra_aux[k];
                        }
                        
                        for(int k =0; k<palavras_certas.size(); k++){
                                if(palavras_certas[k] == palavras[j])
                                    existe=1;
                        }
                              if(existe ==0)
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
}

void descompressao(char * argumento) {
    printf("%s\n", argumento);
    printf("Funcao Descompressao\n");
}

void mostra_tela() {
    //cabeçalho
    cout << "(0 " << palavras_corretas.size() << ")";

    for (int i = 0; i < palavras_corretas.size(); i++) //PRINTA SÓ AS PALAVRAS CORRETAS
    //Printa na tela as palavras do INDICE (RRN)
    cout << palavras_corretas[i] << ",";
    int flag = 0;
    for (int j = 0; j < palavras.size(); j++) {
        flag = 0;
        for (int i = 0; i < palavras_corretas.size(); i++) {
            int tam_aux = palavras[j].length();
			if(flag == 1) {
				break;
			}
            //Printa na tela as palavras que sao menores que 3.
            if (tam_aux <= 3 && flag == 0) {
                flag = 1;
                cout << palavras[j];
            }
            //Printa na tela as palavras que sao maiores que tres, já comprimidas.
            if (palavras_corretas[i] == palavras[j] && flag == 0) {
                flag = 1;
                pos = palavras_corretas.find(i);

                // convertido = pos->first *256;
                int m =  pos->first;
                cout << "(255 " << m << ")";
            }
        }
    }
}