import java.util.*;

public class MessageQueue
{
	private ArrayList<String> messages;
	
	public MessageQueue()
	{
		this.messages = new ArrayList<String>();
	}

	public void addMessage(String s)
	{
		this.messages.add(s);
	}

	public String getMessage()
	{
		if (this.messages.size() > 0)
		{
			return this.messages.remove(0);
		}
		return "";
	}
}

// Contains an ArrayList that allows inserting and removing.
// void addMessage adds a new message string to the end of the queue.
// String getMessage removes and returns the first message in the queue.

// Completed