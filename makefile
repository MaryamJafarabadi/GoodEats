all:goodeats.out
goodeats.out : main.o  Cli.o  error.o utilities.o request.o response.o server.o route.o handlers.o goodeats.o user.o Ruser.o chef.o recipe.o shelf.o
	g++ -g -std=c++11 main.o Cli.o error.o utilities.o request.o response.o server.o route.o handlers.o goodeats.o user.o Ruser.o chef.o recipe.o shelf.o -o goodeats.out

main.o : main.cpp Cli.hpp
	g++ -g -std=c++11 -c main.cpp 

Cli.o : Cli.cpp error.hpp server/server.hpp handlers.hpp 
	g++ -g -std=c++11 -c Cli.cpp 

error.o : error.cpp error.hpp
	g++ -g -std=c++11 -c error.cpp 

handlers.o : handlers.cpp handlers.hpp Cli.hpp error.hpp
	g++ -g -std=c++11 -c handlers.cpp

goodeats.o : goodeats.cpp goodeats.hpp error.hpp shelf.hpp recipe.hpp user.hpp Ruser.hpp chef.hpp 
	g++ -g --std=c++11 -c goodeats.cpp

user.o : user.cpp user.hpp shelf.hpp recipe.hpp
	g++ -g --std=c++11 -c user.cpp

Ruser.o : Ruser.cpp Ruser.hpp user.hpp shelf.hpp error.hpp recipe.hpp
	g++ -g -std=c++11 -c Ruser.cpp

chef.o : chef.cpp chef.hpp shelf.hpp recipe.hpp error.hpp
	g++ -g -std=c++11 -c chef.cpp 

shelf.o : shelf.cpp shelf.hpp recipe.hpp error.hpp
	g++ -g -std=c++11 -c shelf.cpp 

recipe.o : recipe.cpp recipe.hpp error.hpp
	g++ -g -std=c++11 -c recipe.cpp 

server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp 
	g++ -g -std=c++11 -c server/server.cpp 

route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	g++ -g -std=c++11 -c server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp 

request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	g++ -g -std=c++11 -c utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp

response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	g++ -g -std=c++11 -c utils/response.cpp utils/response.hpp utils/include.hpp

utilities.o: utils/utilities.cpp utils/utilities.hpp
	g++ -g -std=c++11 -c utils/utilities.cpp utils/utilities.hpp

clean :
	rm *.o
	rm goodeats.out 