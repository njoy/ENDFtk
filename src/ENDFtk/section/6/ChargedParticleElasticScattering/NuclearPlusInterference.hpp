/**
 *  @class
 *  @brief Charged particle elastic scattering given as nuclear plus
 *         interference distribution
 *
 *  See ENDF102, section 6.2.6 for more information.
 */
class NuclearPlusInterference : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/NuclearPlusInterference/src/verifyLTP.hpp"
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/NuclearPlusInterference/src/verifySize.hpp"
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/NuclearPlusInterference/src/generateList.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/NuclearPlusInterference/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the incident energy
   */
  double E() const { return ListRecord::C2(); }

  /**
   *  @brief Return the incident energy
   */
  double incidentEnergy() const { return this->E(); }

  /**
   *  @brief Return the representation type
   */
  int LTP() const { return ListRecord::L1(); }

  /**
   *  @brief Return the representation type
   */
  int representation() const { return this->LTP(); }

  /**
   *  @brief Return the number of values in this component
   */
  long NW() const { return ListRecord::NPL(); }

  /**
   *  @brief Return the Legendre order or number of cosine values
   */
  long NL() const { return ListRecord::N2(); }

  /**
   *  @brief Return the cosine values
   */
  StrideRange< AllRange< double > > MU() const {

    return ListRecord::list() | ranges::views::stride( 2 );
  }

  /**
   *  @brief Return the cosine values
   */
  StrideRange< AllRange< double > > cosines() const {

    return this->MU();
  }

  /**
   *  @brief Return the probabilities
   */
  StrideRange< DropRange< AllRange< double > > > PNI() const {

    return ranges::views::drop_exactly( ListRecord::list(), 1 )
             | ranges::views::stride( 2 );
  }

  /**
   *  @brief Return the probabilities
   */
  StrideRange< DropRange< AllRange< double > > > probabilities() const {

    return this->PNI();
  }

  using ListRecord::NC;
  using ListRecord::print;
};
