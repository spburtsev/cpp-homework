#include <iostream>
#include <string>
using std::string;

struct Shape {
    virtual ~Shape() {}
};
struct Rectangle : Shape {};
struct Triangle : Shape {};
struct Hexagon : Shape {};

#include "Multimethod.hpp"

// функция для проверки пересечения двух прямоугольников
bool is_intersect_r_r(Shape * a, Shape * b)
{
    return true;
}

// функция для проверки пересечения прямоугольника и треугольника
bool is_intersect_r_t(Shape * a, Shape * b)
{
    return true;
}

int main()
{
    // мультиметод для наследников Shape
    // возращающий bool и являющийся коммутативным
    Multimethod<Shape, bool, true> is_intersect;

    // добавляем реализацию мультиметода для двух прямоугольников
    is_intersect.addImpl(typeid(Rectangle), typeid(Rectangle), is_intersect_r_r);

    // добавляем реализацию мультиметода для прямоугольника и треугольника
    is_intersect.addImpl(typeid(Rectangle), typeid(Triangle), is_intersect_r_t);

    // создаём две фигуры
    Shape * s1 = new Triangle();
    Shape * s2 = new Rectangle();

    // проверяем, что реализация для s1 и s2 есть
    if (is_intersect.hasImpl(s1, s2))
    {
        // вызывается функция is_intersect_r_t(s2, s1)
        bool res = is_intersect.call(s1, s2);

        // Замечание: is_intersect_r_t ожидает,
        // что первым аргументом будет прямоугольник
        // а вторым треугольник, а здесь аргументы
        // передаются в обратном порядке.
        // ваша реализация должна самостоятельно
        // об этом позаботиться
    }

    return 0;
}
