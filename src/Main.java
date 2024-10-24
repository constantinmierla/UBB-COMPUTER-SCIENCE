import java.util.*;

public class Main {
    public static List<Student> getList(){
        List<Student> l=new ArrayList<Student>();
        l.add(new Student("1",9.7f));
        l.add(new Student("2",7.3f));
        l.add(new Student("3",6f));
        l.add(new Student("4",6.9f));
        l.add(new Student("5",9.5f));
        l.add(new Student("6",9.9f));
        return l;
    }
    public static void main(String[] args) {
        Student s1 = new Student("Dan",  4.5f);
        Student s2 = new Student("Ana",  8.5f);
        Student s3 = new Student("Dan",  4.5f);

        Set<Student> students = new HashSet<>();

        students.add(s1);
        students.add(s2);
        students.add(s3);

        for(Student s : students){
            //System.out.println(s);
        }

        Set<Student> students1 = new TreeSet<>();

        students1.add(s1);
        students1.add(s2);
        students1.add(s3);

        for(Student s : students1){
            //System.out.println(s);
        }

        Set<Student> students2 = new TreeSet<>(new Comparator<Student>() {
            @Override
            public int compare(Student o1, Student o2) {
                return o2.getNume().compareTo(o1.getNume());
            }
        });

        students2.add(s1);
        students2.add(s2);
        students2.add(s3);

        for(Student s : students2){
            //System.out.println(s);
        }

        Map<String, Student> students3 = new HashMap<>(); // new TreeMap<>()

        students3.put(s1.getNume(),s1);
        students3.put(s2.getNume(),s2);
        students3.put(s3.getNume(),s3);

        for(Map.Entry<String, Student> s : students3.entrySet()){
            //System.out.println(s.getKey() + " " + s.getValue().getMedia());
        }

        MyMap map = new MyMap();
        //MyMapComposition map = new MyMapComposition();
        List<Student> studentss = getList();
        for(Student s: studentss){
            map.addStudent(s);
        }
        for(Map.Entry<Integer, List<Student>> o: map.getEntries()){
            System.out.println("Medie= " + o.getKey());
            List<Student> sortedStud = o.getValue();
            Collections.sort(sortedStud);
            for(Student s: sortedStud){
                System.out.println("Student= " + s.getNume());
            }
        }

        Repository<String, Student> repository = new InMemoryRepository<>();
        repository.save(s1);
        repository.save(s2);
        repository.save(s3);

        for(Student s: repository.findAll()){
            System.out.println(s);
        }
    }
}