package pbkim_CSCI201_Assignment1;

import java.io.*;
import java.util.Collection;
import java.util.Scanner;
import java.util.*;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonParseException;
import com.google.gson.reflect.TypeToken;
import com.google.gson.stream.JsonReader; // Tool that I found online

// *Notes/Comments*
/* When user enters nothing as frequency, I will assume there is no frequency; I will not set max's and min's frequency = 0, rather I set the ArrayList to null || Piazza @295
 * I check for Chiral Frequency and GUID and Name and PhoneNumber Uniqueness || Piazza.
 * I will assume that JSON File will have at least one object in the array (Prompt).
 * ^^ I do not test the case where there is no object in JSON.
 * I assume that addresses are always valid.
 * @Piazza @252 it's fine if I leave scanners not closed
 */

public class Main {
	private static String FileName;
	
	// Like a Vector in C++ (java.util.collection used**)
	private ArrayList <TimefallShelter> SheltersList; // To hold data from JSON (TimefallShelter is an object)
	private ArrayList <Integer> FrequencyList = new ArrayList<Integer>(); // To hold frequencies by user input
	
	private Boolean FileExists = false;
	private Boolean ChrialGood = false;
	
	// For Validating that Name, GUID, Chiral Frequencies,and Phone are unique
	Set<String> NameBank = new HashSet<String>();
	Set<String> GUIDBank = new HashSet<String>();
	Set<String> PhoneBank = new HashSet<String>();
	Set<Integer> ChiralBank = new HashSet<Integer>();

	/**
	 * Uses GSON to read the file inputed by the user
	 */
		
	private void readFile() {
		FileExists = true;
		try { 
			// "How to Read JSON from a File using GSON" (Online Documentation)
			JsonReader file = new JsonReader(new FileReader(FileName));
			SheltersList = new Gson().fromJson(file, new TypeToken<ArrayList<TimefallShelter>>() {
            }.getType());
			// Validate GSON Data Fields
			// Piazza @260 GSON Fills in Missing Parameters with null
			for (int i = 0; i < SheltersList.size(); i++) {				
				String GUIDVALID =  "^[{]?[0-9a-fA-F]{8}-([0-9a-fA-F]{4}-){3}[0-9a-fA-F]{12}[}]?$";  //https://www.geeksforgeeks.org/how-to-validate-guid-globally-unique-identifier-using-regular-expression/
				String PHONEVALID = "^(\\+\\d{1,3}( )?)?((\\(\\d{3}\\))|\\d{3})[- .]?\\d{3}[- .]?\\d{4}$"; //https://www.baeldung.com/java-regex-validate-phone-numbers
				
				// Formatting these Parameters
				SheltersList.get(i).setGuid(SheltersList.get(i).getGuid().replaceAll(" ",""));
				SheltersList.get(i).setPhone(SheltersList.get(i).getPhone().replaceAll(" ",""));
				SheltersList.get(i).setName(SheltersList.get(i).getName().trim());
				
				// Validating Name, GUID, and Phone, Chiral (Uniqueness)
				if (NameBank.contains(SheltersList.get(i).getName().toLowerCase().replaceAll(" ",""))) { // this compares two literal strings (no spaces and capitalizations)
					throw new IllegalArgumentException();
				}
				if (GUIDBank.contains(SheltersList.get(i).getGuid())) {
					throw new IllegalArgumentException();
				}
				if (PhoneBank.contains(SheltersList.get(i).getPhone())) {
					throw new IllegalArgumentException();
				}				
				if (ChiralBank.contains(SheltersList.get(i).getChiral())) {
					throw new IllegalArgumentException();
				}
				NameBank.add(SheltersList.get(i).getName().toLowerCase().replaceAll(" ",""));
				GUIDBank.add(SheltersList.get(i).getGuid());
				PhoneBank.add(SheltersList.get(i).getPhone());
				ChiralBank.add(SheltersList.get(i).getChiral());
				
				// Error Checking (If Data Fields are Empty)
				if (SheltersList.get(i).getAddress() == null || SheltersList.get(i).getChiral() == null || SheltersList.get(i).getGuid() == null || SheltersList.get(i).getName() == null || SheltersList.get(i).getPhone() == null || SheltersList.get(i).getTimefall() == null) {
					throw new NullPointerException();
				}	
				if(SheltersList.get(i).getAddress() == "" || SheltersList.get(i).getChiral() == null || SheltersList.get(i).getGuid() == "" || SheltersList.get(i).getName() == "" || SheltersList.get(i).getPhone() == "" || SheltersList.get(i).getTimefall() == null){
					throw new NullPointerException();
				}
				
				// Validating Name and Phone (Format) Piazza @241, @226
				if (SheltersList.get(i).getGuid().matches(GUIDVALID) == false) {
					throw new IllegalArgumentException();
				}
				if (SheltersList.get(i).getPhone().matches(PHONEVALID) == false) {
					throw new IllegalArgumentException();
				}
			}
		}
		catch(NullPointerException e) {
			FileExists = false;
			System.out.println("The GSON format in " + Main.FileName + " is missing data fields.\n");
		}
		catch (JsonParseException e) {
			FileExists = false;
			System.out.println("The GSON format in " + Main.FileName + " could not be parsed.\n");
		}
		catch(FileNotFoundException e) { // File cannot be found
			FileExists = false;
			System.out.println("The file " + Main.FileName + " could not be found.\n");
		}
		catch (IllegalArgumentException e) { // File is invalid
			FileExists = false;
			System.out.println("The file" + Main.FileName + " has illegal arguments found (Either a GSON Data Field Error, or there is a duplicate Name, GUID, Phone Number, or Chiral Value).\n");
		}
		catch (Exception e) { // General Exception
			FileExists = false;
			System.out.println("There is an exception (some error)!!!\n");
		}
	}

