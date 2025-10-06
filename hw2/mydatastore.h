#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include "datastore.h"
#include "user.h"

class Product;
class User;


class MyDataStore : public DataStore { 
  public:
    MyDataStore();
    ~MyDataStore() override;
    void addProduct(Product* p) override;
    void addUser(User* u) override;
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;
    void dump(std::ostream& ofile) override;
    //database helper functions
    std::vector<Product*> viewCart(const std::string& username);
    void addToCart(const std::string& user, Product* p);
    void buyCart(const std::string&username);
    bool valid_user(const std::string&username);
private: 
    std::vector<Product*> products_;
    std::map<std::string, User*> users_;
    std::map<std::string, std::set<Product*>> index_;
    std::map<std::string, std::vector<Product*>> carts_;
    
};
#endif