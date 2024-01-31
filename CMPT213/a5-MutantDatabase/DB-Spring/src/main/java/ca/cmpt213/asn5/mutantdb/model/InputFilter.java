package ca.cmpt213.asn5.mutantdb.model;

import com.google.gson.Gson;

import java.io.File;
import java.io.Reader;
import java.nio.file.Files;
import java.nio.file.Paths;;

/**
 * @author Jai Malhi
 * @mutantFile holds the path of mutant.json
 * @mutantList holds a list of Mutants
 */
public class InputFilter {
    static File mutantFile;
    public static MutantInfo mutantList;

    //Get json file
    public void jsonFilter(){
        //"./data/mutant.json"
        File folder = new File("./data");

        if(!folder.isDirectory()){
            System.out.println("Directory not valid");
            System.exit(-1);
        }
        for(File subFile : folder.listFiles()){
            if(subFile.getName().endsWith(".json")){
                mutantFile = subFile;
            } else {
                System.out.println("No JSON files found");
                System.exit(-1);
            }
        }
    }

    public void readJson(){
        //for each json file
        try {
            Gson gson = new Gson();
            String fileName = mutantFile.getPath();

            Reader reader = Files.newBufferedReader(Paths.get(fileName));
            MutantInfo allMutants = gson.fromJson(reader, MutantInfo.class);
            mutantList = allMutants;

            reader.close();
            //System.out.println("\n" + allMutants);
        } catch (Exception e) {
            System.out.println("Error while reading file");
            e.printStackTrace();
        }
    }

    public MutantInfo getMutantList() { return mutantList; }
}
