/**
 ******************************************************************************
 *                    LAB 10
 ******************************************************************************

Implement the main method()
               
Instantiate a Door dash Driver thread and use ExecutorService to manage Customer Threads. Shut down the service once the 
driver finishes serving the customer.

 *****************************************************************************/

import java.util.*;
import java.util.concurrent.*;
import java.util.concurrent.locks.*;

public class Lab10
{
	public static final int totalCustomers = 15;
	public static final int totalSpots = 3; //waiting queue

	public static void main(String [] args)
	{
		DoordashDriver Driver1 = new DoordashDriver(); // Instantiate a Doordash Driver Thread
		ExecutorService exec = Executors.newCachedThreadPool(); // Create an Executor Service Object to Manage Customer Threads
		for (int i = 1; i <= totalCustomers; i++) { // Loop for 15 Total Customers starting from 1
			Customer customer = new Customer(i, Driver1); // Create Customer Object
			exec.execute(customer); // Executes Thread
			try {
				Random rand = new Random();
				int TimeCustomers = rand.nextInt(2000);
				Thread.sleep(TimeCustomers); // Wait some time and repeat
			}
			catch (InterruptedException e) {
				System.out.print("Exception");
			}
		}
		exec.shutdown(); // Once 15 customers are created shut down the service
		while (!exec.isTerminated()) { 
			Thread.yield();  // Causes the thread to pause temporarily and allow other threads to execute
		}
		Util.printMessage("No more customers ordering today...");
		Util.printMessage("All done for today!  Time to go home!");
		Driver1.wakeUpDriver();
	}
}
