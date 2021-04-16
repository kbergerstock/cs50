# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

An invented word that is a synonym to silicosis, which is a lung disease caused by a very fine dust or ash.

## According to its man page, what does `getrusage` do?

obtains resource usage statistics.

## Per that same man page, how many members are in a variable of type `struct rusage`?

sixteen

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

Passing a reference is faster and uses less stack space.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

Open text input file
Reset word buffer
# start of loop
Read the file one character at a time, until END_OF_FILE is found.
	#process the char
	If the character is in the alphabet or is an apostrophe
		Add it to buffer  holding the current word.
		If the word buffer exceeds maximum allowed
            Reset word buffer
            Read the file  until a non alphanumeric character is found
    Otherwise if the character is a number		
		Reset word buffer
        Read the file  until a non alphanumeric character is found
    And finally  the character must be a word terminator so
    	Null terminate the word buffer
    	If  Checking the words spelling against the dictionary is false
    		Print out misspelled word
        Update counters and benchmarks
        Reset the word buffer
#end of loop
close file
print benchmarks

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

fscanf is unpredictable on how it handles input (garbage especially, can cause buffer overflows), 
fgetc is safe and predictable, therefore giving exact control over the input. 

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

A const parameter (const  char *word), means that the module can NOT change the contents of the parameter,
the compiler will generate an error if you try to do so.
This allows data to be used by other modules knowing that no changes were made to it.
