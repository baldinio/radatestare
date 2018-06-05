#include <stdio.h>
#include <conio.h>

typedef struct {
	char cnp[14];
	char nume[30];
	int an;
	int grupa;
	unsigned char nrd;
	unsigned char note[20];
} STUDENT;

void main()
{
	FILE* f;
	char numef[50];
	STUDENT x;
	int i, c;
	FILE* g;
	char numet[50];

	printf("Nume fisier binar: "); gets_s(numef);
	f = fopen(numef, "rb");
	if (!f)
		printf("Nu se poate deschide fisierul %s", numef);
	else
	{
		printf("\nNume fisier text (lista): "); gets_s(numet);
		g = fopen(numet, "wt");
		fprintf(g, "\t\tLista studentilor");
		fprintf(g, "\n\nNr. %-13s %-30s An Grupa Note","CNP","Nume si prenume");
		c = 0; // list creation start
		fread(&x, sizeof(STUDENT), 1, f);
		while (!feof(f))
		{
			fprintf(g, "\n%3d %-13s %-30s %2d %5d ", ++c, x.cnp, x.nume, x.an, x.grupa);
			for (i = 0; i < x.nrd; i++)
				fprintf(g, "%2d ",x.note[i]);
			fread(&x, sizeof(STUDENT), 1, f);
		} // list creation end
		fclose(f);
		fclose(g);
		printf("\n\nLista se afla in fisierul %s", numet);
	}
	printf("\nGata, apasa o tasta...");
	getch();
}

