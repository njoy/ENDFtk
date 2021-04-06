/**
 *  @class
 *  @brief Convenience interface for fission yield data of a nuclide
 *
 *  See ENDF102, section 8.3 for more information.
 */
template < typename Range >
class FissionProduct {

  /* fields */
  Range chunk;

public:

  /* constructor */
  FissionProduct( Range&& chunk ) : chunk( std::move( chunk ) ) {}

  /**
   *  @brief Return the fission product ZA identifier
   */
  unsigned int ZAFP() const { return this->chunk[0]; }

  /**
   *  @brief Return the fission product ZA identifier
   */
  unsigned int fissionProductIdentifier() const { return this->ZAFP(); }

  /**
   *  @brief Return the fission product isomeric state
   */
  unsigned int FPS() const { return this->chunk[1]; }

  /**
   *  @brief Return the fission product isomeric state
   */
  unsigned int isomericState() const { return this->FPS(); }

  /**
   *  @brief Return the fission yield value and uncertainty
   */
  std::array< double, 2 > Y() const {

    return {{ this->chunk[2], this->chunk[3] }};
  }

  /**
   *  @brief Return the fission yield value and uncertainty
   */
  std::array< double, 2 > fissionYield() const { return this->Y(); }
};
