#include "InputGestureDirectObjects.hpp"

namespace tuio
{

void InputGestureDirectObjects::addTuioObject(int32 id, int32 f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel)
{
    DirectObject * dob = new DirectObject();
    dob->s_id = id;
    dob->f_id = f_id;
    dob->setX( xpos);
    dob->setY( ypos);
    dob->angle = angle;
    dob->xspeed = xspeed;
    dob->yspeed= yspeed;
    dob->rspeed = rspeed;
    dob->maccel = maccel;
    dob->raccel = raccel;
    objects[id]= dob;
    SimpleCallEvent(CanDirectObjects,newObject,(dob));
}

void InputGestureDirectObjects::enterTuioObject(int32 id, int32 f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel)
{
    DirectObject * dob = new DirectObject();
    dob->s_id = id;
    dob->f_id = f_id;
    dob->setX( xpos);
    dob->setY( ypos);
    dob->angle = angle;
    dob->xspeed = xspeed;
    dob->yspeed= yspeed;
    dob->rspeed = rspeed;
    dob->maccel = maccel;
    dob->raccel = raccel;
    objects[id]= dob;
    SimpleCallEvent(CanDirectObjects,enterObject,(dob));
}

void InputGestureDirectObjects::updateTuioObject(int32 id, int32 f_id ,float xpos,float ypos, float angle, float xspeed,float yspeed,float rspeed,float maccel, float raccel)
{
    DirectObject * dob = objects[id];
    dob->s_id = id;
    dob->f_id = f_id;
    dob->setX( xpos);
    dob->setY( ypos);
    dob->angle = angle;
    dob->xspeed = xspeed;
    dob->yspeed= yspeed;
    dob->rspeed = rspeed;
    dob->maccel = maccel;
    dob->raccel = raccel;
    SimpleCallEvent(CanDirectObjects,updateObject,(dob));
}

void InputGestureDirectObjects::removeTuioObject(int32 id)
{
    SimpleCallEvent(CanDirectObjects,removeObject,(objects[id]));
}

void InputGestureDirectObjects::exitTuioObject(int32 id)
{
    SimpleCallEvent(CanDirectObjects,exitObject,(objects[id]));
}

}
