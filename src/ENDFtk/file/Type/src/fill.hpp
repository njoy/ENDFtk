static auto
fill( std::vector< Section >&& sections ) {

  std::map< int, Section > sectionMap;
  ranges::for_each( sections,
                    hana::partial( insert{}, std::ref( sectionMap ) ) );
  return sectionMap;
}
