package ca.cmpt213.as3.ui;

/**
 * @author Jai Malhi
 * responsible for initializing the main grid and cheat grid
 * @gridVertAxis the values for the vertical axis of the grid
 * @rows the number of rows in the grid
 * @cols the number of columns in the grid
 * @mainGrid stores the contents of the main grid visible to player
 * @cheatGrid stores the contents of cheat grid visible during special input
 */
public class gameGrid {
    private final String[] gridVertAxis = {"A","B","C","D","E","F","G","H","I","J"};
    private final int rows = 10;
    private final int cols = 10;
    private String[][] mainGrid;
    private String[][] cheatGrid;

    //constructor
    public gameGrid(){
        initMainGrid();
        initCheatGrid();
    }

    //create playable area from [1][1] to [10][10]
    private void initMainGrid(){
        //using rows+1, cols+1 to add the x-axis, y-axis titles
        this.mainGrid = new String[rows+1][cols+1];
        mainGrid[0][0] = "+"; //empty corner
        //set x-axis titles
        for(int i = 0;i < cols;i++){
            mainGrid[0][i+1] = String.valueOf(i);
        }
        //set y-axis titles
        for(int i = 1;i <= rows;i++){
            mainGrid[i][0] = gridVertAxis[i-1];
        }
        //set main grid content as unknown
        for(int row = 1;row <= rows;row++){
            for(int col = 1;col <= cols;col++){
                mainGrid[row][col] = "~";
            }
        }
    }

    //create cheat version of main grid
    private void initCheatGrid(){
        //using rows+1, cols+1 to add the x-axis, y-axis titles
        this.cheatGrid = new String[rows+1][cols+1];
        cheatGrid[0][0] = "+"; //empty corner
        //set x-axis titles
        for(int i = 0;i < cols;i++){
            cheatGrid[0][i+1] = String.valueOf(i);
        }
        //set y-axis titles
        for(int i = 1;i <= rows;i++){
            cheatGrid[i][0] = gridVertAxis[i-1];
        }
        //set main grid content as unknown
        for(int row = 1;row <= rows;row++){
            for(int col = 1;col <= cols;col++){
                cheatGrid[row][col] = " ";
            }
        }
    }

    //sets a grid location [row][col] to symbol
    public void setMainGridLoc(int row, int col, String symbol){
        mainGrid[row][col] = symbol;
    }
    public void setCheatGridLoc(int row, int col, String symbol){
        cheatGrid[row][col] = symbol;
    }

    //displays main grid
    public void displayMainGrid(){
        for(int row = 0;row <= rows;row++){
            System.out.println();
            for(int col = 0;col <= cols;col++){
                System.out.print(mainGrid[row][col] + "  ");
            }
        }
        System.out.println("\n"); //extra newline
    }

    //displays cheat grid
    public void displayCheatGrid(){
        for(int row = 0;row <= rows;row++){
            System.out.println();
            for(int col = 0;col <= cols;col++){
                System.out.print(cheatGrid[row][col] + "  ");
            }
        }
        System.out.println("\n"); //extra newline
    }

    //getters
    public String getCellCheatGrid(int row, int col) {
        return cheatGrid[row][col];
    }
}
