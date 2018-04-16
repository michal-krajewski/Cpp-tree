//
// Created by Michał Krajewski on 09.12.2017.
//

#ifndef LAB3_CNODE_H
#define LAB3_CNODE_H

#define DEF_VALUE "1";

#include <vector>
#include <string>
#include "CVariable.h"
using namespace std;

int const VALUE_TYPE = 0;
int const VARIABLE_TYPE = -1;
int const ONE_ARG_OP = 1;
int const TWO_ARG_OP = 2;
int const ERR_VAR_NOT_FOUND = 1;
int const ERR_DIVISION_BY_ZERO = 2;



class CNode {
    friend class CTree;
public:
    CNode();
    CNode(CNode &in_node);
    ~CNode();

    bool createTree(string *ps_formula, string::iterator *itr);
    CNode* getLeft();
    int getVarAmount();
    string getVars();
    double sum(CVariable **pv_variables ,int i_vars ,int *error_buffer);
    int nodesNumber(int level, int itr);
private:
    CNode **ppan_children = NULL;
    string s_data = DEF_VALUE;
    int i_type;
    int children_size = 0;


    //methods
    int getType();
    string prefPrint();
    double sin(double d_in);
    double cos(double d_in);



};


#endif //LAB3_CNODE_H
