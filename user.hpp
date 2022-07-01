#ifndef USER_HPP
#define USER_HPP
#include <cstring>
#include <iostream>
#include "recipe.hpp"
#include "shelf.hpp"
using namespace std;
class User
{
public: 
	User(string name, string password_, string type_,bool is_);
	
	string get_username();
	string get_password();
	void rate();
    bool get_is_logged_in();
    string get_type();
	void set_is_logged_in(bool is_);
    virtual float find_recipeANDscore(int id_)=0;
    virtual void add_recipeANDscore(int id_,float score_)=0;
    virtual void set_new_score(int id_ , float score_)=0;
    virtual void add_this_shelf(Shelf* this_shelf)=0;
    virtual Shelf* find_this_shelf(int shelf_id)=0;
    virtual void add_recipeto_shelf(Shelf* this_shelf , Recipe* this_recipe)=0;
    virtual void print_chef(int& n , stringstream& strr)=0;
    virtual void calculate_avg_rating()=0;
    virtual void show_ruser(stringstream& strr,int& num)=0;
    virtual void add_this_recipe(Recipe* this_recipe)=0;
    virtual void remove_this_recipe(int id_)=0;
    virtual vector<Recipe*> get_my_recipes()=0;
    virtual vector<Shelf*> get_shelves()=0;

protected:
	string username;
	string password;
	string type;
	bool is_logged_in;
};
#endif