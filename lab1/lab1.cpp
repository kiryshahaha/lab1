//предстоит сделать проверку на деление на нечистый 0, в вычислениях с числами с плавающей точкой (тип double) из-за округлений результат может не быть ровно 0, даже если теоретически должен быть.
#include <iostream>
#include <cmath>
#include <windows.h>
#include <string>
using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);

    double a_deg = 0.0; 
    const double PI = 3.141592;
    const double normal = 0.0001;
    double z1 = 0.0; 
    double z2_arg = 0.0;
    double z2 = 0.0; 

    while (true) {
        cout << "Enter alpha angle value (in degrees): " << endl;
        string input; //объявляем введенное пользователем сообщение строкой
        cin >> input;

        // Проверка на наличие запятой во вводе, если не находится запятая то возвращается string::npos
        if (input.find(',') != string::npos) {
            cout << "Error: use a dot instead of a comma for decimal numbers. Try again." << endl;
            continue;
        }

        // Попытка преобразовать ввод в double (проверка на недопустимые символы)
        try {
            a_deg = stod(input);

            // Проверка на допустимый диапазон значений угла (0-360)
            if (a_deg < 0 || a_deg >= 360) {
                cout << "Error: incorrect value of degrees, must be in range 0-360." << endl;
                continue;
            }

            break;
        }
        //исключение при неудачном преобразовании строки в число
        catch (invalid_argument&) {
            cout << "Error: incorrect input! Expected a number" << endl;
        }
    }

    double a_rad = a_deg * PI / 180.0;

    double z1_num = sin(PI / 2 + 3 * a_rad);
    double z1_denom = 1 - sin(3 * a_rad - PI);

    // Знаменатель z1 может быть приблизительно равен 0
    if (abs(z1_denom) < normal) {
        cout << "Error: the denominator z1 is too small (division by 0)" << endl;
    }
    else {
        z1 = z1_num / z1_denom;
        cout << "It worked! z1 = " << z1 << endl;
    }

    z2_arg = (5 * PI / 4) + (3 * a_rad / 2);
    double tan_chek = fmod(z2_arg, PI); // fmod вычисляет остаток от деления двух чисел с плавающей точкой
    // tan не определён в точках П/2 и -П/2
    if (abs(tan_chek - PI / 2) < normal || abs(tan_chek + PI / 2) < normal) { 
        cout << "Error: The z2 argument is close to the point where the cotangent is undefined!" << endl;
    }
    else {
        z2 = 1 / tan(z2_arg);
        cout << "It worked! z2 = " << z2 << endl;
    }

    // Сравнение z1 и z2 только если оба значения вычислены
    if (!(abs(z1_denom) < normal) && !(abs(tan_chek - PI / 2) < normal || abs(tan_chek + PI / 2) < normal)) {
        if (abs(z1 - z2) < normal) {
            cout << "z1 and z2 approximately equal (the difference is less than " << normal << ")" << endl;
        }
        else {
            cout << "z1 and z2 are different. Difference: " << abs(z1 - z2) << endl;
        }
    }

    return 0;
}