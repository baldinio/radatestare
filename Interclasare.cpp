#include <stdio.h>
#include <conio.h>

// Interclasare doua secvente consecutive sortate dintr-un vector
//I: a - adresa vector; p1, s1 - capete prima secventa ; p2, s2 - capete a doua secventa
//E: -
void interclasare(float* a, int p1, int s1, int p2, int s2) 
{
	int i, j, k;
	float *t;

	t = new float[s2 - p1 + 1];
	// ^ t = (float*)malloc(sizeof(float)*(s2 - p1 + 1));
	
	i = p1; j = p2; k = 0;
	while ((i <= s1) && (j <= s2))
		if (a[i] < a[j])
			t[k++] = a[i++];
		else
			t[k++] = a[j++];
	while (i <= s1)
		t[k++] = a[i++];
	while (j <= s2)
		t[k++] = a[j++];
	for (i = 0;i < k;i++)
		a[p1++] = t[i];
	delete t;
}

// Sortare prin interclasare
//I: v - vector ; s,d - capete secventa de sortat
//E: -
void sortare_I(float * v, int s, int d)
{
	if (s < d)
	{
		sortare_I(v, s, (s + d) / 2);
		sortare_I(v, (s + d) / 2 + 1, d);
		interclasare(v, s, (s + d) / 2, (s + d) / 2 + 1, d);
	}
}

void main()
{
	float x[] = { 15,19,28,25,29,7,10,3,9,21,18,19,2,13,18,9,7,4,4,27,21,23,14 };
	int n = 23;
	int i;

	sortare_I(x, 0, n - 1);
	printf("\nSortare prin interclasare:\n");
	for (i = 0;i < n;i++)
		printf("%4.1f ", x[i]);

	printf("\n\nGata. Apasa o tasta...");
	getch();
}