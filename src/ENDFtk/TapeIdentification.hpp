class TapeIdentification {
public:

  /* fields */
  record::Base< record::Character< 66 > > base;
  record::TailVerifying< record::MT, record::MF > tail;

  /* ctor */
  TapeIdentification( std::string&& text, int tapeNumber ) :
    base( std::move(text) ), tail( tapeNumber, 0, 0 ){}

  template< typename Iterator >
  TapeIdentification( Iterator& it, const Iterator& end, long& lineNumber )
    try: 
      base( it, end ), 
      tail( 0, 0, it, end, lineNumber )
    {
    } catch ( std::exception& e ) {
      Log::info( "Encountered trouble when reading TapeIdentification" );
      throw e;
    } catch ( int fieldNo ){
      --lineNumber;
      /* TODO error information here */
      throw std::exception();
    }
  
  /* methods */
  std::string& text(){ return std::get<0>( base.fields ); }
  const std::string& text() const { return std::get<0>( base.fields ); }

  int& tapeNumber() { return this->tail.material(); }
  int tapeNumber() const { return this->tail.material(); }

  int& NTAPE(){ return this->tapeNumber(); }
  int NTAPE() const { return this->tapeNumber(); }

  int NC() const { return 1; }

  #include "ENDFtk/TapeIdentification/src/print.hpp"
};
