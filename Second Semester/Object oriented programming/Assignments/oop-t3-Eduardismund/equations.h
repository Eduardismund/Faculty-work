#include <string>
#include <iostream>

class Equation{
private:
    int a,b,c;
public:
    Equation(int a, int b, int c): a{a}, b{b}, c{c}{};
    int getA() const{
        return a;
    };
    int getB() const{
        return b;
    };
    int getC() const{
        return c;
    };

    void setA(int aa) {
        a=aa;
    }

    void setB(int bb){
        b=bb;
    }

    void setC(int cc){
        c=cc;
    }

    int getDegree() const{
        if (a==0)
        {
            if(b==0)
            {
                return 0;
            }
            else{
                return 1;
            }
        }
        else return 2;
    }

    std::string toString() const{

        std::string a_str="", b_str="", c_str="";
        if(a!=0) {
            if (a < 0) {
                a_str = std::to_string(a) + "*x^2";
            }
            else
            {
                if(a==1)
                    a_str="x^2";
                else
                    a_str = std::to_string(a) + "*x^2";


            }
        }

        if(b!=0) {
            if (b < 0) {
                b_str = std::to_string(b) + "*x";
            } else {
                if (a == 0)
                    b_str = std::to_string(b) + "*x";
                else if (b == 1)
                    b_str = "x";
                else
                    b_str = "+" + std::to_string(b) + "*x";
            }
        }
        if(c!=0){
            if (c < 0) {
                c_str = std::to_string(c);
            } else
            {
                if(a==0 and b==0)
                    c_str = std::to_string(c);
                else
                    c_str = "+" + std::to_string(c);
            }
        }

        return a_str+b_str+c_str;
    };
};



