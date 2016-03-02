#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>
#include <cmath>

class Vector {
public:
	Vector();
	Vector( const Vector & v );
	explicit Vector( int size );
	explicit Vector( int size, float * data );
	
	~Vector();
	
	Vector & 		operator=( const Vector & v );
	const float & 	operator[]( const int index ) const;
	float & 		operator[]( const int index );
	
	Vector 	operator+( const Vector & v ) const;
	Vector 	operator-( const Vector & v ) const;
	Vector 	operator*( const float & a ) const;
	float  	operator*( const Vector & v ) const;
	
	Vector & operator+=( const Vector & v );
	Vector & operator-=( const Vector & v );
	Vector & operator*=( const float & a );
	
	friend Vector 	operator*( const float & a, const Vector & u );
	friend Vector & operator*=( const float & a, Vector & u );
	
	void 		Zero();
	void 		Memset( const float & fill );
	Vector 		Normalize() const;
	Vector &	NormalizeSelf();
	float 		Length() const;
	float 		Distance( const Vector & v ) const;
	int 		GetDimension() const;
	
	const float * 	ToFloatPtr() const;
	float * 		ToFloatPtr();
	
private:
	int size;
	float * u;
};

inline Vector::Vector() {
	size = 0;
	u = nullptr;
}

inline Vector::Vector( const Vector & v ) {
	assert( v.u != nullptr && size >= 0 );
	size = v.size;
	u = new float[size];
	std::memcpy(u, v.u, size * sizeof( float ) );
}

inline Vector::Vector( int size ) {
	assert( size >= 0 );
	this->size = size;
	u = new float[size]; 
}

inline Vector::Vector( int size, float * data ) {
	assert( size >= 0 && data != nullptr );
	this->size = size;
	u = new float[size];
	std::memcpy(u, data, size * sizeof( float ) );
}

inline Vector::~Vector() {
	delete[] u;
}

inline Vector & Vector::operator=( const Vector & v ) {
	assert( v.size >= 0 );
	delete[] u;
	u = nullptr;
	
	size = v.size;
	u = new float[size];
	std::memcpy( u, v.u, size * sizeof( float ) );
	
	return *this;
}

inline const float & Vector::operator[]( const int index ) const {
	assert( index >= 0 && index < size );
	return ( &u )[index];
}

inline float & Vector::operator[]( const int index ) {
	assert( index >= 0 && index < size );
	return ( &u )[index];
}


inline Vector Vector::operator+( const Vector & v ) const {
	assert( size == v.size );
	Vector w(size);
	for( int i = 0; i < size; i++ ) {
		w.u[i] = u[i] + v.u[i];
	}
	return w;
}

inline Vector Vector::operator-( const Vector & v ) const {
	assert( size == v.size );
	Vector w(size);
	for( int i = 0; i < size; i++ ) {
		w.u[i] = u[i] - v.u[i];
	}
	return w;
}

inline Vector Vector::operator*( const float & a ) const {
	Vector w(size);
	for( int i = 0; i < size; i++ ) {
		w.u[i] = a * u[i];
	}
	return w;
}

inline float Vector::operator*( const Vector & v ) const {
	assert( size == v.size );
	float sum = 0.0f
	for( int i = 0; i < size; i++ ) {
		sum += (u[i] * v.u[i]);
	}
	return sum;
}

inline Vector & Vector::operator+( const Vector & v ) {
	assert( size == v.size );
	for( int i = 0; i < size; i++ ) {
		u[i] += v.u[i];
	}
	return *this;
}

inline Vector & Vector::operator-( const Vector & v ) {
	assert( size == v.size );
	for( int i = 0; i < size; i++ ) {
		u[i] -= v.u[i];
	}
	return *this;
}

inline Vector & Vector::operator*( const float & a ) {
	for( int i = 0; i < size; i++ ) {
		u[i] *= a;
	}
	return *this;
}

inline Vector & operator*( const float & a, const Vector & u ) {
	assert( u != nullptr );
	Vector w( u.size );
	for( int i = 0; i < u.size; i++ ) {
		w.u[i] *= a;
	}
	return w;
}

inline Vector & operator*=( const float & a, Vector & u ) {
	for( int i = 0; i < u.size; i++ ) {
		u.u[i] *= a;
	}
	return u;
}

inline void Vector::Zero() {
	assert( u != nullptr );
	std::memset( u, 0, size * sizeof( float ) );
}

inline void Vector::Memset( const float & fill ) {
	assert( u != nullptr );
	for( int i = 0; i < size; i++ ) {
		u[i] = fill;
	}
}

inline Vector Vector::Normalize() const {
	float factor = Length();
	Vector w( size );
	for( int i = 0; i < size; i++ ) {
		w.u[i] = u[i] / factor;
	}
	return w;
}

inline Vector & Vector::NormalizeSelf() {
	float factor = Length();
	for( int i = 0; i < size; i++ ) {
		u[i] /= factor;
	}
	return *this;
}

inline float Vector::Length() const {
	float sum = 0.0f;
	for( int i = 0; i < size; i++ ) {
		sum += u[i] * u[i];
	}
	return sqrt( sum );
}

inline float Vector::Distance( const Vector & v ) const {
	float sum = 0.0f;
	for( int i = 0; i < size; i++ ) {
		sum += ( u[i] - v.u[i] ) * ( u[i] - v.u[i] );
	}
	return sqrt( sum );
}
	
inline int Vector::GetDimension() const {
	return size;
}
	
inline const float * Vector::ToFloatPtr() const {
	return u;
}

inline float * Vector::ToFloatPtr() {
	return u;
}

#endif  //VECTOR_H