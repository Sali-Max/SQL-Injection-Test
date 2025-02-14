#include <iostream>
#include <sqlite3.h>
#include <string>
#include <unistd.h> //system()

using namespace std;

class User  
{
private:
    int ID;
    string full_name;
    string password;
    int Student_code;
    bool admin;
public:
    User(string fullname, string pass, int stCode, bool isAdmin)
    {
        full_name = fullname;
        password = pass;
        Student_code = stCode;
        admin = isAdmin;
    }
    void set_full_name(string name)
    {
        full_name = name;
    }
    void set_password(string pass)
    {
        password = pass;
    }
    string getId()
    {
        return to_string(ID);
    }
    bool is_admin()
    {
        return admin;
    }
    void set_admin(bool isAdmin)
    {
        admin = isAdmin;
    }
    string get_name()
    {
        return full_name;
    }
    void setID(int id)
    {
        ID = id;
    }
    string get_password()
    {
        return password;
    }
    void print_all_detail()
    {
        printf("\n full_name: %s \n password: %s \n code_number: %i \n isAdmin %b", full_name.c_str(), password.c_str(), Student_code, admin);
    } 
};

// Login Function
User Login(string user, string pass, string code, sqlite3* db)
{
    string command = "SELECT * FROM users WHERE username='" + user +  "' AND password='" + pass +  "' AND code='" + code + "'; ";

    sqlite3_stmt* stmt;
    int stt = sqlite3_prepare_v2(db, command.c_str(), -1, &stmt, nullptr);
    if(stt != SQLITE_OK)    // Database Error Handled
    {
        printf("Error: Send Data To DataBase");
        sqlite3_close(db);
        exit(1);

    }

    if(sqlite3_step(stmt) != SQLITE_ROW) // Not Found
    {
        printf("Error: User OR Password");
        sqlite3_close(db);
        exit(1);
    }

    const unsigned char* usernameC = sqlite3_column_text(stmt, 1);
    const unsigned char* passwordC = sqlite3_column_text(stmt, 2);
    const int codenumber = sqlite3_column_int(stmt, 3);
    const int admin = sqlite3_column_int(stmt, 4);

    std::string username(usernameC ? reinterpret_cast<const char*>(usernameC): "NULL");
    std::string password(passwordC ? reinterpret_cast<const char*>(passwordC) : "NULL");


    User current_user(username, password, codenumber, admin);


    return current_user;
    
}

bool list_all_user(sqlite3* db)
{
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif

    const char* command = "SELECT id,username FROM users ORDER BY id ASC";

    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db, command, -1, &stmt, nullptr) != SQLITE_OK)
    {
        printf("Database Error \n");
    }


    unsigned int number_of_loop = 0;
    while(true)
    {
        if(sqlite3_step(stmt) != SQLITE_ROW)
        {
            if(number_of_loop == 0)
            {
                printf("User Not Found\n");
                break;
            }
            break;
        }
        number_of_loop++;
        
        const char* id = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        const char* user = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));

        printf("%s-%s\n", id, user);
    }
    

    cout << "\nEnter any key to continue";
    cin.get();
    
    return true;
}

bool createUser(sqlite3* db)
{   
    while (true)
    {   
        string fullname;
        string password;
        string isAdmin;
        string studentCode;
        srand(time(0)); //set seed
        
        printf("Enter Fullname: ");
        getline(cin, fullname);
        cout << "\n";
        
        printf("Enter Password: ");
        getline(cin, password);
        cout << "\n";
    
    
        printf("isAdmin?(y/N): ");
        getline(cin, isAdmin);
        cout << "\n";
        
        if(isAdmin == "y" || isAdmin == "Y")    //is admin set Binary variable
        {
            isAdmin = "1";
        }
        else
        {
            isAdmin = "0";
        }
        
        studentCode = to_string((rand() % 1000000000) + (time(0) % 1000)); //generate Random number


        string command = "INSERT INTO users (username, password, code, admin) VALUES ('"+ fullname +"', '"+ password +"', "+ studentCode +", "+ isAdmin +");";
        printf("\ncommand: %s\n", command.c_str());

        char* errdb;
        int stt = sqlite3_exec(db, command.c_str(), nullptr, nullptr, &errdb);

        if(stt == SQLITE_OK)
        {
            printf("Sucsess\n");
        }
        else
        {
            printf("Error: %s \n", errdb);
            sqlite3_free(errdb);
        }





        string conti;
        printf("Continiue? (Y/n): ");
        getline(cin, conti);
        if(conti == "n" || conti == "N")
        {
            return true;
        }
        else
        {
            continue;
        }
    }
        
    }

