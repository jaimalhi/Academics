package a2.studentdb.backend.model;

import jakarta.persistence.*;

/**
 * @author Jai Malhi
 */
@Entity
@Table(name = "students")
public class Student {
    // next 2 lines create a serial datatype for uid, allowing auto-update
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int uid;
    private String name;
    private int age;
    private int weight;
    private int height;
    private String hairColor;
    private double gpa;

    // Constructors
    public Student() {
    }

    public Student(String name, int age, int weight, int height, String hairColor, double gpa) {
        this.name = name;
        this.age = age;
        this.weight = weight;
        this.height = height;
        this.hairColor = hairColor;
        this.gpa = gpa;
    }

    // Getters & Setters
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public int getWeight() {
        return weight;
    }

    public void setWeight(int weight) {
        this.weight = weight;
    }

    public int getHeight() {
        return height;
    }

    public void setHeight(int height) {
        this.height = height;
    }

    public String getHairColor() {
        return hairColor;
    }

    public void setHairColor(String hairColor) {
        this.hairColor = hairColor;
    }

    public double getGpa() {
        return gpa;
    }

    public void setGpa(double gpa) {
        this.gpa = gpa;
    }

    public int getUid() {
        return uid;
    }

    public void setUid(int uid) {
        this.uid = uid;
    }

    @Override
    public String toString() {
        return "Student [uid=" + uid + ", name=" + name + ", age=" + age + ", weight=" + weight + ", height=" + height
                + ", hairColor=" + hairColor + ", gpa=" + gpa + "]";
    }
}
