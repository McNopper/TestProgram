# Division by infinity should be testable in fenv.h

## Motivation

Following mathematical expression is given:  

![Euler's number expression](graphics/expression.svg)

For `n` going to `∞` [1], the constant Euler's number `e` [2] can be calculated. `e` is a transcendental number [3] and is approximately `2.718281` showing the first six decimal numbers without rounding.  

In C/C++, `e` can be approximated with following line of code:  
  
```cpp
float result = powf(1.0f + 1.0f / n, n);
```

Following table shows the `result` with some given and increasing `n`:
  
|       n | result   |
|---------|----------|
|     1.0 | 2.000000 |
|    10.0 | 2.593743 |
|   100.0 | 2.704811 |
|  1000.0 | 2.717051 |
| 10000.0 | 2.718597 |

## Problem

For `n` having the value `INFINITY` defined in the C/C++ header `fenv.h` [4], this Euler's number expression calculates `1.0`, which seems to be abnormal. Furthermore, this header library has several functions and macros, to test abnormal results e.g., using `FE_DIVBYZERO` to test a division by zero.  
However, to test against the problematic initial division by infinity and later raised by infinity, there is no macro given at this point of time.  
  
It is assumed, that there are many other use cases, where a division by infinity (or other calculus) is not tested and could cause runtime problems, providing non-expected or invalid values.
  
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
```

The build program (e.g. using `gcc`) prints out the following results:  
```
Result with n=0.0: 1.000000
Exception FE_DIVBYZERO
Done.

Result with n=1.0: 2.000000
Done.

Result with n=10.0: 2.593743
Exception FE_INEXACT
Done.

Result with n=100.0: 2.704811
Exception FE_INEXACT
Done.

Result with n=1000.0: 2.717051
Exception FE_INEXACT
Done.

Result with n=10000.0: 2.718597
Exception FE_INEXACT
Done.

Result with n=inf: 1.000000
Done.
```

## Solution

Request for `FE_DIVBYINFINITY` in header `fenv.h` for C/C++, where one can check, if a division by infinity occurred.

## Resources

[1] https://en.wikipedia.org/wiki/Infinity  
[2] https://en.wikipedia.org/wiki/E_(mathematical_constant)  
[3] https://en.wikipedia.org/wiki/Transcendental_number  
[4]	https://en.cppreference.com/w/cpp/numeric/fenv  
