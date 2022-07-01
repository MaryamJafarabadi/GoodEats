#include "goodeats.hpp"
#include "chef.hpp"
#include "Ruser.hpp"
#include "recipe.hpp"
#include "shelf.hpp"
#include "error.hpp"
#include <algorithm>

bool recipe_name_compare(Recipe* r1 ,Recipe* r2)
{
    return r1->get_title() < r2->get_title();
}
bool user_name_compare(User* u1 ,User* u2)
{
    return u1->get_username() < u2->get_username();
}

void Goodeats::signup(string username,string password,string type)
{
    if (!checkif_is_exist(username))
		{
			User* this_user;
			if (type == USER_TYPE)
			{
				Ruser* this_ = new Ruser(username, password, type,false);
				this_user = this_;
			}
			else if (type == CHEF_TYPE)
			{
				Chef* this_ = new Chef(username, password, type,false);
				this_user = this_;
			}
			else
			{
				throw bad_req();
			}
			users.push_back(this_user);
			this_user->set_is_logged_in(true);
            logged_in_user=this_user;
		}
        else
        {
            throw bad_req();
        }
}
bool Goodeats::checkif_is_exist(string name)
{
	for (int i = 0; i < users.size(); i++)
	{
		if (name == users[i]->get_username())
		{
			//throw bad_req();
            //throw "you are already signed up! go to login page:)";
            throw twice_signup();
		}	
	}
	return false;
}
void Goodeats::login(string username, string password)
{
	User* this_user=find_username(username, password);
    this_user->set_is_logged_in(true);
    logged_in_user=this_user;
}
User* Goodeats::find_username(string username_, string password_)
{
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i]->get_username() == username_)
		{
            if (password_== PASSWORD_NO_NEED_JUST_FIND)
                return users[i];
            if(users[i]->get_password() == password_)
                return users[i];
		}	
	}
    if(password_==PASSWORD_NO_NEED_JUST_FIND)
        throw not_f();
	throw bad_req();////
}
void Goodeats::logout()
{
    if (logged_in_user)
    {
        logged_in_user->set_is_logged_in(false);
        logged_in_user=nullptr;
    }
    else
        throw perm_den();
}
void Goodeats::rate(int recipe_id , float score)
{
    if(score>MAX_SCORE || score <MIN_SCORE)
        throw bad_req();
    if (logged_in_user->get_type()==USER_TYPE)
    {
        Recipe* this_recipe = find_this_recipe(recipe_id);
        if (logged_in_user->find_recipeANDscore(recipe_id))
            throw already_rate();
        else
        {
            logged_in_user->add_recipeANDscore(recipe_id,score);
            bool inc_need = true;
            this_recipe->set_rate_num_and_total_rating(score,inc_need);
        }
            
    }
    else 
        throw perm_den();
}
Recipe* Goodeats::find_this_recipe(int id_)
{
	for (int i = 0; i < recipes.size(); i++)
	{
		if (recipes[i]->get_id() == id_)
			return recipes[i];
	}
	throw not_f();
}
void Goodeats::change_rate(int id_,float score)
{
    
    if(logged_in_user->get_type()==USER_TYPE)
    {
        Recipe* this_recipe = find_this_recipe(id_);
        float last_score = logged_in_user->find_recipeANDscore(id_);
        if (last_score)
        {
            if(score>MAX_SCORE || score<MIN_SCORE)
                throw bad_req();
            logged_in_user->set_new_score(id_ , score);
            float diference = score - last_score ;
            bool inc_needed = false ;
            this_recipe->set_rate_num_and_total_rating(diference , inc_needed);
        }
        else 
            throw rate_first();
    }
    else
        throw perm_den();
}
int Goodeats::make_shelf(string name)
{
    if(logged_in_user->get_type()==USER_TYPE)
    {
        last_shelf_num++;
        Shelf* this_shelf = new Shelf(name , last_shelf_num );
        logged_in_user->add_this_shelf(this_shelf);
        shelves.push_back(this_shelf);
        return last_shelf_num;
    }
    else
        throw perm_den();

}

