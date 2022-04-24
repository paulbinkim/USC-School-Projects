import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.text.ParseException;
import java.util.*;
import java.util.concurrent.*;

import com.google.gson.Gson;
import com.google.gson.JsonParseException;
import com.google.gson.reflect.TypeToken;
import com.google.gson.stream.JsonReader;
import com.google.gson.GsonBuilder;

// Main Class
public class PA3 {
	// Initializing and Declaring Variables
	private static String JSONname; // JSON name
	private static String CSVname; // CSV name
	private static Schedule Schedule1; // Schedule Variable
	private static int brokers = 0; // Total Number of Brokers/Threads
	
	// Used to check if file exists
	private Boolean JsonFileExists = false;
	private Boolean CSVFileExists = false;
	
	// Complex Data Structures
	private ArrayList <Stock> StockList; // Holds Data from JSON (Stock Objects)
	private static Map<String, Semaphore> semaphoreMap; // Used for Initialize Semaphore
	private static Map<String, ArrayList<Stock>> TempStorage; // Used for reading object in JSON
	
	 /**
	  * Read Stock Json File inputed by user using GSON
	  */
	
    private void readStockFile() {
    	JsonFileExists = true;
		try {
			// "How to Read JSON from a File using GSON" (Online Documentation) (Same as PA1)
			JsonReader file = new JsonReader(new FileReader(JSONname));
			TempStorage = new Gson().fromJson(file, new TypeToken<Map<String, ArrayList<Stock>>>() {
            }.getType());
			StockList = TempStorage.get("data"); // Since JSON has key
			
			// Validation for an Empty GSON File
			if (StockList.size() == 0) { // Empty File
				throw new IllegalArgumentException();
			}
			
			for (int i = 0; i < StockList.size(); i++) {
				// Error Checking (If Data Fields are Empty or Invalid)
				if (StockList.get(i).getName() == null || StockList.get(i).getTicker() == null || StockList.get(i).getStart() == null || StockList.get(i).getBroker() < 0 || StockList.get(i).getDescription() == null || StockList.get(i).getExchange() == null) {
					throw new NullPointerException();
				}	
				if(StockList.get(i).getName().length() == 0 || StockList.get(i).getTicker().length() == 0 || StockList.get(i).getStart().length() == 0 || StockList.get(i).getDescription().length() == 0 || StockList.get(i).getExchange().length() == 0){
					throw new NullPointerException();
				}
				brokers += StockList.get(i).getBroker(); // Captures total number of brokers
			}
		}
		catch(NullPointerException e) {
			JsonFileExists = false;
			System.out.println("The GSON format in " + PA3.JSONname + " is missing data fields.\n");
		}
		catch (JsonParseException e) {
			JsonFileExists = false;
			System.out.println("The GSON format in " + PA3.JSONname + " could not be parsed.\n");
		}
		catch(FileNotFoundException e) { // File cannot be found
			JsonFileExists = false;
			System.out.println("The file " + PA3.JSONname + " could not be found.\n");
		}
		catch (IllegalArgumentException e) { // File is invalid
			JsonFileExists = false;
			System.out.println("The file" + PA3.JSONname + " has illegal arguments found.\n");
		}
		catch (Exception e) { // General Exception
			JsonFileExists = false;
			System.out.println("There is an exception (some error)!!!\n");
		}
    }

