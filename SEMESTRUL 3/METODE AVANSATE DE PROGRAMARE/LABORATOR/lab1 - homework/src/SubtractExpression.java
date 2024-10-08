public class SubtractExpression extends AbstractExpression {
    public SubtractExpression(ComplexNumber[] numbers) {
        super(OperationType.SUBTRACT, numbers);
    }

    @Override
    protected ComplexNumber applyOperation(ComplexNumber a, ComplexNumber b) {
        return a.subtract(b);
    }
}