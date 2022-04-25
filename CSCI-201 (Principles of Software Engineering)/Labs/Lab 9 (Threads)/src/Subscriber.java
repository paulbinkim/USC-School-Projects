import java.util.Random;
import java.util.concurrent.*;

public class Subscriber extends Thread
{
	MessageQueue temp;
	public Subscriber(MessageQueue Bank) {
		this.temp = Bank;
	}
	
	public void run() {
		int i = 0;
		Random rand1 = new Random();
		while (i != 20) {
			int timer = rand1.nextInt(1000);
			
			try {
				Thread.sleep(timer);
			} 
			catch (InterruptedException ex) {
			}
			
			
			String temp2 = temp.getMessage();
			String time = Util.getDate();
			
			if (temp2 != "") {
				System.out.println(time + " Subscriber: Read Message - " + temp2);
				i++;
			}
			else {
				System.out.println(time + " Subscriber: Read Message - No Message");
			}
		}
	}

}

// Query the messages in the specified Message Queue
// Takes the Message Queue in its constructor 
// in the run() query by calling getMessage)
// continue to query in a loop until it has read 20
// messages. Should sleep after attempting to read a message.
// If there is no message, do not increment the number of read messages
// Ensure that 20 messages will be read.
// Output each message to the console after it has
// been read, along with a time stamp.