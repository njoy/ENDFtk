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
class ParticlePairs : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/resonanceParameters/resolved/RMatrixLimited/ParticlePairs/src/generateList.hpp"
  #include "ENDFtk/resonanceParameters/resolved/RMatrixLimited/ParticlePairs/src/verifySize.hpp"

public:
  /* constructor */
  #include "ENDFtk/resonanceParameters/resolved/RMatrixLimited/ParticlePairs/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the number of particle pairs
   */
  auto NPP() const { return ListRecord::NPL() / 12; }

  /**
   *  @brief Return the number of particle pairs
   */
  auto numberParticlePairs() const { return this->NPP(); }

  /**
   *  @brief Return the mass of the first particle in each particle pair
   */
  auto MA() const { return ListRecord::list() | ranges::view::stride( 12 ); }

  /**
   *  @brief Return the mass of the first particle in each particle pair
   */
  auto massParticleA() const { return this->MA(); }

  /**
   *  @brief Return the mass of the second particle in each particle pair
   */
  auto MB() const {
    return ListRecord::list()
             | ranges::view::drop_exactly( 1 )
             | ranges::view::stride( 12 ); }

  /**
   *  @brief Return the mass of the second particle in each particle pair
   */
  auto massParticleB() const { return this->MB(); }

  /**
   *  @brief Return the charge of the first particle in each particle pair
   */
  auto ZA() const {
    return ListRecord::list()
             | ranges::view::drop_exactly( 2 )
             | ranges::view::stride( 12 ); }

  /**
   *  @brief Return the charge of the first particle in each particle pair
   */
  auto chargeParticleA() const { return this->ZA(); }

  /**
   *  @brief Return the charge of the second particle in each particle pair
   */
  auto ZB() const {
    return ListRecord::list()
             | ranges::view::drop_exactly( 3 )
             | ranges::view::stride( 12 ); }

  /**
   *  @brief Return the charge of the second particle in each particle pair
   */
  auto chargeParticleB() const { return this->ZB(); }

  /**
   *  @brief Return the spin of the first particle in each particle pair
   */
  auto IA() const {
    return ListRecord::list()
             | ranges::view::drop_exactly( 4 )
             | ranges::view::stride( 12 ); }

  /**
   *  @brief Return the spin of the first particle in each particle pair
   */
  auto spinParticleA() const { return this->IA(); }

  /**
   *  @brief Return the spin of the second particle in each particle pair
   */
  auto IB() const {
    return ListRecord::list()
             | ranges::view::drop_exactly( 5 )
             | ranges::view::stride( 12 ); }

  /**
   *  @brief Return the spin of the second particle in each particle pair
   */
  auto spinParticleB() const { return this->IB(); }

  /**
   *  @brief Return the parity of the first particle in each particle pair
   */
  auto PA() const {
    return ListRecord::list()
             | ranges::view::drop_exactly( 10 )
             | ranges::view::stride( 12 ); }

  /**
   *  @brief Return the parity of the first particle in each particle pair
   */
  auto parityParticleA() const { return this->PA(); }

  /**
   *  @brief Return the parity of the second particle in each particle pair
   */
  auto PB() const {
    return ListRecord::list()
             | ranges::view::drop_exactly( 11 )
             | ranges::view::stride( 12 ); }

  /**
   *  @brief Return the parity of the second particle in each particle pair
   */
  auto parityParticleB() const { return this->PB(); }

  /**
   *  @brief Return the Q value for each particle pair
   */
  auto Q() const {
    return ListRecord::list()
             | ranges::view::drop_exactly( 6 )
             | ranges::view::stride( 12 ); }

  /**
   *  @brief Return the penetrability flag for each particle pair
   */
  auto PNT() const {
    return ListRecord::list()
             | ranges::view::drop_exactly( 7 )
             | ranges::view::stride( 12 )
             | ranges::view::transform( [] ( auto pnt )
                                           { return int( pnt ); } ); }

  /**
   *  @brief Return the penetrability flag for each particle pair
   */
  auto penetrabilityFlag() const { return this->PNT(); }

  /**
   *  @brief Return the shift factor flag for each particle pair
   */
  auto SHF() const {
    return ListRecord::list()
             | ranges::view::drop_exactly( 8 )
             | ranges::view::stride( 12 )
             | ranges::view::transform( [] ( auto shf )
                                           { return int( shf ); } ); }

  /**
   *  @brief Return the shift factor flag for each particle pair
   */
  auto shiftFactorFlag() const { return this->SHF(); }

  /**
   *  @brief Return the MT value associated to each particle pair
   */
  auto MT() const {
    return ListRecord::list()
             | ranges::view::drop_exactly( 9 )
             | ranges::view::stride( 12 )
             | ranges::view::transform( [] ( auto mt )
                                           { return int( mt ); } ); }

  using ListRecord::NC;
  using ListRecord::print;
};
