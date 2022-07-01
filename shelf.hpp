#ifndef SHELF_HPP
#define SHELF_HPP

#include <cstring>
#include <iostream>
#include <vector>
#include "recipe.hpp"
using namespace std;
class Shelf
{
    public:
        Shelf(string name_ , int shelf_id);
        string get_name();
        int get_id();
        void add_recipe(Recipe* this_);
        vector <Recipe*> get_recipes();
        void remove_this_recipe(int recipe_id);
        void check_still_not_inshelf(int id_);
    private:
        string name;
        vector <Recipe*> recipes;
        int id;

};

#endif