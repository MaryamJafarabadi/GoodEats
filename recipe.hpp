#ifndef RECIPE_HPP
#define RECIPE_HPP
#include <cstring>
#include <vector>
#include <iostream>
#include <sstream>
#include "error.hpp"
using namespace std;

#define SPACE " "
#define DELIMITER ","
struct Recipe_detail
{
	int id;
	string title;
	int minutes_to_ready;
	string vegetarian;
	vector <string > ingredients;
	vector <string > tags;
	float rating;
	string image_address;
};
class Recipe
{
public:
    Recipe(string title_,int& last_recipe_num,vector<string>ingredients,
           string vegetarian_,vector<string>tags_,string image_address_,int minutes);
	int get_id();
	string get_title();
	string get_vegetarian();
	int get_minutes();
    float get_rating();
    void set_rate_num_and_total_rating(float rating,bool inc_needed);
	vector <string> get_ingredients();
	Recipe_detail get_recipe_details();


private:
	int id;
	string title;
	string vegetarian;
	int minutes_to_ready;
	vector <string>ingredients;
	vector <string>tags;
	float total_rating=0.0;
    int rate_num=0;
    string image_address;
};
#endif