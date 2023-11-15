#include <stdio.h>
#include <stdlib.h>
#include<wchar.h>
#include<locale.h>
#include<time.h>
#include<unistd.h>
#include<string.h>
#include<conio.h>
#include <ctype.h>
#include <windows.h>

struct Libros{
    int ID;
    char nombre[50];
    int cant;
    char editorial[50];
    int duplicado; //- 1 nada; 0 duplicado en inicio; 1 duplicado en final;

    struct Libros *sig;
};

typedef struct Libros *puntero;
puntero Inicio = NULL;

int identificador = 1;

void Menu(){
    puts("Biblioteca: \n\n");
    puts("Menú: ");
    puts("1. Agregar/Modificar libro");
    puts("2. Ver libros");
    puts("3. Buscar libro");
    puts("4. Vender libro");
    puts("5. Duplicar libro");
    puts("6. Salir");
    puts("------------------------");
    printf("Elegir opción: ");
}

int vacia(struct Libros *ptrActual)
{
    if (ptrActual == NULL)
        return 1;
    else
        return 0;
}

int cantidadLibros(struct Libros *actual){
    int cant = 1;
    while(actual!=NULL){
        cant = cant + 1;

        actual = actual->sig;
    }

    return cant;
}

int existeID(int ID) {
    struct Libros *actual = Inicio;

    while (actual != NULL) {
        if (actual->ID == ID) {
            return 1;  //
        }
        actual = actual->sig;
    }

    return 0;
}

void eliminarLibro(int ID) {
    struct Libros *actual = Inicio;
    struct Libros *anterior = NULL;

    while (actual != NULL && actual->ID != ID) {
        anterior = actual;
        actual = actual->sig;
    }

    if (anterior == NULL) {
        Inicio = actual->sig;
        identificador = identificador - 1;
    } else {
        anterior->sig = actual->sig;
        identificador = identificador - 1;
    }
    free(actual);
}

void agregarLibro(){
    struct Libros *nuevo,*actual,*anterior;
    nuevo = malloc(sizeof(struct Libros));

    fflush(stdin);
    printf("Ingrese el nombre del libro: ");
    gets(nuevo->nombre);
    fflush(stdin);
    printf("Ingrese la editorial del libro: ");
    gets(nuevo->editorial);
    printf("Ingrese la cantidad de libros: ");
    scanf("%d",&nuevo->cant);

    actual = Inicio;
    anterior = NULL;

    while (actual != NULL && strcmp(nuevo->editorial, actual->editorial) > 0) {
        anterior = actual;
        actual = actual->sig;
    }

    if (anterior == NULL) {
        nuevo->sig = Inicio;
        Inicio = nuevo;
    } else {
        nuevo->sig = actual;
        anterior->sig = nuevo;
    }

    nuevo->ID = identificador;
    nuevo->duplicado = -1;
    identificador = identificador + 1;

    system("cls");
    puts("--------------------------");
    puts("¡Libro agregado con éxito!");
    puts("--------------------------");
    system("pause");
}

