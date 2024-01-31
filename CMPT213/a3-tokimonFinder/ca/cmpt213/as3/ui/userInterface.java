package ca.cmpt213.as3.ui;
import ca.cmpt213.as3.logic.*;
import java.util.Random;
import java.util.Scanner;

/**
 * @author Jai Malhi
 * Responsible for the majority of game functionality and game UI
 * @numOfSpells the number of spells uses available to the player
 * @tokisCollected the number of tokis the player collects throughout the game
 * @userPos the string input of the desired user input from player
 * @playerRow the row in which the player is currently in
 * @playerCol the column in which the player is currently in
 */
public class userInterface implements spellOptions {
    private int numOfSpells = 3;
    private int tokisCollected = 0;
    private String userPos;
    private int playerRow;
    private int playerCol;

    //start the game UI
    public void startGameUI(gameGrid gg){
        System.out.println("==========================");
        System.out.println("Welcome to Tokimon Finder!");
        System.out.println("==========================");
        gameIntructions();
        gg.displayMainGrid();
        getInitialPos();
        setUserPos(gg);
    }

    //controls each player turn
    public void playerTurn(gameGrid gg, gridLogic gl){
        //offer player to use spells or move normally
        Scanner input = new Scanner(System.in);
        System.out.println("Would you like to:");
        System.out.println("1. Move up, down, left, or right");
        System.out.println("2. Use a spell");
        System.out.println("3. Quit Game");
        //get user movement choice
        boolean validInput = false;
        String turnChoice;
        while(!validInput){
            System.out.print("What would you like to do: ");
            try{
                turnChoice = input.nextLine();
                switch(turnChoice){
                    case "1" -> {
                        System.out.println("==========================");
                        playerMovement(gg);
                        checkUserPos(gg);
                        gg.displayMainGrid();
                        showUserInfo(gl);
                        validInput = true;
                    }
                    case "2" -> {
                        System.out.println("==========================");
                        if(numOfSpells > 0){
                            numOfSpells--;
                            userSpellChoice(gg, gl);
                            checkUserPos(gg);
                            gg.displayMainGrid();
                            showUserInfo(gl);
                            validInput = true;
                        } else {
                            System.out.println("No spells left to use!");
                        }
                    }
                    case "3" -> {
                        System.out.println("========================");
                        System.out.println("Thank you for playing!");
                        System.out.println("========================");
                        System.exit(0);
                    }
                    default -> System.out.println("Invalid Input! try again");
                }
            } catch (Exception e){
                System.out.println("Invalid Input! try again");
            }
        }
    }

