public class MultiplyExpression extends AbstractExpression {
    public MultiplyExpression(ComplexNumber[] numbers) {
        super(OperationType.MULTIPLY, numbers);
    }

    @Override
    protected ComplexNumber applyOperation(ComplexNumber a, ComplexNumber b) {
        return a.multiply(b);
    }
}