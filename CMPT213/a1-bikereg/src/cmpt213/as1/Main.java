package cmpt213.as1;
import java.util.Scanner;
import java.util.ArrayList;

/**
 * @author Jai Malhi
 * @bikeArr holds bikes entered in registry
 * @bikeID keeps track of latest bikeID number
* */
public class Main {
    static ArrayList<BikeRegistry> bikeArr = new ArrayList<>();
    static int bikeID = 1;

    public static void main(String[] args) {
        displayMainMenu();
    }

    public static void displayMainMenu(){
        int userChoice = 0;
        mainMenuVisuals();
        Scanner input = new Scanner(System.in);

        //validate input
        boolean validInput = false;
        while(!validInput){
            System.out.print("Enter a number: ");
            try{
                userChoice = input.nextInt();
                input.nextLine();
                validInput = true;
            } catch (Exception e){
                System.out.println("Invalid Input, must be an integer");
                input.nextLine();
            }
        }

        if(userChoice == 1){
            displayAllBikes();
        } else if (userChoice == 2) {
            addNewBike();
        } else if (userChoice == 3) {
            if(bikeArr.size() < 1){
                System.out.println("No bikes in registry, cannot delete!");
            } else {
                deleteBike();
            }
        } else if (userChoice == 4) {
            if(bikeArr.size() < 1){
                System.out.println("No bikes in registry, cannot alter!");
            } else {
                alterBike();
            }
        } else if (userChoice == 5) {
            displayObjectsDebugger();
        } else if (userChoice == 6) { //exit
            System.out.println("Thank you for using this Registry!");
            return;
        }
        displayMainMenu();
    }

    private static void displayAllBikes(){
        System.out.println("=================");
        System.out.println("  List of Bikes ");
        System.out.println("=================");

        //get spacing required for display
        String ownerSpace = "";
        try{
            ownerSpace = "";
            int ownerLen = bikeArr.get(0).owner.length();
            for(int i = 0;i < ownerLen/2;i++){
                ownerSpace += " ";
            }
        } catch (Exception e){
            System.out.println("Cannot list bikes, none in registry!");
            return;
        }

        System.out.println("ID  Owner" + ownerSpace + "  Serial #" + "   " + "Type \t   Brake  Wheel Size");
        for(BikeRegistry b : bikeArr){
            System.out.println(b.bikeID + "   " + b.owner + "  " + b.serialNum + "  " + b.bikeType + "  " + b.brakeType + "   " + b.wheelSize);
        }
    } //displayAllBikes

    private static void addNewBike(){
        String owner, serialNum;
        String bikeType, brakeType;
        int wheelSize;

        System.out.println("==================");
        owner = setOwnerName();
        serialNum = setSerialNumber();
        bikeType = setBikeType();
        brakeType = setBrakeType();
        String wheelSizeString = setWheelSize();
        wheelSize = Integer.parseInt(wheelSizeString); //cast to integer

        //Adding new bike to registry array
        BikeRegistry newBike = new BikeRegistry(owner, serialNum.toUpperCase(), bikeType, brakeType, wheelSize, bikeID);
        bikeArr.add(newBike);
        bikeID++; //increment bike count
    } //addNewBike

    private static void deleteBike(){
        displayAllBikes();
        Scanner input = new Scanner(System.in);
        BikeRegistry lastBike = bikeArr.get(bikeArr.size()-1); //last element
        int userChoice = -1;
        //validate input
        boolean validInput = false;
        while(!validInput){
            System.out.print("Enter ID (0 to cancel): ");
            try{
                userChoice = input.nextInt();
                input.nextLine();
                if(userChoice <= lastBike.getBikeID()){
                    validInput = true;
                } else {
                    System.out.println("Invalid Input, must be in range");
                }
            } catch (Exception e){
                System.out.println("Invalid Input, must be an integer");
                input.nextLine();
            }
        }

        if(userChoice == 0){
            System.out.println("Cancelled");
            return;
        }
        bikeArr.remove(userChoice-1);
        //correct BikeId's
        int arrSize = bikeArr.size();
        for(int i = userChoice-1;i < arrSize;i++){
            BikeRegistry b = bikeArr.get(i);
            int currentBikeID = b.getBikeID();
            b.setBikeID(currentBikeID-1);
        }
        System.out.println("Bike removed");
    } //deleteBike

