/*

    OF-TangibleFramework . Framework for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2010 Carles F. Julià <carles.fernandez@upf.edu>

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

#include "InputGestureHand.hpp"

namespace tuio {
DirectPoint  Hand::getCenter()
{
    DirectPoint p(0,0);
    if(fingers.size() < 1)
        return p;
    float x = 0;
    float y = 0;
    for(std::list<DirectFinger *>::iterator it = fingers.begin(); it != fingers.end(); ++it)
    {
        x += (*it)->getX();
        y += (*it)->getY();
    }
    p.set(x/fingers.size(),y/fingers.size());
    return p;
}

float Hand::getRadius()
{
    float distance = 0;
    BOOST_FOREACH(DirectFinger * f,fingers)
    {
        distance = std::max(f->getDistance(this->center),distance);
    }
    return distance;
}

bool Hand::isValid()
{
    return fingers.size() >= 1;
}

Hand * InputGestureHands::getNeighbour(DirectPoint * p, Hand * ignore)
{
    Hand * winner = NULL;
    float dwinner = 1000;
    BOOST_FOREACH(Hand *h,hands)
    {
        if (h->is_valid && h != ignore)
        {
            float d = h->center.getDistance(p);
            if (d < HAND_MAX_RADIUS and d < dwinner)
            {
                dwinner = d;
                winner = h;
            }
        }
    }
    return winner;
}

void InputGestureHands::newCursor(DirectFinger *df)
{
    Hand * winner = getNeighbour(df);
    if (!winner)
    {
        winner = new Hand(hands.size());
        hands.push_back(winner);
        assignations[df->s_id]=winner;
        winner->fingers.push_back(df);
        winner->UpdateExposedInfo();
        SimpleCallEvent(CanHands,newHand,(winner));
    }
    else
    {
        assignations[df->s_id]=winner;
        winner->fingers.push_back(df);
        winner->UpdateOffset();
        winner->UpdateExposedInfo();
        SimpleCallEvent(CanHands,updateHand,(winner));
    }
}

void InputGestureHands::removeCursor(DirectFinger *f)
{
    Hand * h = assignations[f->s_id];
    h->fingers.remove(f);
    h->UpdateOffset();
    h->UpdateExposedInfo();
    if (!h->is_valid)
    {
     SimpleCallEvent(CanHands,removeHand,(h));
    }
    else
    {
     SimpleCallEvent(CanHands,updateHand,(h));
    }

}

void InputGestureHands::updateCursor(DirectFinger *f)
{
    Hand * h = assignations[f->s_id];
    h->UpdateExposedInfo();
    SimpleCallEvent(CanHands,updateHand,(h));
    if(h->population == 1)
    {
        Hand * candidate = getNeighbour(f,h);
        if(candidate)
        {
            h->fingers.remove(f);
            h->UpdateOffset();
            h->UpdateExposedInfo();
            SimpleCallEvent(CanHands,removeHand,(h));
            assignations[f->s_id]=candidate;
            candidate->fingers.push_back(f);
            candidate->UpdateOffset();
            candidate->UpdateExposedInfo();
            SimpleCallEvent(CanHands,updateHand,(candidate));
        }
    }else
    if(h->getDistance(f) > HAND_MAX_RADIUS)
    {
        h->fingers.remove(f);
        h->UpdateOffset();
        h->UpdateExposedInfo();
        this->newCursor(f);
    }
}

}
