#include "recipe.hpp"
#include <iomanip>
#include <cmath>

int Recipe::get_id()
{
	return id;
}
string Recipe::get_title()
{
	return title;
}
string Recipe::get_vegetarian()
{
	return vegetarian;
}
int Recipe::get_minutes()
{
	return minutes_to_ready;
}
void Recipe::set_rate_num_and_total_rating(float rating,bool inc_needed)
{
    total_rating+=rating;
    if(inc_needed)
        rate_num++;
}
float Recipe::get_rating()
{
    if(total_rating)
        return (float)total_rating/(float)rate_num;
    return 0.0;
}
Recipe::Recipe(string title_,int& last_recipe_num,vector<string>ingredients_,
               string vegetarian_,vector<string>tags_,string image_address_,int minutes)
{
    title = title_;
    ingredients = ingredients_;
    if(vegetarian_=="No"||vegetarian_=="Yes")
        vegetarian = vegetarian_;
    else{
        last_recipe_num--;
        throw bad_req();
    }
    id = last_recipe_num;
    minutes_to_ready = minutes;
    tags = tags_;
    image_address = image_address_;
}
vector <string> Recipe::get_ingredients()
{
    return ingredients;
}
Recipe_detail Recipe::get_recipe_details()
{
    Recipe_detail this_recipe;
    this_recipe.id = id;
    this_recipe.ingredients=ingredients;
    this_recipe.minutes_to_ready=minutes_to_ready;
    if(rate_num)
        this_recipe.rating=total_rating/rate_num;
    else 
        this_recipe.rating = 0;
    this_recipe.tags=tags;
    this_recipe.title=title;
    this_recipe.vegetarian=vegetarian;
    this_recipe.image_address=image_address;
    return this_recipe;
}