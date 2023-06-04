#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>

typedef struct {
    int numero;
    char endereco[70];
    char categoria[50];
    char cidade[50];
    char pais[30];
    double latitude;
    double longitude;
    char nome[30];
    int codigoPostal;
    char provincia[50];

} fastf;

typedef struct Node {
    fastf* fastfood;
    struct Node* esq;
    struct Node* dir;
} Node;

double distancia(double latitude1, double longitude1, double latitude2, double longitude2) {
    double dlatitude = latitude2 - latitude1;
    double dlongitude = longitude2 - longitude1;
    double distanciaC = sqrt((dlatitude * dlatitude) + (dlongitude * dlongitude));
    return distanciaC;
}

void insert(Node** node, fastf* fastfood, int depth) {
    if (*node == NULL) {
        *node = (Node*)malloc(sizeof(Node));
        (*node)->fastfood = fastfood;
        (*node)->esq = NULL;
        (*node)->dir = NULL;
    } else {
        int currentDim = depth % 2; //PARA CALCULAR PROFUNDIDADE RECURSIVAMENTE
        if (currentDim == 0) {
            if (fastfood->latitude < (*node)->fastfood->latitude)
                insert(&((*node)->esq), fastfood, depth + 1);
            else
                insert(&((*node)->dir), fastfood, depth + 1);
        } else {
            if (fastfood->longitude < (*node)->fastfood->longitude)
                insert(&((*node)->esq), fastfood, depth + 1);
            else
                insert(&((*node)->dir), fastfood, depth + 1);
        }
    }
}

void acharProx(Node* node, double latitude, double longitude, int depth, fastf** fastfProx, double* menorDist, int k) {
    if (node == NULL)
        return;

    double distance = distancia(node->fastfood->latitude, node->fastfood->longitude, latitude, longitude);
    
    for (int i = 0; i < k; i++) {
        if (distance < menorDist[i]) {
            for (int j = k - 1; j > i; j--) {
                fastfProx[j] = fastfProx[j - 1];
                menorDist[j] = menorDist[j - 1];
            }

            fastfProx[i] = node->fastfood;
            menorDist[i] = distance;
            break;
        }
    }
    int currentDim = depth % 2;
    if (currentDim == 0) {
        if (latitude < node->fastfood->latitude) {
            acharProx(node->esq, latitude, longitude, depth + 1, fastfProx, menorDist, k);
            if (fabs(node->fastfood->latitude - latitude) < menorDist[k - 1])
                acharProx(node->dir, latitude, longitude, depth + 1, fastfProx, menorDist, k);
        } else {
            acharProx(node->dir, latitude, longitude, depth + 1, fastfProx, menorDist, k);
            if (fabs(node->fastfood->latitude - latitude) < menorDist[k - 1])
                acharProx(node->esq, latitude, longitude, depth + 1, fastfProx, menorDist, k);
        }
    } else {
        if (longitude < node->fastfood->longitude) {
            acharProx(node->esq, latitude, longitude, depth + 1, fastfProx, menorDist, k);
            if (fabs(node->fastfood->longitude - longitude) < menorDist[k - 1])
                acharProx(node->dir, latitude, longitude, depth + 1, fastfProx, menorDist, k);
        } else {
            acharProx(node->dir, latitude, longitude, depth + 1, fastfProx, menorDist, k);
            if (fabs(node->fastfood->longitude - longitude) < menorDist[k - 1])
                acharProx(node->esq, latitude, longitude, depth + 1, fastfProx, menorDist, k);
        }
    }
}

void vizinhoProx(Node* root, double latitude, double longitude, fastf** fastfProx, double* menorDist, int k) {
    for (int i = 0; i < k; i++) {
        fastfProx[i] = NULL;
        menorDist[i] = 5;
    }

    acharProx(root, latitude, longitude, 0, fastfProx, menorDist, k);
}

void carregarLista(Node *&raiz){
    FILE *arq;
    arq = fopen("fastfoods.txt", "r");
     if(arq == NULL){
         printf("ERRO, A LISTA ESTÁ VAZIA!\n");
     }else{
    while (!feof(arq) == 0) {   
    fastf* fastfx = (fastf*) malloc(sizeof(fastf));
    fscanf(arq, "%d\n %[^ ]\n %[^ ]\n %[^ ]\n %[^ ]\n %lf\n %lf\n %[^ ]\n %d\n %[^ ]\n", &fastfx->numero, &fastfx->endereco, &fastfx->categoria, &fastfx->cidade, &fastfx->pais, &fastfx->latitude, &fastfx->longitude, &fastfx->nome, &fastfx->codigoPostal, &fastfx->provincia);
    insert(&raiz, fastfx, 0);
        }
        fclose(arq);
    }
};