	/**
	 * Gets the supported chiral frequencies from the user
	 */
	
	//It is valid if no frequencies are entered as supported frequencies
	private void setSupportedFrequencies() {
		ChrialGood = true;
		try {
			Scanner input2 = new Scanner(System.in);
			String[] tempArray = input2.nextLine().split(","); // NextLine reads the whole line (and white spaces)
			if (tempArray[0] != "") { // NO USER INPUT
				// Here we split the input as a string, now we convert to an integer.
				for (int i = 0; i < tempArray.length; i++) {
					Integer j = Integer.valueOf(tempArray[i].trim()); // Convert string into Integer
					FrequencyList.add(j); // Add to frequency List
				}
			}
			else if (tempArray.length > 1 ) { // If comma is entered first (edge case)
				throw new NumberFormatException();
			}
			else {
				FrequencyList = null; // IF THERE IS NO USER INPUT
			}
		}
		catch (NumberFormatException e) { // Does not contain a valid integer
			ChrialGood = false;
			System.out.println("Number Format Error (Make sure numbers are separated with commas with a leading space!)");
		}
		catch (Exception e) { // General Exception
			ChrialGood = false;
			System.out.println("There is an exception!!!");
		}
	}

	/**
	 * Prints the option menu
	 */
	private void displayOptions() {
		System.out.println(
				"\n1) List all available shelters within the min and max of supported Chiral frequencies\n"
				+ "2) Search for a shelter by Chiral frequency\n"
				+ "3) Search for a shelter by name\n"
				+ "4) Sort shelters by Chiral frequency\n"
				+ "5) Jump to a shelter with the lowest supported Chiral frequency"
		);
	}

	public static void main(String[] args) {
		Main solution = new Main(); // Create Main Object
		System.out.println("Welcome to Bridges Link.\n");
		
		while (solution.FileExists == false) {
			System.out.print("Please provide timefall shelter data source: ");
			Scanner input1 = new Scanner(System.in); // Receive Input
			FileName = input1.next(); // Sets FileName
			solution.readFile(); // Call readFile Function
		}
		
		System.out.println("=== Data accepted ===\n");
		
		while (solution.ChrialGood == false) {
			System.out.print("Please provide supported Chiral frequencies: ");
			solution.setSupportedFrequencies(); // We want to validate the Chiral frequencies that they are integers (do it in function)
		}
		
		int option = 0;
		WristCuff Instance = new WristCuff(solution.SheltersList, solution.FrequencyList, Main.FileName); // Send Parameters
		
		while (option != 5) {
			solution.displayOptions();
			try {
				System.out.print("Choose an option: ");
				Scanner input2 = new Scanner(System.in);
				option = Integer.parseInt(input2.next());
			}
			catch (Exception e) {
				System.out.println("\nInvalid Input");
			}
			
			if (option == 1) { // List all available shelters within the min and max of Chiral Frequencies
				Instance.listAllShelters();
			}
			else if (option == 2) { // Find Shelter with Unique Chiral
				Instance.findChiral();
			}
			else if (option == 3) { // Find Shelter with Unique Name
				Instance.findName();
			}
			else if (option == 4) { // Sort Shelters
				try {
					Instance.sortShelters();
				}
				catch (FileNotFoundException e){
					System.out.println("Some Error Occurred (file not found)");
				}
			}
			else if (option == 5) { // Find the Shelter by decreasing Chiral Number
				Instance.findShelter();
			}
			else { // Invalid Option
				System.out.println("That option does not exist.");
			}
		}		
	}
}
