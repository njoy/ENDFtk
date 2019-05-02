template < typename Derived >
class BaseWithoutMT {

  /* fields */
  int ZA_;
  double atomicWeightRatio_;

protected:
  
  /* constructor */
  #include "ENDFtk/section/BaseWithoutMT/src/ctor.hpp"

public:

  /* get methods */
  constexpr int MT() const {
      
      return static_cast< const Derived* >( this )->sectionNumber();
  }
  constexpr int ZA() const { return this->ZA_; }
  constexpr double AWR() const { return this->atomicWeightRatio_; }
  constexpr double atomicWeightRatio() const { return this->AWR(); }

  #include "ENDFtk/section/BaseWithoutMT/src/readSEND.hpp"
};
