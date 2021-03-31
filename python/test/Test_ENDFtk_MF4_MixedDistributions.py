# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF4 import LegendreCoefficients
from ENDFtk.MF4 import TabulatedDistribution
from ENDFtk.MF4 import LegendreDistributions
from ENDFtk.MF4 import TabulatedDistributions
from ENDFtk.MF4 import MixedDistributions

class Test_ENDFtk_MF4_MixedDistributions( unittest.TestCase ) :
    """Unit test for the MixedDistributions class."""

    chunk = ( ' 0.000000+0 0.000000+0          0          0          1          29228 4  2     \n'
              '          2          1                                            9228 4  2     \n'
              ' 0.000000+0 1.000000-5          0          0          3          09228 4  2     \n'
              ' 7.392510-5 8.477139-9 1.17106-13                                 9228 4  2     \n'
              ' 0.000000+0 1.000000+6          0          0          2          09228 4  2     \n'
              ' 2.874390-2 3.19645-11                                            9228 4  2     \n'
              ' 0.000000+0 0.000000+0          0          0          1          29228 4  2     \n'
              '          2          5                                            9228 4  2     \n'
              ' 0.000000+0 1.000000+6          0          0          1          29228 4  2     \n'
              '          2          2                                            9228 4  2     \n'
              '-1.000000+0 5.000000-1 1.000000+0 5.000000-1                      9228 4  2     \n'
              ' 0.000000+0 2.000000+7          0          0          1          39228 4  2     \n'
              '          3          2                                            9228 4  2     \n'
              '-1.000000+0 0.000000+0 0.000000+0 1.000000+0 1.000000+0 0.000000+09228 4  2     \n' )

    invalid = ( ' 0.000000+0 0.000000+0          0          0          1          29228 4  2     \n'
                '          2          1                                            9228 4  2     \n'
                ' 0.000000+0 1.000000-5          0          0          3          09228 4  2     \n'
                ' 7.392510-5 8.477139-9 1.17106-13                                 9228 4  2     \n'
                ' 0.000000+0 1.000000+6          0          0          2          09228 4  2     \n'
                ' 2.874390-2 3.19645-11                                            9228 4  2     \n'
                ' 0.000000+0 0.000000+0          0          0          1          29228 4  2     \n'
                '          2          5                                            9228 4  2     \n'
                ' 0.000000+0 1.000000+7          0          0          1          29228 4  2     \n'
                '          2          2                                            9228 4  2     \n'
                '-1.000000+0 5.000000-1 1.000000+0 5.000000-1                      9228 4  2     \n'
                ' 0.000000+0 2.000000+7          0          0          1          39228 4  2     \n'
                '          3          2                                            9228 4  2     \n'
                '-1.000000+0 0.000000+0 0.000000+0 1.000000+0 1.000000+0 0.000000+09228 4  2     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 3, chunk.LTT )
            self.assertEqual( 3, chunk.LAW )

            self.assertEqual( 2, chunk.NR )
            self.assertEqual( 4, chunk.NE )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 1, chunk.interpolants[0] )
            self.assertEqual( 5, chunk.interpolants[1] )
            self.assertEqual( 2, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )

            distributions = chunk.angular_distributions

            self.assertEqual( True, isinstance( distributions[0], LegendreCoefficients ) )
            self.assertEqual( True, isinstance( distributions[1], LegendreCoefficients ) )
            self.assertEqual( True, isinstance( distributions[2], TabulatedDistribution ) )
            self.assertEqual( True, isinstance( distributions[3], TabulatedDistribution ) )

            self.assertAlmostEqual( 1e-5, distributions[0].E )
            self.assertAlmostEqual( 1e+6, distributions[1].E )
            self.assertAlmostEqual( 1e+6, distributions[2].E )
            self.assertAlmostEqual( 2e+7, distributions[3].E )
            self.assertAlmostEqual( 1e-5, distributions[0].incident_energy )
            self.assertAlmostEqual( 1e+6, distributions[1].incident_energy )
            self.assertAlmostEqual( 1e+6, distributions[2].incident_energy )
            self.assertAlmostEqual( 2e+7, distributions[3].incident_energy )

            self.assertEqual( 2, chunk.legendre.NE )
            self.assertEqual( 1, chunk.legendre.NR )
            self.assertEqual( 1, len( chunk.legendre.interpolants ) )
            self.assertEqual( 1, len( chunk.legendre.boundaries ) )
            self.assertEqual( 1, chunk.legendre.interpolants[0] )
            self.assertEqual( 2, chunk.legendre.boundaries[0] )

            ldistributions = chunk.legendre.angular_distributions

            ld = ldistributions[0]
            self.assertAlmostEqual( 1e-5, ld.E )
            self.assertAlmostEqual( 1e-5, ld.incident_energy )
            self.assertEqual( 3, ld.NL )
            self.assertEqual( 3, ld.legendre_order )
            self.assertEqual( 3, len( ld.coefficients ) )
            self.assertAlmostEqual( 7.392510e-5, ld.coefficients[0] )
            self.assertAlmostEqual( 8.477139e-9, ld.coefficients[1] )
            self.assertAlmostEqual( 1.17106e-13, ld.coefficients[2] )

            ld = ldistributions[1]
            self.assertAlmostEqual( 1e+6, ld.E )
            self.assertAlmostEqual( 1e+6, ld.incident_energy )
            self.assertEqual( 2, ld.NL )
            self.assertEqual( 2, ld.legendre_order )
            self.assertEqual( 2, len( ld.coefficients ) )
            self.assertAlmostEqual( 2.874390e-2, ld.coefficients[0] )
            self.assertAlmostEqual( 3.19645e-11, ld.coefficients[1] )

            self.assertEqual( 2, chunk.tabulated.NE )
            self.assertEqual( 1, chunk.tabulated.NR )
            self.assertEqual( 1, len( chunk.tabulated.interpolants ) )
            self.assertEqual( 1, len( chunk.tabulated.boundaries ) )
            self.assertEqual( 5, chunk.tabulated.interpolants[0] )
            self.assertEqual( 2, chunk.tabulated.boundaries[0] )

            tdistributions = chunk.tabulated.angular_distributions

            td = tdistributions[0]
            self.assertAlmostEqual( 1e+6, td.E )
            self.assertAlmostEqual( 1e+6, td.incident_energy )
            self.assertEqual( 2, td.NP )
            self.assertEqual( 1, td.NR )
            self.assertEqual( 1, len( td.boundaries ) )
            self.assertEqual( 1, len( td.interpolants ) )
            self.assertEqual( 2, td.boundaries[0] )
            self.assertEqual( 2, td.interpolants[0] )
            self.assertEqual( 2, len( td.cosines ) )
            self.assertAlmostEqual( -1.0, td.cosines[0] )
            self.assertAlmostEqual( 1.0, td.cosines[1] )
            self.assertEqual( 2, len( td.probabilities ) )
            self.assertAlmostEqual( 0.5 , td.probabilities[0] )
            self.assertAlmostEqual( 0.5, td.probabilities[1] )

            td = tdistributions[1]
            self.assertAlmostEqual( 2e+7, td.E )
            self.assertAlmostEqual( 2e+7, td.incident_energy )
            self.assertEqual( 3, td.NP )
            self.assertEqual( 1, td.NR )
            self.assertEqual( 1, len( td.boundaries ) )
            self.assertEqual( 1, len( td.interpolants ) )
            self.assertEqual( 3, td.boundaries[0] )
            self.assertEqual( 2, td.interpolants[0] )
            self.assertEqual( 3, len( td.cosines ) )
            self.assertAlmostEqual( -1.0 , td.cosines[0] )
            self.assertAlmostEqual( 0.0, td.cosines[1] )
            self.assertAlmostEqual( 1.0, td.cosines[2] )
            self.assertEqual( 3, len( td.probabilities ) )
            self.assertAlmostEqual( 0.0 , td.probabilities[0] )
            self.assertAlmostEqual( 1.0, td.probabilities[1] )
            self.assertAlmostEqual( 0.0, td.probabilities[2] )

            self.assertEqual( 14, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 4, 2 ) )

        # the data is given explicitly
        chunk = MixedDistributions(
                  legendre = LegendreDistributions(
                               [ 2 ], [ 1 ],
        	                   [ LegendreCoefficients( 1e-5, [ 7.392510e-5, 8.477139e-9, 1.17106e-13 ] ),
                                 LegendreCoefficients( 1e+6, [ 2.874390e-2, 3.19645e-11 ] ) ] ),
                  tabulated  = TabulatedDistributions(
                                 [ 2 ], [ 5 ],
                                 [ TabulatedDistribution( 1e+6, [ 2 ], [ 2 ], [ -1.0, 1.0 ], [ 0.5, 0.5 ] ),
                                   TabulatedDistribution( 2e+7, [ 3 ], [ 2 ], [ -1.0, 0.0, 1.0 ], [ 0.0, 1.0, 0.0 ] ) ] ) )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = MixedDistributions.from_string( self.chunk, 9228, 4, 2 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = MixedDistributions( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # incident energy boundary mismatch
        with self.assertRaises( Exception ) :

            chunk = MixedDistributions(
                      legendre = LegendreDistributions(
                                   [ 2 ], [ 1 ],
            	                   [ LegendreCoefficients( 1e-5, [ 7.392510e-5, 8.477139e-9, 1.17106e-13 ] ),
                                     LegendreCoefficients( 1e+6, [ 2.874390e-2, 3.19645e-11 ] ) ] ),
                      tabulated  = TabulatedDistributions(
                                     [ 2 ], [ 5 ],
                                     [ TabulatedDistribution( 2e+6, [ 2 ], [ 2 ], [ -1.0, 1.0 ], [ 0.5, 0.5 ] ),
                                       TabulatedDistribution( 2e+7, [ 3 ], [ 2 ], [ -1.0, 0.0, 1.0 ], [ 0.0, 1.0, 0.0 ] ) ] ) )

        with self.assertRaises( Exception ) :

            chunk = MixedDistributions.from_string( self.invalid, 9228, 2, 151 )

if __name__ == '__main__' :

    unittest.main()
