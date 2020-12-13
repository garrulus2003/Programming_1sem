//Geometry

//Neustroeva Liza 024

//https://contest.yandex.ru/contest/21872/run-report/43797119/

/*
Напишите иерархию классов для работы с геометрическими фигурами на плоскости.

Структура Point - точка на плоскости. Точку можно задать двумя числами типа double. Должны быть открыты поля x и y. Точки можно сравнивать операторами == и !=.
Класс Line - прямая. Прямую можно задать двумя точками, можно двумя числами (угловой коэффициент и сдвиг), можно точкой и числом (угловой коэффициент). 
Линии можно сравнивать операторами == и !=.
Абстрактный класс Shape - фигура.
Класс Polygon - многоугольник. Многоугольник - частный случай фигуры. У многоугольника можно спросить verticesCount() -
количество вершин - и std::vector<Point> getVertices - сами вершины без возможности изменения. Можно спросить isConvex() - выпуклый ли. 
Можно сконструировать многоугольник из вектора точек-вершин в порядке обхода. Можно сконструировать многоугольник из точек, 
передаваемых в качестве параметров через запятую (т.е. неуказанное число аргументов). Для простоты будем считать, что многоугольники 
с самопересечениями никогда не возникают (гарантируется, что в тестах таковые будут отсутствовать). Кроме того, считаем, что три 
последовательных вершины многоугольника никогда не лежат на одной прямой.

Класс Ellipse - эллипс. Эллипс - частный случай фигуры. У эллипса можно спросить std::pair<Point,Point> focuses() - его фокусы; 
std::pair<Line, Line> directrices() - пару его директрис; double eccentricity() - его эксцентриситет, Point center() - его центр. 
Эллипс можно сконструировать из двух точек и double (два фокуса и сумма расстояний от эллипса до них);

Класс Circle - круг. Круг - частный случай эллипса. У круга можно спросить double radius() - радиус. Круг можно задать точкой и числом (центр и радиус).

Класс Rectangle - прямоугольник. Прямоугольник - частный случай многоугольника. У прямоугольника можно спросить Point center() - его центр; 
std::pair<Line, Line> diagonals() - пару его диагоналей. Прямоугольник можно сконструировать по двум точкам (его противоположным вершинам) 
и числу (отношению смежных сторон), причем из двух таких прямоугольников выбирается тот, у которого более короткая сторона 
расположена по левую сторону от диагонали, если смотреть от первой заданной точки в направлении второй.

Класс Square - квадрат. Квадрат - частный случай прямоугольника. У квадрата можно спросить Circle circumscribedCircle(), 
Circle inscribedCircle(). Квадрат можно задать двумя точками - противоположными вершинами.

Класс Triangle - треугольник. Треугольник - частный случай многоугольника. У треугольника можно спросить Circle circumscribedCircle(), 
Circle inscribedCircle(), Point centroid() - его центр масс, Point orthocenter() - его ортоцентр, Line EulerLine() - его прямую Эйлера, 
Circle ninePointsCircle() - его окружность Эйлера.
У любой фигуры можно спросить:

double perimeter() - периметр;
double area() - площадь;
operator==(const Shape& another) - совпадает ли эта фигура с другой как множество точек. (В частности, треугольник ABC равен треугольнику BCA.)
isCongruentTo(const Shape& another) - равна ли эта фигура другой в геометрическом смысле, то есть можно ли совместить эти фигуры движением плоскости. 
Движение – это отображение плоскости на себя, сохраняющее расстояния.
isSimilarTo(const Shape& another) - подобна ли эта фигура другой, то есть можно ли перевести одну фигуру в другую преобразованием подобия. 
(Определение преобразования подобия, кто не знает, можно посмотреть в Википедии.)
containsPoint(Point point) - находится ли точка внутри фигуры.
Фигуры не обязаны иметь одинаковый тип, чтобы считаться равными, конгруэнтными или подобными! 
Любую фигуру должно быть можно сравнить с любой другой и получить правильный ответ, независимо от настоящих типов этих фигур!

С любой фигурой можно сделать:

rotate(Point center, double angle) - поворот на угол (в градусах, против часовой стрелки) относительно точки;
reflex(Point center) - симметрию относительно точки;
reflex(Line axis) - симметрию относительно прямой;
scale(Point center, double coefficient) - гомотетию с коэффициентом coefficient и центром center.
*/




