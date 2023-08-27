#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct alumno { //Defino el struct para el alumno
    char *nombreCompleto;
    int creditosAprobados;
    int semestreEquivalente;
} Alumno;

typedef Alumno *AlumnoPtr;

typedef struct nodo {       // Defino el struct para el nodo
    AlumnoPtr alumno;
    struct nodo *siguientePtr;
} Nodo;

typedef Nodo *NodoPtr; 


//FIRMAS:

AlumnoPtr crearAlumno(char* nombreCompleto, int creditosAprobados, int semestreEquivalente); //pedido
void imprimirAlumno(NodoPtr actualPtr);//pedido
void liberarAlumno(AlumnoPtr alumno); //necesario


NodoPtr crearNodo(AlumnoPtr nuevoAlumno); //pedido
void liberarNodo(NodoPtr nodo); //necesario
void imprimirLista( NodoPtr actualPtr);//pedido
int estaVacia(NodoPtr sPtr); //necesario
void insertarNodoOrdenadoCreditos(NodoPtr *cabeza, NodoPtr nuevoNodo );//pedido

void confirmarAlumnoCreado(AlumnoPtr alumnoX);
void confirmarNodoCreado(NodoPtr nodoX);

void liberarLista(NodoPtr lista); //necesario


//MAIN:
int main()
{
    NodoPtr inicioPtr = NULL;

    //5 instancias de estructuras Alumno:
    printf("\n");
    AlumnoPtr alumno1 = crearAlumno("Paulo Andreu", 57, 3);
    confirmarAlumnoCreado(alumno1);
    AlumnoPtr alumno2 = crearAlumno("Andrea Riquelme", 76, 4);
    confirmarAlumnoCreado(alumno2);
    AlumnoPtr alumno3 = crearAlumno("Emilio Angulo", 38, 2);
    confirmarAlumnoCreado(alumno3);
    AlumnoPtr alumno4 = crearAlumno("Patricia Delgado", 95, 5);
    confirmarAlumnoCreado(alumno4);
    AlumnoPtr alumno5 = crearAlumno("Cintia Ballesteros", 19, 1);
    confirmarAlumnoCreado(alumno5);
    printf("\n\n");
    //la lista con las 5 instancias de Alumno:
    NodoPtr nodo1 = crearNodo(alumno1);
    confirmarNodoCreado(nodo1);
    NodoPtr nodo2 = crearNodo(alumno2);
    confirmarNodoCreado(nodo2);
    NodoPtr nodo3 = crearNodo(alumno3);
    confirmarNodoCreado(nodo3);
    NodoPtr nodo4 = crearNodo(alumno4);
    confirmarNodoCreado(nodo4);
    NodoPtr nodo5 = crearNodo(alumno5);
    confirmarNodoCreado(nodo5);
    printf("\n\n");
    //insertar de forma ordenada de acuerdo al número de créditos:

    insertarNodoOrdenadoCreditos(&inicioPtr, nodo1);
    insertarNodoOrdenadoCreditos(&inicioPtr, nodo2);
    insertarNodoOrdenadoCreditos(&inicioPtr, nodo3);
    insertarNodoOrdenadoCreditos(&inicioPtr, nodo4);
    insertarNodoOrdenadoCreditos(&inicioPtr, nodo5);
    
    imprimirLista(inicioPtr);
    printf("\n");

    liberarLista(inicioPtr);

    
    return 0;
}

//FUNCIONES:


AlumnoPtr crearAlumno(char* nombreCompleto, int creditosAprobados, int semestreEquivalente) {
    AlumnoPtr alumno = (AlumnoPtr)malloc(sizeof(Alumno)); 

    alumno->nombreCompleto = (char*)malloc(strlen(nombreCompleto) + 1);
    strcpy(alumno->nombreCompleto, nombreCompleto);

    alumno->creditosAprobados= creditosAprobados;
    alumno->semestreEquivalente= semestreEquivalente;

    return alumno;
}

//imprime los elementos del alumno:
void imprimirAlumno(NodoPtr actualPtr){
    printf("Nombre: %s, Créditos Aprobados: %i, Semestre Equivalente: %i \n ", actualPtr->alumno->nombreCompleto, actualPtr->alumno->creditosAprobados, actualPtr->alumno->semestreEquivalente);
}

