#include <stdio.h>
#include <conio.h>
#include <string.h>

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
	char cnpcautat[14];

	printf("Nume fisier binar: "); gets_s(numef);
	f = fopen(numef, "rb");
	if (!f)
		printf("Nu se poate deschide fisierul %s", numef);
	else
	{
		printf("\nCNP cautat: "); gets_s(cnpcautat);

		while (!feof(stdin))
		{
			c = 1;
			rewind(f);
			fread(&x, sizeof(STUDENT), 1, f);
			while (!feof(f) && (c != 0))
			{
				c = strcmp(cnpcautat, x.cnp);
				if (c == 0)
				{
					printf("\nNume: %s", x.nume);
					printf("\nAn: %2d, Grupa: %d", x.an, x.grupa);
					printf("\nNote: ");
					for (i = 0; i < x.nrd; i++)
						printf("%2d", x.note[i]);
				}
				fread(&x, sizeof(STUDENT), 1, f);
			}
			if (c != 0)
				printf("\n\nNu am gasit niciun student cu codul cautat");
			printf("\n\nCNP cautat: "); gets_s(cnpcautat);
		}
		fclose(f);
	}
	printf("\nGata, apasa o tasta...");
	getch();
}

