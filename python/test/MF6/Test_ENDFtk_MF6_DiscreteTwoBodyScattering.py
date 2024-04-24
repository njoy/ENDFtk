# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF6 import DiscreteTwoBodyScattering
from ENDFtk.MF6.LAW2 import LegendreCoefficients
from ENDFtk.MF6.LAW2 import TabulatedDistribution

class Test_ENDFtk_MF6_DiscreteTwoBodyScattering( unittest.TestCase ) :
    """Unit test for the DiscreteTwoBodyScattering class."""

    chunk = ( ' 0.000000+0 0.000000+0          0          0          1          29228 6  5     \n'
              '          2          1                                            9228 6  5     \n'
              ' 0.000000+0 1.000000-5          0          0          4          49228 6  5     \n'
              ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      9228 6  5     \n'
              ' 0.000000+0 2.000000+7         12          0          6          39228 6  5     \n'
              ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n' )

    invalid = ( ' 0.000000+0 0.000000+0          0          0          1          29228 6  5     \n'
                '          2          1                                            9228 6  5     \n'
                ' 0.000000+0 1.000000-5          1          0          4          49228 6  5     \n'
                ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      9228 6  5     \n'
                ' 0.000000+0 2.000000+7         12          0          6          39228 6  5     \n'
                ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.LAW )
            self.assertEqual( 2, chunk.NE )
            self.assertEqual( 2, chunk.number_incident_energies )
            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, chunk.number_interpolation_regions )
            self.assertEqual( 1, len( chunk.INT ) )
            self.assertEqual( 1, len( chunk.NBT ) )
            self.assertEqual( 1, chunk.INT[0] )
            self.assertEqual( 2, chunk.NBT[0] )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, chunk.interpolants[0] )
            self.assertEqual( 2, chunk.boundaries[0] )

            self.assertEqual( 2, len( chunk.E ) )
            self.assertEqual( 2, len( chunk.incident_energies ) )
            self.assertAlmostEqual( 1e-5, chunk.E[0] )
            self.assertAlmostEqual( 2e+7, chunk.E[1] )
            self.assertAlmostEqual( 1e-5, chunk.incident_energies[0] )
            self.assertAlmostEqual( 2e+7, chunk.incident_energies[1] )

            distributions = chunk.distributions
            self.assertEqual( True, isinstance( distributions[0], LegendreCoefficients ) )
            self.assertEqual( True, isinstance( distributions[1], TabulatedDistribution ) )

            subsection1 = distributions[0]
            self.assertAlmostEqual( 1e-5, subsection1.E )
            self.assertAlmostEqual( 1e-5, subsection1.incident_energy )
            self.assertEqual( 0, subsection1.LANG )
            self.assertEqual( 4, subsection1.NW )
            self.assertEqual( 4, subsection1.NL )
            self.assertEqual( 4, len( subsection1.A ) )
            self.assertEqual( 4, len( subsection1.coefficients ) )
            self.assertAlmostEqual( 1., subsection1.A[0] )
            self.assertAlmostEqual( 2., subsection1.A[1] )
            self.assertAlmostEqual( 3., subsection1.A[2] )
            self.assertAlmostEqual( 4., subsection1.A[3] )
            self.assertAlmostEqual( 1., subsection1.coefficients[0] )
            self.assertAlmostEqual( 2., subsection1.coefficients[1] )
            self.assertAlmostEqual( 3., subsection1.coefficients[2] )
            self.assertAlmostEqual( 4., subsection1.coefficients[3] )

            subsection2 = distributions[1]
            self.assertAlmostEqual( 2e+7, subsection2.E )
            self.assertAlmostEqual( 2e+7, subsection2.incident_energy )
            self.assertEqual( 12, subsection2.LANG )
            self.assertEqual( 6, subsection2.NW )
            self.assertEqual( 3, subsection2.NL )
            self.assertEqual( 3, len( subsection2.MU ) )
            self.assertEqual( 3, len( subsection2.cosines ) )
            self.assertAlmostEqual( 1., subsection2.MU[0] )
            self.assertAlmostEqual( 3., subsection2.MU[1] )
            self.assertAlmostEqual( 5., subsection2.MU[2] )
            self.assertAlmostEqual( 1., subsection2.cosines[0] )
            self.assertAlmostEqual( 3., subsection2.cosines[1] )
            self.assertAlmostEqual( 5., subsection2.cosines[2] )
            self.assertEqual( 3, len( subsection2.F ) )
            self.assertEqual( 3, len( subsection2.probabilities ) )
            self.assertAlmostEqual( 2., subsection2.F[0] )
            self.assertAlmostEqual( 4., subsection2.F[1] )
            self.assertAlmostEqual( 6., subsection2.F[2] )
            self.assertAlmostEqual( 2., subsection2.probabilities[0] )
            self.assertAlmostEqual( 4., subsection2.probabilities[1] )
            self.assertAlmostEqual( 6., subsection2.probabilities[2] )

            self.assertEqual( 6, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 6, 5 ) )

        # the data is given explicitly
        chunk = DiscreteTwoBodyScattering(
                    boundaries = [ 2 ], interpolants = [ 1 ],
                    distributions = [
                        LegendreCoefficients( 1e-5, [ 1., 2., 3., 4. ] ),
                        TabulatedDistribution( 2e+7, 12, [1., 3., 5. ], [ 2., 4., 6.] ) ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = DiscreteTwoBodyScattering.from_string( self.chunk, 9228, 6, 5 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = DiscreteTwoBodyScattering( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # wrong boundaries
        with self.assertRaises( Exception ) :

            chunk = DiscreteTwoBodyScattering(
                        boundaries = [ 2, 4 ], interpolants = [ 1 ],
                        distributions = [
                            LegendreCoefficients( 1e-5, [ 1., 2., 3., 4. ] ),
                            TabulatedDistribution( 2e+7, 12, [1., 3., 5. ], [ 2., 4., 6.] ) ] )

        with self.assertRaises( Exception ) :

            chunk = DiscreteTwoBodyScattering.from_string( self.invalid, 9228, 6, 5 )

if __name__ == '__main__' :

    unittest.main()
