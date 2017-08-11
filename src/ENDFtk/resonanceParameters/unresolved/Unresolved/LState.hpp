class LState {
protected:
  std::vector< LIST > lists;
  double awri;
  int l;

#include "ENDFtk/resonanceParameters/unresolved/Unresolved/LState/src/ctor.hpp"
#include "ENDFtk/resonanceParameters/unresolved/Unresolved/LState/src/readLists.hpp"

public:
  double AWRI() const { return this->awri; }
  int L() const { return this->l; }

  auto LISTs() const {
    return ranges::make_iterator_range( this->lists.begin(), this->lists.end() );
  }
};
