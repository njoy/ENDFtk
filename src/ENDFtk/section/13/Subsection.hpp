class Subsection : protected TabulationRecord {
  friend Type<13>;

public:
  #include "ENDFtk/section/13/Subsection/src/ctor.hpp"

  double EG() const { return TabulationRecord::C1(); }
  double EK() const { return TabulationRecord::C2(); }
  int LP() const { return TabulationRecord::L1(); }
  int LF() const { return TabulationRecord::L2(); }
  auto energies() const { return TabulationRecord::x(); }
  auto crossSections() const { return TabulationRecord::y(); }

  using TabulationRecord::NC;

  template< typename OutputIterator >
  auto print( OutputIterator& it, int MAT, int MT ) const {
    return TabulationRecord::print( it, MAT, MF(), MT );
  }
};
