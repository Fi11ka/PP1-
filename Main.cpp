#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// Функция f(x), для которой ищем минимум
double f(double x) {
    if (2 - x * x < 0) {
        cout << ("Подкоренное выражение отрицательное, x выходит за пределы области определения.");
    }
    return x * (sqrt(2 - x * x));  // Пример целевой функции
}

// Первая производная функции
double df(double x) {
    if (2 - x * x < 0) {
        cout << ("Подкоренное выражение отрицательное, x выходит за пределы области определения.");
    }
    return (2 * (1 - x * x)) / sqrt(2 - x * x);
}

// Вторая производная f''(x)
double ddf(double x) {
    if (2 - x * x < 0) {
        cout<<("Подкоренное выражение отрицательное, x выходит за пределы области определения.");
    }
    return (2 * x * (x * x - 3)) / pow(2 - x * x, 1.5);
}

// Функция для вывода результатов
void conclusion(double root, int count) {
    if (!isnan(root)) {
        cout << "Приближенное значение минимума: " << root << endl;
        cout << "Значение функции в найденной точке: " << f(root) << endl;
    }
    cout << "Количество итераций: " << count << endl; // Вывод количества итераций
}

//Метод дихотомии
double dichotomy(double a, double b, double e, int& count) {
    double mid1, mid2;

    while ((b - a) / 2 >= e) {  // Пока длина интервала больше требуемой точности
        mid1 = (b + a - e) / 2;  // Левый средний отрезок
        mid2 = (b + a + e) / 2;  // Правый средний отрезок

        count++; // Увеличиваем счетчик итераций

        // Вывод текущих значений для отладки
        cout << "Итерация " << left << setw(2) << count << ":  a = " << left << setw(10) << a 
            << ", b = " << left << setw(10) << b << " mid1 = " << left << setw(10)
            << mid1 << ", f(mid1) = " << left << setw(10) << f(mid1) << ", mid2 = " << left 
            << setw(10) << mid2 << ", f(mid2) = " << left << setw(10)  << f(mid2) << endl;

        // Определяем, в каком из отрезков значение функции меньше
        if (f(mid1) < f(mid2))
            b = mid2;  // Сужаем границу b
        else
            a = mid1;  // Сужаем границу a
    }

    return (a + b) / 2; // Возвращаем найденное приближение минимума
}

//Метод золотого сечения
double golden_section(double a, double b, double e, int& count) {
    const double phi = (sqrt(5) - 1) / 2;  // Отношение золотого сечения

    // Вычисляем начальные точки
    double x1 = a + (b - a) * (1 - phi);
    double x2 = a + (b - a) * phi;
    double f1 = f(x1);
    double f2 = f(x2);

    while ((b - a) > e) {  // Пока интервал больше точности
        count++; // Увеличиваем счетчик итераций

        // Вывод текущих значений для отладки
        cout << "Итерация " << left << setw(2) << count << ": a = " << left << setw(10) << a 
            << ", b = " << left << setw(10) << b << ", x1 = " << left << setw(10) << x1 
            << ", f(x1) = " << left << setw(10) << f1 << ", x2 = " << left << setw(10) << x2 
            << ", f(x2) = " << left << setw(10) << f2 << endl;

        if (f1 <= f2) {
            b = x2;    // Сдвигаем правую границу влево
            x2 = x1;   // Перемещаем x2 влево
            f2 = f1;   // Переносим значение f(x2)
            x1 = a + (b - a) * (1 - phi); // Вычисляем новую x1
            f1 = f(x1);
        }
        else {
            a = x1;    // Сдвигаем левую границу вправо
            x1 = x2;   // Перемещаем x1 вправо
            f1 = f2;   // Переносим значение f(x1)
            x2 = a + (b - a) * phi; // Вычисляем новую x2
            f2 = f(x2);
        }
    }

    return (a + b) / 2; // Возвращаем найденное приближение минимума
}

//Метод поразрядного поиска
double porazryad_poisk(double a, double b, double e, int& count) {
    double x0 = a;
    double h = (b - a) / 4;
    double x1, f0, f1;

    f0 = f(x0);
    while (fabs(h) >= e) {
        count++;
        x1 = x0 + h;
        f1 = f(x1);

        cout << "Итерация " << left << setw(4) << count << " Шаг: " << left 
            << setw(5) << h << " | x = " << left << setw(10) << x0 
            << " f(x) = " << left << setw(10) << f1 << "\n";

        if (f0 > f1) {
            x0 = x1;
            f0 = f1;
            if (x1 < b) {
                continue;
            }
        }
        else {
            h = -h / 4;
        }
    }

    return x0;
}

