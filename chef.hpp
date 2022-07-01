#ifndef CHEF_HPP
#define CHEF_HPP

#include "user.hpp"
#include "recipe.hpp"
#include <sstream>
#include <vector>

#define SPACE " "

class Shelf;///
class Chef :public User
{
public:
	Chef(string name, string password_, string type_,bool is_);
    float find_recipeANDscore(int id_){return 0;}
    void add_recipeANDscore(int id_,float score_){}
    void set_new_score(int id_ , float score_){}
    void add_this_shelf(Shelf* this_shelf){}
    Shelf* find_this_shelf(int shelf_id){return nullptr;}
    void add_recipeto_shelf(Shelf* this_shelf , Recipe* this_recipe){}
    void print_chef(int& n,stringstream& strr);
    void calculate_avg_rating();
    void show_ruser(stringstream& strr,int& num){}
    void add_this_recipe(Recipe* this_recipe);
    void remove_this_recipe(int id_);
    void remove(int id_);
    vector<Recipe*> get_my_recipes();
    vector<Shelf*> get_shelves(){vector<Shelf*> thiss;return thiss;}
private:
    float rating=0.0;
    vector <Recipe*> my_recipes;
};
bool name_compare(Recipe* r1 ,Recipe* r2);
#endif 