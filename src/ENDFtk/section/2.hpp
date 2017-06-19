template<>
class Type< 2 > : protected Base {
public:

  CONT isotope;
  template< typename Iterator >
  Type ( HEAD& head, 
         Iterator& begin, 
         const Iterator& end, 
         long& lineNumber, 
         int MAT )
    try: 
      Base( head, MAT, 2 ),
      isotope( begin, end, lineNumber, head.MAT(), 2, head.MT() )
  {
  } catch( std::exception& e ){
    Log::info( "Encountered error while reading section {} of File 2 of \n"
               "Material {}", head.MT(), MAT );
    throw e;
  }
  using Base::MT;
  using Base::ZA;
  using Base::atomicWeightRatio;
};
