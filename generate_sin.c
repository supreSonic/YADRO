#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SAMPLE_RATE 100				// фикс частота дискретизации 100 гц

void sin_wave (double *t, double *val, double time, double freq);
void sin_wave (double *t, double *val, double time, double freq)
{
	int i, N;
	N = (int) (time * SAMPLE_RATE);
	for (i = 0; i < N; i++)
	{
		t[i] = (double) i / SAMPLE_RATE;
		val[i] = sin (2 * M_PI * freq * t[i]);
	}
	return;
}

void print_into_file (const char *name, double *t, double *val, int N);
void print_into_file (const char *name, double *t, double *val, int N)
{
	int i;
	FILE *fp;
	fp = fopen (name, "w");
	if (!fp)
	{
		printf ("Cannot open the file\n");
		return;
	}
	fprintf (fp, "Time\t\tAmplitude\n");
	for (i = 0; i < N; i++)
	{
		fprintf (fp, "%lf\t%lf\n", t[i], val[i]);
	}
	fclose (fp);
	return;
}

int main (void)
{
	double freq, time;
	int N;
	double *t, *val;
	printf ("Введите частоту:\n");
	scanf ("%lf", &freq);
	printf ("Введите длительность:\n");
	scanf ("%lf", &time);
	N = (int) (time * SAMPLE_RATE);
	t = (double *) malloc (N * sizeof (double));
	if (!t)
	{
		printf ("Not enough memory!\n");
		return 1;
	}
	val = (double *) malloc (N * sizeof (double));
	if (!val)
	{
		printf ("Not enough memory!\n");
		free (t);
		return 1;
	}
	
	sin_wave (t, val, time, freq);
	print_into_file ("sin.csv", t, val, N);
	printf ("Вывод в файле	 sin.csv\n");
	free (t);
	free (val);
	return 0;
}
