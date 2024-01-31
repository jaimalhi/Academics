package ca.cmpt213.asn5.mutantdb.btnhandler;

import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.shape.Polygon;
import javafx.stage.Modality;
import javafx.stage.Stage;

import java.io.IOException;
import java.io.*;
import java.lang.reflect.Type;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

/**
 * @author Jai Malhi
 * @mutantList holds list of mutants
 * @aMutant holds individual mutants
 * @sCategory used to check category and set colour
 */
public class ButtonFunc {
    //JavaFX Attributes
    private Label numOfMutantsLabel;
    private Button getAllMutantsBtn;
    private Button addMutantBtn;
    private Button getIdBtn;
    private TextField getIdField;
    private Button deleteIdBtn;
    private TextField deleteIdField;
    private Stage subStage = new Stage();
    private Group polyGroup;
    private List<Group> polyGroupList = new ArrayList<>();
    //Java Attributes
    private List<MutantInfo.Mutant> mutantList = new ArrayList<>();
    private MutantInfo.Mutant aMutant;
    String sCategory;

    //constructor
    public ButtonFunc(Label numOfMutantsLabel, Button getAllMutantsBtn, Button addMutantBtn, Button idBtnGet, TextField idFieldGet, Button idBtnDelete, TextField idFieldDelete) {
        this.numOfMutantsLabel = numOfMutantsLabel;
        this.getAllMutantsBtn = getAllMutantsBtn;
        this.addMutantBtn = addMutantBtn;
        this.getIdBtn = idBtnGet;
        this.getIdField = idFieldGet;
        this.deleteIdBtn = idBtnDelete;
        this.deleteIdField = idFieldDelete;
    }

    //shows all mutants to user
    public void getAllMutants(Label statusLabel, GridPane showMutants){
        Gson gson = new Gson();
        getAllMutantsBtn.setOnAction(actionEvent -> {
            showMutants.getChildren().remove(polyGroup);
            try {
                URL url = new URL("http://localhost:8080/api/mutant/all");
                HttpURLConnection connection = (HttpURLConnection) url.openConnection();
                connection.setRequestMethod("GET");
                connection.getInputStream();
                BufferedReader br = new BufferedReader(
                        new InputStreamReader(connection.getInputStream())
                );
                String output = br.readLine(); //value returned by endpoint
                //convert json string to object
                Type collectionType = new TypeToken<Collection<MutantInfo.Mutant>>(){}.getType();
                mutantList = gson.fromJson(output, collectionType);
                numOfMutantsLabel.setText("# of Mutants: " + mutantList.size());

                //status label
                int size = mutantList.size();
                String allNames = "";
                for(int i =0;i < size;i++){
                    allNames += (mutantList.get(i).getName() + ", ");
                }
                allNames = allNames.substring(0, allNames.length()-2);
                statusLabel.setText("Names: " + allNames);

                //displaying mutants
                showMutants.getChildren().remove(polyGroup);
                for(Group g : polyGroupList){
                    showMutants.getChildren().remove(g);
                }
                displayMutants(showMutants);

                System.out.println(mutantList);
                System.out.println(connection.getResponseCode());

                connection.disconnect();
            } catch (IOException e) {
                e.printStackTrace();
            }
        });
    }

    //shows specific mutant to user
    public void getMutantById(Label statusLabel, GridPane showMutants){
        Gson gson = new Gson();
        getIdBtn.setOnAction(actionEvent -> {
            String id = getIdField.getText();
            //status label
            int numId = Integer.parseInt(id);
            if(numId < 0 || numId > mutantList.size()){
                statusLabel.setText("Something went wrong, confirm ID");
            }
            try {
                URL url = new URL("http://localhost:8080/api/mutant/" + id);
                HttpURLConnection connection = (HttpURLConnection) url.openConnection();
                connection.setRequestMethod("GET");
                connection.getInputStream();
                BufferedReader br = new BufferedReader(
                        new InputStreamReader(connection.getInputStream())
                );
                String output = br.readLine(); //value returned by endpoint
                aMutant = gson.fromJson(output, MutantInfo.Mutant.class); //convert json string to object
                //set status label
                statusLabel.setText("Name: " + aMutant.getName());
                sCategory = aMutant.getCategory();


                //displaying mutant
                showMutants.getChildren().remove(polyGroup);
                for(Group g : polyGroupList){
                    showMutants.getChildren().remove(g);
                }
                displayMutant(showMutants);
                //showMutants.getChildren().remove(polyGroup);

                System.out.println(aMutant);
                System.out.println(connection.getResponseCode());

                connection.disconnect();
            }
            catch(IOException e){
                e.printStackTrace();
            }
        });
    }

