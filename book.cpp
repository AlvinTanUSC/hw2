#include "book.h"
#include <iomanip>
#include <sstream>
#include "util.h"
using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string author, const std::string isbn):
  Product(category, name, price, qty),
  author_(author),
  isbn_(isbn)
{
  
}

Book::~Book(){

}

std::set<std::string> Book::keywords() const{
  set<string> keyword = parseStringToWords(author_);
  set<string> names = parseStringToWords(name_);
  keyword = setUnion(keyword, names);
  keyword.insert(isbn_);
  return keyword;
}

std::string Book::displayString() const{
  stringstream ss;
  ss << fixed << setprecision(2) << price_;
  return name_ + "\nAuthor: " + author_ + " ISBN: " + isbn_ + "\n" + ss.str() + " " + to_string(qty_) + " left.";
}
void Book::dump(std::ostream& os) const{
  os << category_ << endl;
  os << name_ << endl;
  os << fixed << setprecision(2) << price_ << endl;
  os << qty_ << endl;
  os << isbn_ << endl;
  os << author_ << endl;
}