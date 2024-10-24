public class ComplexNumber {
    private double realPart;
    private double imaginaryPart;

    public ComplexNumber(double realPart, double imaginaryPart) {
        this.realPart = realPart;
        this.imaginaryPart = imaginaryPart;
    }

    public double getRealPart() {
        return realPart;
    }

    public double getImaginaryPart() {
        return imaginaryPart;
    }

    public ComplexNumber add(ComplexNumber other) {
        return new ComplexNumber(this.realPart + other.realPart, this.imaginaryPart + other.imaginaryPart);
    }

    public ComplexNumber subtract(ComplexNumber other) {
        return new ComplexNumber(this.realPart - other.realPart, this.imaginaryPart - other.imaginaryPart);
    }

    public ComplexNumber multiply(ComplexNumber other) {
        double real = this.realPart * other.realPart - this.imaginaryPart * other.imaginaryPart;
        double imaginary = this.realPart * other.imaginaryPart + this.imaginaryPart * other.realPart;
        return new ComplexNumber(real, imaginary);
    }

    public ComplexNumber divide(ComplexNumber other) {
        double denominator = other.realPart * other.realPart + other.imaginaryPart * other.imaginaryPart;
        double real = (this.realPart * other.realPart + this.imaginaryPart * other.imaginaryPart) / denominator;
        double imaginary = (this.imaginaryPart * other.realPart - this.realPart * other.imaginaryPart) / denominator;
        return new ComplexNumber(real, imaginary);
    }

    @Override
    public String toString() {
        if (imaginaryPart < 0) {
            return realPart + " - " + Math.abs(imaginaryPart) + "i";
        } else {
            return realPart + " + " + imaginaryPart + "i";
        }
    }
}
