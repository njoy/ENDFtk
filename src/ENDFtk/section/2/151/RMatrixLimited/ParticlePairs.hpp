/**
 *  @class
 *  @brief Particle pair information used in the resonance reconstruction
 *
 *  The ParticlePairs class stores the information about the various particle
 *  pairs that make up the reaction channels included in the resonance
 *  parameters.
 *
 *  See ENDF102, section 2.2.1.6 for more information.
 */
class ENDFTK_PYTHON_EXPORT ParticlePairs : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/2/151/RMatrixLimited/ParticlePairs/src/generateList.hpp"
  #include "ENDFtk/section/2/151/RMatrixLimited/ParticlePairs/src/verifySize.hpp"

  auto column( unsigned int i ) const {

    using namespace njoy::tools;
    return ListRecord::list()
             | std20::views::drop( i )
             | std23::views::stride( 12 );
  }

public:

  /* constructor */
  #include "ENDFtk/section/2/151/RMatrixLimited/ParticlePairs/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the number of particle pairs
   */
  unsigned int NPP() const { return ListRecord::NPL() / 12; }

  /**
   *  @brief Return the number of particle pairs
   */
  unsigned int numberParticlePairs() const { return this->NPP(); }

  /**
   *  @brief Return the mass of the first particle in each particle pair
   */
  auto MA() const { return ParticlePairs::column( 0 ); }

  /**
   *  @brief Return the mass of the first particle in each particle pair
   */
  auto massParticleA() const { return this->MA(); }

  /**
   *  @brief Return the mass of the second particle in each particle pair
   */
  auto MB() const { return ParticlePairs::column( 1 ); }

  /**
   *  @brief Return the mass of the second particle in each particle pair
   */
  auto massParticleB() const { return this->MB(); }

  /**
   *  @brief Return the charge of the first particle in each particle pair
   */
  auto ZA() const { return ParticlePairs::column( 2 ); }

  /**
   *  @brief Return the charge of the first particle in each particle pair
   */
  auto chargeParticleA() const { return this->ZA(); }

  /**
   *  @brief Return the charge of the second particle in each particle pair
   */
  auto ZB() const { return ParticlePairs::column( 3 ); }

  /**
   *  @brief Return the charge of the second particle in each particle pair
   */
  auto chargeParticleB() const { return this->ZB(); }

  /**
   *  @brief Return the spin of the first particle in each particle pair
   */
  auto IA() const { return ParticlePairs::column( 4 ); }

  /**
   *  @brief Return the spin of the first particle in each particle pair
   */
  auto spinParticleA() const { return this->IA(); }

  /**
   *  @brief Return the spin of the second particle in each particle pair
   */
  auto IB() const { return ParticlePairs::column( 5 ); }

  /**
   *  @brief Return the spin of the second particle in each particle pair
   */
  auto spinParticleB() const { return this->IB(); }

  /**
   *  @brief Return the parity of the first particle in each particle pair
   */
  auto PA() const { return ParticlePairs::column( 10 ); }

  /**
   *  @brief Return the parity of the first particle in each particle pair
   */
  auto parityParticleA() const { return this->PA(); }

  /**
   *  @brief Return the parity of the second particle in each particle pair
   */
  auto PB() const { return ParticlePairs::column( 11 ); }

  /**
   *  @brief Return the parity of the second particle in each particle pair
   */
  auto parityParticleB() const { return this->PB(); }

  /**
   *  @brief Return the Q value for each particle pair
   */
  auto Q() const { return ParticlePairs::column( 6 ); }

  /**
   *  @brief Return the penetrability flag for each particle pair
   */
  auto PNT() const {

    using namespace njoy::tools;
    return ParticlePairs::column( 7 )
             | std20::views::transform( [] ( auto pnt )
                                                   { return int( pnt ); } ); }

  /**
   *  @brief Return the penetrability flag for each particle pair
   */
  auto penetrabilityFlag() const { return this->PNT(); }

  /**
   *  @brief Return the shift factor flag for each particle pair
   */
  auto SHF() const {

    using namespace njoy::tools;
    return ParticlePairs::column( 8 )
             | std20::views::transform( [] ( auto shf )
                                                   { return int( shf ); } ); }

  /**
   *  @brief Return the shift factor flag for each particle pair
   */
  auto shiftFactorFlag() const { return this->SHF(); }

  /**
   *  @brief Return the MT value associated to each particle pair
   */
  auto MT() const {

    using namespace njoy::tools;
    return ParticlePairs::column( 9 )
             | std20::views::transform( [] ( auto mt )
                                                   { return int( mt ); } ); }

  using ListRecord::NC;
  using ListRecord::print;
};
