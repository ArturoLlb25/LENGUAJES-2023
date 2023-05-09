#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char nombre[30];
  long dir, ptr_atr, sig_ent;
} TEntidad;
typedef struct {
  char nombre[50];
  int tipo, clave, tam;
  long dir, sig_atr, sig_ent;
} TAtributo;

typedef struct nodA {
  TAtributo a;
  struct nodA *sig;
} TNodoA;

typedef struct nodE {
  TEntidad e;
  struct nodE *sig;
  TNodoA *aba;
} TNodoE;

typedef struct {
  void *bloque;
  int tam;
  int desp;
} TBloque;

TEntidad captura_entidad();
TAtributo captura_atributo();
void imprime_entidad(TEntidad e);
void imprime_atributo(TAtributo a);
void crea_dicc(char nom_arch[]);
void alta_entidad(char nom_ach[], TEntidad e);
void baja_entidad(char nom_ach[], TEntidad e);
void modifica_entidad(char nom_ach[], TEntidad e_baja, TEntidad e_alta);
void inserta_atributo(char nom_dic[], char nom_ent[], TAtributo a);
void elimina_atributo(char nom_dic[], char nom_ent[], char nom_atr[]);
void modifica_atr(char nom_ach[], char nom_ent_baja[], char nom_atr_baja[],
                  TAtributo alta_a);
void imprime_diccionario(char nom_arch[]);

int main(void) {

  char nom_dic[30] = "tiendita.dic";
  char nom_ent[30], nom_at[30];
  TEntidad e, alta, baja;
  TAtributo a, altaat, bajaat;
  char op;
  int opini, opmen;
  printf("1-Crear diccionario\n2-Abrir diccionario\n¿que deseas hacer?:");
  scanf("\n%d", &opini);
  switch (opini) {
  case 1:
    crea_dicc(nom_dic);
    printf("¿Que quieres realizar?\n1-Alta entidad\n2-Baja "
           "entidad\n3-Modificacion entidad\n4-Alta atributo\n5-Baja "
           "atributo\n6-Modificacion atributo\n7-Muestra diccionario\n8-Salir");
    scanf("\n%d", &opmen);
    while (opmen > 0 && opmen < 8) {
      switch (opmen) {
      case 1:
        e = captura_entidad();
        alta_entidad(nom_dic, e);
        break;
      case 2:
        printf("¿Que entidad deseas eliminar?");
        e = captura_entidad();
        baja_entidad(nom_dic, e);
        break;
      case 3:
        printf("¿Que entidad deseas modificar?");
        baja = captura_entidad();
        printf("¿Como deseas que se llame ahora?");
        alta = captura_entidad();
        modifica_entidad(nom_dic, baja, alta);
        break;
      case 4:
        printf("¿de que entidad quieres el atributo?:");
        scanf("\n%[^\n]", nom_ent);
        a = captura_atributo();
        inserta_atributo(nom_dic, nom_ent, a);
        break;
      case 5:
        printf("¿de que entidad quieres el eliminar el atributo?:");
        scanf("\n%[^\n]", nom_ent);
        printf("¿que atributo quieres eliminar?:");
        scanf("\n%[^\n]", nom_at);
        elimina_atributo(nom_dic, nom_ent, nom_at);
        break;
      case 6:
        printf("¿de que entidad quieres modificar el atributo?:");
        scanf("\n%[^\n]", nom_ent);
        printf("¿que atributo quieres modificar?:");
        scanf("\n%[^\n]", nom_at);
        printf("¿Como quieres que se llame ahora?:");
        altaat = captura_atributo();
        modifica_atr(nom_dic, nom_ent, nom_at, altaat);
        break;
      case 7:
        imprime_diccionario(nom_dic);
        break;
      }
      printf(
          "¿Que quieres realizar?\n1-Alta entidad\n2-Baja "
          "entidad\n3-Modificacion entidad\n4-Alta atributo\n5-Baja "
          "atributo\n6-Modificacion atributo\n7-Muestra diccionario\n8-Salir");
      scanf("\n%d", &opmen);
    }
    break;
  case 2:
    printf("¿Que quieres realizar?\n1-Alta entidad\n2-Baja "
           "entidad\n3-Modificacion entidad\n4-Alta atributo\n5-Baja "
           "atributo\n6-Modificacion atributo\n7-Muestra diccionario\n8-Salir");
    scanf("\n%d", &opmen);
    while (opmen > 0 && opmen < 8) {
      switch (opmen) {
      case 1:
        e = captura_entidad();
        alta_entidad(nom_dic, e);
        break;
      case 2:
        printf("¿Que entidad deseas eliminar?");
        e = captura_entidad();
        baja_entidad(nom_dic, e);
        break;
      case 3:
        printf("¿Que entidad deseas modificar?");
        baja = captura_entidad();
        printf("¿Como deseas que se llame ahora?");
        alta = captura_entidad();
        modifica_entidad(nom_dic, baja, alta);
        break;
      case 4:
        printf("¿de que entidad quieres el atributo?:");
        scanf("\n%[^\n]", nom_ent);
        a = captura_atributo();
        inserta_atributo(nom_dic, nom_ent, a);
        break;
      case 5:
        printf("¿de que entidad quieres el eliminar el atributo?:");
        scanf("\n%[^\n]", nom_ent);
        printf("¿que atributo quieres eliminar?:");
        scanf("\n%[^\n]", nom_at);
        elimina_atributo(nom_dic, nom_ent, nom_at);
        break;
      case 6:
        printf("¿de que entidad quieres modificar el atributo?:");
        scanf("\n%[^\n]", nom_ent);
        printf("¿que atributo quieres modificar?:");
        scanf("\n%[^\n]", nom_at);
        printf("¿Como quieres que se llame ahora?:");
        altaat = captura_atributo();
        modifica_atr(nom_dic, nom_ent, nom_at, altaat);
        break;
      case 7:
        imprime_diccionario(nom_dic);
        break;
      }
      printf(
          "¿Que quieres realizar?\n1-Alta entidad\n2-Baja "
          "entidad\n3-Modificacion entidad\n4-Alta atributo\n5-Baja "
          "atributo\n6-Modificacion atributo\n7-Muestra diccionario\n8-Salir");
      scanf("\n%d", &opmen);
    }
    break;
  }
}

