#include <variant>

template<>
class Type< 1, 452 > : protected Base {
protected:

  /* fields */
  int lnu_;
  std::variant< ListRecord, TabulationRecord > data_;

  /* auxiliary functions */
#include "ENDFtk/section/1/452/src/readData.hpp"

  public:

  /* constructor */
#include "ENDFtk/section/1/452/src/ctor.hpp"

  /* set methods */

  /* get methods */
  static constexpr int MT() { return 452; }

  int LNU() const { return this->lnu_; }

  auto coefficients() const { return std::experimental::get< 0 >( this->data_ ).list(); }

//  const ListRecord& polynomial() const { return this->polynomial_; }
//  const TabulationRecord& tabulated() const { return this->tabulated_; }

  using Base::ZA;
  using Base::AWR;
  using Base::atomicWeightRatio;
};

