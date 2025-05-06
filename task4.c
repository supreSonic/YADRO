#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SAMPLE_RATE 100

void interpolation (const double *in, int n, double *out);		//интерполяция
void interpolation (const double *in, int n, double *out)
{
	int i;
	for (i = 0; i < n - 1; i++)
	{
		out[2 * i] = in[i];
		out[2 * i + 1] = (in[i] + in[i + 1]) * 0.5;
	}
	out[2 * ( n - 1)] = in[n - 1];
	return;
}

void decimation (const double *in, int n, double *out);			//децимация
void decimation (const double *in, int n, double *out)
{
	int i, j;
	for (i = 0, j = 0; i < n; i+=2, j++)
	{
		out[j] = in[i];
	}
	return;
}

double deviation (const double *prev, const double *new, int n);	//отклонение
double deviation (const double *prev, const double *new, int n)
{
	double r = 0;
	int i;
	for (i = 0; i < n; i++)
	{
		double diff = prev[i] - new[i];
		r += diff * diff / n;
	}
	return sqrt(r);
}

void sin_wave (double *t, double *val, double time, double freq);	//построение синуса
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

int main (void)
{
	double freq_list[] = {1, 5, 10, 15, 20, 25, 30, 35, 45, 49};  // Тестируемые частоты
	int num_freqs = sizeof(freq_list) / sizeof(freq_list[0]);
	int k;
	double time;
	printf ("Введите длительность:\n");
	scanf ("%lf", &time);
	int N = (int) (time * SAMPLE_RATE);
	double *t = (double *) malloc (N * sizeof (double));
	if (!t)
	{
		printf ("Not enough memory!\n");
		return 1;
	}
	double *val = (double *) malloc (N * sizeof (double));
	if (!val)
	{
		printf ("Not enough memory!\n");
		free (t);
		return 1;
	}
	double *decimated = (double *) malloc (N * 0.5 * sizeof (double));
	if (!decimated)
	{
		printf ("Not enough memory!\n");
		free (t);
		free (val);
		return 1;
	}
	double *interpolated = (double *) malloc ((2*N-1) * sizeof (double));
	if (!interpolated)
	{
		printf ("Not enough memory!\n");
		free (t);
		free (val);
		free (decimated);
		return 1;
	}
	
	printf("Частота (Гц)\tОшибка\n");
	printf("----------------------------\n");

	for (k = 0; k < num_freqs; k++) {
		double freq = freq_list[k];
		sin_wave(t, val, time, freq);		//синус
		decimation(val, N, decimated);		 	//децимация
		interpolation(decimated, N * 0.5, interpolated);//интерполяция
		double rmse = deviation(val, interpolated, N);
		printf("%.2f\t\t%lf\n", freq, rmse);
	}

	free (t), free (val), free (decimated), free (interpolated);

    return 0;
}
