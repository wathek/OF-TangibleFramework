/*

    OF-TangibleFramework . Framework for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2009 Carles F. Julià <carles.fernandez@upf.edu>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.

*/

#ifndef INPUTGESTUREDIRECTFINGERS_H_INCLUDED
#define INPUTGESTUREDIRECTFINGERS_H_INCLUDED

#include "InputGesture.hpp"
#include "TEvent.hpp"
#include "tuioApp.hpp"
#include "DirectPoint.hpp"
#include "InputGestureBasicFingers.hpp"
#include <map>

using namespace osc;

namespace tuio
{


class DirectFinger: public DirectPoint
{
    public:
    int32 s_id;
    float xspeed, yspeed, maccel;
};

SimpleDeclareEvent(CanDirectFingers,removeCursor,int32);
SimpleDeclareEvent(CanDirectFingers,newCursor,int32,DirectFinger *);
SimpleDeclareEvent(CanDirectFingers,updateCursor,int32);


class InputGestureDirectFingers : public CanBasicFingers < CompositeGesture >
{
    std::map<int32,DirectFinger *> fingers;
    public:
        InputGestureDirectFingers(){}
        void addTuioCursor(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel)
        {
            DirectFinger * e = new DirectFinger();
            e->s_id = id;
            e->setX(xpos);
            e->setY(ypos);
            e->xspeed = xspeed;
            e->yspeed = yspeed;
            e->maccel = maccel;
            fingers[id]=e;
            SimpleCallEvent(CanDirectFingers,newCursor,(id,e));
        }
        void updateTuioCursor(int32 id, float xpos,float ypos,float xspeed,float yspeed,float maccel)
        {
            DirectFinger * e = fingers[id];
            e->s_id = id;
            e->set(xpos,ypos);
            e->xspeed = xspeed;
            e->yspeed = yspeed;
            e->maccel = maccel;
            SimpleCallEvent(CanDirectFingers,updateCursor,(id));
        }
        void removeTuioCursor(int32 id)
        {
             SimpleCallEvent(CanDirectFingers,removeCursor,(id));
        }
};




template <class Base>
class CanDirectFingers : public  Base
{
    public:
    //Interface redefined by ofApp
    virtual void newCursor(int32 id, DirectFinger *){}
    virtual void removeCursor(int32 id){}
    virtual void updateCursor(int32 id){}

    //registering
    CanDirectFingers()
    {
        SimpleRegisterEvent(CanDirectFingers,newCursor);
        SimpleRegisterEvent(CanDirectFingers,removeCursor);
        SimpleRegisterEvent(CanDirectFingers,updateCursor);
        Base::template registerIG<InputGestureDirectFingers>();
    }

};


}
#endif // INPUTGESTUREDIRECTFINGERS_H_INCLUDED
