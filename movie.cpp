#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const string category, const string name, double price, int qty,
            const string genre, const string rating)
      : Product(category, name, price, qty), genre_(genre), rating_(rating)
{

}

std::set<std::string>Movie::keywords()const
{
  set<string>result = parseStringToWords(name_);
  result.insert(convToLower(genre_));
  return result;
}

std::string Movie::displayString()const
{
  ostringstream oss;
  oss<< name_ << "\n"
     <<"Genre: " << genre_ << " Rating: "<< rating_ << "\n"
     << fixed << setprecision(2)<< price_<< " "<< qty_<< " left.";
  return oss.str();
}

void Movie::dump(std:: ostream& os) const
{
  Product::dump(os);
  os<< genre_ << "\n"<< rating_<<endl;
}

Movie :: ~Movie()
{
  
}