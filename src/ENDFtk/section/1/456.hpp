#ifndef NJOY_ENDFTK_SECTION_1_456
#define NJOY_ENDFTK_SECTION_1_456

// system includes
#include <variant>

// other includes
#include "ENDFtk/macros.hpp"
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/section.hpp"

#include "ENDFtk/section/1/PolynomialMultiplicity.hpp"
#include "ENDFtk/section/1/TabulatedMultiplicity.hpp"
#include "ENDFtk/section/1/readMultiplicity.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  /**
   *  @class
   *  @brief MF1 MT456 - the number of prompt fission neutrons
   *
   *  This section is essentially identical to MF1 MT452 so we could have
   *  inherited from that section but the reference_wrapper in the
   *  ENDFtk.MF1.File python bindings does not seem to handle it.
   *
   *  See ENDF102, section 1.4 for more information.
   */
  template<>
  class ENDFTK_PYTHON_EXPORT Type< 1, 456 > : 
    protected BaseWithoutMT< Type< 1, 456 > > {

    friend BaseWithoutMT< Type< 1, 456 > >;

  public:

    using Multiplicity = std::variant< PolynomialMultiplicity,  // LNU=1
                                       TabulatedMultiplicity >; // LNU=2

  private:

    /* fields */

    Multiplicity data_;

  public:

    /* constructors */

    //! @todo pybind11 variant needs default constructor workaround
    #ifdef PYBIND11
    /**
     *  @brief Default constructor - only enabled for pybind11
     */
    Type() = default;
    #endif

    /**
     *  @brief Constructor
     *
     *  @param[in] zaid            the ZA value of the material
     *  @param[in] awr             the atomic weight ratio
     *  @param[in] multiplicity    the multiplicity data
     */
    Type( int zaid, double awr, Multiplicity&& multiplicity ) :
      BaseWithoutMT( zaid, awr ), data_( std::move( multiplicity ) ) {}

    /**
     *  @brief Constructor (from a buffer)
     *
     *  @tparam Iterator        a buffer iterator
     *
     *  @param[in] head         the head record of the section
     *  @param[in] begin        the current position in the buffer
     *  @param[in] end          the end of the buffer
     *  @param[in] lineNumber   the current line number
     *  @param[in] MAT          the expected MAT number
     */
    template< typename Iterator >
    Type ( const HEAD& head,
           Iterator& begin,
           const Iterator& end,
           long& lineNumber,
           int MAT )
      try: BaseWithoutMT( head, MAT, 1 ),
           data_( std::move( readMultiplicity( begin, end, lineNumber,
                                               MAT, 1, head.MT(), head.L2() ) ) ) {
        readSEND( begin, end, lineNumber, MAT, 1 );
      } catch( std::exception& e ) {
        Log::info( "Trouble while reading section {} of File 1 of Material {}",
                   head.MT(), MAT );
        throw e;
      }

    /* methods */

    /**
     *  @brief Return the fission multiplicity representation type
     */
    int LNU() const { return std::visit( [] ( const auto& v ) -> int
                                            { return v.LNU(); },
                                         this->data_ ); }

    /**
     *  @brief Return the fission multiplicity representation type
     */
    int representation() const { return this->LNU(); }

    /**
     *  @brief Return the fission multiplicity data
     */
    const Multiplicity& nubar() const { return this->data_; }

    /**
     *  @brief Return the number of lines in this MF1/MT456 section
     */
    long NC() const { return 1 + std::visit( [] ( const auto& v ) -> long
                                                { return v.NC(); },
                                             this->data_ ); }

    /**
     *  @brief Print the MF1/MT456 section (includes SEND record)
     *
     *  @tparam OutputIterator   an output iterator
     *
     *  @param[in] it            the current position in the output
     *  @param[in] MAT           the MAT number
     *  @param[in] MF            the MF number
     */
    template< typename OutputIterator >
    void print( OutputIterator& it, int MAT, int MF ) const {

      ControlRecord( this->ZA(), this->AWR(), 0,
                     this->LNU(), 0, 0 ).print( it, MAT, MF, this->MT() );
      std::visit( [&] ( const auto& v ) -> void
                      { v.print( it, MAT, MF, this->MT() ); },
                  this->nubar() );
      SEND( MAT, MF ).print( it );
    }

    /**
     *  @brief Return the MT number of the section
     */
    static constexpr int sectionNumber(){ return 456; }

    using BaseWithoutMT::MT;
    using BaseWithoutMT::ZA;
    using BaseWithoutMT::targetIdentifier;
    using BaseWithoutMT::AWR;
    using BaseWithoutMT::atomicWeightRatio;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
