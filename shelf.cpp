#include "shelf.hpp"
#include "error.hpp"

Shelf::Shelf(string name_ , int shelf_id)
{
    name = name_;
    id=shelf_id;
}
int Shelf::get_id()
{
    return id;
}
string Shelf::get_name()
{
    return name;
}
void Shelf::add_recipe(Recipe* this_)
{
    recipes.push_back(this_);
}
vector <Recipe*> Shelf::get_recipes()
{
    return recipes;
}
void Shelf::remove_this_recipe(int recipe_id)
{
    for (int i=0;i<recipes.size();i++)
    {
        if (recipes[i]->get_id()==recipe_id)
        {
            recipes.erase(recipes.begin()+i);
            return;
        }
    }
    throw bad_req();
}
void Shelf::check_still_not_inshelf(int id_)
{
    for (int i=0;i<recipes.size();i++)
    {
        if(recipes[i]->get_id()==id_)
            throw bad_req();
    }
}

