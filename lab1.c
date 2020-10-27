#include <stdio.h>
#include <stdlib.h>
/****************************************
 * Martin Antonio Vivanco Palacios A01701167
 * Lab 1 programacion avanzada
 ****************************************/
typedef unsigned int uint;

typedef struct {
	double *data;
	uint nrows, ncols;
} Matrix;
/****************************************
 * En este procedimiento uso una formula para acceder a la una localidad de 
 * memoria de tamano double y lo imprimo
 ****************************************/
void printm(Matrix *M) {
	printf("Printing matrix:");
	double aux;
	printf("%dx%d \n", M -> nrows, M -> ncols );
	for (uint i = 0; i < (M -> nrows); ++i)
	{
		for (uint j = 0; j < (M -> ncols); ++j)
		{
			aux = M -> data[i*(M -> ncols) + j];
			printf("  %lf  ", aux);
		}
		printf("\n");
	}

}

Matrix* alloc_matrix(uint nrows, uint ncols) {
/****************************************
 * This procedure should request the amount of memory 
 * needed for the Matrix structure and for the storage 
 * of a matrix of the required dimensions. If you can 
 * not get that amount of memory, return NULL.
 * Check that nrows and ncols must be greater than 0.
 * If you have allocated memory and there is an error,
 * you must free all the memory allocated.
 ****************************************/
	if(nrows == 0){
		printf("rows cant be 0\n");
		return NULL;
	}
	if(ncols == 0){
		printf("cols oc cols cant be 0\n");
		return NULL;
	}
	Matrix *a = malloc(sizeof(Matrix)); //crear apuntador a matriz 
	if (a == NULL)
	{
		printf("Error, matriz nula!!!\n");
		return NULL;
	}

	(*a).nrows = nrows; //crear filas en matriz
	(*a).ncols = ncols; // columnas en matrix 
	(*a).data = malloc(sizeof(double)*nrows*ncols); //los datos estaran en una ubicacion de memoria
	// del tamano de un double por el tamano de la matriz mxn
	if (a -> data == NULL)
	{
		printf("Error de datos!!!\n");
		free(a -> data);
		return NULL;
	}
	return a;
}

void set(Matrix *M, uint row, uint col, double val) {
/****************************************
 * Check that the row and column is valid for the matrix, 
 * if not, it displays an error. Otherwise, place the value 
 * in the correct cell. Check the following links:
 * https://stackoverflow.com/questions/2151084/map-a-2d-array-onto-a-1d-array
 * https://stackoverflow.com/questions/14015556/how-to-map-the-indexes-of-a-matrix-to-a-1-dimensional-array-c
 ****************************************/
	if (M == NULL) // se verifica que la matriz no sea nula
	{
		printf("Error, matriz nula!!!\n");
	}
	else if(((M -> nrows) < row)||((M -> ncols) == col)){ // se verifica que la ubicacion exista en la matriz
		printf("Matrix dont have enough space\n");
	}
	else{ // despues de verificarse se inserta el valor con la formula
		M -> data[row*(M -> ncols) + col] = val;
	}

}
double obtenRenglon(Matrix *A, uint m, uint n){
/****************************************
 * Funcion auxiliar que te da el valor de una ubicacion mxn en la matriz
 ****************************************/
	double x;
	x = A -> data[m*(A -> ncols) + n];
	return x;
}

void matrix_mult(Matrix *A, Matrix *B, Matrix *C) {
/****************************************
 * It must be checked that the multiplication can be done 
 * (check the following links:
 * https://es.wikipedia.org/wiki/Multiplicaci%C3%B3n_de_matrices
 * https://www.geogebra.org/m/S6R8A2xD
 * ). If it can not be done, you must display an error message.
 * Remember check for null pointer. 
 * 
 * The multiplication is A x B = C
 * primero se verifican todos los requerimientos para la multiplicacion de matrizes
 * despues se recorre la matriz c y se genera su valor con ayuda de ciclos y la funciom
 * obten renglon
 ****************************************/
	if ((A == NULL)||(B == NULL))
	{
		printf("Error, matriz nula!!!\n");
	}
	else if ((A -> ncols) != (B -> nrows)){
		printf("Error, matriz incompatible1!!!\n");
	}
	else if ((B -> ncols) != (A -> nrows)){
		printf("Error, matriz incompatible2!!!\n");
	}
	else if ((A -> nrows) != (C -> nrows)){
		printf("Error, matriz incompatible3!!!\n");
	}
	else if ((B -> ncols) != (C -> ncols)){
		printf("Error, matriz incompatible4!!!\n");
	}
	else{
		double aux = 0;
		for (uint i = 0; i < (C -> nrows); ++i)
		{
			for (uint j = 0; j < (C -> ncols); ++j)
			{

				for (uint k = 0; k < (C -> ncols); ++k)
				{
					double aux1, aux2;
					aux1 = obtenRenglon(A, i, k);
					aux2 = obtenRenglon(B, k, j);
					aux = aux + aux2*aux1;
				}
				C -> data[i*(C -> ncols) + j] = aux;
				aux = 0;
			}
		}
	}
}


void free_matrix(Matrix *M) {
/****************************************
 * If the element that is received is different from NULL, 
 * the space assigned to the array and the structure must be 
 * freed.
 * si la matriz no es nula se libera el espacio en esta
 ****************************************/
	if(M != NULL){
		free(M);
	}
	else{
		printf("Error matriz nula!!!\n");
	}
}


int main(int argc, char* argv[]) {
	printf("Creating the matrix A:\n");
	Matrix *A = alloc_matrix(3, 2);
	
	printf("Setting the matrix A:\n");
	set(A, 0, 0, 1.2);
	set(A, 0, 1, 2.3);
	set(A, 1, 0, 3.4);
	set(A, 1, 1, 4.5);
	set(A, 2, 0, 5.6);
	set(A, 2, 1, 6.7);
	printf("Printing the matrix A:\n");
	printm(A);
	
	printf("Creating the matrix B:\n");
	Matrix *B = alloc_matrix(2, 3);
	printf("Setting the matrix B:\n");
	set(B, 0, 0, 5.5);
	set(B, 0, 1, 6.6);
	set(B, 0, 2, 7.7);
	set(B, 1, 0, 1.2);
	set(B, 1, 1, 2.1);
	set(B, 1, 2, 3.3);
	printf("Printing the matrix B:\n");
	printm(B);
	
	printf("Creating the matrix C:\n");
	Matrix *C = alloc_matrix(3, 3);
	printf("A x B = C:\n");
	matrix_mult(A, B, C);
	printf("Printing the matrix C:\n");
	printm(C);
	
	printf("B x A = C:\n");
	matrix_mult(B, A, C);
	printf("Printing the matrix C:\n");
	printm(C);
	
	Matrix *D = NULL;
	printf("Setting a NULL matrix (D):\n");
	set(D, 0, 0, 10);
	
	printf("A x D(NULL) = C:\n");
	matrix_mult(A, D, C);
	printf("D(NULL) x A = C:\n");
	matrix_mult(D, A, C);
	
	printf("Allocating E with (0,0): \n");
	Matrix *E = alloc_matrix(0, 0);
	
	printf("Freeing A:\n");
	free_matrix(A);
	printf("Freeing B:\n");
	free_matrix(B);
	printf("Freeing C:\n");
	free_matrix(C);
	printf("Freeing D(NULL):\n");
	free_matrix(D);
	printf("Freeing E(NULL):\n");
	free_matrix(E);

	return 0;
}
