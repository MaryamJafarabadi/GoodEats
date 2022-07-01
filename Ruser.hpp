#ifndef RUSER_HPP
#define RUSER_HPP

#include "user.hpp"
#include <sstream>
#include "shelf.hpp"

#define SPACE " "
#define EMPTY_SENTENCE "Empty"
struct recipeANDscore
{
    int recipe_id;
    float score;
};
class Ruser : public User
{
public:
	Ruser(string name, string password_, string type_,bool is_);
	void login();
    float find_recipeANDscore(int id_);
    void add_recipeANDscore(int id_,float score_);
    void set_new_score(int id_ , float score_);
    void add_this_shelf(Shelf* this_shelf);
    Shelf* find_this_shelf(int shelf_id);
    void add_recipeto_shelf(Shelf* this_shelf , Recipe* this_recipe);
    void print_chef(int& n,stringstream& strr){}
    void calculate_avg_rating(){}
    void show_ruser(stringstream& strr,int& num);
    void add_this_recipe(Recipe* this_recipe){}
    void remove_this_recipe(int id_){}
    vector<Recipe*> get_my_recipes(){vector<Recipe*> s; return s;}
    vector<Shelf*> get_shelves();

  

private:
    vector<recipeANDscore> recipeANDscores;
    vector<Shelf*> shelves;
    
};
#endif