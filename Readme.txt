Samnang San
CIS-154-01A
Project 1:The Most Useful Machine
The most useful machine is a machine that gives users option on what they can let the machine do. a menu gives users selections from 1-9. users are prompted for information and results are displayed.
When i first compiled, i kept getting an error messages. i googled and you have to use -lm flag to use math functions in C. sources will be provided below
instruction:
Compile gcc Project_00291786.c -lm
File a.out is made, run program ./a.out
menu will be displayed for user to select options 1-9

Completion Statement
    Most of the requirements in the assignments were completed. Menu displayed with use of switch. i was stuck an issue with the switch where it kept adding a new line when user selected option, sometimes not allowing user to even select,received some help from tutor and also have source below,.Another part of the program i could not figure out was the "is not a letter" section. Both inputs were made to be true.
    there was an extra function i added called getanswer() where if it returns 1 its true, if 0 false.The most difficult part of the project was finding out all the math with the rounding, closeenough and powpow. i received help from a tutor on those three sections of the project. Everything else took significant time to complete but i did my best.


    sources i used:
    https://www.tutorialspoint.com/c_standard_library/c_function_getchar.htm
    https://medium.com/@larmalade/gcc-the-hard-way-how-to-include-functions-from-the-math-library-1cfe60f24a7a