void modificarLibro(){
    struct Libros *actual = Inicio;

    char nombreNuevo[50],editorialNueva[50];
    int op,ID,cantidadNueva;

    if(!vacia(Inicio)){
        printf("Ingrese el ID del libro que desea encontrar: ");
        scanf("%d",&ID);
        if(existeID(ID)){
            while (actual->ID != ID && actual != NULL) {
                actual = actual->sig;
            }

            system("cls");
            puts("Libro encontrado: \n");
            printf("Nombre: %s\n", actual->nombre);
            printf("Editorial: %s\n", actual->editorial);
            printf("Cantidad: %d\n", actual->cant);
            printf("ID: %d\n", actual->ID);
            printf("---------------------------\n\n");

            puts("¿Qué desea modificar?\n1. Nombre del libro\n2. Nombre de la editorial\n3. Cantidad de libros");
            puts("------------------------------------");
            printf("Elegir opción: ");
            scanf("%d",&op);
            while(op>3 || op<1){
                puts("------------------------------------");
                puts("¡Opción no valida, intente de nuevo!");
                puts("------------------------------------");
                printf("Elegir opción: ");
                scanf("%d",&op);
            }
            switch(op){
                case 1:
                    system("cls");
                    fflush(stdin);
                    printf("Ingrese el nuevo nombre del libro: ");
                    gets(nombreNuevo);

                    strcpy(actual->nombre,nombreNuevo);
                    system("cls");
                    puts("-------------------------------------");
                    puts("¡Nombre del libro cambiado con éxito!");
                    puts("-------------------------------------");
                    system("pause");
                    break;
                case 2:
                    system("cls");
                    fflush(stdin);
                    printf("Ingrese el nuevo nombre de la editorial: ");
                    gets(editorialNueva);

                    strcpy(actual->editorial,editorialNueva);
                    system("cls");
                    puts("-------------------------------------------");
                    puts("¡Nombre de la editorial cambiado con éxito!");
                    puts("-------------------------------------------");
                    system("pause");
                    break;
                case 3:
                    system("cls");
                    printf("Ingrese la nueva cantidad de libros: ");
                    scanf("%d",&cantidadNueva);

                    actual->cant = cantidadNueva;
                    system("cls");
                    puts("-------------------");
                    puts("¡Stock actualizado!");
                    puts("-------------------");
                    system("pause");
                    break;
            }
        }else{
            system("cls");
            puts("-----------------------------------------------");
            printf("¡No se encontró un libro con el ID '%d'!\n",ID);
            puts("-----------------------------------------------");
            system("pause");
        }
    }else{
        system("cls");
        puts("---------------------");
        puts("¡La lista está vacia!");
        puts("---------------------");
        system("pause");
    }
}

void verLibros(){
    struct Libros *actual = Inicio;

    if(!vacia(Inicio)){
        puts("Libros en posesión: \n");
        while (actual != NULL) {
            printf("Nombre: %s\n", actual->nombre);
            printf("Editorial: %s\n", actual->editorial);
            printf("Cantidad: %d\n", actual->cant);
            printf("ID: %d\n", actual->ID);
            printf("---------------------------\n");
            actual = actual->sig;
        }
        system("pause");
    }else{
        puts("---------------------");
        puts("¡La lista está vacia!");
        puts("---------------------");
        system("pause");
    }

}

void buscarLibro(){
    struct Libros *actual = Inicio;

    int ID;

    if(!vacia(Inicio)){
        printf("Ingrese el ID del libro que desea encontrar: ");
        scanf("%d",&ID);
        if(existeID(ID)){
            while (actual->ID != ID && actual!=NULL) {
                actual = actual->sig;
            }

            system("cls");
            puts("Libro encontrado: \n");
            printf("Nombre: %s\n", actual->nombre);
            printf("Editorial: %s\n", actual->editorial);
            printf("Cantidad: %d\n", actual->cant);
            printf("ID: %d\n", actual->ID);
            printf("---------------------------\n");
            system("pause");
        }else{
            system("cls");
            puts("---------------------");
            printf("¡No se encontró un libro con el ID '%d'!\n",ID);
            puts("---------------------");
            system("pause");
        }
    }else{
        puts("---------------------");
        puts("¡La lista está vacia!");
        puts("---------------------");
        system("pause");
    }
}

