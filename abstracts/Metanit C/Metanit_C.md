```c++
#include <stdio.h>
#include <limits.h>
```

# Язык программирования С
## Введение:

Основные особенности Си:
- Высокая скорость выполнения
- Компактность, небольшой размер выходных скомпилированных файлов


## Переменные

- **char**: один символ от -128 до 128 (8 бит)
- **unsigned char**: один символ от 0 до 255 (8 бит);
- **short**: целое число от –32768 до 32767 (16 бит);
- **unsigned short**: целое число от 0 до 65535 (16 бит);
- **int**: целое число от −2 147 483 648 до 2 147 483 647 (32 бита);
- **unsigned int**: целое число от 0 до 4 294 967 295 (32 бита);
- **long**: целое число в диапазоне от −9 223 372 036 854 775 808 до +9 223 372 036 854 775 807 (64 бита);
- **unsigned long**: представляет целое число в диапазоне от 0 до 18 446 744 073 709 551 615 (64 бита);
- **float**:вещественное число ординарной точности с плавающей точкой в диапазоне +/- 3.4E-38 до 3.4E+38 (32 бита);
- **double**: вещественное число двойной точности с плавающей точкой в диапазоне +/- 1.7E-308 до 1.7E+308 (64 бита);
- **long double**: вещественное число двойной точности с плавающей точкой в диапазоне +/- 3.4E-4932 до 1.1E+4932. 80 бит). На некоторых системах может занимать 96 и 128 бит;
- **void**: тип без значения;


```c++
int number = 2;
int a, b;
char c ='d';
float d = -2.1345;
double f = 3.45;
```


```c++
printf("INT_MIN = %d \n", INT_MIN);
printf("INT_MAX = %d \n", INT_MAX);
```

    INT_MIN = -2147483648 
    INT_MAX = 2147483647 


## Консольный вывод. Функция printf

- \n: перевод на новую строку

- \t: табуляция

- \r: возврат каретки (курсора) в начало строки

- \\: обратный слеш

- \\': одинарная кавычка

- \\": двойная кавычка



```c++
printf("The book \"The C Programming Language\"\nBrian Kernighan, Dennis Ritchie");
```

    The book "The C Programming Language"
    Brian Kernighan, Dennis Ritchie

# Спецификаторы

- %c: для вывода отдельных символов (тип char)

- %s: для вывода строк

- %d: для вывода целых чисел со знаком (тип int)

- %i: для вывода целых чисел со знаком (тип int)

- %u: для вывода целых положительных чисел (тип unsigned)

- %f: для вывода чисел с плавающей точкой (float, double)

- %F: для вывода чисел с плавающей точкой в верхнем регистре (float, double)

- %e: для вывода экспоненциального представления чисел с плавающей точкой (float, double)

- %E: для вывода экспоненциального представления чисел с плавающей точкой в верхнем регистре (float, double)

- %g: для вывода чисел используется более короткий из форматов %e или %f

- %G: для вывода чисел используется более короткий из форматов %E или %F

- %o: для вывода восьмеричных чисел без знака

- %x: для вывода шестнадцатеричных чисел

- %X: для вывода шестнадцатеричных чисел в верхнем регистре

- %%: для вывода знака процента


```c++
float r = 71.8986;
printf("x = %f \n", r);
printf("x = %e \n", r);   

char symbol = 'r';
printf("symbol = %c \n", symbol);
     
unsigned int number = 23;
printf("number = %u \n", number);

printf("%s \n", "Hi");

```

    x = 71.898598 
    x = 7.189860e+01 
    symbol = r 
    number = 23 
    Hi 


## Операции сдвига


- <<: Сдвигает битовое представление числа, представленного первым операндом, влево на определенное количество разрядов, которое задается вторым операндом.

- \>>: Сдвигает битовое представление числа вправо на определенное количество разрядов.


```c++
int a = 2 << 2;
int b = 16 >> 3;
printf("a = %d \n", a);
printf("b = %d \n", b);
```

    a = 8 
    b = 2 


