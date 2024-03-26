#include <cctype>
#include <cstring>
#include <iostream>

/********************************************************************************
 * Aaron Willett
 *
 * Prototypes for Show class
 * Prototypes for menu() again()
 *******************************************************************************/

#ifndef SHOW_H 
#define SHOW_H

const int MAX_CHAR = 100;

struct ERR
{
    int code{0};
    char msg[MAX_CHAR]{"Exception thrown"};
};

class Show
{
    public:
        Show();
        ~Show(void);
        int remove_all();
        int display();
        int copy_entry(const Show & to_add);
        int add (char *name, char *genres, char *demos, char *history, char *critique);
        bool getName(char *key);
        bool getGenre(char *key);
        bool clean();
    private:
        char * name;
        char * genres;
        char * demos;
        char * history;
        char * critique;
};

int menu(void);
bool again(void);
#endif