TEntidad captura_entidad() {
  TEntidad e;

  printf("Nombre de la Entidad:");
  scanf("\n%[^\n],", e.nombre);
  fflush(stdin);
  e.dir = e.ptr_atr = e.sig_ent = -1L;
  return e;
}
TAtributo captura_atributo() {
  TAtributo a;

  printf("Nombre:");
  scanf("\n%[^\n],", a.nombre);
  printf("Dame el tipo: ");
  scanf("\n%d", &(a.tipo));
  printf("");
  scanf("");
  switch (a.tipo) {
  case 1:
    a.tam = sizeof(int);
    break;
  case 2:
    a.tam = sizeof(char);
    break;
  case 3:
    printf("tamaño de cadena:");
    scanf("%d", &a.tam);
    break;
  case 4:
    a.tam = sizeof(float);
    break;
  }
  fflush(stdin);
  a.dir = a.sig_atr = -1L;
  return a;
}
void imprime_entidad(TEntidad e) {
  printf("Nombre: %s\n", e.nombre);
  printf("Dir: %ld\n", e.dir);
  printf("Sig Ent:%ld\n", e.sig_ent);
  printf("Ptr Atr:%ld", e.ptr_atr);
}
void imprime_atributo(TAtributo a) {
  printf("Nombre: %s\n", a.nombre);
  printf("Dir: %ld\n", a.dir);
  printf("Sig Ent:%ld\n", a.sig_atr);
  printf("Ptr Atr:%ld", a.sig_ent);
}

void crea_dicc(char nom_arch[]) {
  long cab = -1L;
  FILE *f;

  f = fopen(nom_arch, "wb");
  if (f) {
    fwrite(&cab, sizeof(long), 1, f);
    fclose(f);
  } else
    printf("No se pudo crear el diccionario\n");
}

