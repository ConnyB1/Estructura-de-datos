#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Alumno
{
    char *Apaterno;
    char *AMaterno;
    char *nombre;
    int carrera;
} Alumno;

typedef struct Nodo
{
    Alumno alumno;
    struct Nodo *Siguiente;
    struct Nodo *anterior;
} Nodo;

typedef struct Lista
{
    Nodo *Cabeza;
} Lista;

void InsertarEnPosiEspec(Lista *lista, Alumno *alumno, int posicion);
void EliminarElemento(Lista *lista, int posicion);
Alumno* BuscarElemento(Lista *lista, char* nombre);
void RecorrerLista(Lista *lista);
void OrdenarLista(Lista *lista);
void InsertarOrdenado(Lista *lista, Alumno *alumno);
int ListaVacia(Lista *lista);
int CantidadElementos(Lista *lista);
Nodo* CrearNodo (Alumno *alumno);
void InsertarAlFinal(Lista* lista, Alumno *alumno);

int main()
{
    Lista lista;
    lista.Cabeza = NULL;
    Alumno alumno1 = {"Lopez", "Gomez", "Juan", 1};
    Alumno alumno2 = {"Perez", "Gonzalez", "Maria", 2};
    
    InsertarAlFinal(&lista, &alumno1);
    InsertarAlFinal(&lista, &alumno2);

    RecorrerLista(&lista);

    printf("insetando alumno1 en el lugar del segundo: \n");
    InsertarEnPosiEspec(&lista, &alumno1, 2);

    Alumno *alumnoEncontrado = BuscarElemento(&lista, "Nombre1");

    RecorrerLista(&lista);
    printf("Ordenando lista: \n");
    OrdenarLista(&lista);

    if (ListaVacia(&lista)) 
    {
        printf("La lista está vacía\n");
    } else {
        printf("La lista no está vacía\n");
    }

    int cantidad = CantidadElementos(&lista);
    printf("La cantidad de elementos en la lista es: %d\n", cantidad);

    EliminarElemento(&lista, 1);

    return 0;
}

Nodo* CrearNodo (Alumno *alumno)
{
    Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));
    nodo->alumno.Apaterno = strdup(alumno->Apaterno);
    nodo->alumno.AMaterno = strdup(alumno->AMaterno);
    nodo->alumno.nombre = strdup(alumno->nombre);
    nodo->alumno.carrera = alumno->carrera;

    nodo->Siguiente = NULL;
    return nodo;
}

void InsertarAlFinal(Lista* lista, Alumno *alumno)
{
    Nodo* nodo = CrearNodo(alumno);
    if(lista->Cabeza == NULL)
    {
        lista->Cabeza = nodo;
    }
    else 
    {
        Nodo* puntero = lista->Cabeza;
        while(puntero->Siguiente)
        {
            puntero=puntero->Siguiente;
        }
        puntero->Siguiente=nodo;
    }
}


void InsertarEnPosiEspec(Lista *lista, Alumno *alumno, int posicion)
{
    Nodo* nodo = CrearNodo(alumno);

    if (posicion <= 0) 
    {
        printf("La posición debe ser un número positivo mayor que cero.\n");
        return;
    }

    if (posicion == 1 || lista->Cabeza == NULL) 
    {
        nodo->Siguiente = lista->Cabeza;
        lista->Cabeza = nodo;
        return;
    }

    Nodo* puntero = lista->Cabeza;
    int i = 1;
    while (puntero && i < posicion - 1) 
    {
        puntero = puntero->Siguiente;
        i++;
    }

    if (!puntero) 
    {
        printf("La posición excede el tamaño de la lista. Se insertará al final.\n");
        InsertarAlFinal(lista, alumno);
        return;
    }

    nodo->Siguiente = puntero->Siguiente;
    puntero->Siguiente = nodo;
}

void EliminarElemento(Lista *lista, int posicion)
{
    if (posicion <= 0) 
    {
        printf("La posición debe ser un número positivo mayor que cero.\n");
        return;
    }

    Nodo* temp = lista->Cabeza;

    if (posicion == 1) 
    {
        if (temp == NULL) 
        {
            printf("La lista está vacía, no se puede eliminar.\n");
            return;
        }
        lista->Cabeza = temp->Siguiente;
        free(temp);
        printf("Elemento en la posición 1 eliminado exitosamente.\n");
        return;
    }

    int contador = 1;
    Nodo* previo = NULL;
    while (temp != NULL && contador != posicion) 
    {
        previo = temp;
        temp = temp->Siguiente;
        contador++;
    }

    if (temp == NULL) 
    {
        printf("La posición excede el tamaño de la lista, no se puede eliminar.\n");
        return;
    }

    previo->Siguiente = temp->Siguiente;
    free(temp);
    printf("Elemento en la posición %d eliminado exitosamente.\n", posicion);
}

Alumno* BuscarElemento(Lista *lista, char* nombre)
{
    Nodo* actual = lista->Cabeza;

    while (actual != NULL) 
    {
        if (strcmp(actual->alumno.nombre, nombre) == 0) 
        {
            return &(actual->alumno);
        }
        actual = actual->Siguiente;
    }
    return NULL;
}

void RecorrerLista(Lista *lista)
{
    Nodo* actual = lista->Cabeza;

    if (actual == NULL) 
    {
        printf("La lista está vacía.\n");
        return;
    }

    printf("Contenido de la lista:\n");
    while (actual != NULL) 
    {
        printf("Apellido Paterno: %s\n", actual->alumno.Apaterno);
        printf("Apellido Materno: %s\n", actual->alumno.AMaterno);
        printf("Nombre: %s\n", actual->alumno.nombre);
        printf("Carrera: %d\n", actual->alumno.carrera);
        printf("\n");

        actual = actual->Siguiente;
    }
}

void OrdenarLista(Lista *lista)
{
    if (lista->Cabeza == NULL || lista->Cabeza->Siguiente == NULL) 
    {
        printf("La lista está vacía o tiene solo un elemento, no es necesario ordenar.\n");
        return;
    }

    Nodo *actual, *siguiente;
    Alumno temp;

    for (actual = lista->Cabeza; actual != NULL; actual = actual->Siguiente) 
    {
        for (siguiente = actual->Siguiente; siguiente != NULL; siguiente = siguiente->Siguiente)
        {
            if (strcmp(actual->alumno.nombre, siguiente->alumno.nombre) > 0) 
            {
                temp = actual->alumno;
                actual->alumno = siguiente->alumno;
                siguiente->alumno = temp;
            }
        }
    }

    printf("La lista ha sido ordenada correctamente.\n");
}


int ListaVacia(Lista *lista)
{
    return lista->Cabeza == NULL;
}

int CantidadElementos(Lista *lista)
{
    int contador = 0;
    Nodo* actual = lista->Cabeza;

    while (actual != NULL) 
    {
        contador++;
        actual = actual->Siguiente;
    }
    return contador;
}