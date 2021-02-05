#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Estrutura da arvore */
struct no{

    int estadoAntigo[3][3];
    int estado[3][3];
    struct no *direito;
    struct no *topo;
    struct no *esquerdo;
    struct no *baixo;


}typedef No;

/*Prototipos*/
No* instancia();
void imprimeEstado(int estado[][3]);
void arrCopy(int esquerdo[][3], int direito[][3]);
int match (int estado1[][3], int estado2[][3]);
void troca(int *x, int *y);
No *rotina (int antigo[][3], int a, int b, int c , int d);
int gerarEstado(No *noPtr);

int estadoObjectivo[3][3] = {{1,2,3},{4,5,6},{7,8,0}};

int main(){


    int estado2[3][3] = {{1,6,3},{4,7,2},{5,0,8}};
    No *novoNo = instancia();
    arrCopy(novoNo->estado, estado2);
    gerarEstado(novoNo);


}

/*Funcoes que operam com o quebra cabeca*/

No* instancia(){
    No *noPtr =(No *) malloc(sizeof(No));
    noPtr->topo = NULL;
    noPtr->baixo = NULL;
    noPtr->esquerdo = NULL;
    noPtr->direito = NULL;
}

void imprimeEstado(int estado[][3]){
    int i, j;
    for(i=0; i<3; i++){
       printf("\t\t\t\t\t\t\t");
        for(j=0; j<3; j++){
            printf("%d ", estado[i][j]);
        }
        printf("\n");
    }
      printf("\t\n");
}

void arrCopy(int esquerdo[][3], int direito[][3]){
    int i, j;
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
           esquerdo[i][j] = direito[i][j];
        }
    }
}

int match (int estado1[][3], int estado2[][3]){
    int i, j;
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            if(estado1[i][j] != estado2[i][j])
                return 0;
        }
    }
    return 1;
}

void troca(int *x, int *y){
    int tmp = *x;
    *x =*y;
    *y =tmp;
}

No *rotina (int antigo[][3], int a, int b, int c , int d){
    No *new = instancia();
    arrCopy(new->estado, antigo);
    arrCopy(new->estadoAntigo, antigo);
    troca(&(new->estado[a][b]), &(new->estado[c][d]));
    return new;

}

