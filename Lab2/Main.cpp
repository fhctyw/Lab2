#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;


// Your defines

#define VERSION_2

/*
	#define VERSION_1
	
	OR

	#define VERSION_2
*/

#define GET_ARRAY_LENGHT _countof

int UniversalPluralSize;
int* UniversalPlural;

// input

#ifdef VERSION_1
int A[] = { 1, 2, 3, 4, 13, 14, 16, 17, 21 };
int B[] = { 1, 3, 4, 5, 6, 13, 14, 15, 20, 21 };
int C[] = { 1, 9, 10, 11, 12, 13, 18, 19, 24 };

const int SizeA = GET_ARRAY_LENGHT(A);
const int SizeB = GET_ARRAY_LENGHT(B);
const int SizeC = GET_ARRAY_LENGHT(C);

#endif // VERSION_1

#ifdef VERSION_2

int A[] = { 1, 8, 9 };
int B[] = { 6, 8 };

const int SizeA = GET_ARRAY_LENGHT(A);
const int SizeB = GET_ARRAY_LENGHT(B);

#endif // VERSION_1

// from = -100, to = 200 = {-100, -99, -98 ... 198, 199, 200 }
void SetUniversalPlural(const int from, const int to)
{
	UniversalPluralSize = to - from + 1;
	UniversalPlural = new int[UniversalPluralSize];
	for (int i = 0; i < UniversalPluralSize; i++)
	{
		UniversalPlural[i] = from + i;
	}
}

// Print array
void PrintPluar(const int* p, const int size, const char* addString = nullptr)
{
	if (addString != nullptr)
	{
		cout << "[" << addString << "] ";
	}

	cout << "{";
	for (int i = 0; i < size; i++)
	{
		cout << p[i];
		if (i != size - 1)
		{
			cout << ", ";
		}
	}
	cout << "}" << endl;
}

// A \ B
// {0, 4, -1, 5} \ {2, 3, 5, -2, 0} = {4, -1}
int* Divide(const int* a, const int size_a, const int* b, const int size_b, int& size, bool isSort = true)
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

	size = size_a - index;
	int* res = new int[size];

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

	delete[] tmp;
	tmp = nullptr;

	if (isSort)
		sort(res, res + size);

	return res;
}

// A + B
// {0, 1, 2, 3} + {5, 8, 0, 1, 2} = {0, 1, 2, 3, 5, 8, 0, 1, 2}
int* Add(const int* a, const int size_a, const int* b, const int size_b, int& size, bool isSort = true)
{
	size = size_a + size_b;
	int* res = new int[size];
	int total = 0;

	for (int i = 0; i < size_a; i++, total++)
	{
		res[i] = a[i];
	}

	for (int i = 0; i < size_b && total < size; i++, total++)
	{
		res[total] = b[i];
	}

	if (isSort)
		sort(res, res + size);

	return res;
}

// A u B
// {0, -1, -3, 5, 4, 9} u {3, 2, 5, 6, 7} = {-3, -1, 0, 2, 3, 4, 5, 6, 7, 9 }
int* Unification(const int* a, const int size_a, const int* b, const int size_b, int& size, bool isSort = true)
{
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
		//cout << tmp[i] << " ";
	}

	delete[] tmp;
	tmp = nullptr;
	int s;
	int* tmp2 = Divide(b, size_b, tmp1, indexTmpArray, s);

	delete[] tmp1;

	int* res = Add(tmp2, s, a, size_a, size);

	if (isSort)
		sort(res, res + size);

	return res;
}

// !A
// {1, 3, 5, 7, 14} = { 2, 4, 6, 8, 9, 10, 11, 12, 13, 15, ... , 25 }
int* Not(const int* a, const int size_a, int& size, bool isSort = true)
{
	return Divide(UniversalPlural, UniversalPluralSize, a, size_a, size);
}

// A ^ B
//   { 0, -1, 3, 5, 6 } ^ { 2, 3, 9, 10, 6 } = { 3, 6 }
int* Cut(const int* a, const int size_a, const int* b, const int size_b, int& size, bool isSort = true)
{
	int s = 0;
	for (int i = 0; i < size_a; i++)
	{
		for (int j = 0; j < size_b; j++)
		{
			if (a[i] == b[j])
			{
				s++;
			}
		}
	}

	size = s;
	int* res = new int[size];
	for (int i = 0, s = 0; i < size_a; i++)
	{
		for (int j = 0; j < size_b; j++)
		{
			if (a[i] == b[j])
			{
				res[s] = a[i];
				s++;
			}
		}
	}

	if (isSort)
		sort(res, res + size);

	return res;
}

