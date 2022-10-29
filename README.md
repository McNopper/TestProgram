# Division by the infinity should be testable in C/C++

## Motivation

Following mathematical expression is given:  

![Euler's number expression](graphics/expression.svg)

For `n` going to `∞` [1], the constant Euler's number `e` [2] can be calculated. `e` is a transcedental number [3] and is approximatelly `2.718281` showing the first six decimal numbers without rounding.  

In C/C++, this value can be calculated with following line of code:  
  
```cpp
float result = powf(1.0f + 1.0f / n, n);
```

Following table shows the `result` with some given and increasing `n`:
  
|       n | result   |
|---------|----------|
|     1.0 | 2.000000 |
|   100.0 | 2.704811 |
| 10000.0 | 2.718597 |

## Problem

For `n` having the value `INFINITY` defined in the C/C++ header `fenv.h`, this Euler's number expression calculates `1.0`, which seems to be abnormal. Furthermore, this header library has several functions and macros, to test abnormal results e.g. using `FE_DIVBYZERO` to test a division by zero.  
However, to test against the problematic division by infinity, there is no macro given at this point of time.  
  
It is assumed, that there are many other use cases, where a division by infinity is not tested and could cause runtime problems, providing non-expected values.
  
### Test program

```cpp
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
```

## Solution

Request for `FE_DIVBYINFINITY` in header `fenv.h` for C/C++, where one can check, if a division by infinity occurred.

## Resources

[1] https://en.wikipedia.org/wiki/Infinity  
[2] https://en.wikipedia.org/wiki/E_(mathematical_constant)  
[3] https://en.wikipedia.org/wiki/Transcendental_number  
[4]	https://en.cppreference.com/w/cpp/numeric/fenv  
