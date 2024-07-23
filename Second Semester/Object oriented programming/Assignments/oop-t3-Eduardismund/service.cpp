
#include "service.h"
#include <cmath>

std::vector<Equation> service::getAllEqs() {
    std::vector<Equation> equations= r.getEqs();
    std::sort(equations.begin(), equations.end(), [](Equation& a, Equation& b){
        return a.getDegree()>b.getDegree();
    });
    return equations;
}


void service::updateEq(int oldA, int oldB, int oldC, int a, int b, int c) {
    std::vector<Equation> eqs=r.getEqs();
    for(Equation& e: r.getEqs())
    {
        int aa=e.getA();
        int bb=e.getB();
        int cc=e.getC();
        if(aa==oldA && bb==oldB && cc==oldC)
        {
            e.setA(a);
            e.setB(b);
            e.setC(c);
            break;
        }
    }
}
std::string service::computeSol(Equation eq) {
    std::string solution, sol1,sol2;
    int a=eq.getA();
    int b=eq.getB();
    int c=eq.getC();

    if(eq.getDegree()==2) {
        int d=b*b-4*a*c;
        if (d > 0) {
            float s1 = ((-1) * float(b) + sqrt(float(d))) / (2 * float(a));
            float s2 = ((-1) * float(b) - sqrt(float(d))) / (2 * float(a));
            sol1 = std::to_string(s1);
            sol2 = std::to_string(s2);
            return "solution: " + sol1 + "; solution: " + sol2;
        }
        if (d == 0) {
            float real = (-1) * float(b) / (2 * float(a));
            return "solution: " + std::to_string(real);
        }
        if (d < 0) {
            d *= -1;
            float real = (-1) * float(b) / (2 * float(a));
            float im = sqrt(float(d)) / (2 * float(a));
            sol1 = std::to_string(real) + "+" + std::to_string(im) + "i";
            sol2 = std::to_string(real) + "-" + std::to_string(im) + "i";
            return "solution: " + sol1 + "; solution: " + sol2;
        }
        return "";
    }
    else if(eq.getDegree()==1){
        float s=-c/b;
        return "solution: " + std::to_string(s);

    }
    else
    {
        return "No solutions!";
    }
}
