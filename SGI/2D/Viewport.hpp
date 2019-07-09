#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

#include <ctime>
#include "Window.hpp"
#include "Objetos.hpp"
#include "World.hpp"
#include "Clipping.hpp"

#define PI 3.1415926535897932384626433832795

// Classe Viewport
// Aqui ficam os algoritmos para desenhar as figuras na viewport

class Viewport
{
    public:
        Viewport(double width, double height, World *world):
            _width(width), _height(height), _world(world), _window(width,height),
            _border(new ClipWindow{-0.95,0.95,-0.95,0.95}), _clipping(_border)
            { updateAll(); }
        virtual ~Viewport(){ delete _border; }

	void update(Objeto* obj);

        void clipAlg(const AlgoritmoClipping alg){_clipping.setClipAlg(alg); updateAll();}

        void zoomW(double step){_window.zoom(step); updateAll();}
        void moveW(double x, double y){_window.move(x,y); updateAll();}
        void rotateW(double graus){_window.setAngulo(graus); updateAll();}

        void desenhaObjs(cairo_t* cr);

    protected:
    private:
	Coordinate transformCoordinate(const Coordinate& c) const;
        void transformCoordinates(const Coordinates& coords, Coordinates& output) const;

	void updateAll();
	
        void desenhaObj(Objeto* obj);
        void desenhaPonto(Objeto* obj);
        void desenhaReta(Objeto* obj);
        void desenhaPoligono(Objeto* obj);
	void desenhaCurva2(Objeto* obj);

        void prepareContext(const Objeto* obj);

        double _width, _height;
        World *_world;
        Window _window;

        cairo_t* _cairo;

		ClipWindow *_border;
        Clipping _clipping;

};

void Viewport::update(Objeto* obj)
{
    auto t = _window.getT();
    obj->transformN(t);
    if(!_clipping.clip(obj))
        obj->getCoordsN().clear();
}


void Viewport::updateAll()
{
    _window.updateTransform();
    auto element = _world->getFirstObject();
    while(element != nullptr)
    {
        update(element->getInfo());
        element = element->getProximo();
    }
}


Coordinate Viewport::transformCoordinate(const Coordinate& c) const 
{
    const Coordinate wmin = _window.wMin();
    const Coordinate wmax = _window.wMax();
    double x = ((c.x-wmin.x)/(wmax.x-wmin.x))*_width;
    double y = (1-((c.y-wmin.y)/(wmax.y-wmin.y)))*_height;
    return Coordinate(x,y);
}

void Viewport::transformCoordinates(const Coordinates& coords, Coordinates& output) const 
{
    for(const auto &c : coords)
        output.push_back(transformCoordinate(c));
}

void Viewport::desenhaObjs(cairo_t* cr)
{
    _cairo = cr;
    auto element = _world->getFirstObject();
    while(element != nullptr)
    {
        desenhaObj(element->getInfo());
        element = element->getProximo();
    }
    desenhaObj(_border);
}

void Viewport::desenhaObj(Objeto* obj)
{
    if(obj->getCoordsNSize() == 0) return;
    switch(obj->getType())
    {
        case ObjType::OBJETO:
            break;
        case ObjType::PONTO:
            this->desenhaPonto(obj);
            break;
        case ObjType::RETA:
            this->desenhaReta(obj);
            break;
        case ObjType::POLIGONO:
            this->desenhaPoligono(obj);
            break;
        case ObjType::CURVA2:
            // TODO
        case ObjType::CURVABSPLINE:
            this->desenhaCurva2(obj);
            break;
    }
}

void Viewport::desenhaPonto(Objeto* obj)
{
    Coordinate coord = transformCoordinate(obj->getCoordN(0));
    prepareContext(obj);
    float size = (_width/_window.getWidth())/2;
    size = size < 0.7 ? 0.7 : (size > 2 ? 2 : size);
    cairo_move_to(_cairo, coord.x, coord.y);
    cairo_arc(_cairo, coord.x, coord.y, 1.0, 0.0, (2*PI) );
    cairo_fill(_cairo);
}

void Viewport::desenhaReta(Objeto* obj)
{
    auto coords = obj->getCoordsN();
    Coordinates coordsN;
    if(coords[0] == coords[1])
    {
        desenhaPonto(obj);
        return;
    }
    transformCoordinates(coords, coordsN);
    prepareContext(obj);
    cairo_move_to(_cairo, coordsN[0].x, coordsN[0].y);
    cairo_line_to(_cairo, coordsN[1].x, coordsN[1].y);
    cairo_stroke(_cairo);
}

void Viewport::desenhaPoligono(Objeto* obj)
{
    auto coords = obj->getCoordsN();
    Coordinates coordsN;
    if(coords.size() == 1)
    {
        desenhaPonto(obj);
        return;
    }
    else if(coords.size() == 2)
    {
        desenhaReta(obj);
        return;
    }
    transformCoordinates(coords, coordsN);
    prepareContext(obj);
    cairo_move_to(_cairo, coordsN[0].x, coordsN[0].y);
    for(unsigned int i = 0; i<coordsN.size(); i++)
        cairo_line_to(_cairo, coordsN[i].x, coordsN[i].y);
    cairo_close_path(_cairo);
    Poligono* p = (Poligono*) obj;
    if(p->filled())
    {
        cairo_stroke_preserve(_cairo);
        cairo_fill(_cairo);
    }
    else
        cairo_stroke(_cairo);
}

void Viewport::desenhaCurva2(Objeto* obj)
{
    auto coords = obj->getCoordsN();
    Coordinates coordsN;

    transformCoordinates(coords, coordsN);
    prepareContext(obj);

    cairo_move_to(_cairo, coordsN[0].x, coordsN[0].y);
    for(unsigned int i = 0; i<coordsN.size(); i++)
        cairo_line_to(_cairo, coordsN[i].x, coordsN[i].y);

    cairo_stroke(_cairo);
}

void Viewport::prepareContext(const Objeto* obj)
{
    cairo_set_source_rgb(_cairo, 0, 0, 0);
    cairo_set_line_width(_cairo, ((obj==_border) ? 3 : 1) );
}

#endif // VIEWPORT_HPP
