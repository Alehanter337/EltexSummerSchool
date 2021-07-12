#include "main.h"
#include <curses.h>
#include <stdio.h>

typedef struct Coords {
    int row;
    int col;
} Coords;

volatile sig_atomic_t signal_status = 0;

void sighandler(int s) {
    signal_status = s;
}

void init() {
    initscr();
    savetty();
    curs_set(1);
    keypad(stdscr, TRUE);
    mousemask(BUTTON1_CLICKED, NULL);
    signal(SIGINT, sighandler);
    signal(SIGQUIT, sighandler);
    signal(SIGWINCH, sighandler);
    signal(SIGTSTP, sighandler);
}

void finish() {
    curs_set(1);
    clear();
    refresh();
    resetty();
    endwin();
    exit(0);
}

void finish_fd_error(int fd){
    perror("Can't open this file\n");
    close(fd);
    curs_set(1);
    clear();
    refresh();
    resetty();
    endwin();
    exit(1);
}

void finish_read_error(int fd) {
    perror("Can't read this file\n");
    close(fd);
    curs_set(1);
    clear();
    refresh();
    resetty();
    endwin();
    exit(2);
}

void read_file(int fd) {
    int cursor_pos = (int) lseek(fd, 0, SEEK_END);
    char buffer[cursor_pos];
    lseek(fd, 0, SEEK_SET);  
    
    if(read(fd, buffer, sizeof(buffer)) < 0) 
        finish_read_error(fd);

    for(int i = 0; i < cursor_pos; i++)
        printw("%c", buffer[i]);
    
    close(fd);
}

void open_file(char *file_name) {
    int fd = -1;
    move(0, 0);
    if((fd = open(file_name, O_RDONLY)) < 0)
        finish_fd_error(fd);
    
    read_file(fd);
}

void save_file(char *file_name) {
    FILE* fd = fopen(file_name, "w");
     
    for(int i = 0; i < LINES; i++)
        for(int j = 0; j < COLS; j++)
            putc(mvinch(i, j) & A_CHARTEXT, fd);
    
    move(0, 0);
    fclose(fd);
}



void logic() {
    int keypress = wgetch(stdscr);
    char file_name[20];
    Coords cursor;
    cursor.row = 0;
    cursor.col = 0;
    getyx(stdscr, cursor.row, cursor.col);
    
    if(keypress == ERR) return;

    switch (keypress) {
        case KEY_LEFT:
            move(cursor.row, cursor.col - 1);
            break;
        
        case KEY_UP:
            move(cursor.row - 1, cursor.col);
            break;

        case KEY_DOWN:
            move(cursor.row + 1, cursor.col);
            break;

        case KEY_RIGHT:
            move(cursor.row, cursor.col + 1);
            break;
         
        case KEY_F(1):
            printw("Input filename\n");
            wgetnstr(stdscr, file_name, 20);
            open_file(file_name);
            break; 
         
        case KEY_F(2):
            save_file("new_text");
            break;
         
        case KEY_F(3):
            finish();
            break;

        case KEY_BACKSPACE:
            getyx(stdscr, cursor.row, cursor.col);
            mvwaddch(stdscr, cursor.row, cursor.col, ' ');
            refresh();
            move(cursor.row, cursor.col);
            break; 
    }
}

int main(void) {
    init();
    while(1) {
        logic();
        refresh();
    }
    finish();
    return 0;
}
