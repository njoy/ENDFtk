class ReichMoore : public BreitWigner {
protected:
  int lad;
  int nlsc;

#include "ENDFtk/resonanceParameters/resolved/ReichMoore/src/validate.hpp"

public:
#include "ENDFtk/resonanceParameters/resolved/ReichMoore/src/ctor.hpp"
#include "ENDFtk/resonanceParameters/resolved/ReichMoore/Lvalue.hpp"
  
  int LAD() const { return this->lad; }
  int NLSC() const { return this->nlsc; }

  static constexpr int LRF() { return 3; }

  auto lValues() const{
    return this->LISTS() | 
      ranges::view::transform(
        []( const auto& list ){ return Lvalue( list ); } 
      );
  }
  
  #include "ENDFtk/resonanceParameters/resolved/ReichMoore/src/print.hpp"
};
