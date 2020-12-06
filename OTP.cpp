/// One-time pad - communicate using ciphertext of unlimited plausible deniability
/// Version 2, plausibility ratio = 1:95, number of plausible messages per ciphertext = 165,153,743,850,136,394,768,170,261,844,001,846,794,583,739,849,096,139,995,229,484,616,386,098,260,836,764,841,563,284,148,593,084,838,704,354,991,162,901,768,186,888,062,928,119,325,079,023,838,043,212,890,625
/// Guess-keys  decrypt all  ciphertext  into all the possible  plaintext
/// combinations while intended messages are known only by the key owners.
/// Nikolay Valentinovich Repnitskiy - License: WTFPLv2+ (wtfpl.net.)


/*This OTP is designed for 1+GB RAM while minimizing the use of type char and built-in C++ functions.
625,000 messages per user. Share multiple folders to have spare keys. Keys are irreversibly truncated
upon use (-320 total digits.) Plaintext is 80 characters max, randomness is appended to all plaintext
to get 80 characters. Ciphertext is always 80 characters. Key files contain digit pairs 00 - 94.
Mathematical proof: pdfhost.net/index.php?Action=Download&File=533e271b583e0243f3c6e07b13e02d63
Encryption/symbol: (plaintext + key.outgoing) mod 95. Decryption/symbol: (x + key.incoming) mod 95 = ciphertext.
Basic text files you should know about--both files are shared then only the generating party swaps their file names:
 * key.incoming  (generating party renames to key.outgoing for symmetry with the other party's key.incoming)  200MB
 * key.outgoing  (generating party renames to key.incoming for symmetry with the other party's key.outgoing)  200MB


How to run the program - Software package repositories for GNU+Linux operating systems have all the developer tools needed.
Open a terminal and use the following command as root to install  Geany  and  g++  on your computer:  apt install geany g++
Geany is a fast & lightweight text editor and Integrated Development Environment (IDE) in which you can write and run code.
g++ is the GNU compiler for C++ which allows written code to run. The compiler operates in the background automatically and
displays errors in your code as you will see in the lower box in Geany. Create a folder somewhere on your machine. Open Geany
and paste this code into the blank Geany page.  Now you can get code-highlighting and set this document as a C++ source file.
Go to Document >> Set Filetype >> Programming Languages >> C++ source file. (A good tip for clarity in auditing is to enable
the indentation guides for the block braces. Go to View >> Show Indentation Guides.) Save the file as anything.cpp within the
newly-created folder (Geany will automatically suggest the .cpp extension.) This folder is now the home directory of OTP.cpp
which will create, write to, and read from files within this folder.  And now you can build then run the program.  Use the
following Geany shortcuts in order:  F9,  F5.  Whenever it is you wish to use the OTP again, open  Geany  and use the same
shortcuts. This will work for any single C++ file whether you paste over the current code or open a new file and repeat.


Additional safety--if you happen to encrypt n messages in a row and send them in a wrong order or don't send them at all, let
them know the value of n so they can adjust the size of their  key.incoming  to match your key.outgoing (they should decrypt
80 zeros n times.)  If you forgot n,  send them a new non-random message and they'll decrypt it until the output makes sense.
	If you send encrypted messages containing seeds to be used by both parties to generate new  symmetric keys,  then perfect
secrecy is reduced to  guaranteed decryption difficulty  as the number of plausible  messages per ciphertext begins to narrow.
This applies to symmetric key transformations and operations with additional components such as transformation determinants. */


#include <cstdlib> //For rand() & srand() (user-defined seeds only.)
#include <fstream> //For file I/O (creates, writes to, and reads from ONLY the two files mentioned above.)
#include <iostream>
using namespace std;

