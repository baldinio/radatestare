#include <stdio.h>
#include <conio.h>

//gasire pivot
//I: v -vector; p,u - capete secventa curenta
//E: k -indice pivot

int pivot(float *v, int p, int u)
{
	int i, j, di, dj;
	float t;
	i = p;
	j = u;
	di = 0;
	dj = -1;
	while (i < j)
	{
		if (v[i] > v[j])
		{
			t = v[i];v[i] = v[j];v[j] = t;
			if (di == 0)
			{
				di = 1;dj = 0;

			}
			else
			{
				di = 0;dj = -1;
			}
		}
		i += di;j += dj;
	}
	return i;
}

//sortare rapida
//I: x-vector; s,d - capete secventa curenta
//E: -

void sortare_rapida(float* x, int s, int d)
{
	int k;
	if (s < d)
	{
		k = pivot(x, s, d);
		sortare_rapida(x, s, k - 1);
		sortare_rapida(x, k + 1, d);
	}
}

void main()
{
	float x[] = { 15,19,28,25,29,7,10,3,9,21,18,19,2,13,18,9,7,4,4,27,21,23,14 };
	int n = 23;
	int i;

	sortare_rapida(x, 0, n - 1);
	printf("\nSortare prin interclasare:\n");
	for (i = 0;i < n;i++)
		printf("%4.1f ", x[i]);

	printf("\n\nGata. Apasa o tasta...");
	getch();
}