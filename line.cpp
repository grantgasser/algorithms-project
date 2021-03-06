/*
    Author: Chris Helms
    Assignment Title: Project 1
    Assignment Description: Graphically displays input curves to the screen.
    Due Date: 1/28/2019
    Date Created: 1/22/2019
    Date Last Modified: 5/5/2019
*/

#include "line.h"

/*
    Description: Default constructor.
    Return: N/A
    Precondition: The instance does not already exist.
    Postcondition: An instance is created.
*/
line::line() {
    p1 = point();
    p2 = point();
    color = color_rgb();
}

/*
    Description: Custom constructor.
    Return: N/A
    Precondition: The instance does not already exist.
    Postcondition: An instance is created with points p1 & p2.
*/
line::line(point p1, point p2) {
    this->p1 = p1;
    this->p2 = p2;
    color = color_rgb();
}

/*
    Description: Custom constructor.
    Return: N/A
    Precondition: The instance does not already exist.
    Postcondition: An instance is created with points p1 & p2.
*/
line::line( pair<int, int> p1, pair<int, int> p2 ) {
    this->p1 = point( p1.first, p1.second );
    this->p2 = point( p2.first, p2.second );
    color = color_rgb();
}

/*
    Description: Destructor.
    Return: N/A
    Precondition: Instance exists.
    Postcondition: The instance is destroyed.
*/
line::~line() {

}

/*
    Description: Displays line to screen.
    Return: void
    Precondition: Output stream is valid.
    Postcondition: Data is unchanged.
*/
void line::display(ostream& out) {
    double m, b;
    if (slope(m)) {
        intercept(b);
        out << "y = " << m << "x + " << b << endl;
    }
    else {
        out << "x = " << p1.getX() << endl;
    }
}

/*
    Description: Graphically displays line to screen.
    Return: void
    Precondition: Plotter has been initialized.
    Postcondition: Data is unchanged.
*/
void line::draw(SDL_Plotter& g) {
    double m, b;
    if (slope(m)) {
        intercept(b);
        p1.setColor(color);
        p1.draw(g);
        if ( m <= 1 && m >= -1 ) {
            for ( int x = p1.getX() + 1; x < p2.getX(); x++ ) {
                double y = m * x + b;
                point p( x, (int) y );
                p.setColor( color );
                p.draw( g );
            }
        }
        else if( m > 1 ) {
            for ( int y = p1.getY() + 1; y < p2.getY(); y++ ) {
                double x = ( y - b ) / m;
                point p( (int) x, y );
                p.setColor( color );
                p.draw( g );
            }
        }
        else {
            for ( int y = p1.getY() - 1; y > p2.getY(); y-- ) {
                double x = ( y - b ) / m;
                point p( (int) x, y );
                p.setColor( color );
                p.draw( g );
            }
        }
        p2.setColor(color);
        p2.draw(g);
    }
    else {
        if (p2.getY() < p1.getY()) {
            swap(p1, p2);
        }
        p1.setColor(color);
        p1.draw(g);
        for (int y = p1.getY() + 1; y < p2.getY(); y++) {
            point p(p1.getX(), y);
            p.setColor(color);
            p.draw(g);
        }
        p2.setColor(color);
        p2.draw(g);
    }
}

/*
    Description: Sets p1 to p.
    Return: void
    Precondition: p is valid.
    Postcondition: p1 is set to p.
*/
void line::setP1(point p) {
    this->p1 = p;
}

/*
    Description: Sets p2 to p.
    Return: void
    Precondition: p is valid.
    Postcondition: p2 is set to p.
*/
void line::setP2(point p) {
    this->p2 = p;
}

/*
    Description: Determines if slope exists & calculates.
    Return: bool
    Precondition: m is valid.
    Postcondition: m is set to the calculated slope.
*/
bool line::slope(double& m) {
    if (p1.getX() != p2.getX()) {
        if (p2.getX() < p1.getX()) {
            swap(p1, p2);
        }
        m = (double)(p2.getY() - p1.getY()) / (p2.getX() - p1.getX());
        return true;
    }

    return false;
}

/*
    Description: Determines if intercept exists & calculates.
    Return: bool
    Precondition: b is valid.
    Postcondition: b is set to the calculated intercept.
*/
bool line::intercept(double& b) {
    double m = 0;
    if (slope(m)) {
        b = p1.getY() - m * p1.getX();
        return true;
    }
    return false;
}

/*
    Description: Graphically displays line to screen.
    Return: void
    Precondition: Plotter has been initialized & p is valid.
    Postcondition: Data is unchanged.
*/
void draw( SDL_Plotter& g, pair<int, int> &p1,
           pair<int, int> &p2, color_rgb c ) {
    point w( p1.first, p1.second ), z( p2.first, p2.second );
    line k( w, z );
    k.setColor( c );
    k.draw( g );
}