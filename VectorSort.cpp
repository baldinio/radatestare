#include <stdio.h>
#include <conio.h>


void main()
{
	FILE *f;
	int n, i, j;
	double x, y;
	char binname[50];
	printf("\nFile name: ");
	gets_s(binname);
	f = fopen(binname, "rb+");
	if (!f)
		printf("\nCan't open the file %s.  Check name location.");
	else
	{
		fseek(f, 0, 2);
		n = ftell(f) / sizeof(double);
		for (i = 0;i<n-1;i++)
			for (j = i + 1;j < n;j++)
			{
				fseek(f, i * sizeof(double), SEEK_SET);
				fread(&x, sizeof(double), 1, f);
				fseek(f, j * sizeof(double), SEEK_SET);
				fread(&y, sizeof(double), 1, f);
				if (x > y)
				{
					fseek(f, i * sizeof(double), SEEK_SET);
					fwrite(&y, sizeof(double), 1, f);
					fseek(f, j * sizeof(double), SEEK_SET);
					fwrite(&x, sizeof(double), 1, f);
				}
			}
		fclose(f);
	}
	printf("\n\Done, press a key...");
	getch();
}