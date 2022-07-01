#ifndef HANDLERS_HPP
#define HANDLERS_HPP
#include <sstream>
#include "server/server.hpp"
#include "shelf.hpp"
struct Recipe_detail;
using namespace std;
class Cli;
void add_this_recipe(ostringstream& body,Recipe_detail this_recipe);
void add_this_recipe_detail(ostringstream& body , Recipe_detail this_recipe,int shelf_id);
void add_recipe_detail(ostringstream& body , Recipe_detail this_recipe,string shelf_id);
void add_this_shelf(int id , string name , ostringstream& body);
void add_rest_shelf_detail(ostringstream& body,Shelf* this_shelf);
void add_rest_file_add_recipe(ostringstream& body , int shelf_id);
int stringTointeger(string str);
class Signup_Handler:public RequestHandler
{
public:
	Signup_Handler( Cli* cli_){cli = cli_;}
	Response *callback(Request *);
private:
	Cli* cli;
};
class Chef_Login_Handler:public RequestHandler
{
public:
    Chef_Login_Handler(Cli* cli_){cli=cli_;}
    Response *callback(Request *);
private:
    Cli* cli;
};
class Login_Handler:public RequestHandler
{
public:
    Login_Handler(Cli* cli_){cli=cli_;}
    Response *callback(Request *);
private:
    Cli* cli;
};
class Chef_Adder_Handler:public RequestHandler
{
public:
    Chef_Adder_Handler(Cli* cli_){cli=cli_;}
    Response *callback(Request *);
private:
    Cli* cli;
};
class Chef_Remover_Handler:public RequestHandler
{
public:
    Chef_Remover_Handler(Cli* cli_){cli=cli_;}
    Response *callback(Request *);
private:
    Cli* cli;
};
class Ruser_Login_Handler:public RequestHandler
{
public:
    Ruser_Login_Handler(Cli* cli_){cli=cli_;}
    Response *callback(Request *);
private:
    Cli* cli;
};
class Show_Recipe_Handler:public RequestHandler
{
public:
    Show_Recipe_Handler(Cli* cli_){cli=cli_;}
    Response *callback(Request *);
private:
    Cli* cli;
};
class Rate_Handler:public RequestHandler
{
public:
    Rate_Handler(Cli* cli_){cli=cli_;}
    Response *callback(Request *);
private:
    Cli* cli;
};
class Put_Rate_Handler:public RequestHandler
{
public:
    Put_Rate_Handler(Cli* cli_){cli=cli_;}
    Response *callback(Request *);
private:
    Cli* cli;
};
class Change_Rate_Handler:public RequestHandler
{
public:
    Change_Rate_Handler(Cli* cli_){cli=cli_;}
    Response *callback(Request *);
private:
    Cli* cli;
};
class Put_Change_Rate_Handler:public RequestHandler
{
public:
    Put_Change_Rate_Handler(Cli* cli_){cli=cli_;}
    Response *callback(Request *);
private:
    Cli* cli;
};
class Show_Shelves_Handler:public RequestHandler
{
public:
    Show_Shelves_Handler(Cli* cli_){cli=cli_;}
    Response *callback(Request *);
private:
    Cli* cli;
};
class Shelf_Adder_Handler:public RequestHandler
{
public:
    Shelf_Adder_Handler(Cli* cli_){cli=cli_;}
    Response *callback(Request *);
private:
    Cli* cli;
};
class Shelf_Detail_Handler:public RequestHandler
{
public:
    Shelf_Detail_Handler(Cli* cli_){cli=cli_;}
    Response *callback(Request *);
private:
    Cli* cli;
};
class Add_Recipe_Handler:public RequestHandler
{
public:
    Add_Recipe_Handler(Cli* cli_){cli=cli_;}
    Response *callback(Request *);
private:
    Cli* cli;
};
class Recipe_Being_Added_Handler:public RequestHandler
{
public:
    Recipe_Being_Added_Handler(Cli* cli_){cli=cli_;}
    Response *callback(Request *);
private:
    Cli* cli;
};
class Remove_Recipe_Handler:public RequestHandler
{
public:
    Remove_Recipe_Handler(Cli* cli_){cli=cli_;}
    Response *callback(Request *);
private:
    Cli* cli;
};
class Recipe_Being_Removed_Handler:public RequestHandler
{
public:
    Recipe_Being_Removed_Handler(Cli* cli_){cli=cli_;}
    Response *callback(Request *);
private:
    Cli* cli;
};
#endif