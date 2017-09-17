class MultilevelBreitWigner : public BreitWigner {
  /* explicitly declaring this ctor in a private context
     prevents user from accessing to this signature */
  MultilevelBreitWigner( const Base& base,
                         std::optional<TAB1>&& APE,
                         const CONT& cont,
                         std::vector< LIST >&& lists );
  
public:
  template< typename... Args >
  MultilevelBreitWigner( Args&&... args )
    try:
      BreitWigner( std::forward<Args>(args)... ){
    } catch ( std::exception& e ){
      Log::info( "Encountered error while constructing "
                 "multilevel Breit-Wigner resonance parameter subsection" );
      throw e;
    }

  static constexpr int LRF() { return 2; }

  #include "ENDFtk/resonanceParameters/resolved/MultilevelBreitWigner/src/print.hpp"
};

using MLBW = MultilevelBreitWigner;
