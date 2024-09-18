# DCrypt
A C++ program, meant to decipher text without being given the cipher itself.

# THIS PROGRAM IS A WORK-IN-PROGRESS! #

Currently, the features of the program are as follows:
* Basic user I/O (via CLI)
* Simple file transfer
* Retaining file contents within an object (as to not rely on fstreams or similar for everything)
* Character frequency analysis.
* Simple ciphertext decryption.
* Tiny model training!

I intend, at some point, to introduce some kind of neural network to supplement the character frequency analysis: trained on classic English literature, my hope is that it will be able to deduce which characters in the ciphertext may be vowels or consonants, based on their frequency as compared to the English language. I also want to try and use Zipf's law, but right now, the focal data I'm working with (which inspired the project) does not appear to use words.

Feel free to monitor development, or suggest stuff.

# Running the Program #
As far as I can tell, all you need is the executable file. Run it. 
The source codes are also provided, if you're paranoid (like me) of random executables: I compiled it using G++.
You shouldn't need any fancy libraries: everything outside of the standard C++ libraries are provided (as header files).

Put all of the .hpp and .cpp files in the same directory: then, execute `compile.bat` from within that directory.
You will need to have G++ or a similar compiler added as a PATH environment variable (or whatever it's called) to do this.
You could also use Visual Studio or something. I'm not the boss of you.
