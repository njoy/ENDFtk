template<>
class Type< 3 > : protected Base {
public:

  /* fields */
  UnivariateTabulation table;

  /* methods */
  template< typename Iterator >
  Type
  ( HEAD& head, Iterator& begin, const Iterator& end, long& lineNumber, int MAT )
    try: Base( head, MAT, 3 ),
         table( begin, end, lineNumber, head.MAT(), 3, head.MT() ){ 
      const auto found = std::find_if( this->table.yBegin(),
                                       this->table.yEnd(),
                                       []( auto y ) { return y < 0.0; } );
      if( found != this->table.yEnd() ){
        LOG(ERROR) << "Encountered negative cross section"
                   << " value in Section " << head.MT()
                   << " of File 3 of Material " << MAT;
        LOG(ERROR) << "TAB1 entry ["
                   << std::distance( this->table.yBegin(), found )
                   << "]: " << *found;
        throw std::exception();
      }
      readSEND(begin, end, lineNumber, MAT, 3 );
    } catch( std::exception& e ){
      LOG(INFO) << "Trouble encountered while constructing section "
                << head.MT() << " of File 3 of Material " << MAT
                << "on line " << lineNumber << ".";
      throw e;
    }
    
  using Base::MT;
  using Base::ZA;
  using Base::atomicWeightRatio;
};