- &: поразрядная конъюнкция (операция И или поразрядное умножение). Возвращает 1, если оба из соответствующих разрядов обоих чисел равны 1

- |: поразрядная дизъюнкция (операция ИЛИ или поразрядное сложение). Возвращает 1, если хотя бы один из соответствующих разрядов обоих чисел равен 1

- ^: поразрядное исключающее ИЛИ. Возвращает 1, если только один из соответствующих разрядов обоих чисел равен 1

- ~: поразрядное отрицание. Инвертирует все разряды операнда. Если разряд равен 1, то он становится равен 0, а если он равен 0, то он получает значение 1.


```c++
int a = 5 | 2;          // 101 | 010 = 111  - 7
int b = 6 & 2;          // 110 & 010 = 10  - 2
int c = 5 ^ 2;          // 101 ^ 010 = 111 - 7
int d = ~9;             // -10
     
printf("a = %d \n", a);
printf("b = %d \n", b);
printf("c = %d \n", c);
printf("d = %d \n", d);
```

## Операции присвоения


```c++
int a = 5;
a += 10;        // 15
a -= 3;         // 12
a *= 2;         // 24
a /= 6;         // 4
a <<= 4;      // 64
a >>= 2;      // 16
```




    16



## Преобразования типов

- Если один из операндов имеет тип **long double**, то второй операнд тоже будет преобразован в тип **long double**

- Если предыдущий пункт не выполняется и если один из операндов имеет тип **double**, то второй операнд тоже будет преобразован к типу **double**

- Если предыдущий пункт не выполняется и если один из операндов имеет тип **float**, то второй операнд тоже будет преобразован к типу **float**

- Если предыдущий пункт не выполняется и если один из операндов имеет тип **unsigned long int**, то второй операнд тоже будет преобразован к типу **unsigned long int**

- Если предыдущий пункт не выполняется и если один из операндов имеет тип **long**, то второй операнд тоже будет преобразован к типу **long**

- Если предыдущий пункт не выполняется и если один из операндов имеет тип **unsigned**, то второй операнд тоже будет преобразован к типу **unsigned**

- Если предыдущий пункт не выполняется то оба операнда приводятся к типу **int**


```c++
int a = 10;
int b = 4;
int c = a / b;                      // 2
double d = a / b;                   // 2.00000
double e = (double)a / (double)b;   // 2.50000
printf("c = %d \n", c);
printf("d = %f \n", d);
printf("e = %f \n", e);
```

    c = 2 
    d = 2.000000 
    e = 2.500000 



```c++
int number = 70;
char symbol = (char) number;
printf("symbol = %c \n", symbol);               //  F
printf("symbol (int code) = %d \n", symbol);    // 70
```

    symbol = F 
    symbol (int code) = 70 





    24



## Ветвление
### Оператор if


```c++
int x = 60;
     
if(x > 60)
{
    printf("if statement \n");
    printf("x is greater than 60 \n");
}
else if (x < 60)
{
    printf("else if statement \n");
    printf("x is less than 60 \n");
}
else
{
    printf("else statement \n");
    printf("x is equal 60 \n");
}
```

    else statement 
    x is equal 60 


## Конструкция switch


```c++
    int x = 2;
     
    switch(x)
    {
        case 1: 
            printf("x = 1 \n");
            break;
        case 2: 
            printf("x = 2 \n");
            break;
        case 3: 
            printf("x = 3 \n");
            break;
        default: 
            printf("x is undefined \n");
            break;
    }
```

    x = 2 


## Тернарный оператор
<p>[первый операнд - условие] ? [второй операнд] : [третий операнд]</p>


```c++
int x=3;
    int y=2;
    char op ='+';
     
    int z = op == '+'? (x+y) : (x-y);
     
    printf("z = %d", z);        // 5
```

    z = 5




    5



## Циклы

- for
- while
- do..while