// A x B
// {0, 3, 5} x {3, 7} = { (0, 3), {0, 7}, (3, 3), (3, 7), (5, 3), (5, 7) }
int*** Multiply(const int* a, const int size_a, const int* b, const int size_b, int size[], bool isPrinted = false, const char* addString = nullptr)
{
	if (size != nullptr)
	{
		size[0] = size_a;
		size[1] = size_b;
		size[2] = 2;
	}

	int*** res = new int** [size_a];
	for (int i = 0; i < size_a; i++)
	{
		res[i] = new int* [size_b];
		for (int j = 0; j < size_b; j++)
		{
			int* consist = new int[2]{ a[i], b[j] };
			res[i][j] = consist;
		}
	}

	if (isPrinted) {
		if (addString != nullptr)
		{
			cout << "[" << addString << "] ";
		}

		cout << "{";
		for (int i = 0; i < size_a; i++)
		{
			for (int j = 0; j < size_b; j++)
			{
				cout << "(" << res[i][j][0] << ", " << res[i][j][1] << ") ";
			}
			if (i == size_a - 1)
			{
				cout << "}" << endl;
			}
		}
	}

	return res;
}

// A^2
// {0, 3, 5}^2 = {(0, 0), (0, 3), (0, 5), ()}
int*** Pow2(const int* a, const int size_a, int size[], bool isPrinted = false, const char* addString = nullptr)
{
	if (size != nullptr)
	{
		size[0] = size_a;
		size[1] = 2;
	}

	int*** res = new int** [size_a];
	for (int i = 0; i < size_a; i++)
	{
		res[i] = new int* [size_a];
		for (int j = 0; j < size_a; j++)
		{
			int* consist = new int[2]{ a[i], a[j] };
			res[i][j] = consist;
		}
	}

	if (isPrinted) {
		if (addString != nullptr)
		{
			cout << "[" << addString << "] ";
		}

		cout << "{";
		for (int i = 0; i < size_a; i++)
		{
			for (int j = 0; j < size_a; j++)
			{
				cout << "(" << res[i][j][0] << ", " << res[i][j][1] << ") ";
			}
			if (i == size_a - 1)
			{
				cout << "}" << endl;
			}
		}
	}

	return nullptr;
}

int main()
{
	// U[25]
	SetUniversalPlural(1, 25);

#ifdef VERSION_1

	PrintPluar(UniversalPlural, UniversalPluralSize, "U");
	PrintPluar(A, SizeA, "A");
	PrintPluar(B, SizeB, "B");
	PrintPluar(C, SizeC, "C");
	cout << endl;

	// A u C
	int size_p1;
	int* p1 = Unification(A, SizeA, C, SizeC, size_p1);
	PrintPluar(p1, size_p1, "A u C");

	// !C
	int size_p2;
	int* p2 = Not(C, SizeC, size_p2);
	PrintPluar(p2, size_p2, "!C");

	// (A u C) \ C
	int size_p3;
	int* p3 = Divide(p1, size_p1, C, SizeC, size_p3);
	PrintPluar(p3, size_p3, "(A u C) \\ C");

	// ((A u C) \ C) u B
	int size_p4;
	int* p4 = Unification(p3, size_p3, B, SizeB, size_p4);
	PrintPluar(p4, size_p4, "((A u C) \\ C) u B");

	// (((A u C) \ C) u B) \ (!C)
	int size_p5;
	int* p5 = Divide(p4, size_p4, p2, size_p2, size_p5);
	PrintPluar(p5, size_p5, "((A u C)\\C u B)\\(!C)");
#endif // VERSION_1

#ifdef VERSION_2

	PrintPluar(A, SizeA, "A");
	PrintPluar(B, SizeB, "B");
	cout << endl;

	int* size = nullptr; // тому що ми не використовуєм size
	int*** pluar = Multiply(A, SizeA, B, SizeB, size, true, "AxB");
	pluar = Pow2(A, SizeA, size, true, "A^2");
#endif // VERSION_2

	return 0;
}