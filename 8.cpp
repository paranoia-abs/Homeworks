#include <iostream>
#include <vector>

double my_min(double a, double b) {
    return a < b ? a : b;
}

double my_max(double a, double b) {
    return a > b ? a : b;
}

struct Point {
    double x, y;
    Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}
};

class Rectangle {
private:
    double width;
    double height;
    Point bottomLeft;

public:
    Rectangle() : width(1.0), height(1.0), bottomLeft(0.0, 0.0) {
        std::cout << "  [Constructor] Rectangle() → 1x1 at (0,0)\n";
    }

    explicit Rectangle(double size) 
        : width(size >= 0 ? size : 0), height(size >= 0 ? size : 0), bottomLeft(0.0, 0.0) {
        std::cout << "  [Constructor] Rectangle(" << size << ") → square at (0,0)\n";
    }

    Rectangle(double w, double h) 
        : width(w >= 0 ? w : 0), height(h >= 0 ? h : 0), bottomLeft(0.0, 0.0) {
        std::cout << "  [Constructor] Rectangle(" << w << ", " << h << ") at (0,0)\n";
    }

    Rectangle(double w, double h, double x, double y) 
        : width(w >= 0 ? w : 0), height(h >= 0 ? h : 0), bottomLeft(x, y) {
        std::cout << "  [Constructor] Rectangle(" << w << ", " << h << ", " << x << ", " << y << ")\n";
    }

    Rectangle(const Rectangle& other)
        : width(other.width), height(other.height), bottomLeft(other.bottomLeft) {
        std::cout << "  [COPY Constructor]\n";
    }

    Rectangle& operator=(const Rectangle& other) {
        if (this != &other) {
            width = other.width;
            height = other.height;
            bottomLeft = other.bottomLeft;
        }
        return *this;
    }

    void scale(double factor) {
        if (factor > 0) {
            width *= factor;
            height *= factor;
            std::cout << "  [Scale] → " << width << "x" << height << "\n";
        } else {
            std::cout << "  [Scale] Error: factor must be > 0\n";
        }
    }

    std::vector<Point> getAllCorners() const {
        std::vector<Point> corners;
        corners.reserve(4);
        corners.push_back(bottomLeft);
        corners.push_back(Point(bottomLeft.x + width, bottomLeft.y));
        corners.push_back(Point(bottomLeft.x + width, bottomLeft.y + height));
        corners.push_back(Point(bottomLeft.x, bottomLeft.y + height));
        return corners;
    }

    bool intersects(const Rectangle& other) const {
        double left = my_max(bottomLeft.x, other.bottomLeft.x);
        double right = my_min(bottomLeft.x + width, other.bottomLeft.x + other.width);
        double bottom = my_max(bottomLeft.y, other.bottomLeft.y);
        double top = my_min(bottomLeft.y + height, other.bottomLeft.y + other.height);
        return (left < right) && (bottom < top);
    }

    bool contains(const Point& p) const {
        return (p.x >= bottomLeft.x) && (p.x <= bottomLeft.x + width) &&
               (p.y >= bottomLeft.y) && (p.y <= bottomLeft.y + height);
    }

    double getArea() const {
        return width * height;
    }

    Rectangle& moveTo(double x, double y) {
        bottomLeft.x = x;
        bottomLeft.y = y;
        return *this;
    }

    Rectangle& resize(double w, double h) {
        width = (w >= 0) ? w : 0;
        height = (h >= 0) ? h : 0;
        return *this;
    }

    void print() const {
        std::cout << "Rectangle: " << width << "x" << height
                  << " at (" << bottomLeft.x << ", " << bottomLeft.y << ")\n";
    }
};

int main() {
    std::cout << "\n--- Задача 1: Конструкторы ---\n";
    Rectangle r1;                    // по умолчанию
    Rectangle r2(5.0);               // квадрат
    Rectangle r3(4.0, 3.0);          // прямоугольник в (0,0)
    Rectangle r4(2.0, 2.0, 1.0, 1.0); // с позицией

    r1.print();
    r2.print();
    r3.print();
    r4.print();

    std::cout << "\n--- Задача 2: Масштабирование ---\n";
    r3.scale(2.0);
    r3.print();
    r3.scale(-1.0); // ошибка

    std::cout << "\n--- Дополнительно: Пересечение ---\n";
    Rectangle r5(2.0, 2.0, 2.5, 2.5);
    std::cout << "r4 и r5 пересекаются? " << (r4.intersects(r5) ? "Да" : "Нет") << "\n";

    std::cout << "\n--- Дополнительно: Содержит точку ---\n";
    Point p(1.5, 1.5);
    std::cout << "r4 содержит (1.5, 1.5)? " << (r4.contains(p) ? "Да" : "Нет") << "\n";

    return 0;
}