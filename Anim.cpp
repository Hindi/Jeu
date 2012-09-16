#include "Anim.hpp"

// Par d�faut
Anim::Anim()
{

}

// d�structeur
Anim::~Anim()
{

}

// Par copie
Anim::Anim(const Anim& Cpy)
{
    myFrame = Cpy.myFrame;
}

// Ajouter une frame
void Anim::PushFrame(const Frame& NewFrame)
{
    myFrame.push_back(NewFrame);
}

// Nombre de frame(s)
size_t Anim::Size() const
{
    return myFrame.size();
}

// Acc�s a la frame num�ro N
Frame& Anim::operator [] (size_t N)
{
    return myFrame[N];
}
