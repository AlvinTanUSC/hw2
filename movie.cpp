#include "movie.h"
#include "util.h"
#include <iomanip>
#include <sstream>
using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating):
  Product(category, name, price, qty),
  genre_(genre),
  rating_(rating)
{
  
}

Movie::~Movie(){

}

std::set<std::string> Movie::keywords() const{
  set<string> keyword= parseStringToWords(name_);
  keyword.insert(convToLower(genre_));
  return keyword;
}

std::string Movie::displayString() const{
  stringstream ss;
  ss << fixed << setprecision(2) << price_;
  return name_ + "\nGenre: " + genre_ + " Rating: " + rating_ + "\n" + ss.str() + " " + to_string(qty_) + " left.";
}
void Movie::dump(std::ostream& os) const{
  os << category_ << endl;
  os << name_ << endl;
  os << fixed << setprecision(2) << price_ << endl;
  os << qty_ << endl;
  os << genre_ << endl;
  os << rating_ << endl;
}