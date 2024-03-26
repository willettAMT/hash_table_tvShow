#include "table.h"
#include <iostream>

/********************************************************************************
 * Aaron Willett
 * 02.15.24
 *
 * Table class: ADT for hash-table
 *
 * Methods:
 * name_insert
 * genre_insert(char* key, const Show & to_add);   
 * retrieve(char* search_val, Show & found);
 * remove(char* key, Show & to_remove);
 * display_all(void);
 * display_genre(char* key);
 * retrieve(node *& curr, char* search_val, Show &found);
 * remove(node *& prev, node *& curr, char* search_val, Show &to_remove);
 * hash_function(char*key) const;
 * second_hash(char*key) const;
 * table_size;
 * display_all(node *& curr);
 * display_genre(node *&curr, char*key);
 *
 *******************************************************************************/

Table::Table(const int h_size, const int g_size)
{
    int h_index, g_index;

    ht_size = h_size; // ARR_SIZE
    gt_size = g_size; // ARR2_SIZE 
    // allocating both hash_tables
    hash_table = new node*[ht_size];
    genre_table = new node*[gt_size];
    // local variables for constructor
    h_index = (ht_size - 1);
    g_index = (gt_size - 1);
    // iterate through allocating nullptrs for all pointers
    while (h_index >= 0)
    {
        hash_table[h_index] = nullptr;
        --h_index;
    }
    
    while (g_index >= 0)
    {
        genre_table[g_index] = nullptr;
        --g_index;
    }
}

Table::~Table()
{
    int h_index = (ht_size - 1), g_index = (gt_size - 1);
    // iterate through existing hash_tables, deleting ptrs and assigning nullptrs
    while (h_index >= 0)
    {
        while (hash_table[h_index])
        {
            node* temp = hash_table[h_index]->next;
            delete hash_table[h_index];
            hash_table[h_index] = temp;
        }
        hash_table[h_index] = nullptr;
        --h_index;
    }

    while (g_index >= 0)
    {
        while (genre_table[g_index])
        {
            node* _temp = genre_table[g_index]->next;
            delete genre_table[g_index];
            genre_table[g_index] = _temp;
        }
        genre_table[g_index] = nullptr;
        --g_index;
    }
// delete hash tables
    delete [] hash_table;
    delete [] genre_table;
    ht_size = 0;
    gt_size = 0;
}


int Table::name_insert(char* key, const Show& to_add)
{
    unsigned int index = hash_function(key);

    node * nShow = new node;
    nShow->show.copy_entry(to_add);
    nShow->next = nullptr;

    if (hash_table[index] == nullptr) // insert as first pointer to a node
    {
        hash_table[index] = nShow;
        nShow->next = nullptr;
        return 1;
    }

    nShow->next = hash_table[index]; // new pointer becomes first node 
    hash_table[index] = nShow;
    
    return 1;
}

int Table::genre_insert(char* key, const Show& to_add)
{
    unsigned int index = second_hash(key);

    node * nShow = new node;
    nShow->show.copy_entry(to_add);
    nShow->next = nullptr;

    if (genre_table[index] == nullptr)
    {
        genre_table[index] = nShow;
        nShow->next = nullptr;
        return 1;
    }

    nShow->next = genre_table[index];
    genre_table[index] = nShow;
    
    return 1;
}

int Table::hash_function(char* key) const
{
    const int PRIME_A = 54059;
    const int PRIME_B = 76963;
    const int PRIME_C = 37;

    unsigned int index{static_cast<unsigned int>(ht_size)};

    while (*key)
    {
        key[0] = tolower(key[0]);
        //        index = (index * PRIME_A) ^ (key[0] * PRIME_B);
        //        index += (PRIME_A * ARR_SIZE) ^ (key[0] * PRIME_B);
        index += ((PRIME_C * PRIME_A) ^ (key[0] * PRIME_B));
        ++key;
    }
    return (index % ht_size);
}

