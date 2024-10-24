import java.util.*;

public class MyMapComposition{
    private Map<Integer, List<Student>> map;

    public MyMapComposition() {
        this.map = new TreeMap<>(new Comparator<Integer>() {
            @Override
            public int compare(Integer o1, Integer o2) {
                return o2.compareTo(o1);
            }
        });
    }

    public void addStudent(Student student){
        int grade = Math.round(student.getMedia());
        List<Student> list = map.get(grade);
        if(list == null){
            list = new ArrayList<>();
            map.put(grade, list);
        }
        list.add(student);
    }

    public Set<Map.Entry<Integer, List<Student>>> getEntries(){
        return map.entrySet();
    }
}
