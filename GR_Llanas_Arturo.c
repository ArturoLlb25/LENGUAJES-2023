#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo {
  char izq[20];
  char der[20];
  struct nodo *sig;
  struct nodo *ant;
} * LISTA;

int leeArchivo(LISTA *cab, LISTA *cab2);
int insFin(LISTA *cab, LISTA *cab2, char *i, char *d, int *tam);
int creaNodo(LISTA *nuevo, char *i, char *d);
void muestraLista(LISTA cab);
char *obtenerExpresionRegular(LISTA cab);

int main(void) {
  LISTA lista = NULL;
  LISTA lista2 = NULL;
  FILE *f;
  int tam = leeArchivo(&lista, &lista2);
  muestraLista(lista);
  printf("numero de no termianles: %d", tam);
  char *exp = obtenerExpresionRegular(lista);
  printf("\n%s", exp);
  int n=strlen(exp);
  for(int i=0;i<n;i++){
    if(exp[i]=='{'){
      for(int j=i;j<n;j++)
        exp[j]=exp[j+1];
    }
  }
  for(int i=0;i<n;i++){
    if(exp[i]=='}' && exp[i-1]==exp[i+1]){
      for(int j=i;j<n;j++)
        exp[j]=exp[j+1];
      exp[i]='+';
    }
    else if(exp[i]=='}' && exp[i-1]!=exp[i+1])
      exp[i]='*';
  }
  printf("\n%s", exp);
}

int leeArchivo(LISTA *cab, LISTA *cab2) {
  FILE *f;
  char linea[100];
  int res, ta = 0;

  f = fopen("producs.txt", "r");
  if (f == NULL) {
    printf("No se pudo abrir el archivo\n");
    return 0;
  }

  while (fgets(linea, 100, f)) {
    char *p = strtok(linea, "-");
    char *q = strtok(NULL, ">");
    int n = strlen(q);
    q[n - 1] = '\0';

    res = insFin(cab, cab2, p, q, &ta);
    if (!res)
      printf("error");
  }
  return ta;
  fclose(f);
}

int insFin(LISTA *cab, LISTA *cab2, char *i, char *d, int *tam) {
  int res = 0;
  LISTA aux = *cab, nuevo, temp;
  while (aux) {
    if (strcmp(aux->izq, i) == 0) {
      strcat(aux->der, "|");
      strcat(aux->der, d);
      res = 1;
      break;
    }
    aux = aux->sig;
  }
  if (res == 0) {
    (*tam)++;
    res = creaNodo(&nuevo, i, d);
    if (res) {
      nuevo->ant = *cab2;
      if (!*cab2)
        *cab = nuevo;
      else
        (*cab2)->sig = nuevo;
      *cab2 = nuevo;
    }
  }
  return res;
}

int creaNodo(LISTA *nuevo, char *i, char *d) {
  int res = 0;
  *nuevo = (LISTA)malloc(sizeof(struct nodo));
  if (*nuevo) {
    strcpy((*nuevo)->izq, i);
    strcpy((*nuevo)->der, d);
    (*nuevo)->sig = NULL;
    (*nuevo)->ant = NULL;
    res = 1;
  }
  return res;
}

void muestraLista(LISTA cab) {
  while (cab) {
    printf("%s->%s \n", cab->izq, cab->der);
    cab = cab->sig;
  }
}

char *obtenerExpresionRegular(LISTA cab) {
  char *er = NULL;
  char *aux = NULL;
  int flag = 1;
  while (flag) {
    flag = 0;
    while (cab) {
      if (strcmp(cab->izq, "S") == 0) {
        if (er == NULL) {
          er = (char *)malloc(strlen(cab->der) + 1);
          strcpy(er, cab->der);
        } else {
          aux = (char *)malloc(strlen(er) + strlen(cab->der) + 2);
          sprintf(aux, "(%s)|(%s)", er, cab->der);
          free(er);
          er = aux;
        }
      } else {
        char *p = er;
        while (p) {
          p = strstr(p, cab->izq);
          if (p != NULL) {
            flag = 1;
            int l = strlen(p) - strlen(cab->izq);
            aux = (char *)malloc(strlen(er) + strlen(cab->der) -
                                 strlen(cab->izq) + 1);
            strncpy(aux, er, p - er);
            aux[p - er] = '\0';
            strcat(aux, cab->der);
            strcat(aux, p + strlen(cab->izq));
            free(er);
            er = aux;
            p += strlen(cab->der) - strlen(cab->izq);
          }
        }
      }
      cab = cab->sig;
    }
  }
  int n=strlen(er);
  for (int i = 0; i < n; i++) {
    if (er[i] >= 'A' && er[i] <= 'Z') {
      er[i] = er[i - 1];
      er[i - 1] = '{';
      er[i + 1] = '}';
    }
  }

  return er;
}
