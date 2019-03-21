#ifndef COORDENADA_HPP
#define COORDENADA_HPP

class Coordenada{
private:
    double x;
    double y;
    double z;
 public:
    Coordenada(double nx, double ny, double nz=0.0);
    Coordenada():x(0),y(0),z(0){}

    double getX();
    double getY();
    double getZ();

    void setX(double newX);
    void setY(double newY);
    void setZ(double newZ);

    Coordenada operator+(Coordenada& b);
    Coordenada operator-(Coordenada& b);
    Coordenada operator*(double);
    bool operator==(Coordenada& b);


Coordenada::Coordenada(double nx, double ny, double nz){
    x = nx;
    y = ny;
    z = nz;

}

double Coordenada::getX(){
    return x;
}
double Coordenada::getY(){
    return y;
}
double Coordenada::getZ(){
    return z;
}
void Coordenada::setX(double newX){
    x = newX;
}
void Coordenada::setY(double newY){
    y = newY;
}
void Coordenada::setZ(double newZ){
    z = newZ;
}
Coordenada Coordenada::operator+(Coordenada& b){
    return Coordenada(x + b.getX(),y + b.getY(),z + b.getZ());
}
Coordenada Coordenada::operator-(Coordenada& b){
    return Coordenada(x-b.getX(),y-b.getY(),z-b.getZ());
}
Coordenada Coordenada::operator*(double escalar){
    return Coordenada(x*escalar,y*escalar,z*escalar);
}
bool Coordenada::operator==(Coordenada& b){
    return x == b.getX() && y == b.getY() && z == b.getZ();
}



};

#endif // COORDENADA_HPP
