# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF6.LAW2 import LegendreCoefficients

class Test_ENDFtk_MF6_LAW2_LegendreCoefficients( unittest.TestCase ) :
    """Unit test for the LegendreCoefficients class."""

    chunk = ( ' 0.000000+0 1.000000-5          0          0          4          49228 6  5     \n'
              ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      9228 6  5     \n' )

    invalid = ( ' 0.000000+0 1.000000-5          1          0          4          49228 6  5     \n'
                ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      9228 6  5     \n' )

    invalid_size = ( ' 0.000000+0 1.000000-5          0          0          4          39228 6  5     \n'
                     ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      9228 6  5     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 1e-5, chunk.E )
            self.assertAlmostEqual( 1e-5, chunk.incident_energy )

            self.assertEqual( 0, chunk.LANG )
            self.assertEqual( 4, chunk.NW )
            self.assertEqual( 4, chunk.NL )
            self.assertEqual( 4, chunk.legendre_order )
            self.assertEqual( 4, len( chunk.A ) )
            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( 1., chunk.A[0] )
            self.assertAlmostEqual( 2., chunk.A[1] )
            self.assertAlmostEqual( 3., chunk.A[2] )
            self.assertAlmostEqual( 4., chunk.A[3] )
            self.assertAlmostEqual( 1., chunk.coefficients[0] )
            self.assertAlmostEqual( 2., chunk.coefficients[1] )
            self.assertAlmostEqual( 3., chunk.coefficients[2] )
            self.assertAlmostEqual( 4., chunk.coefficients[3] )

            self.assertEqual( 2, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 6, 5 ) )

        # the data is given explicitly
        chunk = LegendreCoefficients( energy = 1e-5,
                                      coefficients = [ 1, 2, 3, 4 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = LegendreCoefficients.from_string( self.chunk, 9228, 6, 5 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = LegendreCoefficients( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        with self.assertRaises( Exception ) :

            chunk = LegendreCoefficients.from_string( self.invalid, 9228, 6, 5 )

        with self.assertRaises( Exception ) :

            chunk = LegendreCoefficients.from_string( self.invalid_size, 9228, 6, 5 )

if __name__ == '__main__' :

    unittest.main()
