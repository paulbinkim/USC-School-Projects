import java.util.concurrent.*;

public class Trade extends Thread {
	// Create Trade Class used in "executeTrade()"
	Schedule.Task task1;
	Schedule schedule1;
	Semaphore semaphore1;

	public Trade(Schedule.Task task1, Schedule schedule1, Semaphore semaphore1) {
		this.task1 = task1;
		this.schedule1 = schedule1;
		this.semaphore1 = semaphore1;
    }

	/**
	 * Trading function using locks
	 */
	public void run() {
		try {
			// Starting (Acquire Lock)
			semaphore1.acquire();
			if (task1.getCount() > 0) { // Purchase
				System.out.println("[" + Utility.getZeroTimestamp() + "]" + " Starting purchase of " + Math.abs(task1.getCount()) + " stocks of " + task1.getTicker());
			}
			else { // Sale
				System.out.println("[" + Utility.getZeroTimestamp() + "]" + " Starting sale of " + Math.abs(task1.getCount()) + " stocks of " + task1.getTicker());
			}
			
			Thread.sleep(1000); // Each Stock Action takes 1 second (1000 MS)
			
			// Finished
			if (task1.getCount() > 0) { // Purchase
				System.out.println("[" + Utility.getZeroTimestamp() + "]" + " Finished purchase of " + Math.abs(task1.getCount()) + " stocks of " + task1.getTicker());
			}
			else { // Sale
				System.out.println("[" + Utility.getZeroTimestamp() + "]" + " Finished sale of " + Math.abs(task1.getCount()) + " stocks of " + task1.getTicker());
			}
		}
		catch (InterruptedException e) {
			System.out.println("Some Exception (Interrupted Exception");
			return;
		}
		finally { // Always want to do this (lecture) (Release Semaphore)
			semaphore1.release();
		}
	}
}

// Completed
