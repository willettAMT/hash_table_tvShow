#include "table.h"
#include <fstream>
#include <iostream>

using namespace std;

/********************************************************************************
 * Aaron Willett
 * 
 * Application (Client): prompts for user input and sends data to corresponding
 * functions to handle data
 *
 * Table: - organizing table of two hash tables
 *        - name_insert: takes name (c-string)and Show instance and inserts into hash_table
 *                       using name as the key for hashing
 *        - genre_insert: takes genre (c-string) and Show instance and inserts into
 *                        hash_table using genre as a key
 *        - retrieve: takes c-string and Show instance, and updates Show instance
 *                    with matching instance if one exists
 *        - remove:  takes c-string and Show instance, and updates Show instance
 *                   with matching instance if one exists, while deleting that
 *                   instance from memory
 *        - display_all: displays all instances of Show in memory
 *        - display_genre: takes c-string as argument, displays all Show instances
 *                         matching that entered key
 *
 * Show: organizes information about TV shows
 *       - display: displays TV show information
 *       - copy_entry: takes Show instance as an argument, & copies data to
 *                     show instance
 *       - add: takes 5 c-strings, and adds as data members to a instance of Show
 *       - getName: takes a c-string as an argument and returns a bool if match
 *                  is found
 *       - getGengre: takes a c-string as an argument and returns a bool if match
 *                  is found
 *       - clean: safely deletes data in an instance of Show
 *
 * showF: ifstream variable for reading external data file
 * miscellaneous: menu - prints menu and takes user input
 *                again - loops until user quits
*********************************************************************************/
const int BUF{100};

int main (void)
{

    Table show_table(ARR_SIZE, ARR2_SIZE);
    Show nShow;
    ifstream showF;
    char file_path[20]{"./show_file.txt"}, 
         menu_choice,
         input[BUF],
         nameBuf[BUF], 
         genreBuf[BUF], 
         demoBuf[BUF], 
         histBuf[BUF], 
         critBuf[BUF];
    bool fsBit{false};

//-----------LOADING DATA FROM EXTERNAL FILE---------------------------------//

    // Open external .txt
    showF.open(file_path);
    if (!showF.is_open())
        cerr << "Error opening file\n" << endl;

    while (showF.peek() != EOF)
    {
        showF.getline(nameBuf, MAX_CHAR, '|');
        showF.getline(genreBuf, MAX_CHAR, '|');
        showF.getline(demoBuf, MAX_CHAR, '|');
        showF.getline(histBuf, MAX_CHAR, '|');
        showF.getline(critBuf, MAX_CHAR, '\n');
        fsBit = showF.good();

        if (fsBit)
        {
            nShow.add(nameBuf, genreBuf, demoBuf, histBuf, critBuf);
            show_table.name_insert(nameBuf, nShow);
            show_table.genre_insert(genreBuf, nShow);
            nShow.clean();
        }
        else cout << "Error reading file" << endl;
    }
//------------------------------------------------------------------------//

    do
    {
        cout << "\n\n" << endl;
        menu_choice = menu ();
        switch (menu_choice)
        {
            /*
             * 1. Add Show
             * 2. Display all shows
             * 3. Search by Name
             * 4. Search by Genre
             * 5. Delete show by name
             * 6. Quit
             */
            case 1:
                do
                {
                    cout << "\n\nEnter name of show: ";
                    cin.getline(nameBuf, BUF); 
                    cout << "\n\nEnter genres of the show: ";
                    cin.getline(genreBuf, BUF); 
                    cout << "\n\nEnter demographics of the average viewer: ";
                    cin.getline(demoBuf, BUF); 
                    cout << "\n\nEnter viewing history: ";
                    cin.getline(histBuf, BUF); 
                    cout << "\n\nEnter critic's reception: ";
                    cin.getline(critBuf, BUF); 
                    try
                    {
                        nShow.add(nameBuf, genreBuf, demoBuf, histBuf, critBuf);
                        show_table.name_insert(nameBuf, nShow);
                        show_table.genre_insert(genreBuf, nShow);
                        nShow.clean();
                    }
                    catch (ERR err)
                    {
                        cerr << err.code << endl;
                        cerr << err.msg << endl;
                    }
                } while (again());
                break;

            case 2:
                try {
                    show_table.display_all(); cout << endl << endl;
                } 
                catch (ERR err)
                {
                    cerr << err.code << endl;
                    cerr << err.msg << endl;
                }
                break;
            case 3:
                do
                {
                    cout << "\n\nSearch for show by name: ";

                    try {
                        cin.getline(input, BUF);
                        cout << "entered: " << input << endl;

                        if (show_table.retrieve(input, nShow))
                        {
                            nShow.display();
                            nShow.clean();
                        }
                        else cerr << "Show not found" << endl;
                    }
                 
                    catch (ERR err)
                    {
                        cerr << err.code << endl;
                        cerr << err.msg << endl;
                    }
                    cout << endl << endl;
                } while (again());
                break;

            case 4:
                do
                {
                    cout << "Search by genre: ";
                    try
                    {
                        cin.getline(input, BUF);
                        if (!show_table.display_genre(input))
                            cout << "Shows not found" << endl;
                    }

                    catch (ERR err)
                    {
                        cerr << err.code << endl;
                        cerr << err.msg << endl;
                    }
                    cout << endl << endl;
                } while (again());
                break;

            case 5:
                do
                {
                    cout << "\n\nDelete show by name: ";
                    try {
                        cin.getline(input, BUF);
                        show_table.remove(input, nShow);
                        nShow.display();
                        nShow.clean();
                    }

                    catch (ERR err) {
                        cerr << err.code << endl;
                        cerr << err.msg << endl;
                    }
                    cout << endl << endl;
                } while (again());
                break;

            case 6:
                cout << endl << endl;
                cout << "quitting\n\n" << endl; break;

            default: cout << "Must enter menu number. Try again.\n\n" <<endl; break;
        }

    } while (menu_choice != 6);

    // Close external .txt
    showF.close();
    if (showF.is_open())
        cerr << "Error closing file\n" << endl;

    return 0;
}
