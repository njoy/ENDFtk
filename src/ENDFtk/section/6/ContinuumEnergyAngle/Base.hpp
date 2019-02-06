class Base : protected ListRecord {

public:

  /* get methods */
  double energy() const { return ListRecord::C2(); }
  long ND() const { return ListRecord::L1(); }
  long numberDiscreteEnergies() const { return this->ND(); }
  long NA() const { return ListRecord::L2(); }
  long numberAngularParameters() const { return this->NA(); }
  long NW() const { return ListRecord::NPL(); }
  long NEP() const { return ListRecord::N2(); }
  long numberSecondaryEnergies() const { return this->NEP(); }

  auto energies() const { return ListRecord::list()
                            | ranges::view::stride( 2 + this->NA() ); }
  auto totalEmissionProbabilities() const {
    return ranges::view::drop_exactly( ListRecord::list(), 1 )
             | ranges::view::stride( 2 + this->NA() );
  }
  auto data() const {
    return ListRecord::list() | ranges::view::chunk( 2 + this->NA() )
                              | ranges::view::transform( ranges::view::tail ); }

private:

  /* auxiliary functions */
  #include "ENDFtk/section/6/ContinuumEnergyAngle/Base/src/verifySize.hpp"

public:
  /* constructor */
  #include "ENDFtk/section/6/ContinuumEnergyAngle/Base/src/ctor.hpp"

  using ListRecord::NC;
  using ListRecord::print;
};
