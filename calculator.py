import tkinter as tk
from math import pow

class SignNode:
    def __init__(self, sign, val=0, left=None, right=None):
        self.sign = sign
        self.val = val
        self.left = left
        self.right = right

    def get_value(self):
        return self.val

    def get_left(self):
        return self.left

    def get_right(self):
        return self.right

    def get_sign(self):
        return self.sign

def solve(node):
    if node.get_sign() == '+':
        return solve(node.get_left()) + solve(node.get_right())
    elif node.get_sign() == '-':
        return solve(node.get_left()) - solve(node.get_right())
    elif node.get_sign() == '*':
        return solve(node.get_left()) * solve(node.get_right())
    elif node.get_sign() == '/':
        return solve(node.get_left()) / solve(node.get_right())
    elif node.get_sign() == '^':
        return pow(solve(node.get_left()), solve(node.get_right()))
    else:
        return node.get_value()

def build_expression_tree(expression):
    expression = '(' + expression + ')'
    priority = {'+': 1, '-': 1, '*': 2, '/': 2, '^': 3}
    operator_stack = []
    operand_stack = []

    i = 0
    while i < len(expression):
        char = expression[i]
        if char == '(':
            operator_stack.append(char)
        elif char.isdigit() or char == '.':
            num = []
            while i < len(expression) and (expression[i].isdigit() or expression[i] == '.'):
                num.append(expression[i])
                i += 1
            operand_stack.append(SignNode(0, float(''.join(num))))
            i -= 1
        elif char in priority:
            while operator_stack and operator_stack[-1] != '(' and priority[operator_stack[-1]] >= priority[char]:
                op = operator_stack.pop()
                right = operand_stack.pop()
                left = operand_stack.pop()
                operand_stack.append(SignNode(op, 0, left, right))
            operator_stack.append(char)
        elif char == ')':
            while operator_stack and operator_stack[-1] != '(':
                op = operator_stack.pop()
                right = operand_stack.pop()
                left = operand_stack.pop()
                operand_stack.append(SignNode(op, 0, left, right))
            operator_stack.pop()
        i += 1

    return operand_stack.pop()

def evaluate_expression(expression):
    tree = build_expression_tree(expression)
    return solve(tree)

class Calculator(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Calculator")
        self.geometry("378x260")
        self.expression = ""

        self.display = tk.Entry(self, font=("Arial", 24), bd=8, relief="ridge", justify="right")
        self.display.grid(row=0, column=0, columnspan=4)

        buttons = [
            '7', '8', '9', '/', 
            '4', '5', '6', '*', 
            '1', '2', '3', '-', 
            '0', '.', '^', '+', 
            '(', ')', 'C', '='
        ]

        row = 1
        col = 0
        for button in buttons:
            action = lambda x=button: self.on_button_click(x)
            tk.Button(self, text=button, width=12, height=2, command=action).grid(row=row, column=col)
            col += 1
            if col > 3:
                col = 0
                row += 1

    def on_button_click(self, button):
        if button == 'C':
            self.expression = ""
        elif button == '=':
            try:
                result = evaluate_expression(self.expression)
                self.expression = str(result)
            except Exception as e:
                self.expression = "Error"
        else:
            self.expression += button
        self.display.delete(0, tk.END)
        self.display.insert(tk.END, self.expression)

if __name__ == "__main__":
    app = Calculator()
    app.mainloop()
