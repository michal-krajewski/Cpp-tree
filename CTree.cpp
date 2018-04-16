//
// Created by Michał Krajewski on 09.12.2017.
//

#include "CTree.h"

CTree::CTree(string s_formula) {
    ps_formula = new string(s_formula);
}

CTree::CTree(CTree &in_tree) {
    ps_formula = new string(*in_tree.ps_formula);
    pn_root = new CNode(*in_tree.pn_root);
    i_vars = in_tree.i_vars;
    pv_variables = new CVariable*[i_vars];
    for(int i = 0; i < i_vars; i++){
        pv_variables[i] = new CVariable(*in_tree.pv_variables[i]);
    }
}

CTree::~CTree() {
    delete ps_formula;
    delHelper();
}

bool CTree::buildTree() {
    if (pn_root!=NULL)
        delete pn_root;
    pn_root=new CNode();
    string::iterator *itr = new string::iterator(ps_formula->begin());
    bool not_enough_args = pn_root->createTree(ps_formula, itr);
    if(not_enough_args){ // formula update here!
        //*ps_formula = prefPrint();
    }
    return not_enough_args;
}

string CTree::prefPrint() {
    return pn_root->prefPrint();
}

void CTree::joinTree(CTree *in_tree) {
    if(pn_root->children_size == 0){
        delete pn_root;
        pn_root = new CNode(*in_tree->pn_root);
    }
    else{
        CNode *temp_node = pn_root->getLeft();
        delete temp_node->ppan_children[0];
        temp_node->ppan_children[0] = new CNode(*in_tree->pn_root);
    }
}

int CTree::varAmount() {
    return pn_root->getVarAmount();
}

string CTree::getVars() {
    return pn_root->getVars();
}

void CTree::createVariables() {
    if(pv_variables != NULL){
        for(int i = 0; i < i_vars; i++){
            delete pv_variables[i];
        }
        delete [] pv_variables;
    }
    i_vars = varAmount();
    pv_variables = new CVariable*[i_vars];
    string temp_variables = getVars();
    string::iterator itr = temp_variables.begin();
    for(int i = 0; i < i_vars; i++){
        while(*itr == ' '){
            itr += 1;
        }
        string s_var_name = "";
        while(*itr != ' ' && itr < temp_variables.end()){
            s_var_name += *itr;
            itr += 1;
        }
        bool already_created = false;
        for(int j = 0; j < i; j++){
            if(pv_variables[j]->getVariable() == s_var_name){
                already_created = true;
            }
        }
        if(!already_created) pv_variables[i] = new CVariable(s_var_name);
        else {
            i_vars--;
            i--;
        }
    }
}

string CTree::vars() {
    string out = "";
    for(int i = 0; i < i_vars; i++){
        out += pv_variables[i]->getVariable() + " ";
    }
    return out;
}

double CTree::calculate(string in_values, int *error_buffer) {
    string::iterator itr = in_values.begin();
    for(int i = 0; i < i_vars; i++) {
        while (*itr == ' ') {
            itr += 1;
        }
        string s_value = "";
        while (*itr != ' ' && itr < in_values.end()) {
            s_value += *itr;
            itr += 1;
        }
        double d_value;
        try{
            d_value = stod(s_value);
        }
        catch (invalid_argument &ex){
            *error_buffer = ERR_INVALID_ARGUMENT;
            return 0;
        }
        pv_variables[i]->setValue(d_value);
    }
    while (itr < in_values.end() && *itr == ' ') {
        itr += 1;
    }
    if(itr != in_values.end()){
        *error_buffer = ERR_TOO_MANY_ARGS;
        return 0;
    }
    else {
        return pn_root->sum(pv_variables, i_vars, error_buffer);
    }
}

CTree &CTree::operator=(CTree &pt_other) {
    delHelper();
    pn_root = new CNode(*pt_other.pn_root);
    i_vars = pt_other.i_vars;
    createVariables();
    *ps_formula = prefPrint();
    return *this;
}

void CTree::delHelper() {
    if(pn_root != NULL){
        delete pn_root;
    }
    if(pv_variables != NULL){
        for(int i = 0; i < i_vars; i++){
            delete pv_variables[i];
        }
        delete [] pv_variables;
    }
}

CTree &CTree::operator+(CTree &pt_other) { //Przykład błędu z wyciekiem pamięci. Nie powinienem tutaj zwracać referencji. 
    CTree *out = new CTree(*this);
    out->joinTree(&pt_other);
    out->createVariables();
    return *out;
}
/* Poprawiona wersja
CTree CTree::operator+(CTree &pt_other) { 
    CTree out = new CTree(this);
    out.joinTree(&pt_other);
    out.createVariables();
    return out;
}
*/
int CTree::nodeLvlAmount(int level) {
    if(level <= 0)
        return 0;
    else
        return pn_root->nodesNumber(level, 1);
}






