## General Program Structure

### Item Number
In order to generate and use the unique item number, there is an entire class and header file whos sole purpose is 
to store the item number. This is necessary because having the correct item number is important in several different classes.

### Editing, Adding, Deleting
This program comprises of two major halves of a database: 'Bills' and 'Bill Division'. Both of these halves have their own seperate Qlist and tablemodel.
Every time a user adds or edits a bill, that corresponding bill also gets changed in the list. Editing can only be 
done through the 'Bills' portion of the database, and then we update the 'Bill Division' half of the database accordingly since all bill division 
does is calculation. This means the user only ever directly inputs and edits information from the 'Bills' data.

Any deletion, addition, or editing done to the database is accurately reflected on both sides, with editing requiring a re-calculation
of the division for 'Bill Division'. This is done simply by calling the modular 'peopleTabAdd' function, which calculates and stores
the necessary information in the row given.

### Rent and Utilities Treatment
This program treats both rent and utilities in seperate columns, with each column having its own respective total and remainder.
This is due to the nature in which im going to use this program, as the rent and the utilities are paid for by different people. Since
I saw no harm in slightly seperating these two (since the total due per person is also still calculated) I have seperated them.

### Cent Calculation
This program accounts for cents, as such the way I calculated them (because computers suck at counting floating point numbers) is with 
the following psuedocode:

```c++
floatingTruncated=round(100*floatingNumber);
intNumber=(int)floatingTruncated;
```

This leaves a few useful variables around, such as intNumber for checking equality, or floatingTruncated to easily store back into a double.
Is there a simpler way to do this? Possibly, however since anything involving cents is stored in a double, I was forced to use floating-point
numbers. (Which honestly isn't that bad, it helped me practice a lot of things I have forgotten about math).

### Divison Logic
The logic for dividing between 4 people is done as such:

					Is the rent more than 4 cents?
					/			   \
					no			    yes
				      /			              \
				Add it to extra cents  	           Is it divisble by 4?
								  /			\
							        no			yes
							       /			  \
					Grab remainder, add it to extra cents,		Divide rent by 4, add it to rent per person,
					subtract the remainder from rent, divide	add '0' in extra cents.
					rent between 4 people, add it to rent per person.


The same basic logic structure governs how utilities total is handled, just with minor necessary tweaks.
By the end of both calculations, both rent and utilities total are divisible by 4. Since adding two
multiples of 4 also yields a multiple of 4, I can simply add both together and divide by 4 and get the total
due 'per person'.
						  
### Saving and Loading 	
Saving and loading files are done in two seperate functions. Saving simply saves the entire list, item by item, into the file.
Loading manually grabs each item and sends it to the "AddItem" function to avoid having to repeat code. When loading, however,
the files' items are in the opposite order in that they where originally saved as, so reversing the list is a must.

