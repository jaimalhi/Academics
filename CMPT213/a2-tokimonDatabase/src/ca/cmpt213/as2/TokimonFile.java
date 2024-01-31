package ca.cmpt213.as2;
import java.util.ArrayList;
import java.util.List;

/**
 * @author Jai Malhi
 * @team holds each 'team' object from json files
 * @extra_comments stores the extra comments from each json file
 */
public class TokimonFile {
    //these are outermost objects
    private List<Teams> team = new ArrayList<>();
    private String extra_comments;

    public TokimonFile(){}

    @Override
    public String toString() {
        return "Tokimons{" +
                "team=" + team +
                ", extra_comments='" + extra_comments + '\'' +
                '}';
    }
    public List<Teams> getTeam(){ return this.team; }
    public String getExtra_comments(){ return this.extra_comments; }

    /**
     * @name stores the name attribute of each object in team
     * @id stores the id attribute of each object in team
     * @compatibility holds the objects within 'compatibility'
     */
    public static class Teams {
        private String name;
        private String id;
        private Compatibility compatibility;

        public Teams(){}

        @Override
        public String toString() {
            return "{" +
                    "name='" + name + '\'' +
                    ", id='" + id + '\'' +
                    ", compatibility=" + compatibility +
                    '}';
        }
        public String getName(){ return name;}
        public String getId(){ return id;}
        public Compatibility getCompatibility(){ return compatibility; }

        /**
         * @score stores the score attribute of each object in compatibility
         * @comment stores the comment attribute of each object in compatibility
         */
        public static class Compatibility {
            private double score;
            private String comment;

            public Compatibility(){}

            @Override
            public String toString() {
                return "{" +
                        "score=" + score +
                        ", comment='" + comment + '\'' +
                        '}';
            }
            public double getScore(){ return score; }
            public String getComment(){ return comment; }
        } //Compatibility class
    } //Team class
} //Tokimons class