    //delete specific mutant
    public void deleteMutantById(Label statusLabel){
        deleteIdBtn.setOnAction(actionEvent -> {
            String id = deleteIdField.getText();
            //status label
            int numId = Integer.parseInt(id);
            if(numId < 0 || numId > mutantList.size()){
                statusLabel.setText("Something went wrong, confirm ID");
            }
            try {
                URL url = new URL("http://localhost:8080/api/mutant/" + id);
                HttpURLConnection connection = (HttpURLConnection) url.openConnection();
                connection.setRequestMethod("DELETE");
                connection.getInputStream();
                //set status label
                statusLabel.setText("Deleted Mutant #" + id);

                System.out.println(connection.getResponseCode());

                connection.disconnect();
            }
            catch(IOException e){
                e.printStackTrace();
            }
        });
    }

    //add mutant, go to sub-scene
    public void addMutant(Stage primaryStage, Label statusLabel){
        addMutantBtn.setOnAction(actionEvent -> {
            subStage.setTitle("Add Mutant");
            //associate parent
            try {
                subStage.initModality(Modality.WINDOW_MODAL);
                subStage.initOwner(primaryStage);
            } catch (Exception e){
                System.out.println("Modality only set once");
            }
            //create user options
            GridPane addAttr = new GridPane();
            Button submit = new Button("Submit");
            initAddMutants(addAttr, submit, statusLabel);
            VBox vbox = new VBox(addAttr, submit);
            vbox.setAlignment(Pos.CENTER);
            //The Scene is 300px wide by 200px high.
            Scene subScene = new Scene(vbox,300,200);
            //add style sheet (css)
            subScene.getStylesheets().add("file:css/style.css");
            //set minimum stage size
            subStage.setMinWidth(300);
            subStage.setMinHeight(200);
            //showing subScene
            subStage.setScene(subScene);
            subStage.show();
        });
    }

    //content of add mutant sub-scene, used by initAddMutants()
    private void initAddMutants(GridPane addAttr, Button submit, Label statusLabel){
        double btnWidth = 85;
        //row 0: (0,0), (1,0)
        Label nameLabel = new Label("Name:");
        TextField nameField = new TextField();
        nameLabel.setPrefWidth(btnWidth);
        addAttr.add(nameLabel,0,0);
        addAttr.add(nameField,1,0);
        //row 1: (0,1), (1,1)
        Label categoryLabel = new Label("Category:");
        TextField categoryField = new TextField();
        categoryLabel.setPrefWidth(btnWidth);
        addAttr.add(categoryLabel,0,1);
        addAttr.add(categoryField,1,1);
        //row 2: (0,2), (1,2)
        Label weightLabel = new Label("Weight:");
        TextField weightField = new TextField();
        weightLabel.setPrefWidth(btnWidth);
        addAttr.add(weightLabel,0,2);
        addAttr.add(weightField,1,2);
        //row 3: (0,3), (1,3)
        Label heightLabel= new Label("Height:");
        TextField heightField = new TextField();
        heightLabel.setPrefWidth(btnWidth);
        addAttr.add(heightLabel,0,3);
        addAttr.add(heightField,1,3);
        //row 4: (0,4), (1,4)
        Label abilityLabel = new Label("Ability:");
        TextField abilityField = new TextField();
        abilityLabel.setPrefWidth(btnWidth);
        addAttr.add(abilityLabel,0,4);
        addAttr.add(abilityField,1,4);
        //setup addAttr gridpane
        addAttr.getStyleClass().add("subScene");
        addAttr.setAlignment(Pos.CENTER);
        addAttr.setPadding(new Insets(10));
        addAttr.setHgap(10);
        addAttr.setVgap(5);
        //setup submit button
        submit.getStyleClass().add("subScene");
        submit.setAlignment(Pos.CENTER);
        submitNewMutant(submit, nameField, categoryField, weightField, heightField, abilityField);
        //statusLabel
        statusLabel.setText("Added Mutant");
    }

