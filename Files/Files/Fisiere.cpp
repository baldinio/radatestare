#include <stdio.h>
#include <conio.h>

void main()
{
	FILE* f;
	FILE* g;
	char fname[25]="stud.paf";
	char newname[25];
	int n, l, c, i, j;
	float* v;
	float** a;

	f = fopen(fname, "rt"); // r - open an existing file ; w - create a new file
							// b - binary file ; t - text file
		if (!f)
			printf("\nFile %s cannot be found/opened",fname);
		else
		{
			fscanf(f, "%d", &n);
			v = new float[n];
			for (i = 0; i < n; i++)
				fscanf(f, "%f", &v[i]);
			fscanf(f, "%d %d", &l, &c);
			a = new float*[l];
			for (i = 0; i < l; i++)
				a[i] = new float[c];
			for (i = 0; i < l; i++)
				for (j = 0; j < c; j++)
					fscanf(f, "%f", &a[i][j]);

			printf("\n\nNew text file name:");
			gets_s(newname);
			g = fopen(newname, "wt");

			fprintf(g,"\nVector:\n"); //fprintf(stdout sau filename,"\nVector:\n");
			for (i = 0; i < n; i++)
				fprintf(g,"%f ", v[i]);

			fprintf(g,"\nMatrix:\n");
			for (i = 0; i < l; i++)
			{
				for (j = 0; j < c; j++)
					fprintf(g,"%5.2f ", a[i][j]);
				fprintf(g,"\n");
			}
			fclose(g);

			fclose(f);
		}

		printf("\n\nDone, press a key...");
		getch();
}