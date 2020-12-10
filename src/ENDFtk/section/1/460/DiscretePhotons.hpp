class Discrete {

  /* fields */
  std::vector< DiscretePhoton > photons_;

public:
  /* constructor */
  Discrete( std::vector< DiscretePhoton >&& photons ) : photons_( photons ) {}

  /* get methods */
  static constexpr int LO() { return 1; }
  int NG() const { return this->photons_.size(); }

  auto photons() const { 
    return ranges::make_iterator_range( this->photons_.begin(),
                                        this->photons_.end() );
  }

#include "ENDFtk/section/1/460/Discrete/src/NC.hpp"
#include "ENDFtk/section/1/460/Discrete/src/print.hpp"
};