void venderLibro(){
    struct Libros *actual = Inicio;

    int ID,cant;

    if(!vacia(Inicio)){
        printf("Ingrese el ID del libro que desea vender: ");
        scanf("%d",&ID);
        if(existeID(ID)){
            while (actual != NULL) {
                if (actual->ID == ID) {
                    break;
                }
                actual = actual->sig;
            }

            system("cls");
            puts("Libro encontrado: \n");
            printf("Nombre: %s\n", actual->nombre);
            printf("Editorial: %s\n", actual->editorial);
            printf("Cantidad: %d\n", actual->cant);
            printf("ID: %d\n", actual->ID);
            printf("---------------------------\n\n");

            puts("\n¿Cuantos desea vender?");
            printf("Cantidad: ");
            scanf("%d",&cant);
            while(cant>actual->cant){
                    puts("--------------------------------------");
                    puts("¡Opción no valida, stock insuficiente!");
                    puts("--------------------------------------");
                    printf("Elegir opción: ");
                    scanf("%d",&cant);
            }

            actual->cant = actual->cant - cant;
            system("cls");
            puts("---------------------------------------------");
            printf("¡Libro '%s' vendido con éxito!\n",actual->nombre);
            puts("---------------------------------------------");
            system("pause");

            if(actual->cant == 0){
                system("cls");
                puts("-----------------------------------------------------------");
                printf("¡Nos hemos quedado sin stock del libro '%s'!\n",actual->nombre);
                puts("-----------------------------------------------------------");
                printf("¡Libro '%s' eliminado de la biblioteca!\n",actual->nombre);
                puts("-----------------------------------------------------------");
                system("pause");
                eliminarLibro(ID);
            }
        }else{
            system("cls");
            puts("-----------------------------------------------");
            printf("¡No se encontró un libro con el ID '%d'!\n",ID);
            puts("-----------------------------------------------");
            system("pause");
        }
    }else{
        puts("---------------------");
        puts("¡La lista está vacia!");
        puts("---------------------");
        system("pause");
    }
}

void duplicarLibro(){
    struct Libros *actual = Inicio;
    struct Libros *anterior = NULL;
    struct Libros *nuevo;

    int ID,op;

    if(!vacia(Inicio)){
        printf("Ingrese el ID del libro que desea encontrar: ");
        scanf("%d",&ID);
        if(existeID(ID)){
            while(actual->ID != ID) {
                anterior = actual;
                actual = actual->sig;
            }

            puts("Libro encontrado: \n");
            printf("Nombre: %s\n", actual->nombre);
            printf("Editorial: %s\n", actual->editorial);
            printf("Cantidad: %d\n", actual->cant);
            printf("ID: %d\n", actual->ID);
            printf("---------------------------\n\n");

            if(actual->duplicado == -1){
                puts("¿Donde desea insertarlo?\n1.Inicio\n2.Final");
                scanf("%d",&op);
                while(op>2 || op<1){
                        puts("------------------------------------");
                        puts("¡Opción no valida, intente de nuevo!");
                        puts("------------------------------------");
                        printf("Elegir opción: ");
                        scanf("%d",&op);
                }
                switch(op){
                case 1:
                        nuevo = malloc(sizeof(struct Libros));

                        strcpy(nuevo->nombre,actual->nombre);
                        strcpy(nuevo->editorial,actual->editorial);

                        nuevo->cant = actual->cant;

                        nuevo->ID = identificador;
                        identificador = identificador + 1;

                        nuevo->duplicado = 0;

                        nuevo->sig = Inicio;
                        Inicio = nuevo;

                        system("cls");
                        puts("----------------------------------------");
                        puts("¡Libro insertado en el inicio con éxito!");
                        puts("----------------------------------------");
                        system("pause");
                    break;
                case 2:
                        nuevo = malloc(sizeof(struct Libros));

                        strcpy(nuevo->nombre,actual->nombre);
                        strcpy(nuevo->editorial,actual->editorial);

                        nuevo->cant = actual->cant;

                        nuevo->ID = identificador;
                        identificador = identificador + 1;

                        nuevo->duplicado = 1;

                        anterior->sig = nuevo;
                        nuevo->sig = NULL;

                        system("cls");
                        puts("---------------------------------------");
                        puts("¡Libro insertado en el final con éxito!");
                        puts("---------------------------------------");
                        system("pause");
                    break;
                }
            }else if(actual->duplicado == 0){
                        struct Libros *nuevo, *anterior = NULL;
                        nuevo = malloc(sizeof(struct Libros));

                        strcpy(nuevo->nombre,actual->nombre);
                        strcpy(nuevo->editorial,actual->editorial);

                        nuevo->cant = actual->cant;

                        nuevo->ID = identificador;
                        identificador = identificador + 1;

                        nuevo->duplicado = 1;

                        anterior->sig = nuevo;
                        nuevo->sig = NULL;

                        system("cls");
                        puts("------------------------------------------------------------------------------");
                        puts("¡El libro ya había sido duplicado en el inicio ahora se insertará en el final!");
                        puts("------------------------------------------------------------------------------");
                        system("pause");
            }else if(actual->duplicado == 1){
                        struct Libros *nuevo;
                        nuevo = malloc(sizeof(struct Libros));

                        strcpy(nuevo->nombre,actual->nombre);
                        strcpy(nuevo->editorial,actual->editorial);

                        nuevo->cant = actual->cant;

                        nuevo->ID = identificador;
                        identificador = identificador + 1;

                        nuevo->duplicado = 0;

                        nuevo->sig = Inicio;
                        Inicio = nuevo;

                        system("cls");
                        puts("------------------------------------------------------------------------------");
                        puts("¡El libro ya había sido duplicado en el final ahora se insertará en el inicio!");
                        puts("------------------------------------------------------------------------------");
            }
        }else{
            system("cls");
            puts("-----------------------------------------------");
            printf("¡No se encontró un libro con el ID '%d'!\n",ID);
            puts("-----------------------------------------------");
            system("pause");
        }
    }else{
        puts("---------------------");
        puts("¡La lista está vacia!");
        puts("---------------------");
        system("pause");
    }
}

