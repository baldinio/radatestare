#include <stdio.h>
#include <conio.h>

//conditia de validare partiala
//I: x - solutia construita, i - pozitia de validat
//E: vb - 1 acceptabil 0 neacceptabil
int acceptabil(int*x, int i)
{
	int vb;
	int j;

	vb = 1;
	for (j = 0; j < i; j++)
		if (x[i] == x[j])
			vb = 0;
	return vb;
}

//retinere solutie
//I: x - solutia construita, n - lungime solutie, f - fisier text in care scriu solutia, c - contor solutii
//E: c - contor solutii
void retine(int*x, int n, FILE* f, int &c)
{
	int i;

	fprintf(f, "\nSolutia %3d -> ", ++c);
	for (i = 0; i < n; i++)
		fprintf(f, "%2d ", x[i]);
}

//generare permutari de n elemente
//I: n,k - dimensiune aranjamente, f - fisier text (deschis)
//E: c - contor solutie
void aranjamente(int n,int k, FILE* f, int &c)
{
	int *x;
	int i; // - pozitia barei
	int vb;

	x = new int[k];
	c = 0;

	i = 0;
	x[0] = 0;
	while (i >= 0)
	{
		vb = 0;
		while ((x[i] < n) && (vb == 0))
		{
			x[i] = x[i] + 1; // atribuire
			vb = acceptabil(x, i);
		}
		if (vb == 1)
			if (i == k - 1)
				retine(x, k, f, c);
		// revenire dupa construirea unei solutii
			else
			{
				i = i + 1; // avansare
				x[i] = 0;
			}
		else
			i = i - 1;  // revenire
	}
	delete x;
}

void main()
{
	FILE* fisier;
	char numef[50];
	int dim, cate;
	int contor;

	printf("\nAranjamente de: ");
	scanf("%d", &dim);
	printf("\nAranjamente luate cate: ");
	scanf("%d", &cate);

	sprintf(numef, "Aranjamente_de_%d_cate_%d.txt", dim,cate);
	fisier = fopen(numef, "wt");
	if (!fisier)
		printf("\nNu se poate crea fisierul text pentru rezultate");
	else
	{
		aranjamente(dim,cate, fisier, contor);
		printf("\nAm generat %d aranjamente care sunt in fisierul %s", contor, numef);
		fclose(fisier);
	}

	printf("\n\nGata, apasa o tasta...");
	getch();
}