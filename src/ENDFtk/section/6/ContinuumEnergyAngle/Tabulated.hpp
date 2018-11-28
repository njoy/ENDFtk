class Tabulated : protected Base {

  /* fields */
  int lang_;

  /* auxiliary functions */
  #include "ENDFtk/section/6/ContinuumEnergyAngle/Tabulated/src/generateList.hpp"
    
public:
  /* constructor */
  #include "ENDFtk/section/6/ContinuumEnergyAngle/Tabulated/src/ctor.hpp"

  /* get methods */
  int LANG() const { return this->lang_; }
  using Base::energy;
  using Base::ND;
  using Base::NA;
  using Base::NW;
  using Base::NEP;

  using Base::energies;
  using Base::totalEmissionProbabilities;
  auto cosines() const {
    return Base::list()
             | ranges::view::chunk( 2 + this->NA() )
             | ranges::view::transform( ranges::view::drop( 2 )
                                          | ranges::view::stride( 2 ) ); }
  auto probabilities() const {
    return Base::list()
             | ranges::view::chunk( 2 + this->NA() )
             | ranges::view::transform( ranges::view::drop( 3 )
                                          | ranges::view::stride( 2 ) ); }

  using Base::NC;
  using Base::print;
};