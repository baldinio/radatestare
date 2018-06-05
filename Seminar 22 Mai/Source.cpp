#include<stdio.h>
#include<conio.h>

#define INF 10000

typedef struct {
	int cost;
	char prec;
}ETICHETA;


//preluare graf ponderat, in forma tabelara, din fisier text
//I: nume - nume fisier text
//E: n - nr. virfuri; m - nr. muchii; t - tabel (NULL daca nu se poate citi graful)
int** citire_gp(char nume[], int &n, int &m)
{
	int** t;
	int i;
	FILE* f;

	f = fopen(nume, "rt");
	if (!f)
	{
		t = NULL;n = 0;m = 0;
	}
	else
	{
		fscanf(f, "%d %d", &n, &m);
		t = new int*[m];
		for (i = 0;i < m;i++)
			t[i] = new int[3];
		for (i = 0;i < m;i++)
			fscanf(f, "%d %d %d", &t[i][0], &t[i][1], &t[i][2]);
		fclose(f);
	}
	return t;
}


//conversie reprezentare tabelara in matrice de ponderi
//I: n - nr. virfuri; m - nr. muchii; t - tabel
//E: a - matrice de ponderi
int** tab2w(int n, int m, int** t)
{
	int i,j;
	int** a;

	a = new int*[n];
	for (i = 0;i < n;i++)
	{
		a[i] = new int[n];
		for (j = 0;j < n;j++)
			a[i][j] = INF;
	}
	for (i = 0;i < m;i++)
		a[t[i][0]-1][t[i][1]-1] = a[t[i][1] - 1][t[i][0] - 1] = t[i][2];
	return a;
}

//Dijkstra
//I: w - matrice de ponderi, n - nr. virfuri, v0 - virf initial
//E: e - vector de etichete
ETICHETA* mama(int** w, int n, int v0)
{
	char* a, *b;
	int ca, cb;
	int i, j, poz;
	ETICHETA* e;

	a = new char[n];
	b = new char[n - 1];
	cb = 0;
	a[0] = v0; ca = 1;
	for (i = 1;i <= n;i++)
		if (i != v0)
			b[cb++] = i;
	e = new ETICHETA[n];
	for (i = 0;i < n;i++)
		e[i].cost = INF;
	e[v0 - 1].cost = 0;
	e[v0 - 1].prec = -1;

	/*printf("\n");
	for (i = 0;i < ca;i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	for (i = 0;i < cb;i++)
	{
		printf("%d ", b[i]);
	}
	printf("\n");
	for (i = 0;i < n;i++)
	{
		printf("c:%d, p:%d", e[i].cost, e[i].prec);
	}*/


	for (i = 0;i < n - 1;i++)
	{
		for(j=0;j<cb;j++)
			if (e[b[j] - 1].cost > e[a[ca - 1] - 1].cost + w[a[ca - 1] - 1][b[j] - 1])
			{
				e[b[j] - 1].cost = e[a[ca - 1] - 1].cost + w[a[ca - 1] - 1][b[j] - 1];
				e[b[j] - 1].prec = a[ca - 1];
			}
		poz = 0;
		for (j = 1;j < cb;j++)
			if (e[b[j] - 1].cost < e[b[poz] - 1].cost)
				poz = j;
		a[ca++] = b[poz];
		for (j = poz;j < cb - 1;j++)
			b[j] = b[j + 1];
		cb--;
	}
	delete a;
	delete b;
	return e;
}

//construire arbore partial de cost minim (algoritmul lui Prim)
//I: w - matrice de ponderi, n - nr. virfuri, v0 - virf initial
//E: muchii - muchiile arborelui construit, c - cost arbore
int** Prim(int** w, int n, int v0, int &c)
{
	int** muchii;
	int i, j, k;
	char* viz;
	int v1, v2;
	int min;

	muchii = new int*[n - 1];
	for (i = 0;i < n - 1;i++)
		muchii[i] = new int[2];
	viz = new char[n];
	for (i = 0;i < n;i++)
		viz[i] = 0;
	viz[v0-1] = 1;
	c = 0;
	for (i = 0;i < n - 1;i++)
	{
		min = INF;
		for(j=1;j<=n;j++)
			if(viz[j-1]==1)
				for(k=1;k<=n;k++)
					if ((viz[k - 1] == 0) && (w[j - 1][k - 1] < min))
					{
						v1 = j;
						v2 = k;
						min = w[j - 1][k - 1];
					}
		muchii[i][0] = v1;
		muchii[i][1] = v2;
		viz[v2 - 1] = 1;
		c += w[v1 - 1][v2 - 1];
	}
	delete viz;
	return muchii;
}

void main()
{
	char numef[50]="..\\..\\graf_ponderat.txt";
	int nv, nm;
	int** tab;
	int** ponderi;
	int vi, v;
	int i;
	ETICHETA* rez;
	int** arbore;
	int cost;


	//printf("Nume fisier text: ");
	//gets_s(numef);
	tab = citire_gp(numef, nv, nm);
	if (!tab)
		printf("\nNu s-a putut prelua graful din fisier");
	else
	{
		ponderi = tab2w(nv, nm, tab);
		printf("\nVirf initial: ");
		scanf("%d", &vi);
		
		/*rez = mama(ponderi, nv, vi);
		for (i = 0;i < nv;i++)
		{
			printf("\nVirful %2d: Cost= %3d, Drum= ", i + 1, rez[i].cost);
			v = i + 1;
			do
			{
				printf("%d ", v);
				v = rez[v - 1].prec;
			} 
			while (v != -1);
		}*/

		arbore = Prim(ponderi, nv, vi, cost);
		printf("\nArbore partial cu costul %3d si muchiile:", cost);
		for (i = 0;i < nv - 1;i++)
			printf("\nMuchia: %2d -> %2d, Cost: %2d", arbore[i][0], arbore[i][1], ponderi[arbore[i][0]-1][arbore[i][1]-1]);


		//dezalocare: tab, ad, ordine, parinti
		
		for (i = 0;i < nm;i++)
			delete tab[i];
		delete tab;
		for (i = 0;i < nv;i++)
			delete ponderi[i];
		delete ponderi;
		//delete rez;
		for (i = 0;i < nv - 1;i++)
			delete arbore[i];
		delete arbore;
	}


	printf("\n\nGata, apasa o tasta ...");
	getch();
}