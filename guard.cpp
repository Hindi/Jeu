#include "guard.h"


Guard::Guard( int id, std::string msg):id(id),msg(msg)
{

}

void Guard::Run() {
		for( int i=4000; i>0; --i ) {
			std::cout<<"<"<<id<<","<<msg<<">"<<" "<<i<<std::endl;
		}
	}
