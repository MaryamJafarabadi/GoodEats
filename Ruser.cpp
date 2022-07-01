#include "Ruser.hpp"
#include "error.hpp"
Ruser::Ruser(string name, string password_, string type_,bool is_) :User(name, password_, type_,is_)
{

}
float Ruser::find_recipeANDscore(int id_)
{
    for (int i=0;i<recipeANDscores.size();i++)
    {
        if (recipeANDscores[i].recipe_id==id_)
            return recipeANDscores[i].score;
    }
    return false;
}
void Ruser::add_recipeANDscore(int id_,float score_)
{
    recipeANDscore this_ ;
    this_.recipe_id=id_;
    this_.score=score_;
    recipeANDscores.push_back(this_);

}
void Ruser::set_new_score(int id_ , float score_)
{
    for (int i=0;i< recipeANDscores.size();i++)
    {
        if (id_==recipeANDscores[i].recipe_id)
        {
            recipeANDscores[i].score=score_;
            return;
        }
    }
}
void Ruser::add_this_shelf(Shelf* this_shelf)
{
    shelves.push_back(this_shelf);
}

Shelf* Ruser::find_this_shelf(int shelf_id)
{
    for (int i=0 ; i<shelves.size();i++)
    {
        if(shelves[i]->get_id() == shelf_id)
            return shelves[i];
    }
    throw perm_den();
}
void Ruser:: add_recipeto_shelf(Shelf* this_shelf , Recipe* this_recipe)
{
    this_shelf->add_recipe(this_recipe);

}
void Ruser::show_ruser(stringstream& strr,int& num)
{
    strr << username <<endl;
    num++;
}
vector <Shelf*> Ruser::get_shelves()
{
    return shelves;
}
