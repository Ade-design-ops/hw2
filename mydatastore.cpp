#include "mydatastore.h"
#include "util.h"

using namespace std;

MyDataStore::MyDataStore()
{

}

MyDataStore::~MyDataStore()
{
  for(set<Product*> ::iterator it = products_.begin(); it != products_.end(); ++it){
    delete *it;
  }

  for(map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it){
    delete it->second;
  }
}

void MyDataStore::addUser(User* u)
{
  users_[convToLower(u->getName())] = u;
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type)
{
  vector<Product*>hits;

  if(terms.empty()){
    return hits;
  }

  set<Product*> result;

  for(size_t i = 0; i<terms.size(); i++){
    set<Product*>current;
    map<string, set<Product*> >::iterator found = index_.find(terms[i]);

    if(found != index_.end()){
      current = found->second;
    }

    if(i == 0){
      result = current;
    }else if(type == 0){
      result = setIntersection(result, current);
    }else{
      result = setUnion(result,current);
    }
  }

  for(set<Product*>::iterator it = result.begin(); it != result.end(); ++it){
    hits.push_back(*it);
  }
  return hits;
}

void MyDataStore::dump(ostream& ofile)
{
  ofile<<"<products>"<< endl;
  for(set<Product*>::iterator it = products_.begin(); it != products_.end(); ++it){
    (*it)->dump(ofile);
  }
  ofile<<"</products>"<<endl;

  ofile<< "<users>"<<endl;
  for(map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it){
    it->second->dump(ofile);
  }
  ofile << "</users>" <<endl;
}

bool MyDataStore::hasUser(const string& username)const
{
  return users_.find(convToLower(username)) !=users_.end();
}

void MyDataStore::addToCart(const string& username, Product* p)
{
  carts_[convToLower(username)].push_back(p);
}

void MyDataStore::viewCart(const string& username)
{
  map<string, vector<Product*> >::iterator found = carts_.find(convToLower(username));

  if(found == carts_.end()){
    return;
  }

  vector<Product*>& cart = found->second;

  for(size_t i = 0; i<cart.size(); i++){
    cout<<"Item "<< (i+1)<<endl;
    cout<<cart[i]->displayString()<<endl;
    cout<<endl;
  }

}

void MyDataStore::buyCart(const string& username){
  string key = convToLower(username);
  map<string, User*>::iterator uit = users_.find(key);
  map<string, vector<Product*> >::iterator cit = carts_.find(key);

  if(uit == users_.end() || cit == carts_.end()){
    return;
  }

  User* user = uit->second;
  vector<Product*>& cart= cit->second;
  vector<Product*> remaining;
  for(size_t i = 0; i<cart.size(); i++){
    Product* p = cart[i];
    if(p->getQty()>0 && user->getBalance() >= p->getPrice()){
      p->subtractQty(1);
      user->deductAmount(p->getPrice());
    }
    else{
      remaining.push_back(p);
    }
  }
  cart=remaining;


}

void MyDataStore:: addProduct(Product* p)
{
  products_.insert(p);
  set<string>kw = p->keywords();

  for(set<string>::iterator it = kw.begin(); it != kw.end(); ++it){
    index_[*it].insert(p);
  }
}