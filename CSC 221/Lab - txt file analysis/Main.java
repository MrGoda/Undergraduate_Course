/**
* Project 1 - CSC 221 Spring 2020
* Honor Pledge:
* The code submitted for this project was developed by
* Patrick Fan without outside assistance or consultation 
* except as allowed by the instructions for this project.
* 
*/

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class Main 
{
	public static int midPoint; //used by binarySearch method
	
	public static void main(String[] args)
	{
		int shingleLength = 0; //length k of each shingle
		ArrayList<Node> aList = new ArrayList<>();

		try
		{
			shingleLength = Integer.parseInt(args[0]);
			//assert that shingleLength should be more than zero or the program halts
			assert(shingleLength > 0): "The length of shingle should be more than 0"; 
		}
		catch (NumberFormatException nfe)
		{
			System.out.println("There exists a NumberFormatException: " + nfe.getMessage());
		}
		
		//Extract lines from a file, store into an ArrayList
		try
		{
			FileReader file = new FileReader(args[1]); //Read file name
			try 
			{
				String s = "";
				
				for (int i = file.read(); i != -1; i = file.read()) 
				{
					//if character read is not a part of the characters read below, abort
					assert (i >= 32 && i <= 126 || i == 10 || i == 13): "Character read not a part of recognized commands, contact administrator for immediate upgrade";
					
					//Conditions for extracting the character
					if (i != 10 && i != 13) 
					{
						if (i >= 97 && i <= 122) //a-z
						{
							s = s + (char) i;
						}
						else if (i >= 65 && i <= 90) //A-Z
						{
							i += 32; //all characters are converted to lower cases
							s = s + (char) i;
						}
						//Replace all characters other than a-z with a single space
						else if ((i >= 32 && i <= 64) || (i >= 91 && i <= 96) || (i >= 123 && i <= 126)) 
						{
							i = 32;
							s = s + (char) i;
						}
					}
					else if (i == 10 || i == 13) //end of line or vertical tab
					{
						if (!s.isEmpty()) //not an empty line
						{
							s = s + " "; //a single space is added to the end
							s = clean(s); //"Clean" a line
							
							Insert(aList, s, shingleLength); //line with length 0 will input nothing into the list
						}	
						s = ""; //reset String s so there is no word in it
					}
				} 
			} 
			catch (IOException IOe) 
			{
				System.out.println("IOException");
			}
			
		}
		catch (FileNotFoundException e)
		{
			System.out.println("File not found! Please check if the address of the file is correctly stated.");
		}	
		
		//Output of shingles and its counts
		int i, sumCount;
		for (i = 0, sumCount = 0; i < aList.size(); i ++)
		{
			sumCount += aList.get(i).getCount();
			System.out.println(aList.get(i).toString());
		}
		
		//Summary of processing the result
		System.out.println("\nThe file " + args[1] + " contains " + sumCount + " total shingles of length " + shingleLength + " including " + aList.size() + " distinct shingles.\n\n");
		
		//testing of node
		testNode(new Node("dear",1 ));
	}	

	//clean String s through replacing all sequences of multiple spaces by a single space
	private static String clean(String s) 
	{
		int spaceIndex1 = s.indexOf(32);
		int spaceIndex2;
		if (spaceIndex1 != -1) //make sure there is at least one space in the line
		{
			spaceIndex2 = s.indexOf(32, spaceIndex1 + 1);
			
			while (spaceIndex2 != -1)
			{
				if (spaceIndex2 - spaceIndex1 == 1)
				{
					//two or more consecutive spaces are reduced to just one
					s = s.substring(0, spaceIndex2) + s.substring(spaceIndex2 + 1, s.length());
					spaceIndex2 = s.indexOf(32, spaceIndex1 + 1); //next loop
					
				}
				else //run the next loop
				{
					spaceIndex1 = spaceIndex2;
					spaceIndex2 = s.indexOf(32, spaceIndex1 + 1);
					
				}
			}
			return s;
					
		}
		else
		{
			return s;
		}
	}
	
	//Method that inserts all word with shingleLength into aList
	private static void Insert(ArrayList<Node> aList, String s, int shingleLength)
	{
		int spaceIndex1 = -1;
		int spaceIndex2;
		
		spaceIndex2 = s.indexOf(32, spaceIndex1 + 1);
		
		while (spaceIndex2 != -1)
		{
			String temp = s.substring((spaceIndex1 + 1), spaceIndex2); //Separate one word from the line
			if (temp.length() == shingleLength) //if the length fits, fit this word into ArrayList
			{
				Node nodeTemp = new Node(temp, 1);
				if (aList.isEmpty())
				{
					aList.add(nodeTemp);
				}
				else if (! aList.isEmpty())
				{
					int insertionIndex = binarySearch(aList, 0, aList.size() - 1, nodeTemp);
					if (insertionIndex >= 0)
					{
						aList.get(insertionIndex).increaseCount();
						//(insertionIndex, new Node(aList.get(insertionIndex).getData(), aList.get(insertionIndex).getCount() + 1));
					}
					else if (insertionIndex < 0)
					{
						if (nodeTemp.compareTo(aList.get(-(insertionIndex + 1))) > 0)
						{
							aList.add(-(insertionIndex + 1) + 1, nodeTemp);
						}
						else if (nodeTemp.compareTo(aList.get(-(insertionIndex + 1))) < 0)
						{
							aList.add(-(insertionIndex + 1), nodeTemp);
						}
					}
				}
			}	
			spaceIndex1 = spaceIndex2;
			spaceIndex2 = s.indexOf(32, spaceIndex1 + 1); //reset for the new round of loop
		}
	}
	
	//Method that do binary search through ArrayList aListTemp
	private static int binarySearch(ArrayList<Node> aListTemp, int start, int end, Node n) //return the index of ArrayList where Node n is found, "-1" if not found
	{
		if (end >= start)
		{
			midPoint = start + (end - start) / 2;
			if (n.compareTo(aListTemp.get(midPoint)) == 0)
			{
				return midPoint;
			}
			else if (n.compareTo(aListTemp.get(midPoint)) > 0)
			{
				return binarySearch(aListTemp, midPoint + 1, end, n);
			}
			else if (n.compareTo(aListTemp.get(midPoint)) < 0)
			{
				return binarySearch(aListTemp, start, midPoint - 1, n);
			}
		}
		return (- midPoint - 1); 	//negative value implies that there is no Node with same data name in aList as n does. 
									//midPoint being the value that Node n will be inserted between
									//need to -1 from - midPoint because value "0" could be either positive or negative
	}

	//method used to debug the code
	public static void testNode(Node n)
	{
		System.out.println("The data of this test node is: " + n.getData());
		System.out.println("The count of this test node is: " + n.getCount());
		n.increaseCount();
		System.out.println("The count of this test node is: " + n.getCount());
		Node n1 = new Node("worry", 1);
		Node n2 = n;
		System.out.println("When compared to another node with data 'worry', the result is: " + n.compareTo(n1));
		System.out.println("When compared to another node which is a duplicate of this node, the result is: " + n.compareTo(n2));
		System.out.println("The string representation of this node is: " + n.toString());
	}
}


class Node implements Comparable<Node>
{
	private String data; //A String instance variable to store a shingle of length k
	private int count;	/*An int instance variable to keep count of how many 
						times the shingle has appeared in the text; I called mine count*/
	public Node(String s, int i)
	{
		data = s;
		count = i;
	}
	
	//getter
	public String getData()
	{
		return data;
	}
	
	public int getCount()
	{
		return count;
	}
	
	public void increaseCount()
	{
		count ++;
	}
	
	public int compareTo(Node n)
	{
		Boolean b;
		if (data.equals(n.getData())) //two Strings equal
		{
			return 0;
		}
		else if (data.compareTo(n.getData()) < 0) //the instance String comes before the other
		{
			return -1;
		}
		else if (data.compareTo(n.getData()) > 0) //the instance String comes after the other
		{
			return 1;
		}
		return 0;
	}
	
	public String toString()
	{
		String s = "There are " + count + " shingles that has the same name called: " + data;
		return s;
	}
}