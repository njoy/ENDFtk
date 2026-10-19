#ifndef NJOY_ENDFTK_MATERIAL
#define NJOY_ENDFTK_MATERIAL

// system includes
#include <list>
#include <variant>

// other includes
#include "tools/std20/views.hpp"
#include "ENDFtk/file/1.hpp"
#include "ENDFtk/file/2.hpp"
#include "ENDFtk/file/3.hpp"
#include "ENDFtk/file/4.hpp"
#include "ENDFtk/file/5.hpp"
#include "ENDFtk/file/6.hpp"
#include "ENDFtk/file/7.hpp"
#include "ENDFtk/file/8.hpp"
#include "ENDFtk/file/9.hpp"
#include "ENDFtk/file/10.hpp"
#include "ENDFtk/file/12.hpp"
#include "ENDFtk/file/13.hpp"
#include "ENDFtk/file/14.hpp"
#include "ENDFtk/file/15.hpp"
#include "ENDFtk/file/23.hpp"
#include "ENDFtk/file/26.hpp"
#include "ENDFtk/file/27.hpp"
#include "ENDFtk/file/28.hpp"
#include "ENDFtk/file/30.hpp"
#include "ENDFtk/file/31.hpp"
#include "ENDFtk/file/32.hpp"
#include "ENDFtk/file/33.hpp"
#include "ENDFtk/file/34.hpp"
#include "ENDFtk/file/35.hpp"
#include "ENDFtk/file/40.hpp"
#include "tools/overload.hpp"

namespace njoy {
namespace ENDFtk {

  class Material {

  public:

    using FileVariant = std::variant<
                            file::Type< 1 >, file::Type< 2 >, file::Type< 3 >,
                            file::Type< 4 >, file::Type< 5 >, file::Type< 6 >,
                            file::Type< 7 >, file::Type< 8 >, file::Type< 9 >,
                            file::Type< 10 >, file::Type< 12 >, file::Type< 13 >,
                            file::Type< 14 >, file::Type< 15 >, file::Type< 23 >,
                            file::Type< 26 >, file::Type< 27 >, file::Type< 28 >,
                            file::Type< 30 >, file::Type< 31 >, file::Type< 32 >,
                            file::Type< 33 >, file::Type< 34 >, file::Type< 35 >,
                            file::Type< 40 > >;

    using SectionVariant = std::variant<
                               std::reference_wrapper< const section::Type< 1, 451 > >,
                               std::reference_wrapper< const section::Type< 1, 452 > >,
                               std::reference_wrapper< const section::Type< 1, 455 > >,
                               std::reference_wrapper< const section::Type< 1, 456 > >,
                               std::reference_wrapper< const section::Type< 1, 458 > >,
                               std::reference_wrapper< const section::Type< 1, 460 > >,
                               std::reference_wrapper< const section::Type< 2, 151 > >,
                               std::reference_wrapper< const section::Type< 2, 152 > >,
                               std::reference_wrapper< const section::Type< 3 > >,
                               std::reference_wrapper< const section::Type< 4 > >,
                               std::reference_wrapper< const section::Type< 5 > >,
                               std::reference_wrapper< const section::Type< 6 > >,
                               std::reference_wrapper< const section::Type< 7, 2 > >,
                               std::reference_wrapper< const section::Type< 7, 4 > >,
                               std::reference_wrapper< const section::Type< 7, 451 > >,
                               std::reference_wrapper< const section::Type< 8, 454 > >,
                               std::reference_wrapper< const section::Type< 8, 457 > >,
                               std::reference_wrapper< const section::Type< 8, 459 > >,
                               std::reference_wrapper< const section::Type< 9 > >,
                               std::reference_wrapper< const section::Type< 10 > >,
                               std::reference_wrapper< const section::Type< 12 > >,
                               std::reference_wrapper< const section::Type< 13 > >,
                               std::reference_wrapper< const section::Type< 14 > >,
                               std::reference_wrapper< const section::Type< 15 > >,
                               std::reference_wrapper< const section::Type< 23 > >,
                               std::reference_wrapper< const section::Type< 26 > >,
                               std::reference_wrapper< const section::Type< 27 > >,
                               std::reference_wrapper< const section::Type< 28 > >,
                               std::reference_wrapper< const section::Type< 31 > >,
                               std::reference_wrapper< const section::Type< 32, 151 > >,
                               std::reference_wrapper< const section::Type< 33 > >,
                               std::reference_wrapper< const section::Type< 34 > >,
                               std::reference_wrapper< const section::Type< 35 > >,
                               std::reference_wrapper< const section::Type< 40 > > >;

