/// OTP - fast & plentiful One-time pad
/// Version 4, plausibility ratio = 1:95, number of plausible messages per ciphertext = 1,738,460,461,580,383,102,822,844,861,515,808,913,627,197,261,569,433,052,581,362,995,961,958,929,061,439,629,911,192,464,722,032,471,986,361,631,485,925,281,770,388,295,399,243,361,316,621,303,558,349,609,375
/// Use OTP to communicate with ciphertext of unlimited plausible deniability.
/// Guess-keys  decrypt all  ciphertext  into all the possible  plaintext
/// combinations while intended messages are known only by the key owners.
/// Nikolay Valentinovich Repnitskiy - License: WTFPLv2+ (wtfpl.net.)

/*  Get   7MB of keys in 20 seconds and    20,000 outgoing messages per user.
Or  Get 512MB of keys in 20 minutes and 1,600,000 outgoing messages per user.  Generate and share multiple folders in
private to have spare keys. Keys are truncated upon use. Plaintext is 79 char max. The 80th char holds the message length.
As with all my OTPs,  reserved randomness within the key files is appended to all plaintext  then both that randomness and
plaintext are encrypted, along with the message length information. This prevents key fragment exposure and file analytics
based on size. All ciphertext is 80 characters total. The following files conjure speedy automated dual-channel symmetry:
-----------------------------------------------------------------------------------------------------------------------
 * keys                    (folder)
   * incoming              (folder within the keys folder)
   * outgoing              (folder within the keys folder)
 * remaining.encrypt.txt   (Contains the remaining quantity to encrypt, on top of being printed after each encryption.)
 * remaining.decrypt.txt   (Contains the remaining quantity to decrypt, on top of being printed after each decryption.)
 * symmetry.entanglement   (After generating keys & sharing this folder, the generator removes this file on their end.)
----------------------------------------------------------------------------------------------------------------------
IF OPTION 3 (keys in 20 secinds) - requires 7MB of RAM to get keys. Very lightweight, ***slightly weaker randomness.***
  * 0000 - 0099   (3.2MB)  (100 key files within incoming folder, each 32,000 char +end-null--capable of 200 messages.)
  * 0000 - 0099   (3.2MB)  (100 key files within outgoing folder, each 32,000 char +end-null--capable of 200 messages.)
----------------------------------------------------------------------------------------------------------------------
IF OPTION 4 (keys in 20 minutes) - requires 1GB of RAM to get keys. ***Strong randomness.***
  * 0000 - 2559   (256MB)  (2,560 key files within incoming folder, each 100k char +end-null--capable of 625 messages.)
  * 0000 - 2559   (256MB)  (2,560 key files within outgoing folder, each 100k char +end-null--capable of 625 messages.)
----------------------------------------------------------------------------------------------------------------------
If you happen to encrypt n messages in a row and send them disordered or don't send them at all, send the other party
a new message where they decrypt it until the output makes sense. If you send encrypted messages containing seeds for
generating new symmetric keys, then perfect secrecy is reduced to guaranteed  decryption  difficulty as the number of
plausible messages per ciphertext begins to narrow. This applies to symmetric key transformations and operations with
additional components such as transformation determinants for the keys. The following link contains mathematical proof.
https://github.com/compromise-evident/OTP/blob/main/Perfect%20secrecy%20and%20computational%20difficulty%20proof.pdf
---------------------------------------------------------------------------------------------------------------------
How to run the program - Software package repositories for GNU+Linux operating systems have all the developer tools needed.
Open a terminal and use the following command as root to install  Geany  and  g++  on your computer:  apt install geany g++
Geany is a fast & lightweight text editor and Integrated Development Environment (IDE) in which you can write and run code.
g++ is the GNU compiler for C++ which allows written code to run. The compiler operates in the background automatically and
displays errors in your code as you will see in the lower Geany box.  Create a folder somewhere on your machine. Open Geany
and paste this code into the blank Geany page.  (A good tip for clarity in auditing is to enable indentation guides for the
block braces. Go to View > Show Indentation Guides.) Save the file as anything.cpp within the newly-created folder. Now you
can use these shortcuts to run the program: F9, F5. Whenever you wish to run the program again, open Geany and use the same
shortcuts. This will work for any single C++ file whether you paste over the current code or open a new tab and repeat. */

#include <cstdlib>    //For rand() & srand() (here: user-defined seeds only.)
#include <fstream>    //For file I/O (creates, writes to, and reads from ONLY the 5,123 and 203 files mentioned above.)
#include <iostream>
#include <sys/stat.h> /*For mkdir() (creating folders.) Here are some examples you might find useful as a GNU+Linux user:
------------------------------------------------------------------------------------------------------------------------
used, requires header   (create folders)-                             mkdir("keys", 0777);
used, requires header   (create folders within folders)-              mkdir("./keys/incoming", 0777);
used                    (file I/O in folders)-              out_stream.open("./keys/incoming/file_1");
                        (file I/O elsewhere)-               out_stream.open("//home//nikolay//Desktop//folder_1//file_1");
      requires header   (create folders elsewhere)-                   mkdir("//home//nikolay//Desktop//folder_1//keys", 0777);
----------------------------------------------------------------------------------------------------------------------------*/
using namespace std;

