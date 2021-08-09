# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF27 import File
from ENDFtk.MF27 import Section
from ENDFtk.tree import Tape

class Test_ENDFtk_MF27_File( unittest.TestCase ) :
    """Unit test for the File class."""

    chunk = ( ' 1.000000+3 9.991673-1          0          0          0          0 10027  1     \n'
              ' 0.000000+0 1.000000+0          0          0          1          2 10027  1     \n'
              '          2          5                                             10027  1     \n'
              ' 1.000000-5 1.000000+0 2.000000+7 2.000000+0                       10027  1     \n'
              '                                                                   10027  0     \n'
              ' 1.000000+3 9.991673-1          0          0          0          0 10027  2     \n'
              ' 0.000000+0 1.000000+0          0          0          1          2 10027  2     \n'
              '          2          2                                             10027  2     \n'
              ' 1.000000-5 3.000000+0 2.000000+7 4.000000+0                       10027  2     \n'
              '                                                                   10027  0     \n'
              ' 1.000000+3 9.991673-1          0          0          0          0 10027102     \n'
              ' 0.000000+0 1.000000+0          0          0          1          2 10027102     \n'
              '          2          5                                             10027102     \n'
              ' 1.000000-5 5.000000+0 2.000000+7 6.000000+0                       10027102     \n'
              '                                                                   10027  0     \n' )

    valid_TPID = 'Just a tape identifier                                                          \n'
    valid_FEND = '                                                                   100 0  0     \n'
    valid_MEND = '                                                                     0 0  0     \n'
    valid_TEND = '                                                                    -1 0  0     \n'
    invalid_FEND = '                                                                   10027  1     \n'

    def test_file( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 27, chunk.MF )
            self.assertEqual( 27, chunk.file_number )

            self.assertEqual( True, chunk.has_MT( 1 ) )
            self.assertEqual( True, chunk.has_MT( 2 ) )
            self.assertEqual( True, chunk.has_MT( 102 ) )
            self.assertEqual( True, chunk.has_section( 1 ) )
            self.assertEqual( True, chunk.has_section( 2 ) )
            self.assertEqual( True, chunk.has_section( 102 ) )

            self.assertEqual( False, chunk.has_MT( 12 ) )
            self.assertEqual( False, chunk.has_section( 12 ) )

            section = chunk.section( 1 )
            self.assertEqual( 1000, section.ZA )
            self.assertEqual( 1, section.Z )
            self.assertEqual( 5, section.interpolants[0] )

            section = chunk.section( 2 )
            self.assertEqual( 1000, section.ZA )
            self.assertEqual( 1, section.Z )
            self.assertEqual( 2, section.interpolants[0] )

            section = chunk.section( 102 )
            self.assertEqual( 1000, section.ZA )
            self.assertEqual( 1, section.Z )
            self.assertEqual( 5, section.interpolants[0] )

            section = chunk.MT( 1 )
            self.assertEqual( 1000, section.ZA )
            self.assertEqual( 1, section.Z )
            self.assertEqual( 5, section.interpolants[0] )

            section = chunk.MT( 2 )
            self.assertEqual( 1000, section.ZA )
            self.assertEqual( 1, section.Z )
            self.assertEqual( 2, section.interpolants[0] )

            section = chunk.MT( 102 )
            self.assertEqual( 1000, section.ZA )
            self.assertEqual( 1, section.Z )
            self.assertEqual( 5, section.interpolants[0] )

            # verify string
            self.assertEqual( self.chunk + self.valid_FEND,
                              chunk.to_string( 100 ) )

        sorted = [ Section( 1, 1000., 0.9991673,
                            [ 2 ], [ 5 ],
                            [ 1e-5, 2e+7 ], [ 1., 2. ] ),
                   Section( 2, 1000., 0.9991673,
                            [ 2 ], [ 2 ],
                            [ 1e-5, 2e+7 ], [ 3., 4. ] ),
                   Section( 102, 1000., 0.9991673,
                            [ 2 ], [ 5 ],
                            [ 1e-5, 2e+7 ], [ 5., 6. ] ) ]
        unsorted = [ Section( 102, 1000., 0.9991673,
                              [ 2 ], [ 5 ],
                              [ 1e-5, 2e+7 ], [ 5., 6. ] ),
                     Section( 2, 1000., 0.9991673,
                              [ 2 ], [ 2 ],
                              [ 1e-5, 2e+7 ], [ 3., 4. ] ),
                     Section( 1, 1000., 0.9991673,
                              [ 2 ], [ 5 ],
                              [ 1e-5, 2e+7 ], [ 1., 2. ] ) ]

        # the data is given explicitly - sorted sections
        chunk = File( sorted )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = File( unsorted )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = File.from_string( self.chunk + self.valid_FEND )

        verify_chunk( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk +
                                 self.valid_FEND + self.valid_MEND +
                                 self.valid_TEND )
        chunk = tape.material( 100 ).file( 27 ).parse()

        verify_chunk( self, chunk )

        # the data is copied
        copy = File( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # illegal SEND
        with self.assertRaises( Exception ) :

            chunk = File.from_string( self.chunk + self.invalid_FEND )

if __name__ == '__main__' :

    unittest.main()
