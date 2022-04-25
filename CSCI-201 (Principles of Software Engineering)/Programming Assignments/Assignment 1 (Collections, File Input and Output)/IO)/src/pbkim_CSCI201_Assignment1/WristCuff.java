package pbkim_CSCI201_Assignment1;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.*;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonIOException;
import com.google.gson.JsonSyntaxException;

public class WristCuff {
	
	public ArrayList <TimefallShelter> ShelterList;
	private ArrayList <Integer> FrequencyList;
	String FileName;

    //Setting Initial Values (Constructor)
    public WristCuff(ArrayList<TimefallShelter> list, ArrayList <Integer> list2, String file) {
    	this.ShelterList = list;
    	this.FrequencyList = list2;
    	this.FileName = file;
    }

    /**
     * List all available shelters within the min and max of supported Chiral frequencies
     */
    public void listAllShelters() {
    	if (FrequencyList == null) { // No Frequency User Input
    		System.out.println("\n" + 0 + " results\n");
    		return;
    	}
    	int count = 0;
    	ArrayList<TimefallShelter> ValidSolution = new ArrayList<TimefallShelter>();
    	
    	for (int i = 0; i < this.ShelterList.size(); i++) {
    		int Chiral = ShelterList.get(i).getChiral();
    		if (FrequencyList.contains(Chiral)) {
    			if (ShelterList.get(i).getTimefall() == false) {
    				ValidSolution.add(ShelterList.get(i));
        			count++;
    			}
    		}
    	}
    	
    	System.out.println("\n" + String.valueOf(count) + " results\n");
    	for (int i = 0; i < ValidSolution.size(); i++) {
    		System.out.println(ValidSolution.get(i).toString());
    	}
    }
    
    // I will keep this commented code here to not get docked points for prompt.
    // Prompt says between min and max ranges of frequencies.
    // Piazza @311 says only the available shelters with the supported Chiral frequencies within the range.
    
	//    public void listAllShelters() {
	//    	if (FrequencyList == null) {
	//    		System.out.println("\n" + 0 + " results\n");
	//    		return;
	//    	}
	//    	
	//    	int min = Collections.min(FrequencyList);
	//    	int max = Collections.max(FrequencyList);
	//    	int count = 0;
	//    	ArrayList<TimefallShelter> ValidSolution = new ArrayList<TimefallShelter>();
	//    	
	//    	for (int i = 0; i < this.ShelterList.size(); i++) {
	//    		int Chiral = ShelterList.get(i).getChiral();
	//    		if (Chiral >= min && Chiral <= max) {
	//    			if (ShelterList.get(i).getTimefall() == false) {
	//    				ValidSolution.add(ShelterList.get(i));
	//        			count++;
	//    			}
	//    		}
	//    	}
	//    	
	//    	System.out.println("\n" + String.valueOf(count) + " results\n");
	//    	
	//    	for (int i = 0; i < ValidSolution.size(); i++) {
	//    		System.out.println(ValidSolution.get(i).toString());
	//    	}
	//    }
  
    /** (Very Similar Functions)
     * Functions for:
     * Search for a shelter by Chiral frequency
     * Search for a shelter by name
     */
    
    public void findName() {
    	boolean temp = false;
    	String option;
    	while (temp == false) {
    		try {
    			System.out.print("\nWhat shelter's name are you looking for? ");
    			Scanner input = new Scanner(System.in);
    			option = input.nextLine().trim(); // We want to uniformly compare strings later
    			System.out.println("");
    			for (int i = 0; i < this.ShelterList.size(); i++) {
    				String temp1 = ShelterList.get(i).getName().trim();
    				if (option.equalsIgnoreCase(temp1) == true) {
    					System.out.println("Found!\n");
    					System.out.println(ShelterList.get(i).toString());
    					temp = true;
    					return; // From Prompt we do not have to worry about duplicate cases
    				}
    			}
    			// This means the name doesn't exist
    			// By logic, the function should've returned already
    			throw new NoSuchElementException();
    		}
    		catch (NoSuchElementException e) {
    			System.out.println("No such shelter...");
    		}
    		catch (Exception e) { // General Exception
    			System.out.println("There is an exception (some error)!!!\n");
    		}
    	}
    }
    
    public void findChiral() {
    	boolean temp = false;
    	Integer option;
    	while (temp == false) {
    		try {
    			System.out.print("\nWhat Chiral frequency are you looking for? ");
    			Scanner input = new Scanner(System.in);
    			option = Integer.parseInt(input.nextLine().trim()); // We want to uniformly compare strings later
    			System.out.println("");
    			for (int i = 0; i < this.ShelterList.size(); i++) {
    				Integer temp1 = ShelterList.get(i).getChiral();
    				if (option == temp1) {
    					System.out.println(ShelterList.get(i).toString());
    					temp = true;
    					return;
    					// all frequencies are unique
    				}
    			}
    			// Every Chiral will be unique (prompt)
    			// will reach here if freq DNE
    			throw new NoSuchElementException();
    		}
    		catch (NoSuchElementException e) { // This means Chiral DNE
    			System.out.println("That Chiral frequency does not exist.");
    		}
    		catch (NumberFormatException e) {
    			System.out.println("Wrong Input, enter an integer");
    		}
    		catch (Exception e) { // General Exception
    			System.out.println("There is an exception (some error)!!!\n");
    		}
    	}
    }