int Table::second_hash(char* key) const
{
    const int PRIME_A = 54059;
    const int PRIME_B = 76963;
    const int PRIME_C = 79;

    unsigned int index{static_cast<unsigned int>(gt_size)};

    while (*key)
    {
        key[0] = tolower(key[0]);
        index = (index * PRIME_A) ^ (key[0] * PRIME_B);
        //index = (PRIME_A * PRIME_B) ^ (key[0] * PRIME_C);
        //index += ((PRIME_C * PRIME_A) ^ (key[0] * PRIME_B));
        ++key;
    }
    return (index % gt_size);
}

int Table::retrieve(char* search_val, Show& found)
{
    unsigned int index{0};
    char* copy = new char[strlen(search_val) + 1];
    strcpy(copy, search_val);
    index = hash_function(copy);

    delete [] copy;    
    return retrieve(hash_table[index], search_val, found);
}

int Table::retrieve(node*& curr, char* search_val, Show& found)
{
    ERR err;
    if (!curr) // value not found
    {
        err.code = 451;
        strcpy(err.msg, "Show not found");
        throw err;
    }

    if (curr->show.getName(search_val))
    {
        found.copy_entry(curr->show);
        return 1;
    }
    return retrieve(curr->next, search_val, found); // recursive function call
}

int Table::display_all(void) 
{
    Show show;
    int retrieved{0};

    // access all indices in hash_table, and display from every node on the LLL
    for (int i = 0; i < ARR_SIZE; ++i)
    {
        retrieved = display_all(hash_table[i]); // recursive function call
    }

    return retrieved;
}


int Table::display_all(node*& curr) // recursive function
{
    ERR err;
    if (!curr) return 1;

    if (!curr->show.display())
    {
        err.code = 10;
        strcpy(err.msg, "Error displaying data");
        throw err;
    }

    return display_all(curr->next);
}
        
int Table::display_genre(char* key)
{
    unsigned int index{0};
    char* copy = new char[strlen(key) + 1];
    strcpy(copy, key);
    index = second_hash(copy);
    delete [] copy;

    return display_genre(genre_table[index], key);
}

int Table::display_genre(node*& curr, char* key)
{
    ERR err;
    if (!curr) return 1;
    
    if (curr->show.getGenre(key)) // if getGenre returns true, display
        curr->show.display();

    return display_genre(curr->next, key);
}

int Table::remove(char* search_val, Show& to_remove)
{
    ERR err;
    unsigned int index{0};
    char* copy = new char[strlen(search_val) + 1]; // creates copy of key to hash
    strcpy(copy, search_val); //creates copy of key to hash
    index = hash_function(copy); // get index from Hash function
    delete [] copy;

    if (hash_table[index] == nullptr) // Check if we hit nullptr with hash function- throw exception of
    {                                      // indexes to empty array val
        err.code = 911;
        strcpy(err.msg, "BAD INDEXING");
        throw err;
    }

    if (hash_table[index]->show.getName(search_val)) // if search_val matches first node's value
    {
        if (hash_table[index]->next) // hold on to rest of list of first val needs to be deleted
        {
            node* temp = hash_table[index]->next;
            to_remove.copy_entry(hash_table[index]->show);
            delete hash_table[index];
            hash_table[index] = temp;
            return 1;
        }

        to_remove.copy_entry(hash_table[index]->show);
        delete hash_table[index];
        hash_table[index] = nullptr;
        return 1;
    }

    return remove(hash_table[index], hash_table[index]->next, search_val, to_remove);
}

int Table::remove(node*& prev, node*& curr, char* search_val, Show &to_remove)
{
    ERR err;

    if (!curr) // reached end of list without removing
    {
        err.code = 401;
        strcpy(err.msg, "No match. Removal aborted");
        throw err;
    }


    if (curr->show.getName(search_val)) // found show to remove at curr
    {
        if (!curr->next) // curr is last node in list
        {
            to_remove.copy_entry(curr->show);
            delete curr;
            curr = nullptr;
            return 1;
        }

        to_remove.copy_entry(curr->show); // curr is middle of list
        node * temp = curr->next;
        delete curr;
        curr = temp;
        return 1;
    }

    return remove(prev->next, curr->next, search_val, to_remove);
}
