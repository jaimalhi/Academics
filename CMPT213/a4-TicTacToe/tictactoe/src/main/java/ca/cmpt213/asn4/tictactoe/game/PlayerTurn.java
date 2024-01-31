package ca.cmpt213.asn4.tictactoe.game;

import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;

/**
 * @author Jai Malhi
 * @boardX the image for X on the board
 * @boardO the image for O on the board
 * @boardBG the base image for the board
 * @playerTurn which players turn it is, by default player X turn
 */
public class PlayerTurn {
    final Image boardX = new Image("file:images/boardX.png");
    final Image boardO = new Image("file:images/boardO.png");
    final Image boardBG = new Image("file:images/boardBG.png");
    int playerTurn = 0;

    //what happens after pressing 'New Game' button
    public void newGame(GameBoard bg, GridPane outerGrid, Button playBtn, Label status){
        status.getStyleClass().add("all-text");
        playBtn.setOnAction(actionEvent -> {
            status.setText("Game On! X starts");
            bg.resetBoardCells();
            bg.resetGameBoard();
            playerTurn = 0;
        });
        HBox hbox = new HBox(status);
        hbox.setAlignment(Pos.CENTER);
        outerGrid.add(hbox, 1, 0);
    }

    //create click events for all grid cells
    public void boardEvents(GameBoard gb, Label status){
        int rows = gb.getRows();
        int cols = gb.getCols();
        for(int col = 0;col < cols;col++){
            for(int row = 0;row < rows;row++){
                ImageView IView = gb.boardCell[col][row];
                int currCol = col;
                int currRow = row;
                IView.addEventHandler(MouseEvent.MOUSE_CLICKED, mEvent -> {
                    onCellClick(gb, IView, status, currCol, currRow);
                });
            }
        }
    }

    //setting grid cell to X or O
    private void onCellClick(GameBoard gb, ImageView IView, Label status, int col, int row){
        if(playerTurn % 2 == 0) { //player X turn
            status.setText("Player O"); //show next player turn
            playerTurn++; //change player turn
            gb.setBoardCellLoc(col, row, boardX);
            IView.setDisable(true); //allow button press once
            gb.setGameBoardLoc(row, col, "X"); //set gameBoard content
            checkPlayerWin(gb, status); //Check if player won
        } else { //player O turn
            status.setText("Player X"); //show next player turn
            playerTurn++; //change player turn
            gb.setBoardCellLoc(col, row, boardO);
            IView.setDisable(true); //allow button press once
            gb.setGameBoardLoc(row, col, "O"); //set gameBoard content
            checkPlayerWin(gb, status); //Check if player won
        }
    }

    //check if any player has won the game
    private void checkPlayerWin(GameBoard gb, Label status){
        if(gb.checkForDraw()){
            status.setText("Draw!");
            gb.disableAllCells();
        }
        String winX = "XXXX", winO = "OOOO";
        //10 different ways a player can win: 4 horizontal, 4 vertical, 2 diagonal
        for(int i = 0;i < 10;i++){
            String line = switch (i) {
                //check rows
                case 0 ->
                        gb.getGameBoardCell(0, 0) + gb.getGameBoardCell(1, 0) + gb.getGameBoardCell(2, 0) + gb.getGameBoardCell(3, 0);
                case 1 ->
                        gb.getGameBoardCell(0, 1) + gb.getGameBoardCell(1, 1) + gb.getGameBoardCell(2, 1) + gb.getGameBoardCell(3, 1);
                case 2 ->
                        gb.getGameBoardCell(0, 2) + gb.getGameBoardCell(1, 2) + gb.getGameBoardCell(2, 2) + gb.getGameBoardCell(3, 2);
                case 3 ->
                        gb.getGameBoardCell(0, 3) + gb.getGameBoardCell(1, 3) + gb.getGameBoardCell(2, 3) + gb.getGameBoardCell(3, 3);
                //check columns
                case 4 ->
                        gb.getGameBoardCell(0, 0) + gb.getGameBoardCell(0, 1) + gb.getGameBoardCell(0, 2) + gb.getGameBoardCell(0, 3);
                case 5 ->
                        gb.getGameBoardCell(1, 0) + gb.getGameBoardCell(1, 1) + gb.getGameBoardCell(1, 2) + gb.getGameBoardCell(1, 3);
                case 6 ->
                        gb.getGameBoardCell(2, 0) + gb.getGameBoardCell(2, 1) + gb.getGameBoardCell(2, 2) + gb.getGameBoardCell(2, 3);
                case 7 ->
                        gb.getGameBoardCell(3, 0) + gb.getGameBoardCell(3, 1) + gb.getGameBoardCell(3, 2) + gb.getGameBoardCell(3, 3);
                //check diagonals
                case 8 ->
                        gb.getGameBoardCell(0, 0) + gb.getGameBoardCell(1, 1) + gb.getGameBoardCell(2, 2) + gb.getGameBoardCell(3, 3);
                case 9 ->
                        gb.getGameBoardCell(0, 3) + gb.getGameBoardCell(1, 2) + gb.getGameBoardCell(2, 1) + gb.getGameBoardCell(3, 0);
                default -> "";
            };
            if(line.equals(winX)){ //player X wins
                status.setText("Player X Wins!");
                gb.disableAllCells();
            } else if(line.equals(winO)){ //player O wins
                status.setText("Player O Wins!");
                gb.disableAllCells();
            }
        }
    }
}
