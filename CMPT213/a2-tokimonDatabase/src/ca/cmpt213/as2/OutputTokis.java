package ca.cmpt213.as2;
import com.opencsv.CSVWriter;
import java.io.File;
import java.io.FileWriter;
import java.util.Arrays;

/**
 * @author Jai Malhi
 * @info this class is used to output the collected data to a CSV file
 */
public class OutputTokis {
    public static void outToCSV(String output){
        // 1-OneTeamOneToki | 2-OneTeamManyTokis | 3-CoupleSmallTeams
        // "./AnalysisResults_v2/2-OneTeamManyTokis/teamData.csv"

        //Specifiy filepath where CSV will be placed
        File outputPath = new File(output);
        try {
            //create FileWriter object with file as parameter
            FileWriter fw = new FileWriter(outputPath);
            //create CSVWriter object filewriter object as parameter
            CSVWriter writer = new CSVWriter(fw);

            //adding header to csv
            String[] header = { "Team #","From Toki","To Toki","","Score","Comment","","Extra" };
            writer.writeNext(header);

            //Create main CSV content
            writer.writeNext(new String[]{"Team 1"});
            for(TokimonFile tf : InputFilter.getTokiDataList()){
                String xComment = tf.getExtra_comments();
                //get main toki ID to compare other tokis to
                TokimonFile.Teams temp = tf.getTeam().get(0);
                String mainTokiID = temp.getId();
                //get the team name
                String teamName = temp.getName().substring(0,5);
                for(TokimonFile.Teams t : tf.getTeam()){
                    String id = t.getId();
                    String comment = t.getCompatibility().getComment();
                    String score = Double.toString(t.getCompatibility().getScore());

                    if(teamName.equals("Team1") || teamName.equals("Team2")){
                        if(id.equals(mainTokiID)) {
                            id = "-";
                            String[] data = {"", mainTokiID, id, "", score, comment, "", xComment};
                            writer.writeNext(data);
                        } else {
                            String[] data = {"", mainTokiID, id, "", score, comment, ""};
                            writer.writeNext(data);
                        }
                    } else {
                        break;
                    }
                } //forEach team
            } //forEach tokimonFile

            int count = 0;
            for(TokimonFile tf : InputFilter.getTokiDataList()){
                String xComment = tf.getExtra_comments();
                //get main toki ID to compare other tokis to
                TokimonFile.Teams temp = tf.getTeam().get(0);
                String mainTokiID = temp.getId();
                //get the team name
                String teamName = temp.getName().substring(0,5);
                for(TokimonFile.Teams t : tf.getTeam()){
                    String id = t.getId();
                    String comment = t.getCompatibility().getComment();
                    String score = Double.toString(t.getCompatibility().getScore());

                    if(teamName.equals("Team3") || teamName.equals("Team4")){
                        if(count == 0) writer.writeNext(new String[]{"Team 2"});
                        if(id.equals(mainTokiID)) {
                            id = "-";
                            String[] data = {"", mainTokiID, id, "", score, comment, "", xComment};
                            writer.writeNext(data);
                        } else {
                            String[] data = {"", mainTokiID, id, "", score, comment, ""};
                            writer.writeNext(data);
                        }
                        count++;
                    } else {
                        break;
                    }
                } //forEach team
            } //forEach tokimonFile

            //closing writer connection
            writer.close();
        } catch (Exception e){
            System.out.println("Error while generating CSV");
            e.printStackTrace();
        }
    }
}
