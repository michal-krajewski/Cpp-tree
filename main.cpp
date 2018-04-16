#include <iostream>
#include <string>
#include <vector>
#include "CTree.h"

using namespace std;

void menu() {
    cout<<"List of commands: \n enter <formula> - builds a tree from the given formula\n vars - prints all variables\n"
        <<" print - prints the tree\n comp <var0> <var1> ... - computes the expression for given variable values\n"
        <<" join <formula> - tries to add the given formula to a root of the current tree\n"
        <<" stop - ends the program\n\n";
}

string* split(string s_in)
{
    int i_pos=s_in.find_first_of("  ");
    string *out=new string[2];
    if (i_pos!=-1)
    {
        out[0]=s_in.substr(0, i_pos);
        out[1]=s_in.substr(i_pos+1)+' ';
    }
    else
    {
        out[0]=s_in;
        out[1]="";
    }
    return out;
}

void interface(){
    menu();
    bool b_go=true;
    bool b_exists=false;
    CTree *pt_tree;
    while (b_go)
    {
        string s_in;
        getline(cin, s_in);
        string *s_input=split(s_in);
        int *pi_error=new int(ERR_NO_ERROR);
        if (s_input[0]=="enter")
        {
            if (s_input[1]=="")
                cout<<"Please enter a formula\n";
            else
            {
                if (b_exists)
                    delete pt_tree;
                pt_tree=new CTree(s_input[1]);
                if (!pt_tree->buildTree())
                    cout<<"Tree created succesfully\n";
                else
                    cout<<"Wrong formula given\nTree fixed to: "<<pt_tree->prefPrint() << endl;
                pt_tree->createVariables();
                b_exists=true;
            }
        }
        else if (s_input[0]=="vars")
        {
            if (b_exists)
                cout<<pt_tree->vars() << endl;
            else
                cout<<"Tree doesn't exist yet\n";
        }
        else if (s_input[0]=="print")
        {
            if (b_exists)
                cout << "Tree: " << pt_tree->prefPrint() << endl;
            else
                cout<<"Tree doesn't exist yet\n";
        }
        else if (s_input[0]=="comp")
        {
            if (b_exists)
            {
                double d_out=pt_tree->calculate(s_input[1], pi_error);
                if (*pi_error==ERR_TOO_MANY_ARGS)
                    cout<<"Error, wrong number of variables\n";
                else if (*pi_error==ERR_INVALID_ARGUMENT)
                    cout<<"Error, wrong arguments\n";
                else if (*pi_error==ERR_DIVISION_BY_ZERO)
                    cout<<"Error, Division by zero!\n";
                else if (*pi_error==ERR_NO_ERROR){
                    cout << "Value: " << to_string(d_out) << endl;
                }
            }
            else
                cout<<"Tree doesn't exist yet\n";
        }
        else if (s_input[0]=="join")
        {
            if (!b_exists)
                cout<<"First tree doesn't exist yet\n";
            else if (s_input[1]=="")
                cout<<"Please enter a formula after the command\n";
            else
            {
                CTree *temp=new CTree(s_input[1]);
                if (!temp->buildTree())
                    cout<<"New tree created\n";
                else
                    cout<<"Wrong formula given\nNew tree fixed to: "<<temp->prefPrint() << endl;
                temp->createVariables();
                //pt_tree->joinTree(temp);
                CTree *out = new CTree("");
                *out = *pt_tree + *temp;
                cout<<"Trees merged\n";
                delete temp;
                delete pt_tree;
                pt_tree = out;
            }

        }
        else if(s_input[0] == "numb"){
            cout << pt_tree->nodeLvlAmount(stoi(s_input[1])) << endl;
        }
        else if (s_input[0]=="stop"||s_input[0]=="exit") {
            b_go = false;
        }
        else if (s_input[0] == "menu"){
            menu();
        }
        else {
            cout << "Wrong command\n";
        }
    }
    if (b_exists)
        delete pt_tree;

}

int main() {
    interface();
}
