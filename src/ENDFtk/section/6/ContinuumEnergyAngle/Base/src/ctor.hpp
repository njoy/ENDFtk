//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
Base() = default;
#endif

Base( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

  verifySorted( this->energies() | njoy::tools::std20::views::drop( this->ND() ),
                "Energy" );
  verifySize( this->NW(), this->NA(), this->NEP() );
};

Base( double energy, long nd, long na, long nep,
      std::vector< double >&& list ) :
  Base( ListRecord( 0.0, energy, nd, na, nep,
                    std::move( list ) ) ) {};

template< typename Iterator >
Base( Iterator& it, const Iterator& end, long& lineNumber,
      int MAT, int MF, int MT ) :
  Base( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