#include <vector>
#include <cmath>
#include <typeinfo>

const double EPS = 1e-6;
#define M_PI 3.14159265358979323846


//Comparison functions

bool equal(double a, double b) {
    return std::fabs(a - b) < EPS;
}

bool leq(double a, double b) {
    return (b - a) > -EPS;
}

bool geq(double a, double b) {
    return (a - b) > -EPS;
}



//Elementary geometric objects

struct Point;
struct Vector;
class Line;


struct Point {
    double x;
    double y;

    Point(double X, double Y) : x(X), y(Y) {}
    Point() : x(0.0), y(0.0) {}
    Point(Line l1, Line l2);

    void rotate(Point center, double angle);
    void reflex(Point center);
    void reflex(Line axis);
    void scale(Point center, double coefficient);
};


bool operator == (const Point& a, const Point& b) {
    return equal(a.x, b.x) && equal(a.y, b.y);
}

bool operator != (const Point& a, const Point& b) {
    return !(a == b);
}





struct Vector : public Point {
    Vector() = default;
    Vector(Point p) : Point(p) {}
    Vector(double a, double b) : Point(a, b) {}
    Vector(const Point& end, const Point& begin) : Point(begin.x - end.x, begin.y - end.y) {}
    double length() const;
    Vector operator *(double k) const;
};

Vector operator + (const Vector& v1, const Vector& v2) {
    return Vector(v1.x + v2.x, v1.y + v2.y);
}

Vector operator - (const Vector& v1, const Vector& v2) {
    return Vector(v1.x - v2.x, v1.y - v2.y);
}

double Vector::length() const{
    return sqrt(x * x + y * y);
}

double vectorMultiplication(const Vector& a, const Vector& b) {
    return a.x * b.y - a.y * b.x;
}

double cos(const Vector& a, const Vector& b) {
    double scalar = a.x * b.x + a.y * b.y;
    return (scalar / (a.length() * b.length()));
}

Vector Vector::operator *(double k) const{
    return Point(x * k, y * k);
}





class Line {
public:
    double a;
    double b;
    double c;

    Line(): a(1), b(0), c(0) {}
    Line(double A, double B, double C) : a(A), b(B), c(C) {}
    Line(const Point& p1, const Point& p2);
    Line(double k, double shift) : a(k), b(-1), c(shift) {}
    Line(const Point& p, double k);

    bool operator == (const Line& other)const;
    bool operator != (const Line& other) const;

    Vector normal() const;
};

bool Line::operator == (const Line& other) const{
    return equal(a * other.b, b * other.a) && equal(b * other.c, c * other.b) && equal(c * other.a, a * other.c);
}

bool Line::operator != (const Line& other) const {
    return !(*this == other);
}

Line::Line(const Point& p1, const Point& p2) {
    a = p1.y - p2.y;
    b = p2.x - p1.x;
    c = p2.y*p1.x - p2.x*p1.y;
}

Line::Line(const Point& p, double k) {
    a = k;
    b = -1;
    c = -(a * p.x + b * p.y);
}

Vector Line::normal() const{
    Vector v(a, b);
    double coefficient = 1.0 / v.length();
    v = v * coefficient;
    return v;
}



//Elementary geomery fuctions

double distance(const Point& point, const Line& line) {
    return std::fabs((line.a * point.x + line.b * point.y + line.c) / (sqrt(line.a * line.a + line.b * line.b)));
}

bool incident(const Point& point, const Line& line) {
    return equal(0.0, line.a * point.x + line.b * point.y + line.c);
}



//Plane movements

void Point::reflex(Line axis) {
    Vector v = axis.normal() * distance(*this, axis);
    if (incident((*this - v), axis)) {
        *this = *this - v * 2;
    }
    else {
        *this = *this + v * 2;
    }
}

void Point::rotate(Point center, double angle) {
    if (equal((cos(angle * M_PI) / 180.0), 1.0)) return;           //if it is an identical movement
    if (equal((cos(angle * M_PI) / 180.0), -1.0)) {                //if it is a central reflexion
        reflex(center);
        return;
    }
    double tg = tan((angle * M_PI) / 360.0);                       // using that two symmetries equal a rotation
    Line axis1(center, 0);
    Line axis2(center, tg);
    reflex(axis1);
    reflex(axis2);
}

void Point::reflex(Point center) {                                 // using that two symmetries equal a rotation
    Line axis1(center, 1);
    Line axis2(center, -1);
    reflex(axis1);
    reflex(axis2);
}

