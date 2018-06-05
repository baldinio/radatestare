#include <stdio.h>
#include <conio.h>

#define INF 10000

typedef struct {
	int cost;
	char prec;
} ETICHETA ;

//Preluare graf ponderat din fisier text
//I: nume - nume fisier text
//E: n - nr de varfuri, m -  nr de muchii, t - tabel
int** citire_gp(char* nume, int &n, int &m)
{
	FILE* f;
	int i;
	int** t;

	f = fopen(nume, "rt");
	if (!f)
		t = NULL;
	else
	{
		fscanf(f, "%d %d", &n, &m);
		t = new int*[m];
		for (i = 0; i < n; i++)
			t[i] = new int[3];
		for (i = 0; i < m; i++)
			fscanf(f, "%d %d %d", &t[i][0], &t[i][1], &t[i][2]);
		fclose(f);
	}
	return t;
}


//construire matricea de adiacenta de ponderi
//I: n -nr varfuri m - nr muchii t -tabel
//E: a -  matricea de adiacenta
int** tab2w(int n, int m, int** t)
{
	int **a;
	int i, j;

	a = new int*[n];
	for (i = 0; i < n; i++)
		a[i] = new int[n];
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			a[i][j] = INF;
	for (i = 0; i < n; i++)
		a[t[i][0] - 1][t[i][1] - 1] = a[t[i][1] - 1][t[i][0] - 1] = t[i][2];
	return a;
}

//Dijkstra
//I: w - matrice de ponderi, n - nr de varfuri, v0 - varf initial
//E: e - vector de etichete
ETICHETA* mama(int** w, int n, int v0)
{
	char* a, *b;
	char ca, cb;
	int i, j, poz;
	ETICHETA* e;
	
	a = new char[n];
	b = new char[n - 1];
	cb = 0;
	a[0] = v0; ca = 1;
	for (i = 1; i <= n; i++)
		if (i != 0)
			b[cb++] = i;
	e = new ETICHETA[n];
	for (i = 0; i < n; i++)
		e[i].cost = INF;
	e[v0-1].cost = 0;
	e[v0 - 1].prec = -1;

	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < cb; j++)
			if (e[b[j] - 1].cost > e[a[ca - 1] - 1].cost + w[a[ca - 1] - 1][b[j] - 1])
			{
				e[b[j] - 1].cost = e[a[ca - 1] - 1].cost + w[a[ca - 1] - 1][b[j] - 1];
				e[b[j] - 1].cost = a[ca - 1];
			}
		poz = 0;
		for (j = 1; j < cb; j++)
			if (e[b[j] - 1].cost < e[b[poz] - 1].cost)
				poz = j;
		a[ca++] = b[poz];
		for (j = poz; j < cb - 1; i++)
			b[j] = b[j + 1];
		cb--;
	}
	delete a;
	delete b;
	return e;
}


void main()
{
	char numef[50] = "..\\..\\grafponderat.txt";
	int** tab;
	int nv, nm;
	int i;
	int** ponderi;
	int vi, v;
	ETICHETA* rez;

	tab = citire_gp(numef, nv, nm);
	if (tab = NULL)
		printf("\nNu se poate prelua graful");
	else
	{

		ponderi = tab2w(nv, nm, tab);
		printf("\n Varf initial:");
		scanf("%d", &vi);

		rez = mama(ponderi, nv, vi);
		for (i = 0; i < nv; i++)
		{
			printf("\nVirful %2d: Cost %3d, Drum ", i + 1, rez[i].cost);
			v = i + 1;
			do
			{
				printf("%d", v);
				v = rez[v - 1].prec;
			} while (v != -1);
		}
		//curatenie

		for (i = 0; i < nm; i++)
			delete tab[i];
		delete tab;
		for (i = 0; i < nv; i++)
			delete ponderi[i];
		delete ponderi;
		delete rez;
	}
	printf("\nGata, apasa o tasta...");
	getch();
}