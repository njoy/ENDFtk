#ifndef NJOY_ENDFTK_TREE_FILE
#define NJOY_ENDFTK_TREE_FILE

// system includes
#include <list>

// other includes
#include "tools/std20/views.hpp"
#include "ENDFtk/file/Type.hpp"
#include "ENDFtk/tree/Section.hpp"
#include "ENDFtk/tree/toSection.hpp"

namespace njoy {
namespace ENDFtk {
namespace tree {

  /**
   *  @class
   *  @brief The ENDF tree file to index and access ENDF section data
   *
   *  This class represents a single file in an ENDF tape and contains the
   *  indexed ENDF sections from that file. It is created by the ENDF tree
   *  Material class and should not be directly constructed by a user.
   */
  class File {

    /* fields */

    int mat_;
    int mf_;
    std::list< Section > sections_;

    /* auxiliary functions */

    /**
     *  @brief Return iterator to the section with the given mt number
     *
     *  @param[in] mt    the mt number
     */
    auto find( int mt ) {

      auto iter = std::lower_bound( this->sections_.begin(), this->sections_.end(), mt,
                                    [] ( auto&& left, auto&& right )
                                       { return left.sectionNumber() < right; } );

      if ( iter != this->sections_.end() ) {

        if ( iter->sectionNumber() == mt ) {

          return iter;
        }
      }
      return this->sections_.end();
    }

    /**
     *  @brief Return iterator to the section with the given mt number
     *
     *  @param[in] mt    the mt number
     */
    auto find( int mt ) const {

      auto iter = std::lower_bound( this->sections_.begin(), this->sections_.end(), mt,
                                    [] ( auto&& left, auto&& right )
                                       { return left.sectionNumber() < right; } );

      if ( iter != this->sections_.end() ) {

        if ( iter->sectionNumber() == mt ) {

          return iter;
        }
      }
      return this->sections_.end();
    }

    template< typename BufferIterator >
    static std::list< Section >
    fill
    ( const HEAD& head, BufferIterator begin,
      BufferIterator& position, const BufferIterator& end, long& lineNumber ){

      std::list< Section > sections;

      auto compare = [] ( auto&& left, auto&& right )
                        { return left.sectionNumber() < right; };

      // read the first HEAD record (we need a structure division)
      --lineNumber;
      position = begin;
      auto division = StructureDivision( position, end, lineNumber );

      // continue reading sections for the same mf
      auto mf = head.MF();
      while ( division.isHead() && ( division.tail.MF() == mf ) ) {

        auto iter = std::lower_bound( sections.begin(), sections.end(), division.tail.MT(), compare );

        // check for duplicate mt
        if ( iter != sections.end() ) {

          if ( iter->sectionNumber() == division.tail.MT() ) {

            Log::error( "Found a duplicate section for MT{}", division.tail.MT() );
            Log::info( "Current position: MAT{} MF{} MT{} at line {}",
                       division.tail.MAT(), division.tail.MF(), division.tail.MT(),
                       lineNumber );
            throw std::exception();
          }
        }

        // add the section
        sections.emplace( iter, asHead( division ), begin, position, end, lineNumber );

        // check for end of stream
        if ( position >= end ) {

          Log::error( "Encountered the end of stream before a FEND record was found" );
          throw std::exception();
        }

        // skip any duplicate SEND records
        begin = position;
        division = StructureDivision( position, end, lineNumber );

        while ( division.isSend() ) {

          begin = position;
          division = StructureDivision( position, end, lineNumber );
          if ( position >= end ) {

            break;
          }
        }
      }

      // warn for missing FEND record
      if ( !division.isFend() ) {

        position = begin;
        Log::info( "The FEND record for MF{} appears to be missing", mf );
        Log::info( "Current position: MAT{} MF{} MT{} at line {}",
                   division.tail.MAT(), division.tail.MF(), division.tail.MT(),
                   lineNumber );
      }

      return sections;
    }

  public:

    /* constructor */

    /**
     *  @brief Empty tree file constructor
     *
     *  @param[in] mat    the MAT number of the file
     *  @param[in] mf     the MF number of the file
     */
    File( unsigned int mat, unsigned int mf ) : mat_( mat ), mf_( mf ) {}