void alta_entidad(char nom_ach[], TEntidad e) {
  FILE *f;
  long cab;
  TEntidad aux, ant;

  f = fopen(nom_ach, "rb+");
  if (!f) {
    printf("No se pudo abrir el diccionario");
    return;
  }
  fread(&cab, sizeof(long), 1, f);
  fseek(f, 0, SEEK_END); // Mover al fin del archivo
  e.dir = ftell(f);
  if (cab == -1) {
    cab = e.dir;
    fseek(f, 0, SEEK_SET);            // Mover al inicio del archivo
    fwrite(&cab, sizeof(long), 1, f); // Actualiza cabecera en el archivo.
  } else {
    fseek(f, cab, SEEK_SET);
    fread(&aux, sizeof(TEntidad), 1, f);
    if (strcmp(aux.nombre, e.nombre) > 0) {
      e.sig_ent = cab;
      cab = e.dir;
      fseek(f, 0, SEEK_SET);            // Mover al inicio del archivo
      fwrite(&cab, sizeof(long), 1, f); // Actualiza la cabecera en el archivo
    } else {
      while (strcmp(aux.nombre, e.nombre) < 0 && aux.sig_ent != -1) {
        ant = aux;
        fseek(f, aux.sig_ent, SEEK_SET);
        fread(&aux, sizeof(TEntidad), 1, f);
      }
      if (strcmp(aux.nombre, e.nombre) > 0) {
        e.sig_ent = aux.dir;
        ant.sig_ent = e.dir;
        fseek(f, ant.dir, SEEK_SET);
        fwrite(&ant, sizeof(TEntidad), 1, f);
      } else {
        aux.sig_ent = e.dir;
        fseek(f, aux.dir, SEEK_SET);
        fwrite(&aux, sizeof(TEntidad), 1, f);
      }
    }
  }
  fseek(f, e.dir, SEEK_SET);
  fwrite(&e, sizeof(TEntidad), 1, f);

  fclose(f);
}

void imprime_diccionario(char nom_arch[]) {
  FILE *f;
  long pos, cab;
  TEntidad aux;
  TAtributo aux_a;

  f = fopen(nom_arch, "rb");
  if (f == NULL) {
    printf("No se pudo abrir el archivo\n");
    return;
  }
  fread(&cab, sizeof(long), 1, f);
  if (cab != -1) {
    while (cab != -1) {
      fseek(f, cab, SEEK_SET);
      fread(&aux, sizeof(TEntidad), 1, f);
      imprime_entidad(aux);
      pos = aux.ptr_atr;
      while (pos != -1L) {
        fseek(f, pos, SEEK_SET);
        fread(&aux_a, sizeof(TAtributo), 1, f);
        imprime_atributo(aux_a);
        pos = aux_a.sig_atr;
      }
      cab = aux.sig_ent;
    }
  } else {
    printf("El diccionario esta vacio\n");
    return;
  }
  fclose(f);
}

void baja_entidad(char nom_ach[], TEntidad e) {
  FILE *f;
  long cab;
  TEntidad aux, ant;

  f = fopen(nom_ach, "rb+");
  if (!f) {
    printf("No se pudo abrir el diccionario");
    return;
  }
  fread(&cab, sizeof(long), 1, f);
  fseek(f, 0, SEEK_END); // Mover al fin del archivo
  e.dir = ftell(f);
  if (cab == -1) {
    printf("ERROR:esta vacia");
    return;
  } else {
    fseek(f, cab, SEEK_SET);
    fread(&aux, sizeof(TEntidad), 1, f);
    if (strcmp(aux.nombre, e.nombre) == 0) {
      cab = aux.sig_ent;
      fseek(f, 0, SEEK_SET);            // Mover al inicio del archivo
      fwrite(&cab, sizeof(long), 1, f); // Actualiza la cabecera en el archivo
    } else {
      while (strcmp(aux.nombre, e.nombre) != 0 && aux.sig_ent != -1) {
        ant = aux;
        fseek(f, aux.sig_ent, SEEK_SET);
        fread(&aux, sizeof(TEntidad), 1, f);
      }
      if (strcmp(aux.nombre, e.nombre) == 0) {
        ant.sig_ent = aux.sig_ent;
        fseek(f, ant.dir, SEEK_SET);
        fwrite(&ant, sizeof(TEntidad), 1, f);
      } else {
        printf("ERROR: no se encontro");
      }
    }
    fclose(f);
  }
}

void modifica_entidad(char nom_ach[], TEntidad e_baja, TEntidad e_alta) {
  baja_entidad(nom_ach, e_baja);
  alta_entidad(nom_ach, e_alta);
}

