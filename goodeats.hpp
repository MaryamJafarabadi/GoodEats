#ifndef GOODEATS_HPP
#define GOODEATS_HPP
#include <sstream>
#include <vector>
#include "user.hpp"
using namespace std;
#define PASSWORD_NO_NEED_JUST_FIND "nothing"
#define CHEF_TYPE "chef"
#define USER_TYPE "user"
#define EMPTY_SENTENCE "Empty"
#define MAX_SCORE 5
#define MIN_SCORE 1
#define COMMA ','
#define DELEMITER " "
#define IS_EMPTY ""
#define INCREASE_ONE 1
#define DECREASE_ONE -1
#define MIN_DISCOUNT_AGREED 19
class Recipe;
class User;
class Shelf;
class Goodeats
{
public:

    void signup(string username,string password,string type);
	bool checkif_is_exist(string name);
	void login(string username, string password);
	User* find_username(string username_, string password_);
    void logout();
    User* find_who_is_logged_in();
    void rate(int recipe_id , float score);
	Recipe* find_this_recipe(int id_);
    void change_rate(int id_ , float score);
    int make_shelf(string name);
    void add_this_recipeto_shelf(int shelf_id , int recipe_id);
    Shelf* find_this_shelf(int shelf_id);
    void delete_recipe_from_shelf(int recipe_id , int shelf_id);
    int chef_added_recipe(string title,string all_ingredient,string vegatarian,
                           int minutes,string all_tags,string image_address);
    void chef_delete_recipe(int recipe_id);
    void remove_this_recipe_fromall(int id_);
    vector<User*> remove_this_user();
    User* get_logged_in_user();
    vector<Recipe*> get_all_recipes();
  
private:
   
	vector <User*> users;
	vector <Recipe*> recipes;
	vector <Shelf*> shelves;
    User* logged_in_user=nullptr;
    int last_shelf_num=0;
    int last_recipe_num=0;

};
void sort_users(vector<User*>& temp_users);
vector<string> divide_items(string line);
void sort_recipes(vector <Recipe*>& recipes);
bool recipe_name_compare( Recipe* r1 ,  Recipe* r2);
bool user_name_compare(User* u1 ,User* u2);
#endif