    /**
     *  @brief Constructor (from a buffer)
     *
     *  This constructor is not to be called directly by a user.
     *
     *  @param[in] head         the first head record of the file
     *  @param[in] begin        the beginning of the buffer
     *  @param[in] position     the current position in the buffer
     *  @param[in] end          the end of the buffer
     *  @param[in] lineNumber   the current line number
     */
    template< typename BufferIterator >
    File( const HEAD& head, BufferIterator begin,
          BufferIterator& position, const BufferIterator& end, long& lineNumber )
      try: mat_( head.MAT() ),
           mf_( head.MF() ),
           sections_( fill( head, begin, position, end, lineNumber ) ) {}
      catch ( std::exception& e ) {

        Log::info( "Trouble encountered while constructing an ENDF tree file" );
        throw e;
      }

    /* methods */

    /**
     *  @brief Return MAT number of the file
     */
    int MAT() const { return this->mat_; }

    /**
     *  @brief Return MAT number of the file
     */
    int materialNumber() const { return this->MAT(); }

    /**
     *  @brief Return MF number of the file
     */
    int MF() const { return this->mf_; }

    /**
     *  @brief Return MF number of the file
     */
    int fileNumber() const { return this->MF(); }

    /**
     *  @brief Return all section numbers in the file
     */
    auto sectionNumbers() const {

      using namespace njoy::tools;
      return this->sections_ | std20::views::transform(
                                   [] ( auto&& section )
                                      { return section.sectionNumber(); } );
    }

    /**
     *  @brief Return the section with the requested MT number
     *
     *  @param[in]   mt   the MT number of the section to be returned
     */
    const Section& section( int mt ) const {

      auto iter = this->find( mt );
      if ( iter != this->sections_.end() ) {

        return *iter;
      }

      Log::error( "The requested section (MF{} MT{}) is not present "
                  "in the ENDF file tree",
                  this->fileNumber(), mt );
      throw std::exception();
    }

    /**
     *  @brief Return the section with the requested MT number
     *
     *  @param[in]   mt   the MF number of the section to be returned
     */
    Section& section( int mt ) {

      return const_cast< Section& >
             ( const_cast< const File& >( *this ).section( mt ) );
    }

    /**
     *  @brief Return the section with the requested MT number
     *
     *  @param[in]   mt   the MT number of the section to be returned
     */
    const Section& MT( int mt ) const { return this->section( mt ); }

    /**
     *  @brief Return the section with the requested MT number
     *
     *  @param[in]   mt   the MT number of the section to be returned
     */
    Section& MT( int mt ) { return this->section( mt ); }

    /**
     *  @brief Return whether or not the file has a section with the given MT
     *         number
     *
     *  @param[in]   mt   the MT number of the section
     */
    bool hasMT( int mt ) const {

      return this->find( mt ) != this->sections_.end();
    }

    /**
     *  @brief Return whether or not the file has a section with the given MT
     *         number
     *
     *  @param[in]   mt   the MT number of the section
     */
    bool hasSection( int mt ) const {  return this->hasMT( mt ); }

    /**
     *  @brief Return all sections in the file
     */
    auto sections() const {

      using namespace njoy::tools;
      return std20::views::all( this->sections_ );
    }

    /**
     *  @brief Return all sections in the file
     */
    auto sections() {

      using namespace njoy::tools;
      return std20::views::all( this->sections_ );
    }

    /**
     *  @brief Return a begin iterator to all sections
     */
    auto begin() const {

      return this->sections().begin();
    }

    /**
     *  @brief Return an end iterator to all sections
     */
    auto end() const {

      return this->sections().end();
    }

    /**
     *  @brief Return a begin iterator to all sections
     */
    auto begin() {

      return this->sections().begin();
    }

    /**
     *  @brief Return an end iterator to all sections
     */
    auto end() {

      return this->sections().end();
    }

    /**
     *  @brief Return the number of files in the materials
     */
    std::size_t size() const { return this->sections_.size(); }

    /**
     *  @brief Return the file's content
     */
    auto content() const {

      std::string content;
      for ( const auto& section : this->sections() ) {

        content += section.content();
      }

      if ( content.size() ) {

        auto output = std::back_inserter( content );
        FEND( this->MAT() ).print( output );
      }

      return content;
    }

