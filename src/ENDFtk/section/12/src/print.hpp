/**
 *  @brief Print the MF7/MT2 section (includes SEND record)
 *
 *  @tparam OutputIterator   an output iterator
 *
 *  @param[in] it            the current position in the output
 *  @param[in] MAT           the MAT number
 *  @param[in] MF            the MF number
 */
template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF ) const {

  struct L2 {

    int operator()( const Multiplicities& ) { return 0; }
    int operator()( const TransitionProbabilities& value ) {

      return value.LG();
    }
  };

  struct N1 {

    int operator()( const Multiplicities& value ) { return value.NK(); }
    int operator()( const TransitionProbabilities& value ) {

      return value.NT() + 2;
    }
  };

  int MT = this->MT();
  ControlRecord( this->ZA(), this->AWR(), this->LO(),
                 std::visit( L2(), this->photon_ ),
                 std::visit( N1(), this->photon_ ),
                 0 ).print( it, MAT, MF, MT );
  std::visit( [&] ( const auto& v ) -> void
                  { v.print( it, MAT, MF, MT ); },
              this->photon_ );
  SEND( MAT, MF ).print( it );
}