int main()
{	cout << "\n(One-time pad)\n\n"
	
	     << "(1) Encrypt\n"
	     << "(2) Decrypt\n"
	     << "(3) Get keys in 20s (20,000 msg/user.)\n"
	     << "(4) Get keys in 20m (1.6 million msg/user.)\n\n"
	
	     << "Enter option: ";
	
	int user_option;
	cin >> user_option;
	if((user_option != 1) && (user_option != 2) && (user_option != 3) && (user_option != 4)) {cout << "\nInvalid, program ended.\n"; return 0;}
	//(You can run each of the four ifs holding options 1, 2, and 3, and 4 in isolation--they are self-sustained.)
	
	
	
	
	
	//______________________________________________________Encrypt___________________________________________________//
	if(user_option == 1)
	{	ifstream in_stream;
		ofstream out_stream;
		
		//Checks that messages left to encrypt is not zero.
		char remaining_encrypt[7];
		in_stream.open("remaining.encrypt.txt");
		if(in_stream.fail() == true) {in_stream.close(); cout << "\n\nCan't encrypt without keys.\n"; return 0;}
		for(int a = 0; a < 7; a++) {in_stream >> remaining_encrypt[a];}
		in_stream.close();
		
		for(int a = 0; a < 7; a++) {remaining_encrypt[a] -= 48;} //Fixes input.
		int remaining_encrypt_decimal = 0;
		if(remaining_encrypt[0] > 0) {remaining_encrypt_decimal += (remaining_encrypt[0] * 1000000);}
		if(remaining_encrypt[1] > 0) {remaining_encrypt_decimal += (remaining_encrypt[1] *  100000);}
		if(remaining_encrypt[2] > 0) {remaining_encrypt_decimal += (remaining_encrypt[2] *   10000);}
		if(remaining_encrypt[3] > 0) {remaining_encrypt_decimal += (remaining_encrypt[3] *    1000);}
		if(remaining_encrypt[4] > 0) {remaining_encrypt_decimal += (remaining_encrypt[4] *     100);}
		if(remaining_encrypt[5] > 0) {remaining_encrypt_decimal += (remaining_encrypt[5] *      10);}
		if(remaining_encrypt[6] > 0) {remaining_encrypt_decimal +=  remaining_encrypt[6]           ;}
		if(remaining_encrypt_decimal == 0)   {cout << "\n\nEncryption keys depleted.\n"; return 0;}
		
		cout << "79 characters max (width of terminal -1.) Enter message:\n\n";
		
		//USELNX If you entered a message and got the "Input invisible" error, remove the following two lines of code.
		char nothing_to_see_here[1]; //This is here to catch the cached new line.
		cin.getline(nothing_to_see_here, 1);
		
		char plaintext[80];
		for(int a = 0; a < 80; a++) {plaintext[a] = '\0';} //Fills plaintext[] with null.
		cin.getline(plaintext, 80);
		plaintext[79] = '\0'; //Message is cut down to 79 characters.
		
		if(plaintext[0] == '\0') {cout << "Input invisible. If input was given, find the line with characters USELNX\n"; return 0;}
		
		int ciphertext[80];
		for(int a = 0; a < 80; a++) //Prepares initial ciphertext[]. Pressing arrow/other keys WILL TRIGGER THE FOLLOWING ELSE!
		{	     if(plaintext[a] == ' ') {ciphertext[a] =  0;}	else if(plaintext[a] == 'P') {ciphertext[a] = 48;}
			else if(plaintext[a] == '!') {ciphertext[a] =  1;}	else if(plaintext[a] == 'Q') {ciphertext[a] = 49;}
			else if(plaintext[a] == '"') {ciphertext[a] =  2;}	else if(plaintext[a] == 'R') {ciphertext[a] = 50;}
			else if(plaintext[a] == '#') {ciphertext[a] =  3;}	else if(plaintext[a] == 'S') {ciphertext[a] = 51;}
			else if(plaintext[a] == '$') {ciphertext[a] =  4;}	else if(plaintext[a] == 'T') {ciphertext[a] = 52;}
			else if(plaintext[a] == '%') {ciphertext[a] =  5;}	else if(plaintext[a] == 'U') {ciphertext[a] = 53;}
			else if(plaintext[a] == '&') {ciphertext[a] =  6;}	else if(plaintext[a] == 'V') {ciphertext[a] = 54;}
			else if(plaintext[a] =='\'') {ciphertext[a] =  7;}	else if(plaintext[a] == 'W') {ciphertext[a] = 55;}
			else if(plaintext[a] == '(') {ciphertext[a] =  8;}	else if(plaintext[a] == 'X') {ciphertext[a] = 56;}
			else if(plaintext[a] == ')') {ciphertext[a] =  9;}	else if(plaintext[a] == 'Y') {ciphertext[a] = 57;}
			else if(plaintext[a] == '*') {ciphertext[a] = 10;}	else if(plaintext[a] == 'Z') {ciphertext[a] = 58;}
			else if(plaintext[a] == '+') {ciphertext[a] = 11;}	else if(plaintext[a] == '[') {ciphertext[a] = 59;}
			else if(plaintext[a] == ',') {ciphertext[a] = 12;}	else if(plaintext[a] =='\\') {ciphertext[a] = 60;}
			else if(plaintext[a] == '-') {ciphertext[a] = 13;}	else if(plaintext[a] == ']') {ciphertext[a] = 61;}
			else if(plaintext[a] == '.') {ciphertext[a] = 14;}	else if(plaintext[a] == '^') {ciphertext[a] = 62;}
			else if(plaintext[a] == '/') {ciphertext[a] = 15;}	else if(plaintext[a] == '_') {ciphertext[a] = 63;}
			else if(plaintext[a] == '0') {ciphertext[a] = 16;}	else if(plaintext[a] == '`') {ciphertext[a] = 64;}
			else if(plaintext[a] == '1') {ciphertext[a] = 17;}	else if(plaintext[a] == 'a') {ciphertext[a] = 65;}
			else if(plaintext[a] == '2') {ciphertext[a] = 18;}	else if(plaintext[a] == 'b') {ciphertext[a] = 66;}
			else if(plaintext[a] == '3') {ciphertext[a] = 19;}	else if(plaintext[a] == 'c') {ciphertext[a] = 67;}
			else if(plaintext[a] == '4') {ciphertext[a] = 20;}	else if(plaintext[a] == 'd') {ciphertext[a] = 68;}
			else if(plaintext[a] == '5') {ciphertext[a] = 21;}	else if(plaintext[a] == 'e') {ciphertext[a] = 69;}
			else if(plaintext[a] == '6') {ciphertext[a] = 22;}	else if(plaintext[a] == 'f') {ciphertext[a] = 70;}
			else if(plaintext[a] == '7') {ciphertext[a] = 23;}	else if(plaintext[a] == 'g') {ciphertext[a] = 71;}
			else if(plaintext[a] == '8') {ciphertext[a] = 24;}	else if(plaintext[a] == 'h') {ciphertext[a] = 72;}
			else if(plaintext[a] == '9') {ciphertext[a] = 25;}	else if(plaintext[a] == 'i') {ciphertext[a] = 73;}
			else if(plaintext[a] == ':') {ciphertext[a] = 25;}	else if(plaintext[a] == 'j') {ciphertext[a] = 74;}
			else if(plaintext[a] == ';') {ciphertext[a] = 27;}	else if(plaintext[a] == 'k') {ciphertext[a] = 75;}
			else if(plaintext[a] == '<') {ciphertext[a] = 28;}	else if(plaintext[a] == 'l') {ciphertext[a] = 76;}
			else if(plaintext[a] == '=') {ciphertext[a] = 29;}	else if(plaintext[a] == 'm') {ciphertext[a] = 77;}
			else if(plaintext[a] == '>') {ciphertext[a] = 30;}	else if(plaintext[a] == 'n') {ciphertext[a] = 78;}
			else if(plaintext[a] == '?') {ciphertext[a] = 31;}	else if(plaintext[a] == 'o') {ciphertext[a] = 79;}
			else if(plaintext[a] == '@') {ciphertext[a] = 32;}	else if(plaintext[a] == 'p') {ciphertext[a] = 80;}
			else if(plaintext[a] == 'A') {ciphertext[a] = 33;}	else if(plaintext[a] == 'q') {ciphertext[a] = 81;}
			else if(plaintext[a] == 'B') {ciphertext[a] = 34;}	else if(plaintext[a] == 'r') {ciphertext[a] = 82;}
			else if(plaintext[a] == 'C') {ciphertext[a] = 35;}	else if(plaintext[a] == 's') {ciphertext[a] = 83;}
			else if(plaintext[a] == 'D') {ciphertext[a] = 36;}	else if(plaintext[a] == 't') {ciphertext[a] = 84;}
			else if(plaintext[a] == 'E') {ciphertext[a] = 37;}	else if(plaintext[a] == 'u') {ciphertext[a] = 85;}
			else if(plaintext[a] == 'F') {ciphertext[a] = 38;}	else if(plaintext[a] == 'v') {ciphertext[a] = 86;}
			else if(plaintext[a] == 'G') {ciphertext[a] = 39;}	else if(plaintext[a] == 'w') {ciphertext[a] = 87;}
			else if(plaintext[a] == 'H') {ciphertext[a] = 40;}	else if(plaintext[a] == 'x') {ciphertext[a] = 88;}
			else if(plaintext[a] == 'I') {ciphertext[a] = 41;}	else if(plaintext[a] == 'y') {ciphertext[a] = 89;}
			else if(plaintext[a] == 'J') {ciphertext[a] = 42;}	else if(plaintext[a] == 'z') {ciphertext[a] = 90;}
			else if(plaintext[a] == 'K') {ciphertext[a] = 43;}	else if(plaintext[a] == '{') {ciphertext[a] = 91;}
			else if(plaintext[a] == 'L') {ciphertext[a] = 44;}	else if(plaintext[a] == '|') {ciphertext[a] = 92;}
			else if(plaintext[a] == 'M') {ciphertext[a] = 45;}	else if(plaintext[a] == '}') {ciphertext[a] = 93;}
			else if(plaintext[a] == 'N') {ciphertext[a] = 46;}	else if(plaintext[a] == '~') {ciphertext[a] = 94;}
			else if(plaintext[a] == 'O') {ciphertext[a] = 47;}	else if(plaintext[a] =='\0') {ciphertext[a] = -1;} //If message < 79 char, this marks all ending unused spaces to which randomness will be applied then encrypted.
			
			else
			{	cout << "\nDefective input, try again.\n";
				
				//Overwrites RAM of arrays plaintext[] and ciphertext[].
				for(int a = 0; a < 80; a++)
				{	for(int b = 0; b < 10; b++)
					{	plaintext[a]  = b;
						ciphertext[a] = b;
					}
				} //Only partially effective, printed/copied text is cloned from RAM to RAM.
				
				return 0;
			}
		}
		
		//Adjusting file remaining.encrypt.txt.
		remaining_encrypt_decimal--;
		out_stream.open("remaining.encrypt.txt");
		if(remaining_encrypt_decimal < 1000000) {out_stream << "0";}
		if(remaining_encrypt_decimal <  100000) {out_stream << "0";}
		if(remaining_encrypt_decimal <   10000) {out_stream << "0";}
		if(remaining_encrypt_decimal <    1000) {out_stream << "0";}
		if(remaining_encrypt_decimal <     100) {out_stream << "0";}
		if(remaining_encrypt_decimal <      10) {out_stream << "0";}
		out_stream << remaining_encrypt_decimal;
		out_stream << " messages left to encrypt.\n\n"
		
		           << "Do not modify this file.\n"
		           << "This number must consist\n"
		           << "of digits 0000000 - 1600000.";
		out_stream.close();
		
		//Maintaining symmetry entanglement. If you received the symmetry.entanglement file,
		//these file names are modified in the path-to-file section where only the folder
		//names are swapped. Now your incoming channel is symmetric with their outgoing
		//channel, and your outgoing channel is symmetric with their incoming channel.
		char file_name_key_outgoing[21] = "./keys/outgoing/0000";
		in_stream.open("symmetry.entanglement");
		if(in_stream.fail() == false)
		{	file_name_key_outgoing[ 7] = 'i';
			file_name_key_outgoing[ 8] = 'n';
			file_name_key_outgoing[ 9] = 'c';
			file_name_key_outgoing[10] = 'o';
			file_name_key_outgoing[11] = 'm';
		}
		in_stream.close();
		
		//Generates key file NAME based on depletion.
		int file_numbering = 1000000; //Only the last 4 digits are used, size makes mod operations easier.
		for(int a = 0; a < 10000; a++)
		{	int temp_file_numbering = file_numbering;
			file_name_key_outgoing[19] = (temp_file_numbering % 10) + 48; //       ./keys/outgoing/0  0  0  0    (file name)
			temp_file_numbering /=    10; //                                                       ^  ^  ^  ^
			file_name_key_outgoing[18] = (temp_file_numbering % 10) + 48; //                      16 17 18 19    (element layout)
			temp_file_numbering /=    10;
			file_name_key_outgoing[17] = (temp_file_numbering % 10) + 48;
			temp_file_numbering /=    10;
			file_name_key_outgoing[16] = (temp_file_numbering % 10) + 48;
			
			in_stream.open(file_name_key_outgoing);
			if(in_stream.fail() == false) {in_stream.close(); break;}
			in_stream.close();
			
			file_numbering++;
		}
		
		//Gets a copy of the key file. (Only the first 160 characters!)
		char key_outgoing_content[160];
		in_stream.open(file_name_key_outgoing);
		for(int a = 0; a < 160; a++) {in_stream.get(key_outgoing_content[a]);}
		in_stream.close();
		for(int a = 0; a < 160; a++) {key_outgoing_content[a] -= 32;} //Fixes key contents.
		
		//Gets the message length information.
		int message_length = 0;
		for(int a = 0; a < 79; a++)
		{	if(ciphertext[a] != -1) {message_length++;}
		}
		
		//Appends randomness if message is less than 79 characters.
		for(int a = 0; a < 79; a++)
		{	if(ciphertext[a] == -1) {ciphertext[a] = key_outgoing_content[a];}
		}
		
		//Appends message length information (overwrites 80th element.)
		ciphertext[79] = (message_length);
		
		///Encrypts message.
		for(int a = 0; a < 80; a++) {ciphertext[a] += key_outgoing_content[a + 80]; ciphertext[a] %= 95;}
		
		//Prints ciphertext.
		cout << "\nSelect all 80 characters including end spaces if any. Ciphertext:\n";
		for(int a = 0; a < 80; a++)
		{	cout << char(ciphertext[a] + 32);
		}
		
		//Overwriting RAM of plaintext[], ciphertext[].
		for(int a = 0; a < 80; a++)
		{	for(int b = 0; b < 10; b++)
			{	plaintext[a] = b;
			}
		} //Only partially effective, printed/copied text is cloned from RAM to RAM.
		
		//Overwriting RAM of key_outgoing_content[].
		for(int a = 0; a < 160; a++)
		{	for(int b = 0; b < 10; b++)
			{	key_outgoing_content[a] = b;
			}
		}
		
		//Truncating the outgoing key file by the first 160 characters.
		in_stream.open(file_name_key_outgoing);
		char truncating_table_private[100001];
		int  truncating_table_private_null_bookmark = 160; //Initially 160 as worst case: whole key file depleted, but no seg fault!
		for(int a = 0; a < 100001; a++)
		{	in_stream.get(truncating_table_private[a]);
			if(truncating_table_private[a] == '\0') {truncating_table_private_null_bookmark = a; break;}
		}
		in_stream.close();
		
		if(truncating_table_private_null_bookmark == 160)
		{	remove(file_name_key_outgoing);
		}
		else
		{	out_stream.open(file_name_key_outgoing);
			for(int a = 160; a < truncating_table_private_null_bookmark; a++) {out_stream.put(truncating_table_private[a]);}
			out_stream << '\0';
			out_stream.close();
		}
		
		//Overwriting RAM of truncating_table_private[];
		for(int a = 0; a < 100001; a++)
		{	for(int b = 0; b < 10; b++) {truncating_table_private[a] = b;}
		}
		
		//Displays # of messages left to generate.
		if     (remaining_encrypt_decimal == 0) {cout << "\n\nEncryption keys depleted.\n"        ;}
		else if(remaining_encrypt_decimal == 1) {cout << "\n\nYou may encrypt one more message.\n";}
		else   {cout << "\n\nYou may encrypt " << remaining_encrypt_decimal << " more messages.\n";}
	}
	
	
	
	
	
	//______________________________________________________Decrypt___________________________________________________//
	if(user_option == 2)
	{	ifstream in_stream;
		ofstream out_stream;
		
		//Checks that messages left to decrypt is not zero.
		char remaining_decrypt[7];
		in_stream.open("remaining.decrypt.txt");
		if(in_stream.fail() == true) {in_stream.close(); cout << "\n\nCan't decrypt without keys.\n"; return 0;}
		for(int a = 0; a < 7; a++) {in_stream >> remaining_decrypt[a];}
		in_stream.close();
		
		for(int a = 0; a < 7; a++) {remaining_decrypt[a] -= 48;} //Fixes input.
		int remaining_decrypt_decimal = 0;
		if(remaining_decrypt[0] > 0) {remaining_decrypt_decimal += (remaining_decrypt[0] * 1000000);}
		if(remaining_decrypt[1] > 0) {remaining_decrypt_decimal += (remaining_decrypt[1] *  100000);}
		if(remaining_decrypt[2] > 0) {remaining_decrypt_decimal += (remaining_decrypt[2] *   10000);}
		if(remaining_decrypt[3] > 0) {remaining_decrypt_decimal += (remaining_decrypt[3] *    1000);}
		if(remaining_decrypt[4] > 0) {remaining_decrypt_decimal += (remaining_decrypt[4] *     100);}
		if(remaining_decrypt[5] > 0) {remaining_decrypt_decimal += (remaining_decrypt[5] *      10);}
		if(remaining_decrypt[6] > 0) {remaining_decrypt_decimal +=  remaining_decrypt[6]           ;}
		if(remaining_decrypt_decimal == 0)   {cout << "\n\nDecryption keys depleted.\n"; return 0;}
		
		cout << "Decrypt in the order received.\n"
		     << "Enter ciphertext of 80 characters including end spaces if any:\n\n";
		
		//WINBAD If you entered a message and got the "Input invisible" error, remove the following two lines of code.
		char nothing_to_see_here[1]; //This is here to catch the cached new line.
		cin.getline(nothing_to_see_here, 1);
		
		char ciphertext[81]; //Incase the user enters too many.
		for(int a = 0; a < 81; a++) {ciphertext[a] = '\0';} //Fills ciphertext[] with null.
		cin.getline(ciphertext, 81);
		ciphertext[80] = '\0'; //Input is cut down to 80 characters.
		
		if(ciphertext[0] == '\0') {cout << "Input invisible. If input was given, find the line with characters WINBAD\n"; return 0;}
		for(int a = 0; a < 80; a++) {ciphertext[a] -= 32;} //Fixes ciphertext.
		
		//Adjusting file remaining.decrypt.txt
		remaining_decrypt_decimal--;
		out_stream.open("remaining.decrypt.txt");
		if(remaining_decrypt_decimal < 1000000) {out_stream << "0";}
		if(remaining_decrypt_decimal <  100000) {out_stream << "0";}
		if(remaining_decrypt_decimal <   10000) {out_stream << "0";}
		if(remaining_decrypt_decimal <    1000) {out_stream << "0";}
		if(remaining_decrypt_decimal <     100) {out_stream << "0";}
		if(remaining_decrypt_decimal <      10) {out_stream << "0";}
		out_stream << remaining_decrypt_decimal;
		out_stream << " messages left to decrypt.\n\n"
		
		           << "Do not modify this file.\n"
		           << "This number must consist\n"
		           << "of digits 0000000 - 1600000.";
		out_stream.close();
		
		//Maintaining symmetry entanglement. If you received the symmetry.entanglement file,
		//these file names are modified in the path-to-file section where only the folder
		//names are swapped. Now your incoming channel is symmetric with their outgoing
		//channel, and your outgoing channel is symmetric with their incoming channel.
		char file_name_key_incoming[21] = "./keys/incoming/0000";
		in_stream.open("symmetry.entanglement");
		if(in_stream.fail() == false)
		{	file_name_key_incoming[ 7] = 'o';
			file_name_key_incoming[ 8] = 'u';
			file_name_key_incoming[ 9] = 't';
			file_name_key_incoming[10] = 'g';
			file_name_key_incoming[11] = 'o';
		}
		in_stream.close();
		
		//Generates key file NAME based on existence.
		int file_numbering = 1000000; //Only the last 4 digits are used, size makes mod operations easier.
		for(int a = 0; a < 10000; a++)
		{	int temp_file_numbering = file_numbering;
			file_name_key_incoming[19] = (temp_file_numbering % 10) + 48; //       ./keys/incoming/0  0  0  0    (file name)
			temp_file_numbering /=    10; //                                                       ^  ^  ^  ^
			file_name_key_incoming[18] = (temp_file_numbering % 10) + 48; //                      16 17 18 19    (element layout)
			temp_file_numbering /=    10;
			file_name_key_incoming[17] = (temp_file_numbering % 10) + 48;
			temp_file_numbering /=    10;
			file_name_key_incoming[16] = (temp_file_numbering % 10) + 48;
			
			in_stream.open(file_name_key_incoming);
			if(in_stream.fail() == false) {in_stream.close(); break;}
			in_stream.close();
			
			file_numbering++;
		}
		
		//Gets a copy of the key file. (Only the first 160 characters!)
		char key_incoming_content[160];
		in_stream.open(file_name_key_incoming);
		for(int a = 0; a < 160; a++) {in_stream.get(key_incoming_content[a]);}
		in_stream.close();
		for(int a = 80; a < 160; a++) {key_incoming_content[a] -= 32;} //Fixes key content portion used for decryption.
		
		/// Decrypts message. The following formula helps extract plaintext quickly.
		//      ______________________________________________ ________________________________________________
		//     |                                              |                                                |
		//     |          if sub-key <= ciphertext            |                     else                       |
		//     |   then plaintext = (ciphertext - sub-key)    |    plaintext = ((95 - sub-key) + ciphertext)   |
		//     |______________________________________________|________________________________________________|
		//
		int plaintext[80];
		for(int a = 0; a < 80; a++)
		{	if(key_incoming_content[a + 80] <= ciphertext[a])
			{	plaintext[a] = (ciphertext[a] - key_incoming_content[a + 80]);
			}
			else
			{	plaintext[a] = ((95 - key_incoming_content[a + 80]) + ciphertext[a]);
			}
		}
		
		//Prints plaintext.
		cout << "\nPlaintext:\n";
		for(int a = 0; a < (plaintext[79]); a++) {cout << char(plaintext[a] + 32);}
		
		//Overwriting RAM of plaintext[], ciphertext[].
		for(int a = 0; a < 80; a++)
		{	for(int b = 0; b < 10; b++)
			{	plaintext[a] = b;
			}
		} //Only partially effective, printed/copied text is cloned from RAM to RAM.
		
		//Overwriting RAM of key_incoming_content[].
		for(int a = 0; a < 160; a++)
		{	for(int b = 0; b < 10; b++)
			{	key_incoming_content[a] = b;
			}
		}
		
		//Truncating the incoming key file by the first 160 characters.
		in_stream.open(file_name_key_incoming);
		char truncating_table_private[100001];
		int  truncating_table_private_null_bookmark = 160; //Initially 160 as worst case: whole key file depleted, but no seg fault!
		for(int a = 0; a < 100001; a++)
		{	in_stream.get(truncating_table_private[a]);
			if(truncating_table_private[a] == '\0') {truncating_table_private_null_bookmark = a; break;}
		}
		in_stream.close();
		
		if(truncating_table_private_null_bookmark == 160)
		{	remove(file_name_key_incoming);
		}
		else
		{	out_stream.open(file_name_key_incoming);
			for(int a = 160; a < truncating_table_private_null_bookmark; a++) {out_stream.put(truncating_table_private[a]);}
			out_stream << '\0';
			out_stream.close();
		}
		
		//Overwriting RAM of truncating_table_private[];
		for(int a = 0; a < 100001; a++)
		{	for(int b = 0; b < 10; b++) {truncating_table_private[a] = b;}
		}
		
		//Displays # of messages left to decrypt.
		if     (remaining_decrypt_decimal == 0) {cout << "\n\nDecryption keys depleted.\n"        ;}
		else if(remaining_decrypt_decimal == 1) {cout << "\n\nYou may decrypt one more message.\n";}
		else   {cout << "\n\nYou may decrypt " << remaining_decrypt_decimal << " more messages.\n";}
	}
	
	
	
	
	
	//______________________________________________________Get_keys_in_20_seconds____________________________________//
	if(user_option == 3)
	{	ifstream in_stream;
		ofstream out_stream;
		
		//Are you testing your fork and need keys fast?
		//Set the following variable to 1 and it will ask for only one seed.
		int value_90_seeds = 90;
		
		//Checks if regular files already exist.
		in_stream.open("remaining.encrypt.txt");
		if(in_stream.fail() == false)
		{	in_stream.close();
			cout << "\n\nKeys already exist, run a new OTP.cpp file in a different folder.\n";
			return 0;
		}
		in_stream.close();
		
		cout << "\nEnter a random nine-digit integer, repeat 90 times. (Get 7MB in 20s @2.1GHz.)\n\n";
		
		//Fills user_seeds[].
		unsigned int user_seeds[90] = {0};
		for(int a = 0; a < value_90_seeds; a++)
		{	if(a < 9) {cout << " " << (a + 1) << " of 90: ";} //Prints blank to align input status report (aesthetics.)
			else      {cout <<        (a + 1) << " of 90: ";}
			
			cin >> user_seeds[a];
		}
		
		//Fills table_private[] with randomness 00 - 94
		unsigned char table_private[6400000] = {0};
		for(int a = 0; a < value_90_seeds; a++) //Constructively applies random digits to table_private[] based on the 90 seeds provided by the user.
		{	srand(user_seeds[a]);               //WRITES ALTERNATING BETWEEN LEFT TO RIGHT & RIGHT TO LEFT. Alternation is based on the 90 user seeds.
			
			if((user_seeds[a] % 2) == 0)
			{	for(int b = 0; b < 6400000; b++) //WRITES LEFT TO RIGHT.
				{	table_private[b] += (rand() % 95);
					table_private[b] %= 95;
				}
			}
			else
			{	for(int b = 6399999; b >= 0; b--) //WRITES RIGHT TO LEFT.
				{	table_private[b] += (rand() % 95);
					table_private[b] %= 95;
				}
			}
		}
		
		//Adding additional randomness in table_private[].
		if(user_seeds[1] > 0) //(Inactive if in testing mode.)
		{	unsigned int seeds_sum = 0;
			for(int a = 0; a < 90; a++) {seeds_sum = ((seeds_sum + user_seeds[a]) % 1000000000);}
			srand(seeds_sum); //A new 9-digit seed comes from the sum of ALL user-seeds.
			for(int a = 0; a < 6400000; a++) //WRITES LEFT TO RIGHT.
			{	table_private[a] += (rand() % 95);
				table_private[a] %= 95;
			}
			
			//Again, adding additional randomness in table_private[].
			seeds_sum = 0;
			for(int a = 0; a < 90; a += 2) {seeds_sum = ((seeds_sum + user_seeds[a]) % 1000000000);}
			srand(seeds_sum); //Another new 9-digit seed comes from the sum of EVERY OTHER user-seed.
			for(int a = 6399999; a >= 0; a--) //WRITES RIGHT TO LEFT.
			{	table_private[a] += (rand() % 95);
				table_private[a] %= 95;
			}
			seeds_sum = 123456789; //Overwriting.
		}
		
		//Writing all keys for channel incoming then all keys for channel outgoing (separately, reusing code.)
		mkdir("keys"           ,  0777); //Creates a folder. Folder-izing helps lighten resource usage by 1,000%.
		mkdir("./keys/incoming",  0777); //Creates a folder within that keys folder.
		mkdir("./keys/outgoing",  0777); //Creates another folder within that keys folder.
		char file_name_key_incoming[21] = "./keys/incoming/0000";
		char file_name_key_outgoing[21] = "./keys/outgoing/0000";
		
		//Writes keys to folder incoming.
		int table_private_read_bookmark = 0;
		int file_numbering = 1000000; //Only the last 2 digits are used, size makes mod operations easier.
		for(int a = 0; a < 100; a++)
		{	out_stream.open(file_name_key_incoming);
			for(int b = 0; b < 32000; b++)
			{	out_stream.put(table_private[table_private_read_bookmark] + 32);
				
				table_private_read_bookmark++;
			}
			out_stream << '\0';
			out_stream.close();
			
			file_numbering++; //Adjusts file nunbering.
			int temp_file_numbering = file_numbering;
			file_name_key_incoming[19] = (temp_file_numbering % 10) + 48;//        ./keys/incoming/0  0  0  0    (file name)
			temp_file_numbering /=    10; //                                                       ^  ^  ^  ^
			file_name_key_incoming[18] = (temp_file_numbering % 10) + 48; //                      16 17 18 19    (element layout)
		}
		
		//Writes keys to folder outgoing, table_private_read_bookmark is not reset.
		file_numbering = 1000000; //Resetting. Only the last 2 digits are used, size makes mod operations easier.
		for(int a = 0; a < 100; a++)
		{	out_stream.open(file_name_key_outgoing);
			for(int b = 0; b < 32000; b++)
			{	out_stream.put(table_private[table_private_read_bookmark] + 32);
				
				table_private_read_bookmark++;
			}
			out_stream << '\0';
			out_stream.close();
			
			file_numbering++; //Adjusts file nunbering.
			int temp_file_numbering = file_numbering;
			file_name_key_outgoing[19] = (temp_file_numbering % 10) + 48; //       ./keys/outgoing/0  0  0  0    (file name)
			temp_file_numbering /=    10; //                                                       ^  ^  ^  ^
			file_name_key_outgoing[18] = (temp_file_numbering % 10) + 48; //                      16 17 18 19    (element layout)
		}
		
		//Creates the encryption remaining counter file.
		out_stream.open("remaining.encrypt.txt");
		out_stream << "0020000 messages left to encrypt.\n\n"
		
		           << "Do not modify this file.\n"
		           << "This number must consist\n"
		           << "of digits 0000000 - 1600000.";
		out_stream.close();
		
		//Creates the decryption remaining counter file.
		out_stream.open("remaining.decrypt.txt");
		out_stream << "0020000 messages left to decrypt.\n\n"
		
		           << "Do not modify this file.\n"
		           << "This number must consist\n"
		           << "of digits 0000000 - 1600000.";
		out_stream.close();
		
		//Creates the symmetry entanglement file.
		out_stream.open("symmetry.entanglement");
		out_stream << "REMINDER: one of you must remove this file!\n"
		           << "(Key maker had already been asked to do so.)";
		out_stream.close();
		
		//Overwrites RAM of user_seeds[].
		for(int a = 0; a < 90; a++)
		{	user_seeds[a] = 123456789;
			user_seeds[a] = 987604321;
			user_seeds[a] = 0;
		} //Only partially effective, printed/copied text is cloned from RAM to RAM.
		
		//Overwrites RAM of array table_private[].
		for(int a = 0; a < 6400000; a++)
		{	for(int b = 0; b < 10; b++) {table_private[a] = b;}
		}
		
		cout << "\n\nFinished! Share this folder in private, then\n"
		     << "REMOVE file symmetry.entanglement on your end ONLY!\n\n";
	}
	
	
	
	
	
	//______________________________________________________Get_keys_in_20_minutes____________________________________//
	if(user_option == 4)
	{	ifstream in_stream;
		ofstream out_stream;
		
		//Checks if regular files already exist.
		in_stream.open("remaining.encrypt.txt");
		if(in_stream.fail() == false)
		{	in_stream.close();
			cout << "\n\nKeys already exist, run a new OTP.cpp file in a different folder.\n";
			return 0;
		}
		in_stream.close();
		
		cout << "\nEnter a random nine-digit integer, repeat 90 times. (Get 512MB in 20m @2.1GHz.)\n\n";
		
		//Fills user_seeds[].
		unsigned int user_seeds[90] = {0};
		for(int a = 0; a < 90; a++)
		{	if(a < 9) {cout << " " << (a + 1) << " of 90: ";} //Prints blank to align input status report (aesthetics.)
			else      {cout <<        (a + 1) << " of 90: ";}
			
			cin >> user_seeds[a];
		}
		
		//Fills table_private[] with randomness 00 - 94
		static unsigned char table_private[512000000] = {0};
		for(int a = 0; a < 90; a++) //Constructively applies random digits to table_private[] based on the 90 seeds provided by the user.
		{	srand(user_seeds[a]);               //WRITES ALTERNATING BETWEEN LEFT TO RIGHT & RIGHT TO LEFT. Alternation is based on the 90 user seeds.
			
			if((user_seeds[a] % 2) == 0)
			{	for(int b = 0; b < 512000000; b++) //WRITES LEFT TO RIGHT.
				{	table_private[b] += (rand() % 95);
					table_private[b] %= 95;
				}
			}
			else
			{	for(int b = 511999999; b >= 0; b--) //WRITES RIGHT TO LEFT.
				{	table_private[b] += (rand() % 95);
					table_private[b] %= 95;
				}
			}
		}
		
		//Adding additional randomness in table_private[].
		unsigned int seeds_sum = 0;
		for(int a = 0; a < 90; a++) {seeds_sum = ((seeds_sum + user_seeds[a]) % 1000000000);}
		srand(seeds_sum); //A new 9-digit seed comes from the sum of ALL user-seeds.
		for(int a = 0; a < 512000000; a++) //WRITES LEFT TO RIGHT.
		{	table_private[a] += (rand() % 95);
			table_private[a] %= 95;
		}
		
		//Again, adding additional randomness in table_private[].
		seeds_sum = 0;
		for(int a = 0; a < 90; a += 2) {seeds_sum = ((seeds_sum + user_seeds[a]) % 1000000000);}
		srand(seeds_sum); //Another new 9-digit seed comes from the sum of EVERY OTHER user-seed.
		for(int a = 511999999; a >= 0; a--) //WRITES RIGHT TO LEFT.
		{	table_private[a] += (rand() % 95);
			table_private[a] %= 95;
		}
		seeds_sum = 123456789; //Overwriting. (Only partially effective, printed/copied text is cloned from RAM to RAM.)
		
		//Writing all keys for channel incoming then all keys for channel outgoing (separately, reusing code.)
		mkdir("keys"           ,  0777); //Creates a folder. Folder-izing helps lighten resource usage by 1,000%.
		mkdir("./keys/incoming",  0777); //Creates a folder within that keys folder.
		mkdir("./keys/outgoing",  0777); //Creates another folder within that keys folder.
		char file_name_key_incoming[21] = "./keys/incoming/0000";
		char file_name_key_outgoing[21] = "./keys/outgoing/0000";
		
		//Writes keys to folder incoming.
		int table_private_read_bookmark = 0;
		int file_numbering = 1000000; //Only the last 4 digits are used, size makes mod operations easier.
		for(int a = 0; a < 2560; a++)
		{	out_stream.open(file_name_key_incoming);
			for(int b = 0; b < 100000; b++)
			{	out_stream.put(table_private[table_private_read_bookmark] + 32);
				
				table_private_read_bookmark++;
			}
			out_stream << '\0';
			out_stream.close();
			
			file_numbering++; //Adjusts file nunbering.
			int temp_file_numbering = file_numbering;
			file_name_key_incoming[19] = (temp_file_numbering % 10) + 48;//        ./keys/incoming/0  0  0  0    (file name)
			temp_file_numbering /=    10; //                                                       ^  ^  ^  ^
			file_name_key_incoming[18] = (temp_file_numbering % 10) + 48; //                      16 17 18 19    (element layout)
			temp_file_numbering /=    10;
			file_name_key_incoming[17] = (temp_file_numbering % 10) + 48;
			temp_file_numbering /=    10;
			file_name_key_incoming[16] = (temp_file_numbering % 10) + 48;
		}
		
		//Writes keys to folder outgoing, table_private_read_bookmark is not reset.
		file_numbering = 1000000; //Resetting. Only the last 4 digits are used, size makes mod operations easier.
		for(int a = 0; a < 2560; a++)
		{	out_stream.open(file_name_key_outgoing);
			for(int b = 0; b < 100000; b++)
			{	out_stream.put(table_private[table_private_read_bookmark] + 32);
				
				table_private_read_bookmark++;
			}
			out_stream << '\0';
			out_stream.close();
			
			file_numbering++; //Adjusts file nunbering.
			int temp_file_numbering = file_numbering;
			file_name_key_outgoing[19] = (temp_file_numbering % 10) + 48; //       ./keys/outgoing/0  0  0  0    (file name)
			temp_file_numbering /=    10; //                                                       ^  ^  ^  ^
			file_name_key_outgoing[18] = (temp_file_numbering % 10) + 48; //                      16 17 18 19    (element layout)
			temp_file_numbering /=    10;
			file_name_key_outgoing[17] = (temp_file_numbering % 10) + 48;
			temp_file_numbering /=    10;
			file_name_key_outgoing[16] = (temp_file_numbering % 10) + 48;
		}
		
		//Creates the encryption remaining counter file.
		out_stream.open("remaining.encrypt.txt");
		out_stream << "1600000 messages left to encrypt.\n\n"
		
		           << "Do not modify this file.\n"
		           << "This number must consist\n"
		           << "of digits 0000000 - 1600000.";
		out_stream.close();
		
		//Creates the decryption remaining counter file.
		out_stream.open("remaining.decrypt.txt");
		out_stream << "1600000 messages left to decrypt.\n\n"
		
		           << "Do not modify this file.\n"
		           << "This number must consist\n"
		           << "of digits 0000000 - 1600000.";
		out_stream.close();
		
		//Creates the symmetry entanglement file.
		out_stream.open("symmetry.entanglement");
		out_stream << "REMINDER: one of you must remove this file!\n"
		           << "(Key maker had already been asked to do so.)";
		out_stream.close();
		
		//Overwrites RAM of user_seeds[].
		for(int a = 0; a < 90; a++)
		{	user_seeds[a] = 123456789;
			user_seeds[a] = 987604321;
			user_seeds[a] = 0;
		} //Only partially effective, printed/copied text is cloned from RAM to RAM.
		
		//Overwrites RAM of array table_private[].
		for(int a = 0; a < 512000000; a++)
		{	for(int b = 0; b < 10; b++) {table_private[a] = b;}
		}
		
		cout << "\n\nFinished! Share this folder in private, then\n"
		     << "REMOVE file symmetry.entanglement on your end ONLY!\n\n";
	}
}
