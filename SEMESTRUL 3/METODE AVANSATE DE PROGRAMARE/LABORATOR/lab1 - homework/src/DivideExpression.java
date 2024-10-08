public class DivideExpression extends AbstractExpression {
    public DivideExpression(ComplexNumber[] numbers) {
        super(OperationType.DIVIDE, numbers);
    }

    @Override
    protected ComplexNumber applyOperation(ComplexNumber a, ComplexNumber b) {
        return a.divide(b);
    }
}