public class ExpressionFactory {
    private static ExpressionFactory instance;

    private ExpressionFactory() {}

    public static ExpressionFactory getInstance() {
        if (instance == null) {
            instance = new ExpressionFactory();
        }
        return instance;
    }

    public AbstractExpression createExpression(OperationType operationType, ComplexNumber[] numbers) {
        switch (operationType) {
            case ADD:
                return new AddExpression(numbers);
            case SUBTRACT:
                return new SubtractExpression(numbers);
            case MULTIPLY:
                return new MultiplyExpression(numbers);
            case DIVIDE:
                return new DivideExpression(numbers);
            default:
                throw new UnsupportedOperationException("eroare op.!");
        }
    }
}