    /**
     * Read Stock Trades CSV File inputed by user
     */
    private void readScheduleFile() { // Similar Exceptions to PA1 and JSON Parser
    	CSVFileExists = true;
    	Schedule1 = new Schedule();
		try {
			String substr = CSVname.substring(CSVname.length()-3);
			if (substr == "csv") {
				System.out.println(substr);
				throw new FileNotFoundException();
			}
			BufferedReader file = new BufferedReader(new FileReader(CSVname));
			String line = file.readLine();
			while (line != null) {
				String[] Parsed = line.split(",");
				// Get Rid of White Spaces
				for (int i = 0; i < Parsed.length; i++) {
					Parsed[i] = Parsed[i].trim();
					Parsed[i] = Parsed[i].replaceAll("[^\\p{ASCII}]", ""); // Stack Overflow and Piazza for first line error
				}
				
				// Check if Correct Data Types
				int Start = 0, Count = 0;
				try {
					Start = Integer.parseInt(Parsed[0]);
					Count = Integer.parseInt(Parsed[2]);
				}
				catch (NumberFormatException e) {
					System.out.println("First and/or Third Parameter of CSV cannot be parsed to Integer.");
					return;
				}
				
				if (Parsed[1] == "" || Parsed[1] == null) {
					throw new NullPointerException();
				}
				String Ticker = Parsed[1];
				
				try {
					Schedule.Task temp = new Schedule.Task(Start, Ticker, Count);
					Schedule1.getBlockQueue().put(temp);
				}
				catch (InterruptedException e) {
					System.out.println("Concurrency Error adding CSV Data in Blocking Queue!");
					return;
				}
				line = file.readLine();
			}
		}
		catch(NullPointerException e) {
			CSVFileExists = false;
			System.out.println("The file " + PA3.CSVname + " is missing data fields.\n");
		}
		catch(FileNotFoundException e) { // File cannot be found
			CSVFileExists = false;
			System.out.println("The file " + PA3.CSVname + " could not be found or not CSV format.\n");
		}
		catch (IllegalArgumentException e) { // File is invalid
			CSVFileExists = false;
			System.out.println("The file" + PA3.CSVname + " has illegal arguments found.\n");
		}
		catch (Exception e) { // General Exception
			CSVFileExists = false;
			System.out.println("There is an exception (some error)!!!\n");
		}
    }

    /**
     *Set up Semaphore for Stock Brokers
     */
    private void initializeSemaphor() {
    	semaphoreMap = new HashMap<String, Semaphore>(); // Semaphors = Used to control the number of threads that can access a shared resource
    	for (int i = 0; i < StockList.size(); i++) {
    		Stock temp = StockList.get(i);
    		String Ticker = temp.getTicker();
    		int numBroker = temp.getBroker();
    		Semaphore sem1 = new Semaphore(numBroker); // Number of Brokers = Num of Trades (Processors)
    		semaphoreMap.put(Ticker, sem1); // Put in Map
    	}
    }

    // Main Call to Concurrency
    // Semaphore is stored in a Map where key is the ticker name, and value is the Semaphore with correct number of threads.
    private void executeTrades() throws InterruptedException {
    	ScheduledExecutorService exec = Executors.newScheduledThreadPool(brokers); // https://docs.oracle.com/javase/7/docs/api/java/util/concurrent/ScheduledExecutorService.html
    	BlockingQueue<Schedule.Task> Queue = Schedule1.getBlockQueue();
    	while (Queue.size() > 0){ // Queue will have X items
    		Schedule.Task task1 = Queue.take();
    		String Ticker = task1.getTicker();
    		int Start = task1.getStartTime();
    		//Trade(Schedule.Task task1, Schedule schedule1, Semaphore semaphore1)
    		Trade temp = new Trade(task1, Schedule1, semaphoreMap.get(Ticker));
    		exec.schedule(temp, Start, TimeUnit.SECONDS);
    	}
    	// End Executor Service
    	exec.shutdown();
    	while (!exec.isTerminated()) { // Good Practice
			Thread.yield();  // Causes the thread to pause temporarily and allow other threads to execute
		}
    	System.out.println("All trades completed!"); // We are done
    }

    // Main Call
    public static void main(String[] args) throws InterruptedException {
    	PA3 solution = new PA3(); // Create PA3 Object
    	while (solution.JsonFileExists == false) { // Json Parsing
    		System.out.println("What is the name of the file containing the company information?");
    		Scanner input1 = new Scanner(System.in); // Receieve Input
    		JSONname = input1.next();
    		solution.readStockFile();
    	}
    	System.out.println(" ");
    	while (solution.CSVFileExists == false) { // CSV Parsing
    		System.out.println("What is the name of the file containing the schedule information?");
    		Scanner input2 = new Scanner(System.in); // Receieve Input
    		CSVname = input2.next();
    		solution.readScheduleFile();
    	}
    	System.out.println(" ");
    	System.out.println("Starting execution of program...");
    	solution.initializeSemaphor(); // Initializing Semaphore
    	solution.executeTrades(); // Executing Trades
    }
}

// Piazza @856, @881 (it is okay if timestamps do not round properly and ordering doesn't matter if same time)
// File I/0 (20) (Good)
// Locks Implementation (20) (Good) (Used Semaphors)
// Scheduler Execution (60) (Good) // Piazza @881 (Order doesn;t matter for when tasks should occur at the same time with the +/- leniency)

// Completed