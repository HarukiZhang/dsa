#include<iostream>

using namespace std;

bool evalExpr();
bool evalFact();

int main() {
    int counter = 1;
    char input = cin.peek();
    while (input != EOF){
        bool res = evalExpr();
        if (res)
            cout << "Expression " << counter << ": V\n" << flush;
        else
            cout << "Expression " << counter << ": F\n" << flush;
        
        ++counter;
        input = cin.peek();
    }
}

bool evalExpr(){
    bool val_expr = evalFact(), val_expr_nxt;
    cin >> ws;
    char input = cin.peek();
    while (!(input == EOF || input == '\r' || input == '\n')){
        switch (input) {
        case '&':
            cin >> input;
            val_expr_nxt = evalFact();
            val_expr = val_expr && val_expr_nxt;
            break;
        case '|':
            cin >> input;
            val_expr_nxt = evalFact();
            val_expr = val_expr || val_expr_nxt;
            break;
        default :// such as the peek return a ')';
            return val_expr;
        }

        cin >> ws;
        input = cin.peek();
    }
    return val_expr;
}

bool evalFact(){
    cin >> ws;
    char input = cin.peek();
    switch (input) {
    case '!':
        cin >> input >> ws;
        return !evalFact();
    case '(':
        cin >> input >> ws;
        bool val_fact;
        val_fact = evalExpr();
        cin >> ws >> input;
        // This above line input should be ')';
        return val_fact;
    case 'V':
        cin >> input;
        return true;
    case 'F':
        cin >> input;
        return false;
    default :
        return false;
    }
}

/*描述
The objective of the program you are going to produce is to evaluate boolean expressions 
as the one shown next:
Expression: ( V | V ) & F & ( F | V )

where V is for True, and F is for False. 
The expressions may include the following operators: 
    ! for not , 
    & for and, 
    | for or , 
    the use of parenthesis for operations grouping is also allowed.

To perform the evaluation of an expression, 
it will be considered the priority of the operators, 
    the not having the highest, 
    and the or the lowest. 
The program must yield V or F , as the result for each expression in the input file.

输入
The expressions are of a variable length, although will never exceed 100 symbols. 
Symbols may be separated by any number of spaces or no spaces at all, 
therefore, the total length of an expression, as a number of characters, is unknown.

The number of expressions in the input file is variable and will never be greater than 20. 
Each expression is presented in a new line, as shown below.

输出
For each test expression, print "Expression " followed by its sequence number, ": ", 
and the resulting value of the corresponding test expression. 
Separate the output for consecutive test expressions with a new line.

Use the same format as that shown in the sample output shown below.

样例输入
( V | V ) & F & ( F| V)
!V | V & V & !F & (F | V ) & (!F | F | !V & V)
(F&F|V|!V&!F&!(F|F&V))

样例输出
Expression 1: F
Expression 2: V
Expression 3: V
*/