class SingleLevelBreitWigner : public BreitWigner {

  /* explicitly declaring this ctor in a private context
     prevents user from accessing to this signature */
  SingleLevelBreitWigner( const Base& base,
                          std::optional<TAB1>&& APE,
                          const CONT& cont,
                          std::vector< LIST >&& lists );
  
public:
  template< typename... Args >
  SingleLevelBreitWigner( Args&&... args )
    try:
      BreitWigner( std::forward<Args>(args)... ){
    } catch ( std::exception& e ){
      Log::info( "Encountered error while constructing"
                 " single level Breit-Wigner resonance parameter subsection" );
      throw e;
    }
};

using SLBW = SingleLevelBreitWigner;