int gerarEstado(No *noPtr){

        imprimeEstado(noPtr->estado);

    if(match(noPtr->estado, estadoObjectivo) == 1){
        printf("Objectivo atingido ");
        return 1;
    }
    else{
    if(noPtr->estado[0][0] == 0){
        noPtr->baixo = rotina(noPtr->estado, 0,0,1,0);
        if(match(noPtr->baixo->estado, noPtr->baixo->estadoAntigo) == 0)
            gerarEstado(noPtr->baixo);

        noPtr->direito = rotina(noPtr->estado, 0,0,0,1);
        if(match(noPtr->direito->estado, noPtr->estadoAntigo) == 0)
            gerarEstado(noPtr->direito);

    }
     if(noPtr->estado[0][1] == 0){
        noPtr->direito = rotina(noPtr->estado, 0,1,0,2);
        if(match(noPtr->direito->estado, noPtr->estadoAntigo) == 0){
            gerarEstado(noPtr->direito);
        }

        noPtr->esquerdo = rotina(noPtr->estado, 0,1,0,0);
        if(match(noPtr->esquerdo->estado, noPtr->estadoAntigo) == 0)
            gerarEstado(noPtr->esquerdo);

        noPtr->baixo = rotina(noPtr->estado, 0,1,1,1);
        if(match(noPtr->baixo->estado, noPtr->estadoAntigo) == 0)
            gerarEstado(noPtr->baixo);
    }
    if(noPtr->estado[0][2] == 0){
        noPtr->esquerdo = rotina(noPtr->estado, 0,2,0,1);
        if(match(noPtr->esquerdo->estado, noPtr->estadoAntigo) == 0)
            gerarEstado(noPtr->esquerdo);

        noPtr->baixo = rotina(noPtr->estado, 0,2,1,2);
        if(match(noPtr->baixo->estado, noPtr->estadoAntigo) == 0)
            gerarEstado(noPtr->baixo);
    }
    if(noPtr->estado[1][0] == 0){
         noPtr->topo = rotina(noPtr->estado, 1,0,0,0);
         if(match(noPtr->topo->estado, noPtr->estadoAntigo) == 0)
            gerarEstado(noPtr->topo);
        noPtr->direito = rotina(noPtr->estado, 1,0,1,1);
        if(match(noPtr->direito->estado, noPtr->estadoAntigo) == 0)
            gerarEstado(noPtr->direito);

        noPtr->baixo = rotina(noPtr->estado, 1,0,2,0);
        if(match(noPtr->baixo->estado, noPtr->baixo->estadoAntigo) == 0)
            gerarEstado(noPtr->baixo);
    }
     if(noPtr->estado[1][1] == 0){
        noPtr->topo = rotina(noPtr->estado, 1,1,0,1);
        if(match(noPtr->topo->estado, noPtr->estadoAntigo) == 0)
            gerarEstado(noPtr->topo);

        noPtr->direito = rotina(noPtr->estado, 1,1,1,2);
        if(match(noPtr->direito->estado, noPtr->estadoAntigo) == 0)
            gerarEstado(noPtr->direito);

        noPtr->esquerdo = rotina(noPtr->estado, 1,1,1,0);
        if(match(noPtr->esquerdo->estado, noPtr->estadoAntigo) == 0)
            gerarEstado(noPtr->esquerdo);

        noPtr->baixo = rotina(noPtr->estado, 1,1,2,1);
        if(match(noPtr->baixo->estado, noPtr->baixo->estadoAntigo) == 0)
            gerarEstado(noPtr->baixo);
    }
    if(noPtr->estado[1][2] == 0){
        noPtr->esquerdo = rotina(noPtr->estado, 1,2,1,1);
        if(match(noPtr->esquerdo->estado, noPtr->estadoAntigo) == 0)
            gerarEstado(noPtr->esquerdo);

        noPtr->topo = rotina(noPtr->estado, 1,2,0,2);
        if(match(noPtr->topo->estado, noPtr->estadoAntigo) == 0)
            gerarEstado(noPtr->topo);

        noPtr->baixo = rotina(noPtr->estado, 1,2,2,2);
        if(match(noPtr->baixo->estado, noPtr->estadoAntigo) == 0)
            gerarEstado(noPtr->baixo);
    }
     if(noPtr->estado[2][0] == 0){
        noPtr->topo = rotina(noPtr->estado, 2,0,1,0);
        if(match(noPtr->topo->estado, noPtr->estadoAntigo) == 0)
            gerarEstado(noPtr->topo);

        noPtr->direito = rotina(noPtr->estado, 2,0,2,1);
        if(match(noPtr->direito->estado, noPtr->estadoAntigo) == 0)
            gerarEstado(noPtr->direito);


    }
    if(noPtr->estado[2][1] == 0){
        noPtr->direito = rotina(noPtr->estado, 2,1,2,2);
        if(match(noPtr->direito->estado, noPtr->estadoAntigo) == 0)
            gerarEstado(noPtr->direito);


        noPtr->esquerdo = rotina(noPtr->estado, 2,1,2,0);
        if(match(noPtr->esquerdo->estado, noPtr->estadoAntigo) == 0)
            gerarEstado(noPtr->esquerdo);

        noPtr->topo = rotina(noPtr->estado, 2,1,1,1);
        if(match(noPtr->topo->estado, noPtr->estadoAntigo) == 0)
            gerarEstado(noPtr->topo);
    }
    if(noPtr->estado[2][2] == 0){
        noPtr->esquerdo =rotina(noPtr->estado, 2,2,2,1);
        if(match(noPtr->esquerdo->estado, noPtr->estadoAntigo) == 0)
            gerarEstado(noPtr->esquerdo);

        noPtr->topo =rotina(noPtr->estado, 2,2,1,2);
        if(match(noPtr->topo->estado, noPtr->estadoAntigo) == 0)
            gerarEstado(noPtr->topo);
    }
    }

}
