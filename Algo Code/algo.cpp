#include<bits/stdc++.h>
using namespace std;

vector<char> operators = {'+', '-', '*', '/', '^'};

// Function to apply an operator on two numbers
double applyOperator(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return (b != 0) ? a / b : 1e9; // Avoid division by zero
        case '^': return pow(a, b);
        default: return 1e9;
    }
}

// Function to evaluate an expression using stacks (handles precedence)
bool evaluateExpression(const string &expr, double &result) {
    stack<double> values;
    stack<char> ops;

    for (size_t i = 0; i < expr.length(); i++) {
        if (isdigit(expr[i])) {
            double num = expr[i] - '0';
            while (i + 1 < expr.length() && isdigit(expr[i + 1])) {
                num = num * 10 + (expr[i + 1] - '0');
                i++;
            }
            values.push(num);
        } else if (expr[i] == '(') {
            ops.push(expr[i]);
        } else if (expr[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOperator(a, b, op));
            }
            ops.pop(); // Remove '('
        } else {
            while (!ops.empty() && ops.top() != '(') {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOperator(a, b, op));
            }
            ops.push(expr[i]);
        }
    }
    while (!ops.empty()) {
        double b = values.top(); values.pop();
        double a = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOperator(a, b, op));
    }
    result = values.top();
    return abs(result - 100) < 1e-6;
}

// Backtracking function to generate expressions with parentheses
bool generateExpressions(string digits, string expr, int index) {
    if (index == 6) {
        double result;
        return evaluateExpression(expr, result);
    }
    
    bool found = false;
    for (char op : operators) {
        string newExpr = expr + op + digits[index];
        if (generateExpressions(digits, newExpr, index + 1)) {
            found = true;
        }
    }
    
    // Also consider concatenation (no operator)
    if (generateExpressions(digits, expr + digits[index], index + 1)) {
        found = true;
    }
    
    return found;
}

// Wrapper function
bool canForm100(string digits) {
    return generateExpressions(digits, string(1, digits[0]), 1);
}

int main() {
    vector<string> cannotForm100;
    
    for (int num=666566;num<=666646;num++){
        string input=to_string(num);
        if(!canForm100(input)) {
            cannotForm100.push_back(input);
        }
    }
    
    cout << "Numbers that cannot form 100: \n";
    for (const string &num : cannotForm100) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}
