#ifndef CLI_HPP
#define CLI_HPP

#include <sstream>
#include <cstring>
#include "error.hpp"
#include "goodeats.hpp"

#define OK_SENTENCE "OK"
using namespace std;
class Cli
{
public:
	void run();
    Goodeats* get_goodeats();
private:
	istringstream strr;
	Goodeats* goodeats;
    bool someone_is_logged_out=false;
	
};
#endif