int main()
{
    int menu,salir,case1;

    setlocale(LC_ALL, "");
    srand(time(NULL));

    do{
        system("cls");
        Menu();
        scanf("%d",&menu);
        while(menu>6 || menu<1){
            puts("------------------------------------");
            puts("¡Opción no valida, intente de nuevo!");
            puts("------------------------------------");
            printf("Elegir opción: ");
            scanf("%d",&menu);
        }
        switch(menu){
        case 1:
            system("cls");
            puts("¿Qué desea hacer?\n1.Agregar Libro\n2.Modificar libro");
            puts("------------------------------------");
            printf("Elegir opción: ");
            scanf("%d",&case1);
            while(case1>2 || case1<1){
                puts("------------------------------------");
                puts("¡Opción no valida, intente de nuevo!");
                puts("------------------------------------");
                printf("Elegir opción: ");
                scanf("%d",&case1);
            }
            switch(case1){
                case 1:
                    if(cantidadLibros(Inicio)<=10){
                        system("cls");
                        agregarLibro();
                    }else{
                        system("cls");
                        puts("-----------------------------------------");
                        puts("¡Se ha excedido el límite de libros (10)!");
                        puts("-----------------------------------------");
                        system("pause");
                    }
                    break;
                case 2:
                    system("cls");
                    modificarLibro();
                    break;
            }
            break;
        case 2:
            system("cls");
            verLibros();
            break;
        case 3:
            system("cls");
            buscarLibro();
            break;
        case 4:
            if(cantidadLibros(Inicio)>=5){
                system("cls");
                venderLibro();
            }else{
                system("cls");
                puts("----------------------------------------------------------------");
                puts("¡Se debe agregar al menos (5) libros para acceder a esta opción!");
                puts("----------------------------------------------------------------");
                system("pause");
            }
            break;
        case 5:
            if(cantidadLibros(Inicio)>=5){
                system("cls");
                duplicarLibro();
            }else{
                system("cls");
                puts("----------------------------------------------------------------");
                puts("¡Se debe agregar al menos (5) libros para acceder a esta opción!");
                puts("----------------------------------------------------------------");
                system("pause");
            }
            break;
        case 6:
            system("cls");
                puts("¿Está seguro que desea salir?\n1.Si\n2.No");
                puts("-----------------");
                printf("Elegir opción: ");
                scanf("%d",&salir);
                while(salir>2 || salir<1){
                    puts("------------------------------------");
                    puts("¡Opción no valida, intente de nuevo!");
                    puts("------------------------------------");
                    printf("Elegir opción: ");
                    scanf("%d",&salir);
                }
                switch(salir){
                case 1:
                    system("cls");
                    puts("Saliendo del programa...");
                    sleep(2);
                    break;
                case 2:
                    system("cls");
                    puts("Volviendo al menú...");
                    sleep(2);
                    menu=1;
                    break;
                }
                break;
        }
    }while(menu!=6);
    return 0;
}
