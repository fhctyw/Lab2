#include <iostream>
#include <cmath>
using namespace std;

// input
int A[9] = {1, 2, 3, 4, 13, 14, 16, 17, 21};
int C[9] = {1, 9, 10, 11, 12, 13, 18, 19, 24};
int B[10] = {1, 3, 4, 5, 6, 13, 14, 15, 20, 21};

// output
int F[4];

// A \ B
void Divide(const int *a, const int size_a, const int *b, const int size_b, int *c, int &size_c)
{
	int index = 0;
	int* tmp = new int[size_a];
	for (int i = 0; i < size_a; i++)
	{
		for (int j = 0; j < size_b; j++)
		{
			if (a[i] == b[j])
			{
				tmp[index] = i;
				index++;
			}
		}
	}

	size_c = size_a - index;
	int *res = new int[size_c];

	for (int i = 0, i1 = 0; i < size_a; i++)
	{
 		if (i == tmp[i1])
		{
			i1++;
		}
		else
		{
			res[i - i1] = a[i];
		}
	}

	for (int i = 0; i < size_c; i++)
	{
		cout << res[i] << endl;
	}

	delete[] tmp;
	tmp = nullptr;
	delete c;
	
	c = res;
}

// ((A u C)\C u B)\(!C) 

/*
int A1[] = { 1, 2, 3, 4 ,9, 10, 11, 12, 13, 14, 16, 17, 18, 19, 21, 24 };

int C1[9] = { 1, 9, 10, 11, 12, 13, 18, 19, 24 };

int Result[] = { 2, 3, 4, 14, 16, 17, 21 };
int B[10] = { 1, 3, 4, 5, 6, 13, 14, 15, 20, 21 };

int temp[] = { 1, 2, 3, 4, 5, 6, 13, 14, 15, 16, 17, 20, 21 };



int res[] = { 2, 3, 4, 5, 6, 7, 8, 14, 17, 20, 21, 22, 23, 25 };


int finialResult[] = { 1, 13, 15, 16 };
*/

// A u B
void unification(const int *a, const int size_a, const int *b, const int size_b, int *c, int &size_c)
{
	//	{1, 2, 3, 4, 13, 14, 16, 17, 21};
	//	{1, 9, 10, 11, 12, 13, 18, 19, 24};

	int* tmp = new int[size_b];
	int indexTmpArray = 0;

	for (int i = 0; i < size_a; i++)
	{
		for (int j = 0; j < size_b; j++)
		{
			if (a[i] == b[j])
			{
				tmp[indexTmpArray] = a[i];
				indexTmpArray++;
			}
		}
	}

	int* tmp1 = new int[indexTmpArray];
	for (int i = 0; i < indexTmpArray; i++)
	{
		tmp1[i] = tmp[i];
	}
	delete[] tmp;
	tmp = nullptr;
	
	size_c = size_b - indexTmpArray;
	int* tmp2 = new int[size_c];
	int indexTmp1Array = 0;

	for (int i = 0; i < size_b; i++)
	{
		for (int j = 0; j < indexTmpArray; j++)
		{
			if (b[i] != tmp1[j])
			{
				tmp2[i] = b[i];
				indexTmp1Array++;
			}
			
		}
	}

	for (int i = 0; i < size_c; i++)
	{
		cout << tmp2[i] << endl;
	}

	int size = size_a + indexTmpArray;
	c = new int[size];



}


int main()
{
	int arr_1[20];
	int size_arr_1;
	//unification(A, 9, C, 9, arr_1, size_arr_1);
	
	while (true) {
	int* res = NULL;
	int size_res;
	Divide(A, 9, C, 9, res, size_res);
	
	for (int i = 0; i < size_res; i++)
	{
		cout << res[i] << endl;
	}

		delete[] res;
	}

	return 0;
}
