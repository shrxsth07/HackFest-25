const operators = ['+', '-', '*', '/', '^'];

// Function to apply an operator on two numbers
function applyOperator(a, b, op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return (b !== 0) ? a / b : 1e9; // Avoid division by zero
        case '^': return Math.pow(a, b);
        default: return 1e9;
    }
}

// Function to evaluate an expression using stacks (handles precedence)
function evaluateExpression(expr) {
    let values = [];
    let ops = [];

    for (let i = 0; i < expr.length; i++) {
        if (!isNaN(expr[i])) {
            let num = parseInt(expr[i], 10);
            while (i + 1 < expr.length && !isNaN(expr[i + 1])) {
                num = num * 10 + parseInt(expr[i + 1], 10);
                i++;
            }
            values.push(num);
        } else if (expr[i] === '(') {
            ops.push(expr[i]);
        } else if (expr[i] === ')') {
            while (ops.length && ops[ops.length - 1] !== '(') {
                let b = values.pop();
                let a = values.pop();
                let op = ops.pop();
                values.push(applyOperator(a, b, op));
            }
            ops.pop(); // Remove '('
        } else {
            while (ops.length && ops[ops.length - 1] !== '(') {
                let b = values.pop();
                let a = values.pop();
                let op = ops.pop();
                values.push(applyOperator(a, b, op));
            }
            ops.push(expr[i]);
        }
    }
    while (ops.length) {
        let b = values.pop();
        let a = values.pop();
        let op = ops.pop();
        values.push(applyOperator(a, b, op));
    }
    return Math.abs(values[0] - 100) < 1e-6;
}

// Backtracking function to generate expressions with parentheses
function generateExpressions(digits, expr, index) {
    if (index === 6) {
        return evaluateExpression(expr);
    }
    
    let found = false;
    for (let op of operators) {
        let newExpr = expr + op + digits[index];
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
function canForm100(digits) {
    return generateExpressions(digits, digits[0], 1);
}

function main() {
    let cannotForm100 = [];
    
    for (let num = 757829; num <=757829; num++) {
        let input = num.toString();
        if (!canForm100(input)) {
            cannotForm100.push(input);
        }
    }
    
    console.log("Numbers that cannot form 100:");
    console.log(cannotForm100.join(" "));
}

main();
