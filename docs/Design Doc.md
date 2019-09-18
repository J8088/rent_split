## General Program Structure

In order to generate and use the unique item number, there is an entire class and header file whos sole purpose is 
to store the item number. This is necessary because having the correct item number is important in several different classes.

This program comprises of two major halves of a database: 'Bills' and 'Bill Division'.Both of these halves have their own seperate Qlist and tablemodel.
Every time a user adds or edits a bill, that corresponding bill also gets changed in the list. Editing can only be 
done through the 'Bills' portion of the database, and then we update the 'Bill Division' half of the database accordingly since all bill division 
does is calculation. This means the user only ever directly inputs and edits information from the 'Bills' data.

Any deletion, addition, or editing done to the database is accurately reflected in both sides, with editing requiring a re-calculation
of the division for 'Bill Division'. This is done simply by calling the modular 'peopleTabAdd' function, which calculates and stores
the necessary information in the row given.

This program accounts for cents, as such the way I calculated them (because computers suck at counting floating point numbers) is with 
the following psuedocode:

```c++
floatingTruncated=round(100*floatingNumber);
intNumber=(int)floatingTruncated;
```

This leaves a few useful variables around, such as intNumber for checking equality, or floatingTruncated to easily store back into a double.
Is there a simpler way to do this? Possibly, however since anything involving cents is stored in a double, I was forced to use floating-point
numbers. (Which honestly isn't that bad, it helped me practice a lot of things I have forgotten about math).

The logic for dividing between 4 people is done as such:

						Is the rent more than 4 cents?
						/			\
					       no			yes
					      /			           \
					add it to extra cents  	           is it divisble by 4?
									/			\
								       no			yes
								      /				\
					grab remainder, add it to extra cents,
					subtract the remainder from rent, divide
					rent between 4 people, add it to rent per person.
							  
 	
Saving and loading files are done in two seperate functions. Saving simply saves the entire list, item by item, into the file.
Loading manually grabs each item and sends it to the "AddItem" function to avoid having to repeat code. When loading, however,
the files' items are in the opposite order in that they where originally saved as, so reversing the list is a must.

To calculate the overall total of the database, I have saved each individual "total" in a map, with its corresponding item number being its key.
(I recognize that this is redundant, as the total is already in Qlist and I can simply iterate addition. Will change this in future update.)

Cents aren't supported due to my original client not requesting such a feature, as nearly all items are bought in flat dollars.
