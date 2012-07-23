#ifndef GUARD_H_INCLUDED
#define GUARD_H_INCLUDED
#include <SFML/System.hpp>
#include <string>
#include <iostream>

class Guard:public sf::Thread
{
public:
	Guard( int id, std::string msg);
private:
	// Run() is a virtual function of sf::Thread
	void Run();

	int id;
	std::string msg;
};

#endif // GUARD_H_INCLUDED
