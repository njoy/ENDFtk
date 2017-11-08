class DiscreteTwoBodyScattering {
public:

#include "ENDFtk/section/6/DiscreteTwoBodyScattering/LegendreCoefficients.hpp"
#include "ENDFtk/section/6/DiscreteTwoBodyScattering/Tabulated.hpp"
#include "ENDFtk/section/6/DiscreteTwoBodyScattering/SubSection.hpp"

private:
  InterpolationSequenceRecord< SubSection > data_;

public:
  /* constructor */
#include "ENDFtk/section/6/DiscreteTwoBodyScattering/src/ctor.hpp"

  /* get methods */
  long NR() const { return this->data_.tab2().NR(); }
  long NE() const { return this->data_.tab2().NZ(); }

  auto energies() const { return this->data_.records(); }

  auto interpolants() const { return this->data_.tab2().interpolants(); }
  auto boundaries() const { return this->data_.tab2().boundaries(); }

  long NC() const { return this->data_.NC(); }

#include "ENDFtk/section/6/DiscreteTwoBodyScattering/src/print.hpp"
};
