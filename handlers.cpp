#include "handlers.hpp"
#include "Cli.hpp"
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <bits/stdc++.h>
using namespace std;
string read_file(string add )
{
	std::string line;
	std::ostringstream body;
	std::ifstream input_html( add );
	while( input_html >> line )
		body << line << endl;
	return body.str();
}
Response* Signup_Handler::callback( Request *req ) 
{
	Response *res = new Response;
	res->setHeader( "Content-Type" , "text/html" );
	std::ostringstream body;
	try
	{
        
		cli->get_goodeats()->signup( req->getQueryParam( "Username" ) , req->getQueryParam( "Password" ) , 
								req->getQueryParam( "Type" ) );
        body <<read_file("signup.txt") ;
    if (cli->get_goodeats()->get_logged_in_user()->get_type()=="user")
    {
       body<<R"( <a href = "/Ruser_HomePage" target="_blank"> THIS</a>)";
    }
    else 
    {
        body<<R"( <a href = "/chef_HomePage" target="_blank" >THIS</a>)";
    }
    body <<"to access HomePage</div></h3>";
    body<<R"(
             </body>    
             </html>)";
             res->setBody( body.str() );
	}
	catch( string error )
	{ 
		body << "<!DOCTYPE html>" << "<html>" 
		<< "<head>An error has ocuured while trying to signup!</head>"
		<<"<br/>"<<"<p>Error message: "<< error <<"</p>" << "<a href = \"/\">try again</a></html>";
		res->setBody( body.str() );
	}
	return res;
}
Response *Login_Handler::callback( Request *req ) 
{
	Response *res = new Response;
	res->setHeader( "Content-Type" , "text/html" );
	try
	{
		cli->get_goodeats()->login(req->getQueryParam( "Username" ) , req->getQueryParam( "Password"));
        if (cli->get_goodeats()->get_logged_in_user()->get_type()=="chef")
  		    res = Response::redirect("/chef_HomePage");
        else 
            res = Response::redirect("/Ruser_HomePage"); 
	}
	catch(string error)
	{
		std::ostringstream error_body;
		error_body << "<!DOCTYPE html>" << "<html>" 
		<< "<head>An error has ocuured while trying to login!</head>"
		<<"<br/>"<<"<p>Error message: "<< error <<"</p>" << "</html>";
		res->setBody( error_body.str());
	}
  	return res;
}
Response *Chef_Login_Handler::callback( Request *req ) 
{
	Response *res = new Response;
	res->setHeader( "Content-Type" , "text/html" );
    ostringstream body;
    body << read_file("chef_home_page.txt");
	try
	{
        for(int i=0;i<cli->get_goodeats()->get_logged_in_user()->get_my_recipes().size();i++)
        {
            Recipe_detail this_recipe = cli->get_goodeats()->get_logged_in_user()->get_my_recipes()[i]->get_recipe_details();
            add_this_recipe(body,this_recipe);
        }
        body << read_file("chef_home_page2.txt");
        res->setBody(body.str());
	}
	catch(string error)
	{
		std::ostringstream error_body;
		error_body << "<!DOCTYPE html>" << "<html>" 
		<< "<head>An error has ocuured while trying to login!</head>"
		<<"<br/>"<<"<p>Error message: "<< error <<"</p>" << "</html>";
		res->setBody( error_body.str());
	}
  	return res;
}
void add_this_recipe(ostringstream& body,Recipe_detail this_recipe)
{
    body<<"<tr>"<<"<th>"<<this_recipe.id<<"</th>"<<"<th>"<<this_recipe.title<<"</th>"
        <<"<th>"<<this_recipe.vegetarian<<"</th>"<<"<th>"<<this_recipe.minutes_to_ready<<"</th>"<<"<th>";
    for (int i=0;i<this_recipe.ingredients.size();i++)
    {
        body<<this_recipe.ingredients[i];
        if(i!=this_recipe.ingredients.size()-1)
            body<<",";
    }
    body<<"</th>"<<"<th>";
    for (int i=0;i<this_recipe.tags.size();i++)
    {
        body<<this_recipe.tags[i];
        if(i!=this_recipe.tags.size()-1)
            body<<",";       
    }
    body<<"</th>"<<"<th>"<<this_recipe.rating<<"</th>"<<"</tr>";
}
Response *Chef_Adder_Handler::callback( Request *req ) 
{
	Response *res = new Response;
	res->setHeader( "Content-Type" , "text/html" );
    ostringstream body;
	try
	{
		int id = cli->get_goodeats()->chef_added_recipe(req->getBodyParam("Title"),req->getBodyParam("Ingredients"),
                                               req->getBodyParam("Vegetarian"),stringTointeger(req->getBodyParam("Minutes_to_ready")),
                                               req->getBodyParam("Tags"),req->getBodyParam("Image_address"));
        body<<read_file("successfuly_add_chef_recipe.txt");
        body<<id<<"</p>"<<"</body>"<<"</html>";
        res->setBody(body.str());
	}
	catch(string error)
	{
		body << "<!DOCTYPE html>" << "<html>" 
		<< "<head>An error has ocuured while trying to Add!</head>"
		<<"<br/>"<<"<p>Error message: "<< error <<"</p>" << "</html>";
		res->setBody( body.str());
	}
  	return res;
}
int stringTointeger(string str)
{
    int temp = 0;
    for (int i = 0; i < str.length(); i++) {
        temp = temp * 10 + (str[i] - '0');
    }
    return temp;
}
Response *Chef_Remover_Handler::callback( Request *req ) 
{
	Response *res = new Response;
	res->setHeader( "Content-Type" , "text/html" );
    ostringstream body;
	try
	{
        cli->get_goodeats()->chef_delete_recipe(stringTointeger(req->getBodyParam("Id")));
        cli->get_goodeats()->remove_this_recipe_fromall(stringTointeger(req->getBodyParam("Id")));//
        body << read_file("successfuly_removed_chef_recipe.txt");
        res->setBody(body.str());
	}
	catch(string error)
	{
		std::ostringstream error_body;
		error_body << "<!DOCTYPE html>" << "<html>" 
		<< "<head>An error has ocuured while trying to Remove!</head>"
		<<"<br/>"<<"<p>Error message: "<< error <<"</p>" << "</html>";
		res->setBody( error_body.str());
	}
  	return res;
}
Response *Ruser_Login_Handler::callback( Request *req ) 
{
	Response *res = new Response;
	res->setHeader( "Content-Type" , "text/html" );
    ostringstream body;
    body<<read_file("Ruser_homepage.txt");
	try
	{
        for (int i=0;i<cli->get_goodeats()->get_all_recipes().size();i++)
        {
            Recipe_detail this_recipe = cli->get_goodeats()->get_all_recipes()[i]->get_recipe_details();
            add_this_recipe_detail(body,this_recipe,0);
        }
        res->setBody(body.str());
	}
	catch(string error)
	{
		std::ostringstream error_body;
		error_body << "<!DOCTYPE html>" << "<html>" 
		<< "<head>An error has ocuured while trying to Login!</head>"
		<<"<br/>"<<"<p>Error message: "<< error <<"</p>" << "</html>";
		res->setBody( error_body.str());
	}
  	return res;
}
void add_this_recipe_detail(ostringstream& body , Recipe_detail this_recipe,int shelf_id)
{
        body<<"<tr>"<<"<th>"<<"<a href='show_recipe_indetail?Recipe_Id="<<this_recipe.id;
        //if(shelf_id)
            body<<"&shelf_id="<<shelf_id;
        body<<"'>"<<this_recipe.id<<"</a>"<<"</th>"<<"<th>"<<this_recipe.title<<"</th>"
        <<"<th>"<<this_recipe.vegetarian<<"</th>"<<"<th>"<<this_recipe.minutes_to_ready<<"</th>"
        <<"<th>"<<"</tr>";
}
Response *Show_Recipe_Handler::callback( Request *req ) 
{
	Response *res = new Response;
	res->setHeader( "Content-Type" , "text/html" );
    ostringstream body;
    body<<read_file("Ruser_show_recipe_detail.txt");
	try
	{

        Recipe_detail this_recipe = cli->get_goodeats()->find_this_recipe(stringTointeger(req->getQueryParam("Recipe_Id")))->get_recipe_details();
        add_recipe_detail(body,this_recipe,req->getQueryParam("Shelf_Id"));
        res->setBody(body.str());
	}
	catch(string error)
	{
		std::ostringstream error_body;
		error_body << "<!DOCTYPE html>" << "<html>" 
		<< "<head>An error has ocuured while trying to Show!</head>"
		<<"<br/>"<<"<p>Error message: "<< error <<"</p>" << "</html>";
		res->setBody( error_body.str());
	}
  	return res;
}
void add_recipe_detail(ostringstream& body , Recipe_detail this_recipe,string shelf_id)
{
    body<<"<p>"<<"Id : "<<this_recipe.id<<"<br>"<<"Title : "<<this_recipe.title<<"<br>"
        <<"Vegetarian : "<<this_recipe.vegetarian<<"<br>"<<"Ingredients : ";
    for(int i=0;i<this_recipe.ingredients.size();i++)
    {
        body<<this_recipe.ingredients[i];
        if(i!=this_recipe.ingredients.size()-1)
            body<<",";
    }
    body<<"<br>"<<"Minutes to ready : "<<this_recipe.minutes_to_ready<<"<br>"<<"Tags : ";
    for (int i=0;i<this_recipe.tags.size();i++)
    {
        body<<this_recipe.tags[i];
        if(i!=this_recipe.tags.size()-1)
            body<<",";       
    }
    body<<"<br>"<<"Rating : "<<this_recipe.rating<<"</p>";
    body<<"<img src = "<<R"(")"<<this_recipe.image_address<<R"(")"
        <<R"( alt = "Trulli" height = "250" width = "270" />)"
        <<"</div>"<<R"(<div style = "position:absolute; left:180px; top:300px;">)"
        <<"<a href='rate?Recipe_Id="<<this_recipe.id<<"&Shelf_Id="<<shelf_id<<"'>"<<"<button>Rate</button><br><br></a>"
        <<"<a href='change_rating?Recipe_Id="<<this_recipe.id<<"&Shelf_Id="<<shelf_id<<"'>"<<"<button>Change Rating</button><br><br></a>"
        <<R"(</a><a href="/"><button>Logout</button></a>)";
    if(shelf_id!="0")
        body<<R"(<a href="/show_shelf_indetail?Id=)"<<shelf_id<<R"(">)";
    else 
        body<<R"(<a href="/Ruser_HomePage">)";
    body<<R"(<button>Back</button></a></div></body></html>)";
} 
Response *Rate_Handler::callback( Request *req ) 
{
	Response *res = new Response;
	res->setHeader( "Content-Type" , "text/html" );
    ostringstream body;
    body<<read_file("rate.txt");
	try
	{
        int recipe_id = stringTointeger(req->getQueryParam("Recipe_Id"));
        int shelf_id = stringTointeger(req->getQueryParam("Shelf_Id"));
        body<<R"(<input type='hidden' name="Recipe_Id" value=')"<<recipe_id
            <<R"('/>)"
            <<R"(<input type='hidden' name="Shelf_Id" value=')"<<shelf_id
            <<R"('/>)"
            <<R"(<br><button type="submit">Rate</button><br/></form><a href="/show_recipe_indetail?Recipe_Id=)"
            <<recipe_id<<"&Shelf_id="<<shelf_id
            <<R"("><button>Back</button><br><br></a><a href="/"><button>Logout</button></a></div>)"
            <<"</body></html>";
        res->setBody(body.str());
	}
	catch(string error)
	{
		std::ostringstream error_body;
		error_body << "<!DOCTYPE html>" << "<html>" 
		<< "<head>An error has ocuured while trying to Rate!</head>"
		<<"<br/>"<<"<p>Error message: "<< error <<"</p>" << "</html>";
		res->setBody( error_body.str());
	}
  	return res;
}      
Response *Put_Rate_Handler::callback( Request *req ) 
{
	Response *res = new Response;
	res->setHeader( "Content-Type" , "text/html" );
    ostringstream body;
    body<<read_file("Put_rate.txt");
	try
	{
        cli->get_goodeats()->rate(stringTointeger(req->getBodyParam("Recipe_Id")),stof(req->getBodyParam("Score")));
        body<<R"(<a href="/rate?Recipe_Id=)"<<req->getBodyParam("Recipe_Id")
            <<"&Shelf_Id="<<req->getBodyParam("Shelf_Id")
            <<R"("><button>Back</button><br><br></a></div></body></html>)";
        res->setBody(body.str());
	}
    
	catch(string error)
	{
		std::ostringstream error_body;
		error_body << "<!DOCTYPE html>" << "<html>" 
		<< "<head>An error has ocuured while trying to Rate!</head>"
		<<"<br/>"<<"<p>Error message: "<< error <<"</p>" << "</html>";
		res->setBody( error_body.str());
	}
  	return res;
} 
Response *Change_Rate_Handler::callback( Request *req ) 
{
	Response *res = new Response;
	res->setHeader( "Content-Type" , "text/html" );
    ostringstream body;
    body<<read_file("change_rate.txt");
	try
	{ 
        int recipe_id = stringTointeger(req->getQueryParam("Recipe_Id"));
        int shelf_id = stringTointeger(req->getQueryParam("Shelf_Id"));
        body<<R"(<input type='hidden' name="Recipe_Id" value=')"<<recipe_id
            <<"'/>"
            <<R"(<input type='hidden' name="Shelf_Id" value=')"<<shelf_id
            <<R"('/><br><button type="submit">Apply</button><br/></form><a href="/show_recipe_indetail?Recipe_Id=)"
            <<recipe_id<<"&Shelf_Id="<<shelf_id
            <<R"("><button>Back</button><br><br></a><a href="/"><button>Logout</button></a></div>)"
            <<"</body></html>";
        res->setBody(body.str());
	}
	catch(string error)
	{
		std::ostringstream error_body;
		error_body << "<!DOCTYPE html>" << "<html>" 
		<< "<head>An error has ocuured while trying to Change Rate!</head>"
		<<"<br/>"<<"<p>Error message: "<< error <<"</p>" << "</html>";
		res->setBody( error_body.str());
	}
  	return res;
}  