```c++
    for (int i = 0; i < 9; i++)
    {
        printf("%d * %d = %d \n", i, i,  i * i);
    }
```

    0 * 0 = 0 
    1 * 1 = 1 
    2 * 2 = 4 
    3 * 3 = 9 
    4 * 4 = 16 
    5 * 5 = 25 
    6 * 6 = 36 
    7 * 7 = 49 
    8 * 8 = 64 



```c++
int i = -1;
do
{
    printf("%d", i);
    i--;
}
while (i > 0);
```

    -1


```c++
int i = 6;
while (i > 0)
{
    printf("%d \n", i);
    i--;
}
```

    6 
    5 
    4 
    3 
    2 
    1 


## Массивы и строки




```c++
    int numbers[4];
    numbers[0] = 1;
    numbers[1] = 2;
    numbers[2] = 3;
    numbers[3] = 4;
     
    printf("numbers[2] = %d", numbers[2]); 
```

    numbers[2] = 3


```c++
    int numbers[5] = { 10, 12, 13, 54, 43 };
    for(int i =0; i < 5; i++)
    {
        printf("numbers[%d] = %d \n", i, numbers[i]);
    }
```

    numbers[0] = 10 
    numbers[1] = 12 
    numbers[2] = 13 
    numbers[3] = 54 
    numbers[4] = 43 



```c++
    int numbers[3][2] = { {1, 2}, {4, 5}, {7, 8} };
    for(int i =0; i < 3; i++)
    {
        for(int j =0; j<2; j++)
        {
            printf("numbers[%d][%d] = %d \n", i, j, numbers[i][j]);
        }
    }
```

    numbers[0][0] = 1 
    numbers[0][1] = 2 
    numbers[1][0] = 4 
    numbers[1][1] = 5 
    numbers[2][0] = 7 
    numbers[2][1] = 8 



```c++
char welcome[] = "Hello";
printf("welcome = %s \n", welcome); 
```

    welcome = Hello 


# Препроцессор

- **#define**: определяет макрос или препроцессорный идентификатор;
- **#undef**: отменяет определение макроса или идентификатора;
- **#ifdef**: проверяет, определен ли идентификатор;
- **#ifndef**: проверяет неопределенности идентификатор;
- **#include**: включает текст из файла;
- **#if**: проверяет условие выражение (как условная конструкция if);
- **#else**: задает альтернативное условие для #if;
- **#endif**: окончание условной директивы #if;
- **#elif**: задает альтернативное условие для #if;
- **#line**: меняет номер следующей ниже строки;
- **#error**: формирует текст сообщения об ошибке трансляции;
- **#pragma**: определяет действия, которые зависят от конкретной реализации компилятора;
- **#**: пустая директива, по сути ничего не делает


### Директива #include. Включение файлов

`
#include <имя_файла>  // абсолютный
#include "имя_файла"  // относительный
`

### Директива #define

Директива #define определяет идентификатор и последовательность символов, которые будут подставляться вместо идентификатора каждый раз, когда он встретится в исходном файле. Формальное определение директивы:


```c++
#define BEGIN {
#define END }
#define N 23

BEGIN
    int x = N;
    return 0;
END
```




    0



### Директива #undef

многократно определять новое значение для одного идентификатора


```c++
#define STRING "Good morning \n"    
printf(STRING);
#undef STRING
#define STRING "Good afternoon \n"
printf(STRING);
#undef STRING
#define STRING "Good evening \n"
printf(STRING);
```

    Good morning 
    Good afternoon 
    Good evening 


## Макросы
Все идентификаторы, определяемые с помощью директив #define, которые предполагают замену на определенную последовательность символов, еще называют макросами.


```c++
#define HELLO printf("Hello World! \n")
#define FOR for(int i=0; i<4; i++)
FOR HELLO;

```

    Hello World! 
    Hello World! 
    Hello World! 
    Hello World! 



```c++
#define t int
#define swap(t, x, y) { t temp = x; x = y; y=temp;}
t x = 4;
t y = 10;
swap(t, x, y)
printf("x=%d \t y=%d", x, y);
```

    x=10 	 y=4


