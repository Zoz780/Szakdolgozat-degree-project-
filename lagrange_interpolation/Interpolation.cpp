#include <stdio.h>

/**
		** Implementation of lagrange interpolation
*/
bool LagrangeInterpolation(float x[], float y[], int num, float in, float *result)
{
	float s = 1, t = 1;
	for (int i = 0; i<num; i++)
	{
		s = 1;
		t = 1;
		for (int j = 0; j<num; j++)
		{
			if (j != i)
			{
				s = s*(in - x[j]);
				t = t*(x[i] - x[j]);
			}
		}
		*result += ((s / t)*y[i]);
	}
	return true;
}

int main(void)
{
	float x[100], y[100], input, result = 0;
	int number_of_pairs, i, j, isContinue = 1;
	printf("Adja meg hany x es y erteket szeretne beirni: ");
	scanf("%d", &number_of_pairs);
	if (number_of_pairs == 0)
	{
		return false;
	}
	printf("Irja be az x es y ertekeket: \n");
	for (i = 0; i<number_of_pairs; i++)
	{
		scanf("%f", &x[i]);
		scanf("%f", &y[i]);
	}
	printf("A bevitt ertekek a kovetkezok: \n");
	for (i = 0; i<number_of_pairs; i++)
	{
		printf("%0.3f\t%0.3f", x[i], y[i]);
		printf("\n");
	}
	while (isContinue == 1)
	{
		result = 0;
		printf("\nIrja be azt az x erteket, amelyhez meg szeretne tudni az y-t: ");
		scanf("%f", &input);

		LagrangeInterpolation(x, y, number_of_pairs, input, &result);

		printf("\nA beirt x-hez tartozo y ertek: %f", result);
		printf("\nSzeretne meg egy y-t kiszamolni?\nNyomja meg az 1-es gombot ha igen, barmelyik mas szamot, ha nem.");
		scanf("%d", &isContinue);
	}
	return 0;
}