void Point::scale(Point center, double coefficient) {
    Vector v = *this - center;
    v = v * coefficient;
    *this = center + v;
}



//Point as the intersection of two linnes

Point::Point(Line l1, Line l2) {
    double det = l1.a * l2.b - l2.a * l1.b;
    if (equal(det, 0)) {
        Point();
    }
    double det1 = -(l1.c * l2.b - l2.c * l1.b);
    double det2 = -(l1.a * l2.c - l2.a * l1.c);
    x = det1 / det;
    y = det2 / det;
}





//Shape classes

class Shape {
public:
    Shape() = default;

    virtual double perimeter() const = 0;
    virtual double area() const = 0;
    virtual bool operator==(const Shape& another) const = 0;
    virtual bool operator!=(const Shape& another) const = 0;
    virtual bool isCongruentTo(const Shape& another) const = 0;
    virtual bool isSimilarTo(const Shape& another) const = 0;
    virtual bool containsPoint(Point point) const = 0;

    virtual void rotate(Point center, double angle) = 0;
    virtual void reflex(Point center) = 0;
    virtual void reflex(Line axis) = 0;
    virtual void scale(Point center, double coefficient) = 0;

    virtual ~Shape() = default;
};

class Polygon : public Shape {
public:
    Polygon() : vertices(std::vector <Point> (0)) {}

    template<typename... Args>                                    //constructor from a list of vertices
    Polygon(Args... args);
    static void addVertices() {};
    template<typename Head, typename... Tail>
    void addVertices(const Head& head, const Tail &... tail);

    Polygon(std::vector<Point>& points) : vertices(points) {}     //constructor from a vector of vertices

    double perimeter() const override;
    double area() const override;
    bool operator==(const Shape& another) const override;
    bool operator!=(const Shape& another) const override;
    bool isCongruentTo(const Shape& another) const override;
    bool isSimilarTo(const Shape& another) const override;
    bool containsPoint(Point point) const override;

    void rotate(Point center, double angle) override;
    void reflex(Point center) override;
    void reflex(Line axis) override;
    void scale(Point center, double coefficient) override;

    std::vector<Point> getVertices() const;
    int verticesCount() const;
    bool isConvex() const;

protected:
    std::vector <Point> vertices;
};

template<typename Head, typename... Tail>
void Polygon::addVertices(const Head& head, const Tail&... tail) {
    vertices.push_back(head);
    addVertices(tail...);
}

template<typename... Args>
Polygon::Polygon(Args... args) {
    addVertices(args...);
}

double Polygon::perimeter() const {                                      //returns sum of all side lengths
    double perimeter = 0;
    for (size_t i = 0; i < (vertices.size() - 1); ++i) {
        perimeter += (vertices[i + 1] - vertices[i]).length();
    }
    perimeter += (vertices[vertices.size() - 1] - vertices[0]).length();
    return perimeter;
}

double Polygon::area() const {                                //sum all the triangles areas with vertex 0 and opposite side being polygon's side
    double area = 0;

    for (size_t i = 2; i < vertices.size(); i++) {
        Vector a(vertices[i-1] - vertices[0]);
        Vector b(vertices[i] - vertices[0]);

        area += vectorMultiplication(a, b);
    }

    return std::fabs(area) / 2.0;
}

bool Polygon::operator==(const Shape& another) const {
    try {
        const auto a = dynamic_cast<const Polygon&>(another); 
        size_t n = vertices.size();
        if (n != a.vertices.size()) return false;

        for (size_t i = 0; i < n; ++i) {                     //checks all rotations if orientation is the same
            bool congruent = true;
            for (size_t j = 0; j < n; ++j) {
                if (!(vertices[j] == a.vertices[(i+j)%n])) {
                    congruent = false;
                    break;
                }
            }
            if (congruent) return true;
        }

        for (size_t i = 0; i < n; ++i) {                     //checks all rotations if orientation is different
            bool congruent = true;
            for (size_t j = 0; j < n; ++j) {
                if (!(vertices[j] == a.vertices[n - 1 - (i + j) % n])) {
                    congruent = false;
                    break;
                }
            }
            if (congruent) return true;
        }
        return false;
    }
    catch (std::bad_cast& m) {
        return false;
    }
}

bool Polygon::operator!=(const Shape& another) const{
    return !(*this == another);
}

