#include "mydatastore.h"
#include "util.h"
using namespace std;

MyDataStore::~MyDataStore(){
  while(!products_.empty()){
    Product* p = products_.back();
    products_.pop_back();
    delete p;
  }
  while(!users_.empty()){
    User* u = users_.back();
    users_.pop_back();
    delete u;
  }
}

void MyDataStore::addProduct(Product* p){
  products_.push_back(p);
}

void MyDataStore::addUser(User* u){
  users_.push_back(u);
  usernames_[convToLower(u->getName())] = u;
}

void MyDataStore::dump(std::ostream& ofile){
  ofile <<"<products>" << endl;
  for(int i = 0; i < products_.size(); i++)
    products_[i]->dump(ofile);
  ofile <<"</products>" << endl;
  ofile <<"<users>" << endl;
  for(int i = 0; i < users_.size(); i++)
    users_[i]->dump(ofile);
  ofile <<"</users>" << endl;
}

void MyDataStore::addCart(string username, Product* p){
  carts_[convToLower(username)].push_back(p);
}

bool MyDataStore::checkUser(string username){
  return usernames_.find(convToLower(username)) != usernames_.end(); 
}

void MyDataStore::viewCart(string username){
  username = convToLower(username);
  for(deque<Product*>::iterator it = carts_[username].begin(); it != carts_[username].end(); it++){
    cout << "Cart\t" << (it - carts_[username].begin()) + 1 << endl;
    cout << (*it) -> displayString() << endl;
  }
}

void MyDataStore::buyCart(string username){
  username = convToLower(username);
  deque<Product*> temp;
  while(!carts_[username].empty()){
    Product* p = carts_[username].front();
    carts_[username].pop_front();
    if((p -> getQty()) > 0 && (usernames_[username]->getBalance()) >= (p->getPrice())){
      p -> subtractQty(1);
      usernames_[username]->deductAmount(p -> getPrice());
    } else {
      temp.push_back(p);
    }

  }
  carts_[username] = temp;
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
  vector<Product*> results;
  set<string> searchterms;
  for(string s : terms)
    searchterms.insert(s);
  if(!type){
    for(Product* p : products_){
      set<string> keywords = p->keywords();
      set<string> inter = setIntersection(keywords, searchterms);
      if(setIntersection(searchterms, keywords).size() == terms.size())
        results.push_back(p);
      }
    } else {
    for(Product* p : products_){
          set<string> keywords = p->keywords();
          if(setIntersection(keywords, searchterms).size())
            results.push_back(p);
          }
    }
  return results;
}