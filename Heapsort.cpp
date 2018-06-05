#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

//arrange heap
//I: v- vector address; n -size; i - position to be arranged
//E: -

void arrange_heap(float* v, int n,int i)
{
	int s, d, max;
	float t;

	s = 2 * i;
	d = 2 * i + 1;
	if ((s <= n) && (v[s] > v[i]))
		max = s;
	else max = i;
	if ((d <= n) && (v[d] > v[max]))
		max = d;
	if (max != i)
	{
		t = v[i];
		v[i] = v[max];
		v[max] = t;
		arrange_heap(v, n, max);
	}
}

//build heap
//I: v - vector address; n - size
//E: - 

void build_heap(float* v, int n)
{
	int i;
	for (i = n / 2;i >= 1;i--)
		arrange_heap(v, n, i);
}

//heap sort
//I: v - vector address; n- size
//E: -

void h_sort(float* v, int n)
{
	int i;
	int t;

	build_heap(v, n);
	for (i = n;i >= 2;i--)
	{
		t = v[1];
		v[1] = v[i];
		v[i] = t;
		arrange_heap(v, i, 1);
	}
}

void main()
{
	float *x;
	int l = 30;
	int min = 0;
	int max = 100;
	int i;

	x = new float[l+1];
	for (i = 1;i < l+1;i++)
		x[i] = (double)rand() / (RAND_MAX + 1)*(max - min) + min;

	printf("\nInitial vector:\n");
	for (i = 1;i < l+1;i++)
		printf("%5.2f ", x[i]);

	h_sort(x, l+1);

	printf("\nSorted vector:\n");
	for (i = 1;i < l+1;i++)
		printf("%5.2f ", x[i]);

	delete x;
	printf("\nDone. Press a key...");
	getch();

}