#include "clothing.h"
#include "util.h"
#include <iostream>
#include <sstream>

Clothing::Clothing(const std::string& name, double price, int quantity
        ,const std::string& size, const std::string& brand)
        : Product("clothing",name, price, quantity), size_(size), brand_(brand)
        {}

std::set<std::string> Clothing::keywords() const{

    std:: string keyword_master = getName() + " " + size_ + " " + brand_;
    std::set<std::string> keywords = parseStringToWords(keyword_master);
    return keywords;
}
std::string Clothing::displayString() const {
    std::ostringstream out;
    out << getName() << std::endl;
    out << "Size: " << size_ << " Brand: " << brand_ << std::endl;
    out << price_ << " " << getQty() << " left." << std::endl;

    return out.str();
}
void Clothing::dump(std::ostream& os) const {
    os << "clothing" << std::endl;
    os << getName() << std::endl;
    os << price_ << std::endl;
    os << getQty() << std::endl;
    os << size_ << std::endl;
    os << brand_ << std::endl;
}



