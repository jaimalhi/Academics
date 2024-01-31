package ca.cmpt213.as3.logic;
import ca.cmpt213.as3.ui.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/**
 * @author Jai Malhi
 * Responsible for filling creating tokimon and fokimon
 * locations on the grid
 * @numToki the number of tokis on the grid
 * @numFoki the number of fokis on the grid
 * @tokiList stores the coords. for each tokimon
 * @fokiList stores the coords. for each fokimon
 */
public class gridLogic {
    /**
     * Class used to store all tokimon and fokimon locations
     * @row the row at which the toki/foki is located
     * @col the col at which the toki/foki is located
     */
    public class gridLocation {
        private final int row;
        private final int col;
        public gridLocation(int row, int col){
            this.row = row;
            this.col = col;
        }
        public int getRow(){ return row; }
        public int getCol(){ return col; }
    }
    private final int numToki;
    private final int numFoki;
    public List<gridLocation> tokiList = new ArrayList<>();
    public List<gridLocation> fokiList = new ArrayList<>();

    //Constructor
    public gridLogic(int numToki, int numFoki){
        this.numToki = numToki;
        this.numFoki = numFoki;
    }

    //helper function to place tokis and fokis
    public void fillGridCells(gameGrid gg){
        createTokiLocations(gg);
        //allTokiFokiLocations(); //Used for debugging
    }

    private void createTokiLocations(gameGrid gg){
        Random rand = new Random();
        //create toki locations
        for(int i = 0;i < numToki;i++){
            //rand from 0-9
            int row = rand.nextInt(10)+1;
            int col = rand.nextInt(10)+1;
            //confirm toki doesn't already exist at location
            boolean cellEmpty = false;
            while(!cellEmpty){
                String checkCell = gg.getCellCheatGrid(row, col);
                if(checkCell.equals(" ")){ //cell empty
                    gridLocation newLoc = new gridLocation(row, col);
                    tokiList.add(newLoc);
                    gg.setCheatGridLoc(row, col, "$"); //toki at cell
                    cellEmpty = true;
                }
                row = rand.nextInt(10)+1;
                col = rand.nextInt(10)+1;
            }
        }
        //create foki locations
        for(int i = 0;i < numFoki;i++){
            //rand from 0-9
            int row = rand.nextInt(10)+1;
            int col = rand.nextInt(10)+1;
            //confirm toki doesn't already exist at location
            boolean cellEmpty = false;
            while(!cellEmpty){
                String checkCell = gg.getCellCheatGrid(row, col);
                if(checkCell.equals(" ")){ //cell empty
                    gridLocation newLoc = new gridLocation(row, col);
                    fokiList.add(newLoc);
                    gg.setCheatGridLoc(row, col, "X"); //foki at cell
                    cellEmpty = true;
                }
                row = rand.nextInt(10)+1;
                col = rand.nextInt(10)+1;
            }
        }
    }

    //getters
    public int getNumToki(){ return numToki; }

    //debugger function
    private void allTokiFokiLocations(){
        for(gridLocation gl : tokiList){
            System.out.println("===============");
            System.out.println("Row: " + gl.getRow());
            System.out.println("Col: " + gl.getCol());
        }
        System.out.println("\n\n");
        for(gridLocation gl : fokiList){
            System.out.println("===============");
            System.out.println("Row: " + gl.getRow());
            System.out.println("Col: " + gl.getCol());
        }
    }
}