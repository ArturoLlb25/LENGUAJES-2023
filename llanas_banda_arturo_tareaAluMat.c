#include <stdio.h>
#include <stdlib.h>


typedef struct{
    int clave;
    char nombre[50];
    int num_cred;
}TMateria;

typedef struct{
    int clave;
    char nombre[50];
    int gene;
    char carrera[50];
}TAlumno;

typedef struct{
    int tipo;
    void *info;
}TInfo;

int capturaDatos(TInfo *datos,int n);
void guardarDatos(TInfo *datos, int n);
void leerDatos(TInfo *datos, int n);

int main(){
    TInfo *datos;
    int n;

    printf("Cuantos alumnos/materias desea ingresar?: ");
    scanf("%d", &n);
    fflush(stdin);
    datos = (TInfo*) malloc(sizeof(TInfo)*n);
    if(capturaDatos(datos,n) == 0){
        printf("No se pudieron capturar los datos correctamente.\n");
        return 0;
    }

    guardarDatos(datos, n);

    leerDatos(datos, n);

    printf("\n");
    return 0;
}

int capturaDatos(TInfo *datos,int n){
    int i, tipo;
    TMateria *materia;
    TAlumno *alumno;

    for(i=0; i<n; i++){
        fflush(stdin);
        printf("Que tipo de datos desea ingresar? (1=Materia, 2=Alumno): ");
        scanf("%d", &tipo);
        fflush(stdin);
        if(tipo != 1 && tipo != 2){
            printf("Debe ingresar 1 o 2 para seleccionar el tipo de datos.\n");
            return 0;
        }

        datos[i].tipo = tipo;
        if(datos[i].tipo == 1){
            fflush(stdin);
            materia = (TMateria*) malloc(sizeof(TMateria));
            printf("Clave de la materia: ");
            scanf("%d", &materia->clave);
            fflush(stdin);
            printf("Nombre de la materia: ");
            scanf("%s", materia->nombre);
            fflush(stdin);
            printf("Numero de creditos: ");
            scanf("%d", &materia->num_cred);
            fflush(stdin);
            datos[i].info = materia;
        }
        else{
            alumno = (TAlumno*) malloc(sizeof(TAlumno));
            printf("Clave del alumno: ");
            scanf("%d", &alumno->clave);
            fflush(stdin);
            printf("Nombre del alumno: ");
            scanf("%s", alumno->nombre);
            fflush(stdin);
            printf("Generacion: ");
            scanf("%d", &alumno->gene);
            fflush(stdin);
            printf("Carrera: ");
            scanf("%s", alumno->carrera);
            fflush(stdin);
            datos[i].info = alumno;
        }
    }
    return 1;
}

void guardarDatos(TInfo *datos, int n){
    FILE *archivo;
    int i;
    TMateria *materia;
    TAlumno *alumno;

    archivo = fopen("datos.bin", "wb");
    if(archivo == NULL){
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    for(i=0; i<n; i++){
        if(datos[i].tipo == 1){
            materia = (TMateria*) datos[i].info;
            fwrite(materia, sizeof(TMateria), 1, archivo);
        }
        else{
            alumno = (TAlumno*) datos[i].info;
            fwrite(alumno, sizeof(TAlumno), 1, archivo);
        }
    }
    fclose(archivo);
}

void leerDatos(TInfo *datos, int n){
    FILE *archivo;
    int i;
    TMateria *materia;
    TAlumno *alumno;

    archivo = fopen("datos.bin", "rb");
    if(archivo == NULL){
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    for(i=0; i<n; i++){
        if(datos[i].tipo == 1){
            materia = (TMateria*) malloc(sizeof(TMateria));
            fread(materia, sizeof(TMateria), 1, archivo);
            printf("Materia: %s, clave: %d, creditos: %d\n", materia->nombre, materia->clave, materia->num_cred);
            free(materia);
        }
        else{
            alumno = (TAlumno*) malloc(sizeof(TAlumno));
            fread(alumno, sizeof(TAlumno), 1, archivo);
            printf("Alumno: %s, clave: %d, generacion: %d, carrera: %s\n", alumno->nombre, alumno->clave, alumno->gene, alumno->carrera);
            free(alumno);
        }
    }
    fclose(archivo);
}
