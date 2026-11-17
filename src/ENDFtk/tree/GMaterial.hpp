#ifndef NJOY_ENDFTK_TREE_GMATERIAL
#define NJOY_ENDFTK_TREE_GMATERIAL

// system includes
#include <list>

// other includes
#include "tools/std20/views.hpp"
#include "ENDFtk/tree/GSection.hpp"
#include "ENDFtk/tree/GFile.hpp"

namespace njoy {
namespace ENDFtk {
namespace tree {

  /**
   *  @class
   *  @brief The GENDF tree material to index and access GENDF file data
   *
   *  This class represents a single material in a GENDF tape and contains the
   *  indexed GENDF files. It is created by the GENDF tree GTape class and should
   *  not be directly constructed by a user.
   */
  class GMaterial {

    /* fields */

    int mat_;
    std::list< GFile > files_;

    /* auxiliary functions */

    template< typename BufferIterator >
    static std::list< GFile >
    fill
    ( const HEAD& head, BufferIterator begin,
      BufferIterator& position, const BufferIterator& end, long& lineNumber ){

      std::list< GFile > files;
      std::vector< GSection > sections;

      auto compare = [] ( auto&& left, auto&& right ) {

        if ( left.MF() < right.first ) {

          return true;
        }
        else if ( left.MF() == right.first ) {

          return left.MT() < right.second;
        }
        else {

          return false;
        }
      };

      // read the first HEAD record (we need a structure division)
      --lineNumber;
      position = begin;
      auto division = StructureDivision( position, end, lineNumber );

      // continue reading sections for the same mf
      auto mat = head.MAT();
      while ( division.isHead() && ( division.tail.MAT() == mat ) ) {

        auto iter = std::lower_bound( sections.begin(), sections.end(),
                                      std::make_pair( division.tail.MF(), division.tail.MT() ),
                                      compare );

        // check for duplicate mf,mt
        if ( ( iter != sections.end() ) &&
             ( iter->fileNumber() == division.tail.MF() ) &&
             ( iter->sectionNumber() == division.tail.MT() ) ) {

          Log::info( "Found a duplicate section for MF{} MT{}, skipping section",
                     division.tail.MF(), division.tail.MT() );
          Log::info( "Current position: MAT{} MF{} MT{} at line {}",
                     division.tail.MAT(), division.tail.MF(), division.tail.MT(),
                     lineNumber );

          //just skip the section
          GSection( asHead( division ), begin, position, end, lineNumber );
        }
        else {

          // add the section
          sections.emplace( iter, asHead( division ), begin, position, end, lineNumber );
        }

        // check for end of stream
        if ( position >= end ) {

          Log::error( "Encountered the end of stream before an END record was found" );
          throw std::exception();
        }

        // get the next HEAD record
        begin = position;
        division = StructureDivision( position, end, lineNumber );
        if ( ! division.isHead() && division.isFend() ) {

          begin = position;
          division = StructureDivision( position, end, lineNumber );
        }
      }

      // subdivide into files
      auto iter = sections.begin();
      auto upper = std::upper_bound( sections.begin(), sections.end(), iter->fileNumber(),
                                     [] ( auto&& left, auto&& right )
                                        { return left < right.fileNumber(); } );
      while ( iter != sections.end() ) {

        files.emplace_back( iter->materialNumber(), iter->fileNumber(),
                            std::list< GSection >( iter, upper ) );

        iter = upper;
        upper = std::upper_bound( iter, sections.end(), iter->fileNumber(),
                                  [] ( auto&& left, auto&& right )
                                     { return left < right.fileNumber(); } );
      }

      return files;
    }

    // blatantly copied from the tree Material

    /**
     *  @brief Return iterator to the file with the given mf number
     *
     *  @param[in] mf    the mf number
     */
    auto find( int mf ) {

      auto iter = std::lower_bound( this->files_.begin(), this->files_.end(), mf,
                                    [] ( auto&& left, auto&& right )
                                       { return left.fileNumber() < right; } );

      if ( iter != this->files_.end() ) {

        if ( iter->fileNumber() == mf ) {

          return iter;
        }
      }
      return this->files_.end();
    }

    /**
     *  @brief Return iterator to the file with the given mf number
     *
     *  @param[in] mf    the mf number
     */
    auto find( int mf ) const {

      auto iter = std::lower_bound( this->files_.begin(), this->files_.end(), mf,
                                    [] ( auto&& left, auto&& right )
                                       { return left.fileNumber() < right; } );

      if ( iter != this->files_.end() ) {

        if ( iter->fileNumber() == mf ) {

          return iter;
        }
      }
      return this->files_.end();
    }

  public:

    /* constructor */

    /**
     *  @brief Empty material constructor
     *
     *  @param[in] mat    the MAT number of the file
     */
    GMaterial( unsigned int mat ) : mat_( mat ), files_() {}

    /**
     *  @brief Constructor (from a buffer)
     *
     *  This constructor is not to be called directly by a user.
     *
     *  @param[in] head         the first head record of the material
     *  @param[in] begin        the beginning of the buffer
     *  @param[in] position     the current position in the buffer
     *  @param[in] end          the end of the buffer
     *  @param[in] lineNumber   the current line number
     */
    template< typename BufferIterator >
    GMaterial( const HEAD& head, BufferIterator begin, BufferIterator& position,
               const BufferIterator& end, long& lineNumber )
      try : mat_( head.MAT() ),
            files_( fill( head, begin, position, end, lineNumber ) ) {}
      catch( std::exception& e ) {

        Log::info( "Trouble encountered while constructing a GENDF tree material" );
        Log::info( "Material number (MAT): {}", head.MAT() );
        throw e;
      }

