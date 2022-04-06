

# PESAssignment-6 Breakfast Serial
Spring 2022, 
Written By **Chinmay Shalawadi**
University of Colorado Boulder, ECEE
chsh1552@colorado.edu
References -> **Lecture Slides ,Dean Text Book, Disassembly from MCUXpresso**

UART0 of the KL25Z has been configured to the following parameters

 - Baud Rate - 38400
 - Stop Bits - 2
 - Parity - No Parity
 - Over sample rate - 16

This program implements a command processor with the following commands.

 - DUMP
 - HELP
 - AUTHOR
 
 The commands are case insensitive

If the DEBUG Flag is set, CBFIFO tests are run and
the result is displayed before the command processor is called.

SCREENSHOTS have been included in the repository.

## Extra Credit - Backspace

 - Backspace Key and extra white spaces has been handled as part of Extra Credit
 

## Extra Credit - Help Command

 - Help command has been implemented as a part of Extra credit. 


    
