#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include "fastf.h"

int main() {
    Node* raiz = NULL;
    carregarLista(raiz);

    double targetLatitude = -12.9711;
    double targetLongitude = -38.5108;
    int k = 5;
    fastf* localProx[k];
    double menorDist[k];

    vizinhoProx(raiz, targetLatitude, targetLongitude, localProx, menorDist, k);
    for (int i = 0; i < k; i++) {
        if (localProx[i] != NULL) {
            printf("Endereço: %s", localProx[i]->endereco);
            printf("Categoria: %s", localProx[i]->categoria);
            printf("Cidade: %s", localProx[i]->cidade);
            printf("País: %s", localProx[i]->pais);
            printf("Latitude: %f", localProx[i]->latitude);
            printf("Longitude: %f", localProx[i]->longitude);
            printf("Nome: %s", localProx[i]->nome);
            printf("Código postal: %d", localProx[i]->codigoPostal);
            printf("Província: %s", localProx[i]->provincia);
        }
    }
    return 0;
}