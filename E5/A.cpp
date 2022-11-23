/********************************************************************
** E5 - A
*/

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <cstring>
#include <cmath>
#include <complex>
#include <algorithm>

// Too large?
#ifdef INTERNAL
const int MAX_SIZE = 1004;
#else
const int MAX_SIZE = 500005;
#endif

const double PI = std::acos(-1.0);

char bufferA[MAX_SIZE];
char bufferB[MAX_SIZE];
int result[MAX_SIZE];

using complex_t = std::complex<double>;
complex_t compA[MAX_SIZE];
complex_t compB[MAX_SIZE];

void divide(complex_t comp[], int length);
void FFT(complex_t comp[], int length, int flag);
void convolute(complex_t a[], complex_t b[], int length);
int initialize(char strA[], char strB[]);
int multiply(int length);
void printNumber(int arr[], int length);
int main()
{
	int t;
	int length;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%s %s", bufferA, bufferB);
		length = initialize(bufferA, bufferB);
		length = multiply(length);
		printNumber(result, length);
	}

	return 0;
}

void divide(complex_t comp[], int length)
{
	int j = length >> 1;

	for (int i = 1; i < length - 1; i++)
	{
		if (i < j)
			std::swap(comp[i], comp[j]);
		int k = length >> 1;
		while (j >= k)
		{
			j -= k;
			k >>= 1;
		}
		if (j < k)
			j += k;
	}
}

void FFT(complex_t comp[], int length, int flag)
{
	complex_t unit;
	complex_t factor;	// rotate factor?

	divide(comp, length);
	for (int i = 2; i <= length; i <<= 1)
	{
		unit.real(std::cos(-flag * 2.0 * PI / i));
		unit.imag(std::sin(-flag * 2.0 * PI / i));
		for (int j = 0; j < length; j += i)
		{
			factor = 1.0;
			for (int k = j; k < j + (i >> 1); k++)
			{
				complex_t u = comp[k];
				complex_t v = factor * comp[k + (i >> 1)];

				comp[k] = u + v;
				comp[k + (i >> 1)] = u - v;

				factor = factor * unit;
			}
		}
	}
	if (flag == -1)	// IDFT
	{
		for (int i = 0; i < length; i++)
			comp[i].real(comp[i].real() / (double)length);
	}
}

void convolute(complex_t a[], complex_t b[], int length)
{
	FFT(a, length, 1);
	FFT(b, length, 1);

	for (int i = 0; i < length; i++)
		a[i] = a[i] * b[i];

	FFT(a, length, -1);
}

int initialize(char strA[], char strB[])
{
	int lengthA = strlen(strA);
	int lengthB = strlen(strB);
	int length = 1;

	while ((length < (lengthA << 1)) \
		|| (length < (lengthB << 1)))
	{
		length <<= 1;
	}

	int i;
	for (i = 0; i < lengthA; i++)
		compA[i] = (double)(strA[lengthA - i - 1] - '0');
	while (i < length)
		compA[i++] = 0.0;

	for (i = 0; i < lengthB; i++)
		compB[i] = (double)(strB[lengthB - i - 1] - '0');
	while (i < length)
		compB[i++] = 0.0;

	return length;
}

int multiply(int length)
{
	memset(result, 0, sizeof(result));

	convolute(compA, compB, length);

	for (int i = 0; i < length; i++)
		result[i] = (int)(compA[i].real() + 0.5);
	for (int i = 0; i < length; i++)
	{
		result[i + 1] += result[i] / 10;
		result[i] %= 10;
	}

	int high = 0;
	for (int i = length - 1; i >= 0; i--)
	{
		if (result[i])
		{
			high = i;
			break;
		}
	}

	return high + 1;
}

void printNumber(int arr[], int length)
{
	for (int i = length - 1; i >= 0; i--)
		putchar('0' + arr[i]);
	putchar('\n');
}

