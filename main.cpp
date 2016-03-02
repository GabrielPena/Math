#include "Matrix.hpp"
#include <iostream>

int main() {
	Matrix x( 3,3 );
	Matrix y( 3,3 );
	x.Memset(2);
	y.Memset(5);
	
	Matrix z(3,3);
	z.Memset(1);
	z = 3.0f * z;//x * y;

	for( int i = 0; i < x.GetNumRows(); i++ ) {
		for( int j = 0; j < x.GetNumCols(); j++ ) {
			std::cout << z[i][j] << " ";
		}
		std::cout << "\n";
	}
	
	return 0;
}