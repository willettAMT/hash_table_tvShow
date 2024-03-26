#include "show.h"

/********************************************************************************
 * Aaron Willett
 *
 * Prototypes for Table class
 * Prototypes for menu() again()
 * Definition of node for handling nodes on Table
 *******************************************************************************/

#ifndef TABLE_H
#define TABLE_H

const int ARR2_SIZE = 31;
const int ARR_SIZE= 97;

struct node
{
    Show show; //show instance
    node * next;
};

class Table
{
    public:
        Table(const int h_size, const int g_size);     
        ~Table(void);
        int name_insert(char * key, const Show & to_add);   
        int genre_insert(char * key, const Show & to_add);   
        int retrieve(char * search_val, Show & found);
        int remove(char * key, Show & to_remove);
        int display_all(void);
        int display_genre(char * key);
    private:
        node ** genre_table;
        node ** hash_table;  
        int gt_size;
        int ht_size;
        int retrieve(node *& curr, char * search_val, Show &found);
        int remove(node *& prev, node *& curr, char * search_val, Show &to_remove);
        int hash_function(char *key) const;
        int second_hash(char *key) const;
        int table_size;
        int display_all(node *& curr);
        int display_genre(node *&curr, char *key);
};

#endif
