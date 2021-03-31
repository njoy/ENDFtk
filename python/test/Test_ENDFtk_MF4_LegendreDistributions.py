# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF4 import LegendreCoefficients
from ENDFtk.MF4 import LegendreDistributions

class Test_ENDFtk_MF4_LegendreDistributions( unittest.TestCase ) :
    """Unit test for the LegendreDistributions class."""

    chunk = ( ' 0.000000+0 0.000000+0          0          0          1          29228 4  2     \n'
              '          2          1                                            9228 4  2     \n'
              ' 0.000000+0 1.000000-5          0          0          3          09228 4  2     \n'
              ' 7.392510-5 8.477139-9 1.17106-13                                 9228 4  2     \n'
              ' 0.000000+0 2.000000+7          0          0          2          09228 4  2     \n'
              ' 2.874390-2 3.19645-11                                            9228 4  2     \n' )

    invalid = ( ' 0.000000+0 0.000000+0          0          0          3          29228 4  2     \n'
                '          2          1                                            9228 4  2     \n'
                ' 0.000000+0 1.000000-5          0          0          3          09228 4  2     \n'
                ' 7.392510-5 8.477139-9 1.17106-13                                 9228 4  2     \n'
                ' 0.000000+0 2.000000+7          0          0          2          09228 4  2     \n'
                ' 2.874390-2 3.19645-11                                            9228 4  2     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 1, chunk.LTT )
            self.assertEqual( 1, chunk.LAW )

            self.assertEqual( 2, chunk.NE )
            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, chunk.interpolants[0] );
            self.assertEqual( 2, chunk.boundaries[0] );

            self.assertEqual( 2, len( chunk.incident_energies ) )
            self.assertEqual( 2, len( chunk.angular_distributions ) )

            self.assertAlmostEqual( 1e-5, chunk.incident_energies[0] )
            self.assertAlmostEqual( 2e+7, chunk.incident_energies[1] )

            distributions = chunk.angular_distributions

            d = distributions[0];
            self.assertAlmostEqual( 1e-5, d.E )
            self.assertAlmostEqual( 1e-5, d.incident_energy )
            self.assertEqual( 3, d.NL )
            self.assertEqual( 3, d.legendre_order )
            self.assertEqual( 3, len( d.coefficients ) )
            self.assertAlmostEqual( 7.392510e-5 , d.coefficients[0] )
            self.assertAlmostEqual( 8.477139e-9, d.coefficients[1] )
            self.assertAlmostEqual( 1.17106e-13, d.coefficients[2] )

            d = distributions[1];
            self.assertAlmostEqual( 2e+7, d.E )
            self.assertAlmostEqual( 2e+7, d.incident_energy )
            self.assertEqual( 2, d.NL )
            self.assertEqual( 2, d.legendre_order )
            self.assertEqual( 2, len( d.coefficients ) )
            self.assertAlmostEqual( 2.874390e-2  , d.coefficients[0] )
            self.assertAlmostEqual( 3.19645e-11, d.coefficients[1] )

            self.assertEqual( 6, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 4, 2 ) )

        # the data is given explicitly
        chunk = LegendreDistributions(
                  boundaries = [ 2 ], interpolants = [ 1 ],
                  distributions = [ LegendreCoefficients( 1e-5, [ 7.392510e-5, 8.477139e-9, 1.17106e-13 ] ),
                                    LegendreCoefficients( 2e+7, [ 2.874390e-2, 3.19645e-11 ] ) ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = LegendreDistributions.from_string( self.chunk, 9228, 4, 2 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = LegendreDistributions( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        with self.assertRaises( Exception ) :

            chunk = LegendreDistributions(
                      boundaries = [ 2, 4 ], interpolants = [ 1 ],
                      distributions = [ LegendreCoefficients( 1e-5, [ 7.392510e-5, 8.477139e-9, 1.17106e-13 ] ),
                                        LegendreCoefficients( 2e+7, [ 2.874390e-2, 3.19645e-11 ] ) ] )

        with self.assertRaises( Exception ) :

            chunk = LegendreDistributions(
                      boundaries = [ 2 ], interpolants = [ 1, 2 ],
                      distributions = [ LegendreCoefficients( 1e-5, [ 7.392510e-5, 8.477139e-9, 1.17106e-13 ] ),
                                        LegendreCoefficients( 2e+7, [ 2.874390e-2, 3.19645e-11 ] ) ] )

        with self.assertRaises( Exception ) :

            chunk = LegendreDistributions(
                      boundaries = [ 2 ], interpolants = [ 1 ],
                      distributions = [ LegendreCoefficients( 1e-5, [ 7.392510e-5, 8.477139e-9, 1.17106e-13 ] ) ] )

        with self.assertRaises( Exception ) :

            chunk = LegendreDistributions.from_string( self.invalid, 9228, 2, 151 )

if __name__ == '__main__' :

    unittest.main()