    private static void alterBike(){
        displayAllBikes();
        Scanner input = new Scanner(System.in);
        BikeRegistry lastBike = bikeArr.get(bikeArr.size()-1); //last element
        int userChoice = -1;
        String attribute = "ERROR_UNDEFINED";
        String newAttribute = "ERROR_UNDEFINED";

        boolean validInput = false;
        while(!validInput){
            System.out.print("Enter ID (0 to cancel): ");
            try{
                userChoice = input.nextInt();
                input.nextLine();
                if(userChoice <= lastBike.getBikeID()){
                    validInput = true;
                } else {
                    System.out.println("Invalid Input, must be in range");
                }
            } catch (Exception e){
                System.out.println("Invalid Input, must be an integer");
                input.nextLine();
            }
        }
        //cancel operation
        if(userChoice == 0){
            System.out.println("Cancelled");
            return;
        }

        validInput = false;
        while(!validInput){
            System.out.print("Which Attribute: ");
            attribute = input.nextLine();
            attribute = attribute.substring(0, 1).toUpperCase() + attribute.substring(1); //capitalize
            switch (attribute){
                case "Owner", "Serial", "Serial #", "Type", "Brake", "Wheel Size", "Wheel size", "Wheel", "Size" -> validInput = true;
                default -> System.out.println("Invalid Input, enter Owner, Type, Serial, Brake, or Wheel Size");
            }
        }

        //input checking for newAttribute types
        switch (attribute) {
            case "Owner" -> newAttribute = setOwnerName();
            case "Serial", "Serial #" -> newAttribute = setSerialNumber();
            case "Type" -> newAttribute = setBikeType();
            case "Brake" -> newAttribute = setBrakeType();
            case "Wheel Size", "Wheel size", "Wheel", "Size" -> newAttribute = setWheelSize();
            default -> System.out.println("ERROR - Unknown attribute type!");
        }

        BikeRegistry temp = bikeArr.get(userChoice-1);
        switch (attribute) {
            case "Owner" -> temp.setOwner(newAttribute);
            case "Type" -> temp.setBikeType(newAttribute);
            case "Serial", "Serial #" -> temp.setSerialNum(newAttribute.toUpperCase());
            case "Brake" -> temp.setBrakeType(newAttribute);
            case "Wheel Size", "Wheel size", "Wheel" -> temp.setWheelSize(Integer.parseInt(newAttribute));
        }
        bikeArr.set(userChoice-1, temp);
        System.out.println("New value saved");
    } //alterBike

    private static void displayObjectsDebugger(){
        System.out.println("All Bike objects:");
        for(BikeRegistry b : bikeArr){
            System.out.println(b);
        }
    } //displayObjectsDebugger (using toString)

    private static void mainMenuVisuals(){
        System.out.println("\n=============");
        System.out.println("  Main Menu ");
        System.out.println("=============");
        System.out.println("1. List Bikes");
        System.out.println("2. Add a Bike");
        System.out.println("3. Remove a Bike");
        System.out.println("4. Alter a Bike");
        System.out.println("5. Display Objects (toString)");
        System.out.println("6. Exit Registry");
    } //mainMenuVisuals

    private static String setOwnerName(){
        Scanner input = new Scanner(System.in);
        String owner = "ERROR_UNDEFINED";
        boolean validInput = false;
        while(!validInput){
            System.out.print("Enter Owner name: ");
            owner = input.nextLine();
            if(owner.equals("")){
                System.out.println("Invalid Input, cannot be empty");
            } else {
                validInput = true;
            }
        }
        //capitalize
        owner = owner.substring(0, 1).toUpperCase() + owner.substring(1);
        return owner;
    } //setOwnerName

    private static String setSerialNumber(){
        Scanner input = new Scanner(System.in);
        String serialNum = "ERROR_UNDEFINED";
        boolean validInput = false;
        while(!validInput){
            System.out.print("Enter Bike's serial number: ");
            serialNum = input.nextLine();
            if(serialNum.equals("")){
                System.out.println("Invalid Input, cannot be empty");
            } else {
                validInput = true;
            }
        }
        return serialNum;
    } //setSerialNumber

    private static String setBikeType(){
        Scanner input = new Scanner(System.in);
        String bikeType = "ERROR_UNDEFINED";
        boolean validInput = false;
        while(!validInput){
            System.out.print("Enter Bike type: ");
            bikeType = input.next();
            bikeType = bikeType.substring(0, 1).toUpperCase() + bikeType.substring(1); //capitalize
            switch (bikeType){
                case "Mountain", "Road", "Commuter", "Touring", "Utility", "Electric", "Cruiser" -> validInput = true;
                case "Folding", "Track", "Fixed", "BMX", "Bmx", "Recumbent", "Hybrid" -> validInput = true;
                default -> System.out.println("Invalid Input, enter a valid bike type");
            }
            input.nextLine();
        }
        return bikeType;
    } //setBikeType

    private static String setBrakeType(){
        Scanner input = new Scanner(System.in);
        String brakeType = "ERROR_UNDEFINED";
        boolean validInput = false;
        while(!validInput){
            System.out.print("Enter Bike's brake type: ");
            brakeType = input.next();
            brakeType = brakeType.substring(0, 1).toUpperCase() + brakeType.substring(1); //capitalize
            switch (brakeType){
                case "Rim", "Disc", "Drum" -> validInput = true;
                default -> System.out.println("Invalid Input, enter Rim, Disc, or Drum");
            }
            input.nextLine();
        }
        return brakeType;
    } //setBrakeType

    private static String setWheelSize(){
        Scanner input = new Scanner(System.in);
        int wheelSize = -1;
        boolean validInput = false;
        while(!validInput){
            System.out.print("Enter Bike's wheel size: ");
            try{
                wheelSize = input.nextInt();
                input.nextLine();
                if(wheelSize > 0 && wheelSize <= 50){
                    validInput = true;
                } else {
                    System.out.println("Invalid Input, must be greater than 0 and less than 50");
                }
            } catch (Exception e){
                System.out.println("Invalid Input, must be an integer");
                input.nextLine();
            }
        }
        return String.valueOf(wheelSize);
    } //setWheelSize
}

