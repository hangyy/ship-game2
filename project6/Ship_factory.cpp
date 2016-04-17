#include "Ship_factory.h"
#include "Navigation.h"
#include "Warships.h"
#include "Tanker.h"
#include "Cruise_ship.h"
#include "Utility.h"
#include "Model.h"

#include <memory>
using std::shared_ptr;

/* This is a very simple form of factory, a function; you supply the information, it creates
 the specified kind of object and returns a pointer to it. The Ship is allocated
 with new, so some other component is resposible for deleting it.
 */
shared_ptr<Ship> create_ship(const std::string& name, const std::string& type,
                              Point initial_position) {
    if (type == "Cruiser")
        return shared_ptr<Ship>(new Cruiser(name, initial_position));
    else if (type == "Tanker")
        return shared_ptr<Ship>(new Tanker(name, initial_position));
    else if (type == "Cruise_ship")
        return shared_ptr<Ship>(new Cruise_ship(name, initial_position));
    else if (type == "Torpedo_boat")
        return shared_ptr<Ship>(new Torpedo_boat(name, initial_position));
    else
        throw Error("Trying to create ship of unknown type!");
}

shared_ptr<Ship> restore_ship(std::istream& is) {
    std::string type;
    is >> type;
    shared_ptr<Ship> new_ship;
    if (type == "Cruiser") {
        new_ship = shared_ptr<Ship>(new Cruiser(is));
    } else if (type == "Tanker") {
        new_ship = shared_ptr<Ship>(new Tanker(is));
    } else if (type == "Cruise_ship") {
        new_ship = shared_ptr<Ship>(new Cruise_ship(is));
    } else if (type == "Torpedo_boat") {
        new_ship = shared_ptr<Ship>(new Torpedo_boat(is));
    }
    if (Model::get_instance().is_ship_present(new_ship->get_name())) {
        *(Model::get_instance().get_ship_ptr(new_ship->get_name())) = *new_ship;
    }
    return new_ship;
}