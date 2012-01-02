//
//  main.c
//  test
//
//  Created by Adam Mclain on 1/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


//#include <stdio.h>
//#include <stdlib.h>
#include <signal.h>
#include <ncurses.h>
#include <time.h>   

void updateTitleBar(WINDOW *local_win);

int main()
{	int ch;
    char answer1[80];
    char answer2[80];
    char answer3[80];
    
	initscr();
	keypad(stdscr, TRUE);
    cbreak();
    
    WINDOW *titleBar;
    WINDOW *mainWindow;
    
    titleBar = newwin(1, COLS, 0, 0);
    mainWindow = newwin(LINES -1, COLS, 1, 0);
    
    // while (1) {
    updateTitleBar(titleBar);
    // }
    
    getch();
    
    char eventName[10000];
    
    FILE *cal;
    cal=fopen("cal.txt", "r");
    
    
    while (fscanf(cal, "%[^\n]\n", eventName) !=EOF) {
        printw("%s\n", eventName);
    }
    fclose(cal);
    
    
    wprintw(mainWindow, "Set three goals for the day:\n1.\n2.\n3.");
    wmove(mainWindow, 1, 3);
    wrefresh(mainWindow);
    getstr(answer1);
    wmove(mainWindow, 2, 3);
    wrefresh(mainWindow);
    getstr(answer2);
    wmove(mainWindow, 3, 3);
    wrefresh(mainWindow);
    getstr(answer3);
    noecho();
    erase();
    
    FILE *fp;
    fp=fopen("test.txt", "w");
    fprintf(fp, "%s,%s,%s,", answer1,answer2,answer3);
    fclose(fp);
    
    /*
     int lunch;
     printw("What is your plan for lunch?\n");
     printw("1. pack/will pack\n");
     printw("2. eat out\n");
     printw("3. skip\n");
     echo();
     lunch = getch();
     noecho();
     erase();
     
     int dinner;
     printw("What is your plan for dinner?\n");
     printw("1. cook\n");
     printw("2. eat out\n");
     printw("3. skip\n");
     echo();
     dinner = getch();
     noecho();
     erase();
     */
    
    printw("Have a great day!");
    
    
	ch = getch();			/* If raw() hadn't been called
                             * we have to press enter before it
                             * gets to the program 		*/
	if(ch == KEY_F(1))	{	/* Without keypad enabled this will */
		printw("F1 Key pressed");/*  not get to us either	*/
        /* Without noecho() some ugly escape
         * charachters might have been printed
         * on screen			*/
    } else if (ch == '1') {
        attron(A_BOLD | A_UNDERLINE);
        printw("You pressed 1!!!");
        attroff(A_BOLD | A_UNDERLINE);
    }
    else
	{	printw("The pressed key is ");
		attron(A_BOLD);
		printw("%c", ch);
		attroff(A_BOLD);
	}
	refresh();			/* Print it on to the real screen */
    getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */
    
    
	return 0;
}

void updateTitleBar(WINDOW *local_win) {
    time_t t;
    time(&t);
    wmove(local_win, 0, 0);
    wrefresh(local_win);
    clrtoeol();
    wprintw(local_win, "%s", ctime(&t));
    wrefresh(local_win);
}