//Метод хорд
double chord_method(double a, double b, double e, int& count) {

    if (df(a) < 0 && df(b) < 0) return b;
    if (df(a) > 0 && df(b) > 0) return a;

    double x;
    while (fabs(b - a) > e) {
        count++;

        if (fabs(df(a) - df(b)) < 1e-9) {
            cerr << "Ошибка: деление на ноль при вычислении x" << endl;
            return (a + b) / 2;
        }

        x = a - (df(a) / (df(a) - df(b))) * (a - b);

        cout << "Итерация " << left << setw(4) << count
            << " | a = " << left << setw(15) << a << " b = " << left << setw(15) << b << " x = " 
            << left << setw(15) << x << "f'(x) = " << left << setw(15) << df(x) << "f(x) = " 
            << left << setw(15) << f(x) << endl;

        if (fabs(df(x)) <= e) {
            return x;
        }

        // Определяем новый интервал поиска
        if (df(x) > 0) {
            b = x;
        }
        else {
            a = x;
        }
        
    }
    return x;
}

//Медот ньютона
double newton_method(double x0, double e, int& count) {
    double x = x0;

    do {
        count++;

        cout << "Итерация " << left << setw(4) << count
            << "| x = " << left << setw(15) << x << "f'(x) = " << left << setw(15) << df(x) 
            << "f''(x) = " << left << setw(15) << ddf(x) << "f(x) = " << left << setw(15) 
            << f(x) << endl;

        if (ddf(x) < 1e-9) {
            std::cerr << "Ошибка: вторая производная слишком мала для данного метода." << std::endl;
            return -1;
        }

        x = x - df(x) / ddf(x);
    } while (fabs(df(x)) > e);

    return x;
}

double midpoint_method(double a, double b, double e, int& count) {
    double xc;
    while (fabs(b - a) > e) {
        xc = (a + b) / 2;
        double df_xc = df(xc);
        count++;

        cout << "Итерация " << left << setw(4) << count << "| a = " << left << setw(10) << a 
            << "b = " << left << setw(10) << b << "x = " << left << setw(10) << xc << "f(x) = " 
            << left << setw(10) << f(xc) << endl;

        if (df_xc > 0) {
            b = xc;
        }
        else if (df_xc < 0) {
            a = xc;
        }
        else {
            break;
        }
    }
    return (a + b) / 2;
}

int menu(double a, double b, double e) {
    int count = 0;
    int choice;

    // Выводим меню выбора метода
    cout << "Выберите метод: \n1 - Дихотомии\n2 - Золотого сечения\n3 - Поразрядного поиска\n4 - Метод хорд\n5 - Метод Ньютона\n6 - Метод средней точки\n";
    cin >> choice;

    double root; // Переменная для хранения результата

    // Запускаем соответствующий метод
    switch (choice) {
    case 1:
        cout << "Метод дихотомии:\n";
        root = dichotomy(a, b, e, count);
        break;
    case 2:
        cout << "Метод золотого сечения:\n";
        root = golden_section(a, b, e, count);
        break;
    case 3:
        cout << "Метод поразрядного поиска:\n";
        root = porazryad_poisk(a, b, e, count);
        break;
    case 4:
        cout << "Метод хорд:\n";
        root = chord_method(a, b, e, count);
        break;
    case 5:
        double x0;
        cout << "Введите начальное приближение: ";
        cin >> x0;
        cout << "Метод Ньютона:\n";
        root = newton_method(x0, e, count);
        break;
    case 6:
        cout << "Метод средней точки:\n";
        root = midpoint_method(a, b, e, count);
        break;
    default:
        cout << "Некорректный выбор!" << endl;
        return menu(a, b, e); // Повторный вызов main() в случае ошибки
    }

    conclusion(root, count); // Выводим результаты

    system("pause");
    system("cls");
    return menu(a,b,e);
}

int main(){
     setlocale(LC_ALL, "Russian"); // Устанавливаем локаль для корректного отображения русского языка

// Границы интервала и точность
double a, b;
double e;

cout << "Введите левую границу: ";
cin >> a;
cout << "Введите правую границу: ";
cin >> b;
cout << "Введите нужную точность: ";
cin >> e;
cin.ignore();
system("cls");

menu(a,b,e);

system("cls");
return main();
}