bool Polygon::isCongruentTo(const Shape& another) const {
    try {
        const auto a = dynamic_cast<const Polygon&>(another);
        size_t n = vertices.size();
        if (n != a.vertices.size()) return false;

        std::vector <double> angles(n);                           //two polygons are equal if they have same angles
        std::vector <double> angles_a(n);
        std::vector <double> sides(n);
        std::vector <double> sides_a(n);

        for (size_t i = 0; i < n; ++i) {
            angles[i] = cos(vertices[(i + 1) % n] - vertices[i], vertices[(i + 2) % n] - vertices[(i+1)%n]);
            angles_a[i] = cos(a.vertices[(i + 1) % n] - a.vertices[i], a.vertices[(i + 2) % n] - a.vertices[(i+1)%n]);
            sides[i] = (vertices[(i)%n] - vertices[(i + 1) % n]).length();
            sides_a[i] = (a.vertices[(i)%n] - a.vertices[(i+1) % n]).length();
        }

        for (size_t i = 0; i < n; ++i) {                           //checks if orientation is the same
            bool congruent = true;
            for (size_t j = 0; j < n; ++j) {
                if (!equal(sides[j], sides_a[(i + j)%n]) || !equal(angles[j], angles_a[(i + j)%n])) {
                    congruent = false;
                    break;
                }
            }
            if (congruent) return true;
        }

        for (size_t i = 0; i < n; ++i) {                           //checks if the orientation is different
            bool congruent = true;
            for (size_t j = 0; j < n; ++j) {
                if (!equal(sides[j], sides_a[(2*n - 1 - i - j) % n]) || !equal(angles[j], angles_a[(2 * n - 2 - i - j) % n])) {
                    congruent = false;
                    break;
                }
            }
            if (congruent) return true;
        }

        return false;
    }
    catch (std::bad_cast& m) {
        return false;
    }
}

bool Polygon::isSimilarTo(const Shape& another) const {
    try {
        const auto a = dynamic_cast<const Polygon&>(another);
        Polygon copy = a;                                             //creates a copy that might be congruent to this shape
        double coefficient = sqrt(area() / a.area());
        copy.scale(Point(), coefficient);
        return isCongruentTo(copy);
    }
    catch (std::bad_cast& m) {
        return false;
    }
}

bool Polygon::containsPoint(Point point) const {

    Vector v1 = vertices[vertices.size() - 1] - point;    //cheks whrther all triangles with vertex point and
    Vector v2 = vertices[0] - point;                      //opposite side being a side of a polygon are oriented samely

    double base = vectorMultiplication(v1, v2);
    bool sign = (geq(base, 0));

    for (size_t i = 0; i < vertices.size() - 1; ++i) {
        v1 = vertices[i] - point;
        v2 = vertices[i+1] - point;
        double mult = vectorMultiplication(v1, v2);
        bool mult_sign = (geq(mult, 0));
        if (sign != mult_sign) return false;
    }

    return true;
}



//all plane movements for a polygon consist of movements of its vertices
void Polygon::reflex(Line axis) {
    for (size_t i = 0; i < vertices.size(); ++i) {
        vertices[i].reflex(axis);
    }
}

void Polygon::rotate(Point center, double angle) {
    for (size_t i = 0; i < vertices.size(); ++i) {
        vertices[i].rotate(center, angle);
    }
}

void Polygon::reflex(Point center) {
    for (size_t i = 0; i < vertices.size(); ++i) {
        vertices[i].reflex(center);
    }
}

void Polygon::scale(Point center, double coefficient) {
    for (size_t i = 0; i < vertices.size(); ++i) {
        vertices[i].scale(center, coefficient);
    }
}



//functions returning some information about the polygon
std::vector<Point> Polygon::getVertices() const {
    return vertices;
}

int Polygon::verticesCount() const {
    return vertices.size();
}

bool Polygon::isConvex() const {
    Vector v1 = vertices[vertices.size() - 1] - vertices[0];              //checks whether all angles are less than 180
    Vector v2 = vertices[1] - vertices[0];
    double base = vectorMultiplication(v1, v2);
    bool sign = (geq(base, 0));

    for (size_t i = 1; i < vertices.size(); ++i) {
        v1 = vertices[i - 1] - vertices[i];
        v2 = vertices[(i+1)%vertices.size()] - vertices[i];
        double mult = vectorMultiplication(v1, v2);
        bool mult_sign = (geq(mult, 0));
        if (sign != mult_sign) return false;
    }
    return true;
}



