import java.util.*;

class Solution {
    public List<String> braceExpansionII(String expression) {
        Deque<Set<String>> operands = new ArrayDeque<>();
        Deque<Character> operators = new ArrayDeque<>();

        for (int i = 0; i < expression.length(); i++) {
            char c = expression.charAt(i);

            // Handle implicit concatenation
            if (i > 0) {
                char prev = expression.charAt(i - 1);
                boolean prevCanConcat = Character.isLowerCase(prev) || prev == '}';
                boolean currCanConcat = Character.isLowerCase(c) || c == '{';

                if (prevCanConcat && currCanConcat) {
                    while (!operators.isEmpty() && precedence('*') <= precedence(operators.peek())) {
                        evaluate(operands, operators.pop());
                    }
                    operators.push('*');
                }
            }

            if (Character.isLowerCase(c)) {
                StringBuilder word = new StringBuilder();
                word.append(c);
                while (i + 1 < expression.length() && Character.isLowerCase(expression.charAt(i + 1))) {
                    word.append(expression.charAt(++i));
                }
                Set<String> set = new HashSet<>();
                set.add(word.toString());
                operands.push(set);
            } else if (c == '{') {
                operators.push('{');
            } else if (c == ',') {
                while (!operators.isEmpty() && precedence('+') <= precedence(operators.peek())) {
                    evaluate(operands, operators.pop());
                }
                operators.push('+');
            } else if (c == '}') {
                while (!operators.isEmpty() && operators.peek() != '{') {
                    evaluate(operands, operators.pop());
                }
                operators.pop(); // Pop '{'
            }
        }

        while (!operators.isEmpty()) {
            evaluate(operands, operators.pop());
        }

        List<String> result = new ArrayList<>(operands.pop());
        Collections.sort(result);
        return result;
    }

    private int precedence(char op) {
        if (op == '*') return 2;
        if (op == '+') return 1;
        return 0; // for '{'
    }

    private void evaluate(Deque<Set<String>> operands, char op) {
        Set<String> right = operands.pop();
        Set<String> left = operands.pop();

        if (op == '+') { // Union
            left.addAll(right);
            operands.push(left);
        } else if (op == '*') { // Product (Concatenation)
            Set<String> product = new HashSet<>();
            for (String l : left) {
                for (String r : right) {
                    product.add(l + r);
                }
            }
            operands.push(product);
        }
    }
}