    //user choosing starting position
    private void getInitialPos(){
        Scanner input = new Scanner(System.in);
        //validate input for initial position
        boolean validInput = false;
        String posChoice = "";
        while(!validInput){
            System.out.print("Choose initial position (A0-J9): ");
            try{
                posChoice = input.nextLine();
                posChoice = posChoice.toUpperCase();
                //invalid grid location
                if(posChoice.length() > 2 || posChoice.length() < 1){
                    System.out.println("Invalid Input! try again");
                    continue;
                }
                //invalid y-axis
                switch (posChoice.charAt(0)){
                    case 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' -> {
                        //invalid x-axis
                        switch (posChoice.charAt(1)){
                            case '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' -> validInput = true;
                            default -> System.out.println("Invalid Input! try again");
                        }
                    }
                    default -> System.out.println("Invalid Input! try again");
                }

            } catch (Exception e){
                System.out.println("Invalid Input! try again");
            }
        }
        userPos = posChoice;
    }

    //What to do with user position
    private void setUserPos(gameGrid gg){
        //the +1 is required to have proper grid indexing
        int xAxis = (userPos.charAt(1)-'0')+1; //cols
        int yAxis = -1; //rows
        switch(userPos.charAt(0)){
            case 'A' -> yAxis = 1;
            case 'B' -> yAxis = 2;
            case 'C' -> yAxis = 3;
            case 'D' -> yAxis = 4;
            case 'E' -> yAxis = 5;
            case 'F' -> yAxis = 6;
            case 'G' -> yAxis = 7;
            case 'H' -> yAxis = 8;
            case 'I' -> yAxis = 9;
            case 'J' -> yAxis = 10;
        }
        //set old position to empty
        gg.setMainGridLoc(playerRow, playerCol, " ");
        gg.setCheatGridLoc(playerRow, playerCol, " ");
        //update current position
        playerRow = yAxis;
        playerCol = xAxis;
        checkUserPos(gg);
        //set current position on grid
        gg.setMainGridLoc(playerRow, playerCol, "@");
        gg.setCheatGridLoc(playerRow, playerCol, "@");
    }

    //user choosing to move W A S D
    private void playerMovement(gameGrid gg){
        boolean validInput = false;
        while(!validInput){
            String moveChoice = userMoveChoice();
            //move user to desired location
            gg.setMainGridLoc(playerRow, playerCol, " "); //set old position to empty
            gg.setCheatGridLoc(playerRow, playerCol, " ");
            switch(moveChoice){
                case "W" -> {
                    if(playerRow > 1){
                        playerRow--; //update player pos
                        checkUserPos(gg);
                        gg.setMainGridLoc(playerRow, playerCol, "@");
                        gg.setCheatGridLoc(playerRow, playerCol, "@");
                        validInput = true;
                    }
                    else System.out.println("(W) Cannot move up!");
                }
                case "A" -> {
                    if(playerCol > 1){
                        playerCol--; //update player pos
                        checkUserPos(gg);
                        gg.setMainGridLoc(playerRow, playerCol, "@");
                        gg.setCheatGridLoc(playerRow, playerCol, "@");
                        validInput = true;
                    }
                    else System.out.println("(A) Cannot move left!");
                }
                case "D" -> {
                    if(playerCol < 10){
                        playerCol++; //update player pos
                        checkUserPos(gg);
                        gg.setMainGridLoc(playerRow, playerCol, "@");
                        gg.setCheatGridLoc(playerRow, playerCol, "@");
                        validInput = true;
                    }
                    else System.out.println("(D) Cannot move right!");
                }
                case "S" -> {
                    if(playerRow < 10){
                        playerRow++; //update player pos
                        checkUserPos(gg);
                        gg.setMainGridLoc(playerRow, playerCol, "@");
                        gg.setCheatGridLoc(playerRow, playerCol, "@");
                        validInput = true;
                    }
                    else System.out.println("(S) Cannot move down!");
                }
            }
        }
    }

    //input checking for playerMovement()
    private String userMoveChoice(){
        Scanner input = new Scanner(System.in);
        //get user movement choice
        boolean validInput = false;
        String moveChoice = "";
        while(!validInput){
            System.out.print("Choose Move (W, A, S, D): ");
            try{
                moveChoice = input.nextLine();
                moveChoice = moveChoice.toUpperCase();
                switch(moveChoice){
                    case "W", "A", "S", "D" -> validInput = true;
                    default -> System.out.println("Invalid Input! try again");
                }
            } catch (Exception e){
                System.out.println("Invalid Input! try again");
            }
        }
        return moveChoice;
    }

    //check if current pos on tokimon or fokimon
    private void checkUserPos(gameGrid gg){
        String checkCell = gg.getCellCheatGrid(playerRow, playerCol);
        if(checkCell.equals("$")){ //landed on toki
            System.out.println("===============================");
            System.out.println("You found a Tokimon, Congrats!");
            System.out.println("===============================");
            tokisCollected++;
        } else if(checkCell.equals("X")){ //landed on foki
            System.out.println("================================");
            System.out.println("You landed on a Fokimon, Game Over.");
            System.out.println("================================");
            gg.setCheatGridLoc(playerRow, playerCol, "@X");
            gg.displayCheatGrid();
            System.exit(0);
        }
    }

    //show user number of tokis collected and remaining
    private void showUserInfo(gridLogic gl){
        int tokisRemaining = gl.getNumToki() - tokisCollected;
        System.out.println("========================");
        System.out.println("Tokis collected: " + tokisCollected);
        System.out.println("Tokis remaining: " + tokisRemaining);
        System.out.println("Spells remaining: " + numOfSpells);
        System.out.println("========================");
    }

    //user choosing to use 1 of 3 spells
    private void userSpellChoice(gameGrid gg, gridLogic gl){
        Scanner input = new Scanner(System.in);
        System.out.println("Choose a spell to use!");
        System.out.println("1. Teleport to location");
        System.out.println("2. Reveal Tokimon location");
        System.out.println("3. Kill Fokimon");
        //get user movement choice
        boolean validInput = false;
        String spellChoice;
        while(!validInput){
            System.out.print("Which spell would you like to use: ");
            try{
                spellChoice = input.nextLine();
                switch(spellChoice){
                    case "1" -> {
                        teleportPlayerTo(gg);
                        checkUserPos(gg);
                        validInput = true;
                    }
                    case "2" -> {
                        revealToki(gg, gl);
                        validInput = true;
                    }
                    case "3" -> {
                        killFoki(gg, gl);
                        validInput = true;
                    }
                    default -> System.out.println("Invalid Input! try again");
                }
            } catch (Exception e){
                System.out.println("Invalid Input! try again");
            }
        }
    }

    //show player game instructions
    private void gameIntructions(){
        String gameIntro = """
                You are a Tokimon Trainer trying to collect all Tokimons
                within a 10x10 grid! With no knowledge of their locations
                your goal is to find all Tokimons, but be careful, for each
                cell can also be occupied by a Fokimon! An evil bird-like
                creature looking to harm trainers. If you land on a Fokimon,
                you lose! Collect all Tokimon to Win! Good luck trainer!""";
        System.out.println(gameIntro);
        System.out.println("**************************");
        System.out.println("How to Play:");
        String gameRules = """
                - W, A, S, D to move up, left, down, or right
                - 3 different spells, with a limit of 3 uses total:
                   1. Teleport allows you to teleport to any cell on the grid
                   2. Reveal Tokimon randomly reveals 1 Tokimon on the grid, shown with '$'
                   3. Kill Fokimon randomly kills 1 Fokimon on the grid
                - @ tells you your position on the grid""";
        System.out.println(gameRules);
        System.out.println("**************************");
    }

    //getter
    public int getTokisCollected() { return tokisCollected; }

    //From spellOptions interface
    public void teleportPlayerTo(gameGrid gg) {
        Scanner input = new Scanner(System.in);
        //validate input for teleporting position
        boolean validInput = false;
        String posChoice = "";
        while(!validInput){
            System.out.print("Choose position to teleport to: ");
            try{
                posChoice = input.nextLine();
                posChoice = posChoice.toUpperCase();
                //invalid grid location
                if(posChoice.length() > 2 || posChoice.length() < 1){
                    System.out.println("Invalid Input! try again");
                    continue;
                }
                //invalid y-axis
                switch (posChoice.charAt(0)){
                    case 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' -> {
                        //invalid x-axis
                        switch (posChoice.charAt(1)){
                            case '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' -> validInput = true;
                            default -> System.out.println("Invalid Input! try again");
                        }
                    }
                    default -> System.out.println("Invalid Input! try again");
                }

            } catch (Exception e){
                System.out.println("Invalid Input! try again");
            }
        }
        userPos = posChoice;
        setUserPos(gg);
    }

    //From spellOptions interface
    public void revealToki(gameGrid gg, gridLogic gl) {
        Random rand = new Random();
        int listSize = gl.fokiList.size();
        int index = rand.nextInt(listSize); //get random foki
        int row = gl.tokiList.get(index).getRow();
        int col = gl.tokiList.get(index).getCol();
        //reveal foki on grid
        gg.setMainGridLoc(row, col, "$");
        System.out.println("*****************");
        System.out.println("Tokimon Revealed!");
        System.out.println("*****************");
    }

    //From spellOptions interface
    public void killFoki(gameGrid gg, gridLogic gl) {
        Random rand = new Random();
        int listSize = gl.fokiList.size();
        int index = rand.nextInt(listSize); //get random foki
        int row = gl.fokiList.get(index).getRow();
        int col = gl.fokiList.get(index).getCol();
        //remove foki from grid
        gg.setCheatGridLoc(row, col, " ");
        gl.fokiList.remove(index);
        System.out.println("***************");
        System.out.println("Fokimon Killed!");
        System.out.println("***************");
    }
}
