//линейная интерполяция
void interpolation (const double *in, int n, double *out);
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

//использую простую децимацию, полагая,
// что в сигнале уже нет высокочастотных компонент (не использую фильтрацию)

void decimation (const double *in, int n, double *out);
void decimation (const double *in, int n, double *out)
{
	int i, j;
	for (i = 0, j = 0; i < n; i+=2, j++)
	{
		out[j] = in[i];
	}
	return;
}



