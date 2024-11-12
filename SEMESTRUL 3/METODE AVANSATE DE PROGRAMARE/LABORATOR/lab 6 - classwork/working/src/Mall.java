import java.util.Objects;

public class Mall {
    private String name;
    private String manager;
    private Integer year;
    private Double profit;

    public Mall(String name, String manager, Integer year, Double profit) {
        this.name = name;
        this.manager = manager;
        this.year = year;
        this.profit = profit;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getManager() {
        return manager;
    }

    public void setManager(String manager) {
        this.manager = manager;
    }

    public Integer getYear() {
        return year;
    }

    public void setYear(Integer year) {
        this.year = year;
    }

    public Double getProfit() {
        return profit;
    }

    public void setProfit(Double profit) {
        this.profit = profit;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Mall mall = (Mall) o;
        return Objects.equals(name, mall.name) && Objects.equals(manager, mall.manager) && Objects.equals(year, mall.year) && Objects.equals(profit, mall.profit);
    }

    @Override
    public int hashCode() {
        return Objects.hash(name, manager, year, profit);
    }

    @Override
    public String toString() {
        return "Mall{" +
                "name='" + name + '\'' +
                ", manager='" + manager + '\'' +
                ", year=" + year +
                ", profit=" + profit +
                '}';
    }
}
