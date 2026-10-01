/**
 *  @class
 *  @brief Tabulated incoherent inelastic scattering law
 *
 *  The Tabulated class is used to represent the case in which the incoherent
 *  inelastic thermal scattering law of the principal scatterer in
 *  ENDF section MF4/MT4 is represented entirely as a tabulated function.
 *
 *  The tabulated S(alpha,beta,T) functions are given as tabulated S(alpha,T)
 *  functions for fixed beta values.
 *
 *  See ENDF102, section 7.5 for more information.
 */
class ENDFTK_PYTHON_EXPORT TabulatedFunctions {

public:

  #include "ENDFtk/section/7/4/TabulatedFunctions/ScatteringFunction.hpp"

private:

  /* members */

  InterpolationSequenceRecord< ScatteringFunction > data_;

  /* auxiliary functions */

  /* constructor */

  /**
   *  @brief Private constructor
   */
  TabulatedFunctions( InterpolationSequenceRecord< ScatteringFunction >&& sequence ) :
    data_( std::move( sequence ) ) {

    //! @todo verify number of beta versus NB
    //! @todo verify the same temperature in each ScatteringFunction
    //! @todo verify the same temperature interpolants in each ScatteringFunction
  }

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] boundaries     the interpolation range boundaries
   *  @param[in] interpolants   the interpolation types for each range
   *  @param[in] functions      the beta values and associated S(alpha,T)
   *                            functions
   */
  TabulatedFunctions( std::vector< long >&& boundaries,
                      std::vector< long >&& interpolants,
                      std::vector< ScatteringFunction >&& functions )
    try : TabulatedFunctions( InterpolationSequenceRecord< ScatteringFunction >(
                                InterpolationRecord( 0.0, 0.0, 0, 0,
                                                     std::move( boundaries ),
                                                     std::move( interpolants ) ),
                                std::move( functions ) ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing tabulated thermal "
                 "scattering law" );
      throw;
    }

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
  TabulatedFunctions( Iterator& begin,
                      const Iterator& end,
                      long& lineNumber,
                      int MAT,
                      int MF,
                      int MT )
    try : TabulatedFunctions(
            ENDFtk::readInterpolationSequenceRecord< ScatteringFunction >(
                begin, end, lineNumber, MAT, MF, MT ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing tabulated thermal "
                 "scattering law" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the number of interpolation ranges on the beta grid
   */
  long NR() const { return this->data_.tab2().NR(); }

  /**
   *  @brief Return the number of interpolation ranges on the beta grid
   */
  long numberInterpolationRegions() const { return this->NR(); }

  /**
   *  @brief Return the number of beta values
   */
  long NB() const { return this->data_.tab2().NZ(); }

  /**
   *  @brief Return the number of beta values
   */
  long numberBetas() const { return this->NB(); }

  /**
   *  @brief Return the beta values and associated S(alpha,T) functions
   */
  auto B() const {

    using namespace njoy::tools;
    return this->data_.records() | std20::views::transform( [] ( const auto& record )
                                                               { return record.beta(); } );
  }

  /**
   *  @brief Return the beta values and associated S(alpha,T) functions
   */
  auto betas() const { return this->B(); }

  /**
   *  @brief Return the beta values and associated S(alpha,T) functions
   */
  auto S() const { return this->data_.records(); }

  /**
   *  @brief Return the beta values and associated S(alpha,T) functions
   */
  auto scatteringFunctions() const {

    return this->S();
  }

  /**
   *  @brief Return the interpolation type for each range on the beta grid
   */
  auto INT() const { return this->data_.tab2().INT(); }

  /**
   *  @brief Return the interpolation type for each range on the beta grid
   */
  auto interpolants() const { return this->INT(); }

  /**
   *  @brief Return the interpolation boundaries for the beta grid
   */
  auto NBT() const { return this->data_.tab2().NBT(); }

  /**
   *  @brief Return the interpolation boundaries for the beta grid
   */
  auto boundaries() const { return this->NBT(); }

  /**
   *  @brief Return the number of lines in this MF7/MT4 component
   */
  long NC() const { return this->data_.NC(); }

  /** 
   *  @brief Print this MF7/MT4 component
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
    this->data_.print( it, MAT, MF, MT );
  } 
};