  private:

    /* fields */

    int mat_;
    std::list< FileVariant > files_;

    /* auxiliary functions */

    /**
     *  @brief Return iterator to the file with the given mf number
     *
     *  @param[in] mt    the mf number
     */
    auto find( int mf ) {

      auto getMF = [] ( auto&& value ) { return value.MF(); };
      auto iter = std::lower_bound( this->files_.begin(), this->files_.end(), mf,
                                    [&getMF] ( auto&& left, auto&& right )
                                             { return std::visit( getMF, left ) < right; } );

      if ( iter != this->files_.end() ) {

        if ( std::visit( getMF, *iter ) == mf ) {

          return iter;
        }
      }
      return this->files_.end();
    }

    /**
     *  @brief Return iterator to the section with the given mf number
     *
     *  @param[in] mf    the mf number
     */
    auto find( int mf ) const {

      auto getMF = [] ( auto&& value ) { return value.MF(); };
      auto iter = std::lower_bound( this->files_.begin(), this->files_.end(), mf,
                                    [&getMF] ( auto&& left, auto&& right )
                                             { return std::visit( getMF, left ) < right; } );

      if ( iter != this->files_.end() ) {

        if ( std::visit( getMF, *iter ) == mf ) {

          return iter;
        }
      }
      return this->files_.end();
    }

    static auto
    fill( std::vector< FileVariant >&& files ) {

      std::list< FileVariant > list;
      for ( auto&& file : files ) {

        auto getMF = [] ( auto&& value ) { return value.MF(); };
        int MF = std::visit( getMF, file );
        auto iter = std::lower_bound( list.begin(), list.end(), MF,
                                      [&getMF] ( auto&& left, auto&& right )
                                               { return std::visit( getMF, left ) < right; } );
        if ( iter != list.end() ) {

          if ( std::visit( getMF, *iter ) == MF ) {

            Log::error( "File with duplicate file number found" );
            Log::info( "Files are required to specify a unique MF or file number" );
            Log::info( "Encountered duplicate MF: {}", MF );
            throw std::exception();
          }
        }
        list.insert( iter, std::move( file ) );
      }
      return list;
    }

