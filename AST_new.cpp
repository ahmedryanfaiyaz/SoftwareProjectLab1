#include <bits/stdc++.h>

using namespace std;

void program();
void decl_list();
bool decl();
bool var_decl();
void type_spec();
void function_decl();
bool params();
bool params_print();
bool param_list();
bool param_list_print();
bool param();
bool param_print();
bool stmt_list();
bool stmt_list_print();
bool stmt();
bool stmt_print();
bool expr_stmt();
bool expr_stmt_print();
bool while_stmt();
bool while_stmt_print();
bool compound_stmt();
bool compound_stmt_print();
bool local_decls();
bool local_decls_print();
bool local_decl();
bool local_decl_print();
bool if_stmt();
bool if_stmt_print();
bool return_stmt();
bool return_stmt_print();
bool break_stmt();
bool break_stmt_print();
bool expr();
bool expr_print();
bool arglist();
bool args();

//struct node{
//    string data;
//    struct node* parent;
//    vector <struct node*> children;
//};


int i=0;
ifstream ifile;
ofstream ofile;

string untokenedArray[500];
int filled_untokened_upto=0;

string tokenedArray[500];
int filled_tokened_upto=0;

int main()
{
    ifile.open("vau.txt");
    //ofile.open("AST.txt");

    if(ifile.is_open())
    {
        cout << "vau file has been opened" << endl;

        string untokened, tokened;

        while(!ifile.eof())
        {
            ifile >> untokened >> tokened;

            untokenedArray[filled_untokened_upto]=untokened;
            filled_untokened_upto++;

            tokenedArray[filled_tokened_upto]=tokened;
            filled_tokened_upto++;
        }

    }
    else
    {
        cout << "vau file has not opened" << endl;
    }

    if(tokenedArray[i]=="header_file") program();

    return 0;
}


void program()
{
    cout << "program" << endl;
    i++;

    while(true)
    {
        if(tokenedArray[i]=="header_file")
        {
            i++;
        }
        else
        {
            decl_list();
            break;
        }
    }
}


int decl_list_flag=0;
void decl_list()
{
    if(decl_list_flag==0)
    {
        cout << "decl_list" << endl;

        decl_list_flag=1;
    }

    if(decl()==false)
    {
        //decl_list_flag=0;
        return;
    }

    decl_list();
}


bool decl()
{
    if(tokenedArray[i]=="type_spec" && tokenedArray[i+1]=="IDENT" && (tokenedArray[i+2]=="SEMICOLON"||tokenedArray[i+2]=="FIRST_BRACKET_OPEN"))
    {
        if(tokenedArray[i+2]=="SEMICOLON")
        {
            cout << "decl" << endl;
            var_decl();
            i++;
            return true;
        }
        else if(tokenedArray[i+2]=="FIRST_BRACKET_OPEN")
        {
            cout << "decl" << endl;
            i=i+3;
            function_decl();
            return true;
        }
    }
    else
    {
        return false;
    }
}


bool var_decl()
{
    cout << "var_decl" << endl;

    type_spec();

    return true;
}


void type_spec()
{
    cout << "type_spec" << endl << untokenedArray[i] << endl;
    i++;
    cout << "IDENT" << endl << untokenedArray[i] << endl;
    i++;

    return;
}


void function_decl()
{
    int marker=i;

    if(params()==true && compound_stmt()==true)
    {
        cout << "function_decl" << endl;
        i=marker;
        params_print();
        compound_stmt_print();

        return;
    }
    else
    {
        cout << "--Incorrect Compound Statement OR Incorrect Parameter--" << endl;
        return;
    }

}


bool params()
{
    if(tokenedArray[i]=="VOID" && tokenedArray[i+1]=="FIRST_BRACKET_CLOSE")
    {
        i=i+2;
        return true;
    }
    else if(param_list()==false)
    {
        return false;
    }
}


bool params_print()
{
    cout << "params" << endl;
    if(tokenedArray[i]=="VOID" && tokenedArray[i+1]=="FIRST_BRACKET_CLOSE")
    {
        cout << "VOID" << endl;
        i=i+2;
        return true;
    }
    else if(param_list_print()==false)
    {
        return false;
    }
}


bool param_list()
{
    if(param()==true)
    {
        if(tokenedArray[i]=="COMA")
        {
            i++;
            param_list();
        }
        else
        {
            return true;
        }
    }
    else return false;
}


