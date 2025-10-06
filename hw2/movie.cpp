#include "movie.h"
#include "util.h"
#include <iostream>
#include <sstream>

Movie::Movie(const std::string& name, double price, int quantity
        ,const std::string& genre, const std::string& rating)
        : Product("movie",name, price, quantity), 
        genre_(genre), rating_(rating)
        {}

std::set<std::string> Movie::keywords() const{

    std:: string keyword_master = getName() + " " + genre_ + " " + rating_;
    std::set<std::string> keywords = parseStringToWords(keyword_master);
    return keywords;
}
std::string Movie::displayString() const {
    std::ostringstream out;
    out << getName() << std::endl;
    out << "Genre: " << genre_ << " Rating: " << rating_ << std::endl;
    out << getPrice() << " " << getQty() << " left." << std::endl;

    return out.str();
}
void Movie::dump(std::ostream& os) const {
    os << "movie" << std::endl;
    os << getName() << std::endl;
    os << price_ << std::endl;
    os << getQty() << std::endl;
    os << genre_ << std::endl;
    os << rating_ << std::endl;
}



