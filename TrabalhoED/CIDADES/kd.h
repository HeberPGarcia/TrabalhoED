#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>

typedef struct {
    int codigoIBGE;
    char nome[50];
    double latitude;
    double longitude;
    int codUF;
    int estadoUF;
    int capital;
    char regiao[30];
    char codSiafi[10];
    int ddd;
    char fusoHorario[70];
} cidade;

typedef struct Node {
    cidade* cidade;
    struct Node* esq;
    struct Node* dir;
} Node;

Node* criarNo(cidade* cidade) {
    Node* no = (Node*)malloc(sizeof(Node));
    no->cidade = cidade;
    no->esq = NULL;
    no->dir = NULL;
    return no;
}

Node* inserirRecursao(Node* node, cidade* cidade, int depth) {
    if (node == NULL) {
        return criarNo(cidade);
    }

    int profundidade = depth % 2;
    if (profundidade == 0) { //Checar latitude
        if (cidade->latitude < node->cidade->latitude)
            node->esq = inserirRecursao(node->esq, cidade, depth + 1);
        else
            node->dir = inserirRecursao(node->dir, cidade, depth + 1);
    } else { //checar longitude
        if (cidade->longitude < node->cidade->longitude)
            node->esq = inserirRecursao(node->esq, cidade, depth + 1);
        else
            node->dir = inserirRecursao(node->dir, cidade, depth + 1);
    }

    return node;
}

double distancia(double latitude1, double longitude1, double latitude2, double longitude2) {
    double dlatitude = latitude2 - latitude1;
    double dlongitude = longitude2 - longitude1;
    double distanciaC = sqrt((dlatitude * dlatitude) + (dlongitude * dlongitude));
    return distanciaC;
}

void insert(Node** raiz, cidade* cidade) {
    *raiz = inserirRecursao(*raiz, cidade, 0);
}

void visinhoMaisProxRecursao(Node* node, double latitude, double longitude, int depth, cidade** cidadeProxima, double* menorDistancia) {
    if (node == NULL)
        return;

    double distanciaC = distancia(node->cidade->latitude, node->cidade->longitude, latitude, longitude);
    if (distanciaC < *menorDistancia) {
        *cidadeProxima = node->cidade;
        *menorDistancia = distanciaC;
    }

    int profundidade = depth % 2;
    if (profundidade == 0) {
        if (latitude < node->cidade->latitude) {
            visinhoMaisProxRecursao(node->esq, latitude, longitude, depth + 1, cidadeProxima, menorDistancia);
            if (fabs(node->cidade->latitude - latitude) < *menorDistancia)
                visinhoMaisProxRecursao(node->dir, latitude, longitude, depth + 1, cidadeProxima, menorDistancia);
        } else {
            visinhoMaisProxRecursao(node->dir, latitude, longitude, depth + 1, cidadeProxima, menorDistancia);
            if (fabs(node->cidade->latitude - latitude) < *menorDistancia)
                visinhoMaisProxRecursao(node->esq, latitude, longitude, depth + 1, cidadeProxima, menorDistancia);
        }
    } else {
        if (longitude < node->cidade->longitude) {
            visinhoMaisProxRecursao(node->esq, latitude, longitude, depth + 1, cidadeProxima, menorDistancia);
            if (fabs(node->cidade->longitude - longitude) < *menorDistancia)
                visinhoMaisProxRecursao(node->dir, latitude, longitude, depth + 1, cidadeProxima, menorDistancia);
        } else {
            visinhoMaisProxRecursao(node->dir, latitude, longitude, depth + 1, cidadeProxima, menorDistancia);
            if (fabs(node->cidade->longitude - longitude) < *menorDistancia)
                visinhoMaisProxRecursao(node->esq, latitude, longitude, depth + 1, cidadeProxima, menorDistancia);
        }
    }
}

cidade* findNearestNeighbor(Node* raiz, double latitude, double longitude) {
    cidade* cidadeProxima = NULL;
    double menorDistancia = INT_MAX;
    visinhoMaisProxRecursao(raiz, latitude, longitude, 0, &cidadeProxima, &menorDistancia);
    return cidadeProxima;
}

/*
void carregar1(Node *&root){
    FILE *arq1 = fopen("c.txt", "r");
    for(int i = 0; i < 5571; i++){
    cidade* cidadex = (cidade*) malloc(sizeof(cidade));
    fscanf(arq1, "%d %s %f %f %d %d %d %d %s", cidadex->codigoIBGE, cidadex->nome, cidadex->latitude, cidadex->longitude, cidadex->codUF, cidadex->codSiafi, cidadex->ddd, cidadex->fusoHorario);
    insert(&root, cidadex);
    }
}*/

void carregarLista(Node *&raiz){
    FILE *arq;
    arq = fopen("cidades.txt", "r");
     if(arq == NULL){
         printf("ERRO, A LISTA ESTÁ VAZIA!");
     }else{
    while (!feof(arq) == 0) {   
    cidade* cidadex = (cidade*) malloc(sizeof(cidade));
    fscanf(arq, "%d %[^ ] %lf %lf %d %d %s %d %s", &cidadex->codigoIBGE, &cidadex->nome, &cidadex->latitude, &cidadex->longitude, &cidadex->capital, &cidadex->codUF, &cidadex->codSiafi, &cidadex->ddd, &cidadex->fusoHorario);
    insert(&raiz, cidadex);
        }
        fclose(arq);
    }
};