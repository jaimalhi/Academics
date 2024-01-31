package ca.cmpt213.asn4.tictactoe.game;

import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.GridPane;

/**
 * @author Jai Malhi
 * @rows the number of rows in the game board
 * @cols the number of columns in the game board
 * @gameBoard the Board used to store user locations and moves
 * @boardCell the Board used to hold all images within the board
 */
public class GameBoard {
    private final Image boardBG = new Image("file:images/boardBG.png");
    private final int cols = 4;
    private final int rows = 4;
    private String[][] gameBoard;
    public ImageView[][] boardCell;

    //constructor
    public GameBoard(){
        initGameBoard();
        initBoardCell();
    }

    //create empty game board, [0][0] to [3][3]
    private void initGameBoard(){
        this.gameBoard = new String[cols][rows];
        //set main grid content as unknown
        for(int col = 0;col < cols;col++){
            for(int row = 0;row < rows;row++){
                gameBoard[col][row] = "";
            }
        }
    }

    //fill boardCell with images, [0][0] to [3][3]
    private void initBoardCell(){
        this.boardCell = new ImageView[cols][rows];
        //set main grid content as unknown
        for(int col = 0;col < cols;col++){
            for(int row = 0;row < rows;row++){
                ImageView viewBG = new ImageView(boardBG);
                boardCell[col][row] = viewBG;
            }
        }
    }

    //puts content of boardCell into a gridpane
    public void createGridPane(GridPane gp){
        for(int col = 0;col < cols;col++){
            for(int row = 0;row < rows;row++){
                gp.add(boardCell[col][row], col, row);
            }
        }
    }

    //sets a grid location [row][col] to X or O
    public void setGameBoardLoc(int col, int row, String symbol){
        if(row >= 4 || col >= 4){
            System.out.println("Invalid row or column input, try again!");
            System.exit(-1);
        }
        gameBoard[col][row] = symbol;
    }

    //sets a grid location [row][col] to X or O
    public void setBoardCellLoc(int col, int row, Image symbol){
        if(row >= 4 || col >= 4){
            System.out.println("Invalid row or column input, try again!");
            System.exit(-1);
        }
        boardCell[col][row].setImage(symbol);
    }

    //reset board for new games
    public void resetBoardCells(){
        for(int col = 0;col < cols;col++){
            for(int row = 0;row < rows;row++){
                setBoardCellLoc(col, row, boardBG);
                boardCell[col][row].setDisable(false); //allow all buttons to be pressed
            }
        }
    }

    //reset board for new games
    public void resetGameBoard(){
        //new function call for readability
        initGameBoard();
    }

    //disables all clickable cells after a win
    public void disableAllCells(){
        for(int col = 0;col < cols;col++){
            for(int row = 0;row < rows;row++){
                boardCell[col][row].setDisable(true);
            }
        }
    }

    //check if gameboard full (draw)
    public boolean checkForDraw(){
        for(int col = 0;col < cols;col++){
            for(int row = 0;row < rows;row++){
                String cell = gameBoard[col][row];
                if(cell.equals("")){
                    return false;
                }
            }
        }
        return true;
    }

    //getters
    public int getCols(){
        return cols;
    }
    public int getRows() {
        return rows;
    }
    public String getGameBoardCell(int col, int row){
        return gameBoard[col][row];
    }

    //!displays Board on console, for debugging
    public void displayGameBoard(){
        System.out.print("\n================");
        for(int col = 0;col < cols;col++){
            System.out.println();
            for(int row = 0;row < rows;row++){
                System.out.print("[" + gameBoard[col][row] + "] ");
            }
        }
        System.out.println("\n================");
    }
}