Response *Put_Change_Rate_Handler::callback( Request *req ) 
{
	Response *res = new Response;
	res->setHeader( "Content-Type" , "text/html" );
    ostringstream body;
    body<<read_file("Put_rate.txt");
	try
	{
        cli->get_goodeats()->change_rate(stringTointeger(req->getBodyParam("Recipe_Id")),stof(req->getBodyParam("Score")));
        body<<R"(<a href="/change_rating?Recipe_Id=)"<<req->getBodyParam("Recipe_Id")
            <<"&Shelf_Id="<<req->getBodyParam("Shelf_Id")
            <<R"("><button>Back</button><br><br></a></div></body></html>)";
        res->setBody(body.str());
	}
    
	catch(string error)
	{
		std::ostringstream error_body;
		error_body << "<!DOCTYPE html>" << "<html>" 
		<< "<head>An error has ocuured while trying to Change Rate!</head>"
		<<"<br/>"<<"<p>Error message: "<< error <<"</p>" << "</html>";
		res->setBody( error_body.str());
	}
  	return res;
} 
Response *Show_Shelves_Handler::callback( Request *req ) 
{
	Response *res = new Response;
	res->setHeader( "Content-Type" , "text/html" );
    ostringstream body;
    body<<read_file("shelves.txt");
	try
	{
        vector<Shelf*> shelves = cli->get_goodeats()->get_logged_in_user()->get_shelves();
        for (int i=0;i<shelves.size();i++)
        {
            add_this_shelf(shelves[i]->get_id(),shelves[i]->get_name(),body);     
        }
        res->setBody(body.str());
	}
	catch(string error)
	{
		std::ostringstream error_body;
		error_body << "<!DOCTYPE html>" << "<html>" 
		<< "<head>An error has ocuured while trying to Show shelves!</head>"
		<<"<br/>"<<"<p>Error message: "<< error <<"</p>" << "</html>";
		res->setBody( error_body.str());
	}
  	return res;
}
void add_this_shelf(int id , string name , ostringstream& body)
{
    body<<"<tr>"<<"<th>"<<"<a href='show_shelf_indetail?Id="<<id
        <<"'>"<<id<<"</a>"<<"</th>"<<"<th>"<<name<<"</th>"<<"</tr>";
}
Response *Shelf_Adder_Handler::callback( Request *req ) 
{
	Response *res = new Response;
	res->setHeader( "Content-Type" , "text/html" );
    ostringstream body;
	try
	{
		int id = cli->get_goodeats()->make_shelf(req->getBodyParam("Name"));
        body<<read_file("successfuly_add_shelf.txt");
        body<<id<<"</p>"<<"</body>"<<"</html>";
        res->setBody(body.str());
	}
	catch(string error)
	{
		body << "<!DOCTYPE html>" << "<html>" 
		<< "<head>An error has ocuured while trying to Add!</head>"
		<<"<br/>"<<"<p>Error message: "<< error <<"</p>" << "</html>";
		res->setBody( body.str());
	}
  	return res;
}

