public class Movie {
    private String name;
    private int year;

    public Movie(String name, int year) {
        this.name = name;
        this.year = year;
    }

    @Override
    public String toString() {
        return "Movie : "
                + name + ", year - " +
                 year;
    }
}
