#include <stdio.h>
#include <conio.h>

#define INF 10000

//Preluare reprezentare tabelara din fisier text
//I: nume - nume fisier text
//E: n - nr de varfuri, m -  nr de muchii, t - tabel
unsigned char** citire_gn(char* nume, int &n, int &m)
{
	FILE* f;
	int i;
	unsigned char** t;

	f = fopen(nume, "rt");
	if (!f)
		t = NULL;
	else
	{
		fscanf(f, "%d %d", &n, &m);
		t = new unsigned char*[m];
		for (i = 0; i < n; i++)
			t[i] = new unsigned char[2];
		for (i = 0; i < m; i++)
			fscanf(f, "%d %d", &t[i][0], &t[i][1]);
		fclose(f);
	}
	return t;
}


//construire matricea de adiacenta
//I: n -nr varfuri m - nr muchii t -tabel
//E: a -  matricea de adiacenta
char** tab2ad(int n, int m, unsigned char** t)
{
	char **a;
	int i, j;

	a = new char*[n];
	for (i = 0; i < n; i++)
		a[i] = new char[n];
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			a[i][j] = 0;
	for (i = 0; i < n; i++)
		a[t[i][0] - 1][t[i][1] - 1] = a[t[i][1] - 1][t[i][0] - 1] = 1;
	return a;
}

//parcurgere in latime cu vector de distante
//I: a - matrice de adiacenta, n - nr de varfuri, v0 -varf initial
//E: lista - ordine de parcurgere, nvp - nr varfuri vizitate, p - vector de parinti
unsigned char* BF_distante(char** a, int n, int v0, int &nvp, int* &p)
{
	int* d;
	unsigned char* lista;
	int i, j, k;
	int done;
	int v;

	d = new int[n];
	p = new int[n];
	lista = new unsigned char[n];
	nvp = 0;
	for (i = 0; i < n; i++)
		d[i] = p[i] = INF;
	d[v0 - 1] = 0;
	p[v0 - 1] = 0;
	i = 0;
	done = 0;
	while (!done)
	{
		done = 1;
		for(j=0;j<n;j++)
			if (d[j] == i)
			{
				v = j + 1;
				lista[nvp++] = v;
				for(k=0;k<n;k++)
					if ((a[j][k] == 1) && (d[k] == INF))
					{
						p[k] = v;
						d[k] = d[j] + 1;
						done = 0;
					}
			}
		i = i + 1;
	}
	delete d;
	return lista;
}


void main()
{
	char numef[50] = "..\\graf.txt";
	unsigned char** tab;
	int nv, nm;
	int i, j;
	char** ad;
	int vi;
	unsigned char* ordine;
	int vparc;
	int* parinti;


	tab = citire_gn(numef, nv, nm);
	if (tab = NULL)
		printf("\nNu se poate prelua graful");
	else
	{
		/*printf("\nNumar varfuri: %2d, Numar muchii: %2d", nv, nm);
		printf("\nMuchii:");
		for (i = 0; i < nm; i++)
			printf("\n%2d %2d", tab[i][0], tab[i][1]);*/

		ad = tab2ad(nv, nm, tab);
		printf("\n Varf initial:");
		scanf("%d", &vi);
		ordine = BF_distante(ad, nv, vi, vparc, parinti);
		printf("\nOrdine de vizitare: ");
		for (i = 0; i < vparc; i++)
			printf("%d", ordine[i]);
		printf("\nParinti: ");
		for (i = 0; i < nv; i++)
			printf("\nVarful %2d a fost descoperit de varful %2d", i + 1, parinti[i]);

		//curatenie
		delete ordine;
		delete parinti;
		for (i = 0; i < nm; i++)
			delete tab[i];
		delete tab;
		for (i = 0; i < nv; i++)
			delete ad[i];
		delete ad;
	}
	printf("\nGata, apasa o tasta...");
	getch();
}