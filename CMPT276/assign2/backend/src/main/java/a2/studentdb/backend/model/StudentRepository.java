package a2.studentdb.backend.model;

import org.springframework.data.jpa.repository.JpaRepository;
import java.util.List;

// allows interface with a table based on certain class
// i.e., JpaRepository translates code into SQL commands
public interface StudentRepository extends JpaRepository<Student, Integer> {
    List<Student> findByName(String name);

    List<Student> findByGpa(double gpa);

    List<Student> findByHeight(int height);

    List<Student> findByWeight(int weight);

    List<Student> findByHairColor(String hairColor);

    Student findByUid(int uid);

}
