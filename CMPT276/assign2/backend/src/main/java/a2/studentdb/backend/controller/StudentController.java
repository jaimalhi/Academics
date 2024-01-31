package a2.studentdb.backend.controller;

import java.util.Collections;
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.ResponseBody;

import a2.studentdb.backend.model.Student;
import a2.studentdb.backend.model.StudentRepository;
import jakarta.servlet.http.HttpServletResponse;

/**
 * @author Jai Malhi
 * @ResponseBody indicates that the returned object should be serialized
 *               directly to the HTTP response body.
 *               The list of students will be converted to a JSON array.
 */
@Controller
public class StudentController {
    @Autowired
    private StudentRepository stdRepo;

    @GetMapping("/students/view")
    @ResponseBody
    public List<Student> getAllStudents(Model model, HttpServletResponse response) {
        System.out.println("Getting all Students");
        try {
            // get all users from database
            List<Student> stdList = stdRepo.findAll();
            return stdList;
            // model.addAttribute("std", stdList);
            // return "students/showAll";
        } catch (Exception e) {
            System.out.println("Nothing found");
            response.setStatus(404); // 404 = not found
            return Collections.emptyList();
            // return "error";
        }
    }

    @GetMapping("/students/view/{uid}")
    @ResponseBody
    public Student getStudent(@PathVariable String uid, Model model, HttpServletResponse response) {
        System.out.println("Getting Student with id: " + uid);
        int userId = Integer.parseInt(uid);
        try {
            Student student = stdRepo.findByUid(userId);
            return student;
            // model.addAttribute("student", student);
            // return "students/showOne";
        } catch (Exception e) {
            System.out.println("Invalid uid");
            response.setStatus(404); // 404 = not found
            return null;
            // return "error";
        }
    }

    @PostMapping("/students/add") // @RequestBody
    public void addStudent(@RequestBody Student newStudent, HttpServletResponse response) {
        System.out.println("Adding new Student");
        try {
            String newName = newStudent.getName();
            // Capitalize first letter of name
            newName = newName.substring(0, 1).toUpperCase() + newName.substring(1);

            int newAge = newStudent.getAge();
            int newWeight = newStudent.getWeight();
            int newHeight = newStudent.getHeight();
            String newHairColor = newStudent.getHairColor();
            // lowercase the color
            newHairColor = newHairColor.toLowerCase();
            double newGpa = newStudent.getGpa();
            // add new student to student table in DB
            Student newStd = new Student(newName, newAge, newWeight, newHeight, newHairColor, newGpa);
            stdRepo.save(newStd);

            response.setStatus(201); // 201 = created new object
            // return "students/added";
        } catch (Exception e) {
            System.out.println("Invalid input or access failed");
            response.setStatus(401); // 401 = Unauthorized
            // return "error";
        }
    }

    // "/students/update" was used with thymeleaf, not utilzed for svelte frontend
    /*
     * @PostMapping("/students/update")
     * public String showUpdateForm(@RequestParam("uidInput") String uid, Model
     * model, HttpServletResponse response) {
     * System.out.println("Retrieve Student with id: " + uid + " for updating");
     * int userId = Integer.parseInt(uid);
     * try {
     * Student student = stdRepo.findByUid(userId);
     * model.addAttribute("student", student);
     * return "update";
     * } catch (Exception e) {
     * System.out.println("Invalid uid");
     * response.setStatus(404); // 404 = not found
     * return "error";
     * }
     * }
     */

    @PutMapping("/students/update/{uid}")
    public void updateStudent(@PathVariable String uid, @RequestBody Student updatedStudent,
            HttpServletResponse response) {
        System.out.println("Updating student with id: " + uid);
        int userId = Integer.parseInt(uid);
        try {
            Student student = stdRepo.findByUid(userId);
            // Update the fields of the existing student with the new values
            student.setName(updatedStudent.getName());
            student.setAge(updatedStudent.getAge());
            student.setWeight(updatedStudent.getWeight());
            student.setHeight(updatedStudent.getHeight());
            student.setHairColor(updatedStudent.getHairColor());
            student.setGpa(updatedStudent.getGpa());
            // add new student to student table in DB
            stdRepo.save(student);

            response.setStatus(201); // 201 = created new object
            // return "students/updated";
        } catch (Exception e) {
            System.out.println("Invalid uid");
            response.setStatus(400); // 400 = Bad request
            // return "error";
        }
    }

    @DeleteMapping("/students/delete/{uid}")
    public void deleteStudent(@PathVariable String uid, HttpServletResponse response) {
        System.out.println("Deleting Student");
        // a url in address bar of a browser is a GET request.
        // i.e., if we type /students/delete/4 manually, this has to be a GetMapping
        try {
            int userId = Integer.parseInt(uid);
            stdRepo.deleteById(userId);
            response.setStatus(200); // 200 = OK
            // return "students/deleted";
        } catch (Exception e) {
            System.out.println("Invalid uid, cannot delete");
            response.setStatus(400); // 400 = Bad request
            // return "error";
        }
    }
}