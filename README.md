# Word_Finder
Word_Finder is a program that finds the words in a file that starts with the user’s given input, one by one. A user provides a prefix and a file, and the program starts to iterate through the file and find the words that start with the prefix. First, it checks the file length. If it was more than 100, it returns an error. Then, the program starts to iterate through the file and finds the words one by one. Furthermore, there is an option for the user to specify whether he or she wants to continue the process after the program finds a word or not. If the user decides to have this option, after the program finds a word with the given prefix, it asks the user to know whether he or she wants to continue the process or not. Finally, the program prints the amount of the file that it has read.


## Inputs
Argv[1] = Prefix

Argv[2] = Path of the file

Argv[3] =  0, if the user wants to see all the words without any interruption.
1, if the user wants to enable the step by step option.

## Outputs
One or more words that start with the given prefix.


## What are the vulnerabilities?
There are two vulnerabilities in this program, 1) TOCTOU, and 2) Buffer Overflow. If the user decides to choose the option to see the words with an interruption between them, the program gets an input from the user after it finds each word. If the user provides a bad response to the question, the program asks for the input again, and it sleeps for 50000 microseconds. Meanwhile, the user can change the text file to a very large file and overflow the buffer. By doing that, he or she can run a shellcode, which a user should not be able to do that.

### TOCTOU 
The program checks the input file’s length only at the first of the runtime. Therefore, it gives the user a chance to provide a small length file and change the file to a larger size one after the program’s check is completed.

### Buffer Overflow
Because the program checks the length of the file at the first of the process, it assumes the buffer will not be overflown.


## Step-by-step exploiting
### Step 1
Create a text file and write “ hi hey ” in it.
### Step 2
Run the program: “ word_finder h ./text.txt 1”
### Step 3	 
The program asks you to know if you want to continue the search or not. Change the text file in a way to overflow the buffer and rewrite the main’s return address. You can put a shellcode in the buffer and change the main’s return address in a way that the program’s flow returns to the shellcode, and runs it. The return address is in 0x7fffffffe428 address, and the buffer is in 0x7fffffffe170. Therefore, you have to put the buffer with some nop sleds (‘\x90’) and shellcode 
**_NOTE:_** The numbers are different in different systems.
### Step 4
Finally, provide a bad response at least once.
