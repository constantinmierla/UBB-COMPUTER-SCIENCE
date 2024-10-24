import java.util.Objects;

public class Student extends Entity<String> implements Comparable<Student>{
    private String nume;
    private float media;

    public Student(String nume, float media) {
        this.nume = nume;
        this.media = media;
        this.id = nume;
    }

    public String getNume() {
        return nume;
    }

    public float getMedia() {
        return media;
    }

    public void setNume(String nume) {
        this.nume = nume;
        this.id = nume;
    }

    @Override
    public void setId(String id){
        this.nume = nume;
        this.id = id;
    }

    public void setMedia(float media) {
        this.media = media;
    }

    @Override
    public String toString() {
        return "Student{" +
                "nume='" + nume + '\'' +
                ", media=" + media +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Student student = (Student) o;
        return Float.compare(media, student.media) == 0 && Objects.equals(nume, student.nume);
    }

    @Override
    public int hashCode() {
        return Objects.hash(nume, media);
    }

    @Override
    public int compareTo(Student o) {
        return nume.compareTo(o.nume);
    }
}