void Goodeats:: add_this_recipeto_shelf(int shelf_id , int recipe_id)
{
    if(logged_in_user->get_type()==USER_TYPE)
    {
        Shelf* this_shelf = logged_in_user->find_this_shelf(shelf_id);
        Recipe* this_recipe = find_this_recipe(recipe_id);
        this_shelf->check_still_not_inshelf(recipe_id);
        logged_in_user->add_recipeto_shelf(this_shelf , this_recipe);
    }
    else 
        throw perm_den();
   
}
Shelf* Goodeats::find_this_shelf(int shelf_id)
{
    for (int i=0;i<shelves.size();i++)
    {
        if (shelves[i]->get_id()==shelf_id)
        {
            return shelves[i];
        }
    }
    throw not_f();
}
void Goodeats::delete_recipe_from_shelf(int recipe_id , int shelf_id)
{
    if(logged_in_user->get_type()==USER_TYPE)
    {
        Shelf* this_shelf = logged_in_user ->find_this_shelf(shelf_id);
        this_shelf->remove_this_recipe(recipe_id);
    }
    else   
        throw perm_den();

}

void sort_users(vector<User*>& temp_users)
{
    for (int i = 1; i < temp_users.size(); i++)
	{
		for (int j = 0; j < temp_users.size() - 1; i++)
		{
			if (temp_users[i]->get_username() > temp_users[i + 1]->get_username())
				swap(temp_users[i], temp_users[i + 1]);
		}
	}
}


vector<User*> Goodeats::remove_this_user()
{
    vector<User*>temp_users = users;
    for (int i=0;i<users.size();i++)
    {
        if(users[i]->get_username()==logged_in_user->get_username())
        {
             users.erase(temp_users.begin()+i);
             return temp_users;
        }  
    }
    return temp_users;
}
int Goodeats::chef_added_recipe(string title,string all_ingredient,string vegatarian,
                           int minutes,string all_tags,string image_address)
{
    cout<<all_ingredient[0]<<"****************************************"<<endl;
    if(logged_in_user->get_type()==CHEF_TYPE)
    {
        vector <string> ingredients = divide_items(all_ingredient);
        vector <string> tags = divide_items(all_tags);
        cout<<all_ingredient[0]<<"****************************************"<<endl;
        last_recipe_num++;
        Recipe* this_recipe = new Recipe(title,last_recipe_num,ingredients,vegatarian,tags,image_address,minutes);
        logged_in_user->add_this_recipe(this_recipe);
        recipes.push_back(this_recipe);
        return last_recipe_num;
    }
    else
        throw perm_den();
}
vector<string> divide_items(string line)
{
    string item=IS_EMPTY;
    vector<string>items;
    for(int i=0;i<line.length();i++)
    {
        if (line[i]==COMMA)
        {
            items.push_back(item);
            item=IS_EMPTY;
            continue;
        }
        item+=line[i];
    }
     items.push_back(item);
    return items;
}
void Goodeats::chef_delete_recipe(int recipe_id)
{
    if(logged_in_user->get_type()==CHEF_TYPE)
    {
       
        logged_in_user->remove_this_recipe(recipe_id);
        remove_this_recipe_fromall(recipe_id);
    }
    else
        throw perm_den();

}
void Goodeats::remove_this_recipe_fromall(int id_)
{
    for (int i=0;i<recipes.size();i++)
    {
        if (recipes[i]->get_id()==id_)
        {
            recipes.erase(recipes.begin()+i);
            return;
        }
    }
    throw not_f();
}
User* Goodeats::get_logged_in_user()
{
    return logged_in_user;
}

vector<Recipe*> Goodeats::get_all_recipes()
{
    return recipes;
}