void inserta_atributo(char nom_dic[], char nom_ent[], TAtributo a) {
  FILE *f;
  long cab;
  TEntidad e;
  TAtributo aux_a;
  int enc = 0;

  f = fopen(nom_dic, "rb+");
  if (f == NULL) {
    printf("No se pudo abrir el diccionario");
    return;
  }
  fread(&cab, sizeof(long), 1, f);
  while (cab != -1L && !enc) {
    fseek(f, cab, SEEK_SET);
    fread(&e, sizeof(TEntidad), 1, f);
    if (strcmp(e.nombre, nom_ent) == 0)
      enc = 1;
    else
      cab = e.sig_ent;
  }
  if (enc) {
    fseek(f, 0, SEEK_END);
    a.dir = ftell(f);
    if (e.ptr_atr == -1L) {
      e.ptr_atr = a.dir;
      fseek(f, e.dir, SEEK_SET);
      fwrite(&e, sizeof(TEntidad), 1, f);
    } else {
      cab = e.ptr_atr;
      do {
        fseek(f, cab, SEEK_SET);
        fread(&aux_a, sizeof(TAtributo), 1, f);
        if (aux_a.sig_atr != -1L)
          cab = aux_a.sig_atr;
      } while (aux_a.sig_atr != -1L);
      aux_a.sig_atr = a.dir;
      fseek(f, aux_a.dir, SEEK_SET);
      fwrite(&aux_a, sizeof(TAtributo), 1, f);
    }
    fseek(f, a.dir, SEEK_SET);
    fwrite(&a, sizeof(TAtributo), 1, f);
  }
  fclose(f);
}

void elimina_atributo(char nom_dic[], char nom_ent[], char nom_atr[]) {
  TEntidad e;
  TAtributo aux, ant;
  long cab, pos;
  FILE *f;
  int enc = 0;

  f = fopen(nom_dic, "rb+");
  if (f == NULL) {
    printf("ERROR: no existe diccionario");
    return;
  }
  fread(&cab, sizeof(long), 1, f);
  while (cab != -1L && !enc) {
    fseek(f, cab, SEEK_SET);
    fread(&e, sizeof(TEntidad), 1, f);
    if (strcmp(e.nombre, nom_ent) == 0)
      enc = 1;
    else {
      cab = e.sig_ent;
    }
  }
  if (enc) {
    pos = e.ptr_atr;
    enc = 0;
    while (pos != -1L && !enc) {
      fseek(f, pos, SEEK_SET);
      fread(&aux, sizeof(TAtributo), 1, f);
      if (strcmp(aux.nombre, nom_atr) == 0)
        enc = 1;
      else {
        ant = aux;
        pos = aux.sig_atr;
      }
    }
    if (enc) {
      if (pos == e.ptr_atr) {
        e.ptr_atr = aux.sig_atr;
        fseek(f, e.dir, SEEK_SET);
        fwrite(&e, sizeof(TEntidad), 1, f);
      } else {
        ant.sig_atr = aux.sig_atr;
        fseek(f, ant.dir, SEEK_SET);
        fwrite(&ant, sizeof(TAtributo), 1, f);
      }
    } else
      printf("ATRIBUTO NO ENCONTRADO");
  } else
    printf("ENTIDAD NO ENCONTRADA");
  fclose(f);
}

void modifica_atr(char nom_ach[], char nom_ent[], char nom_atr_baja[],
                  TAtributo alta_a) {
  elimina_atributo(nom_ach, nom_ent, nom_atr_baja);
  inserta_atributo(nom_ach, nom_ent, alta_a);
}

TBloque crea_bloque(TNodoE *e) {
  TNodoA *a;
  TBloque b;
  b.desp = 0;
  b.tam = 0;
  a = e->aba;
  while (a != NULL) {
    if (a->a.clave == 1)
      b.desp = b.tam;
    b.tam += a->a.tam;
    a = a->sig;
  }
  b.tam += sizeof(long) * 2;
  b.tam = malloc(b.tam);
  *((long *)(b.bloque + (b.tam - (sizeof(long) * 2)))) = -1L;
  *((long *)(b.bloque + (b.tam - sizeof(long)))) = -1L;
  return b;
}

void captura_bloque(TNodoE *e, TBloque b) {
  TNodoA *a;
  int d = 0;

  printf("%s:\n", e->e.nombre);
  a = e->aba;
  while (a != NULL) {
    printf("%s:", a->a.nombre);
    // 1-int 2-char 3-cadena 4-flat//
    switch (a->a.tipo) {
    case 1:
      scanf("%d", (int *)(b.bloque + d));
      break;
    case 2:
      scanf("%c", (char *)(b.bloque + d));
      break;
    case 3:
      scanf("%[^\n]", (char *)(b.bloque + d));
      break;
    case 4:
      scanf("%f", (float *)(b.bloque + d));
      break;
    }
    d += a->a.tam;
    a = a->sig;
  }
}