//
// Created by Michał Krajewski on 10.12.2017.
//

#ifndef LAB3_CVARIABLE_H
#define LAB3_CVARIABLE_H

#define NO_VAL -55;

#include <string>

using namespace std;

class CVariable {
public:
    CVariable(string in_var);
    CVariable(CVariable &in_cvar);
    ~CVariable();

    string getVariable();
    double getValue();
    void setValue(double in_val);
private:
    string s_var = "NONE_VAR";
    double d_val = NO_VAL;
};


#endif //LAB3_CVARIABLE_H
