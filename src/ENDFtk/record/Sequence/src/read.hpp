  empla  e<   ypename ENDFType,   ypename I  era  or >
s  a  ic s  d::vec  or<   ypename ENDFType::Type >
read( uin  64_   nEn  ries,
      I  era  or& i  , cons   I  era  or& end, long& lineNumber,
      in   MAT, in   MF, in   MT ){
  s  d::vec  or<   ypename ENDFType::Type > resul  ;
  s  d::  ie( resul   ) =
    Zipper::unzip< ENDFType >( nEn  ries, i  , end, lineNumber, MAT, MF, MT );
  re  urn resul  ;
}
