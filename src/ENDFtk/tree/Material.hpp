#ifndef NJOY_ENDFTK_TREE_MATERIAL
#define NJOY_ENDFTK_TREE_MATERIAL

// system includes
#include <list>

// other includes
#include "tools/std20/views.hpp"
#include "ENDFtk/tree/Section.hpp"
#include "ENDFtk/tree/toSection.hpp"
#include "ENDFtk/tree/File.hpp"
#include "ENDFtk/tree/toFile.hpp"

namespace njoy {
namespace ENDFtk {
namespace tree {

  /**
   *  @class
   *  @brief The ENDF tree material to index and access ENDF file data
   *
   *  This class represents a single material in an ENDF tape and contains the
   *  indexed ENDF files. It is created by the ENDF tree Tape class and should
   *  not be directly constructed by a user.
   */
  class Material {

    /* fields */

    int mat_;
    std::list< File > files_;

    /* auxiliary functions */

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

    template< typename BufferIterator >
    static std::list< File >
    fill
    ( const HEAD& head, BufferIterator begin,
      BufferIterator& position, const BufferIterator& end, long& lineNumber ){

      std::list< File > files;

      auto compare = [] ( auto&& left, auto&& right )
                        { return left.fileNumber() < right; };

      // read the first HEAD record (we need a structure division)
      --lineNumber;
      position = begin;
      auto division = StructureDivision( position, end, lineNumber );

      // continue reading sections for the same mf
      auto mat = head.MAT();
      while ( division.isHead() && ( division.tail.MAT() == mat ) ) {

        auto iter = std::lower_bound( files.begin(), files.end(), division.tail.MF(), compare );

        // check for duplicate mf
        if ( iter != files.end() ) {

          if ( iter->fileNumber() == division.tail.MF() ) {

            Log::error( "Found a duplicate section for MF{}", division.tail.MF() );
            Log::info( "Current position: MAT{} MF{} MT{} at line {}",
                       division.tail.MAT(), division.tail.MF(), division.tail.MT(),
                       lineNumber );
            throw std::exception();
          }
        }

        // add the file
        files.emplace( iter, asHead( division ), begin, position, end, lineNumber );

        // check for end of stream
        if ( position >= end ) {

          Log::error( "Encountered the end of stream before a MEND record was found" );
          throw std::exception();
        }

        // skip any duplicate FEND records
        begin = position;
        division = StructureDivision( position, end, lineNumber );

        while ( division.isFend() ) {

          begin = position;
          division = StructureDivision( position, end, lineNumber );
          if ( position >= end ) {

            break;
          }
        }
      }

      // warn for missing MEND record
      if ( !division.isMend() ) {

        position = begin;
        Log::info( "The MEND record for MAT{} appears to be missing", mat );
        Log::info( "Current position: MAT{} MF{} MT{} at line {}",
                   division.tail.MAT(), division.tail.MF(), division.tail.MT(),
                   lineNumber );
      }

      return files;
    }

  public:

    /* constructor */

