/**
 *  @class
 *  @brief Decay modes and branching ratio information
 *
 *  The DecayModes class is used to store the spin, parity and decay modes
 *  from MF8/MT457.
 *
 *  See ENDF102, section 8.4 for more information.
 */
class ENDFTK_PYTHON_EXPORT DecayModes : protected ListRecord {

  /* members */

  /* auxiliary functions */
  #include "ENDFtk/section/8/457/DecayModes/src/readListRecord.hpp"
  #include "ENDFtk/section/8/457/DecayModes/src/verifyNDK.hpp"
  #include "ENDFtk/section/8/457/DecayModes/src/generateList.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/8/457/DecayModes/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the spin of the target
   */
  double SPI() const { return ListRecord::C1(); }

  /**
   *  @brief Return the spin of the target
   */
  double spin() const { return this->SPI(); }

  /**
   *  @brief Return the parity of the target
   */
  double PAR() const { return ListRecord::C2(); }

  /**
   *  @brief Return the parity of the target
   */
  double parity() const { return this->PAR(); }

  /**
   *  @brief Return the number of decay modes NDK
   */
  int NDK() const { return ListRecord::N2(); }

  /**
   *  @brief Return the number of decay modes NDK
   */
  int numberDecayModes() const { return this->NDK(); }

  /**
   *  @brief Return the decay mode information
   */
  auto decayModes() const {

    using namespace njoy::tools;
    return ListRecord::list()
              | std23::views::chunk( 6 )
              | std20::views::transform(
                  [] ( const auto& range )
                     { return DecayMode( range[0], range[1], range[2],
                                         range[3], range[4], range[5] ); } );
  }

  using ListRecord::NC;
  using ListRecord::print;
};
