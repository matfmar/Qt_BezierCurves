#ifndef CORE_H
#define CORE_H

#include <tgmath.h>
#include <fstream>

namespace MMarzec {



    struct TBezierPoint {
        TBezierPoint(double a, double b,double c = 1) : x(a), y(b), w(c) {}
        double x;
        double y;
        double w;
        TBezierPoint* next = nullptr;
    };

    struct TMyPoint {
        TMyPoint(double a, double b) : x(a), y(b) {}
        double x;
        double y;
    };

    void saveCurve(double x, double y);
    void createFile();

    double silnia(int n);
    double WielomianB(int i, int n, double u);
    int countBezierPoints(TBezierPoint* list);

    class TCurve {

        public:
            TCurve() {}
            TCurve* next = nullptr;
            virtual TMyPoint produceNextPoint(double) = 0;
            virtual ~TCurve() {}
        protected:

        private:

    };

    class TBezierCurve final : public TCurve {

        public:
            TBezierCurve() = default;
            TBezierCurve(TBezierPoint* list, int a) : controlPointList(list), controlPointNumber(a) {}
            ~TBezierCurve() {}
            TMyPoint produceNextPoint(double u) override;
        private:
            TBezierPoint* controlPointList = nullptr;
            int controlPointNumber = 1;
    };

}

#endif
