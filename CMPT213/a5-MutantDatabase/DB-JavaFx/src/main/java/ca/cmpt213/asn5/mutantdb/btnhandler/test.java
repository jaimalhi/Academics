package ca.cmpt213.asn5.mutantdb.btnhandler;

import javafx.application.Application;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

public class test extends Application {

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        Button toggle = new Button("Toggle");
        Label status = new Label("Currently: off");
        VBox display = new VBox(10, status, toggle);
        display.setAlignment(Pos.CENTER);
        Scene scene = new Scene(display, 200, 150);
        primaryStage.setScene(scene);
        primaryStage.setTitle("My Tesla");
        primaryStage.show();
    }
}
