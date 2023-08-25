#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*No me dió el tiempo de implementarlo, estaba fallando el internet de la biblioteca,
no obstante ya tengo la idea y una parte del código*/

typedef struct alumno {
    char *nombreCompleto;
    int creditosAprobados;
    int semestreEquivalente;
} Alumno;

typedef Alumno *AlumnoPtr;

typedef struct nodo {       // Definimos el struct para la lista
    AlumnoPtr alumno;
    struct nodo *siguientePtr;
} Nodo;

typedef struct nodo *NodoPtr; //lo puse de esta forma porque vs code lloraba cuando ponía Nodo


/*Firmas*/

AlumnoPtr crearAlumno(char* nombreCompleto, int creditosAprobados, int semestreEquivalente); //pedido
void liberarAlumno(AlumnoPtr alumno);
void imprimeAlumno(AlumnoPtr alumno);

NodoPtr crearNodo(AlumnoPtr nuevoAlumno); //pedido
void liberarNodo(NodoPtr nodo);
void imprimeLista( NodoPtr actualPtr);//pedido
int estaVacia(NodoPtr sPtr);
void eliminarNodoPorNombre(NodoPtr* cabecera, char* dato);
void actualizarNodoPorNombre(NodoPtr *cabecera, char* dato, char* nuevoDato);
void insertarOrdenado(NodoPtr *cabeza, NodoPtr nuevo);
void liberarLista(NodoPtr lista);
void insertarNodoOrdenadoCreditos(NodoPtr *cabeza);//pedido

//MAIN:
int main()
{
    NodoPtr inicioPtr = NULL;

    insertarOrdenado(&inicioPtr,crearNodo(crearAlumno("Hola", "Russ")));
    insertarOrdenado(&inicioPtr,crearNodo(crearAlumno("Bonilla", "Russel")));
    insertarOrdenado(&inicioPtr,crearNodo(crearAlumno("Bonilla", "Adrian")));
    insertarOrdenado(&inicioPtr,crearNodo(crearAlumno("Hola", "Adrian")));
    imprimeLista(inicioPtr);
    printf("\n \n");

    eliminarNodoPorNombre(&inicioPtr, "Russ");
    imprimeLista(inicioPtr);
    printf("\n \n");

    actualizarNodoPorNombre(&inicioPtr, "Adrian", "Siuu");
    imprimeLista(inicioPtr);

    



    liberarLista(inicioPtr);

    
    return 0;
}

//FUNCIONES:

/*
char* crearCadena(char* cadena) {

    AlumnoPtr alumno = (AlumnoPtr)malloc(sizeof(Alumno));
   
    char* nuevaCadena = (char*)malloc(strlen(cadena) + 1);
    strcpy(nuevaCadena, cadena);
    return nuevaCadena;
}
*/

AlumnoPtr crearAlumno(char* nombreCompleto, int creditosAprobados, int semestreEquivalente) {
    AlumnoPtr alumno = (AlumnoPtr)malloc(sizeof(Alumno));

    alumno->nombreCompleto = (char*)malloc(strlen(nombreCompleto) + 1);
    strcpy(alumno->nombreCompleto, nombreCompleto);

    alumno->creditosAprobados= creditosAprobados;
    alumno->semestreEquivalente= semestreEquivalente;

    return alumno;
}

void imprimeAlumno(AlumnoPtr alumno){

}

void liberarAlumno(AlumnoPtr alumno) {
    free(alumno->nombreCompleto);
    free(alumno->creditosAprobados);
    free(alumno->semestreEquivalente);
    free(alumno);
}

NodoPtr crearNodo(AlumnoPtr nuevoAlumno) {
    NodoPtr nuevoNodo = (NodoPtr)malloc(sizeof(Nodo));

    nuevoNodo->alumno = nuevoAlumno;
    nuevoNodo->siguientePtr = NULL;

    return nuevoNodo;
}

void liberarNodo(NodoPtr nodo){

    free(nodo);   
}