```c++
#define min(a,b) (a < b ? a : b)
int x = 23;
int y = 14;
int z = min(x,y);
printf("min = %d", z);
```

    min = 14

## Препроцессорные операции

При обработки исходного кода препроцессор может выполнять две операции: # и ##.


```c++
#define print_int(n) printf(#n"=%d \n",n);
int x = 23;
print_int(x);       // x=23
int y = 14;
print_int(y);       // y=14
int number = 203;
print_int(number);  // number=203
```

    x=23 
    y=14 
    number=203 





    12




```c++
#define print(a,b,c) printf("%d", a##b##c);
print(2, 81, 34);
```

    28134


```c++
#define unite(a,b,c) a##b##c;
int x = unite(2, 81, 34);
printf("%d \n", x);
```

    28134 


## Условная компиляция

```
#if условие
текст_1
#else
текст_2
#endif
```


```c++
#undef N
#define N 22
#if N==22
    printf("N=22");
#else
    printf("N is undefined");
#endif
```

    N=22




    4




```c++
#define BETA
#define DEBUG
#if defined DEBUG && !defined BETA
    printf("debug mode; final version");
#elif defined DEBUG && defined BETA
    printf("debug mode; beta version");
#else
    printf("undefined mode");
#endif
```

    debug mode; beta version




    24



# Функции

```
тип имя_функции(параметры)
{
    выполняемые_выражения
}
```


```c++
void hello() {
    printf("Hello!\n");    
}

hello();
```

    Hello!


## Передача параметров в функцию

Функция может принимать параметры. Параметры перечисляются в скобках после имени функции имеют следующее определение:


```c++
void factorial(int n)
{
    int result = 1;
    for(int i=1;i<=n;i++)
    {
        result *= i;
    }
    printf("factorial of %d is equal %d \n", n, result);
}

factorial(4);
factorial(6);
```

    factorial of 4 is equal 24 
    factorial of 6 is equal 720 


## Возвращение значений из функции


```c++
int factorial(int n)
{
    int result = 1;
    for(int i=1;i<=n;i++)
    {
        result *= i;
    }
    return result;
}

int arg,f;
     
arg = 4;
f = factorial(arg);
printf("factorial of %d is equal %d \n", arg, f);
     
arg = 6;
f = factorial(arg);
printf("factorial of %d is equal %d \n", arg, f);
```

    factorial of 4 is equal 24 
    factorial of 6 is equal 720 


## Рекурсивные функции




```c++
int factorial(int n)
{
    if (n == 1)
    {
        return 1;
    }
    else
    {
        return n * factorial(n - 1);
    }
}

int result = factorial(6);
printf("%d \n", result); 
```

    720 



```c++
int fibonachi(int n)
{
    if (n == 0)
    {
        return 0;
    }
    if (n == 1)
    {
        return 1;
    }
    else
    {
        return fibonachi(n - 1) + fibonachi(n - 2);
    }
}

int result = fibonachi(10);
printf("%d \n", result);
```

## Указатели
Указатели представляют собой объекты, значением которых служат адреса других объектов (переменных, констант, указателей) или функций. Указатели - это неотъемлемый компонент для управления памятью в языке Си.


```c++
    int x = 10;
    int *p;
    p = &x;
    printf("Address = %p \n", p);
    printf("x = %d \n", *p);
```

    Address = 0x7fd7bd8140d0 
    x = 10 



```c++
    char c = 'N';
    int d = 10;
    short s = 2;
     
    char *pc = &c;          // получаем адрес переменной с типа char
    int *pd = &d;           // получаем адрес переменной d типа int
    short *ps = &s;         // получаем адрес переменной s типа short
     
    printf("Variable c: address=%p \t value=%c \n", pc, *pc);
    printf("Variable d: address=%p \t value=%d \n", pd, *pd);
    printf("Variable s: address=%p \t value=%hd \n", ps, *ps);
```

    Variable c: address=0x7fd7bd8140d8 	 value=N 
    Variable d: address=0x7fd7bd8140dc 	 value=10 
    Variable s: address=0x7fd7bd8140e0 	 value=2 


