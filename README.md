# Bare-metal programming of a STM32 card

Different steps of the project :
1. Creation of a simple executable
2. Using GPIO to make the board's led blink
3. Using UART to send and receive characters 
4. Using the led matrix to display animations and a static picture (from a raw file)
5. Using IRQ to make a led blink when pushing a button
6. Using IRQ + UART + led matrix to display animation sent by the computer
7. Using timers to generate interruptions
8. Moving the code to XIP 

How to use it
1. Use make to produce the executable file prog
2. Connect your STM32 board with the led matrix on you computer
3. Use make connect to launch the driver
4. Use make run to launch the cross-debugger
5. Use flash to load the executable
6. Use continue to run the code


