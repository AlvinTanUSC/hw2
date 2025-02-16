#include "clothing.h"
#include "util.h"
#include <iomanip>
#include <sstream>
using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand):
  Product(category, name, price, qty),
  size_(size),
  brand_(brand)
{
  
}

Clothing::~Clothing(){
  
}

std::set<std::string> Clothing::keywords() const{
  set<string> keyword = parseStringToWords(brand_);
  set<string> names = parseStringToWords(name_);
  
  keyword = setUnion(keyword, names);
  return keyword;
}

std::string Clothing::displayString() const{
  stringstream ss;
  ss << fixed << setprecision(2) << price_;
  return name_ + "\nSize: " + size_ + " Brand: " + brand_ + "\n" + ss.str() + " " + to_string(qty_) + " left.";
}
void Clothing::dump(std::ostream& os) const{
  os << category_ << endl;
  os << name_ << endl;
  os << fixed << setprecision(2) << price_ << endl;
  os << qty_ << endl;
  os << size_ << endl;
  os << brand_ << endl;
}