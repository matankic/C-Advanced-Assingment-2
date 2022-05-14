// Course: Advanced C programming
// exercise 2, question 1
// file name: ex2_q1.c

// --------------------------- //
// DO NOT CHANGE anything in the following macro:
#ifdef FUNC_DECLARE
#include "ex2_q1.h"
#else
// --------------------------------------- //
// Include and definition package section:
// --------------------------------------- //
#define FUNC_DECLARE
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define scanf_s scanf
#define ROWS 4
#define COLS 4
// --------------------------------------- //
// Types declration section:
// --------------------------------------- //
typedef struct fraction
{
	int num, numerator, denominator;
} fraction;
// --------------------------------------- //
// Functions declration section:
// --------------------------------------- //
unsigned long student_id();
fraction ** createMatrix(int rows, int cols);
fraction ** matrixAverageNeighbor(int A[][COLS], int rows, int cols);
fraction neighborFractionAverage(int A[][COLS], int i, int j, int rows, int cols);
void printMatrix(fraction** B, int rows, int cols);
void freeMatrix(fraction** B, int rows);
fraction reduceFraction(int numer, int denom);
// --------------------------------------- //
// Main section:
// --------------------------------------- //
int main()
{
	unsigned long id_num;
	fraction** B;
	int A[ROWS][COLS] = {
		{5, 12, 6, 8},
		{4, 7, 0, 9},
		{13, 20, 8, 2},
		{18, 0, 2, 6}
	};
	
	// call functions:
	id_num = student_id();
	printf("[id: %lu] start main\n", id_num);

	B = matrixAverageNeighbor(A, ROWS, COLS);

	// write output:
	printf("Output:\n");
	printMatrix(B, ROWS, COLS);

	// free matrix:
	freeMatrix(B, ROWS);

	return 0;
}
#endif
// --------------------------- //


// --------------------------- //
// function implementation section:
unsigned long student_id()
{
	// return your id number,
	// for example if your id is 595207432
	// return 595207432;
	// your code:
	return 333333333;
}
// --------------------------- //


/// <summary>
/// This code required one extra important function.
/// Think hard about what it should be.
/// </summary>
/// <params>You decide</params>
/// <returns>You decide</returns>
fraction reduceFraction(int numer, int denom)
{
	// your code:
	fraction frac;
	if(numer == 0){
		frac.num = 0;
		frac.numerator = 0;
		frac.denominator = 1;
		return frac;
	}
	frac.num = numer / denom;
	int nu = numer, de = denom;
	if (nu < 0)
		nu *= -1;
	nu %= denom;
	if (nu == 0){
		frac.numerator = 0;
		frac.denominator = 1;
		return frac;
	}
	if (nu == 1){
		frac.numerator = 1;
		frac.denominator = denom;
		return frac;
	}
	// greatest common divisor
	int gcd = 1, r, a, b;
	if (nu > denom){
		a = nu;
		b = denom;
	}
	else{
		b = nu;
		a = denom;
	}
	r = a - b*(a/b);
	while (r){
		gcd = r;
		a = b;
		b = r;
		r = a - b*(a/b);
	}
	frac.numerator = nu / gcd;
	frac.denominator = denom / gcd;
	return frac;
}
// --------------------------- //

/// <summary>
/// This function allocate a dynamic matrix from type fraction.
/// </summary>
/// <param>int rows - the number of rows in the matrix</param>
/// <param>int cols - the number of colums in the matrix</param>
/// <returns>allocated empty matrix B from type fraction</returns>
fraction** createMatrix(int rows, int cols)
{
	// your code:
	fraction **matrix = (fraction**)malloc(rows * sizeof(fraction*));
	{
		int i;
		for (i = 0; i < rows; i++)
			matrix[i] = (fraction*)malloc(cols * sizeof(fraction));
	}
	return matrix;
}
// --------------------------- //

/// <summary>
/// The function receives a static matrix 
/// and for each cell in the matrix calculates 
/// the average of its neighbors.  
/// </summary>
/// <param>int A[][COLS] - the static matrix</param>
/// <param>int rows - the number of rows in the matrix</param>
/// <param>int cols - the number of colums in the matrix</param>
/// <returns>matrix B from type fraction</returns>
fraction** matrixAverageNeighbor(int A[][COLS], int rows, int cols)
{
	// your code:
	fraction **matrix = createMatrix(rows, cols);
	int i, j;
	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++)
			matrix[i][j] = neighborFractionAverage(A, i, j, rows, cols);
	return matrix;
}
// --------------------------- //

/// <summary>
/// The function receives a static matrix, and a cell value,
/// and calculates the average of its neighbors.  
/// </summary>
/// <param>int A[][COLS] - the static matrix</param>
/// <param>int i - the cell row number in matrix</param>
/// <param>int j - the cell colum number in the matrix</param>
/// <param>int rows - the number of rows in the matrix</param>
/// <param>int cols - the number of colums in the matrix</param>
/// <returns>value from type fraction</returns>
fraction neighborFractionAverage(int A[][COLS], int i, int j, int rows, int cols)
{
	// your code:
	if(rows == 1 && cols == 1) //Edge case
		return reduceFraction(0, 1);

	int counter = 0, sum = 0; // 8 cases to be checked
	if(i-1 >= 0 && j-1 >= 0){ // Upper-left
		sum += A[i-1][j-1];
		counter++;
	}
	if(j-1 >= 0){ // middle-left
		sum += A[i][j-1];
		counter++;
	}
	if(i+1 < rows && j-1 >= 0){ // lower-left
		sum += A[i+1][j-1];
		counter++;
	}
	if(i+1 < rows){ // lower-middle
		sum += A[i+1][j];
		counter++;
	}
	if(i+1 < rows && j+1 < cols){ // lower-right
		sum += A[i+1][j+1];
		counter++;
	}
	if(j+1 < cols){ // middle-right
		sum += A[i][j+1];
		counter++;
	}
	if(i-1 >= 0 && j+1 < cols){ // upper-right
		sum += A[i-1][j+1];
		counter++;
	}
	if(i-1 >= 0){ // middle-upper
		sum += A[i-1][j];
		counter++;
	}
	if(counter == 0)
		return reduceFraction(0, 1);
	return reduceFraction(sum, counter);
}
// --------------------------- //


/// <summary>
/// The function receives a dynamic matrix from type fraction,
/// and print the matrix as double varibles.  
/// </summary>
/// <param>fraction** B - the dynamic matrix</param>
/// <param>int rows - the number of rows in the matrix</param>
/// <param>int cols - the number of colums in the matrix</param>
/// <returns>None</returns>
void printMatrix(fraction** B, int rows, int cols)
{
	// your code:
	{
		int i, j;
		for (i = 0; i < rows; i++){
			for (j = 0; j < cols; j++){
				printf("%.2lf ", (double)B[i][j].num +
						(double)B[i][j].numerator / (double)B[i][j].denominator);
			}
			printf("\n");
		}
	}
}
// --------------------------- //


/// <summary>
/// The function receives a dynamic matrix from type fraction,
/// and free all allocated memory.  
/// </summary>
/// <param>fraction** B - the dynamic matrix</param>
/// <param>int rows - the number of rows in the matrix</param>
/// <returns>None</returns>
void freeMatrix(fraction** B, int rows)
{
	// your code:
	{
		int i;
		for (i = 0; i < rows; i++){
			free(B[i]);
			B[i] = NULL;
		}
	}
	free(B);
	B = NULL;
}
// --------------------------- //
