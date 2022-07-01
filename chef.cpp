#include "chef.hpp"
#include "error.hpp"
#include <cmath>
#include <algorithm>
#include <iomanip>
Chef::Chef(string name, string password_, string type_,bool is_):User(name , password_ , type_,is_)
{

}
void Chef::print_chef(int& n,stringstream& strr)
{
    calculate_avg_rating();
    n++;
    strr<< username <<SPACE<< fixed << setprecision(1)<<ceil(rating * 10.0) / 10.0  <<endl;
}
void Chef::calculate_avg_rating()
{
    int num=0;
    float total =0;
    for (int i=0;i<my_recipes.size();i++)
    {
        if(my_recipes[i]->get_rating()!=0.0)
            num++;
        total+=my_recipes[i]->get_rating();
    }
    if(num)
        rating = total/(float)num;
}
bool name_compare(Recipe* r1 ,Recipe* r2)
{
    return r1->get_title() < r2->get_title();
}
void Chef::add_this_recipe(Recipe* this_recipe)
{
    my_recipes.push_back(this_recipe);
}
void Chef::remove_this_recipe(int id_)
{
   for (int i=0;i<my_recipes.size();i++)
   {
       if(my_recipes[i]->get_id()==id_)
       {
           my_recipes.erase(my_recipes.begin()+i);
           return;
       } 
   }
   throw perm_den(); 
}
vector<Recipe*> Chef::get_my_recipes()
{
    return my_recipes;
}