class Ellipse : public Shape {
public:
    Ellipse() : focus1(Point()), focus2(Point()), distanceSum(0) {}
    Ellipse(Point f1, Point f2, double distance) : focus1(f1), focus2(f2), distanceSum(distance) {}

    std::pair<Point, Point> focuses() const;
    std::pair<Line, Line> directrices() const;
    double eccentricity() const;
    Point center() const;

    double perimeter() const override;
    double area() const override;
    bool operator==(const Shape& another) const override;
    bool operator!=(const Shape& another) const override;
    bool isCongruentTo(const Shape& another) const override;
    bool isSimilarTo(const Shape& another) const override;
    bool containsPoint(Point point) const override;

    void rotate(Point center, double angle) override;
    void reflex(Point center) override;
    void reflex(Line axis) override;
    void scale(Point center, double coefficient) override;

protected:
    Point focus1;
    Point focus2;
    double distanceSum;

    double getMajorAxis() const;
    double getMinorAxis() const;
};


//functions returning some information about the ellipse
std::pair<Point, Point> Ellipse::focuses() const {
    return std::make_pair(focus1, focus2);
}

double Ellipse::getMajorAxis() const {
    return 0.5 * distanceSum;
}

double Ellipse::getMinorAxis() const {
    double a = getMajorAxis();
    double c = 0.5 * (focus1 - focus2).length();
    return sqrt(a * a - c * c);
}

double Ellipse::eccentricity() const {
    return (focus1 - focus2).length() / (2 * getMajorAxis());
}

std::pair<Line, Line> Ellipse::directrices() const {
    return std::make_pair(Line(eccentricity(), 0.0, getMajorAxis()), Line(eccentricity(), 0.0, -getMajorAxis()));
}

Point Ellipse::center() const {
    return (focus1 + focus2) * 0.5;
}

double Ellipse::perimeter() const {
    return M_PI * (3 * (getMinorAxis() + getMajorAxis()) - sqrtl((3 * getMajorAxis() + getMinorAxis()) * (getMajorAxis() + 3 * getMinorAxis())));
}
double Ellipse::area() const {
    return std::fabs(M_PI * getMajorAxis() * getMinorAxis());
}




bool Ellipse::operator==(const Shape& another) const {
    try {                                                                //two ellipses are equal if they have same focuses and distanceSum
        const auto a = dynamic_cast<const Ellipse&>(another);
        bool same_focuses = ((focus1 == a.focus1) && (focus2 == a.focus2)) || ((focus1 == a.focus2) && (focus2 == a.focus1));
        bool same_distSum = (equal(distanceSum, a.distanceSum));
        return same_focuses&&same_distSum;
    }
    catch (std::bad_cast& m) {
        return false;
    }
}

bool Ellipse::operator!=(const Shape& another) const {
    return !(*this == another);
}

bool Ellipse::isCongruentTo(const Shape& another) const {                //two ellipses are congruent if they are similar and have same distanceSum
    try {
        const auto a = dynamic_cast<const Ellipse&>(another);
        return equal(eccentricity(), a.eccentricity()) && equal(distanceSum, a.distanceSum);
    }
    catch (std::bad_cast& m) {
        return false;
    }
}

bool Ellipse::isSimilarTo(const Shape& another) const {                  //ellipses of similar eccentricity are similar
    try {
        const auto a = dynamic_cast<const Ellipse&>(another);
        return equal(eccentricity(), a.eccentricity());
    }
    catch (std::bad_cast& m) {
        return false;
    }
}

bool Ellipse::containsPoint(Point point) const {
    return leq((point - focus1).length() + (point - focus2).length(), distanceSum);
}




//ellipse movement consists of moving its focuses

void Ellipse::rotate(Point center, double angle) {
    focus1.rotate(center, angle);
    focus2.rotate(center, angle);
}

void Ellipse::reflex(Point center) {
    focus1.reflex(center);
    focus2.reflex(center);
}

void Ellipse::reflex(Line axis) {
    focus1.reflex(axis);
    focus2.reflex(axis);
}

void Ellipse::scale(Point center, double coefficient) {
    focus1.scale(center, coefficient);
    focus2.scale(center, coefficient);
    distanceSum *= coefficient;
}

