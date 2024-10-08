public abstract class AbstractExpression {
    protected OperationType operationType;
    protected ComplexNumber[] numbers;

    public AbstractExpression(OperationType operationType, ComplexNumber[] numbers) {
        this.operationType = operationType;
        this.numbers = numbers;
    }

    public ComplexNumber calculate() {
        ComplexNumber result = numbers[0];
        for (int i = 1; i < numbers.length; i++) {
            result = applyOperation(result, numbers[i]);
        }
        return result;
    }

    protected abstract ComplexNumber applyOperation(ComplexNumber a, ComplexNumber b);
}