Response *Shelf_Detail_Handler::callback( Request *req ) 
{
	Response *res = new Response;
	res->setHeader( "Content-Type" , "text/html" );
    ostringstream body;
    body<<read_file("shelf_detail.txt");
	try
	{

        Shelf* this_shelf = cli->get_goodeats()->find_this_shelf(stringTointeger(req->getQueryParam("Id")));
        for(int i =0;i<this_shelf->get_recipes().size();i++)
        {
            Recipe_detail this_recipe = this_shelf->get_recipes()[i]->get_recipe_details();
            add_this_recipe_detail(body,this_recipe,this_shelf->get_id());
        }
        add_rest_shelf_detail(body,this_shelf);
        //body<<read_file("Ruser_show_recipe_detail2.txt");
        res->setBody(body.str());
	}
	catch(string error)
	{
		std::ostringstream error_body;
		error_body << "<!DOCTYPE html>" << "<html>" 
		<< "<head>An error has ocuured while trying to Show!</head>"
		<<"<br/>"<<"<p>Error message: "<< error <<"</p>" << "</html>";
		res->setBody( error_body.str());
	}
  	return res;
}
void add_rest_shelf_detail(ostringstream& body,Shelf* this_shelf)
{
    body<<R"(</table></div><div style = "position:absolute; left:180px; top:300px; color:teal">)"
        <<"<p>"<<"shelf id = "<<this_shelf->get_id()<<"<br>"
        <<"shelf name : "<<this_shelf->get_name()<<"</p><br>"
        <<R"( <a href="/add_recipe?Shelf_Id=)"<<this_shelf->get_id()
        <<R"("><button>Add Recipe</button></a><a href="/remove_recipe?shelf_id=)"
        <<this_shelf->get_id()
        <<R"("><button>Remove Recipe</button><br><br></a><a href="/show_shelves">
        <button>Back</button></a><a href="/"><button>Logout</button></a></div></body></html>)";
}
Response *Add_Recipe_Handler::callback( Request *req ) 
{
	Response *res = new Response;
	res->setHeader( "Content-Type" , "text/html" );
    ostringstream body;
	try
	{
		int shelf_id = stringTointeger(req->getQueryParam("shelf_id"));
        body<<read_file("add_recipe.txt");
        add_rest_file_add_recipe(body,shelf_id);
        res->setBody(body.str());
	}
	catch(string error)
	{
		body << "<!DOCTYPE html>" << "<html>" 
		<< "<head>An error has ocuured while trying to Add!</head>"
		<<"<br/>"<<"<p>Error message: "<< error <<"</p>" << "</html>";
		res->setBody( body.str());
	}
  	return res;
}
void add_rest_file_add_recipe(ostringstream& body , int shelf_id)
{
    body<<R"(<input type='hidden' name='Shelf_Id' value=')"<<shelf_id
        <<R"('/><br><br>
            <button type="submit">Apply</button></div>
        </form>
        <div style ="position:absolute; left:520px; top:400px;">
        <a href="/">
            <button>Logout</button><br><br>
        </a>
        <a href="/show_shelf_indetail?Id=)"
        <<shelf_id<<R"(">
            <button>Back</button>
        </a>
    </body>
    </html>)";
}
Response *Recipe_Being_Added_Handler::callback( Request *req ) 
{
	Response *res = new Response;
	res->setHeader( "Content-Type" , "text/html" );
    ostringstream body;
	try
	{
        cli->get_goodeats()->add_this_recipeto_shelf(stringTointeger(req->getBodyParam("Shelf_Id")),
                                                     stringTointeger(req->getBodyParam("Recipe_Id")));
        body<<read_file("successfuly_addORremove_recipe_to_shelf.txt");
        body<<R"(<a href="add_recipe?Shelf_Id=)"<<req->getBodyParam("Shelf_Id")
            <<R"("><button>Back</button></a></body></html>)";
        res->setBody(body.str());
	}
	catch(string error)
	{
		body << "<!DOCTYPE html>" << "<html>" 
		<< "<head>An error has ocuured while trying to Add!</head>"
		<<"<br/>"<<"<p>Error message: "<< error <<"</p>" << "</html>";
		res->setBody( body.str());
	}
  	return res;
}
Response *Remove_Recipe_Handler::callback( Request *req ) 
{
	Response *res = new Response;
	res->setHeader( "Content-Type" , "text/html" );
    ostringstream body;
	try
	{
		int shelf_id = stringTointeger(req->getQueryParam("shelf_id"));
        body<<read_file("remove_recipe.txt");
        add_rest_file_add_recipe(body,shelf_id);
        res->setBody(body.str());
	}
	catch(string error)
	{
		body << "<!DOCTYPE html>" << "<html>" 
		<< "<head>An error has ocuured while trying to Remove!</head>"
		<<"<br/>"<<"<p>Error message: "<< error <<"</p>" << "</html>";
		res->setBody( body.str());
	}
  	return res;
}
Response *Recipe_Being_Removed_Handler::callback( Request *req ) 
{
	Response *res = new Response;
	res->setHeader( "Content-Type" , "text/html" );
    ostringstream body;
	try
	{
        cli->get_goodeats()->delete_recipe_from_shelf(stringTointeger(req->getBodyParam("Recipe_Id")),
                                                      stringTointeger(req->getBodyParam("Shelf_Id")));
        body<<read_file("successfuly_addORremove_recipe_to_shelf.txt");
        body<<R"(<a href="remove_recipe?Shelf_Id=)"<<req->getBodyParam("Shelf_Id")
            <<R"("><button>Back</button></a></body></html>)";
        res->setBody(body.str());
	}
	catch(string error)
	{
		body << "<!DOCTYPE html>" << "<html>" 
		<< "<head>An error has ocuured while trying to Remove!</head>"
		<<"<br/>"<<"<p>Error message: "<< error <<"</p>" << "</html>";
		res->setBody( body.str());
	}
  	return res;
}