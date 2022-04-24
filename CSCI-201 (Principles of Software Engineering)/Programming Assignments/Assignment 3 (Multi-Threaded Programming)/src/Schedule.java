import java.util.concurrent.*;

/** 
 * Stock Trades Schedule 
 * Keep the track of tasks
*/
public class Schedule {
	// Blocking Queue, allows multiple threads to be inserted and taken concurrently (Lecture Reference)
	private BlockingQueue<Task> Queue; 
	
    public Schedule() {
    	this.Queue = new LinkedBlockingQueue<Task>(); // LinkedBQ doesn't need a size, whereas Array's size needs to be declared
    }
    
    public BlockingQueue<Task> getBlockQueue() {
    	return this.Queue;
    }
  
    /**
     * Inner class to store task object
     */
    public static class Task {
    	private int startTime;
    	private String Ticker;
    	private int countStock;
    	
    	// Constructor
        public Task(int startTime, String Ticker, int countStock) {
        	this.startTime = startTime;
        	this.Ticker = Ticker;
        	this.countStock = countStock;
        }
        
        // Getters and Setters
        public int getStartTime() {
        	return this.startTime;
        }
        
        public String getTicker() {
        	return this.Ticker;
        }
        
        public int getCount() {
        	return this.countStock;
        }
        
        public void setStartTime(int startTime) {
        	this.startTime = startTime;
        }
        
        public void setTicker(String ticker) {
        	this.Ticker = ticker;
        }
        
        public void setCount(int countStock) {
        	this.countStock = countStock;
        }
    }
}

// Completed