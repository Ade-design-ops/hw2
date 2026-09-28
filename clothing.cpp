#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"
using namespace std;

Clothing::Clothing(const string category, const string name, double price, int qty,
                  const string size, const string brand)
        :Product(category,name, price,qty), size_(size), brand_(brand)
{

}

Clothing:: ~Clothing()
{

}

std::set<string>Clothing::keywords()const
{
  set<string>nameWords = parseStringToWords(name_);
  set<string>brandWords = parseStringToWords(brand_);
  return setUnion(nameWords, brandWords);

}

std::string Clothing::displayString()const
{
  ostringstream oss;
  oss << fixed<< setprecision(2);
  oss<< name_ << "\n";
  oss<< "Size: "<< size_ << " Brand: "<< brand_ << "\n";
  oss<< price_ << " "<< qty_ << " left. ";
  return oss.str();
}

void Clothing :: dump(std::ostream& os)const
{
  Product::dump(os);
  os<<size_<<"\n"<< brand_<<endl;
}