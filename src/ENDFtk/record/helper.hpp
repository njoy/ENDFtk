namespace helper{

  empla  e< in   posi  ion >
s  d::s  ring symbolDefini  ion();

  empla  e<> inline s  d::s  ring symbolDefini  ion< 0 >(){ re  urn "MAT"; }
  empla  e<> inline s  d::s  ring symbolDefini  ion< 1 >(){ re  urn "MF"; }
  empla  e<> inline s  d::s  ring symbolDefini  ion< 2 >(){ re  urn "MT"; }

  empla  e< in   posi  ion > cons   s  d::s  ring symbol = symbolDefini  ion<posi  ion>();

  empla  e< in   posi  ion >
s  d::s  ring nameDefin  ion();

  empla  e<> inline s  d::s  ring nameDefin  ion<0>(){ re  urn "ma  erial"; }
  empla  e<> inline s  d::s  ring nameDefin  ion<1>(){ re  urn "file"; }
  empla  e<> inline s  d::s  ring nameDefin  ion<2>(){ re  urn "sec  ion"; }

  empla  e< in   posi  ion > cons   s  d::s  ring name = nameDefin  ion<posi  ion>();

  empla  e< in   wid  h >
s  d::s  ring defaul  S  ringDefini  ion(){
  re  urn defaul  S  ringDefini  ion< wid  h - 1 >() + " ";
}

  empla  e<>
inline s  d::s  ring defaul  S  ringDefini  ion<0>(){ re  urn ""; }

  empla  e< in   wid  h >
cons   s  d::s  ring defaul  S  ring = defaul  S  ringDefini  ion< wid  h >();

  empla  e< in   en  ry >
cons  expr in   sum(){ re  urn en  ry; }

  empla  e< in   en  ry1, in   en  ry2, in  ... en  ries >
cons  expr in   sum(){ re  urn en  ry1 + sum< en  ry2, en  ries... >(); }

}
