#include "mydatastore.h"
#include "datastore.h"
#include "util.h"
#include "product.h"
#include <algorithm>
#include <cctype> 
#include <map>

MyDataStore::MyDataStore() {}

// Destructor
MyDataStore::~MyDataStore() {
    for (Product* p : products_) {delete p;}
    //test may cause leak
    for (std::pair<const std::string, User*>& u : users_) {
    delete u.second;
    }
     
}

bool MyDataStore::valid_user(const std::string&username) {
  std::string name = convToLower(username);
  return users_.find(name) != users_.end();

}

void MyDataStore::addProduct(Product* product) {
  
    products_.push_back(product);

    std::set<std::string> keys = product->keywords();
    std::set<std::string>::iterator it; 
    for (it = keys.begin(); it != keys.end(); it++) {
        index_[convToLower(*it)].insert(product);
        std::cout << "Keyword: [" << *it << "]" << std::endl;       
    }
}

//amazon functions
void MyDataStore::addToCart(const std::string& user, Product* p) {
    if(p == nullptr) return;
    std::string username = convToLower(user);
    //user is not valid
    if(users_.find(username) == users_.end()) {
        return;
    }
    else {
        carts_[username].push_back(p);
    }
}

std::vector<Product*> MyDataStore::viewCart(const std::string& username) {
    std::string user = convToLower(username);
    std::map<std::string, std::vector<Product*> >::iterator it = carts_.find(user);
    //validity check
    if(it == carts_.end()){
        std::vector<Product*> empty;
        std::cout << "Invalid username" << std::endl;
        return empty;
    }
    return it->second; 
}

void MyDataStore::buyCart(const std::string&username) {
    std::string user = convToLower(username);
    std::map<std::string, User*>::iterator it = users_.find(user);
    if(it == users_.end()) {
        std::cout << "Invalid username" << std::endl;
        return;
    }
    User* u = it->second;
    std::vector<Product*> buy; 
    std::vector<Product*>& cart = carts_[user]; 
    for (std::vector<Product*>::iterator it2 = cart.begin(); it2 != cart.end(); it2++) {
        Product* p = *it2;
        if (p->getQty() > 0 && u->getBalance() >= p->getPrice()) {            
            u->deductAmount(p->getPrice());
            p->subtractQty(1);
        }
        else {
            buy.push_back(p);                                             
    }
    }
    cart.swap(buy);
}


void MyDataStore::addUser(User* user) {
    std::string username = convToLower(user->getName());
    users_[username]=user;
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
   std::vector<Product*> search_results;
    if(terms.empty()) { return search_results;}
    std::set<Product*> running;
    std::map<std::string, std::set<Product*> >::iterator it = index_.find(terms[0]);
    std::set<Product*> bucket;
    if(type == 0) {
        if(it == index_.end()) {
            running = std::set<Product*>();
        } else {
            running = it->second;
        }
        for(size_t i = 1; i<terms.size(); i++) {
            bucket.clear();
            it = index_.find(terms[i]);
            if(it != index_.end()) {
                bucket = it->second;
            }
            running = setIntersection(running, bucket);
        }
    }
    else {
        for(size_t i=0; i<terms.size(); i++) {
            bucket.clear();
            it=index_.find(terms[i]);
            if(it != index_.end()) {
                bucket = it->second;
            }
            running = setUnion(running,bucket);
        }
    }
    for (size_t i = 0; i < products_.size(); ++i) {
            Product* p = products_[i];
            if (running.find(p) != running.end()) {
                search_results.push_back(p);
            }
    }

    return search_results;
}

void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>" << std::endl;
    for(size_t i =0; i<products_.size(); i++) {
        products_[i]->dump(ofile);
    }
    ofile << "</products>" << std::endl;

    ofile << "<users>" << std::endl;
    for(std::map<std::string, User*>::const_iterator it = users_.begin();
         it != users_.end(); ++it) {
        it->second->dump(ofile);
    }
    ofile << "</users>" << std::endl;

}