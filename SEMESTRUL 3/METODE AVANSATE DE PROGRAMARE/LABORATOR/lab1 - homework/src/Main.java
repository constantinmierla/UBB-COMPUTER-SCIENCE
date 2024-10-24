public class Main {
    public static void main(String[] args) {
        try {
            ExpressionParser parser = new ExpressionParser();
            AbstractExpression expression = parser.parseExpression(args);
            ComplexNumber result = expression.calculate();
            System.out.println("rezultat: " + result);
        } catch (Exception e) {
            System.out.println("eroare: " + e.getMessage());
        }
    }
}
