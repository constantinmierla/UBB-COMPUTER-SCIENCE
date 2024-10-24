import java.util.*;
import java.util.function.Supplier;
import java.util.stream.Collectors;

public class MyMap extends TreeMap<Integer, List<Student>> {

    public MyMap() {
        super(new Comparator<Integer>() {
            @Override
            public int compare(Integer o1, Integer o2) {
                return o2.compareTo(o1);
            }
        });
    }

    public void addStudent(Student student){
        int grade = Math.round(student.getMedia());
        List<Student> list = super.get(grade);
        if(list == null){
            list = new ArrayList<>();
            super.put(grade, list);
        }
        list.add(student);
    }
    /*
    public Set<Map.Entry<Integer, List<Student>>> getEntries() {
        Comparator<Map.Entry<Integer, List<Student>>> byKeyDesc = (e1, e2) -> e2.getKey().compareTo(e1.getKey());
        Supplier<TreeSet<Map.Entry<Integer, List<Student>>>> sortedSet = () -> new TreeSet<>(byKeyDesc);
        return super.entrySet().stream().collect(Collectors.toCollection(sortedSet));
    }

     */

    public Set<Map.Entry<Integer, List<Student>>> getEntries(){
        return super.entrySet();
    }

}
