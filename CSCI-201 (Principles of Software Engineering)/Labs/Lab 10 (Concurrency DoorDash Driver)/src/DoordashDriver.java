/**
 ******************************************************************************
 *                    LAB 10
 ******************************************************************************

  Implements the run for one driver.
  The Driver serves customers from the same pool, and the number of available spots in the app's queue is set to three.
  Implement methods in the class.

 *****************************************************************************/

import java.util.*;
import java.util.concurrent.*;
import java.util.concurrent.locks.*;

public class DoordashDriver extends Thread
{
	private ArrayList<Customer> customersWaiting = new ArrayList<Customer>();
	private Lock driverLock = new ReentrantLock();
	private Condition sleepingCondition = driverLock.newCondition();
	private Boolean condition = true;
	private Customer customer = null;
	
	public DoordashDriver() { // Constructor invokes .start()
		this.start();
	}

	public synchronized boolean addCustomerToWaiting(Customer customer)
	{
		/*
		 * Your code here
		 */
		if (customersWaiting.size() == 3) { // 3 is the capacity of customers
			return false;
		}
	
		Util.printMessage("Customer " + customer.getCustomerName() + " is waiting");
		String customersString = "";
		/*
		 * Your code here
		 */
		customersWaiting.add(customer);
		for (int i = 0; i < customersWaiting.size(); i++) {
			customersString += customersWaiting.get(i).getCustomerName();
			if (i < customersWaiting.size()-1) {
				customersString += ",";
			}
		}
		Util.printMessage("Customers currently waiting: " + customersString);
		return true;
	}

	public void wakeUpDriver() {
		try {
			driverLock.lock();
			sleepingCondition.signal();
		}
		finally {
			driverLock.unlock();
		}
	}

	public void run() {
		while(condition) {
			while(!customersWaiting.isEmpty()) {
				customer = customersWaiting.remove(0);
				//System.out.println(customer);
				customer.startingDelivery();
				try {
					Thread.sleep(1000);
				}
				catch (InterruptedException e) {
					System.out.println("Exception");
				}
				customer.finishingDelivery();
				Util.printMessage("Checking for more customers...");
			}
			try {
				driverLock.lock();
				Util.printMessage("No customers, so time to sleep...");
				sleepingCondition.await();
				Util.printMessage("Someone woke me up!");
			} catch (InterruptedException ie) {
				System.out.println("ie while sleeping: " + ie.getMessage());
			}      
			finally {
				driverLock.unlock();
			}
		}
	}
}
