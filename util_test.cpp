#include "util.h"
#include "mydatastore.h"
#include <iostream> 
#include <set>
#include <string>
#include <vector>


//test book
#include "book.h"

//test clothing
#include "clothing.h"

//test movie
#include "movie.h"
using namespace std;
int main() {
    // string text = "Harry's Potter";
    // //cout << text << endl;
    // set<string> dictionary = parseStringToWords(text);
    // for (string w : dictionary) {
    //     cout << "d: " << w << endl;
    // }

    // Book book("The Bluest Eye", 4.99, 5, "231532424", "Toni Morrison");
    // cout << book.getName() << endl;
    // book.keywords();

    /* test book */
    // Clothing shirt("blue shirt", 4.99, 5, "M", "Amazon Basics");
    // cout << shirt.getName() << endl;
    // shirt.keywords();

    // Movie SurfsUp("surfs up", 4000.99, 1, "Comedy", "PG");
    // cout << SurfsUp.getName() << endl;
    // SurfsUp.keywords();

    MyDataStore ds;

    ds.addProduct(new Book("The Great Gatsby", 10.99, 5, "9780743273565", "F. Scott Fitzgerald"));
    ds.addProduct(new Book("The Bluest Eye", 9.99, 2, "231532424", "Toni Morrison"));
    ds.addProduct(new Movie("Surf’s Up", 14.99, 3, "Comedy", "PG"));
    ds.addProduct(new Clothing("Blue Shirt", 19.99, 10, "M", "Amazon Basics"));

    vector<string> terms1 = {"the", "eye"};     // AND search
    vector<string> terms2 = {"great", "eye"};   // OR search

    // 0
    vector<Product*> results_and = ds.search(terms1, 0);
    for (size_t i = 0; i < results_and.size(); ++i) {
        cout << results_and[i]->displayString() << endl;
    }

    // 1
    vector<Product*> results_or = ds.search(terms2, 1);
    for (size_t i = 0; i < results_or.size(); ++i) {
        cout << results_or[i]->displayString() << endl;
    }


    return 0;
}
