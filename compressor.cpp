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
 *			Gabriel Velasco
 *
 */

//-----------------------------------------------------------------------------
//	Variavéis Globais
//-----------------------------------------------------------------------------
FILE * arq_entrada;
FILE * arq_saida;
ofstream fout;

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
void descompressao();
void abertura(char * argumento);
void ler_arq();
void gravar_arq(char * argumento);
void cabecalho(char * argumento);
void mostra_tela();


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
        abertura(argv[2]);
        while (!feof(arq_entrada)) {
            ler_arq();
            compressao();
			cabecalho(argv[2]); 
            gravar_arq(argv[2]);
            //mostra_tela();
        }
    } else if (argv[1] == descomprimir) {
        // Chamada funcao de descompressao
        abertura(argv[1]);
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
void abertura(char * argumento) {
    arq_entrada = fopen(argumento, "r");
    if (arq_entrada == NULL) {
        cout << "arq_entrada = Cannot open file!" << endl;
        exit(0);
    }  
}

void ler_arq() {
    char palavra_original[64];
    int tam_aux1 = 0;
    char caractere;
    
    while ((tam_aux1 < 4096) && (!feof(arq_entrada))) {
        fscanf(arq_entrada, "%64[^,.!;:? ]s", &palavra_original);
		string palavra_aux = palavra_original;
		
		caractere = getc(arq_entrada);
		
		palavras[contador] = palavra_aux;
		contador++;
        
        switch(caractere){
            case ',':
                palavras[contador] = ',';
                break;
            case '.':
                palavras[contador] = '.';
                break;
            case '!':
                palavras[contador] = '!';
                break;
            case ';':
                palavras[contador] = ';';
                break;
            case ':':
                palavras[contador] = ':';
                break;
            case '?':
                palavras[contador] = '?';
                break;
            case ' ':
                palavras[contador] = ' ';
                break;
            default:
				break;
        }
        
		contador++;
		
		caractere = getc(arq_entrada);
	
		while(caractere == ',' || caractere == '.' || caractere == '!' || caractere == ';' || caractere == ':' || caractere == '?' || caractere == ' ') {
			palavras[contador] = caractere;
			contador++;
			caractere = getc(arq_entrada);
		}
		
		ungetc(caractere, arq_entrada);
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

void cabecalho(char * argumento) {
    strcat(argumento, ".cmp");
    short int tamanho = palavras_corretas.size();
    arq_saida = fopen(argumento, "w");
    unsigned char bytemais = ((tamanho >> 8) & 255); // byte mais significativo
    unsigned char bytemenos = (tamanho & 255); // byte mais significativo
    fprintf(arq_saida, "%c", bytemais);
    fprintf(arq_saida, "%c", bytemenos);
    fclose(arq_saida);

    char d_indice = ','; //delimitador de indice
    for (int i = 0; i < palavras_corretas.size(); i++) {
        //PRINTA SÓ AS PALAVRAS CORRETAS+
        fout.open(argumento, ofstream::app);
        fout << palavras_corretas[i] << d_indice;
        fout.close();
    }
}

void gravar_arq(char * argumento) {  
    char d_palavras = char (255); //delimitador de palavras
    
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
                fout.open(argumento, ofstream::app);
                fout << palavras[j];
                fout.close();
            }
            //Printa na tela as palavras que sao maiores que tres, já comprimidas.
            if (palavras_corretas[i] == palavras[j] && flag == 0) {
                flag = 1;
                pos = palavras_corretas.find(i);
                short int bytepalavra = pos->first;

                arq_saida = fopen(argumento, "a");
                fwrite(&d_palavras, 1, 1, arq_saida); //byte sinalizador de palavras

                unsigned char bytemais = ((bytepalavra >> 8) & 255); // byte mais significativo
                unsigned char bytemenos = (bytepalavra & 255); // byte mais significativo
                fprintf(arq_saida, "%c", bytemais);
                fprintf(arq_saida, "%c", bytemenos);
                fclose(arq_saida);
            }
        }
    }
}

void descompressao(char * argumento) {
    printf("%s\n", argumento);
    printf("Caso de uso 2 não implementado!\n");
}

//-----------------------------------------------------------------------------
//	Funcao Auxiliar
//-----------------------------------------------------------------------------
void mostra_tela() {
    //cabeçalho
    int x = 0;
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
                int m = pos->first;
                cout << "(255 " << x << " " << m << ")";
            }
        }
    }
}
