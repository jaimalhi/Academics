package ca.cmpt213.asn5.mutantdb;

import ca.cmpt213.asn5.mutantdb.btnhandler.*;
import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane; //col, row
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

public class Main extends Application {
    private VBox outerBox;
    private Label statusLabel = new Label();
    private GridPane showMutants = new GridPane();
    private final GridPane optionsBar = new GridPane();
    private final VBox displayArea = new VBox(10, statusLabel, showMutants);
    ButtonFunc actions;

    @Override
    public void start(Stage primaryStage) {
        startUI(primaryStage);
        //The Scene is 605 wide by 455 high.
        Scene scene = new Scene(outerBox, 605, 455);
        //add style sheet (css)
        scene.getStylesheets().add("file:css/style.css");
        //set minimum stage size
        primaryStage.setMinWidth(650);
        primaryStage.setMinHeight(500);
        //Add the Scene to the Stage.
        primaryStage.setScene(scene);
        //Set the stage title.
        primaryStage.setTitle("Mutant Database");
        //Show the window.
        primaryStage.show();
    }


    //starts the game, for simplification
    private void startUI(Stage primaryStage){
        //col 0: (0,0), (0,1)
        Button getAllMutantsBtn = new Button("Get All Mutants");
        Label numOfMutantsLabel = new Label("# of Mutants: ");
        optionsBar.add(getAllMutantsBtn,0,0);
        optionsBar.add(numOfMutantsLabel,0,1);
        //col 1: (1,0), (1,1)
        Button addMutantBtn = new Button("Add new Mutant");
        Label addMutantLabel = new Label("-Opens new tab-");
        optionsBar.add(addMutantBtn,1,0);
        optionsBar.add(addMutantLabel,1,1);
        //col 2: (2,0), (2,1)
        Button idBtnGet = new Button("Get Mutant of ID:");
        TextField idFieldGet = new TextField();
        idFieldGet.setPrefWidth(idBtnGet.getWidth());
        optionsBar.add(idBtnGet,2,0);
        optionsBar.add(idFieldGet,2,1);
        //col 3; (3,0), (3,1)
        Button idBtnDelete = new Button("Delete Mutant of ID:");
        TextField idFieldDelete = new TextField();
        idFieldDelete.setPrefWidth(idBtnDelete.getWidth());
        optionsBar.add(idBtnDelete,3,0);
        optionsBar.add(idFieldDelete,3,1);
        //optionsBar alignment, spacing, and styling
        optionsBar.getStyleClass().add("optionsBar");
        optionsBar.getStyleClass().add("all-text");
        optionsBar.setAlignment(Pos.CENTER);
        optionsBar.setPadding(new Insets(10));
        optionsBar.setHgap(10);
        optionsBar.setVgap(5);
        //Set up Display area for mutants
        displayArea.getStyleClass().add("displayArea");
        displayArea.setPrefHeight(400);
        displayArea.setAlignment(Pos.TOP_CENTER);
        //statusLabel + showMutants
        statusLabel.getStyleClass().add("all-text");
        showMutants.getStyleClass().add("all-text");
        //add to outerBox
        outerBox = new VBox(optionsBar, displayArea);
        outerBox.setAlignment(Pos.TOP_CENTER);
        outerBox.getStyleClass().add("outerBox");
        showMutants.setAlignment(Pos.CENTER);
        //Button Functionality
        actions = new ButtonFunc(numOfMutantsLabel,getAllMutantsBtn,addMutantBtn,idBtnGet,idFieldGet,idBtnDelete,idFieldDelete);
        buttonFunctionality(primaryStage);
    }

    private void buttonFunctionality(Stage primaryStage){
        actions.getAllMutants(statusLabel, showMutants);
        actions.getMutantById(statusLabel, showMutants);
        actions.addMutant(primaryStage, statusLabel);
        actions.deleteMutantById(statusLabel);
    }

    public static void main(String[] args) {
        launch(args);
    }
}
