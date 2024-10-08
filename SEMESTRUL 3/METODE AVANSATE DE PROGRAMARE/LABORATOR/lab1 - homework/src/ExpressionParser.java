public class ExpressionParser {
    public AbstractExpression parseExpression(String[] args) {
        OperationType operationType = parseOperation(args[1]);
        ComplexNumber[] numbers = extractComplexNumbers(args);
        return ExpressionFactory.getInstance().createExpression(operationType, numbers);
    }

    private OperationType parseOperation(String operator) {
        switch (operator.trim()) {
            case "+":
                return OperationType.ADD;
            case "-":
                return OperationType.SUBTRACT;
            case "*":
                return OperationType.MULTIPLY;
            case "/":
                return OperationType.DIVIDE;
            default:
                throw new IllegalArgumentException("Operator invalid: " + operator);
        }
    }

    private ComplexNumber[] extractComplexNumbers(String[] args) {
        int count = (args.length + 1) / 2;
        ComplexNumber[] numbers = new ComplexNumber[count];
        for (int i = 0; i < count; i++) {
            numbers[i] = parseSingleComplex(args[i * 2]);
        }
        return numbers;
    }

    private ComplexNumber parseSingleComplex(String str) {
        str = str.replace(" ", "");
        String[] parts = str.split("[+-]", 2);
        double re = Double.parseDouble(parts[0]);
        double im = Double.parseDouble(parts[1].replace("i", ""));
        return new ComplexNumber(re, im);
    }
}
