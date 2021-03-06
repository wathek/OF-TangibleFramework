/*
    OF-TangibleFramework . Framework for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2009 Daniel Gallardo Grassot <daniel.gallardo@upf.edu>

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
#include "ofMain.h"
#include "GraphicDispatcher.hpp"

GraphicDispatcher::GraphicDispatcher(){
}

GraphicDispatcher::~GraphicDispatcher(){
}

void GraphicDispatcher::Draw(){
    for(std::list<Graphic*>::iterator it = graphics.begin(); it != graphics.end(); it++)
        (*it)->draw();
}

void GraphicDispatcher::Update(){
    std::list<Graphic*> l (graphics);
    for(std::list<Graphic*>::iterator it = l.begin(); it != l.end(); it++)
        (*it)->update();
}

void GraphicDispatcher::Resize(int w, int h){
    std::list<Graphic*> l (graphics);
    for(std::list<Graphic*>::iterator it = l.begin(); it != l.end(); it++)
        (*it)->resize(w,h);
}

void GraphicDispatcher::AddGraphic(Graphic* graphic){
    graphics.push_back(graphic);
    graphics.sort(CompareLayers);
}

void GraphicDispatcher::RemoveGraphic(Graphic* graphic){
    graphics.remove(graphic);
}

void GraphicDispatcher::bring_top(Graphic* graphic){
    for ( std::list<Graphic*>::iterator it=graphics.begin(); it!=graphics.end();it++){
        if ( (*it) == graphic){
            graphics.remove(*it);
            break;
        }
    }
    graphics.push_back(graphic);
    graphics.sort(CompareLayers);
}
