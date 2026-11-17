#ifndef NJOY_ENDFTK_SECTION_REACTIONBLOCK
#define NJOY_ENDFTK_SECTION_REACTIONBLOCK

// system includes
#include <vector>

// other includes
#include "tools/std20/views.hpp"
#include "ENDFtk/macros.hpp"
#include "ENDFtk/section/CovariancePairs.hpp"
#include "ENDFtk/section/SquareMatrix.hpp"
#include "ENDFtk/section/RectangularMatrix.hpp"
#include "ENDFtk/section/ExplicitCovariance.hpp"
#include "ENDFtk/section/DerivedRedundant.hpp"
#include "ENDFtk/section/DerivedRatioToStandard.hpp"
#include "ENDFtk/section/DerivedCovariance.hpp"
#include "ENDFtk/ControlRecord.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

/**
 *  @class
 *  @brief A Reaction block (subsection) given in an MF33 covariance section
 *
 *  The ReactionBlock class is used to represent a subsection in
 *  an ENDF MF33 section, which represents a covariance of the reaction
 *  cross section (MT) relative to another reaction (MF1/MT1).
 *
 *  See ENDF102, section 33.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT ReactionBlock {

  /* fields */

  int xmf1_;
  int xlfs1_;
  int mat1_;
  int mt1_;
  std::vector< DerivedCovariance > nc_;
  std::vector< ExplicitCovariance > ni_;

  /* auxiliary functions */

  template< typename Iterator >
  static std::vector< DerivedCovariance >
  readNC( Iterator& begin,
                    const Iterator& end,
                    long& lineNumber,
                    int MAT, int MF, int MT,
                    int numberNC ) {

    std::vector< DerivedCovariance > result;

    for (int i=0; i<numberNC; ++i) {

      ControlRecord cont( begin, end, lineNumber, MAT, MF, MT );

      switch ( cont.L2() ) {

        // DerivedRedundant
        case 0:
          result.push_back(
            DerivedRedundant( cont.L2(),
                              begin, end, lineNumber, MAT, MF, MT ) );
          break;

        // DerivedRatioToStandard
        case 1:
        case 2:
        case 3:
          result.push_back(
            DerivedRatioToStandard( cont.L2(),
                                    begin, end, lineNumber, MAT, MF, MT ) );
          break;

        // Error
        default:
          Log::error( "Encountered illegal LTY value" );
          Log::info( "LTY can only be 0,1,2,3" );
          Log::info( "LTY value: {}", cont.L2() );
          Log::info( "Line number: {}", lineNumber - 1 );
          throw std::exception();

      }

    }

    return result;

  }

  /* constructor */

  template< typename Iterator >
  ReactionBlock( ControlRecord&& cont,
                 std::vector< DerivedCovariance >&& nc,
                 Iterator& begin,
                 const Iterator& end,
                 long& lineNumber,
                 int MAT, int MF, int MT ) :
    ReactionBlock( static_cast< int >( std::round( cont.C1() ) ),
                   static_cast< int >( std::round( cont.C2() ) ),
                   cont.L1(), cont.L2(), std::move( nc ),
                   readSequence( begin, end, lineNumber, MAT, MF, MT, cont.N2() ) ) {}

  template< typename Iterator >
  ReactionBlock( ControlRecord&& cont,
                 Iterator& begin,
                 const Iterator& end,
                 long& lineNumber,
                 int MAT, int MF, int MT ) :
    ReactionBlock( std::move( cont ),
                   readNC( begin, end, lineNumber,
                           MAT, MF, MT, cont.N1() ),
                   begin, end, lineNumber, MAT, MF, MT ) {}

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] xmf1          the file number of the second cross section
   *  @param[in] xlfs1         the final excited state of the second cross section
   *  @param[in] mat1          the material number of the second cross section
   *  @param[in] mt1           the section number of the second cross section
   *  @param[in] nc            the NC-type (derived) subsubsections
   *  @param[in] ni            the NI-type (explicit) subsubsections
   */
  ReactionBlock( int xmf1, int xlfs1, int mat1, int mt1,
                 std::vector< DerivedCovariance >&& nc,
                 std::vector< ExplicitCovariance >&& ni ) :
    xmf1_( xmf1 ), xlfs1_( xlfs1 ),
    mat1_( mat1 ), mt1_( mt1 ),
    nc_( std::move( nc ) ),
    ni_( std::move( ni ) ) {}

  /**
   *  @brief Constructor
   *
   *  NC Only.
   *
   *  @param[in] xmf1          the file number of the second cross section
   *  @param[in] xlfs1         the final excited state of the second cross section
   *  @param[in] mat1          the material number of the second cross section
   *  @param[in] mt1           the section number of the second cross section
   *  @param[in] nc            the NC-type (derived) subsubsections
   */
  ReactionBlock( int xmf1, int xlfs1, int mat1, int mt1,
                 std::vector< DerivedCovariance >&& nc ) :
    xmf1_( xmf1 ), xlfs1_( xlfs1 ), mat1_( mat1 ), mt1_( mt1 ),
    nc_( std::move( nc ) ) {}

  /**
   *  @brief Constructor
   *
   *  NI Only.
   *
   *  @param[in] xmf1          the file number of the second cross section
   *  @param[in] xlfs1         the final excited state of the second cross section
   *  @param[in] mat1          the material number of the second cross section
   *  @param[in] mt1           the section number of the second cross section
   *  @param[in] ni            the NI-type (explicit) subsubsections
   *
   */
  ReactionBlock( int xmf1, int xlfs1, int mat1, int mt1,
                 std::vector< ExplicitCovariance >&& ni ) :
    xmf1_( xmf1 ), xlfs1_( xlfs1 ), mat1_( mat1 ), mt1_( mt1 ),
    ni_( std::move( ni ) ) {}

  /**
   *  @brief Constructor (from a buffer)
   *
   *  @tparam Iterator        a buffer iterator
   *
   *  @param[in] it           the current position in the buffer
   *  @param[in] end          the end of the buffer
   *  @param[in] lineNumber   the current line number
   *  @param[in] MAT          the expected MAT number
   *  @param[in] MF           the expected MF number
   *  @param[in] MT           the expected MT number
   */
  template< typename Iterator >
  ReactionBlock( Iterator& it, const Iterator& end, long& lineNumber,
                 int MAT, int MF, int MT )
  try :
    ReactionBlock(
      ControlRecord( it, end, lineNumber, MAT, MF, MT ),
      it, end, lineNumber, MAT, MF, MT ) {

  } catch( std::exception& e ) {

    Log::info( "Trouble while creating a covariance ReactionBlock",
               MT, MAT );
    throw e;
  }

  /* methods */

  /**
   *  @brief Return the file number for the second cross section
   */
  int XMF1() const { return this->xmf1_; }

  /**
   *  @brief Return the file number for the second cross section
   */
  int secondFileNumber() const { return this->XMF1(); }

  /**
   *  @brief Return the final excited state for the second cross section
   */
  int XLFS1() const { return this->xlfs1_; }

  /**
   *  @brief Return the final excited state for the second cross section
   */
  int secondFinalExcitedState() const { return this->XLFS1(); }

  /**
   *  @brief Return the material number for the second cross section
   */
  int MAT1() const { return this->mat1_; }

  /**
   *  @brief Return the material number for the second cross section
   */
  int secondMaterialNumber() const { return this->MAT1(); }

  /**
   *  @brief Return the section number for the second cross section
   */
  int MT1() const { return this->mt1_; }

  /**
   *  @brief Return the section number for the second cross section
   */
  int secondSectionNumber() const { return this->MT1(); }

  /**
   *  @brief Return the number of NC-type subsubsections
   */
  int NK() const { return this->nc_.size(); }

  /**
   *  @brief Return the number of NC-type subsubsections
   */
  int numberDerived() const { return this->NK(); }

  /**
   *  @brief Return the number of NI-type subsubsections
   */
  int NI() const { return this->ni_.size(); }

  /**
   *  @brief Return the number of NI-type subsubsections
   */
  int numberExplicit() const { return this->NI(); }

  /**
   *  @brief Return the NC-type subsubsections
   */
  auto derivedCovariances() const {

    using namespace njoy::tools;
    return std20::views::all( this->nc_ );
  }

  /**
   *  @brief Return the NI-type subsubsections
   */
  auto explicitCovariances() const {

    using namespace njoy::tools;
    return std20::views::all( this->ni_ );
  }

  /**
   *  @brief Return the number of lines in this MF33 subsection
   */
  long NC() const {

    long result = 1;

    // NC subsubsections
    for ( const auto& nc : this->nc_ ) {
      std::visit( [&] ( const auto& v ) -> void
                      { result += v.NC(); },
                  nc );
    }

    // NI subsubsections
    for ( const auto& ni : this->ni_ ) {
      std::visit( [&] ( const auto& v ) -> void
                      { result += v.NC(); },
                  ni );
    }

    return result;

  }

  /**
   *  @brief Print this MF33 component
   *
   *  @tparam OutputIterator   an output iterator
   *
   *  @param[in] it            the current position in the output
   *  @param[in] MAT           the MAT number
   *  @param[in] MF            the MF number
   *  @param[in] MT            the MT number
   */
  template< typename OutputIterator >
  void print( OutputIterator& it, int MAT, int MF, int MT ) const {

    // metadata
    ControlRecord( this->XMF1(), this->XLFS1(), this->MAT1(), this->MT1(),
                   this->NK(), this->NI() ).print( it, MAT, MF, MT );

    // NC subsubsections
    for ( auto& nc : this->nc_ ) {
      std::visit( [&] ( const auto& v ) -> void
                      { v.print( it, MAT, MF, MT ); },
                  nc );
    }

    // NI subsubsections
    for ( auto& ni : this->ni_ ) {
      std::visit( [&] ( const auto& v ) -> void
                      { v.print( it, MAT, MF, MT ); },
                  ni );
    }

  }
};

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
