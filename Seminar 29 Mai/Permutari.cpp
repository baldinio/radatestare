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

	fprintf(f, "\nSolutia %3d -> ",++c);
	for (i = 0; i < n; i++)
		fprintf(f, "%2d ", x[i]);
}

//generare permutari de n elemente
//I: n - dimensiune permutare, f - fisier text (deschis)
//E: c - contor solutie
void permutari(int n, FILE* f, int &c)
{
	int *x;
	int i; // - pozitia barei
	int vb;

	x = new int[n];
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
			if (i == n - 1)
				retine(x, n, f, c);
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
	int dim; // dimensiunea permutarii
	int contor;

	printf("\nDimensiune permutare: ");
	scanf("%d", &dim);

	sprintf(numef, "Permutari_de_%d.txt", dim);
	fisier = fopen(numef,"wt");
	if (!fisier)
		printf("\nNu se poate crea fisierul text pentru rezultate");
	else
	{
		permutari(dim, fisier,contor);
		printf("\nAm generat %d permutari care sunt in fisierul %s", contor, numef);
		fclose(fisier);
	}

	printf("\n\nGata, apasa o tasta...");
	getch();
}