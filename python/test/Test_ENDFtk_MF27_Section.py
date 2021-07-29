# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF27 import Section
from ENDFtk.tree import Tape

class Test_ENDFtk_MF27_Section( unittest.TestCase ) :
    """Unit test for the Section class."""

    chunk = ( ' 1.000000+3 9.992414-1          0          0          0          0 10027502     \n'
              ' 0.000000+0 1.000000+0          0          0          1          2 10027502     \n'
              '          2          2                                             10027502     \n'
              ' 0.000000+0 1.000000+0 1.000000+9 2.000000+0                       10027502     \n' )

    valid_TPID = 'Just a tape identifier                                                          \n'
    valid_SEND = '                                                                   10027  0     \n'
    valid_FEND = '                                                                   100 0  0     \n'
    valid_MEND = '                                                                     0 0  0     \n'
    valid_TEND = '                                                                    -1 0  0     \n'
    invalid_SEND = '                                                                   10027  1     \n'

    def test_section( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 502, chunk.MT )
            self.assertEqual( 1000, chunk.ZA )
            self.assertAlmostEqual( 0.9992414, chunk.AWR )
            self.assertAlmostEqual( 0.9992414, chunk.atomic_weight_ratio )
            self.assertEqual( 1, chunk.Z )
            self.assertEqual( 1, chunk.atom_z )

            self.assertEqual( 2, chunk.NP )
            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 2, chunk.interpolants[0] );
            self.assertEqual( 2, chunk.boundaries[0] );
            self.assertEqual( 2, len( chunk.X ) )
            self.assertEqual( 2, len( chunk.H ) )
            self.assertAlmostEqual( 00., chunk.X[0] )
            self.assertAlmostEqual( 1e+9, chunk.X[1] )
            self.assertAlmostEqual( 1., chunk.H[0] )
            self.assertAlmostEqual( 2., chunk.H[1] )

            self.assertEqual( 4, chunk.NC )

            # verify string
            self.assertEqual( self.chunk + self.valid_SEND,
                              chunk.to_string( 100, 27 ) )

        # the data is given explicitly
        chunk = Section( mt = 502,  zaid = 1000, awr = 0.9992414,
                         interpolants = [ 2 ], boundaries = [ 2 ],
                         x = [ 0., 1e+9 ],
                         h = [ 1., 2. ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk + self.valid_SEND )

        verify_chunk( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.material( 100 ).file( 27 ).section( 502 ).parse()

        verify_chunk( self, chunk )

        # the data is copied
        copy = Section( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # illegal SEND
        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.chunk + self.invalid_SEND )

if __name__ == '__main__' :

    unittest.main()
