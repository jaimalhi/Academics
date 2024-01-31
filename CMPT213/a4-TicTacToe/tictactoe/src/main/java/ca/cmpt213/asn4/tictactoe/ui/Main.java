package ca.cmpt213.asn4.tictactoe.ui;

import ca.cmpt213.asn4.tictactoe.game.*;
import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.stage.Stage;

/**
 * @author Jai Malhi
 * @gameBoard class that stores information about game progress/content
 * @pTurn class that allows players to take turns and advance game
 * @gameGrid playable grid area, visual aspect
 * @playBtn clickable button to start a new game
 * @currStatus shows the current status of game including player turn
 * @outerGrid container for all content of game, including gameGrid, playBtn, and currStatus
 */
public class Main extends Application {
    //Custom Classes
    private GameBoard gameBoard = new GameBoard();
    private PlayerTurn pTurn = new PlayerTurn();
    //JavaFX Classes
    private GridPane gameGrid = new GridPane();
    private Button playBtn = new Button("New Game");
    private Label currStatus = new Label("");
    private GridPane outerGrid = new GridPane();

    @Override
    public void start(Stage primaryStage) throws Exception{
        startGame();
        //The Scene is 500px wide by 500 px high.
        Scene scene = new Scene(outerGrid, 500, 500);
        //add style sheet (css)
        scene.getStylesheets().add("file:css/style.css");
        //set minimum stage size
        primaryStage.setMinHeight(450);
        primaryStage.setMinWidth(400);
        //Add the Scene to the Stage.
        primaryStage.setScene(scene);
        //Set the stage title.
        primaryStage.setTitle("TicTacToe");
        //Show the window.
        primaryStage.show();
    }

    //starts the game, for simplification
    private void startGame(){
        //bLogic.displayGameBoard();
        initGridPane();
        pTurn.newGame(gameBoard, outerGrid, playBtn, currStatus);
        pTurn.boardEvents(gameBoard, currStatus);
    }

    //initialize all scene components
    private void initGridPane(){
        //play game button
        playBtn.getStyleClass().add("play-game");
        HBox hbox = new HBox(playBtn);
        hbox.setAlignment(Pos.CENTER);
        //Adjusting and creating game board
        gameGrid.getStyleClass().add("gridpane");
        gameBoard.createGridPane(gameGrid);
        gameGrid.setAlignment(Pos.CENTER);
        gameGrid.setHgap(10);
        gameGrid.setVgap(10);
        gameGrid.setPadding(new Insets(20));
        //adding gameGrid and hbox to outergrid
        outerGrid.add(gameGrid,1,1);
        outerGrid.add(hbox,1,2);
        outerGrid.setVgap(15);
        outerGrid.setAlignment(Pos.CENTER);
    }

    public static void main(String[] args) {
        launch(args);
    }
}