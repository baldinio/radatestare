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
	int i;

	printf("Nume fisier binar: "); gets_s(numef);
	f = fopen(numef, "wb");
	if (!f)
		printf("Nu se poate crea fisierul %s", numef);
	else
	{
		printf("\nCNP: "); gets_s(x.cnp);
		while (!feof(stdin))
		{
			printf("Nume: "); gets_s(x.nume);
			printf("An: "); scanf("%d", &x.an);
			printf("Grupa: "); scanf("%d", &x.grupa);
			printf("Nr. discipline: "); scanf("%d", &x.nrd);
			for (i = 0; i < x.nrd; i++)
				x.note[i] = 0;
			
			fwrite(&x, sizeof(STUDENT), 1, f);
			printf("\nCNP: "); 
			// fflush(stdin);
			gets_s(x.cnp);
			if(x.cnp[0]==0)
				gets_s(x.cnp); // <- fflush(stdin) in Visual Studio
		}
		fclose(f);
		printf("\nA fost creat fisierul binar %s", numef);
	}
	printf("\nGata, apasa o tasta...");
	getch();
}

