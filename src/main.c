//Решить систему из двух линейных уравнений (частные случаи можно не рассматривать).
//Для решения задачи использовать указатели.

#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#define NOERRORS 0
#define ERR_NOX -1
#define ERR_NOY -2

//Структура, содержащая множители уравнения
typedef struct
{
	double a;
	double b;
	double c;
}
Equation;

void SwapEquations(Equation* a, Equation* b);
void DiffSLE(Equation* f1, Equation* f2);
void Normaliser(Equation* f);
int SLEsolver(double* x, double* y, Equation f1, Equation f2);
void PrintEquation(Equation* f);

int main()
{
	double x, y;
	Equation f1, f2;

	puts("Введите значения a b c для первого уравнения");
	scanf("%lf %lf %lf", &f1.a, &f1.b, &f1.c);
	puts("Введите значения a b c для второго уравнения");
	scanf("%lf %lf %lf", &f2.a, &f2.b, &f2.c);
	putchar('\n');

	//Вывод уравнений на экран
	PrintEquation(&f1);
	PrintEquation(&f2);

	//На основе возвращённого флага определяется, какой вывод осуществить
	switch (SLEsolver(&x, &y, f1, f2))
	{
	default:
		break;
	case NOERRORS:
		printf("\nx = %5.2lf\ny = %5.2lf\n", x, y);
		return NOERRORS;
	case ERR_NOX:
		putchar('\n');
		puts("Невозможно определить x");
		return ERR_NOX;
	case ERR_NOY:
		putchar('\n');
		puts("Невозможно определить y");
		return ERR_NOY;
	}
}

//Функция перестановки двух уравнений
void SwapEquations(Equation* a, Equation* b)
{
	Equation tmp = *a;
	*a = *b;
	*b = tmp;
}

//Функция поочерёдного вычитания множителей двух уравнений
void DiffSLE(Equation* f1, Equation* f2)
{
	f2->a -= f1->a;
	f2->b -= f1->b;
	f2->c -= f1->c;
}

//Функция нормирования всех множителей уравнения по а
void Normaliser(Equation* f)
{
	if (f->a == 1.0)
		return;

	double mult = 1.0 / f->a;
	f->a = 1.0;
	f->b *= mult;
	f->c *= mult;
}

//Функция решения системы двух уравнений с двумя неизвестными
int SLEsolver(double* x, double* y, Equation f1, Equation f2)
{
	if (!(f1.b || f2.b))	//Если b равен нулю в обоих уравнениях, значит y либо равен нулю, либо (-inf;+inf)
	{
		if ((*x = f2.c / f2.a) == (f1.c / f1.a))	//Если x cходится в обоих уравнениях, значит y == 0
		{
			*y = 0.0;
			return NOERRORS;
		}
		/*else*/return ERR_NOY;
	}

	if (f1.a)
	{
		Normaliser(&f1);
		if (f2.a)
		{
			Normaliser(&f2);
			DiffSLE(&f1, &f2);	//Вычитаем из второй строки первую
		}
	}
	else if (f2.a)
	{
		SwapEquations(&f1, &f2);	//Если в первой строке не было значения a, то меняем строки местами и решаем
		Normaliser(&f1);
	}
	else						//Если a равен нулю в обоих уравнениях, значит x либо равен нулю, либо (-inf;+inf)
	{
		if ((*y = f2.c / f2.b) == (f1.c / f1.b))	//Если y cходится в обоих уравнениях, значит x == 0
		{
			*x = 0.0;
			return NOERRORS;
		}
		/*else*/return ERR_NOX;
	}

	*y = f2.c / f2.b;
	*x = (f1.c - (*y * f1.b));
	return NOERRORS;
}

//Вывод данного уравнения на экран
void PrintEquation(Equation* f)
{
	printf("(%+5.2lf)*x + (%+5.2lf)*y = %-5.2lf\n", f->a, f->b, f->c);
}