bool edit_user(sqlite3* db, string userId)
{   
    string command = "SELECT id,username,code,password,admin FROM users WHERE id="+ userId +"";

    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db, command.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        printf("Database Error\n");
        cin.get();
        return false;
    }

    if(sqlite3_step(stmt) == SQLITE_ROW)
    {
        const int id = sqlite3_column_int(stmt, 0);
        const char* username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const int stcode = (sqlite3_column_int(stmt, 2));
        const char* password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        const int admin = sqlite3_column_int(stmt, 4);

        string usernameS(username);
        string passwordS(password);
        



        bool adminBool = (admin == 1) ? 1 : 0;

        User edited_user(usernameS, passwordS, stcode, adminBool);
        edited_user.setID(id);  
        
        
        while(true)
        {
            #ifdef __WIN32
            system("cls");
            #else
            system("clear");
            #endif
            
            
            printf("%s-Username: %s \n", edited_user.getId().c_str(), edited_user.get_name().c_str());
            printf("Password: %s \n \n", edited_user.get_password().c_str());
            
            printf("1-Edit\n");
            printf("2-Delete\n");

            
            if(edited_user.is_admin())
            {
                printf("3-Downgrade to User\n");
            }
            else
            {
                printf("3-Upgrade to Admin\n");
            }
            printf("9-Unsave and Exit\n");
            printf("0-Save and Exit\n");

            string input;
            printf("#: ");
            getline(cin, input);


            if(input == "1")
            { 
                #ifdef __WIN32
                system("cls");
                #else
                system("clear");
                #endif
                printf("1-Username\n");
                printf("2-Password\n\n");

                string select_usr_or_pass;
                printf("#: ");
                getline(cin,select_usr_or_pass);
                printf("\n\n");

                string changed_value;
                string chagne_command;
                if(select_usr_or_pass == "1")
                {
                    printf("Enter Username: ");
                    getline(cin,changed_value);
                    chagne_command = "UPDATE users SET username='"+ changed_value +"' WHERE id="+ edited_user.getId() +";";

                }
                else if(select_usr_or_pass == "2")
                {
                    printf("Enter Password: ");
                    getline(cin,changed_value);
                    chagne_command = "UPDATE users SET password='"+ changed_value +"' WHERE id="+ edited_user.getId() +";";
                }
                else
                {
                    printf("Invalid Number!");
                    continue;
                }
                
                char* errdb;
                //edit database
                if(sqlite3_exec(db, chagne_command.c_str(), nullptr, nullptr, &errdb) != SQLITE_OK)
                {
                    printf("Change Error: %s", errdb);
                    cin.get();
                    continue;
                }

                //Edite Cache
                if(select_usr_or_pass == "1")
                {
                    edited_user.set_full_name(changed_value);
                }
                else if(select_usr_or_pass == "2")
                {
                    edited_user.set_password(changed_value);
                }

                printf("Sucsess");
                cin.get();




                



            }
            else if(input == "2")
            {
                string command = "DELETE FROM users where id="+ edited_user.getId() +";";
                char* errdb;
                if(sqlite3_exec(db, command.c_str(), nullptr,nullptr, &errdb))
                {
                    printf("Delete Error: %s", errdb);
                    cin.get();
                    continue;
                }
                
                printf("Sucsess");
                cin.get();
                break;
                
            }
            else if(input == "3")
            {
                string command;
                if(!edited_user.is_admin()) // Admin to User , User to Admin
                {
                    command = "UPDATE users SET admin=1 WHERE id="+ edited_user.getId() +";";
                }
                else
                {
                    command = "UPDATE users SET admin=0 WHERE id="+ edited_user.getId() +";";
                }

                char* errdb;
                // Set To database
                if(sqlite3_exec(db,command.c_str(), nullptr,nullptr, &errdb) != SQLITE_OK)
                {
                    printf("Database Error: %s", errdb);
                    cin.get();
                    continue;
                }
                
                //change catch
                edited_user.is_admin() ? edited_user.set_admin(false) : edited_user.set_admin(true);

                printf("Sucsess");
                cin.get();

            }
            else if(input == "0")
            {

            }
            else if(input == "9")
            {

            }
            else
            {
                printf("Invalid Number!");
                cin.get();
                continue;
            }

        }


    }
    else
    {
        printf("User Not Found!!!");
        cin.get();
    }


    return false;
} 

