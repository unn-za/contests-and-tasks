#include <iostream>

using namespace std;

class GasHolder
{
public:
    // Создать газгольдер заданного объёма.
    // Температура созданного термостата равна 273 К.
    GasHolder(float v);

    // Уничтожить газгольдер.
   // ~GasHolder();

    // Впрыск порции газа массой m и молярной массой M.
    // Считать, что газ принимает текущую температуру газгольдера за пренебрежимо малое время.
    void inject(float m, float M);

    // Подогреть газгольдер на dT градусов.
    // Считать, что нагрев возможен до любых значений температуры.
    void heat(float dT);

    // Охладить газгольдер на dT градусов.
    // При попытке охладить ниже 0 К температура становится ровно 0 К.
    void cool(float dT);

    // Получить текущее давление в газгольдере.
    // Считать, что для газа верно уравнение состояния PV = (m/M)RT. 
    // Значение постоянной R принять 8.31 Дж/(моль*К).
    float getPressure();

private:
    float vol;
    float temp;
    float v;
};

GasHolder::GasHolder(float v) {
    vol = v;
    temp = 273;
    this->v = 0;
}
//GasHolder::~GasHolder(float v) {}

void GasHolder::inject(float m, float M) {
    v += m/M;
}
void GasHolder::heat(float dT) {
    temp += dT;
}
void GasHolder::cool(float dT) {
    temp -= dT;
    if (temp < 0) {
        temp = 0;
    }
}
float GasHolder::getPressure() {
    return (v*8.31*temp)/vol;
}

int main() {
    GasHolder h(1.0);
    h.inject(29, 29);
    cout << "Pressure after operation: " << h.getPressure() << " Pa" << endl;
    h.inject(29, 29);
    cout << "Pressure after operation: " << h.getPressure() << " Pa" << endl;
    h.heat(273);
    cout << "Pressure after operation: " << h.getPressure() << " Pa" << endl;
    h.cool(373);
    cout << "Pressure after operation: " << h.getPressure() << " Pa" << endl;
    h.cool(373);
    cout << "Pressure after operation: " << h.getPressure() << " Pa" << endl;
    return 0;
}


// smth