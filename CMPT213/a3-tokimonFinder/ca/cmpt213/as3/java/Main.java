package ca.cmpt213.as3.java;
import ca.cmpt213.as3.logic.*;
import ca.cmpt213.as3.ui.*;

/**
 * @author Jai Malhi
 * @StudentID 301457742
 * @numToki holds the number of tokimon in grid, default 10
 * @numFoki holds the number of fokimon in grid, default 5
 */
public class Main {
    private static int numOfTokis = 10;
    private static int numOfFokis = 5;
    private static boolean cheatMode = false;

    public static void main(String[] args) {
        parseArgs(args);
        checkTokiFokiLimit();
        //showAttributeValues();
        startGame();
    }

    //start the game
    public static void startGame(){
        gameGrid gg = new gameGrid();
        userInterface ui = new userInterface();
        gridLogic gl = new gridLogic(numOfTokis, numOfFokis);
        //Start UI functions
        ui.startGameUI(gg);
        gl.fillGridCells(gg);
        //if --cheat in arguments
        if(cheatMode){
            System.out.print("\t\tCHEAT GRID ACTIVE");
            gg.displayCheatGrid();
        }
        gg.displayMainGrid();
        //Get initial values for total number of tokis and tokis collected
        int tokiCollected = ui.getTokisCollected();
        int numOfToki = gl.getNumToki();
        //keep game running while player hasn't collected all tokis
        while(tokiCollected != numOfToki){
            ui.playerTurn(gg, gl);
            tokiCollected = ui.getTokisCollected();
            numOfToki = gl.getNumToki();
        }
        System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        System.out.println("Congratulations! You found all the Tokimon!");
        System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        gg.displayCheatGrid();
    }

    //parse individual arguments
    private static void parseArgs(String[] args){
        int numOfArgs = args.length;
        if(numOfArgs == 0){ //0 args
            return; //do nothing
        } else if(numOfArgs == 1){ //1 arg
            checkArgs(args[0]);
        } else if(numOfArgs == 2){ //2 args
            checkArgs(args[0]);
            checkArgs(args[1]);
        } else if(numOfArgs == 3){ //3 args
            checkArgs(args[0]);
            checkArgs(args[1]);
            checkArgs(args[2]);
        } else { //error
            System.out.println("ERROR: Too many arguments given\n");
            System.exit(-1);
        }
    }

    //verify given arguments
    public static void checkArgs(String arg){
        arg = arg.substring(2); //remove --
        if(arg.equals("cheat")){ //cheat
            cheatMode = true;
        } else if(arg.substring(0,7).equals("numFoki")){ //numFoki
            numOfFokis = Integer.parseInt(arg.substring(8)); //get number
        } else if(arg.substring(0,7).equals("numToki")){ //numToki
            numOfTokis = Integer.parseInt(arg.substring(8)); //get number
        } else {
            System.out.println("Invalid arguments, restart and try again");
            System.exit(-1);
        }
    }

    //ensure that the there are not more than 99 tokis and fokis combined
    public static void checkTokiFokiLimit(){
        int sum = numOfFokis + numOfTokis;
        if(sum > 99){
            System.out.println("Error: To many tokimons/fokimons present, retry with new arguments");
            System.exit(-1);
        }
    }

    //debugger function
    public static void showAttributeValues(){
        String cheatValue = (cheatMode ? "True" : "False");
        System.out.println("Cheat: " + cheatValue);
        System.out.println("Tokis: " + numOfTokis);
        System.out.println("Fokis: " + numOfFokis);
    }
}
