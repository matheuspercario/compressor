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

FILE * arq_entrada;
FILE * arq_saida;
map < int, string > palavras;
map < int, string > palavras_certas;
map < int, string > palavras_corretas;
map < int, string > ::iterator pos;

int contador = 0;
int existe = 0;


ofstream f_out("texto.txt.cmp");
if(!f_out.is_open()) {
	cout << "unable" << endl;
}
	


//-----------------------------------------------------------------------------
//	Prototipo das Funcoes
//-----------------------------------------------------------------------------

void compressao();
void descompressao(char * argumento);
void abertura(char * argumento);
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
        abertura(argv[2]);
        while (!feof(arq_entrada)) {
            ler_arq();
            compressao();
			cabecalho(); //JA IMPRIME
            gravar_arq();
            mostra_tela();

            //ler_arq_comprimido();
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
    
    /*arq_saida = fopen("texto.txt.cmp", "w+");
    if (arq_saida == NULL) {
        cout << "arq_saida = Cannot open file!" << endl;
        exit(0);
    }*/
   
}

void ler_arq() {
    char palavra_original[50];
    int tam_aux1 = 0;
    
    while ((tam_aux1 < 4096) && (!feof(arq_entrada))) {
        fscanf(arq_entrada, "%s", &palavra_original);
		string palavra_aux = palavra_original;
        string palavra_aux1 = palavra_original;

        int tam_aux = palavra_aux.size() - 1;
		//cout << "\"" << palavra_aux << "\"" << endl;
		//cout << "tamanho:" << tam_aux << endl;
        
        //Caractere espaço:
        char caractere = getc(arq_entrada);
        
		//cout << "Caractere: \"" << caractere << "\"" << endl;
        
		palavras[contador] = palavra_aux;
		contador++;
        
        switch(palavra_aux[tam_aux]){
            case ',':
                palavras[contador] = ',';
                contador++;
				palavras[contador] = ' ';
				contador++;
                break;
            case '.':
                palavras[contador] = '.';
                contador++;
                palavras[contador] = ' ';
				contador++;
                break;
            case '!':
                palavras[contador] = '!';
                contador++;
                palavras[contador] = ' ';
				contador++;
                break;
            case ';':
                palavras[contador] = ';';
                contador++;
                palavras[contador] = ' ';
				contador++;
                break;
            case ':':
                palavras[contador] = ':';
                contador++;
                palavras[contador] = ' ';
				contador++;
                break;
            case '?':
                palavras[contador] = '?';
                contador++;
                palavras[contador] = ' ';
				contador++;
                break;
            default:
				if(caractere == ' ') {
					palavras[contador] = ' ';
				}
				contador++;
				break;
        }
    }
}

void cabecalho() {
    int tamanho = palavras_corretas.size();
    char tamanho_char = char(tamanho);
    //fwrite(&tamanho_char, sizeof(char), 1, arq_saida);
}

void gravar_arq() {  
    char d_palavras = char (255);//delimitador de palavras
    char d_indice = ',';//delimitador de indice
    for (int i = 0; i < palavras_corretas.size(); i++) {
        //PRINTA SÓ AS PALAVRAS CORRETAS
        //cout << "\n" << "\n" << "\n" << "\n" << palavras_corretas[i] << "\n" << "\n" << "\n" << "\n" << endl;
        //fwrite(&palavras_corretas[i], 1, sizeof(palavras_corretas[i]), arq_saida);
        //fwrite(&d_indice, 1, 1, arq_saida);
        
        //printf("%c\n", palavras_corretas[i]);
        f_out << palavras_corretas[i] << d_indice << endl;
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
                //fwrite(&palavras[j], sizeof(palavras[j].length()), 1, arq_saida);
                //cout << palavras[j];
            }
            //Printa na tela as palavras que sao maiores que tres, já comprimidas.
            if (palavras_corretas[i] == palavras[j] && flag == 0) {
                flag = 1;
                pos = palavras_corretas.find(i);

                // convertido = pos->first *256;
                int m = pos->first;
                char var = char(m);
                //fwrite(&d_palavras, 1, 1, arq_saida);
                //fwrite(&var, 2, 1, arq_saida);
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