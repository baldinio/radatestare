#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

// Counting sort
//I: v -vector address ; n -size; k - max value (exclusive)
//E: -

void c_sort(int* v, int n, int k)
{
	int* c, *t;
	int i;

	c = new int[k];
	for (i = 0;i < k;i++)
		c[i] = 0;

	for (i = 0;i < n;i++)
		c[v[i]]++;

	for (i = 1;i < k;i++)
		c[i] += c[i - 1];

	t = new int[n];
	for (i = n - 1;i >= 0;i--)
	{		t[c[v[i]] - 1] = v[i];
			c[v[i]]--;
	}

	for (i = 0;i < n;i++)
		v[i] = t[i];

	delete t;
	delete c;
}

void main()
{
	int *x;
	int l = 30;
	int min = 0;
	int max = 100;
	int i;

	x = new int[l];
	for (i = 0;i < l;i++)
		x[i] = (double)rand() / (RAND_MAX + 1)*(max - min) + min;

	printf("\nInitial vector:\n");
	for (i = 0;i < l;i++)
		printf("%3d ", x[i]);

	c_sort(x, l, max);

	printf("\nSorted vector:\n");
	for (i = 0;i < l;i++)
		printf("%3d ", x[i]);

	delete x;
	printf("\nDone. Press a key...");
	getch();

}