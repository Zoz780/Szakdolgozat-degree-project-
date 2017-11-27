#include <iostream>
using namespace std;

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
	float *x, *y, input, result = 0;
	int number_of_pairs, i, j, isContinue = 1;
	cout << "Adja meg hany x es y erteket szeretne beirni: ";
	cin >> number_of_pairs;
	if (number_of_pairs == 0)
	{
		return 0;
	}
	else
	{
		x = (float *)malloc(number_of_pairs * sizeof(float));
		y = (float *)malloc(number_of_pairs * sizeof(float));
	}
	cout << "Irja be az x es y ertekeket: \n";
	for (i = 0; i<number_of_pairs; i++)
	{
		cin >> x[i];
		cin >> y[i];
	}
	cout << "A bevitt ertekek a kovetkezok: \n";
	for (i = 0; i<number_of_pairs; i++)
	{
		cout << x[i] << "\t" << y[i] << endl;
	}
	while (isContinue == 1)
	{
		result = 0;
		cout << "\nIrja be azt az x erteket, amelyhez meg szeretne tudni az y-t: ";
		cin >> input;

		LagrangeInterpolation(x, y, number_of_pairs, input, &result);

		cout << "\nA beirt x-hez tartozo y ertek: " << result;
		cout << "\nSzeretne meg egy y-t kiszamolni?\nNyomja meg az 1-es gombot ha igen, barmelyik mas szamot, ha nem.";
		cin >> isContinue;
	}
	return 0;
}