    /**
     *  @brief Remove the section in the file if it is present
     *
     *  @param[in]   mt   the mt number of the section to be removed
     */
    void remove( int mt ) {

      auto iter = this->find( mt );
      if ( iter != this->sections_.end() ) {

        this->sections_.erase( iter );
      }
    }

    /**
     *  @brief Insert or replace the section in the file
     *
     *  This function inserts or replaces the section in the ENDF file tree.
     *
     *  An exception will be thrown if the MAT and MF number of the section do
     *  not match the MAT and MF number of the file.
     *
     *  @param[in]   section   the section to be inserted or replaced
     */
    void insertOrReplace( Section&& section ) {

      if ( ( this->MAT() != section.MAT() ) || ( this->MF() != section.MF() ) ) {

        Log::error( "The section to be inserted does not have the correct "
                    "MAT and MF number" );
        Log::info( "Expected MAT{} MF{}", this->MAT(), this->MF() );
        Log::info( "Found MAT{} MF{}", section.MAT(), section.MF() );
        throw std::exception();
      }

      auto iter = std::lower_bound( this->sections_.begin(), this->sections_.end(), section.sectionNumber(),
                                    [] ( auto&& left, auto&& right )
                                       { return left.sectionNumber() < right; } );
      if ( iter != this->sections_.end() ) {

        if ( iter->sectionNumber() == section.sectionNumber() ) {

          iter = this->sections_.erase( iter );
        }
      }
      this->sections_.emplace( iter, std::move( section ) );
    }

    /**
     *  @brief Insert or replace the section in the file
     *
     *  This function inserts or replaces the section in the ENDF file tree.
     *
     *  An exception will be thrown if the MAT and MF number of the section do
     *  not match the MAT and MF number of the file.
     *
     *  @param[in]   section   the section to be inserted or replaced
     */
    template< int MF, int... OptionalMT >
    void insertOrReplace( const section::Type< MF, OptionalMT... >& section ) {

      this->insertOrReplace( toSection( section, this->MAT() ) );
    }

    /**
     *  @brief Insert the section in the file
     *
     *  This function inserts the section in the ENDF file tree only if a
     *  section with that MT number is not present yet.
     *
     *  An exception will be thrown if the MAT and MF number of the section do
     *  not match the MAT and MF number of the file, and when a section with the
     *  same MT number is already present.
     *
     *  @param[in]   section   the section to be inserted
     */
    void insert( Section&& section ) {

      if ( this->hasMT( section.MT() ) ) {

        Log::error( "A section for MT{} is already present in the ENDF file tree",
                    section.MT() );
        throw std::exception();
      }

      this->insertOrReplace( std::move( section ) );
    }

    /**
     *  @brief Insert the section in the file
     *
     *  This function inserts the section in the ENDF file tree only if a
     *  section with that MT number is not present yet.
     *
     *  An exception will be thrown if the MAT and MF number of the section do
     *  not match the MAT and MF number of the file, and when a section with the
     *  same MT number is already present.
     *
     *  @param[in]   section   the section to be inserted
     */
    template< int MF, int... OptionalMT >
    void insert( const section::Type< MF, OptionalMT... >& section ) {

      this->insert( toSection( section, this->MAT() ) );
    }

    /**
     *  @brief Parse the file
     *
     *  @param[in] lineNumber   the line number to be used in parsing
     */
    template< int MF >
    file::Type< MF > parse( long& lineNumber ) const {

      std::string content = this->content();
      auto position = content.begin();
      auto end = content.end();

      StructureDivision division( position, end, lineNumber );
      return { division, position, end, lineNumber };
    }

    /**
     *  @brief Parse the file
     */
    template< int MF >
    file::Type< MF > parse() const {

      long lineNumber = 1;
      return this->parse<MF>( lineNumber );
    }

    /**
     *  @brief Clean up the file
     *
     *  This function removes the sequence numbers from the file
     */
    void clean() {

      for ( auto& section : this->sections() ) {

        section.clean();
      }
    }
  };

} // tree namespace
} // ENDFtk namespace
} // njoy namespace

#endif
