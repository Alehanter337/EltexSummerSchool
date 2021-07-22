#include <asm-generic/ioctls.h>
#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

volatile sig_atomic_t signal_status = 0;

void sighandler(int s) {
    signal_status = s;
}

void init() {
    initscr();
    savetty();
    curs_set(0);
    cbreak();
    noecho();
    //keypad(stdscr, TRUE);
    //mousemask(BUTTON1_CLICKED, NULL);
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
}

void print_left_border(struct winsize size, int mid, WINDOW **border_left_win)
{
    *border_left_win = newwin(size.ws_row, mid, 0, 0);
    box(*border_left_win, '|', '-');
    if (*border_left_win == NULL)
    {
        finish();
        exit(-1);
    }
    wrefresh(*border_left_win);
}

void print_right_border(struct winsize size, int mid, WINDOW **border_right_win)
{
    *border_right_win = newwin(size.ws_row, mid, 0, mid);
    box(*border_right_win, '|', '-');
    if (*border_right_win == NULL)
    {
        finish();
        exit(-2);
    }
    wrefresh(*border_right_win);
}

void print_left_win(struct winsize size, int mid, WINDOW **border_left_win, WINDOW **left_win)
{
    *left_win = derwin(*border_left_win, size.ws_row - 2, mid - 2, 1, 1);
    if (*left_win == NULL)
    {
        finish();
        exit(-3);
    }
}

void print_right_win(struct winsize size, int mid, WINDOW **border_right_win, WINDOW **right_win)
{
    *right_win = derwin(*border_right_win, size.ws_row - 2, mid - 2, 1, 1);
    if (*right_win == NULL)
    {
        finish();
        exit(-4);
    }
}

int main(void)
{
    init();

    //Размер окна
    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    int mid = size.ws_col / 2;
    
    //Цвета
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_YELLOW);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);

    //Рамки
    WINDOW *border_left_win;
    WINDOW *border_right_win;
    print_left_border(size, mid, &border_left_win);
    print_right_border(size, mid, &border_right_win);

    //Окна
    WINDOW *left_win;
    WINDOW *right_win;
    print_left_win(size, mid, &border_left_win, &left_win);
    print_right_win(size, mid, &border_right_win, &right_win);

    napms(3000);
    
    finish();
    return 0;
}