    /**
     *  @brief Empty material constructor
     *
     *  @param[in] mat    the MAT number of the file
     */
    Material( unsigned int mat ) : mat_( mat ) {}

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
    Material( const HEAD& head, BufferIterator begin, BufferIterator& position,
              const BufferIterator& end, long& lineNumber )
      try : mat_( head.MAT() ),
            files_( fill( head, begin, position, end, lineNumber ) ) {}
      catch( std::exception& e ) {

        Log::info( "Trouble encountered while constructing a material tree." );
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
    const File& file( int mf ) const {

      auto iter = this->find( mf );
      if ( iter != this->files_.end() ) {

        return *iter;
      }

      Log::error( "The requested file (MF{}) is not present "
                  "in the ENDF file tree", mf );
      throw std::exception();
    }

    /**
     *  @brief Return the file with the requested MF number
     *
     *  @param[in]   mf   the MF number of the file to be returned
     */
    File& file( int mf ) {

      return const_cast< File& >
             ( const_cast< const Material& >( *this ).file( mf ) );
    }

    /**
     *  @brief Return the file with the requested MF number
     *
     *  @param[in]   mf   the MF number of the file to be returned
     */
    const File& MF( int mf ) const { return this->file( mf ); }

    /**
     *  @brief Return the file with the requested MF number
     *
     *  @param[in]   mf   the MF number of the file to be returned
     */
    File& MF( int mf ) { return this->file( mf ); }

    /**
     *  @brief Return the section with the requested MF and MT number
     *
     *  @param[in]   mf   the MF number of the section to be returned
     *  @param[in]   mt   the MT number of the section to be returned
     */
    const Section& section( int mf, int mt ) const {

      return this->file( mf ).section( mt );
    }

    /**
     *  @brief Return the section with the requested MF and MT number
     *
     *  @param[in]   mf   the MF number of the section to be returned
     *  @param[in]   mt   the MT number of the section to be returned
     */
    Section& section( int mf, int mt ) {

      return this->file( mf ).section( mt );
    }

    /**
     *  @brief Return the section with the requested MF and MT number
     *
     *  @param[in]   mf   the MF number of the section to be returned
     *  @param[in]   mt   the MT number of the section to be returned
     */
    const Section& MFMT( int mf, int mt ) const {

      return this->section( mf, mt );
    }

    /**
     *  @brief Return the section with the requested MF and MT number
     *
     *  @param[in]   mf   the MF number of the section to be returned
     *  @param[in]   mt   the MT number of the section to be returned
     */
    Section& MFMT( int mf, int mt ) {

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

    /**
     *  @brief Remove the file in the material if it is present
     *
     *  @param[in]   mf   the mf number of the file to be removed
     */
    void remove( int mf ) {

      auto iter = this->find( mf );
      if ( iter != this->files_.end() ) {

        this->files_.erase( iter );
      }
    }

    /**
     *  @brief Remove the section in the material if it is present
     *
     *  @param[in]   mf   the mf number of the section to be removed
     *  @param[in]   mt   the mt number of the section to be removed
     */
    void remove( int mf, int mt ) {

      auto iter = this->find( mf );
      if ( iter != this->files_.end() ) {

        iter->remove( mt );
      }
    }

    /**
     *  @brief Insert or replace the section in the material
     *
     *  This function inserts or replaces the section in the ENDF material tree.
     *
     *  An exception will be thrown if the MAT number of the section does
     *  not match the MAT number of the material.
     *
     *  @param[in]   section   the section to be inserted or replaced
     */
    void insertOrReplace( Section&& section ) {

      if ( !this->hasMF( section.MF() ) ) {

        auto iter = std::lower_bound( this->files_.begin(), this->files_.end(), section.fileNumber(),
                                      [] ( auto&& left, auto&& right )
                                         { return left.fileNumber() < right; } );

        this->files_.emplace( iter, File( this->MAT(), section.MF() ) );
      }

      this->MF( section.MF() ).insertOrReplace( std::move( section ) );
    }

    /**
     *  @brief Insert or replace the section in the material
     *
     *  This function inserts or replaces the section in the ENDF material tree.
     *
     *  An exception will be thrown if the MAT number of the section does
     *  not match the MAT number of the material.
     *
     *  @param[in]   section   the section to be inserted or replaced
     */
    template< int MF, int... OptionalMT >
    void insertOrReplace( const section::Type< MF, OptionalMT... >& file ) {

      this->insertOrReplace( toSection( file, this->MAT() ) );
    }

    /**
     *  @brief Insert or replace the file in the material
     *
     *  This function inserts or replaces the file in the ENDF material tree. This
     *  does not merge sections if the file is already present: the old file is
     *  removed prior to inserting the new file.
     *
     *  An exception will be thrown if the MAT number of the file does
     *  not match the MAT number of the material.
     *
     *  @param[in]   file   the file to be inserted or replaced
     */
    void insertOrReplace( File&& file ) {

      if ( this->MAT() != file.MAT() ) {

        Log::error( "The file to be inserted does not have the correct "
                    "MAT number" );
        Log::info( "Expected MAT{}", this->MAT() );
        Log::info( "Found MAT{}", file.MAT() );
        throw std::exception();
      }

      auto iter = std::lower_bound( this->files_.begin(), this->files_.end(), file.fileNumber(),
                                    [] ( auto&& left, auto&& right )
                                       { return left.fileNumber() < right; } );
      if ( iter != this->files_.end() ) {

        if ( iter->fileNumber() == file.fileNumber() ) {

          iter = this->files_.erase( iter );
        }
      }
      this->files_.emplace( iter, std::move( file ) );
    }

    /**
     *  @brief Insert or replace the file in the material
     *
     *  This function inserts or replaces the file in the ENDF material tree. This
     *  does not merge sections if the file is already present: the old file is
     *  removed prior to inserting the new file.
     *
     *  An exception will be thrown if the MAT number of the file does
     *  not match the MAT number of the material.
     *
     *  @param[in]   file   the file to be inserted or replaced
     */
    template< int MF >
    void insertOrReplace( const file::Type< MF >& file ) {

      this->insertOrReplace( toFile( file, this->MAT() ) );
    }

    /**
     *  @brief Insert the section in the material
     *
     *  This function inserts the section in the ENDF material tree only if a
     *  section with that MT number is not present yet. If the file the section is
     *  to be added to is missing, it is added.
     *
     *  An exception will be thrown if the MAT number of the section does
     *  not match the MAT number of the file, and when a section with the
     *  same MT number is already present.
     *
     *  @param[in]   section   the section to be inserted
     */
    void insert( Section&& section ) {

      if ( !this->hasMF( section.MF() ) ) {

        auto iter = std::lower_bound( this->files_.begin(), this->files_.end(), section.fileNumber(),
                                      [] ( auto&& left, auto&& right )
                                         { return left.fileNumber() < right; } );

        this->files_.emplace( iter, File( this->MAT(), section.MF() ) );
      }

      this->MF( section.MF() ).insert( std::move( section ) );
    }

    /**
     *  @brief Insert the section in the material
     *
     *  This function inserts the section in the ENDF material tree only if a
     *  section with that MT number is not present yet. If the file the section is
     *  to be added to is missing, it is added.
     *
     *  An exception will be thrown if the MAT number of the section does
     *  not match the MAT number of the file, and when a section with the
     *  same MT number is already present.
     *
     *  @param[in]   section   the section to be inserted
     */
    template< int MF, int... OptionalMT >
    void insert( const section::Type< MF, OptionalMT... >& section ) {

      this->insert( toSection( section, this->MAT() ) );
    }

    /**
     *  @brief Insert the file in the material
     *
     *  This function inserts the file in the ENDF material tree only if a
     *  file with that MF number is not present yet.
     *
     *  An exception will be thrown if the MAT number of the file does
     *  not match the MAT number of the file, and when a file with the
     *  same MF number is already present.
     *
     *  @param[in]   file   the file to be inserted
     */
    void insert( File&& file ) {

      if ( this->hasMF( file.MF() ) ) {

        Log::error( "A file for MF{} is already present in the ENDF material tree",
                    file.MF() );
        throw std::exception();
      }

      this->insertOrReplace( std::move( file ) );
    }

    /**
     *  @brief Insert the file in the material
     *
     *  This function inserts the file in the ENDF material tree only if a
     *  file with that MF number is not present yet.
     *
     *  An exception will be thrown if the MAT number of the file does
     *  not match the MAT number of the file, and when a file with the
     *  same MF number is already present.
     *
     *  @param[in]   file   the file to be inserted
     */
    template< int MF >
    void insert( const file::Type< MF >& file ) {

      this->insert( toFile( file, this->MAT() ) );
    }

    /**
     *  @brief Parse the material
     *
     *  @param[in] lineNumber   the line number to be used in parsing
     */
    ::njoy::ENDFtk::Material parse( long& lineNumber ) const {

      std::string content = this->content();
      auto position = content.begin();
      auto end = content.end();

      StructureDivision division( position, end, lineNumber );
      return { division, position, end, lineNumber };
    }

    /**
     *  @brief Parse the material
     */
    ::njoy::ENDFtk::Material parse() const {

      long lineNumber = 1;
      return this->parse( lineNumber );
    }

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
