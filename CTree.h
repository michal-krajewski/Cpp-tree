//
// Created by Michał Krajewski on 09.12.2017.
//

#ifndef LAB3_CTREE_H
#define LAB3_CTREE_H

#include "CNode.h"
#include "CVariable.h"

int const ERR_INVALID_ARGUMENT = 5;
int const ERR_TOO_MANY_ARGS = 6;
int const ERR_NO_ERROR = 0;

class CTree {
public:
    CTree(string s_formula);
    CTree(CTree &in_tree);
    ~CTree();

    CTree& operator= (CTree &pt_other);
    CTree& operator+ (CTree &pt_other);
    bool buildTree();
    string prefPrint();
    void joinTree(CTree *in_tree);
    void createVariables();
    string vars();
    double calculate(string in_values, int *error_buffer);
    int nodeLvlAmount(int level);
private:
    CNode *pn_root = NULL;
    string *ps_formula;
    CVariable **pv_variables = NULL;
    int i_vars;

    int varAmount();
    string getVars();
    void delHelper();
};




#endif //LAB3_CTREE_H
