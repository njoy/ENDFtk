# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF26.LAW1 import LegendreCoefficients

class Test_ENDFtk_MF26_LAW1_LegendreCoefficients( unittest.TestCase ) :
    """Unit test for the LegendreCoefficients class."""

    chunk = ( ' 0.000000+0 1.000000-5          0          1          6          2922826  5     \n'
              ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+0922826  5     \n' )

    invalid = ( ' 0.000000+0 1.000000-5          0          1          5          2922826  5     \n'
                ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0           922826  5     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 1, chunk.LANG )
            self.assertEqual( 1, chunk.representation )
            self.assertAlmostEqual( 1e-5, chunk.E )
            self.assertAlmostEqual( 1e-5, chunk.incident_energy )

            self.assertEqual( 0, chunk.ND )
            self.assertEqual( 0, chunk.number_discrete_energies )
            self.assertEqual( 1, chunk.NA )
            self.assertEqual( 1, chunk.number_angular_parameters )
            self.assertEqual( 1, chunk.NL )
            self.assertEqual( 1, chunk.legendre_order )
            self.assertEqual( 6, chunk.NW )
            self.assertEqual( 2, chunk.NEP )
            self.assertEqual( 2, chunk.number_secondary_energies )
            self.assertEqual( 2, len( chunk.EP ) )
            self.assertEqual( 2, len( chunk.energies ) )
            self.assertAlmostEqual( 1., chunk.EP[0] )
            self.assertAlmostEqual( 4., chunk.EP[1] )
            self.assertAlmostEqual( 1., chunk.energies[0] )
            self.assertAlmostEqual( 4., chunk.energies[1] )
            self.assertEqual( 2, len( chunk.A ) )
            self.assertEqual( 2, len( chunk.coefficients ) )
            self.assertAlmostEqual( 2., chunk.A[0][0] )
            self.assertAlmostEqual( 3., chunk.A[0][1] )
            self.assertAlmostEqual( 5., chunk.A[1][0] )
            self.assertAlmostEqual( 6., chunk.A[1][1] )
            self.assertAlmostEqual( 2., chunk.coefficients[0][0] )
            self.assertAlmostEqual( 3., chunk.coefficients[0][1] )
            self.assertAlmostEqual( 5., chunk.coefficients[1][0] )
            self.assertAlmostEqual( 6., chunk.coefficients[1][1] )
            self.assertEqual( 2, len( chunk.F0 ) )
            self.assertEqual( 2, len( chunk.total_emission_probabilities ) )
            self.assertAlmostEqual( 2., chunk.F0[0] )
            self.assertAlmostEqual( 5., chunk.F0[1] )
            self.assertAlmostEqual( 2., chunk.total_emission_probabilities[0] )
            self.assertAlmostEqual( 5., chunk.total_emission_probabilities[1] )

            self.assertEqual( 2, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 26, 5 ) )

        # the data is given explicitly
        chunk = LegendreCoefficients( energy = 1e-5, nd = 0, na = 1,
                                      energies = [ 1., 4. ],
                                      coefficients = [ [ 2., 3. ], [ 5., 6. ] ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = LegendreCoefficients.from_string( self.chunk, 9228, 26, 5 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = LegendreCoefficients( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # not the same NA
        with self.assertRaises( Exception ) :

            chunk = LegendreCoefficients( energy = 1e-5, nd = 0, na = 1,
                                          energies = [ 1., 4. ],
                                          coefficients = [ [ 2., 3., 3 ], [ 5., 6. ] ] )

        # not the same NEP
        with self.assertRaises( Exception ) :

            chunk = LegendreCoefficients( energy = 1e-5, nd = 0, na = 1,
                                          energies = [ 1., 4. ],
                                          coefficients = [ [ 2., 3. ], [ 5., 6. ], [ 7., 8. ] ] )

        with self.assertRaises( Exception ) :

            chunk = LegendreCoefficients.from_string( self.invalid, 9228, 26, 5 )

if __name__ == '__main__' :

    unittest.main()
