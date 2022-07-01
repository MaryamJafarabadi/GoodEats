#include "Cli.hpp"
#include "error.hpp"
#include <iostream>
#include<vector>
#include "server/server.hpp"
#include "handlers.hpp"

void Cli::run()
{
    goodeats = new Goodeats;
    Server server(20250);
    server.get("/background.jpg",new ShowImage("background.jpg"));
    server.get("/chef_background.jpg",new ShowImage("chef_background.jpg"));
    server.get("/Ruser_background.jpg",new ShowImage("Ruser_background.jpg"));
    server.get("/this.jpg",new ShowImage("this.jpg"));
    server.get( "/" , new ShowPage( "signup.html" ));
    server.get("/signup",new Signup_Handler(this));
    server.get("/login_p" , new ShowPage("login.html"));
    server.get("/login", new Login_Handler(this));
    server.get("/signup_success" , new ShowPage("signup_success.html"));
    server.get("/chef_HomePage",new Chef_Login_Handler(this));
    server.get("/Ruser_HomePage",new Ruser_Login_Handler(this));
    server.get("/chef_add_recipe",new ShowPage("chef_add_recipe.html"));
    server.post("/chef_add_recipe",new Chef_Adder_Handler(this));
    server.get("/chef_remove_recipe",new ShowPage("chef_remove_recipe.html"));
    server.post("/chef_remove_recipe",new Chef_Remover_Handler(this));
    server.get("/show_recipe_indetail", new Show_Recipe_Handler(this));
    server.get("/rate",new Rate_Handler(this));
    server.post("/rate",new Put_Rate_Handler(this));
    server.get("/change_rating",new Change_Rate_Handler(this));
    server.post("/change_rating",new Put_Change_Rate_Handler(this));
    server.get("/show_shelves",new Show_Shelves_Handler(this));
    server.get("/show_shelf_indetail",new Shelf_Detail_Handler(this));
    server.get("/add_shelf",new ShowPage("shelf_add.html"));
    server.post("/add_shelf",new Shelf_Adder_Handler(this));
    server.get("/add_recipe",new Add_Recipe_Handler(this));
    server.post("/add_recipe",new Recipe_Being_Added_Handler(this));
    server.get("/remove_recipe",new Remove_Recipe_Handler(this));
    server.post("/remove_recipe",new Recipe_Being_Removed_Handler(this));
    server.run();
    /*goodeats = new Goodeats;
    string command;
    while(getline(cin, command))
    {
        someone_is_logged_out = false;
        set_strr(command);
        read_entrance_commands();
    }*/
	
}
Goodeats* Cli::get_goodeats()
{
    return goodeats;
}