    //submit button functionality, used by initAddMutants()
    private void submitNewMutant(Button submit,TextField nameField,TextField categoryField,TextField weightField,TextField heightField,TextField abilityField){
        submit.setOnAction(actionEvent -> {
            String newName = nameField.getText();
            String newCategory = categoryField.getText();
            String newWeight = weightField.getText();
            String newHeight = heightField.getText();
            String newAbility = abilityField.getText();
            try {
                URL url = new URL("http://localhost:8080/api/mutant/add");
                HttpURLConnection connection = (HttpURLConnection) url.openConnection();
                connection.setRequestMethod("POST");
                connection.setDoOutput(true);
                connection.setRequestProperty("Content-Type","application/json");

                OutputStreamWriter wr = new OutputStreamWriter(connection.getOutputStream());
                String jsonMutant = "{\"name\":\""+newName+"\",\"category\":\""+newCategory+"\",\"weight\":"+newWeight+",\"height\":"+newHeight+",\"ability\":"+newAbility+"}";
                System.out.println("JSON: " + jsonMutant);
                wr.write(jsonMutant);
                wr.flush();
                wr.close();

                connection.connect();
                System.out.println(connection.getResponseCode());
                connection.disconnect();
                subStage.close();
            }
            catch(Exception e){
                e.printStackTrace();
            }
        });
    }

    //shows all mutants on display area, used by getALlMutants()
    private void displayMutants(GridPane showMutants){
        //iterate through mutant list
        int size = mutantList.size();
        for(int i = 0;i < size;i++){
            //get mutant stats
            sCategory = mutantList.get(i).getCategory();
            double dWeight = mutantList.get(i).getWeight();
            double dHeight = mutantList.get(i).getHeight();
            double dAbility = mutantList.get(i).getAbility();
            //Scene is 605 wide by 455 high
            double points[] = {25.0-(dWeight/3), 50.0,
                    75.0+(dHeight/2), 50.0,
                    125.0, 150.0+(dAbility/2),
            };

            //create a polygon
            Polygon polygon = new Polygon(points);
            polyGroup = new Group(polygon);
            polyGroupList.add(polyGroup);
            showMutants.add(polyGroup, i+1, 1);

            //change fill depending on category
            sCategory = sCategory.toLowerCase();
            if (sCategory.equals("magic")) {
                polygon.setFill(Color.PURPLE);
            } else if (sCategory.equals("fire")) {
                polygon.setFill(Color.RED);
            } else if (sCategory.equals("water")) {
                polygon.setFill(Color.BLUE);
            } else if (sCategory.equals("flight")) {
                polygon.setFill(Color.WHITESMOKE);
            } else if (sCategory.equals("earth")) {
                polygon.setFill(Color.BURLYWOOD);
            } else if (sCategory.equals("telepathy")) {
                polygon.setFill(Color.HOTPINK);
            } else if (sCategory.equals("radiation")) {
                polygon.setFill(Color.GREENYELLOW);
            } else if (sCategory.equals("ice")) {
                polygon.setFill(Color.ALICEBLUE);
            }
        }
    }

    //show mutant on display area, used by getMutantById()
    private void displayMutant(GridPane showMutants){
        //get mutant stats
        double dWeight = aMutant.getWeight(); //150
        double dHeight = aMutant.getHeight(); //60
        double dAbility = aMutant.getAbility(); //55

        //Scene is 605 wide by 455 high.
        double points[] = { 200.0-dWeight,100.0,
                400.0+dHeight,100.0,
                300.0,250.0+dAbility,
                };
        //create a polygon
        Polygon polygon = new Polygon(points);
        polyGroup = new Group(polygon);
        showMutants.add(polyGroup,1,1);

        //change fill depending on category
        sCategory = sCategory.toLowerCase();
        if(sCategory.equals("magic")){
            polygon.setFill(Color.PURPLE);
        } else if(sCategory.equals("fire")){
            polygon.setFill(Color.RED);
        } else if(sCategory.equals("water")){
            polygon.setFill(Color.BLUE);
        } else if(sCategory.equals("flight")){
            polygon.setFill(Color.WHITESMOKE);
        } else if(sCategory.equals("earth")){
            polygon.setFill(Color.BURLYWOOD);
        } else if(sCategory.equals("telepathy")){
            polygon.setFill(Color.HOTPINK);
        } else if(sCategory.equals("radiation")){
            polygon.setFill(Color.GREENYELLOW);
        } else if(sCategory.equals("ice")){
            polygon.setFill(Color.ALICEBLUE);
        }
    }
}
