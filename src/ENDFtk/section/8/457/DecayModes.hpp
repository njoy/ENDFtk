/**
 *  @class
 *  @brief Decay modes and branching ratio information
 *
 *  The DecayModes class is used to store the spin, parity and decay modes
 *  from MF8/MT457.
 *
 *  See ENDF102, section 8.4 for more information.
 */
class DecayModes : protected ListRecord {

  /* members */

  /* auxiliary functions */
  #include "ENDFtk/section/8/457/DecayModes/src/verifyNDK.hpp"
  #include "ENDFtk/section/8/457/DecayModes/src/generateList.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/8/457/DecayModes/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the spin of the target
   */
  auto spin() const { return ListRecord::C1(); }

  /**
   *  @brief Return the parity of the target
   */
  auto parity() const { return ListRecord::C2(); }

  /**
   *  @brief Return the number of decay modes NDK
   */
  int NDK() const { return ListRecord::N2(); }

  /**
   *  @brief Return the decay mode information
   */
  auto decayModes() const {
    return ranges::view::zip_with(
               [] ( const double rtyp, const double rfs, const double q, 
                    const double dq, const double br, const double dbr )
                  { return DecayMode( rtyp, rfs, q, dq, br, dbr ); },
               ListRecord::list() | ranges::view::stride( 6 ),
               ListRecord::list() | ranges::view::drop_exactly( 1 )
                                  | ranges::view::stride( 6 ),
               ListRecord::list() | ranges::view::drop_exactly( 2 )
                                  | ranges::view::stride( 6 ),
               ListRecord::list() | ranges::view::drop_exactly( 3 )
                                  | ranges::view::stride( 6 ),
               ListRecord::list() | ranges::view::drop_exactly( 4 )
                                  | ranges::view::stride( 6 ),
               ListRecord::list() | ranges::view::drop_exactly( 5 )
                                  | ranges::view::stride( 6 ) );
  }

  using ListRecord::NC;
  using ListRecord::print;
};