## Операции с указателями
### Присваивание


```c++
    int a = 10;
    int b = 2;
     
    int *pa = &a;
    int *pb = &b;
     
    printf("Variable a: address=%p \t value=%d \n", pa, *pa);
    printf("Variable b: address=%p \t value=%d \n", pb, *pb);
     
    pa = pb;    // теперь указатель pa хранит адрес переменной b
    printf("Variable b: address=%p \t value=%d \n", pa, *pa);
```

    Variable a: address=0x7fd7bd814118 	 value=10 
    Variable b: address=0x7fd7bd81411c 	 value=2 
    Variable b: address=0x7fd7bd81411c 	 value=2 


### Разыменование указателя


```c++
    int a = 10;
     
    int *pa = &a;
    int *pb = pa;
     
    *pa = 25;
     
    printf("Value on pointer pa: %d \n", *pa);  // 25
    printf("Value on pointer pb: %d \n", *pb);  // 25
    printf("Value of variable a: %d \n", a);    // 25
```

    Value on pointer pa: 25 
    Value on pointer pb: 25 
    Value of variable a: 25 





    25



### Адрес указателя


```c++
int a = 10;
int *pa = &a;
printf("address of pointer=%p \n", &pa);        // адрес указателя
printf("address stored in pointer=%p \n", pa);  // адрес, который хранится в указателе - адрес переменной a         
printf("value on pointer=%d \n", *pa);          // значение по адресу в указателе - значение переменной a
```

    address of pointer=0x7fd7bd814150 
    address stored in pointer=0x7fd7bd814148 
    value on pointer=10 





    21



### Операция сравнения


```c++
int a = 10;
int b = 20;
int *pa = &a;
int *pb = &b;
if(pa > pb)
    printf("pa (%p) is greater than pb (%p) \n", pa, pb);
else
    printf("pa (%p) is less or equal pb (%p) \n", pa, pb);
```

    pa (0x7fd7bd814158) is less or equal pb (0x7fd7bd81415c) 


### Приведение типов


```c++
char c = 'N';
char *pc = &c;
int *pd = (int *)pc;
printf("pc=%p \n", pc);
printf("pd=%p \n", pd);
```

    pc=0x7fd7bd814170 
    pd=0x7fd7bd814170 


## Арифметика Указателей



```c++
    int n = 10;
     
    int *ptr = &n;
    printf("address=%p \t value=%d \n", ptr, *ptr);
     
    ptr++;
    printf("address=%p \t value=%d \n", ptr, *ptr);
     
    ptr--;
    printf("address=%p \t value=%d \n", ptr, *ptr);
```

    address=0x7fd7bd814188 	 value=10 
    address=0x7fd7bd81418c 	 value=0 
    address=0x7fd7bd814188 	 value=10 


## Константы и указатели


```c++
    const int a = 10;
    const int *pa = &a;
    printf("address=%p \t value=%d \n", pa, *pa);
```

    address=0x7fd7b4e81018 	 value=10 



```c++
int a = 10;
const int *const pa = &a;
 
//*pa = 22;  так сделать нельзя
 
int b = 45;
// pa = &b;  так сделать нельзя 
```

## Указатели на мссив


```c++
    int a[5] = {1, 2, 3, 4, 5};
     
    for(int i=0;i<5;i++)
    {
        printf("a[%d]: address=%p \t value=%d \n", i, a+i, *(a+i));
    }
```

    a[0]: address=0x7fd7bd8141a0 	 value=1 
    a[1]: address=0x7fd7bd8141a4 	 value=2 
    a[2]: address=0x7fd7bd8141a8 	 value=3 
    a[3]: address=0x7fd7bd8141ac 	 value=4 
    a[4]: address=0x7fd7bd8141b0 	 value=5 



```c++
int a[5] = {1, 2, 3, 4, 5};
int *ptr = a;
int a2 = *(ptr+2);
printf("value: %d \n", a2); // 3
```

    value: 3 





    10