bool search_user(sqlite3* db, string searchText, int type)  // type 1(search with fullname) 2(with student code) 3(with id)
{
    printf("--------------------\n");
    string command;
    if(type == 1)
    {
        command = "SELECT id,username,code FROM users WHERE username LIKE '%"+ searchText +"%'";
    }
    else if(type == 2)
    {
        command = "SELECT id,username,code FROM users WHERE code LIKE '%"+ searchText +"%'";
    }
    else if(type == 3)
    {
        command = "SELECT id,username,code FROM users WHERE id LIKE '%"+ searchText +"%'";
    }

    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db, command.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        printf("Search Error: Database Err\n");
    }

    int number_of_loop = 0;
    while(true)
    {
        if(sqlite3_step(stmt) != SQLITE_ROW)
        {
            if(number_of_loop == 0)
            {
                printf("User Not Found");
                cin.get();
                return false;
            }
            break;
        }
        number_of_loop++;

        const char* id = reinterpret_cast<const char*>(sqlite3_column_text(stmt,0));
        const char* username = reinterpret_cast<const char*>(sqlite3_column_text(stmt,1));
        const char* studentCode = reinterpret_cast<const char*>(sqlite3_column_text(stmt,2));

        printf("%s-%s - StCode:%s\n", id, username, studentCode);


        
    }


    string select_id;
    printf("\nSelect User by id(null for continue): ");
    getline(cin, select_id);
    if(select_id == "")
    {
        return true;
    }

    return edit_user(db, select_id);

    
    
}

 

int main()
{
    sqlite3* DB;
    sqlite3_open("Student.db", &DB);
    int stt = sqlite3_exec(DB, "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT , username TEXT NOT NULL, password TEXT NOT NULL,code INTIGER NOT NULL, admin INTIGER NOT NULL);", nullptr, nullptr, nullptr);
    if(stt != SQLITE_OK)
    {
        printf("Error: To Connect Database");
        return 1;
    }


    string username;
    string password;
    string code_number;


    printf("Username: ");
    getline(cin, username);

    printf("Password: ");
    getline(cin, password);

    printf("CodeNumber: ");
    getline(cin, code_number);
    

    User current_user = Login(username, password, code_number, DB);
    
    // get Controll Shell
    printf("Welcome: %s\n", (current_user.get_name()).c_str());

    
    while (true)
    {
        #ifdef __WIN32
        system("cls");
        #else
        system("clear");
        #endif

        printf("1- Show Profile\n");
        printf("2- Edit Profile\n");
        if(current_user.is_admin()) //  admin options
        {
            printf("\n3- Create User\n");
            printf("4- List All User\n");
            printf("5- Search User\n\n");

        }
        printf("0- Exit\n");

        string input;
        cout << "#: ";
        getline(cin, input);

        if(input == "1")
        {
            current_user.print_all_detail();
            cout << "\n\nEnter key to continue";
            cin.get();
        }
        else if(input == "2")
        {
            continue;
        }
        else if (input == "3")
        {
            if(current_user.is_admin()) // Admin Check
            {
                createUser(DB);
            }
            else
            {
                continue;
            }
        }
        else if (input == "4")
        {
            if(current_user.is_admin()) // Admin Check
            {
                list_all_user(DB);
            }
            else
            {
                continue;
            }
        }
        else if (input == "5")
        {
            if(current_user.is_admin()) // Admin Check
            {
                string search_method;
                printf("\n1-by name\n");
                printf("2-by Student code\n");
                printf("3-by id\n\n");
                printf("Search method: ");
                getline(cin, search_method);
                cout << "\n";

                if(search_method != "1" && search_method != "2" && search_method != "3")
                {
                    printf("Not Avilable Method");
                    cin.get();
                    continue;
                }


                string search_text;
                printf("Search Text: ");
                getline(cin, search_text);
                cout << "\n";


                search_user(DB, search_text, stoi(search_method));
            }
            else
            {
                continue;
            }
        }
        else if(input == "0")
        {
            sqlite3_close(DB);
            return 0;
        }
    }
    



    sqlite3_close(DB);
    return 0;
}