import java.util.*;
 class SPCC_Exp_5 {

    // Operator precedence
    static Map<Character, Integer> precedence = new HashMap<>();

    static {
        precedence.put('(', 5);
        precedence.put('*', 4);
        precedence.put('/', 3);
        precedence.put('+', 2);
        precedence.put('-', 1);
        precedence.put('$', 0);
    }

    static boolean isVariable(char ch) {
        return Character.isLetter(ch);
    }

    static boolean isOperator(char ch) {
        return precedence.containsKey(ch);
    }

    // Convert infix to postfix
    static String toPostfix(String expression) {

        Stack<Character> stack = new Stack<>();
        stack.push('$');

        StringBuilder postfix = new StringBuilder();

        for (int i = 0; i < expression.length(); i++) {

            char ch = expression.charAt(i);

            if (ch == '(') {
                stack.push(ch);
            }

            else if (ch == ')') {
                while (stack.peek() != '(') {
                    postfix.append(stack.pop());
                }
                stack.pop(); // remove '('
            }

            else if (isVariable(ch)) {
                postfix.append(ch);
            }

            else { // operator
                while (stack.size() > 1 &&
                        stack.peek() != '(' &&
                        precedence.get(stack.peek()) >= precedence.get(ch)) {

                    postfix.append(stack.pop());
                }
                stack.push(ch);
            }
        }

        while (stack.size() > 1) {
            postfix.append(stack.pop());
        }

        return postfix.toString();
    }

    // Generate Three Address Code
    static void generateTAC(String expression) {

        char tempVar = 'A';
        StringBuilder newInput = new StringBuilder();

        int i = 0;

        // Handle unary minus
        while (i < expression.length()) {

            if (i == 0 &&
                    expression.charAt(i) == '-' &&
                    i + 1 < expression.length() &&
                    isVariable(expression.charAt(i + 1))) {

                System.out.println(tempVar + " = -" + expression.charAt(i + 1));
                newInput.append(tempVar);
                tempVar++;
                i += 2;
            }

            else if (i + 2 < expression.length() &&
                    isOperator(expression.charAt(i)) &&
                    expression.charAt(i + 1) == '-' &&
                    isVariable(expression.charAt(i + 2))) {

                System.out.println(tempVar + " = -" + expression.charAt(i + 2));
                newInput.append(expression.charAt(i));
                newInput.append(tempVar);
                tempVar++;
                i += 3;
            }

            else {
                newInput.append(expression.charAt(i));
                i++;
            }
        }

        String postfix = toPostfix(newInput.toString());

        Stack<Character> stack = new Stack<>();

        for (int j = 0; j < postfix.length(); j++) {

            char ch = postfix.charAt(j);

            if (isVariable(ch)) {
                stack.push(ch);
            }

            else { // operator

                char operand2 = stack.pop();
                char operand1 = stack.pop();

                System.out.println(tempVar + " = " +
                        operand1 + " " + ch + " " + operand2);

                stack.push(tempVar);
                tempVar++;
            }
        }

        if (!stack.isEmpty()) {
            System.out.println("Result = " + stack.peek());
        }
    }

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        System.out.print("Enter the expression: ");
        String expression = sc.nextLine();

        generateTAC(expression);

        sc.close();
    }
}