```c++
    int a[3][4] = { {1, 2, 3, 4} , {5, 6, 7, 8}, {9, 10, 11, 12}};
    int n = sizeof(a)/sizeof(a[0]);         // число строк
    int m = sizeof(a[0])/sizeof(a[0][0]);   // число столбцов
     
    int *final = a[0] + n*m - 1;    // указатель на самый последний элемент
    for(int *ptr=a[0], i=1; ptr<=final; ptr++, i++)
    {
        printf("%d \t", *ptr);
        // если остаток от целочисленного деления равен 0,
        // переходим на новую строку
        if(i%m==0)
        {
            printf("\n");
        }
    }   
```

    1 	2 	3 	4 	
    5 	6 	7 	8 	
    9 	10 	11 	12 	


## Массивы указателей, строки и многоуровневая адресация


```c++
int a[] = {1, 2, 3, 4};
int *p1[3];
int *p2[] = { &a[1], &a[2], &a[0] };
int *p3[3] = { &a[3], &a[1], &a[2] };
```


```c++
char *hello = "Hello World!";
printf("%s", hello);
```

    input_line_61:2:16: warning: ISO C++11 does not allow conversion from string literal to 'char *' [-Wwritable-strings]
     char *hello = "Hello World!";
                   ^


    Hello World!

## Указатели на указатели
Кроме обычных указателей в языке Си мы можем создавать указатели на другие указатели. Такие ситуации еще называются многоуровневой адресацией.


```c++
int  x = 22;
int *ptr1;
int **ptr2;
ptr1 = &x;
ptr2 = &ptr1;
     
printf("Address of ptr1: %p \n", ptr2);
printf("Address of x: %p \n", *ptr2);
printf("Value of x: %d \n", **ptr2);
```

    Address of ptr1: 0x7fd7bd814438 
    Address of x: 0x7fd7bd814430 
    Value of x: 22 


## Указатели в параметрах функции


```c++
void increment(int *x)
{
    (*x)++;
    printf("increment function: %d \n", *x);
}

int n = 10;
increment(&n);
printf("main function: %d \n", n);
```

    increment function: 11 
    main function: 11 



```c++
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b=temp;
}

int x = 100;
int y = 200;
swap(&x, &y);
printf("x=%d \t y=%d \n", x, y);
```

    x=200 	 y=100 


## Массивы в параметрах
Если функция принимает в качестве параметра массив, то фактически в эту функцию передается только адрес начала массива. То есть как и в случае с указателями нам доступен адрес, по которому мы можем менять значения. В отличие от параметров примитивных типов, которые передаются по значению.


```c++
void twice(int n, int *p)
{
    for(int i=0; i<n; i++)
    {
        *p++ *=2;
    }
}

int nums[] = {1, 2, 3, 4, 5};
int length = sizeof(nums)/sizeof(nums[0]);
     
twice(length, nums);
     
for(int i=0; i<length; i++)
{
    printf("%d \t", nums[i]);
}
```

    2 	4 	6 	8 	10 	

## Динамическая память

- malloc()<br>
```C++
void *malloc(unsigned s);
```
Выделяет память длиной в s байт и возвращает указатель на начало выделенной памяти. В случае неудачного выполнения возвращает NULL <br>

- calloc()<br>
```C++
void *calloc(unsigned n, unsigned m);
```
Выделяет память для n элементов по m байт каждый и возвращает указатель на начало выделенной памяти. В случае неудачного выполнения возвращает NULL <br>

- realloc()<br>
```C++ 
void *realloc(void *bl, unsigned ns);
```
Изменяет размер ранее выделенного блока памяти, на начало которого указывает указатель bl, до размера в ns байт. Если указатель bl имеет значение NULL, то есть память не выделялась, то действие функции аналогично действию malloc <br>

