#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include "kd.h"

int main() {
    Node* raiz = NULL;

   carregarLista(raiz);

    double targetLatitude = -6.4282;
    double targetLongitude = -36.6347;
    cidade* cidadeMaisProx = findNearestNeighbor(raiz, targetLatitude, targetLongitude);


     if(cidadeMaisProx->codUF > 10 && cidadeMaisProx->codUF < 18){
       strcpy(cidadeMaisProx->regiao, "Norte");
    }
    if(cidadeMaisProx->codUF > 20 && cidadeMaisProx->codUF < 30){
        strcpy(cidadeMaisProx->regiao, "Nordeste");
    }
    if(cidadeMaisProx->codUF > 30 && cidadeMaisProx->codUF < 36){
        strcpy(cidadeMaisProx->regiao, "Sudeste");
    }
    if(cidadeMaisProx->codUF > 40 && cidadeMaisProx->codUF < 44){
        strcpy(cidadeMaisProx->regiao,"Sul");
    }
    if(cidadeMaisProx->codUF > 49 && cidadeMaisProx->codUF < 54){
        strcpy(cidadeMaisProx->regiao, "Centro-Oeste");
    }

   /*
    cidade* cidade1 = (cidade*)malloc(sizeof(cidade));
    cidade1->latitude = -16.7573;
    cidade1->longitude = -49.4412;
    strcpy(cidade1->nome, "Abadia de Goiás");
    cidade1->codUF, cidade1->estadoUF = 52;
    cidade1->capital = 0;
    strcpy(cidade1->codSiafi, "1050");
    cidade1->ddd = 62;
    strcpy(cidade1->fusoHorario, "America/Sao_Paulo");
    cidade1->codigoIBGE = 5200050;
    strcpy(cidade1->regiao, "Centro-Oeste");
    insert(&raiz, cidade1);

    cidade* cidade2 = (cidade*)malloc(sizeof(cidade));
    cidade2->latitude = -18.4831;
    cidade2->longitude = -47.3916;
    strcpy(cidade2->nome, "Abadia dos Dourados");
    cidade2->codUF, cidade2->estadoUF = 31;
    cidade2->capital = 0;
    strcpy(cidade2->codSiafi, "4001");
    cidade2->ddd = 34;
    strcpy(cidade2->fusoHorario, "America/Sao_Paulo");
    cidade2->codigoIBGE = 3100104;
    strcpy(cidade2->regiao, "Sudeste");
    insert(&raiz, cidade2);

    cidade* cidade3 = (cidade*)malloc(sizeof(cidade));
    cidade3->latitude = -3.47525;
    cidade3->longitude = -41.8425;
    strcpy(cidade3->nome, "Caraúbas do Piauí");
    cidade3->codUF, cidade3->estadoUF = 22;
    cidade3->capital = 0;
    strcpy(cidade3->codSiafi, "0298");
    cidade3->ddd = 86;
    strcpy(cidade3->fusoHorario, "America/Sao_Paulo");
    cidade3->codigoIBGE = 2202539;
    strcpy(cidade3->regiao, "Nordeste");
    insert(&raiz, cidade3);
    */

    // double targetLatitude = -6.4282;
    // double targetLongitude = -36.6347;
    // cidade* cidadeMaisProx = findNearestNeighbor(raiz, targetLatitude, targetLongitude);
 
    if (cidadeMaisProx != NULL) {
        printf("Cidade mais próxima:\n");
        printf("Nome: %s\n", cidadeMaisProx->nome);//s
        printf("Latitude: %f\n", cidadeMaisProx->latitude);
        printf("Longitude: %f\n", cidadeMaisProx->longitude);
        printf("Código IBGE: %d\n", cidadeMaisProx->codigoIBGE);
        printf("Código UF: %d\n", cidadeMaisProx->codUF);
        printf("Região: %s\n", cidadeMaisProx->regiao);
        printf("Código estado UF: %d\n", cidadeMaisProx->estadoUF);
        printf("Codigo Siafi: %s\n", cidadeMaisProx->codSiafi); //s
        printf("DDD: %d\n", cidadeMaisProx->ddd);
        printf("Fuso horário: %d\n", cidadeMaisProx->fusoHorario);
        printf("Capital: %d\n", cidadeMaisProx->capital);
    }
    return 0;
}
