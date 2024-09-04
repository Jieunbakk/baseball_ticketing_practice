#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <curses.h>
#include <sys/time.h>

#define ROWEND 15
#define ROWSTART 5
#define COLSTART 5
#define COLEND 15
#define DELAY 30

char seatMap[10][10];

int set_ticker(int);


int is_selected_all(){
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if(seatMap[i][j] == '0')
            	return 0;
        }
    }
    return 1;
}

void displaySeatMap(int signum) {
    int x, y;
    while (is_selected_all() == 0) {
        x = rand() % 10;
        y = rand() % 10;
        if (seatMap[x][y] == '0')
            break;
    }
    if(is_selected_all() == 0){
    	seatMap[x][y] = '-';
    	move(x+ROWSTART, y+COLSTART);
    	addstr("-");
    }
    refresh();
}


void ticketingProcess() {
    move(0, 0);
    addstr("Ticketing in progress...  	");
    refresh();

    for (int i = 5; i > 0; i--) {
        sleep(1);
        char buffer[10];
        sprintf(buffer, "%d..", i);
        addstr(buffer);
        refresh();
    }
    
    move(2, 0);
    addstr("Enter seat coordinates (ROW COL) (ROW:0~9, COL:0~9): ");
    refresh();

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            seatMap[i][j] = '0';
        }
    }
    
    for (int i = ROWSTART; i < ROWEND; ++i) {
        for (int j = COLSTART; j < COLEND; ++j) {
            move(i, j);
            addstr("0");
        }
    }
    refresh();
    
    signal(SIGALRM, displaySeatMap);
    set_ticker(DELAY);
    
    int x,y;
    int flag=0;
    while(is_selected_all()== 0){
        scanw("%d %d", &x, &y);
        if (x >= 0 && x < 10 && y >= 0 && y < 10 && seatMap[x][y] == '0') {
        	move(x+ROWSTART, y+COLSTART);
        	addstr("!");
        	move(3,0);
        	char buffer[30];
        	sprintf(buffer,"Success! your seat is (%d, %d)	", x, y);
        	addstr(buffer);
        	refresh();
        	signal(SIGALRM,SIG_DFL);
        	set_ticker(10000);
        	sleep(5);
        	exit(1);
        } else {
            move(3, 0);
            addstr("Invalid coordinates. Try again.	");
            refresh();
        }
        
    }
    
    move(3,0);
    addstr("Fail. All seats are selected.	");
    refresh();
    signal(SIGALRM,SIG_DFL);
    set_ticker(10000);
    sleep(5);
    exit(1);
   
   
}

int main() {
    char choice;
    initscr();
    cbreak();
    noecho();
    timeout(0);

    while (1) {
        move(0, 0);
        addstr("Do you want to start baseball ticketing practice? (Y/N): ");
        refresh();
        timeout(-1);
        choice = getch();

        if (choice == 'Y' || choice == 'y') {
            pid_t pid = fork();

            if (pid == -1) {
                perror("Fork failed");
                exit(EXIT_FAILURE);
            }

            if (pid == 0) {
                // Child process
                clear();
                ticketingProcess();
                exit(EXIT_SUCCESS);
            } else {
                // Parent process
                wait(NULL);
                clear();
                
            }
        } else if(choice=='N' || choice=='n'){
            break;
        }
    }

    endwin();
    return 0;
}

int set_ticker(int n_msecs) {
    struct itimerval new_timeset;
    long n_sec, n_usecs;

    n_sec = n_msecs / 1000;
    n_usecs = (n_msecs % 1000) * 1000L;

    new_timeset.it_interval.tv_sec = n_sec;
    new_timeset.it_interval.tv_usec = n_usecs;
    new_timeset.it_value.tv_sec = n_sec;
    new_timeset.it_value.tv_usec = n_usecs;

    return setitimer(ITIMER_REAL, &new_timeset, NULL);
}

