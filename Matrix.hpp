#ifndef MATRIX_H
#define MATRIX_H

#include <cstring>
#include <cassert>
#include "Vector.hpp"

class Matrix {
public:
	Matrix();
	Matrix( const Matrix & other );
	explicit Matrix( int rows, int cols );
	explicit Matrix( int rows, int cols, float * data );
	
	~Matrix();
	
	const float * 	operator[]( int index ) const;
	float * 		operator[]( int index );
	
	Matrix & 	operator=( const Matrix & other );
	Matrix  	operator+( const Matrix & other ) const;
	Matrix  	operator-( const Matrix & other ) const;
	Matrix  	operator*( const Matrix & other ) const;
	Matrix  	operator*( const float & a ) const;
	Vector		operator*( const Vector & v ) const;
	
	Matrix & 	operator+=( const Matrix & other );
	Matrix & 	operator-=( const Matrix & other );
	Matrix & 	operator*=( const Matrix & other ); //not implemented
	Matrix & 	operator*=( const float & a );
	Vector	 	operator*=( const Vector & v );		//not implemented
	
	friend Matrix 	operator*( const float & a, const Matrix & m );
	friend Vector	operator*( const Vector & v, const Matrix & m );
	friend Matrix & operator*=( const float & a, Matrix & m );
	
	void 	Zero();
	void 	Memset( const float & fill );
	void 	Identity();
	Matrix 	Transpose() const;
	
	int GetNumRows() const;
	int GetNumCols() const;
	int GetDimension() const;
	
	const float * 	ToFloatPtr() const;
	float * 		ToFloatPtr();
	
private:
	int numRows;
	int numCols;
	float * mat;	
};


inline Matrix::Matrix() { 
	numRows = numCols = 0;
	mat = nullptr;
}

inline Matrix::Matrix( const Matrix & other ) {
	assert( numRows >= 0 && numCols >= 0 );
	numRows = other.numRows;
	numCols = other.numCols;
	mat = new float[numRows * numCols];
	for( int i = 0; i < numRows * numCols; i++ ) {
		mat[i] = other.mat[i];
	}
}

inline Matrix::Matrix( int rows, int cols ) {
	assert( rows >= 0 && cols >= 0 );
	numRows = rows;
	numCols = cols;
	mat = new float[ rows * cols ];
}

inline Matrix::Matrix( int rows, int cols, float * data ) {
	assert(rows >= 0 && cols >= 0);
	if( data != nullptr ) {
		numRows = rows;
		numCols = cols;
		mat = new float[ rows * cols ];
		std::memcpy(mat, data, rows * cols * sizeof( float ));
	} 
}

inline Matrix::~Matrix() {
	delete[] mat;
}

inline const float * Matrix::operator[]( int index ) const {
	assert( index < numRows && index >= 0 );
	return mat + index * numCols;
}

inline float * Matrix::operator[]( int index ) {
	assert( index < numRows && index >= 0 );
	return mat + index * numCols;
}

inline Matrix & Matrix::operator=( const Matrix & other ) {
	std::memcpy( mat, other.mat, numRows * numCols * sizeof( float ) );
	return *this;
}

inline Matrix Matrix::operator+( const Matrix & other ) const {
	assert( numRows == other.numRows && numCols == other.numCols );
	Matrix m( numRows, numCols );
	m.Zero();
	for( int i = 0; i < numRows * numCols; i++ ) {
		m.mat[i] = mat[i] + other.mat[i];
	}
	return m;
}

inline Matrix Matrix::operator-( const Matrix & other ) const {
	assert( numRows == other.numRows && numCols == other.numCols );
	Matrix m( numRows, numCols );
	m.Zero();
	for( int i = 0; i < numRows * numCols; i++ ) {
		m.mat[i] = mat[i] - other.mat[i];
	}
	return m;
}

inline Matrix Matrix::operator*( const float & a ) const {
	Matrix m( numRows, numCols );
	for( int i = 0; i < numRows * numCols; i++ ) {
		m.mat[i] = a * mat[i];
	}
	return m;
}

inline Matrix Matrix::operator*( const Matrix & other ) const {
	assert( numCols == other.numRows );
	Matrix m( numRows, other.numCols );
	m.Zero();
	for( int i = 0; i < numRows; i++ ) {
		for( int j = 0; j < other.numCols; j++ ) {
			for( int k = 0; k < other.numCols; k++ ) {
				m.mat[i + j * numCols] += mat[i + k * numCols] * other.mat[k + j * numCols];
			}
		}
	}
	return m;
}

inline Vector Matrix::operator*( const Vector & v ) const {
	assert( numCols == v.size );
	Vector w( numRows );
	for( int i = 0; i < numRows; i++ ) {
		for( int j = 0; j < size; j++ ) {
			w.u[i] = v.u[i] * mat[ i + j * numCols ]; 
		}
	}
	return w;
}

inline Matrix operator*( const float & a, const Matrix & m ) {
	Matrix b( m.numRows, m.numCols );
	for( int i = 0; i < m.numRows * m.numCols; i++ ) {
		b.mat[i] = a * m.mat[i];
	}
	return b;
}

inline Vector operator*( const Vector & v, const Matrix & m ) {
	assert( v.size == m.numRows );
	Vector w( size );
	for( int i = 0; i < size; i++ ) {
		for( int j = 0; j < m.numCols; j ++ ) {
			w.u[i] = v.u[i] * m.mat[ i + j * numCols ];
		}
	}
	return w;
}

inline Matrix & operator*=( const float & a, Matrix & m ) {
	for( int i = 0; i < m.numRows * m.numCols; i++ ) {
		m.mat[i] *= a;
	}
	return m;
}

inline Matrix & Matrix::operator+=( const Matrix & other ) {
	assert( numRows == other.numRows && numCols == other.numCols );
	for( int i = 0; i < numRows * numCols; i++ ) {
		mat[i] += other.mat[i];
	}
	return *this;
}

inline Matrix & Matrix::operator-=( const Matrix & other ) {
	assert( numRows == other.numRows && numCols == other.numCols );
	for( int i = 0; i < numRows * numCols; i++ ) {
		mat[i] -= other.mat[i];
	}
	return *this;
}

inline Matrix & Matrix::operator*=( const float & a ) {
	for( int i = 0; i < numRows * numCols; i++ ) {
		mat[i] *= a;
	}
	return *this;
}

inline void Matrix::Zero() {
	std::memset( mat, 0, numRows * numCols * sizeof( float ) );
}

inline void Matrix::Memset( const float & fill ) {
	for( int i = 0; i < numRows * numCols; i++ ) {
		mat[i] = fill;
	}
}

inline void Matrix::Identity() {
	assert( numCols == numRows );
	std::memset( mat, 0, numRows * numCols * sizeof(float) );
	for( int i = 0; i < numRows; i++ ) {
		mat[i + i * numCols] = 1.0f;
	}
}

inline Matrix Matrix::Transpose() const {
	Matrix m( numCols, numRows );
	//TO DO
	return m;
}

inline int Matrix::GetNumRows() const {
	return numRows;
}

inline int Matrix::GetNumCols() const {
	return numCols;
}

inline int Matrix::GetDimension() const {
	return numRows * numCols;
}

inline const float * Matrix::ToFloatPtr() const {
	return mat;
}

inline float * Matrix::ToFloatPtr() {
	return mat;
}

#endif  //MATRIX_H