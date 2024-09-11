# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF6.LAW1 import TabulatedDistribution

class Test_ENDFtk_MF6_LAW1_TabulatedDistribution( unittest.TestCase ) :
    """Unit test for the TabulatedDistribution class."""

    chunk = ( ' 0.000000+0 1.000000-5          0          4         12          29228 6  5     \n'
              ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n'
              ' 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n' )

    invalid = ( ' 0.000000+0 1.000000-5          0          4         13          29228 6  5     \n'
                ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n'
                ' 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n'
                ' 1.300000+0                                                       9228 6  5     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 1e-5, chunk.E )
            self.assertAlmostEqual( 1e-5, chunk.incident_energy )

            self.assertEqual( 11, chunk.LANG )
            self.assertEqual( 11, chunk.representation )

            self.assertEqual( 0, chunk.ND )
            self.assertEqual( 0, chunk.number_discrete_energies )
            self.assertEqual( 4, chunk.NA )
            self.assertEqual( 4, chunk.number_angular_parameters )
            self.assertEqual( 12, chunk.NW )
            self.assertEqual( 2, chunk.NEP )
            self.assertEqual( 2, chunk.number_secondary_energies )
            self.assertEqual( 2, len( chunk.EP ) )
            self.assertEqual( 2, len( chunk.energies ) )
            self.assertAlmostEqual( 1., chunk.EP[0] )
            self.assertAlmostEqual( 7., chunk.EP[1] )
            self.assertAlmostEqual( 1., chunk.energies[0] )
            self.assertAlmostEqual( 7., chunk.energies[1] )
            self.assertEqual( 2, len( chunk.F0 ) )
            self.assertEqual( 2, len( chunk.total_emission_probabilities ) )
            self.assertAlmostEqual( 2., chunk.F0[0] )
            self.assertAlmostEqual( 8., chunk.F0[1] )
            self.assertAlmostEqual( 2., chunk.total_emission_probabilities[0] )
            self.assertAlmostEqual( 8., chunk.total_emission_probabilities[1] )
            #self.assertEqual( 2, len( chunk.MU ) )
            #self.assertEqual( 2, len( chunk.cosines ) )
            #self.assertAlmostEqual( 3., chunk.MU[0][0] )
            #self.assertAlmostEqual( 5., chunk.MU[0][1] )
            #self.assertAlmostEqual( 9., chunk.MU[1][0] )
            #self.assertAlmostEqual( 11., chunk.MU[1][1] )
            #self.assertAlmostEqual( 3., chunk.cosines[0][0] )
            #self.assertAlmostEqual( 5., chunk.cosines[0][1] )
            #self.assertAlmostEqual( 9., chunk.cosines[1][0] )
            #self.assertAlmostEqual( 11., chunk.cosines[1][1] )
            #self.assertEqual( 2, len( chunk.F ) )
            #self.assertEqual( 2, len( chunk.probabilities ) )
            #self.assertAlmostEqual( 4., chunk.F[0][0] )
            #self.assertAlmostEqual( 6., chunk.F[0][1] )
            #self.assertAlmostEqual( 10., chunk.F[1][0] )
            #self.assertAlmostEqual( 12., chunk.F[1][1] )
            #self.assertAlmostEqual( 4., chunk.probabilities[0][0] )
            #self.assertAlmostEqual( 6., chunk.probabilities[0][1] )
            #self.assertAlmostEqual( 10., chunk.probabilities[1][0] )
            #self.assertAlmostEqual( 12., chunk.probabilities[1][1] )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 6, 5 ) )

        # the data is given explicitly
        chunk = TabulatedDistribution( lang = 11, energy = 1e-5, nd = 0, na = 4,
                                       energies = [ 1., 7. ], emissions = [ 2., 8. ],
                                       cosines = [ [ 3., 5. ], [ 9., 11. ] ],
                                       probabilities = [ [ 4., 6. ], [ 10., 12. ] ] )

        verify_chunk( self, chunk )

        # the data is copied
        copy = TabulatedDistribution( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # not the same NA
        with self.assertRaises( Exception ) :

            chunk = TabulatedDistribution( lang = 11, energy = 1e-5, nd = 0, na = 3,
                                           energies = [ 1., 7. ], emissions = [ 2., 8. ],
                                           cosines = [ [ 3., 5. ], [ 9., 11. ] ],
                                           probabilities = [ [ 4., 6. ], [ 10., 12. ] ] )

if __name__ == '__main__' :

    unittest.main()
