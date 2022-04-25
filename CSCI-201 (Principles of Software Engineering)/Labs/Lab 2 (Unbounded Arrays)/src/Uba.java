/*
 * Lab02.
 *
 *
*  Adding extra helper functions is allowed and would be a good idea.
 * Extra class variables can be added but are not required to solve this lab.
 *
 * It's always a good idea to split your logic into multiple functions since each
 * function should ideally do one thing and do it well.
 *
 * Good luck! Have fun! (If you're not having fun ask CPs for help :-)
*/


// Create a data structure for an unbounded array (similar to vector)
// Must resize explicitly and allocate more memory whenever you have hit the limit of allocated of memory
// Implement logic for the constructor, add, remove, and toString member functions

// Maintain an array and an internal index size
// When we add a new element, increment size.

// If array is full and want to add another element. Allocate a new array of a larger length (double length)
// and copy the elements we already have to the new array.


public class Uba<AnyType>  implements UbaInterface<AnyType>
{
    private static final int DEFAULT_CAPACITY = 5;

    private AnyType[] items;
    private AnyType[] temp;
    private int size; // the current number of elements in the array
    private int CurrentSize;

  /**
	*  Constructs an empty array of default capacity
	*/
	@SuppressWarnings("unchecked")
	public Uba()
	{	
		this.CurrentSize = 0;
		this.size = DEFAULT_CAPACITY;
		items = (AnyType[]) new Object[size]; // Initial Array of size 5
	}


  /**
	*  Adds an item to this collection, at the end.
	*/
	@SuppressWarnings("unchecked")
	public void add(AnyType x)
	{		
		if (CurrentSize == size) { // Means we need to resize
			temp = (AnyType[]) new Object[size];
			temp = items;
			size *= 2;
			items = (AnyType[]) new Object[size]; // new array of double the size
			for (int i = 0; i < temp.length; i++) {
				items[i] = temp[i];
			}
		}
		
		items[CurrentSize] = x;
		CurrentSize++;
	}

  /**
	*   Removes the last item from the list and returns it
	*/
	public AnyType remove()
	{
		CurrentSize--;
        return items[CurrentSize];
	}


  /**
	*  Returns a string representation
	*/
	@Override
	public String toString( )
	{	
		String solution = "[";
		for (int i = 0; i < CurrentSize; i++) {
			solution += items[i];
			if (i != CurrentSize-1) {
				solution += ", ";
			}
		}
		solution += "]";
        return solution;
	}

	public static void main(String[] args)
	{
		Uba<Integer> tmp = new Uba<Integer> ();
		System.out.println(tmp);

		for(int i = 0; i < 50; i++) tmp.add(i);
		System.out.println(tmp);

		System.out.println(tmp.remove());
		System.out.println(tmp);

		Uba< String > tmp1 = new Uba<String> ();
		for(int i = 0; i < 6; i++) tmp1.add("uba" + i);
		System.out.println(tmp1);

		System.out.println(tmp1.remove());
		System.out.println(tmp1);

	}

}