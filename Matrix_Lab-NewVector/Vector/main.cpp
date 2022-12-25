#include <iostream>
#include "Vector.h"
#include "Matrix.h"
using namespace std;


int main()
{
	TDynamicMatrix<int> a(3);

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			a[i][j] = i - j + 3;
	cout << a << endl;

	TDynamicMatrix<int> b(a);

	b = b * a;
	cout << b << endl;

	return 0;
}