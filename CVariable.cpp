//
// Created by Michał Krajewski on 10.12.2017.
//

#include "CVariable.h"

CVariable::CVariable(string in_var) {
    s_var = in_var;
}

CVariable::CVariable(CVariable &in_cvar) {
    s_var = in_cvar.s_var;
    d_val = in_cvar.d_val;
}

CVariable::~CVariable() {

}

string CVariable::getVariable() {
    return s_var;
}

double CVariable::getValue() {
    return d_val;
}

void CVariable::setValue(double in_val) {
    d_val = in_val;
}