    template< typename Iterator >
    static auto
    read( StructureDivision& division,
          Iterator& begin,
          const Iterator& end,
          long& lineNumber ) {

      std::vector< FileVariant > files;
      while ( not division.isMend() ) {

        switch ( division.tail.MF() ) {

          case  1 : { files.emplace_back( file::Type<  1 >( division, begin, end, lineNumber ) ); break; }
          case  2 : { files.emplace_back( file::Type<  2 >( division, begin, end, lineNumber ) ); break; }
          case  3 : { files.emplace_back( file::Type<  3 >( division, begin, end, lineNumber ) ); break; }
          case  4 : { files.emplace_back( file::Type<  4 >( division, begin, end, lineNumber ) ); break; }
          case  5 : { files.emplace_back( file::Type<  5 >( division, begin, end, lineNumber ) ); break; }
          case  6 : { files.emplace_back( file::Type<  6 >( division, begin, end, lineNumber ) ); break; }
          case  7 : { files.emplace_back( file::Type<  7 >( division, begin, end, lineNumber ) ); break; }
          case  8 : { files.emplace_back( file::Type<  8 >( division, begin, end, lineNumber ) ); break; }
          case  9 : { files.emplace_back( file::Type<  9 >( division, begin, end, lineNumber ) ); break; }
          case 10 : { files.emplace_back( file::Type< 10 >( division, begin, end, lineNumber ) ); break; }
          case 12 : { files.emplace_back( file::Type< 12 >( division, begin, end, lineNumber ) ); break; }
          case 13 : { files.emplace_back( file::Type< 13 >( division, begin, end, lineNumber ) ); break; }
          case 14 : { files.emplace_back( file::Type< 14 >( division, begin, end, lineNumber ) ); break; }
          case 15 : { files.emplace_back( file::Type< 15 >( division, begin, end, lineNumber ) ); break; }
          case 23 : { files.emplace_back( file::Type< 23 >( division, begin, end, lineNumber ) ); break; }
          case 26 : { files.emplace_back( file::Type< 26 >( division, begin, end, lineNumber ) ); break; }
          case 27 : { files.emplace_back( file::Type< 27 >( division, begin, end, lineNumber ) ); break; }
          case 28 : { files.emplace_back( file::Type< 28 >( division, begin, end, lineNumber ) ); break; }
          case 30 : { files.emplace_back( file::Type< 30 >( division, begin, end, lineNumber ) ); break; }
          case 31 : { files.emplace_back( file::Type< 31 >( division, begin, end, lineNumber ) ); break; }
          case 32 : { files.emplace_back( file::Type< 32 >( division, begin, end, lineNumber ) ); break; }
          case 33 : { files.emplace_back( file::Type< 33 >( division, begin, end, lineNumber ) ); break; }
          case 34 : { files.emplace_back( file::Type< 34 >( division, begin, end, lineNumber ) ); break; }
          case 35 : { files.emplace_back( file::Type< 35 >( division, begin, end, lineNumber ) ); break; }
          case 40 : { files.emplace_back( file::Type< 40 >( division, begin, end, lineNumber ) ); break; }
          default : {

            int MF = division.tail.MF();
            Log::error( "Found unsupported file MF{} - skipping file", MF );
            throw std::exception();
          }
        }
        division = StructureDivision( begin, end, lineNumber );
      }
      verifyMEND( division, lineNumber );
      return std::move( files );
    }

    static void
    verifyMEND( const StructureDivision& structureDivision,
               long lineNumber ) {

      if ( not structureDivision.isMend() ) {

        Log::error( "Expected MEND record" );
        Log::info("Line number: {}", lineNumber );
        throw std::exception{};
      }
    }

    /* constructor */

    /**
     *  @brief Private intermediate constructor
     *
     *  @param[in] sections   the sections of the file
     */
    template< typename Iterator >
    Material( int MAT,
              StructureDivision& division,
              Iterator& begin,
              const Iterator& end,
              long& lineNumber ) :
      Material( MAT, this->read( division, begin, end, lineNumber ) ) {}

  public:

    /* constructors */

    /**
     *  @brief Constructor
     *
     *  @param[in] sections   the sections of the file
     */
    Material( int MAT, std::vector< FileVariant >&& files ) :
      mat_( MAT ), files_( fill( std::move( files ) ) ) {}

    /**
     *  @brief Constructor (from a buffer)
     *
     *  @tparam Iterator        a buffer iterator
     *
     *  @param[in] division     the first HEAD record of the section
     *  @param[in] it           the current position in the buffer
     *  @param[in] end          the end of the buffer
     *  @param[in] lineNumber   the current line number
     */
    template< typename Iterator >
    Material( StructureDivision& division,
              Iterator& begin,
              const Iterator& end,
              long& lineNumber )
      try: Material( division.tail.MAT(), division, begin, end, lineNumber ) {

        this->verifyMEND( division, lineNumber );
      }
      catch ( std::exception& e ) {

        Log::info( "Error while reading material {}", division.tail.MAT() );
        throw e;
      }

    /* methods */

    /**
     *  @brief Return the material number
     */
    int MAT() const { return this->mat_; }

    /**
     *  @brief Return the material number
     */
    int materialNumber() const { return this->MAT(); }

    /**
     *  @brief Return the files stored in this material
     */
    auto MFs() {

      using namespace njoy::tools;
      return std20::views::all( this->files_ );
    }

    /**
     *  @brief Return the files stored in this material
     */
    auto files() { return this->MFs(); }

    /**
     *  @brief Return the files stored in this material
     */
    auto MFs() const {

      using namespace njoy::tools;
      return std20::views::all( this->files_ );
    }

    /**
     *  @brief Return the files stored in this material
     */
    auto files() const { return this->MFs(); }

    /**
     *  @brief Return an iterator to the start of the files
     */
    auto begin() { return this->files().begin(); }