int main()
{	cout << "\n(One-time pad)\n\n"
		 
		 << "(1) Encrypt\n"
		 << "(2) Decrypt\n"
		 << "(3) Get keys\n\n"
		 
		 << "Enter option: ";
		 
	int user_option;
	cin >> user_option;
	if((user_option != 1) && (user_option != 2) && (user_option != 3)) {cout << "\nInvalid, program ended.\n"; return 0;}
	//(You can run each of the three ifs holding options 1, 2, and 3, in isolation--they are self-sustained.)
	
	
	
	
	
	//                                                      1   Encrypt
	//_______________________________________________________________________________________________________________________
	if(user_option == 1)
	{	cout << "80 characters max (width of terminal.) Randomness will be appended if your\n"
			 << "message is less than 80, make it distinguishable from the noise. Enter message:\n\n";
		
		//If you entered a message and got the "No input visible" error, remove the following two lines of code.
		char nothing_to_see_here[1]; //This is here to catch the cached new line.
		cin.getline(nothing_to_see_here, 1);
		
		char plaintext[10000]; //Incase the user enters too many.
		for(int a = 0; a < 10000; a++) {plaintext[a] = '\0';} //Fills plaintext[] with null.
		cin.getline(plaintext, 10000);
		plaintext[80] = '\0'; //Message is truncated to 80 characters.
		
		if(plaintext[0] == '\0') {cout << "No input visible, program ended. See line 70 if input was given.\n"; return 0;}
		
		int plaintext_decimal[80];
		int plaintext_null_bookmark;
		for(int a = 0;; a++) //Converts plaintext to decimal. Pressing arrow keys in the terminal will trigger this else.
		{	if(plaintext[a] == '\0') {plaintext_null_bookmark = a; break;}
			
			     if(plaintext[a] == ' ') {plaintext_decimal[a] =  0;}
			else if(plaintext[a] == '!') {plaintext_decimal[a] =  1;}
			else if(plaintext[a] == '"') {plaintext_decimal[a] =  2;}
			else if(plaintext[a] == '#') {plaintext_decimal[a] =  3;}
			else if(plaintext[a] == '$') {plaintext_decimal[a] =  4;}
			else if(plaintext[a] == '%') {plaintext_decimal[a] =  5;}
			else if(plaintext[a] == '&') {plaintext_decimal[a] =  6;}
			else if(plaintext[a] =='\'') {plaintext_decimal[a] =  7;}
			else if(plaintext[a] == '(') {plaintext_decimal[a] =  8;}
			else if(plaintext[a] == ')') {plaintext_decimal[a] =  9;}
			else if(plaintext[a] == '*') {plaintext_decimal[a] = 10;}
			else if(plaintext[a] == '+') {plaintext_decimal[a] = 11;}
			else if(plaintext[a] == ',') {plaintext_decimal[a] = 12;}
			else if(plaintext[a] == '-') {plaintext_decimal[a] = 13;}
			else if(plaintext[a] == '.') {plaintext_decimal[a] = 14;}
			else if(plaintext[a] == '/') {plaintext_decimal[a] = 15;}
			else if(plaintext[a] == '0') {plaintext_decimal[a] = 16;}
			else if(plaintext[a] == '1') {plaintext_decimal[a] = 17;}
			else if(plaintext[a] == '2') {plaintext_decimal[a] = 18;}
			else if(plaintext[a] == '3') {plaintext_decimal[a] = 19;}
			else if(plaintext[a] == '4') {plaintext_decimal[a] = 20;}
			else if(plaintext[a] == '5') {plaintext_decimal[a] = 21;}
			else if(plaintext[a] == '6') {plaintext_decimal[a] = 22;}
			else if(plaintext[a] == '7') {plaintext_decimal[a] = 23;}
			else if(plaintext[a] == '8') {plaintext_decimal[a] = 24;}
			else if(plaintext[a] == '9') {plaintext_decimal[a] = 25;}
			else if(plaintext[a] == ':') {plaintext_decimal[a] = 25;}
			else if(plaintext[a] == ';') {plaintext_decimal[a] = 27;}
			else if(plaintext[a] == '<') {plaintext_decimal[a] = 28;}
			else if(plaintext[a] == '=') {plaintext_decimal[a] = 29;}
			else if(plaintext[a] == '>') {plaintext_decimal[a] = 30;}
			else if(plaintext[a] == '?') {plaintext_decimal[a] = 31;}
			else if(plaintext[a] == '@') {plaintext_decimal[a] = 32;}
			else if(plaintext[a] == 'A') {plaintext_decimal[a] = 33;}
			else if(plaintext[a] == 'B') {plaintext_decimal[a] = 34;}
			else if(plaintext[a] == 'C') {plaintext_decimal[a] = 35;}
			else if(plaintext[a] == 'D') {plaintext_decimal[a] = 36;}
			else if(plaintext[a] == 'E') {plaintext_decimal[a] = 37;}
			else if(plaintext[a] == 'F') {plaintext_decimal[a] = 38;}
			else if(plaintext[a] == 'G') {plaintext_decimal[a] = 39;}
			else if(plaintext[a] == 'H') {plaintext_decimal[a] = 40;}
			else if(plaintext[a] == 'I') {plaintext_decimal[a] = 41;}
			else if(plaintext[a] == 'J') {plaintext_decimal[a] = 42;}
			else if(plaintext[a] == 'K') {plaintext_decimal[a] = 43;}
			else if(plaintext[a] == 'L') {plaintext_decimal[a] = 44;}
			else if(plaintext[a] == 'M') {plaintext_decimal[a] = 45;}
			else if(plaintext[a] == 'N') {plaintext_decimal[a] = 46;}
			else if(plaintext[a] == 'O') {plaintext_decimal[a] = 47;}
			else if(plaintext[a] == 'P') {plaintext_decimal[a] = 48;}
			else if(plaintext[a] == 'Q') {plaintext_decimal[a] = 49;}
			else if(plaintext[a] == 'R') {plaintext_decimal[a] = 50;}
			else if(plaintext[a] == 'S') {plaintext_decimal[a] = 51;}
			else if(plaintext[a] == 'T') {plaintext_decimal[a] = 52;}
			else if(plaintext[a] == 'U') {plaintext_decimal[a] = 53;}
			else if(plaintext[a] == 'V') {plaintext_decimal[a] = 54;}
			else if(plaintext[a] == 'W') {plaintext_decimal[a] = 55;}
			else if(plaintext[a] == 'X') {plaintext_decimal[a] = 56;}
			else if(plaintext[a] == 'Y') {plaintext_decimal[a] = 57;}
			else if(plaintext[a] == 'Z') {plaintext_decimal[a] = 58;}
			else if(plaintext[a] == '[') {plaintext_decimal[a] = 59;}
			else if(plaintext[a] =='\\') {plaintext_decimal[a] = 60;}
			else if(plaintext[a] == ']') {plaintext_decimal[a] = 61;}
			else if(plaintext[a] == '^') {plaintext_decimal[a] = 62;}
			else if(plaintext[a] == '_') {plaintext_decimal[a] = 63;}
			else if(plaintext[a] == '`') {plaintext_decimal[a] = 64;}
			else if(plaintext[a] == 'a') {plaintext_decimal[a] = 65;}
			else if(plaintext[a] == 'b') {plaintext_decimal[a] = 66;}
			else if(plaintext[a] == 'c') {plaintext_decimal[a] = 67;}
			else if(plaintext[a] == 'd') {plaintext_decimal[a] = 68;}
			else if(plaintext[a] == 'e') {plaintext_decimal[a] = 69;}
			else if(plaintext[a] == 'f') {plaintext_decimal[a] = 70;}
			else if(plaintext[a] == 'g') {plaintext_decimal[a] = 71;}
			else if(plaintext[a] == 'h') {plaintext_decimal[a] = 72;}
			else if(plaintext[a] == 'i') {plaintext_decimal[a] = 73;}
			else if(plaintext[a] == 'j') {plaintext_decimal[a] = 74;}
			else if(plaintext[a] == 'k') {plaintext_decimal[a] = 75;}
			else if(plaintext[a] == 'l') {plaintext_decimal[a] = 76;}
			else if(plaintext[a] == 'm') {plaintext_decimal[a] = 77;}
			else if(plaintext[a] == 'n') {plaintext_decimal[a] = 78;}
			else if(plaintext[a] == 'o') {plaintext_decimal[a] = 79;}
			else if(plaintext[a] == 'p') {plaintext_decimal[a] = 80;}
			else if(plaintext[a] == 'q') {plaintext_decimal[a] = 81;}
			else if(plaintext[a] == 'r') {plaintext_decimal[a] = 82;}
			else if(plaintext[a] == 's') {plaintext_decimal[a] = 83;}
			else if(plaintext[a] == 't') {plaintext_decimal[a] = 84;}
			else if(plaintext[a] == 'u') {plaintext_decimal[a] = 85;}
			else if(plaintext[a] == 'v') {plaintext_decimal[a] = 86;}
			else if(plaintext[a] == 'w') {plaintext_decimal[a] = 87;}
			else if(plaintext[a] == 'x') {plaintext_decimal[a] = 88;}
			else if(plaintext[a] == 'y') {plaintext_decimal[a] = 89;}
			else if(plaintext[a] == 'z') {plaintext_decimal[a] = 90;}
			else if(plaintext[a] == '{') {plaintext_decimal[a] = 91;}
			else if(plaintext[a] == '|') {plaintext_decimal[a] = 92;}
			else if(plaintext[a] == '}') {plaintext_decimal[a] = 93;}
			else if(plaintext[a] == '~') {plaintext_decimal[a] = 94;}
			else
			{	cout << "\nDefective input, try again.\n";
				
				//Overwrites RAM of arrays plaintext[] and plaintext_decimal[].
				for(int a = 0; a < 80; a++)
				{	plaintext[a] = 9;
					plaintext[a] = 8;
					plaintext[a] = 7;
					plaintext[a] = 6;
					plaintext[a] = 5;
					plaintext[a] = 4;
					plaintext[a] = 3;
					plaintext[a] = 2;
					plaintext[a] = 1;
					plaintext[a] = 0;
					plaintext_decimal[a] = 9;
					plaintext_decimal[a] = 8;
					plaintext_decimal[a] = 7;
					plaintext_decimal[a] = 6;
					plaintext_decimal[a] = 5;
					plaintext_decimal[a] = 4;
					plaintext_decimal[a] = 3;
					plaintext_decimal[a] = 2;
					plaintext_decimal[a] = 1;
					plaintext_decimal[a] = 0;
				} //Only partially effective, printed/copied text is cloned from RAM.
				
				return 0;
			}
		}
		
		//Overwrites RAM of array plaintext[].
		for(int a = 0; a < 80; a++)
		{	plaintext[a] = 9;
			plaintext[a] = 8;
			plaintext[a] = 7;
			plaintext[a] = 6;
			plaintext[a] = 5;
			plaintext[a] = 4;
			plaintext[a] = 3;
			plaintext[a] = 2;
			plaintext[a] = 1;
			plaintext[a] = 0;
		} //Only partially effective, printed/copied text is cloned from RAM.
		
		//Key depletion check.
		ifstream in_stream;
		in_stream.open("key.outgoing");
		char depletion_check[1];
		in_stream >> depletion_check[0];
		in_stream.close();
		if((depletion_check[0] < 48) || (depletion_check[0] > 57)) {cout << "\nkey.outgoing has been depleted or doesn't exist.\n"; return 0;}
		
		//Loads file key.outgoing into array key_outgoing[].
		static char key_outgoing[200000000];
		int key_null_bookmark = 200000000;
		in_stream.open("key.outgoing");
		for(int a = 0; a < 200000000; a++)
		{	in_stream >> key_outgoing[a];
			if(key_outgoing[a] == '\0') {key_null_bookmark = a; break;}
		}
		in_stream.close();
		
		for(int a = 0; a < key_null_bookmark; a++) //Converts to numbers.
		{	     if(key_outgoing[a] == 48) {key_outgoing[a] = 0;}
			else if(key_outgoing[a] == 49) {key_outgoing[a] = 1;}
			else if(key_outgoing[a] == 50) {key_outgoing[a] = 2;}
			else if(key_outgoing[a] == 51) {key_outgoing[a] = 3;}
			else if(key_outgoing[a] == 52) {key_outgoing[a] = 4;}
			else if(key_outgoing[a] == 53) {key_outgoing[a] = 5;}
			else if(key_outgoing[a] == 54) {key_outgoing[a] = 6;}
			else if(key_outgoing[a] == 55) {key_outgoing[a] = 7;}
			else if(key_outgoing[a] == 56) {key_outgoing[a] = 8;}
			else if(key_outgoing[a] == 57) {key_outgoing[a] = 9;}
			else {cout << "\nkey.outgoing is corrupted.\n"; return 0;}
		}
		
		//Converts 160 digits from key_outgoing[] to 80 integers in sub_key[].
		//(Every two contiguous digits in the key files are a two-digit number 00 - 94.)
		int sub_key[80];
		int read_bookmark = 0; //For key_outgoing[].
		for(int a = 0; a < 80; a++)
		{	sub_key[a] = key_outgoing[read_bookmark];
			sub_key[a] *= 10;
			sub_key[a] += key_outgoing[read_bookmark + 1];
			read_bookmark += 2;
		}
		
		//Converts another 160 digits from key_outgoing[] to 80 integers in append_random[].
		//(Every two contiguous digits in the key files are a two-digit number 00 - 94.)
		//These numbers will be appended to the user's message if they entered less than 80 characters.
		int append_random[80];
		for(int a = 0; a < 80; a++)
		{	append_random[a] = key_outgoing[read_bookmark];
			append_random[a] *= 10;
			append_random[a] += key_outgoing[read_bookmark + 1];
			read_bookmark += 2;
		}
		
		//Appends randomness to the user's message.
		if(plaintext_null_bookmark < 80)
		{	for(int a = 0; plaintext_null_bookmark < 80; plaintext_null_bookmark++)
			{	plaintext_decimal[plaintext_null_bookmark] = append_random[a];
				a++;
			}
		}
		
		///Encrypts the message, sub_key[] will hold the ciphertext.
		for(int a = 0; a < 80; a++)
		{	sub_key[a] += plaintext_decimal[a];
			sub_key[a] %= 95;
		}
		
		///Writes the key back to its file but with 320 digits truncated off the left end as those digits were consumed.
		ofstream out_stream;
		out_stream.open("key.outgoing");
		for(int a = 320; a < key_null_bookmark; a++)
		{	out_stream << int(key_outgoing[a]);
		}
		out_stream << '\0';
		out_stream.close();
		
		//Overwrites RAM of array key_outgoing[].
		for(int a = 0; a < 200000000; a++)
		{	key_outgoing[a] = 9;
			key_outgoing[a] = 8;
			key_outgoing[a] = 7;
			key_outgoing[a] = 6;
			key_outgoing[a] = 5;
			key_outgoing[a] = 4;
			key_outgoing[a] = 3;
			key_outgoing[a] = 2;
			key_outgoing[a] = 1;
			key_outgoing[a] = 0;
		}
		
		//Overwrites RAM of array plaintext_decimal[].
		for(int a = 0; a < 80; a++)
		{	plaintext_decimal[a] = 9;
			plaintext_decimal[a] = 8;
			plaintext_decimal[a] = 7;
			plaintext_decimal[a] = 6;
			plaintext_decimal[a] = 5;
			plaintext_decimal[a] = 4;
			plaintext_decimal[a] = 3;
			plaintext_decimal[a] = 2;
			plaintext_decimal[a] = 1;
			plaintext_decimal[a] = 0;
		} //Only partially effective, INDIRECT-CORRESPONDING printed/copied text is cloned from RAM.
		
		//Prints ciphertext (held in array sub_key[].)
		cout << "\nSelect all 80 characters including end spaces if any. Ciphertext:\n";
		for(int a = 0; a < 80; a++)
		{	cout << char(sub_key[a] + 32);
		}
		
		//Overwrites RAM of array sub_key[].
		for(int a = 0; a < 80; a++)
		{	sub_key[a] = 9;
			sub_key[a] = 8;
			sub_key[a] = 7;
			sub_key[a] = 6;
			sub_key[a] = 5;
			sub_key[a] = 4;
			sub_key[a] = 3;
			sub_key[a] = 2;
			sub_key[a] = 1;
			sub_key[a] = 0;
		} //Only partially effective, printed/copied text is cloned from RAM.
		
		//Calculates # of messages left to generate.
		key_null_bookmark -= 320;
		key_null_bookmark /= 320;
		if     (key_null_bookmark == 0) {cout << "\n\nkey.outgoing has been depleted.\n";}
		else if(key_null_bookmark == 1) {cout << "\n\nYou may encrypt one more message.\n";}
		else                            {cout << "\n\nYou may encrypt " << key_null_bookmark << " more messages.\n";}
	}
	
	
	
	
	
	//                                                      2   Decrypt
	//_______________________________________________________________________________________________________________________
	if(user_option == 2)
	{	cout << "Decrypt in the order received.\n";
		cout << "Enter ciphertext of 80 characters including end spaces if any:\n\n";
		
		//If you entered a message and got the "No input visible" error, remove the following two lines of code.
		char nothing_to_see_here[1]; //This is here to catch the cached new line.
		cin.getline(nothing_to_see_here, 1);
		
		char ciphertext[10000]; //Incase the user enters too many.
		for(int a = 0; a < 10000; a++) {ciphertext[a] = '\0';} //Fills ciphertext[] with null.
		cin.getline(ciphertext, 10000);
		
		if(ciphertext[0] == '\0') {cout << "No input visible, program ended. See line 369 if input was given.\n"; return 0;}
		
		//Converts ciphertext[] characters to final integers of 0 - 94 (ciphertext_decimal[] will hold the result.)
		int ciphertext_decimal[80];
		for(int a = 0; a < 80; a++)
		{	ciphertext_decimal[a] = (ciphertext[a] -32);
		}
		
		//Key depletion check.
		ifstream in_stream;
		in_stream.open("key.incoming");
		char depletion_check[1];
		in_stream >> depletion_check[0];
		in_stream.close();
		if((depletion_check[0] < 48) || (depletion_check[0] > 57)) {cout << "\nkey.incoming has been depleted or doesn't exist.\n"; return 0;}
		
		//Loads file key.incoming into array key_incoming[].
		static char key_incoming[200000000];
		int key_null_bookmark = 200000000;
		in_stream.open("key.incoming");
		for(int a = 0; a < 200000000; a++)
		{	in_stream >> key_incoming[a];
			if(key_incoming[a] == '\0') {key_null_bookmark = a; break;}
		}
		in_stream.close();
		
		for(int a = 0; a < key_null_bookmark; a++) //Converts to numbers.
		{	     if(key_incoming[a] == 48) {key_incoming[a] = 0;}
			else if(key_incoming[a] == 49) {key_incoming[a] = 1;}
			else if(key_incoming[a] == 50) {key_incoming[a] = 2;}
			else if(key_incoming[a] == 51) {key_incoming[a] = 3;}
			else if(key_incoming[a] == 52) {key_incoming[a] = 4;}
			else if(key_incoming[a] == 53) {key_incoming[a] = 5;}
			else if(key_incoming[a] == 54) {key_incoming[a] = 6;}
			else if(key_incoming[a] == 55) {key_incoming[a] = 7;}
			else if(key_incoming[a] == 56) {key_incoming[a] = 8;}
			else if(key_incoming[a] == 57) {key_incoming[a] = 9;}
			else {cout << "\nkey.incoming is corrupted.\n"; return 0;}
		}
		
		//Converts 160 digits from key_incoming[] to 80 integers in sub_key[].
		//(Every two contiguous digits in the key files are a two-digit number 00 - 94.)
		int sub_key[80];
		int read_bookmark = 0; //For key_incoming[].
		for(int a = 0; a < 80; a++)
		{	sub_key[a] = key_incoming[read_bookmark];
			sub_key[a] *= 10;
			sub_key[a] += key_incoming[read_bookmark + 1];
			read_bookmark += 2;
		}
		
		//The following formula helps extract plaintext quickly.
		//      ______________________________________________ ________________________________________________
		//     |                                              |                                                |
		//     |          if sub-key <= ciphertext            |                     else                       |
		//     |   then plaintext = (ciphertext - sub-key)    |    plaintext = ((95 - sub-key) + ciphertext)   |
		//     |______________________________________________|________________________________________________|
		//
		///Decrypts the message, sub_key[] will hold the plaintext.
		for(int a = 0; a < 80; a++)
		{	if(sub_key[a] <= ciphertext_decimal[a]) {sub_key[a] = (ciphertext_decimal[a] - sub_key[a]);}
			else {sub_key[a] = ((95 - sub_key[a]) + ciphertext_decimal[a]);}
		}
		
		///Writes the key back to its file but with 320 digits truncated off the left end as those digits were consumed.
		ofstream out_stream;
		out_stream.open("key.incoming");
		for(int a = 320; a < key_null_bookmark; a++)
		{	out_stream << int(key_incoming[a]);
		}
		out_stream << '\0';
		out_stream.close();
		
		//Overwrites RAM of array key_incoming[].
		for(int a = 0; a < 200000000; a++)
		{	key_incoming[a] = 9;
			key_incoming[a] = 8;
			key_incoming[a] = 7;
			key_incoming[a] = 6;
			key_incoming[a] = 5;
			key_incoming[a] = 4;
			key_incoming[a] = 3;
			key_incoming[a] = 2;
			key_incoming[a] = 1;
			key_incoming[a] = 0;
		}
		
		//Prints plaintext (held in array sub_key[].)
		cout << "\nPlaintext:\n";
		for(int a = 0; a < 80; a++) {cout << char(sub_key[a] + 32);}
		
		//Overwrites RAM of array sub_key[].
		for(int a = 0; a < 80; a++)
		{	sub_key[a] = 9;
			sub_key[a] = 8;
			sub_key[a] = 7;
			sub_key[a] = 6;
			sub_key[a] = 5;
			sub_key[a] = 4;
			sub_key[a] = 3;
			sub_key[a] = 2;
			sub_key[a] = 1;
			sub_key[a] = 0;
		} //Only partially effective, printed/copied text is cloned from RAM.
		
		//Calculates # of possible messages left to decrypt.
		key_null_bookmark -= 320;
		key_null_bookmark /= 320;
		if     (key_null_bookmark == 0) {cout << "\n\nkey.incoming has been depleted.\n";}
		else if(key_null_bookmark == 1) {cout << "\n\nYou may decrypt one more message.\n";}
		else                            {cout << "\n\nYou may decrypt " << key_null_bookmark << " more messages.\n";}
	}
	
	
	
	
	
	//                                                     3   Get keys
	//_______________________________________________________________________________________________________________________
	if(user_option == 3)
	{	cout << "\nEnter 9 random digits, repeat 90 times. (Generates 400MB in 10m @2.4GHz)\n\n";
		
		unsigned int user_seed[90]; //Fills array user_seed[] with 90 user-defined seeds of size 9.
		for(int a = 0; a < 90; a++)
		{	if(a < 9) {cout << " " << (a + 1) << " of 90: ";} //Prints blank to align input status report (aesthetics.)
			else {cout << (a + 1) << " of 90: ";}
			
			cin >> user_seed[a];
		}
		
		static short table_private[200000000] = {0};
		for(int a = 0; a < 90; a++) //Constructively applies random digits to table_private[] based on the 90 seeds provided by the user.
		{	srand(user_seed[a]);    //WRITES ALTERNATING BETWEEN LEFT TO RIGHT & RIGHT TO LEFT. Alternation is based on the 90 user seeds.
			
			if((user_seed[a] % 2) == 0)
			{	for(int b = 0, temp; b < 200000000; b++) //WRITES LEFT TO RIGHT.
				{	temp = rand() % 95;
					temp += table_private[b];
					temp %= 95;
					table_private[b] = temp;
				}
			}
			else
			{	for(int b = 199999999, temp; b >= 0; b--) //WRITES RIGHT TO LEFT.
				{	temp = rand() % 95;
					temp += table_private[b];
					temp %= 95;
					table_private[b] = temp;
				}
			}
		}
		
		//Creates and writes to files key.incoming and key.outgoing
		ofstream out_stream;
		out_stream.open("key.incoming");
		for(int a = 0; a < 100000000; a++)
		{	if(table_private[a] < 10) {out_stream << 0;} //This ensures for example, "4" turns into "04" (digit pair.)
			out_stream << table_private[a];
		}
		out_stream.close();
		
		out_stream.open("key.outgoing");
		for(int a = 100000000; a < 200000000; a++)
		{	if(table_private[a] < 10) {out_stream << 0;} //This ensures for example, "4" turns into "04" (digit pair.)
			out_stream << table_private[a];
		}
		out_stream.close();
		
		//Overwrites RAM of array table_private[].
		for(int a = 0; a < 200000000; a++)
		{	table_private[a] = 9;
			table_private[a] = 8;
			table_private[a] = 7;
			table_private[a] = 6;
			table_private[a] = 5;
			table_private[a] = 4;
			table_private[a] = 3;
			table_private[a] = 2;
			table_private[a] = 1;
			table_private[a] = 0;
		}
		
		cout << "\n\nShare this folder in private, THEN swap the\n"
			 << "following two file names on your end ONLY:\n\n"
			 
			 << "  * Rename key.incoming to key.outgoing\n"
			 << "  * Rename key.outgoing to key.incoming\n";
	}
	
	return 0;
}
