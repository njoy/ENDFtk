# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF6 import NBodyPhaseSpace

class Test_ENDFtk_MF6_NBodyPhaseSpace( unittest.TestCase ) :
    """Unit test for the NBodyPhaseSpace class."""

    chunk = ( ' 5.000000+0 0.000000+0          0          0          0          49228 6  5     \n' )

    invalid = ( ' 5.000000+0 0.000000+0 1        0          0          0          49228 6  5     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 6, chunk.LAW )

            self.assertAlmostEqual( 5., chunk.APSX )
            self.assertAlmostEqual( 5., chunk.total_mass )
            self.assertAlmostEqual( 4, chunk.NPSX )
            self.assertAlmostEqual( 4, chunk.number_particles )

            self.assertEqual( 1, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 6, 5 ) )

        # the data is given explicitly
        chunk = NBodyPhaseSpace( apsx = 5., npsx = 4 )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = NBodyPhaseSpace.from_string( self.chunk, 9228, 6, 5 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = NBodyPhaseSpace( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # wrong boundaries
        with self.assertRaises( Exception ) :

            chunk = NBodyPhaseSpace( zap = 1001., awp = 0.9986234, lip = 0, law = 1,
                                  boundaries = [ 4, 5 ], interpolants = [ 2 ],
                                  energies = [ 1e-5, 1.1e+7, 1.147e+7, 3e+7 ],
                                  multiplicities = [ 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 ] )

        with self.assertRaises( Exception ) :

            chunk = NBodyPhaseSpace.from_string( self.invalid, 9228, 6, 5 )

if __name__ == '__main__' :

    unittest.main()
