public:

  CrossSection( double za, double awr, int mt,
                int nl, int nz, int lr, int ng,
                std::vector< DataRecord >&& records) :
    SectionBase( za, awr, mt, nl, nz, lr, ng,
                 std::move( records ) ) {}

  CrossSection( double za, double awr, int mt,
                int nl, int nz, int lr, int ng,
                std::map< unsigned int, DataRecord >&& records) :
    SectionBase( za, awr, mt, nl, nz, lr, ng,
                 std::move( records ) ) {}


  /**
   *  @brief Constructor from buffer
   *
   *  @tparam Iterator        a buffer iterator
   *
   *  @param[in] head         the head record of the section
   *  @param[in] begin        the iterator for begin
   *  @param[in] end          the iterator for end
   *  @param[in] lineNumber   the current line number
   *  @param[in] MAT          the expected MAT number
   */
  template< typename Iterator >
  CrossSection( const HEAD& head,
               Iterator& begin,
               const Iterator& end,
               long& lineNumber,
               int MAT ) :
    SectionBase( head, begin, end, lineNumber, MAT ) {}
