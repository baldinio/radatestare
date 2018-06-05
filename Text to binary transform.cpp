#include <stdio.h>
#include <conio.h>

void main()
{
	FILE* f, *g;
	int n, i;
	double x;
	char textname[50];
	char binname[50];

	printf("\nText file name: ");
	gets_s(textname);
	f = fopen(textname, "rt");
	if (!f)
		printf("\nCan't open the file %s. Check name/location.");
	else
	{
		printf("\nBinary file name: ");
		gets_s(binname);
		g = fopen(binname, "wb");

		fscanf(f, "%d", &n);
		for (i = 0;i < n;i++)
		{
			fscanf(f, "%lf", &x);
			fwrite(&x, sizeof(double), 1, g);
		}
		fclose(f);
		fclose(g);
	}
	printf("\nDone, press a key...\n");
	getch();
}