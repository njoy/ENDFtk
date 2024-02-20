# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF3 import File
from ENDFtk.MF3 import Section
from ENDFtk.tree import Tape

class Test_ENDFtk_MF3_File( unittest.TestCase ) :
    """Unit test for the File class."""

    chunk = ( ' 1.001000+3 9.991673-1          0          0          0          0 125 3  1     \n'
              ' 0.000000+0 0.000000+0          0          0          1          2 125 3  1     \n'
              '          2          5                                             125 3  1     \n'
              ' 1.000000-5 1.000000+0 2.000000+7 2.000000+0                       125 3  1     \n'
              '                                                                   125 3  0     \n'
              ' 1.001000+3 9.991673-1          0          0          0          0 125 3  2     \n'
              ' 0.000000+0 0.000000+0          0          0          1          2 125 3  2     \n'
              '          2          2                                             125 3  2     \n'
              ' 1.000000-5 3.000000+0 2.000000+7 4.000000+0                       125 3  2     \n'
              '                                                                   125 3  0     \n'
              ' 1.001000+3 9.991673-1          0          0          0          0 125 3102     \n'
              ' 2.224631+6 2.224631+6          0          0          1          2 125 3102     \n'
              '          2          5                                             125 3102     \n'
              ' 1.000000-5 5.000000+0 2.000000+7 6.000000+0                       125 3102     \n'
              '                                                                   125 3  0     \n' )

    valid_TPID = 'Just a tape identifier                                                          \n'
    valid_FEND = '                                                                   125 0  0     \n'
    valid_MEND = '                                                                     0 0  0     \n'
    valid_TEND = '                                                                    -1 0  0     \n'
    invalid_FEND = '                                                                   125 3  1     \n'

    def test_file( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 3, chunk.MF )
            self.assertEqual( 3, chunk.file_number )

            self.assertEqual( True, chunk.has_MT( 1 ) )
            self.assertEqual( True, chunk.has_MT( 2 ) )
            self.assertEqual( True, chunk.has_MT( 102 ) )
            self.assertEqual( True, chunk.has_section( 1 ) )
            self.assertEqual( True, chunk.has_section( 2 ) )
            self.assertEqual( True, chunk.has_section( 102 ) )

            self.assertEqual( False, chunk.has_MT( 12 ) )
            self.assertEqual( False, chunk.has_section( 12 ) )

            section = chunk.section( 1 )
            self.assertEqual( 1001, section.ZA )
            self.assertEqual( 0.0, section.QM )
            self.assertEqual( 0.0, section.QI )
            self.assertEqual( 5, section.interpolants[0] )

            section = chunk.section( 2 )
            self.assertEqual( 1001, section.ZA )
            self.assertEqual( 0.0, section.QM )
            self.assertEqual( 0.0, section.QI )
            self.assertEqual( 2, section.interpolants[0] )

            section = chunk.section( 102 )
            self.assertEqual( 1001, section.ZA )
            self.assertAlmostEqual( 2.224631e+6, section.QM )
            self.assertAlmostEqual( 2.224631e+6, section.QI )
            self.assertEqual( 5, section.interpolants[0] )

            section = chunk.MT( 1 )
            self.assertEqual( 1001, section.ZA )
            self.assertEqual( 0.0, section.QM )
            self.assertEqual( 0.0, section.QI )
            self.assertEqual( 5, section.interpolants[0] )

            section = chunk.MT( 2 )
            self.assertEqual( 1001, section.ZA )
            self.assertEqual( 0.0, section.QM )
            self.assertEqual( 0.0, section.QI )
            self.assertEqual( 2, section.interpolants[0] )

            section = chunk.MT( 102 )
            self.assertEqual( 1001, section.ZA )
            self.assertAlmostEqual( 2.224631e+6, section.QM )
            self.assertAlmostEqual( 2.224631e+6, section.QI )
            self.assertEqual( 5, section.interpolants[0] )

            self.assertEqual( 1001, chunk.section( 1 ).ZA )
            self.assertEqual( 0.0, chunk.section( 1 ).QM )
            self.assertEqual( 0.0, chunk.section( 1 ).QI )
            self.assertEqual( 5, chunk.section( 1 ).interpolants[0] )

            self.assertEqual( 1001, chunk.section( 2 ).ZA )
            self.assertEqual( 0.0, chunk.section( 2 ).QM )
            self.assertEqual( 0.0, chunk.section( 2 ).QI )
            self.assertEqual( 2, chunk.section( 2 ).interpolants[0] )

            self.assertEqual( 1001, chunk.section( 102 ).ZA )
            self.assertAlmostEqual( 2.224631e+6, chunk.section( 102 ).QM )
            self.assertAlmostEqual( 2.224631e+6, chunk.section( 102 ).QI )
            self.assertEqual( 5, chunk.section( 102 ).interpolants[0] )

            self.assertEqual( 1001, chunk.MT( 1 ).ZA )
            self.assertEqual( 0.0, chunk.MT( 1 ).QM )
            self.assertEqual( 0.0, chunk.MT( 1 ).QI )
            self.assertEqual( 5, chunk.MT( 1 ).interpolants[0] )

            self.assertEqual( 1001, chunk.MT( 2 ).ZA )
            self.assertEqual( 0.0, chunk.MT( 2 ).QM )
            self.assertEqual( 0.0, chunk.MT( 2 ).QI )
            self.assertEqual( 2, chunk.MT( 2 ).interpolants[0] )

            self.assertEqual( 1001, chunk.MT( 102 ).ZA )
            self.assertAlmostEqual( 2.224631e+6, chunk.MT( 102 ).QM )
            self.assertAlmostEqual( 2.224631e+6, chunk.MT( 102 ).QI )
            self.assertEqual( 5, chunk.MT( 102 ).interpolants[0] )

            # verify string
            self.assertEqual( self.chunk + self.valid_FEND,
                              chunk.to_string( 125 ) )

        sorted = [ Section( 1, 1001, 0.9991673, 0., 0., 0,
                            [ 2 ], [ 5 ],
                            [ 1e-5, 2e+7 ], [ 1., 2. ] ),
                   Section( 2, 1001, 0.9991673, 0., 0., 0,
                            [ 2 ], [ 2 ],
                            [ 1e-5, 2e+7 ], [ 3., 4. ] ),
                   Section( 102, 1001, 0.9991673, 2.224631e+6, 2.224631e+6, 0,
                            [ 2 ], [ 5 ],
                            [ 1e-5, 2e+7 ], [ 5., 6. ] ) ]
        unsorted = [ Section( 102, 1001, 0.9991673, 2.224631e+6, 2.224631e+6, 0,
                              [ 2 ], [ 5 ],
                              [ 1e-5, 2e+7 ], [ 5., 6. ] ),
                     Section( 2, 1001, 0.9991673, 0., 0., 0,
                              [ 2 ], [ 2 ],
                              [ 1e-5, 2e+7 ], [ 3., 4. ] ),
                     Section( 1, 1001, 0.9991673, 0., 0., 0,
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
        chunk = tape.material( 125 ).file( 3 ).parse()

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
