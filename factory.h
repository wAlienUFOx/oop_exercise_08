#ifndef FACTORY_H
#define FACTORY_H

#include <iostream>
#include "figure.h"

namespace factory {

    class Factory {
    public:
        std::shared_ptr<figures::Figure> FigureCreate(std::istream &is) const {
            std::string type;
            std::cin >> type;
            if (type == "rhombus") {
                return std::shared_ptr<figures::Figure>(new figures::Rhombus(is));
            } else if (type == "rectangle") {
                return std::shared_ptr<figures::Figure>(new figures::Rectangle(is));
            } else if (type == "trapeze") {
                return std::shared_ptr<figures::Figure>(new figures::Trapeze(is));
            }
            throw std::logic_error("Wrong. Figures: rhombus, rectangle, trapeze");
        }
    };
}
#endif
