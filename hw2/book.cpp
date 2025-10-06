#include "book.h"
#include "util.h"
//for testing
#include <iostream>
#include <sstream>

/* Book myBook ("The Rainbow Fish", 4.99, 43, 9780735812321, Marcus Pfister)*/
Book::Book(const std::string& name, double price, int quantity
        ,const std::string& isbn, const std::string& author)
        : Product("book",name, price, quantity), isbn_(isbn), author_(author)
        {}

Book::~Book() {}
std::set<std::string> Book::keywords() const{
    std:: string keyword_master = getName() + " " + author_;
    std::set<std::string> keywords = parseStringToWords(convToLower(keyword_master));
    keywords.insert(convToLower((isbn_)));
    return keywords;
}
std::string Book::displayString() const {
    std::ostringstream out;
    out << getName() << std::endl;
    out << "Author: " << author_ << " ISBN: " << isbn_ << std::endl;
    out << price_ << " " << getQty() << " left." << std::endl;

    return out.str();
}
void Book::dump(std::ostream& os) const {
    os << "book" << std::endl;
    os << getName() << std::endl;
    os << price_ << std::endl;
    os << getQty() << std::endl;
    os << isbn_ << std::endl;
    os << author_ << std::endl;
}