    /**
     *  @brief Return an iterator to the end of the files
     */
    auto end() { return this->files().end(); }

    /**
     *  @brief Return an iterator to the start of the files
     */
    auto begin() const { return this->files().begin(); }

    /**
     *  @brief Return an iterator to the end of the files
     */
    auto end() const { return this->files().end(); }

    /**
     *  @brief Verify if a given file (defined by the MF number) is defined
     *
     *  @param mf   the MF number of the file to be verified
     */
    bool hasMF( int mf ) const {

      return this->find( mf ) != this->files_.end();
    }

    /**
     *  @brief Verify if a given file (defined by the MF number) is defined
     *
     *  @param mf   the MF number of the file to be verified
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

      return this->hasMF( mf )
                 ? std::visit( [&] ( const auto& file ) -> bool
                                   { return file.hasMT( mt ); },
                               this->MF( mf ) )
                 : false;
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
     *  @brief Return the file with the requested MF number
     *
     *  @param[in] mf   the MF number of the file to be returned
     */
    const FileVariant& file( int mf ) const {

      auto iter = this->find( mf );
      if ( iter != this->files_.end() ) {

        return *iter;
      }

      Log::error( "Requested file number (MF) does not"
                  " correspond to a stored file" );
      Log::info( "Requested file number: {}", mf );
      Log::info( "Material queried: ", this->MAT() );
      throw std::exception();
    }

    /**
     *  @brief Return the file with the requested MF number
     *
     *  @param[in] mf   the MF number of the file to be returned
     */
    const FileVariant& MF( int mf ) const {

      return this->file( mf );
    }

    /**
     *  @brief Return the section with the requested MF and MT number
     *
     *  Note: this returns a variant of reference wrappers since the data is
     *        stored by file first.
     *
     *  @param[in] mf   the MF number of the section to be returned
     *  @param[in] mt   the MT number of the section to be returned
     */
    SectionVariant section( int mf, int mt ) const {

      return std::visit(
                 tools::overload{
                     [=] ( const file::Type< 1 >& file ) -> SectionVariant
                         { return std::visit(
                                      [=] ( const auto& section ) -> SectionVariant
                                          { return std::cref( section ); },
                                      file.section( mt ) ); },
                     [=] ( const file::Type< 2 >& file ) -> SectionVariant
                         { return std::visit(
                                      [=] ( const auto& section ) -> SectionVariant
                                          { return std::cref( section ); },
                                      file.section( mt ) ); },
                     [=] ( const file::Type< 7 >& file ) -> SectionVariant
                         { return std::visit(
                                      [=] ( const auto& section ) -> SectionVariant
                                          { return std::cref( section ); },
                                      file.section( mt ) ); },
                     [=] ( const file::Type< 8 >& file ) -> SectionVariant
                         { return std::visit(
                                      [=] ( const auto& section ) -> SectionVariant
                                          { return std::cref( section ); },
                                      file.section( mt ) ); },
                     [] ( const file::Type< 30 >& ) -> SectionVariant
                        { throw std::exception(); },
                     // MF=32 is enumerated but only one section is allowed so
                     // we do not need a visit on the section
                     [=] ( const auto& file ) -> SectionVariant
                         { return std::cref( file.section( mt ) ); } },
                 this->file( mf ) );
    }

    /**
     *  @brief Return the section with the requested MF and MT number
     *
     *  Note: this returns a variant of reference wrappers since the data is
     *        stored by file first.
     *
     *  @param[in] mf   the MF number of the section to be returned
     *  @param[in] mt   the MT number of the section to be returned
     */
    SectionVariant MFMT( int mf, int mt ) const {

      return this->section( mf, mt );
    }

    /**
     *  @brief Print the file (includes FEND record)
     *
     *  @tparam OutputIterator   an output iterator
     *
     *  @param[in] it            the current position in the output
     */
    template< typename OutputIterator >
    void print( OutputIterator& it ) const {

      int MAT = this->MAT();
      for ( const auto& entry : this->files_ ) {

        std::visit( [&] ( auto&& file ) { file.print( it, MAT ); }, entry );
      }
      MEND().print( it );
    }
  };

} // ENDFtk namespace
} // njoy namespace

#endif
