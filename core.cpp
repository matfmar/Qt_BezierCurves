#include "core.h"

namespace MMarzec {

    int countBezierPoints(TBezierPoint* list) {
        int n(0);
        TBezierPoint* runner(list);
        while (runner != nullptr) {
            n++;
            runner = runner -> next;
        }
        return n;
    }

    double silnia(int n) {
        int a = 1;
        for (int i=1; i < n+1; ++i) {
            a *= i;
        }
        return ((double) (a));
    }

    double WielomianB(int i, int n, double u) {
        if(i < 0 || i > n)
            return 0;
        else {
            if(i == 0)
                return pow(1-u, n);
            return silnia(n) * pow(u, i) * pow(1-u, n-i) / (silnia(i) * silnia(n-i));
        }
    }

    void saveCurve(double x, double y) {
        std::ofstream file;
        file.open("krzywa.txt", std::ios::app);
        if (!file.is_open())
            return;
        std::string s = "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
        file << s << std::endl;
        file.close();

    }

    void createFile() {
        std::ofstream file;
        file.open("krzywa.txt");
        if (!file.is_open())
            return;
        file.close();

    }

    TMyPoint TBezierCurve::produceNextPoint(double u) {

        double licznikX = 0.0;
        double licznikY = 0.0;
        double mianownik = 0.0;
        double x = 0.0;
        double y = 0.0;
        TBezierPoint* controlPointRunner(controlPointList);
        int i =-1;
        while (controlPointRunner != nullptr) {
            i++;
            licznikX += controlPointRunner -> w * controlPointRunner -> x * WielomianB(i, controlPointNumber-1, u);
            licznikY += controlPointRunner -> w * controlPointRunner -> y * WielomianB(i, controlPointNumber-1, u);
            mianownik += controlPointRunner -> w * WielomianB(i, controlPointNumber-1, u);
            controlPointRunner = controlPointRunner -> next;
        }
        if (mianownik != 0) {
            x = licznikX/mianownik;
            y = licznikY/mianownik;
        }
        else {
            x = 0;
            y = 0;
        }
        return TMyPoint(x, y);

    }



}
