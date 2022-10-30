#include <cfenv>
#include <cmath>
#include <cstdio>

// Request, that c/∞ should be testable in C/C++

void executeExpression(float n)
{
	std::feclearexcept(FE_ALL_EXCEPT);

	float result = powf(1.0f + 1.0f / n, n);

	int excepts = std::fetestexcept(FE_ALL_EXCEPT);
	int classify = std::fpclassify(result);

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

	if(classify != FP_NORMAL)
	{
		if (classify & FP_NAN)
		{
			printf("Classification FP_NAN\n");
		}
		if (classify & FP_INFINITE)
		{
			printf("Classification FP_INFINITE\n");
		}
		if (classify & FP_ZERO)
		{
			printf("Classification FP_ZERO\n");
		}
		if (classify & FP_SUBNORMAL)
		{
			printf("Classification FP_SUBNORMAL\n");
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

    n = 10.0f;
    executeExpression(n);

    n = 100.0f;
    executeExpression(n);

    n = 1000.0f;
    executeExpression(n);

    n = 10000.0f;
    executeExpression(n);

    n = INFINITY;
    executeExpression(n);

    return 0;
}
