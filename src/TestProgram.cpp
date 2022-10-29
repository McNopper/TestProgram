#include <cfenv>
#include <cmath>
#include <cstdio>

// Request for FE_DIVBYINFINITY in header fenv.h for C/C++

void executeExpression(float n)
{
	std::feclearexcept(FE_ALL_EXCEPT);

	float result = powf(1.0f + 1.0f / n, n);
	int excepts = std::fetestexcept(FE_ALL_EXCEPT);

	printf("Result with n=%.1f: %f\n", n, result);

	if(excepts)
	{
		if (excepts & FE_DIVBYZERO)
		{
			printf("Exception FE_DIVBYZERO\n");
		}
		if (excepts & FE_INEXACT)
		{
			printf("Exception FE_INEXACT\n");
		}
		if (excepts & FE_INVALID)
		{
			printf("Exception FE_INVALID\n");
		}
		if (excepts & FE_OVERFLOW)
		{
			printf("Exception FE_OVERFLOW\n");
		}
		if (excepts & FE_UNDERFLOW)
		{
			printf("Exception FE_UNDERFLOW\n");
		}
	}

	printf("Done.\n\n");
}

int main()
{
	float n = 0.0f;
	executeExpression(n);

    n = 1.0f;
    executeExpression(n);

    n = 100.0f;
    executeExpression(n);

    n = 10000.0f;
    executeExpression(n);

    n = INFINITY;
    executeExpression(n);

    return 0;
}