//Libera la dirección de memoria que ocupaba el alumno:
void liberarAlumno(AlumnoPtr alumno) {
    free(alumno->nombreCompleto);
    free(alumno);
}

//crea un nuevo nodo en la lista:
NodoPtr crearNodo(AlumnoPtr nuevoAlumno) {
    NodoPtr nuevoNodo = (NodoPtr)malloc(sizeof(Nodo));

    nuevoNodo->alumno = nuevoAlumno;
    nuevoNodo->siguientePtr = NULL;

    return nuevoNodo;
}

//libera la dirección de memoria que ocupaba un nodo:
void liberarNodo(NodoPtr nodo){
    free(nodo);   
}


//revisa si la lista está vacía:
int estaVacia(NodoPtr sPtr)
{ 
    return sPtr == NULL;
}

//inserta los nodos de manera ordenada de Mayor a menor:
void insertarNodoOrdenadoCreditos(NodoPtr *cabeza, NodoPtr nuevoNodo ){

    NodoPtr nodoActualPtr = *cabeza;
    NodoPtr nodoAnteriorPtr= NULL;

    //esto debido a que si la lista no tiene ningún elemento, no tiene sentido hacer el ciclo while
    if(estaVacia(*cabeza)){
        *cabeza = nuevoNodo;
        return;
    }
    //si la lista no estå vacía, entonces debo recorrer la lista para identificar dónde debería insertar el nodo 
   

    while (nodoActualPtr != NULL && nuevoNodo->alumno->creditosAprobados < nodoActualPtr->alumno->creditosAprobados ) {
        // se avanza en el recorrido de la lista
        nodoAnteriorPtr = nodoActualPtr;
        nodoActualPtr = nodoActualPtr->siguientePtr;

    } 
    
    if (nodoAnteriorPtr == NULL) {//es importante ponerlo para no tener un segmentation fault
        
        nuevoNodo->siguientePtr = *cabeza; 
        *cabeza = nuevoNodo;
    } else { //insercción del nodo entre anterior y actual 
        nodoAnteriorPtr->siguientePtr = nuevoNodo;
        nuevoNodo->siguientePtr = nodoActualPtr;
    }
}


//Funcion para Imprimir la Lista:
void imprimirLista( NodoPtr actualPtr){
    if (actualPtr==NULL){                           //revisa si la lista esta vacia
        printf("Lista vacia \n\n");
        return;
    }
    else{
        printf("Impresión de la lista de alumnos (Créditos Descendentes):\n\n"); 
        
        while(actualPtr != NULL){   //Imprime cada alumno de la lista ordenada previamente de Mayor a menor 
            imprimirAlumno(actualPtr);                
            actualPtr = actualPtr->siguientePtr;  
        }
        
    }
}

//confirma si el alumno fue creado y te dice la dirección de memoria en la que se encuentra:
void confirmarAlumnoCreado(AlumnoPtr alumnoX){
    if(alumnoX ==NULL){
        printf("La creación del alumno fue imposible\n");
    }else{
        printf("Se ha creado una estructura Alumno con la dirección %p\n", alumnoX);
    }
}

//confirma si el nodo fue creado y te dice la dirección de memoria en la que se encuentra:
void confirmarNodoCreado(NodoPtr nodoX){
    if(nodoX==NULL){
        printf("La creación del nodo fue imposible\n");
    }else{
        printf("Se ha creado un nodo en la lista de alumnos en %p\n", nodoX);
    }
}

/*libera la dirección de memoria de la lista completa y de cada elemento dinámico en ella (es responsabilidad del desarrollador liberar elementos
asignados en memoria dinámica)  :*/
void liberarLista(NodoPtr cabeza) {
    while (cabeza != NULL) {
        NodoPtr temp = cabeza;
        cabeza = cabeza->siguientePtr;
        liberarAlumno(temp->alumno);  // Liberar el alumno dentro del nodo
        liberarNodo(temp);            // Liberar el nodo
    }
}

