import java.util.concurrent.*;

public class MessageTest
{
	public static void main(String [] args)
	{
		MessageQueue bank = new MessageQueue();
		ExecutorService executor = Executors.newFixedThreadPool(2);
		executor.execute(new Messenger(bank));
		executor.execute(new Subscriber(bank));
		executor.shutdown();
		while(!executor.isTerminated())
		{
			Thread.yield();
		}
	}
}

// Write our main.
// Create an instance for each of the class.
// Make sure to manage the threads using Executor Service.
// Add the Messenger and Subscriber to the newly created Executor
// Make sure to call shutdown() after adding the two threads.
// Use isTerminated() to help determine if the two tasks are finished.
// Thread.yield() will allow threads to finish in a timely manner. 