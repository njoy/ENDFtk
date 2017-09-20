class ReichMoore : public BreitWigner {
protected:
  int lad;
  int nlsc;

#include "ENDFtk/resonanceParameters/resolved/ReichMoore/src/validate.hpp"

public:
#include "ENDFtk/resonanceParameters/resolved/ReichMoore/src/ctor.hpp"
#include "ENDFtk/resonanceParameters/resolved/ReichMoore/LState.hpp"
  
  int LAD() const { return this->lad; }
  int NLSC() const { return this->nlsc; }

  auto LStates() const{
    return this->LISTS() | 
      ranges::view::transform(
        []( const auto& list ){ return LState( list ); } 
      );
  }
};
