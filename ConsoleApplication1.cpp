// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <list>
#include <limits.h>


using namespace std;


//combinari recursiv c11
long comb(unsigned a, unsigned b)
{
	long c;
	if (b > a)
		c = 0;
	else if ((b == 0) || (b == a))
		c = 1;
	else
		c = comb(a - 1, b) + comb(a - 1, b - 1);
	return c;
	
}

//c14 aparitii vector recursiv


int frequency(int v[],int x,int dimensiune)
{
	int Number = 0;
	if(dimensiune ==0)
			return Number;
	else {
		for (int i = 0; i < dimensiune; i++)
		{
			if (v[i] == x)
				Number = 1;
			else
				Number = 0;
		}

		return Number + frequency(v, x, dimensiune - 1);

	}
}
//c13 cautare binara recursiva a unei valori intr un vector sortat 
int BinarySearch(int A[], int value, int low, int high)//low= 0 si high este cate element ai in vector-1
{
	
	if (high < low)
		return -1;
	else {
		int mid = low + ((high - low) / 2);
		if (A[mid] > value)
			return BinarySearch(A, value, low, mid - 1);
		else if (A[mid] < value)
			return BinarySearch(A, value, mid + 1, high);
		else
			return mid;// found
	}
	
}
//c 39 toate submultimile unei multimi cu n elemente
char sp2[] = "               ";
int x2[20], n2, nrsol2 = 0;

void Afisare2()
{
	int i;
	cout << sp2 << "{ ";
	for (i = 1; i <= n2; i++)
		if (x2[i] == 1) cout << i << " ";
	cout << char(8) << "}" << endl;
	nrsol2++;
}

void BackRec2(int k)
{
	int i;
	for (i = 0; i <= 1; i++)
	{
		x2[k] = i;
		if (k == n2) Afisare2();
		else BackRec2(k + 1);
	}
}

// c40 coin change
int count(int S[], int m, int n)//n= suma,s=vectorul cu bacnote,m=s.length
{
	// If n is 0 then there is 1 solution 
	// (do not include any coin)
	if (n == 0)
		return 1;

	// If n is less than 0 then no 
	// solution exists
	if (n < 0)
		return 0;

	// If there are no coins and n 
	// is greater than 0, then no
	// solution exist
	if (m <= 0 && n >= 1)
		return 0;

	// count is sum of solutions (i) 
	// including S[m-1] (ii) excluding S[m-1]
	return count(S, m - 1, n) + count(S, m, n - S[m - 1]);
}
//c19 functie pe ramuri
int h(int a, int b, int m, int n)
{
	return((m == 1) ? n : ((n == 1) ? m : (a *h(a, b, m - 1, n) + b * h(a, b, m, n - 1))));

}
//c6 cmmdc divide et impera
int cmmdc(int st, int dr, int x[])
{
	int m, m1, m2, r;
	if (st == dr)
		return x[st];
	else
	{
		m = (st + dr) / 2;
		m1 = cmmdc(st, m, x);
		m2 = cmmdc(m + 1, dr, x);
		r = m1 % m2;
		while (r)
		{
			m1 = m2;
			m2 = r;
			r = m1 % m2;
		}
		return m2;
	}
}

int main()
{

	/*unsigned n = 30;
	unsigned k = 20;
	long rez = comb(n, k);
	cout << rez << endl;

	int v[] = { 1,3,45,2,4,1,22,5,1 };
	int dimensiune = 9;
	int x = 1;
	int rez2 = frequency(v, x, dimensiune);
	cout << rez2 << endl;*/
	
	/*int arr[] = { 1,4,6,12,33,44,53,61,74 };
	int low = 0;
	int high =8;
	int key = 44;
	
	int x= BinarySearch(arr, key, low, high);
	cout << x << endl;
	*/
	/*cout << endl << endl << sp2 << "Submultimile multimii {1,2,3.....,n}" << endl;
	cout << endl << sp2 << " Dati valoarea lui n: "; cin >> n2;
	cout << endl;
	BackRec2(1);
	cout << endl << sp2 << "Numar solutii: " << nrsol2;*/
	
	/*int arr[] = { 1, 2};
	int m = sizeof(arr) / sizeof(arr[0]);
	printf("%d ", count(arr, m, 4));
	getchar();
*/
	/*int x[] = { 40,120,50,440,1200,60,480,180 };
	int n = 8;
	cout << cmmdc(1, n, x);*/



	int a = 1, b = 40, m = 5, n = 1;
		
	cout << h(a, b, m, n) <<endl;
	
    return 0;
}

