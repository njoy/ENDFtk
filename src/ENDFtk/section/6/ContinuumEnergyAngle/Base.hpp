class Base : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/6/ContinuumEnergyAngle/Base/src/verifySize.hpp"
    
public:
  /* constructor */
  #include "ENDFtk/section/6/ContinuumEnergyAngle/Base/src/ctor.hpp"

  /* get methods */
  double energy() const { return ListRecord::C2(); }
  long ND() const { return ListRecord::L1(); }
  long NA() const { return ListRecord::L2(); }
  long NW() const { return ListRecord::NPL(); }
  long NEP() const { return ListRecord::N2(); }

  auto energies() const { return ListRecord::list()
                            | ranges::view::stride( 2 + this->NA() ); }
  auto totalEmissionProbabilities() const {
    return ranges::view::drop_exactly( ListRecord::list(), 1 )
             | ranges::view::stride( 2 + this->NA() );
  }
  auto data() const {
    return ListRecord::list() | ranges::view::chunk( 2 + this->NA() )
                              | ranges::view::transform( ranges::view::tail ); }
  using ListRecord::list;

  using ListRecord::NC;
  using ListRecord::print;
};
