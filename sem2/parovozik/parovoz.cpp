#include <iostream>
using namespace std;
class Train
{
public:
    // Создать паровоз массой m,
    // стоящий в начале координат
    Train(double m);

    // Ехать с текущей скоростью в течение времени dt
    void move(double dt);

    // Изменить полный импульс паровоза (p = mv) на dp
    // Изменение может менять знак скорости
    void accelerate(double dp);

    // Получить текущую координату паровоза
    double getX();

private:
    double mass;
    double v;
    double x;
};
Train::Train(double m) {
    mass = m;
    x = 0;
    v = 0;
}
void Train::move(double dt) {
    x += v*dt;
}
void Train::accelerate(double dp) {
    v += dp/mass;
}
double Train::getX() {
    return x;
}



int main() {
    // Код для базового тестирования реализации класса:
        Train t(10);
    t.accelerate(1); // Скорость стала 0.1
    t.move(1);
    cout << "Current X: " << t.getX() << endl;
    t.move(1);
    cout << "Current X: " << t.getX() << endl;
    t.accelerate(-2); // Скорость стала -0.1
    t.move(3);
    cout << "Current X: " << t.getX() << endl;
    // Базовый тест должен вывести:
    //
    // Current X: 0.1
    // Current X: 0.2
    // Current X: -0.1
    return 0;
}