package ca.cmpt213.as2;

/**
 * @author Jai Malhi
 * @info The main class
 */
public class Main {
    public static void main(String[] args){
        System.out.println("Input: " + args[0]);
        System.out.println("Output: " + args[1]);

        InputFilter.jsonFilter(args[0]);
        InputFilter.readJson();
        OutputTokis.outToCSV(args[1]);
    }
}