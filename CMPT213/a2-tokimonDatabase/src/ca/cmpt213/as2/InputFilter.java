package ca.cmpt213.as2;
import com.google.gson.Gson;
import java.io.File;
import java.io.Reader;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * @author Jai Malhi
 * @fileList holds the path to each json file
 * @tokiDataList holds each json files formatted contents
 */
public class InputFilter {
    static List<File> fileList = new ArrayList<>();
    static List<TokimonFile> tokiDataList = new ArrayList<>();

    //Iterate through files in a subdirectories
    public static void fetchFiles(File dir) {
        if(dir.isDirectory()){
            for(File subFile : dir.listFiles()){
                if(subFile.getName().endsWith(".json")){
                    fileList.add(subFile);
                }
                fetchFiles(subFile);
            }
        }
    }

    //Get all json files
    public static void jsonFilter(String input){
        // 1-OneTeamOneToki | 2-OneTeamManyTokis | 3-CoupleSmallTeams
        // java "./InputTestDataSets/1-OneTeamOneToki"

        //Get all json files
        File folder = new File(input);
        if(!folder.isDirectory()){
            System.out.println("Directory not valid");
            System.exit(-1);
        }
        fetchFiles(folder);
        if(fileList.isEmpty()){
            System.out.println("No JSON files found");
            System.exit(-1);
        }
    }

    public static void readJson(){
        //for each json file
        try {
            Gson gson = new Gson();
            for(File file : fileList){
                String fileName = file.getPath();

                Reader reader = Files.newBufferedReader(Paths.get(fileName));
                TokimonFile allTokis = gson.fromJson(reader, TokimonFile.class);
                tokiDataList.add(allTokis);
                reader.close();
                //System.out.println("\n" + allTokis);
            }
        } catch (Exception e) {
            System.out.println("Error while reading file");
            e.printStackTrace();
        }
        //check if any scores less than 0
        for(TokimonFile tf : tokiDataList){
            for(TokimonFile.Teams t : tf.getTeam()){
                double currScore = t.getCompatibility().getScore();
                if(currScore < 0){
                    System.out.println("A Tokimon Score is less than 0");
                    System.exit(-1);
                }
            }
        }
    }

    //Getters
    public static List<TokimonFile> getTokiDataList(){ return tokiDataList; }
    public static List<File> getFileList() { return fileList; }
}
