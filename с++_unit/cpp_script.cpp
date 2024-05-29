#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;


double x10 = 50, x20 = -20;
double dt = 0.001, t = 0;

struct cur_x {
    double x1, x2, n1, n2, u;
    double x1p, x2p, n1p, n2p, up;

    cur_x() {
        x1 = n1 = x10;
        x2 = x20;
        u = n2 = 0;
        x1p = x2p = n1p = n2p = up = 0;
    }

    void next_moment() {
        t += dt;
        x1p = x1 + x2 * dt;
        x2p = x2 + (4.9 * x1 - 0.25 * u) * dt;
        up = (819.6 * n1 + 408 * n2); //matrix k is inputing
        n1p = n1 + (102 * (x1 - n1) + n2) * dt; //matrix l is inputing
        n2p = n2 + (-200 * n1 + 204.9 * x1 - 0.25 * u) * dt;
        x1 = x1p;
        x2 = x2p;
        n1 = n1p;
        n2 = n2p;
        u = up;
    }

    void print() {
        cout << "t = " << t << endl;
        cout << "x: " << x1 << ", " << x2 << endl;
        cout << "n: " << n1 << ", " << n2 << endl;
        cout << "u: " << u << endl;
    }

    void plus_t(double t) {
        for (double i = 0; i < t / dt; i++)
            next_moment();
    }
};

int click_it(cur_x a) {
    char c;
    do {
        a.next_moment();
        c = getch();
        if (c == 32) for (double i = 0; i < 0.05 / dt - 2; i++) a.next_moment(); //+5dt - space
        else if (c == 'x') a.plus_t(3 - 1.5 * dt);
        a.print();
    } while (c != 27);
    return 0;
}

int main() {
    cur_x obj;
    obj.print();
    click_it(obj);
    return 0;
}

