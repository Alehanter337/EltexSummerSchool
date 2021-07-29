#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define DATAFILE "/var/chance.data"    //Тут хранятся пользовательские данные

//Структура хранит данные о пользователе
struct user
{
    uid_t uid;
    int credits;
    int highscore;
    char name[100];
    int (*curr_game) ();

};

//Прототипы функций
int get_player_data();
void register_new_player();
void update_player_data();
void show_highscore();
void jackpot();
void input_name();
void print_cards(char *, char *, int);
int take_wager(int, int);
void play_the_game();
int pick_a_number();
int dealer_no_match();
int find_the_ace();
void fatal(char *);

//Глобальные переменные
struct user player;    //Структура хранит данные игрока

int main(void)
{
    int choice = 0;
    int last_game = 0;

    srand(time(NULL));
        
    if(get_player_data() == -1)
    {
        register_new_pleyer();
    }

    while(choice != 7)
    {
        printf("-=[ Game of Chance Menu ]=-\n");
        printf("1 - Play the Pick a Number game\n");
        printf("2 - Play the No Match Dealer game\n");
        printf("3 - Play the Find the Ace game\n");
        printf("4 - View current high score\n");
        printf("5 - Change your user name\n");
        printf("6 - Reset your account at 100 credits\n");
        printf("7 - Quit\n");
        printf("[Name: %s]\n", player.name);
        printf("[You have %u credits] -> ", player.credits);
        scanf("%d", &choice);
        
        if(choice < 1 || choice > 7)
        {
            printf("\n[!!] The number %d is an invalid selection.\n\n", choice);
        }
        else if(choice < 4)
        {
            if(choice != last_game)
            {
                if(choice == 1)
                {
                    player.curr_game = pick_a_number;
                }
                else if(choice == 2) 
                {
                    player.curr_game = dealer_no_match;
                }
                else
                {
                    player.curr_game = find_the_ace;
                }
                last_game = choice;
            }
            play_the_game();
        } 
        else if(choice == 4)
        {
            show_highscore();
        }
        else if(choice == 5)
        {
            printf("\nChange user name\n");
            printf("Enter your new name: ");
            input_name();
            printf("Your name has been changed.\n\n");
        }
        else if(choice == 6)
        {
            printf("\nYour account has been reset with 100 credits.\n\n");
            player.credits = 100;
        }
    }
    update_player_data();
    printf("\nThanks for playing! Bye.\n");
}
void fatal(char *message) 
{
      char error_message[100];
      strcpy(error_message, "[!!] Fatal Error ");
      strncat(error_message, message, 83);
      perror(error_message);
      exit(EXIT_FAILURE);
}

void *ec_malloc(unsigned int size) 
{
    void *ptr;
    ptr = malloc(size);
    if(ptr == NULL)
    {
        fatal("in ec_malloc() on memory allocation");
    }  
    return ptr;
}

int get_player_data()
{
    int fd;
    int read_bytes;
    uid_t uid;
    
    struct user entry;

    uid = getuid();
    
    fd = open(DATAFILE, O_RDONLY);
    
    if(fd == -1)
    {
        return -1;
    }

    read_bytes = read(fd, &entry,sizeof(struct user));
    
    while(entry.uid != uid && read_bytes > 0)
    {
        read_bytes = read(fd, &entry, sizeof(struct user));
    }
    
    close(fd);

    if(read_bytes < sizeof(struct user))
    {
        return -1;
    }
    else 
    {
        player = entry;
    }
    
    return 1;
}

void register_new_player() 
{
    int fd;
    printf("-=-={ New Player Registration }=-=-\n");
    printf("Enter your name: ");
    
    input_name();
    
    player.uid = getuid();
    player.highscore = player.credits = 100;
    
    fd = open(DATAFILE, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR);
    
    if(fd == -1)
    {
        fatal("in register_new_player() while opening file");
    }
    
    write(fd, &player, sizeof(struct user));
    
    close(fd);
    
    printf("\nWelcome to the Game of Chance %s.\n", player.name);
    printf("You have been given %u credits.\n", player.credits);
}

void input_name() 
{
    char *name_ptr, input_char= '\n';
    while(input_char == '\n')
    {
        scanf("%c", &input_char);          // символы перевода строки.
    }
    
    name_ptr = (char *) &(player.name);    // name_ptr = адрес имени игрока
    
    while(input_char != '\n') 
    {                                      // Повторять до перевода строки.
      *name_ptr = input_char;              // Поместить введенный символ в поле name.
      scanf("%c", &input_char);            // Получить следующий символ.
      name_ptr++;                          // Увеличить указатель.
    }
   
    *name_ptr = 0;                         // Завершить строку.
}