class Circle : public Ellipse {
public:
    Circle(Point p, double r);
    double radius() const;
    double perimeter() const override;
};

Circle::Circle(Point p, double r) {
    focus1 = p;
    focus2 = p;
    distanceSum = 2 * r;
}

double Circle::radius() const {
    return distanceSum / 2.0;
}

double Circle::perimeter() const {
    return 2 * M_PI * radius();
}





class Rectangle: public Polygon {
public:
    Rectangle(Point a, Point b, double tg);
    Point center() const;
    std::pair<Line, Line> diagonals() const;
};

Rectangle::Rectangle(Point a, Point b, double tg) {
    vertices.resize(4, Point());
    vertices[0] = a;
    vertices[2] = b;
    Point center = a + b;
    tg = (leq(tg, 1)) ? tg : (1.0 / tg);
    double angle = -(std::atan(tg) * 360.0 / M_PI);
    vertices[1] = a;
    vertices[1].rotate(center, angle);
    vertices[3] = b;
    vertices[3].rotate(center, angle);
}

Point Rectangle::center() const {                         //center of a polygon is the center of it's diagonal
    return Point((vertices[0] + vertices[2]) * 0.5);
}

std::pair<Line, Line> Rectangle::diagonals() const {
    Line diagonal1 = Line(vertices[0], vertices[2]);
    Line diagonal2 = Line(vertices[1], vertices[3]);
    return std::make_pair(diagonal1, diagonal2);
}




class Square: public Rectangle {
public:
    Circle circumscribedCircle() const;
    Circle inscribedCircle() const;
    Square(Point a, Point b) : Rectangle(a, b, 1) {};
};

Circle Square::circumscribedCircle() const {
    return Circle(center(), 0.5 * ((vertices[0] - vertices[1]).length()));
}

Circle Square::inscribedCircle() const {
    Circle inscribed = circumscribedCircle();
    inscribed.scale(center(), sqrt(1.0 / 2.0));
    return inscribed;
}




class Triangle: public Polygon {
public:
    Triangle(const Point& a, const Point& b, const Point& c);
    Circle circumscribedCircle() const;
    Circle inscribedCircle() const;
    Point centroid() const;
    Point orthocenter() const;
    Line EulerLine() const;
    Circle ninePointsCircle() const;
};

Triangle::Triangle(const Point& a, const Point& b, const Point& c) {
    vertices.push_back(a);
    vertices.push_back(b);
    vertices.push_back(c);
}

Circle Triangle::circumscribedCircle() const {
    Line AB = Line(vertices[0], vertices[1]);               //circumcenter is the intersection of middle perpendiculars
    Line BC = Line(vertices[1], vertices[2]);
    Point Mc = (vertices[0] + vertices[1]) * 0.5;
    Point Ma = (vertices[1] + vertices[2]) * 0.5;
    Line midPerC = Line(Mc, Mc + AB.normal());
    Line midPerA = Line(Ma, Ma + BC.normal());

    Point circumcenter = Point(midPerA, midPerC);
    double radius = (vertices[0] - circumcenter).length();

    return Circle(circumcenter, radius);
}

Circle Triangle::inscribedCircle() const {
    double c = (vertices[0] - vertices[1]).length();
    double a = (vertices[1] - vertices[2]).length();
    double b = (vertices[2] - vertices[0]).length();

    Point incenter = (Vector(vertices[0]) * a + Vector(vertices[1]) * b + Vector(vertices[2]) * c) * (1.0 / (a + b + c));    // formula from mass geometry
    double radius = (2 * area()) / (a + b + c);
    return Circle(incenter, radius);
}

Point Triangle::centroid() const {
    return Point((vertices[0] + vertices[1] + vertices[2]) * (1.0 / 3.0));    // formula from mass geometry
}

Point Triangle::orthocenter() const {
    Line AB = Line(vertices[0], vertices[1]);
    Line BC = Line(vertices[1], vertices[2]);
    Line heightC = Line(vertices[2], vertices[2] + AB.normal());
    Line heightA = Line(vertices[0], vertices[0] + BC.normal());
    return Point(heightA, heightC);
}

Line Triangle::EulerLine() const {
    return Line(orthocenter(), centroid());
}

Circle Triangle::ninePointsCircle() const {
    Circle eulerCircle = circumscribedCircle();         //great geometry fact :)
    eulerCircle.scale(centroid(), -0.5);
    return eulerCircle;
}