//Funcion para Imprimir la Lista
void imprimeLista( NodoPtr actualPtr){
    if (actualPtr==NULL){                           //revisa si la lista esta vacia
        printf("Lista vacia \n\n");
        return;
    }
    else{
        printf("Contenido de la lista:\n");
        
        while(actualPtr != NULL){                   //Imprime la lista
            printf("%s %s \n ", actualPtr->alumno->apellidoPaterno, actualPtr->alumno->nombre);
            actualPtr = actualPtr->siguientePtr;  
        }
        
    }
}

int estaVacia(NodoPtr sPtr)
{ 
    return sPtr == NULL;
}

void eliminarNodoPorNombre(NodoPtr* cabecera, char* nombre){
    NodoPtr anterior, actual;
    anterior = NULL;
    actual = *cabecera;
    
    //Buscar el nodo
    while(actual!=NULL && strcmp(actual->alumno->nombre, nombre) != 0 ){ //no sé si es suficiente con eso o requiero comparar elemento por elemento
        anterior = actual;
        actual = actual->siguientePtr;
    }
    // Si no lo encontro 
    if(actual == NULL){
       printf("Nodo no encontrado");
       return; 
    }
    //al inciio
    if(actual == *cabecera){
        *cabecera = actual->siguientePtr;
    }else //enmedio
        anterior->siguientePtr=actual->siguientePtr;
    
    liberarNodo(actual);    
}


void actualizarNodoPorNombre(NodoPtr *cabecera, char* nombre, char* nuevoNombre){
    NodoPtr actual;
   
    actual = *cabecera;
    
   while(actual != NULL  && strcmp(actual->alumno->nombre, nombre) != 0){
    actual = actual->siguientePtr;
   }

   if(actual == NULL ){ //si actual es null, significa  que nunca se encontro el nodo
    printf("No se encontro el nodo a actualizar");
   }
   else{
    strcpy(actual->alumno->nombre, nuevoNombre);
   }
}


void insertarOrdenado(NodoPtr *cabeza, NodoPtr nuevoNodo ){

    NodoPtr nodoActualPtr = *cabeza;
    NodoPtr nodoAnteriorPtr= NULL;

    //esto debido a que si la lista no tiene ningún elemento, no tiene sentido 
    //hacer lo sig.
    if(estaVacia(*cabeza)){
        *cabeza = nuevoNodo;
        return;
    }
    //si la lista no estå vacía, entonces debo recorrer la lista para identificar
    //dónde debería insertar el nodo 
   

    while (nodoActualPtr != NULL && strcmp(nuevoNodo->alumno->apellidoPaterno, nodoActualPtr->alumno->apellidoPaterno)>0 ) {
        // se avanza en el recorrido de la lista
        nodoAnteriorPtr = nodoActualPtr;
        nodoActualPtr = nodoActualPtr->siguientePtr;

        if(strcmp(nuevoNodo->alumno->apellidoPaterno, nodoActualPtr->alumno->apellidoPaterno)==0){
            while (strcmp(nuevoNodo->alumno->nombre, nodoActualPtr->alumno->nombre)>0 ){
                nodoAnteriorPtr = nodoActualPtr;
                nodoActualPtr = nodoActualPtr->siguientePtr;
            }
        }
    } 
    
    if (nodoAnteriorPtr == NULL) {/*nodoAnteriorPtr->siguientePtr. Si es NULL, 
    significa que el nuevo nodo debe convertirse en la cabeza de la lista, es importante ponerlo
    para no tener un segmentation fault*/
        nuevoNodo->siguientePtr = *cabeza;
        *cabeza = nuevoNodo;
    } else { //insercción del nodo entre anterior y actual 
        nodoAnteriorPtr->siguientePtr = nuevoNodo;
        nuevoNodo->siguientePtr = nodoActualPtr;
    }
}

void liberarLista(NodoPtr cabeza) {
    while (cabeza != NULL) {
        NodoPtr temp = cabeza;
        cabeza = cabeza->siguientePtr;
        liberarAlumno(temp->alumno);  // Liberar el alumno dentro del nodo
        liberarNodo(temp);            // Liberar el nodo
    }
}


//para comprar dos cadenas usamos la función de la biblioteca: strcmp (una función que recibe dos apuntadores y devuelve 
//si la cadena a>b devuelve algo mayor a 0, si a es menor que b devuelve un float menor que 0 (la diferencia)
// y si son iguales devuelve 0)
//string comper lo que devuelve es la diferencia