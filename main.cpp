#include <iostream>
#include <sqlite3.h>
#include <string>

using namespace std;
//Global Variable
string current_user;
int current_codeNumber;


class User
{
private:
    string full_name;
    string password;
    int code_number;
    bool admin;
public:
    User(string fullname, string pass, int codeNumber)
    {
        full_name = fullname;
        password = pass;
        code_number = codeNumber;
    }
    void set_full_name(string name)
    {
        if (admin == true || current_user == full_name && current_codeNumber == code_number)
        {
            full_name = name;
        }
        else
        {
            printf("Acsess Denid\n");
        }
    }
    void set_password(string pass)
    {
        if ( admin == true || current_user == full_name && current_codeNumber == code_number)
        {
            password = pass;
        }
        else
        {
            printf("Acsess Denid\n");
        }
    }
    void print_all_deteil()
    {
        printf("full_name: %s \n password: %s \n code_number: %i \n isAdmin %b", full_name, password, code_number, admin);
    } 
};


User checkAvilable_user_and_password_and_code(string user, string pass, string code, sqlite3* db)
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

    std::string username(reinterpret_cast<const char*>(usernameC));
    std::string password(reinterpret_cast<const char*>(usernameC));
    

    User current_user(username, password, codenumber);
    current_user.print_all_deteil();

    return current_user;
    
}






int main()
{
    sqlite3* DB;
    sqlite3_open("Student.db", &DB);
    int stt = sqlite3_exec(DB, "CREATE TABLE IF NOT EXISTS users (id INITIALLY PRIMARY KEY NOT NULL, username TEXT NOT NULL, password TEXT NOT NULL,code INTIGER NOT NULL, admin BOOL NOT NULL);", nullptr, nullptr, nullptr);
    if(stt != SQLITE_OK)
    {
        printf("Error: To Connect Database");
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
    

    if(checkAvilable_user_and_password_and_code(username, password, code_number, DB))
    {
        
    }
    else
    {
        printf("Fail to Logon");
    }
    



    sqlite3_close(DB);
    return 0;
}