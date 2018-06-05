#include <stdio.h>
#include <conio.h>

void main()
{
	FILE* f, *g;
	int n, i;
	double x;
	char binname[50];

	printf("\nFile name: ");
	gets_s(binname);
	f = fopen(binname, "rb");  // fopen_s(&f,binname,"rb");
	if (!f)
		printf("\nCan't open the file %s. Check name/location.");
	else
	{
		fseek(f, 0, SEEK_END );
			n = ftell(f) / sizeof(double);
		fseek(f, 0, 0); // rewind(f);
		printf("\nArray with %d elements from file-->%s<--\n", n, binname);
		for (i = 0;i < n;i++)
		{
			fread(&x, sizeof(double), 1, f);
			printf("%6.2lf ", x);
		}

		fclose(f);
	}
	printf("\nDone, press a key...\n");
	getch();
}