#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Producto
{
    char *nombre;
    int codigo;
    int cantidad;
} Producto;

typedef struct Nodo
{
    Producto producto;
    struct Nodo *Siguiente;
    struct Nodo *anterior;
} Nodo;

typedef struct Lista
{
    Nodo *Cabeza;
} Lista;

void InsertarEnPosiEspec(Lista *lista, Producto *producto, int posicion);
void EliminarElemento(Lista *lista, int posicion);
Producto* BuscarElemento(Lista *lista, char* nombre);
void RecorrerLista(Lista *lista);
void OrdenarLista(Lista *lista);
void InsertarOrdenado(Lista *lista, Producto *producto);
int ListaVacia(Lista *lista);
int CantidadElementos(Lista *lista);
Nodo* CrearNodo (Producto *producto);
void InsertarAlFinal(Lista* lista, Producto *producto);

int main()
{
    Lista lista;
    lista.Cabeza = NULL;
    Producto Producto1 = {"soda", 23, 1};
    Producto Producto2 = {"oreo", 12, 2};
    
    InsertarAlFinal(&lista, &Producto1);
    InsertarAlFinal(&lista, &Producto2);

    RecorrerLista(&lista);

    InsertarEnPosiEspec(&lista, &Producto1, 2);
    BuscarElemento(&lista, "Nombre1");

    RecorrerLista(&lista);

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

Nodo* CrearNodo (Producto *Producto)
{
    Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));
    nodo->producto.nombre = strdup(Producto->nombre);
    nodo->producto.cantidad = Producto->cantidad;
    nodo->Siguiente = NULL;
    return nodo;
}

void InsertarAlFinal(Lista* lista, Producto *producto)
{
    Nodo* nodo = CrearNodo(producto);
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


void InsertarEnPosiEspec(Lista *lista,Producto *producto, int posicion)
{
    Nodo* nodo = CrearNodo(producto);

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
        InsertarAlFinal(lista, producto);
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

Producto* BuscarElemento(Lista *lista, char* nombre)
{
    Nodo* actual = lista->Cabeza;

    while (actual != NULL) 
    {
        if (strcmp(actual->producto.nombre, nombre) == 0) 
        {
            return &(actual->producto);
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
        printf("Nombre: %s\n", actual->producto.nombre);
        printf("precio: %d\n", actual->producto.cantidad);
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
    Producto temp;

    for (actual = lista->Cabeza; actual != NULL; actual = actual->Siguiente) 
    {
        for (siguiente = actual->Siguiente; siguiente != NULL; siguiente = siguiente->Siguiente)
        {
            if (strcmp(actual->producto.nombre, siguiente->producto.nombre) > 0) 
            {
                temp = actual->producto;
                actual->producto = siguiente->producto;
                siguiente->producto = temp;
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