int param_list_flag=0;
bool param_list_print()
{
    if(param_list_flag==0)
    {
        cout << "param_list" << endl;
        param_list_flag=1;
    }

    if(param_print()==true)
    {
        if(tokenedArray[i]=="COMA")
        {
            i++;
            param_list_print();
        }
        else
        {
            param_list_flag=0;
            return true;
        }
    }
    else return false;
}


bool param()
{
    if(tokenedArray[i]=="type_spec" && tokenedArray[i+1]=="IDENT")
    {
        i=i+2;
        return true;
    }
    else
    {
        return false;
    }
}


bool param_print()
{
    if(tokenedArray[i]=="type_spec" && tokenedArray[i+1]=="IDENT")
    {
        cout << "param" << endl;
        type_spec();
        return true;
    }
    else
    {
        return false;
    }
}


bool stmt_list()
{
    if(stmt()==true)
    {
        stmt_list();
    }
    else
    {
        return true;
    }

}


int stmt_list_flag=0;
bool stmt_list_print()
{
    if(stmt_list_flag==0)
    {
        cout << "stmt_list" << endl;
        stmt_list_flag=1;
    }

    if(stmt_print()==false)
    {
        stmt_list_flag=0;
        return true;
    }

    stmt_list_print();

}


bool stmt()
{
    if(expr_stmt()==true)
    {
        return true;
    }
//    else if(compound_stmt()==true)
//    {
//        i=k;
//        return true;
//    }
    else if(if_stmt()==true)
    {
        return true;
    }
    if(while_stmt()==true)
    {
        return true;
    }
    else if(return_stmt()==true)
    {
        return true;
    }
    else if(break_stmt()==true)
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool stmt_print()
{
    if(expr_stmt_print()==true)
    {
        return true;
    }
//    else if(compound_stmt()==true)
//    {
//        cout << "stmt" << endl;
//        return true;
//    }
    else if(if_stmt_print()==true)
    {
        return true;
    }
    else if(while_stmt_print()==true)
    {
        return true;
    }
    else if(return_stmt_print()==true)
    {
        return true;
    }
    else if(break_stmt_print()==true)
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool expr_stmt()
{
    if(tokenedArray[i+1]=="SEMICOLON")
    {
        i++;
        return true;
    }
    else if((tokenedArray[i+6]=="SEMICOLON"||tokenedArray[i+4]=="SEMICOLON") && expr()==true)
    {
        i++;
        return true;
    }
    else
    {
        return false;
    }
}


bool expr_stmt_print()
{
    if(tokenedArray[i+1]=="SEMICOLON")
    {
        cout << "stmt" << endl;
        cout << "expr_stmt" << endl;
        cout << ";" << endl;
        i++;
        return true;
    }
    else if((tokenedArray[i+6]=="SEMICOLON"||tokenedArray[i+4]=="SEMICOLON") && expr_print()==true)
    {
        i++;
        return true;
    }
    else
    {
        return false;
    }
}


bool while_stmt()
{
    if(tokenedArray[i+1]=="WHILE"&&tokenedArray[i+2]=="FIRST_BRACKET_OPEN")
    {
        i=i+2;
        if(expr()==true)
        {
            if(tokenedArray[i+1]=="FIRST_BRACKET_CLOSE")
            {

                i++;
                if(stmt()==true)
                {
                    return true;
                }
            }
        }
    }
    else
    {
        return false;
    }
}

bool while_stmt_print()
{
    if(tokenedArray[i+1]=="WHILE"&&tokenedArray[i+2]=="FIRST_BRACKET_OPEN")
    {
        cout << "stmt" << endl;
        cout << "while_stmt_print" << endl;
        i=i+2;

        if(expr_print()==true)
        {
            if(tokenedArray[i+1]=="FIRST_BRACKET_CLOSE")
            {
                i++;
                if(stmt_print()==true)
                {
                    return true;
                }
            }
        }
    }
    else
    {
        return false;
    }
}

bool compound_stmt()
{

    bool step1 = (tokenedArray[i]=="SECOND_BRACKET_OPEN");
    bool step2 = local_decls();
    bool step3 = stmt_list();
    bool step4 = (tokenedArray[i+1]=="SECOND_BRACKET_CLOSE");

    if(step1 && (step2 || step3) && step4)
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool compound_stmt_print()
{
    int k=i;

    bool step1 = (tokenedArray[i]=="SECOND_BRACKET_OPEN");
    bool step2 = local_decls();
    bool step3 = stmt_list();
    bool step4 = (tokenedArray[i+1]=="SECOND_BRACKET_CLOSE");

    if(step1 && (step2 || step3) && step4)
    {
        i=k;
        if(step2==true)
        {
            local_decls_print();
        }
        if(step3==true)
        {
            stmt_list_print();
        }

        return true;
    }
    else
    {
        return false;
    }
}

int local_decls_flag1=0;
bool local_decls()
{
    if(local_decl()==true)
    {
        local_decls();
        local_decls_flag1=1;
    }
    else
    {
        if(local_decls_flag1==1)
        {
            return true;
            local_decls_flag1=0;
        }
        else
        {
            return false;
        }
    }
}


int local_decls_flag2=0;
bool local_decls_print()
{
    if(local_decls_flag2==0)
    {
        cout << "local_decls" << endl;
        local_decls_flag2=1;
    }

    if(local_decl_print()==false)
    {
        local_decls_flag2=0;
        return true;
    }

    local_decls_print();
}


bool local_decl()
{
    if(tokenedArray[i+1]=="type_spec" && tokenedArray[i+2]=="IDENT" && tokenedArray[i+3]=="SEMICOLON")
    {
        i=i+3;
        return true;
    }
    else
    {
        return false;
    }
}


bool local_decl_print()
{
    if(tokenedArray[i+1]=="type_spec" && tokenedArray[i+2]=="IDENT" && tokenedArray[i+3]=="SEMICOLON")
    {
        cout << "local_decl" << endl;
        i=i+1;
        type_spec();
        return true;
    }
    else
    {
        return false;
    }
}


bool if_stmt()
{
    if(tokenedArray[i+1]=="IF" && tokenedArray[i+2]=="FIRST_BRACKET_OPEN")
    {
        i=i+2;

        if(expr()==true)
        {
            if(tokenedArray[i+1]=="FIRST_BRACKET_CLOSE")
            {
                i++;

                if(stmt()==true)
                {
                    if(tokenedArray[i+1]=="ELSE")
                    {
                        i++;

                        if(stmt()==true)
                        {
                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    }

                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }

        return true;
    }
    else
    {
        return false;
    }
}


bool if_stmt_print()
{
    if(tokenedArray[i+1]=="IF" && tokenedArray[i+2]=="FIRST_BRACKET_OPEN")
    {
        cout << "stmt" << endl;
        cout << "if_stmt" << endl;

        i=i+2;

        if(expr_print()==true)
        {
            if(tokenedArray[i+1]=="FIRST_BRACKET_CLOSE")
            {
                i++;

                if(stmt_print()==true)
                {
                    if(tokenedArray[i+1]=="ELSE")
                    {
                        cout << "else" << endl;

                        i++;

                        if(stmt_print()==true)
                        {
                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    }

                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }

        return true;
    }
    else
    {
        return false;
    }
}


bool return_stmt()
{
    if(tokenedArray[i+1]=="RETURN"&&tokenedArray[i+2]=="SEMICOLON")
    {
        i=i+2;
        return true;
    }
    else if(tokenedArray[i+1]=="RETURN")
    {
        i=i+1;
        if(expr()==true)
        {
            if(tokenedArray[i+1]=="SEMICOLON")
            {
                i=i++;
                return true;
            }
        }
    }
    else
    {
        return false;
    }
}


bool return_stmt_print()
{
    if(tokenedArray[i+1]=="RETURN"&&tokenedArray[i+2]=="SEMICOLON")
    {
        cout << "stmt" << endl;
        cout << "return_stmt-1" << endl;
        i=i+2;
        return true;
    }
    else if(tokenedArray[i+1]=="RETURN")
    {
        i=i+1;
        if(expr()==true)
        {
            if(tokenedArray[i]=="SEMICOLON")
            {
                cout << "stmt" << endl;
                cout << "return_stmt-2" << endl;
                i=i+2;
                return true;
            }
        }
    }
    else
    {
        return false;
    }
}


bool break_stmt()
{
    if(tokenedArray[i+1]=="BREAK" && tokenedArray[i+2]=="SEMICOLON")
    {
        i=i+2;
        return true;
    }
    else
    {
        return false;
    }
}

bool break_stmt_print()
{
    if(tokenedArray[i+1]=="BREAK" && tokenedArray[i+2]=="SEMICOLON")
    {
        cout << "stmt" << endl;
        cout << "break_stmt" << endl;
        i=i+2;
        return true;
    }
    else
    {
        return false;
    }
}


bool expr_print()
{
    if(tokenedArray[i+1]=="IDENT"&&tokenedArray[i+2]=="ASSIGNMENT"&&tokenedArray[i+3]=="IDENT"&&(tokenedArray[i+4]=="ADD"||tokenedArray[i+4]=="SUBTRACT"||tokenedArray[i+4]=="MULTIPLICATION"||tokenedArray[i+4]=="DIVISION")&&tokenedArray[i+5]=="IDENT")
    {
        cout << "stmt" << endl;
        cout << "expr_stmt" << endl;
        cout << "IDENT" << endl << untokenedArray[i+1] << endl;
        cout << "ASSIGNMENT" << endl << "=" << endl;
        cout << "IDENT" << endl << untokenedArray[i+3] << endl;

        if(tokenedArray[i+4]=="ADD")
        {
            cout << "ADD" << endl << "+" << endl;
        }
        if(tokenedArray[i+4]=="SUBTRACT")
        {
            cout << "SUBTRACT" << endl << "-" << endl;
        }
        if(tokenedArray[i+4]=="MULTIPLICATION")
        {
            cout << "MULTIPLICATION" << endl << "*" << endl;
        }
        if(tokenedArray[i+4]=="DIVISION")
        {
            cout << "DIVISION" << endl << "/" << endl;
        }

        cout << "IDENT" << endl << untokenedArray[i+5] << endl;
        i=i+5;
        return true;

    }
    else if(tokenedArray[i+1]=="IDENT"&&tokenedArray[i+2]=="ASSIGNMENT"&&tokenedArray[i+3]=="IDENT")
    {
        cout << "stmt" << endl;
        cout << "expr_stmt" << endl;
        cout << "IDENT" << endl << untokenedArray[i+1] << endl;
        cout << "ASSIGNMENT" << endl << "=" << endl;
        cout << "IDENT" << endl << untokenedArray[i+3] << endl;
        i=i+3;
        return true;
    }
    else if(tokenedArray[i+1]=="IDENT"&&(tokenedArray[i+2]=="EQ"||tokenedArray[i+2]=="NE"||tokenedArray[i+2]=="LESSER"||tokenedArray[i+2]=="GREATER")&&tokenedArray[i+3]=="IDENT")
    {
        cout << "stmt" << endl;
        cout << "expr_stmt" << endl;
        cout << "IDENT" << endl << untokenedArray[i+1] << endl;

        if(tokenedArray[i+2]=="EQ")
        {
            cout << "EQ" << endl << "==" << endl;
        }
        else if(tokenedArray[i+2]=="NE")
        {
            cout << "NE" << endl << "!=" << endl;
        }
        if(tokenedArray[i+2]=="LESSER")
        {
            cout << "LESSER" << endl << "<" << endl;
        }
        if(tokenedArray[i+2]=="GREATER")
        {
            cout << "GREATER" << endl << ">" << endl;
        }

        cout << "IDENT" << endl << untokenedArray[i+3] << endl;
        i=i+3;
        return true;
    }
    else
    {
        return false;
    }
}

bool expr()
{
    if(tokenedArray[i+1]=="IDENT"&&tokenedArray[i+2]=="ASSIGNMENT"&&tokenedArray[i+3]=="IDENT"&&(tokenedArray[i+4]=="ADD"||tokenedArray[i+4]=="SUBTRACT"||tokenedArray[i+4]=="MULTIPLICATION"||tokenedArray[i+4]=="DIVISION")&&tokenedArray[i+5]=="IDENT")
    {
        i=i+5;
        return true;
    }
    else if(tokenedArray[i+1]=="IDENT"&&tokenedArray[i+2]=="ASSIGNMENT"&&tokenedArray[i+3]=="IDENT")
    {
        i=i+3;
        return true;
    }
    else if(tokenedArray[i+1]=="IDENT"&&(tokenedArray[i+2]=="EQ"||tokenedArray[i+2]=="NE"||tokenedArray[i+2]=="LESSER"||tokenedArray[i+2]=="GREATER")&&tokenedArray[i+3]=="IDENT")
    {
        i=i+3;
        return true;
    }
    else
    {
        return false;
    }
//    if(tokenedArray[i]=="IDENT"&&tokenedArray[i+1]=="ASSIGNMENT"&&expr())
//    {
//        cout << "expr" << endl;
//        i=i+2;
//        return true;
//    }
//    else if(expr()==true&&tokenedArray[i]=="OR"&&expr())
//    {
//        cout << "expr" << endl;
//        i=i++;
//        return true;
//    }
//    else if(expr()==true&&tokenedArray[i]=="EQ"&&expr())
//    {
//        cout << "expr" << endl;
//        i=i++;
//        return true;
//    }
//    else if(expr()==true&&tokenedArray[i]=="NE"&&expr())
//    {
//        cout << "expr" << endl;
//        i=i++;
//        return true;
//    }
//    else if(expr()==true&&tokenedArray[i]=="LE"&&expr())
//    {
//        cout << "expr" << endl;
//        i=i++;
//        return true;
//    }
//    else if(expr()==true&&tokenedArray[i]=="LESSER"&&expr())
//    {
//        cout << "expr" << endl;
//        i=i++;
//        return true;
//    }
//    else if(expr()==true&&tokenedArray[i]=="GE"&&expr())
//    {
//        cout << "expr" << endl;
//        i=i++;
//        return true;
//    }
//    else if(expr()==true&&tokenedArray[i]=="GREATER"&&expr())
//    {
//        cout << "expr" << endl;
//        i=i++;
//        return true;
//    }
//    else if(expr()==true&&tokenedArray[i]=="AND"&&expr())
//    {
//        cout << "expr" << endl;
//        i=i++;
//        return true;
//    }
//    if(expr()==true)
//    {
//        if(tokenedArray[i+1]=="ADD")
//        {
//            i++;
//
//            if(expr()==true)
//            {
//                return true;
//            }
//        }
//    }
//    else if(expr()==true&&tokenedArray[i]=="SUBTRACT"&&expr())
//    {
//        cout << "expr" << endl;
//        i=i++;
//        return true;
//    }
//    else if(expr()==true&&tokenedArray[i]=="MULTIPLICATION"&&expr())
//    {
//        cout << "expr" << endl;
//        i=i++;
//        return true;
//    }
//    else if(expr()==true&&tokenedArray[i]=="DIVISION"&&expr())
//    {
//        cout << "expr" << endl;
//        i=i++;
//        return true;
//    }
//    else if(expr()==true&&tokenedArray[i]=="MODULUS"&&expr())
//    {
//        cout << "expr" << endl;
//        i=i++;
//        return true;
//    }
//    else if(tokenedArray[i]=="NOT"&&expr()==true)
//    {
//        cout << "expr" << endl;
//        i=i++;
//        return true;
//    }
//    else if(tokenedArray[i]=="SUBTRACT"&&expr()==true)
//    {
//        cout << "expr" << endl;
//        i=i++;
//        return true;
//    }
//    if(tokenedArray[i]=="ADD"&&expr()==true)
//    {
//        cout << "expr" << endl;
//        i=i++;
//        return true;
//    }
//    else if(tokenedArray[i]=="FIRST_BRACKET_OPEN"&&expr()==true&&tokenedArray[i]=="FIRST_BRACKET_CLOSE")
//    {
//        cout << "expr" << endl;
//        i=i+2;
//        return true;
//    }
//    else if(tokenedArray[i+1]=="IDENT")
//    {
//        i++;
//        return true;
//    }
//    else if(tokenedArray[i]=="IDENT"&&tokenedArray[i]=="FIRST_BRACKET_OPEN"&&args()&&tokenedArray[i]=="FIRST_BRACKET_CLOSE")
//    {
//        cout << "expr" << endl;
//        i=i++;
//        return true;
//    }
//    else if(tokenedArray[i+1]=="BOOL_LITERAL"||tokenedArray[i+1]=="INT_LITERAL"||tokenedArray[i+1]=="FLOAT_LITERAL"||tokenedArray[i+1]=="STRING_LITERAL")
//    {
//        i++;
//        return true;
//    }
//    else
//    {
//        return false;
//    }
}


bool arg_list()
{
    if(expr()==true)
    {
        cout << "arg_list" << endl;
        return true;
    }
    else if(arg_list()==true&&tokenedArray[i]=="COMA"&&expr()==true)
    {
        cout << "arg_list" << endl;
        i++;
        return true;
    }
    else
    {
        return false;
    }
}


bool args()
{
    arg_list();
    return true;
}
