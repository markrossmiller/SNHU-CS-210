# SNHU-CS-210
CS-210 Programming Languages

# Summarize the project and what problem it was solving.
This project was a C++ program that classifies animals into two types, Oviparous or Mammal, then stores information about individual animals of those types and retrieves the information back again. It stores the information in memory in a C++ class found in Animal.h and Animal.cpp

# What did you do particularly well?
I think the part that I felt I did best at was the code which read in or printed out the animal information to zoodata.txt

# Where could you enhance your code? How would these improvements make your code more efficient, secure, and so on?
I think the part of the program that could have used more work would be error checking for bad input. As it is now, I only handled minimum amounts of malformed input and if I had to have this working for a production environment, I'd have created a program that checked its inputs with more care and consideration.

# Did you find writing any piece of this code challenging, and how did you overcome this? What tools and/or resources are you adding to your support network?
The parts of the code I found most challenging were where I had to implement fixed-length strings for output to zoodata.txt; it was challenging because I didn't know how to do it with C++ strings easily, so what I ended up using were C-language char*'s.

# What skills from this project will be particularly transferable to other projects and/or course work?
The skills which will be most transferrable to other projects and course work will be my new knowledge of C++ classes. Learning about classes gave me new insights in how to deal with sets of data, which I'd have otherwise created using structs and just plain functions without the wrappings of a class file.

# How did you make this program maintainable, readable, and adaptable?
I tried to keep comments where something was perhaps not completely understandable by raw code. I also tried to organize my code into functions which made sense for what I was doing, keeping things separated out from main(). Since I put all the animal class stuff in Animal.h and Animal.cpp, it should be re-usable if need be in the future.
