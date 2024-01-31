package ca.cmpt213.asn5.mutantdb.controller;
import ca.cmpt213.asn5.mutantdb.model.*;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.server.ResponseStatusException;

import javax.annotation.PostConstruct;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;


/**
 * @author Jai Malhi
 * @mutants a list to holds all mutants
 * @inputFilter InputFilter object to parse json
 * @mutantInfo holds individual mutants
 */
@RestController
public class MutantController {
    private List<MutantInfo.Mutant> mutants = new ArrayList<>();
    private InputFilter inputFilter = new InputFilter();
    private MutantInfo mutantInfo;

    @GetMapping("/api/mutant/all")
    public List<MutantInfo.Mutant> getAllMutants(){
        System.out.println("GET all mutants:");
        //System.out.println(this.mutants);
        return this.mutants;
    }

    @GetMapping("/api/mutant/{id}") //'HttpServletResponse resp' param
    public MutantInfo.Mutant getMutant(@PathVariable String id){
        int newId = Integer.parseInt(id);
        if(newId >= mutants.size()){
            System.out.println("Incorrect ID, try again");
            throw new ResponseStatusException(HttpStatus.NOT_FOUND, "Invalid ID");
            //resp.setStatus(HttpServletResponse.SC_NOT_FOUND); //404
        } else if(newId < 0){
            System.out.println("Incorrect ID, try again");
            throw new ResponseStatusException(HttpStatus.NOT_FOUND, "Invalid ID");
            //resp.setStatus(HttpServletResponse.SC_NOT_FOUND); //404
        } else {
            try {
                System.out.println("Get Mutant with ID: " + newId);
                return mutants.get(newId);
            } catch (Exception e){
                System.out.println("Something went wrong, please try again");
                throw new ResponseStatusException(HttpStatus.NOT_FOUND, "Something went wrong, Confirm ID");
                //resp.setStatus(HttpServletResponse.SC_NOT_FOUND); //404
            }
        }
        //return null;
    }

    @PostMapping("/api/mutant/add")  //'HttpServletResponse resp' param
    public MutantInfo.Mutant addMutant(@RequestBody MutantInfo.Mutant newMutant){
        System.out.println(newMutant);
        mutants.add(newMutant);
        updateJson(mutants); //update mutant.json file
        //resp.setStatus(HttpServletResponse.SC_CREATED); //201
        return newMutant;
    }

    @DeleteMapping("api/mutant/{id}") //'HttpServletResponse resp' param
    public MutantInfo.Mutant deleteMutant(@PathVariable String id){
        int newId = Integer.parseInt(id);
        //delete the person, id corresponds to index
        try {
            //correct IDs of remaining mutants
            int size = mutants.size();;
            for(int i = newId;i < size;i++){
                mutants.get(i).setId(i-1);
            }
            MutantInfo.Mutant temp = mutants.get(newId);
            mutants.remove(newId);
            updateJson(mutants); //update mutant.json file
            System.out.println("Delete person: " + newId);
            return temp;
            //resp.setStatus(HttpServletResponse.SC_NO_CONTENT); //204
        } catch (Exception e){
            System.out.println("Something went wrong, confirm correct ID");
            e.printStackTrace();
            throw new ResponseStatusException(HttpStatus.NOT_FOUND, "Something went wrong, Confirm ID");
            //resp.setStatus(HttpServletResponse.SC_NOT_FOUND); //404
        }
    }

    @PostConstruct
    public void initIt(){
        System.out.println("POST CONSTRUCT CODE");
        //add default mutants to json
        writeJsonData();
        //read from json
        collectJsonData();
        mutantInfo = inputFilter.getMutantList();
        //set mutant list
        this.mutants = mutantInfo.getMutants();
    }

    //reading JSON files
    private void collectJsonData(){
        inputFilter.jsonFilter();
        inputFilter.readJson();
    }

    //writing to JSON files
    private void writeJsonData(){
        Gson gson = new GsonBuilder().setPrettyPrinting().create();
        //create mutants
        MutantInfo.Mutant m1 = new MutantInfo.Mutant("Shadow","magic",150,60,55);
        MutantInfo.Mutant m2 = new MutantInfo.Mutant("Iceman","ice",225,70,75);
        MutantInfo.Mutant m3 = new MutantInfo.Mutant("Maki","fire",110,40,65);
        //add mutants to temp MutantInfo
        List<MutantInfo.Mutant> newMutants = new ArrayList<>();
        newMutants.add(m1);
        newMutants.add(m2);
        newMutants.add(m3);
        MutantInfo temp = new MutantInfo();
        temp.setMutants(newMutants);
        //Java objects to JSON file
        try (FileWriter writer = new FileWriter("./data/mutant.json")) {
            gson.toJson(temp, writer);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    //update json after removal/adding
    private void updateJson(List<MutantInfo.Mutant> remainingMutants){
        Gson gson = new GsonBuilder().setPrettyPrinting().create();
        //convert to MutantInfo type
        MutantInfo temp = new MutantInfo();
        temp.setMutants(remainingMutants);
        //Java objects to JSON file
        try (FileWriter writer = new FileWriter("./data/mutant.json")) {
            gson.toJson(temp, writer);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

