#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// ������� f(x), ��� ������� ���� �������
double f(double x) {
    if (2 - x * x < 0) {
        cout << ("����������� ��������� �������������, x ������� �� ������� ������� �����������.");
    }
    return x * (sqrt(2 - x * x));  // ������ ������� �������
}

// ������ ����������� �������
double df(double x) {
    if (2 - x * x < 0) {
        cout << ("����������� ��������� �������������, x ������� �� ������� ������� �����������.");
    }
    return (2 * (1 - x * x)) / sqrt(2 - x * x);
}

// ������ ����������� f''(x)
double ddf(double x) {
    if (2 - x * x < 0) {
        cout<<("����������� ��������� �������������, x ������� �� ������� ������� �����������.");
    }
    return (2 * x * (x * x - 3)) / pow(2 - x * x, 1.5);
}

// ������� ��� ������ �����������
void conclusion(double root, int count) {
    if (!isnan(root)) {
        cout << "������������ �������� ��������: " << root << endl;
        cout << "�������� ������� � ��������� �����: " << f(root) << endl;
    }
    cout << "���������� ��������: " << count << endl; // ����� ���������� ��������
}

//����� ���������
double dichotomy(double a, double b, double e, int& count) {
    double mid1, mid2;

    while ((b - a) / 2 >= e) {  // ���� ����� ��������� ������ ��������� ��������
        mid1 = (b + a - e) / 2;  // ����� ������� �������
        mid2 = (b + a + e) / 2;  // ������ ������� �������

        count++; // ����������� ������� ��������

        // ����� ������� �������� ��� �������
        cout << "�������� " << left << setw(2) << count << ":  a = " << left << setw(10) << a 
            << ", b = " << left << setw(10) << b << " mid1 = " << left << setw(10)
            << mid1 << ", f(mid1) = " << left << setw(10) << f(mid1) << ", mid2 = " << left 
            << setw(10) << mid2 << ", f(mid2) = " << left << setw(10)  << f(mid2) << endl;

        // ����������, � ����� �� �������� �������� ������� ������
        if (f(mid1) < f(mid2))
            b = mid2;  // ������ ������� b
        else
            a = mid1;  // ������ ������� a
    }

    return (a + b) / 2; // ���������� ��������� ����������� ��������
}

//����� �������� �������
double golden_section(double a, double b, double e, int& count) {
    const double phi = (sqrt(5) - 1) / 2;  // ��������� �������� �������

    // ��������� ��������� �����
    double x1 = a + (b - a) * (1 - phi);
    double x2 = a + (b - a) * phi;
    double f1 = f(x1);
    double f2 = f(x2);

    while ((b - a) > e) {  // ���� �������� ������ ��������
        count++; // ����������� ������� ��������

        // ����� ������� �������� ��� �������
        cout << "�������� " << left << setw(2) << count << ": a = " << left << setw(10) << a 
            << ", b = " << left << setw(10) << b << ", x1 = " << left << setw(10) << x1 
            << ", f(x1) = " << left << setw(10) << f1 << ", x2 = " << left << setw(10) << x2 
            << ", f(x2) = " << left << setw(10) << f2 << endl;

        if (f1 <= f2) {
            b = x2;    // �������� ������ ������� �����
            x2 = x1;   // ���������� x2 �����
            f2 = f1;   // ��������� �������� f(x2)
            x1 = a + (b - a) * (1 - phi); // ��������� ����� x1
            f1 = f(x1);
        }
        else {
            a = x1;    // �������� ����� ������� ������
            x1 = x2;   // ���������� x1 ������
            f1 = f2;   // ��������� �������� f(x1)
            x2 = a + (b - a) * phi; // ��������� ����� x2
            f2 = f(x2);
        }
    }

    return (a + b) / 2; // ���������� ��������� ����������� ��������
}

//����� ������������ ������
double porazryad_poisk(double a, double b, double e, int& count) {
    double x0 = a;
    double h = (b - a) / 4;
    double x1, f0, f1;

    f0 = f(x0);
    while (fabs(h) >= e) {
        count++;
        x1 = x0 + h;
        f1 = f(x1);

        cout << "�������� " << left << setw(4) << count << " ���: " << left 
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

//����� ����
double chord_method(double a, double b, double e, int& count) {

    if (df(a) < 0 && df(b) < 0) return b;
    if (df(a) > 0 && df(b) > 0) return a;

    double x;
    while (fabs(b - a) > e) {
        count++;

        if (fabs(df(a) - df(b)) < 1e-9) {
            cerr << "������: ������� �� ���� ��� ���������� x" << endl;
            return (a + b) / 2;
        }

        x = a - (df(a) / (df(a) - df(b))) * (a - b);

        cout << "�������� " << left << setw(4) << count
            << " | a = " << left << setw(15) << a << " b = " << left << setw(15) << b << " x = " 
            << left << setw(15) << x << "f'(x) = " << left << setw(15) << df(x) << "f(x) = " 
            << left << setw(15) << f(x) << endl;

        if (fabs(df(x)) <= e) {
            return x;
        }

        // ���������� ����� �������� ������
        if (df(x) > 0) {
            b = x;
        }
        else {
            a = x;
        }
        
    }
    return x;
}

//����� �������
double newton_method(double x0, double e, int& count) {
    double x = x0;

    do {
        count++;

        cout << "�������� " << left << setw(4) << count
            << "| x = " << left << setw(15) << x << "f'(x) = " << left << setw(15) << df(x) 
            << "f''(x) = " << left << setw(15) << ddf(x) << "f(x) = " << left << setw(15) 
            << f(x) << endl;

        if (ddf(x) < 1e-9) {
            std::cerr << "������: ������ ����������� ������� ���� ��� ������� ������." << std::endl;
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

        cout << "�������� " << left << setw(4) << count << "| a = " << left << setw(10) << a 
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

    // ������� ���� ������ ������
    cout << "�������� �����: \n1 - ���������\n2 - �������� �������\n3 - ������������ ������\n4 - ����� ����\n5 - ����� �������\n6 - ����� ������� �����\n";
    cin >> choice;

    double root; // ���������� ��� �������� ����������

    // ��������� ��������������� �����
    switch (choice) {
    case 1:
        cout << "����� ���������:\n";
        root = dichotomy(a, b, e, count);
        break;
    case 2:
        cout << "����� �������� �������:\n";
        root = golden_section(a, b, e, count);
        break;
    case 3:
        cout << "����� ������������ ������:\n";
        root = porazryad_poisk(a, b, e, count);
        break;
    case 4:
        cout << "����� ����:\n";
        root = chord_method(a, b, e, count);
        break;
    case 5:
        double x0;
        cout << "������� ��������� �����������: ";
        cin >> x0;
        cout << "����� �������:\n";
        root = newton_method(x0, e, count);
        break;
    case 6:
        cout << "����� ������� �����:\n";
        root = midpoint_method(a, b, e, count);
        break;
    default:
        cout << "������������ �����!" << endl;
        return menu(a, b, e); // ��������� ����� main() � ������ ������
    }

    conclusion(root, count); // ������� ����������

    system("pause");
    system("cls");
    return menu(a,b,e);
}

int main(){
     setlocale(LC_ALL, "Russian"); // ������������� ������ ��� ����������� ����������� �������� �����

// ������� ��������� � ��������
double a, b;
double e;

cout << "������� ����� �������: ";
cin >> a;
cout << "������� ������ �������: ";
cin >> b;
cout << "������� ������ ��������: ";
cin >> e;
cin.ignore();
system("cls");

menu(a,b,e);

system("cls");
return main();
}
