#include "show.h"

using namespace std;
/********************************************************************************
 * Aaron Willett
 * 02.15.24
 *
 * Show implementation (ADT): Constructor, Destructor and methods
 *
 * Methods:
 * remove_all()
 * display()
 * copy_entry(const Show & to_add)
 * add(char* name, char* genres, char* demos, char* history, char* critique)
 *
 *******************************************************************************/


Show::Show()
{
    name = nullptr;
    genres = nullptr;
    demos = nullptr;
    history = nullptr;
    critique = nullptr;
}

Show::~Show() // destructor
{
    if (name)
    {
        delete [] name;
        name = nullptr;
    }
    if (genres)
    {
        delete [] genres;
        genres = nullptr;
    }
    if (demos)
    {
        delete [] demos;
        demos = nullptr;
    }
    if (history)
    {
        delete [] history;
        history = nullptr;
    }
    if (critique)
    {
        delete [] critique;
        critique = nullptr;
    }
}

int Show::copy_entry(const Show & to_add)
{
    name = new char[strlen(to_add.name) + 1];
    strcpy(name, to_add.name);

    genres = new char[strlen(to_add.genres) + 1];
    strcpy(genres, to_add.genres);

    demos = new char[strlen(to_add.demos) + 1];
    strcpy(demos, to_add.demos);

    history = new char[strlen(to_add.history) + 1];
    strcpy(history, to_add.history);

    critique = new char[strlen(to_add.critique) + 1];
    strcpy(critique, to_add.critique);

    return 1;
}
        
int Show::display()
{
    cout << endl; // display data members of Show
    cout << "Title: " << name << "\tGenres: " << genres
        << "\nDemographics: " << demos << "\tViewing History: "
        << history << "\nCritic Response: " << critique << endl;
    return 1;
}

int Show::add(char * t_name, char * t_genres, char * t_demos, char * t_history, char * t_critique) 
{ // assigning arguments to data members of Show instance
  ERR err;

  // error handling. Cannot enter null values
  if (t_name[0] == '\0' ||
      t_genres[0] == '\0' ||
      t_demos[0] == '\0' ||
      t_history[0] == '\0' || 
      t_critique[0] == '\0')
  {
      err.code = 101;
      strcpy(err.msg, "Values cannot be empty.");
      throw err;
  }

  name = new char[strlen(t_name) + 1];
  strcpy(name, t_name);

  genres = new char[strlen(t_genres) + 1];
  strcpy(genres, t_genres);

  demos = new char[strlen(t_demos) + 1];
  strcpy(demos, t_demos);

  history = new char[strlen(t_history) + 1];
  strcpy(history, t_history);

  critique = new char[strlen(t_critique) + 1];
  strcpy(critique, t_critique);

  return 1;
}

bool Show::getName(char * key)
{ // if key matches data member name, return true
    if (strcmp(key, name) == 0) 
        return true;
    return false;
}

bool Show::getGenre(char * key)
{ // if key matches data member genre, return true
    if (strcmp(key, genres) == 0)
        return true;
    return false;
}

bool Show::clean()
{
    // manual data member deallocation
    if (name)
    {
        delete [] name;
        name = nullptr;
    }
    if (genres)
    {
        delete [] genres;
        genres = nullptr;
    }
    if (demos)
    {
        delete [] demos;
        demos = nullptr;
    }
    if (history)
    {
        delete [] history;
        history = nullptr;
    }
    if (critique)
    {
        delete [] critique;
        critique = nullptr;
    }

    return true;
}


bool again(void) // my attempt at recreating Karla's again();
{
    char entered;
       
    cout << "Repeat?\n>> ";
    cin >> entered; cin.ignore(1000, '\n');
    entered = toupper(entered);

    while (entered != 'Y' && entered != 'N')
    {
        cout << "Please enter Yes or No" << endl;
        cin.clear();
        cin >> entered; cin.ignore(1000, '\n');
        entered = toupper(entered);
    }

    if (entered == 'N')
        return false;
    return true;
}

int menu(void) // displays menu, takes user input and validates
{
    int choice {0};
 
     char options[200]{"Menu~\n1. Add Show\n2. "
        "Display all shows\n3. Search for show by name\n4. Search for show by genre\n5. Delete show by name\n"
        "6. Quit\n>> "};

     cout << options;
     cin >> choice;
     cin.ignore(1000, '\n');

     while (!cin || choice < 1 || choice > 6)
     {
         cout << "Invalid number. Try again.\n\n";
         cin.clear();
         cin.ignore(1000, '\n');
         cout << ">> ";
         cin >> choice;
         cin.ignore(1000, '\n');
     }

     return choice;
}
