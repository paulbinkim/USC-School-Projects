/** **************************************************************************
 *                     The  generic Binary Search Tree class.
 *
 *****************************************************************************/

import java.util.*;
import java.io.*;
import java.net.*;

public class BST <T extends Comparable<T>> implements Cloneable, Iterable<T>
{
	private Node<T> root;
	
	public BST () {
		root = null;
	}
	
	public BST(Node<T> item) {
		root = item;
	}
	
	public int compareTwoNodes (Node<T> x, T y) {
		return x.data.compareTo(y); // CompareTo is a predefined method in Java
	}
	

/*****************************************************
*            INSERT
******************************************************/
   public void insert(T data)
   {
		root = recursiveInsert(this.root, data);
   }
   
   public Node<T> recursiveInsert(Node<T> root, T toSearch) {
	   if (root == null) {
		   Node<T> newNode = new Node<T> (toSearch);
		   return newNode;
	   }
	   int tempValue = compareTwoNodes(root, toSearch);
	   //System.out.print(tempValue);
	   
	   // Will be no duplicates
	   
	   if (tempValue < 0) {
		   root.right = recursiveInsert(root.right, toSearch);
	   }
	   else if (tempValue > 0) {
		   root.left = recursiveInsert(root.left, toSearch);
	   }
	   return root;
   }


/*****************************************************
*            SEARCH
******************************************************/
   public boolean search(T toSearch)
   {
      boolean solution = recursiveSearch(this.root, toSearch);
      return solution;
   }
   
   public boolean recursiveSearch(Node<T> root, T toSearch) {
	   if (root == null) {
		   return false;
	   }
	   else {
		   if (root.data == toSearch) {
			   return true;
		   }
		   
		   int tempValue = compareTwoNodes(root, toSearch);
		   if (tempValue == 0) {
			   return true;
		   }
		   else if (tempValue > 0) {
			   return recursiveSearch(root.left, toSearch);
		   }
		   else if (tempValue < 0){
			   return recursiveSearch(root.right, toSearch);
		   }
	   }
	   return false;
   }
   // Super buggy


/*****************************************************
*           CLONE
******************************************************/

	public BST<T> clone()
	{
		if (root == null) {
			return null;
		}
		BST<T> twin = new BST<T>();
		twin.root = cloneTree(root);
		return twin;
	}
	
	public Node<T> cloneTree(Node<T> root1) {
		if (root1 == null) {
			return null;
		}
		Node<T> newNode = new Node (root1.data, null, null); // New copy
		newNode.left = cloneTree(root1.left);
		newNode.right = cloneTree(root1.right);
		return newNode;
		
	}
	

/*****************************************************
*            TREE ITERATOR
******************************************************/

   public Iterator<T> iterator()
   {
      return new BSTIterator();
   }
   
   private class BSTIterator implements Iterator<T> {
	   private Stack<Node <T>> stack1 = new Stack<Node <T>>();
	   
	   public BSTIterator() {
		   pushAll(root);
	   }

		@Override
		public boolean hasNext() {
			return !stack1.isEmpty();
		}
	
		@Override
		public T next() {
			Node<T> tempNode = stack1.pop();
			pushAll(tempNode.right);
			return tempNode.data;
		}
		
		private void pushAll(Node<T> node) {
			for (; node != null; stack1.push(node), node = node.left);
		}
	   
   }
   
   
/*****************************************************
*            HEIGHT
******************************************************/

	// Returns the height of the tree
	public int height()
	{
		 return height(root);
	}
	private int height(Node<T> p)
	{
		return (p == null)?-1: 1+Math.max(height(p.left), height(p.right));
	}

/*****************************************************
*            Node class
******************************************************/

	private class Node<T>
	{
		private T data;
		private Node<T> left, right;

		/**
		*  Constructor builds the Node<T> with the supplied parameter
		*/
		public Node(T data)
		{
			left = right = null;
			this.data = data;
		}

		/**
		*  Constructor builds the Node<T> with the supplied parameter
		*/
		public Node(T data, Node<T> l, Node<T> r)
		{
			left = l; right = r;
			this.data = data;
		}

		/**
		*  Returns string representation of the object
		*/
		public String toString()
		{
			return data.toString();
		}
	}

	public static void main (String[] args )  throws IOException
	{
		BST<Integer> tree = new BST<Integer>();
		int[] ar = {6,5,1,4,3,2,9, 8};
		for (int x : ar) tree.insert(Integer.valueOf(x));
		BST<Integer> twin = (BST<Integer>) tree.clone();
		tree.insert(new Integer(201));
		for (Integer x : tree) System.out.print(x +",");
		System.out.println();
		for (Integer x : twin) System.out.print(x +",");
		System.out.println();
		System.out.println("the tree height is " + tree.height());
		URL url = new URL("https://viterbi-web.usc.edu/~adamchik/dictionary.txt");
		Scanner sc = new Scanner( url.openStream() );
		BST<String> dict = new BST<String>();
		while( sc.hasNext () ) dict.insert(sc.next());		
		System.out.println(dict.search("integer"));
		System.out.println(dict.search("Integer"));
		int count = 0;
		for (String str : dict) count++;
		System.out.println("the dictionary size is " + count);
		System.out.println("the dictionary height is " + dict.height());
	}
}