    /* methods */

    /**
     *  @brief Return MAT number of the material
     */
    int MAT() const { return this->mat_; }

    /**
     *  @brief Return MAT number of the material
     */
    int materialNumber() const { return this->MAT(); }

    /**
     *  @brief Return all file numbers in the material
     */
    auto fileNumbers() const {

      using namespace njoy::tools;
      return this->files_ | std20::views::transform(
                                   [] ( auto&& file )
                                      { return file.fileNumber(); } );
    }

    /**
     *  @brief Return the file with the requested MF number
     *
     *  @param[in]   mf   the MF number of the file to be returned
     */
    const GFile& file( int mf ) const {

      auto iter = this->find( mf );
      if ( iter != this->files_.end() ) {

        return *iter;
      }

      Log::error( "The requested file (MF{}) is not present "
                  "in the GENDF file tree", mf );
      throw std::exception();
    }

    /**
     *  @brief Return the file with the requested MF number
     *
     *  @param[in]   mf   the MF number of the file to be returned
     */
    GFile& file( int mf ) {

      return const_cast< GFile& >
             ( const_cast< const GMaterial& >( *this ).file( mf ) );
    }

    /**
     *  @brief Return the file with the requested MF number
     *
     *  @param[in]   mf   the MF number of the file to be returned
     */
    const GFile& MF( int mf ) const { return this->file( mf ); }

    /**
     *  @brief Return the file with the requested MF number
     *
     *  @param[in]   mf   the MF number of the file to be returned
     */
    GFile& MF( int mf ) { return this->file( mf ); }

    /**
     *  @brief Return the section with the requested MF and MT number
     *
     *  @param[in]   mf   the MF number of the section to be returned
     *  @param[in]   mt   the MT number of the section to be returned
     */
    const GSection& section( int mf, int mt ) const {

      return this->file( mf ).section( mt );
    }

    /**
     *  @brief Return the section with the requested MF and MT number
     *
     *  @param[in]   mf   the MF number of the section to be returned
     *  @param[in]   mt   the MT number of the section to be returned
     */
    GSection& section( int mf, int mt ) {

      return this->file( mf ).section( mt );
    }

    /**
     *  @brief Return the section with the requested MF and MT number
     *
     *  @param[in]   mf   the MF number of the section to be returned
     *  @param[in]   mt   the MT number of the section to be returned
     */
    const GSection& MFMT( int mf, int mt ) const {

      return this->section( mf, mt );
    }

    /**
     *  @brief Return the section with the requested MF and MT number
     *
     *  @param[in]   mf   the MF number of the section to be returned
     *  @param[in]   mt   the MT number of the section to be returned
     */
    GSection& MFMT( int mf, int mt ) {

      return this->section( mf, mt );
    }

    /**
     *  @brief Return whether or not the material has a file with the given MF
     *         number
     *
     *  @param[in]   mf   the MF number of the file
     */
    bool hasMF( int mf ) const { return this->find( mf ) != this->files_.end(); }

    /**
     *  @brief Return whether or not the material has a file with the given MF
     *         number
     *
     *  @param[in]   mf   the MF number of the file
     */
    bool hasFile( int mf ) const { return this->hasMF( mf ); }

    /**
     *  @brief Return whether or not the material has a section with the given
     *         MF and MT number
     *
     *  @param[in]   mf   the MF number of the section
     *  @param[in]   mt   the MT number of the section
     */
    bool hasMFMT( int mf, int mt ) const {

      return this->hasMF( mf ) ? this->file( mf ).hasMT( mt ) : false;
    }

    /**
     *  @brief Return whether or not the material has a section with the given
     *         MF and MT number
     *
     *  @param[in]   mf   the MF number of the section
     *  @param[in]   mt   the MT number of the section
     */
    bool hasSection( int mf, int mt ) const { return this->hasMFMT( mf, mt ); }

    /**
     *  @brief Return all files in the material
     */
    auto files() const {

      using namespace njoy::tools;
      return std20::views::all( this->files_ );
    }

    /**
     *  @brief Return all files in the material
     */
    auto files() {

      using namespace njoy::tools;
      return std20::views::all( this->files_ );
    }

    /**
     *  @brief Return a begin iterator to all files
     */
    auto begin() const { return this->files().begin(); }

    /**
     *  @brief Return an end iterator to all files
     */
    auto end() const { return this->files().end(); }

    /**
     *  @brief Return a begin iterator to all files
     */
    auto begin()  { return this->files().begin(); }

    /**
     *  @brief Return an end iterator to all files
     */
    auto end()  { return this->files().end(); }

    /**
     *  @brief Return the number of files in the materials
     */
    std::size_t size() const { return files_.size(); }

    /**
     *  @brief Return the material's content
     */
    auto content() const {

      std::string content;
      for ( const auto& file : this->files() ) {

        content += file.content();
      }

      if ( content.size() ) {

        auto output = std::back_inserter( content );
        MEND().print( output );
      }

      return content;
    }

//    #include "ENDFtk/tree/Material/src/remove.hpp"
//    #include "ENDFtk/tree/Material/src/insertOrReplace.hpp"
//    #include "ENDFtk/tree/Material/src/insert.hpp"

//    #include "ENDFtk/tree/Material/src/parse.hpp"

    // blatantly copied from the tree Material

    /**
     *  @brief Clean up the material
     *
     *  This function removes the sequence numbers from the material
     */
    void clean() {

      for ( auto& file : this->files() ) {

        file.clean();
      }
    }
  };

} // tree namespace
} // ENDFtk namespace
} // njoy namespace

#endif
