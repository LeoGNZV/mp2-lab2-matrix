#include <iostream>
#include "tmatrix.h"
using namespace std;

void main()
{
	cout << "Hi, this is an application that allows you to set matrices and perform basic operations on them." << endl;
	
	size_t m_sz;
	cout << "Enter the size of the matrix: " << endl;
	cin >> m_sz;

	TDynamicMatrix<int> m1(m_sz);
	cout << "Enter the elements of the matrix: " << endl;
	cin >> m1;
	cout << "Select the mode of working with the matrix: " << endl;
	size_t choice;
	cout << "1 - Multiplication by scalar\n2 - Matrix addition\n 3 - Matrix Subtraction\n4 - Matrix multiplication" << endl;
	cin >> choice;

	if (choice == 1)
	{
		size_t p;
		cout << "Enter the element to multiply: " << endl;
		cin >> p;
		cout << "The result of the operation: " << m1 * p;
	}
	else if (choice == 2)
	{
		TDynamicMatrix<int> m2(m_sz);
		cout << "Enter the elements of the second matrix: " << endl;
		cin >> m2;
		cout << "The result of the operation: " << m1 + m2;
	}
	else if (choice == 3)
	{
		TDynamicMatrix<int> m2(m_sz);
		cout << "Enter the elements of the second matrix: " << endl;
		cin >> m2;
		cout << "The result of the operation: " << m1 - m2;
	}
	else if (choice == 4)
	{
		TDynamicMatrix<int> m2(m_sz);
		cout << "Enter the elements of the second matrix: " << endl;
		cin >> m2;
		cout << "The result of the operation: " << m1 * m2;
	}
	else
	{
		cout << "The entered number does not correspond to any of the operations." << endl;
	}
}