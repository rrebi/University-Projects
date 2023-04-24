#include "Matrix.h"
#include <exception>
using namespace std;


//O(n^2)
Matrix::Matrix(int nrLines, int nrCols) {
	   
	//TODO - Implementation
	this->nrLins = nrLines;
	this->nrCols = nrCols;
	this->matrix = new TElem * [nrLines];

	if (this->nrLins < 1 || this->nrCols < 1) {
		throw exception("Invalid matrix dimensions!");
	}

	for (int i = 0; i < nrLines; i++)
		this->matrix[i] = new TElem[nrCols];

	for (int i = 0; i < nrLines; i++)
		for (int j = 0; j < nrCols; j++)
			this->matrix[i][j] = NULL_TELEM;
}

//O(n)
Matrix::~Matrix() {
	for (int i = 0; i < this->nrLins; i++)
	{
		if (this->matrix[i] != NULL_TELEM)
			delete[] this->matrix[i];
		this->matrix[i] = NULL;
	}
	if (this->matrix != NULL_TELEM)
		delete[] this->matrix;
	this->matrix = NULL;
	if (this->cols != NULL_TELEM)
		delete[] cols;
	this->cols = NULL;
	if (this->lines != NULL_TELEM)
		delete[] lines;
	this->lines = NULL;
	if (this->value != NULL_TELEM)
		delete[] value;
	this->value = NULL;
}

//O(1)
int Matrix::nrLines() const {
	//TODO - Implementation
	return this->nrLins;
}

//O(1)
int Matrix::nrColumns() const {
	//TODO - Implementation
	return this->nrColumns;
}

//O(1)
TElem Matrix::element(int i, int j) const {
	//TODO - Implementation
	if (i < 0 || j<0 || i>this->nrLins || j>this->nrCols)
		throw std::invalid_argument("Out of bounds");
		//return NULL_TELEM; 
	return this->matrix[i][j];
}

//O(n^2)
TElem Matrix::modify(int i, int j, TElem e) {
	//TODO - Implementation
	return NULL_TELEM;
}


