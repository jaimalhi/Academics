package a2.studentdb.backend;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class Assign2Application {

    public static void main(String[] args) {
        SpringApplication.run(Assign2Application.class, args);
    }

}

/*
 * The Spring app should have the following features (I would suggest making a
 * separate endpoint for each):
 * - ability to add new Students (with corresponding attributes) -> POST
 * - ability to change attributes of any of the Students. -> PUT
 * - ability to delete any of the Students -> DELETE
 * - ability to display (draw) all Students currently in the database -> GET
 */
