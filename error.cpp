#include "error.hpp"

string bad_req()
{
	return "Bad Request";
}
string perm_den()
{
	return "Permission Denied";
}
string not_f()
{
	return "Not Found";
}
string twice_signup()
{
	return "you are already signed up! go to login page:)";
}
string already_rate()
{
	return "you have already rated for this recipe!You can just change the score if you want.";
}
string rate_first()
{
	return "you haven't yet rated for this recipe. Rate first!";
}