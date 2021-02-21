#include <stdio.h>

/*
 * This sample show usage of funtion pointer
 */

int my_func(int a, int b) {
    int c = a + b;
    printf("%d + %d = %d\n", a, b, c);
    return c;
}

/* Example 1: define func type, then define func pointer by type */
void test01() {
    typedef int(func_type)(int, int);
    func_type *f = my_func;
    (*f)(11, 22);
    (f)(11, 22);
}

/* Example 2: define func pointer type, then define func pointer variable */
void test02() {
    typedef int(*func_pointer)(int, int);
    func_pointer f = my_func;
    (*f)(33, 44);
    (f)(33, 44);
}

/* Example 3: define func pointer variable directly */
void test03() {
    int (*f)(int, int) = my_func;
    (*f)(55, 66);
    (f)(55, 66);
}

int main() {
    test01();
    test02();
    test03();
}