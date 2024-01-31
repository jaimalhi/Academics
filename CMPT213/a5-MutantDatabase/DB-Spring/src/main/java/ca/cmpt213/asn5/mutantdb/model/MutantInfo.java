package ca.cmpt213.asn5.mutantdb.model;

import java.util.ArrayList;
import java.util.List;

/**
 * @author Jai Malhi
 * @mutants hold each 'mutant' from json file
 */
public class MutantInfo {
    //outermost object 'mutants'
    private List<Mutant> mutants = new ArrayList<>();
    private static int total = 0;

    public static class Mutant {
        private String name;
        private String category;
        private int id;
        private int weight;
        private int height;
        private int ability;

        //constructor
        public Mutant(String name, String category, int weight, int height, int ability) {
            this.name = name;
            this.category = category;
            this.weight = weight;
            this.height = height;
            this.ability = ability;
            this.id = total;
            total++;
        }

        //getters
        public String getName() { return name; }
        public String getCategory() { return category; }
        public int getId() { return id; }
        public int getWeight() { return weight; }
        public int getHeight() { return height; }
        public int getAbility() { return ability; }
        //setter
        public void setId(int id) { this.id = id; }

        @Override
        public String toString() {
            return "Mutant{" +
                    "name='" + name + '\'' +
                    ", category='" + category + '\'' +
                    ", id=" + id +
                    ", weight=" + weight +
                    ", height=" + height +
                    ", ability=" + ability +
                    '}';
        }
    }
    //getter
    public List<Mutant> getMutants(){ return mutants; }
    //setter
    public void setMutants(List<Mutant> mutants){ this.mutants = mutants; }

    @Override
    public String toString() {
        return "MutantInfo{" + mutants + '}';
    }
}
