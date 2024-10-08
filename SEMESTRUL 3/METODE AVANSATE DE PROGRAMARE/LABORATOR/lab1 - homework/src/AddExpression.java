public class AddExpression extends AbstractExpression {
    public AddExpression(ComplexNumber[] numbers) {
        super(OperationType.ADD, numbers);
    }

    @Override
    protected ComplexNumber applyOperation(ComplexNumber a, ComplexNumber b) {
        return a.add(b);
    }
}
