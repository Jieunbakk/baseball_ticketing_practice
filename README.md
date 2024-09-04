# baseball_ticketing_practice_Program

This is a practice program for baseball ticketing, designed to simulate the experience of selecting and securing a seat. The program is compiled and run in a Linux environment.

## Compilation and Execution

To compile the program, use the following command in your terminal:

```bash
make
```
or
```bash
make baseball_ticketing
```

After the program is successfully compiled, you can run it using:
```bash
./baseball_ticketing
```

## How to Play
1. When prompted, if you want to practice baseball ticketing, input y or Y. If you do not want to practice, input N or n.
2. A timer will appear at the top of the screen. The ticketing process will begin after 5 seconds.
3. Seats will be displayed on the screen, and you can select a seat by entering the row and column numbers in the format row col and pressing Enter.
Example: To select seat (3, 3), type 3 3 (with a space between the numbers) and press Enter.
4. Unselected seats are displayed as 0, while selected seats are displayed as -.
5. If you successfully secure a seat, your selected seat will be displayed as !, and the program will end after 5 seconds.
6. If you fail to secure a seat, you must press Enter (required), and the program will end after 5 seconds.
7. The game will then restart from step 1.
