# Язык СИ

- Реализация языка СИ
    - GCC
    - Clang
---

# GCC

Этапы компиляции

1. Обработка препроцессором (gcc -E prog.c -o prog.i)
2. Трансляция программы из языка СИ в Assembler (gcc -S prog.i)
3. Трансляция из Ассемблера в объектный модуль (gcc -c prog.s)
4. Объектый модуль в исполняемый файл (gcc prog.c -o prog)


## Раздельная компиляция

```
gcc module1.c -c
gcc module2.c -c
gcc module3.c -c
gcc main.c -c
gcc module1.o module2.o module3.o main.o -o main
```

[***GCC***](https://gcc.gnu.org/onlinedocs/gccint/)
