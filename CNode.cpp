//
// Created by Michał Krajewski on 09.12.2017.
//

#include "CNode.h"

CNode::CNode() { //Creates node with default value (1)
    i_type = VALUE_TYPE;
    children_size = i_type;
    ppan_children = NULL;
}
CNode::CNode(CNode &in_node){
    s_data = in_node.s_data;
    i_type = in_node.i_type;
    children_size = in_node.children_size;
    ppan_children = new CNode* [children_size];
    for(int i = 0; i < children_size; i++){
        ppan_children[i] = new CNode(*in_node.ppan_children[i]);
    }
}
CNode::~CNode() {
    for(int i = 0; i < children_size; i++){
        delete ppan_children[i];
    }
    delete [] ppan_children;
}
int CNode::getType() {
    try{
        stod(s_data);
        return VALUE_TYPE;
    }
    catch (invalid_argument &ex) {}
    if(s_data == "+" || s_data == "-" || s_data == "/" || s_data == "*") {
        return TWO_ARG_OP;
    }
    else if (s_data == "sin" || s_data == "cos") {
        return ONE_ARG_OP;
    }
    else {
        return VARIABLE_TYPE;
    }
}

bool CNode::createTree(string *ps_formula, string::iterator *itr) {
    bool not_enough_args = false;
    //skip all spaces
    while ((**itr) == ' ') {
        *itr += 1;
    }
    if(*itr != ps_formula->end()) {
        string stemp_value = "";
        while (**itr != ' ' && *itr < ps_formula->end()) {
            stemp_value += **itr;
            *itr += 1;
        }
        s_data = stemp_value;
        i_type = getType();
        if(i_type < 0){
            children_size = 0;
        }
        else {
            children_size = i_type;
        }
        ppan_children = new CNode *[children_size];
        for(int i = 0;i < children_size; i++){
            ppan_children[i] = new CNode();
            not_enough_args = not_enough_args||ppan_children[i]->createTree(ps_formula, itr);
        }
    }
    else {
        not_enough_args = true;
    }
    return not_enough_args;
}

string CNode::prefPrint() {
    string pref = s_data;
    for(int i = 0; i < children_size; i++){
        pref += " " + ppan_children[i]->prefPrint();
    }
    return pref;
}

CNode *CNode::getLeft() {//root can't be operand
    if(i_type > 0){
        if(ppan_children[0]->children_size == 0){
            return this;
        }
        else{
            return ppan_children[0]->getLeft();
        }
    }
    return this;
}

int CNode::getVarAmount() {
    if(i_type == VARIABLE_TYPE){
        return 1;
    }
    else if(i_type == VALUE_TYPE){
        return 0;
    }
    else {
        int i_var_amount = 0;
        for(int i = 0; i < children_size; i++){
            i_var_amount += ppan_children[i]->getVarAmount();
        }
        return i_var_amount;
    }
}

string CNode::getVars() {
    if(i_type == -1){
        return s_data + " ";
    }
    else if(i_type == 0){
        return "";
    }
    else {
        string s_vars = "";
        for(int i = 0; i < children_size; i++){
            s_vars += ppan_children[i]->getVars();
        }
        return s_vars;
    }
}

double CNode::sum(CVariable **pv_variables ,int i_vars ,int *error_buffer) {
    double sum = 0;
    if(i_type == VARIABLE_TYPE){
        for(int i = 0; i < i_vars; i++){
            if(pv_variables[i]->getVariable() == s_data){
                return pv_variables[i]->getValue();
            }
        }
        *error_buffer = ERR_VAR_NOT_FOUND;
        return 0;
    }
    else if(i_type == VALUE_TYPE){
        return stod(s_data);
    }
    else if(s_data == "+") {
        sum = (double) ppan_children[0]->sum(pv_variables ,i_vars ,error_buffer) + ppan_children[1]->sum(pv_variables ,i_vars ,error_buffer);
        return sum;
    }
    else if(s_data == "-") {
        return (double) ppan_children[0]->sum(pv_variables ,i_vars ,error_buffer) - ppan_children[1]->sum(pv_variables ,i_vars ,error_buffer);
    }
    else if(s_data == "*") {
        sum = (double) ppan_children[0]->sum(pv_variables ,i_vars ,error_buffer) * ppan_children[1]->sum(pv_variables ,i_vars ,error_buffer);
        return sum;
    }
    else if(s_data == "/") {
        double d_second = ppan_children[1]->sum(pv_variables ,i_vars ,error_buffer);
        if(d_second == 0){
            *error_buffer = ERR_DIVISION_BY_ZERO;
            return 0;
        }
        else{
            return (double) ppan_children[0]->sum(pv_variables ,i_vars ,error_buffer) / d_second;
        }
    }
    else if(s_data == "sin"){
        return sin(ppan_children[0]->sum(pv_variables ,i_vars ,error_buffer));
    }
    else if(s_data == "cos"){
        return cos(ppan_children[0]->sum(pv_variables ,i_vars ,error_buffer));
    }

}

double CNode::sin(double d_in)  //Bhaskara I's approximation
{
    int mul=1;
    if (d_in<0)
    {
        d_in*=-1;
        mul*=-1;
    }
    while (d_in>=360)
        d_in-=360;
    if (d_in>180)
    {
        mul*=-1;
        d_in-=180;
    }

    return (double) mul*(4*d_in*(180-d_in))/(40500-d_in*(180-d_in));
}
double CNode::cos(double d_in)
{
    return sin(90-d_in);
}

int CNode::nodesNumber(int level, int itr) {
    if(level == itr){
        return 1;
    }
    else{
        if(children_size > 0){
            int amount = 0;
            for(int i = 0; i < children_size; i++){
                amount += ppan_children[i]->nodesNumber(level, itr+1);
            }
            return amount;
        }
        else {
            return 0;
        }
    }
}

