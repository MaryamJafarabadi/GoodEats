
#include "user.hpp"
#include <sstream>

User::User(string name, string password_, string type_,bool is_)
{
	username = name;
	password = password_;
	type = type_;
	is_logged_in = is_;
}
string User::get_username()
{
	return username;
}
string User::get_password()
{
	return password;
}
void User::set_is_logged_in(bool is_)
{
	is_logged_in = is_;
}
bool User::get_is_logged_in()
{
    return is_logged_in;
}
string User::get_type()
{
    return type;
}