    /**
     * Find an available shelter with the lowest supported Chiral frequency
     */
    public void findShelter() {
    	System.out.println("\n== Commencing timefall shelter search ===");
    	if (ShelterList == null|| FrequencyList == null) {
    		try {
				save();
			}
			catch (FileNotFoundException e) {
				System.out.println("File Not Found Error");
			}
			System.out.println("=== No shelter available. You are DOOMED. ===");
			System.exit(0);
		}
    	
    	Collections.sort(FrequencyList);
    	Collections.sort(ShelterList); // Piazza @273 (we should be sorting too)
    	
    	for (int i = 0; i < this.ShelterList.size(); i++) {
    		if (ShelterList.isEmpty() || FrequencyList.isEmpty() || ShelterList == null|| FrequencyList == null) {
    			try {
					save();
				}
				catch (FileNotFoundException e) {
					System.out.println("File Not Found Error");
				}
				System.out.println("=== No shelter available. You are DOOMED. ===");
				System.exit(0);
			}
    		int min = FrequencyList.get(0); // Since Sorted
    		int Chiral = ShelterList.get(i).getChiral();
    		
    		if (Chiral == min) { // If exists
    			if (ShelterList.get(i).getTimefall() == false) {
	    			System.out.println("\n=== Matching timefall shelter found! ===\n");
	    			System.out.println(ShelterList.get(i).toString());
	    			System.out.println("=== Commencing Chiral jump, see you in safety. ===");
	    			System.exit(0);
    			}
    			else { // If not Valid
    				System.out.println("=== Chiral frequency " + min + " unstable, Chiral jump unavailable. ===");
    				System.out.print("=== Removing target shelter from the list of shelters and saving updated list");
    				System.out.println(" to disk. ===");
    				
    				ShelterList.remove(ShelterList.get(i));
    				FrequencyList.remove(0);
    				
    				try {
    					save();
    				}
    				catch (FileNotFoundException e) {
    					System.out.println("File Not Found Error");
    				}
    				catch (Exception e) { // General Exception
    	    			System.out.println("There is an exception (some error)!!!\n");
    	    		}		
		
    				if (ShelterList.isEmpty() || FrequencyList.isEmpty() || ShelterList == null|| FrequencyList == null) {
    					System.out.println("=== No shelter available. You are DOOMED. ===");
    					System.exit(0);
    				}
    			}
    			i = -1; // Restart loop
    		}
    		
    		if (i == this.ShelterList.size()-1) {// If the frequency number (min) does not exist
    			System.out.println("=== Chiral frequency " + min + " unstable, Chiral jump unavailable. ===");
    			System.out.print("=== Removing target shelter from the list of shelters and saving updated list");
				System.out.println(" to disk. ===");
				i = 0;
    			FrequencyList.remove(0);
    			try {
					save();
				}
				catch (FileNotFoundException e) {
					System.out.println("File Not Found Error");
				}
    			catch (Exception e) { // General Exception
        			System.out.println("There is an exception (some error)!!!\n");
        		}
    		}
    	}
    }

    /**
     * Sort shelters by Chiral frequency
     */
    public void sortShelters() throws FileNotFoundException {
    	// We make a CompareTo method in the TimefallShelter class
    	// This automatically compares the Chiral Frequency
    	Collections.sort(ShelterList);
    	try{
    		// Found Online ("How to format GSON with prettyprinting") || Piazza Too
    		Gson gson1 = new GsonBuilder().setPrettyPrinting().create();
            FileWriter temp = new FileWriter(FileName); // Lecture
            gson1.toJson(ShelterList, temp); // Lecture
            // Blank page if we don't do this (consulted online)
            temp.flush();
            temp.close();
            //
            System.out.println("\nShelters successfully sorted by Chiral frequency.");
    	}
    	catch (IOException e){ //If File doesn't open.
            System.out.println("There is an Input/Output exception here!");
        }
    	catch (Exception e) { // General Exception
			System.out.println("There is an exception (some error)!!!\n");
		}
    }

    /**
     * Saves the updated list of shelters to disk
     */
    public void save() throws FileNotFoundException {
    	try{
    		// Same as above
    		Gson gson1 = new GsonBuilder().setPrettyPrinting().create(); // Piazza @ 152
            FileWriter temp = new FileWriter(FileName); // Lecture
            gson1.toJson(ShelterList, temp); // Lecture
            // Blank page if we don't do this (consulted online)
            temp.flush();
            temp.close();
            //
    	}
    	catch (IOException e){ //If File doesn't open.
            System.out.println("There is an Input/Output exception here!");
        }
    	catch (Exception e) { // General Exception
			System.out.println("There is an exception (some error)!!!\n");
		}
    }
}