- free()<br>
```C++ 
void *free(void *bl);
```
Освобождает ранее выделенный блок памяти, на начало которого указывает указатель bl.
Если мы не используем эту функцию, то динамическая память все равно освободится автоматически при завершении работы программы. Однако все же хорошей практикой является вызов функции free(), который позволяет как можно раньше освободить память. <br>

## Указатель как результат функции

```
тип *имя_функции (параметры) 
{
    // тело функции
    тип *имя_указателя;
    return  имя_указателя;
}
```

```C++
int *addArrays(int a[], int b[], int n) 
{
    int *ptr = calloc(n, sizeof(int)); 
 
     for (int i = 0; i < n; i++)
        ptr[i] = a[i] + b[i];
 
     return ptr;
}
 
int main(void)
{
    int a[] = {3,4,5,6,7};
    int b[] = {1,1,1,1,1};
 
    int n = sizeof(a)/sizeof(a[0]);
    int *ptr = addArrays(a, b, n);
    for(int i=0;i<n;i++)
        printf("%d \t", *ptr++);
    free(ptr);
    return 0;
}
```

## Управление динамической памятью

```C++
#include <stdio.h>
#include <stdlib.h>
 
int * createPointer()
{
    static int *p = NULL;
    int n = 1;
    if(p==NULL)
    {
        p = malloc(n * sizeof(int));
        *p = 1;
    }
    printf("%d \t", (*p));
    (*p)++;
    return p;
}
 
int main(void)
{
    int *ptr;
    ptr=createPointer();
    ptr=createPointer();
    ptr=createPointer();
    free(ptr);
    return 0;
}
```

## Указатели на фунцию
```
тип (*имя_указателя) (параметры);
```

```C++ 
void *message (void);
```

```C++
void hello(void)
{
    printf("Hello, World \n");
}
void goodbye()
{
    printf("Good Bye, World \n");
}
int main(void)
{
    void (*message) (void);
     
    message=hello;
    message();
    message = goodbye;
    message();
    return 0;
}
```

## Массивы указателей на функции
```
тип (*имя_массива[размер]) (параметры)
```

```C++
double (*actions[]) (int, int)
```

```C++
#include <stdio.h>
 
void add(int x, int y)
{
    printf("x+y=%d \n", x+y);
}
void subtract(int x, int y)
{
    printf("x+y=%d \n", x-y);
}
void multiply(int x, int y)
{
    printf("x*y=%d \n", x*y);
}
int main(void)
{
    int a = 10;
    int b = 5;
    void (*operations[3])(int, int) = {add, subtract, multiply};
     
    // получаем длину массива
    int length = sizeof(operations)/sizeof(operations[0]);
     
    for(int i=0; i<length;i++)
    {
        operations[i](a, b);    // вызов функции по указателю
    }
     
    return 0;
}
```

## Указатели на функции как параметры и результаты функций


```C++
#include <stdio.h>
 
int add(int x, int y)
{
    return x+y;
}
int subtract(int x, int y)
{
    return x-y;
}
int operation(int (*op)(int, int), int a, int b)
{
    return op(a, b);
}
int main(void)
{
    int a = 10;
    int b = 5;
    int result;
    result = operation(add, a, b);
    printf("result=%d \n", result);
    result = operation(subtract, a, b);
    printf("result=%d \n", result);
    return 0;
}
```

Другой пример - функция, которая может принимать в качестве параметра некоторое услови
```C++
#include <stdio.h>
 
int isEven(int x)
{
    return x%2==0;
}
int isPositive(int x)
{
    return x>0;
}
void action(int (*condition)(int), int numbers[], int n)
{
    for(int i=0; i<n; i++)
    {
        if(condition(numbers[i])!=0)
        {
            printf("%d \t", numbers[i]);
        }
    }
}
int main(void)
{
    int nums[] = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5};
    int n = sizeof(nums)/sizeof(nums[0]);
     
    printf("\n Even numbers: ");
    action(isEven, nums, n);
    printf("\n Positive numbers: ");
    action(isPositive, nums, n);
    return 0;
}
```

## Функции с переменным количеством параметров





```c++

```


```c++

```


```c++

```
