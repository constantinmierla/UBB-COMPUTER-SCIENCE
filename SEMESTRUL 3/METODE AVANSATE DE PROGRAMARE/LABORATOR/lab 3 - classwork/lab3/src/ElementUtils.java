import java.util.List;

public class ElementUtils <T>{
    private T element;
    ElementUtils(T obj){this.element = obj;}

    public static <T> T lastEntry(List<T> list) {
        return list.get(list.size()-1);
    }
}
