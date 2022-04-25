import java.util.Random;
import java.util.concurrent.*;


public class Messenger extends Thread
{
	MessageQueue temp;
	public Messenger(MessageQueue Bank) {
		this.temp = Bank;
	}
	
	public void run() {
		for (int i = 0; i < 20; i++) {
			String temp2 = Util.getDate();
			temp.addMessage("Message - " + String.valueOf(i));
			Random rand1 = new Random();
			int timer = rand1.nextInt(1000);
			System.out.println(temp2 + " Messenger: Insert Message - " + String.valueOf(i));
			try {
				Thread.sleep(timer);
			} 
			catch (InterruptedException ex) {
				
			}
		}
	}
}

// Goal is to add messages to the specified Message Queue.
// Takes a MessageQueue as a parameter in its constructor, and later
// adds to that MessageQueue when it is its turn to run.
// In the run() method
	// Write a loop that iterates 20 times and inserts a different
	// message into the MessageQueue each time.
	// Can be whatever (make sure to include unique identifier)

// After inserting each message, the Messenger should sleep for a
// random amount of time between 0-1 seconds calling Thread.sleep().

// Upon inserting a new message into the MessageQueue, print the 
// inserted message, along with a timestamp, to the console.
// Make sure the outputs are distinct