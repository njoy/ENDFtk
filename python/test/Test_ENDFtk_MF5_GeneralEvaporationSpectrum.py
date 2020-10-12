# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF5 import GeneralEvaporationSpectrum
from ENDFtk.MF5 import EffectiveTemperature
from ENDFtk.MF5 import DistributionFunction

class Test_ENDFtk_MF4_GeneralEvaporationSpectrum( unittest.TestCase ) :
    """Unit test for the GeneralEvaporationSpectrum class."""

    chunk = ( ' 0.000000+0 0.000000+0          0          0          1          29443 5455     \n'
              '          2          2                                            9443 5455     \n'
              ' 1.000000-5 1.000000+0 3.000000+7 1.000000+0                      9443 5455     \n'
              ' 0.000000+0 0.000000+0          0          0          1          69443 5455     \n'
              '          6          1                                            9443 5455     \n'
              ' 0.000000+0 1.533738-7 1.000000+4 1.378483-6 2.000000+4 1.550360-69443 5455     \n'
              ' 1.800000+6 7.90779-31 1.810000+6 0.000000+0 1.820000+6 0.000000+09443 5455     \n' )

    invalid = ( ' 0.000000+0 0.000000+0          0          0          2          29443 5455     \n'
                '          2          2                                            9443 5455     \n'
                ' 1.000000-5 1.000000+0 3.000000+7 1.000000+0                      9443 5455     \n'
                ' 0.000000+0 0.000000+0          0          0          1          69443 5455     \n'
                '          6          1                                            9443 5455     \n'
                ' 0.000000+0 1.533738-7 1.000000+4 1.378483-6 2.000000+4 1.550360-69443 5455     \n'
                ' 1.800000+6 7.90779-31 1.810000+6 0.000000+0 1.820000+6 0.000000+09443 5455     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 5, chunk.LF )
            self.assertEqual( 5, chunk.LAW )

            t = chunk.effective_temperature
            self.assertEqual( 2, t.NP )
            self.assertEqual( 1, t.NR )
            self.assertEqual( 1, len( t.interpolants ) )
            self.assertEqual( 1, len( t.boundaries ) )
            self.assertEqual( 2, t.interpolants[0] )
            self.assertEqual( 2, t.boundaries[0] )
            self.assertEqual( 2, len( t.E ) )
            self.assertEqual( 2, len( t.energies ) )
            self.assertEqual( 2, len( t.thetas ) )
            self.assertAlmostEqual( 1e-5, t.E[0] )
            self.assertAlmostEqual( 3e+7, t.E[1] )
            self.assertAlmostEqual( 1e-5, t.energies[0] )
            self.assertAlmostEqual( 3e+7, t.energies[1] )
            self.assertAlmostEqual( 1.0, t.thetas[0] )
            self.assertAlmostEqual( 1.0, t.thetas[1] )

            df = chunk.distribution_function
            self.assertEqual( 6, df.NP )
            self.assertEqual( 1, df.NR )
            self.assertEqual( 1, len( df.interpolants ) )
            self.assertEqual( 1, len( df.boundaries ) )
            self.assertEqual( 1, df.interpolants[0] )
            self.assertEqual( 6, df.boundaries[0] )
            self.assertEqual( 6, len( df.X ) )
            self.assertEqual( 6, len( df.G ) )
            self.assertAlmostEqual( 0.0, df.X[0] )
            self.assertAlmostEqual( 1e+4, df.X[1] )
            self.assertAlmostEqual( 2e+4, df.X[2] )
            self.assertAlmostEqual( 1.8e+6, df.X[3] )
            self.assertAlmostEqual( 1.81e+6, df.X[4] )
            self.assertAlmostEqual( 1.82e+6, df.X[5] )
            self.assertAlmostEqual( 1.533738e-7, df.G[0] )
            self.assertAlmostEqual( 1.378483e-6, df.G[1] )
            self.assertAlmostEqual( 1.550360e-6, df.G[2] )
            self.assertAlmostEqual( 7.90779e-31, df.G[3] )
            self.assertAlmostEqual( 0.0, df.G[4] )
            self.assertAlmostEqual( 0.0, df.G[5] )

            self.assertEqual( 7, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9443, 5, 455 ) )

        # the data is given explicitly
        chunk = GeneralEvaporationSpectrum(
                    temperature = EffectiveTemperature(
                                       [ 2 ], [ 2 ], [ 1e-5, 3e+7 ], [ 1.0, 1.0 ] ),
                    distribution = DistributionFunction(
                                       [ 6 ], [ 1 ],
                                       [ 0.0, 1e+4, 2e+4, 1.8e+6, 1.81e+6, 1.82e+6 ],
                                       [ 1.533738e-7, 1.378483e-6, 1.550360e-6,
                                         7.90779e-31, 0.0, 0.0 ] ) )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = GeneralEvaporationSpectrum.from_string( self.chunk, 9443, 5, 455 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = GeneralEvaporationSpectrum( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        with self.assertRaises( Exception ) :

            chunk = GeneralEvaporationSpectrum.from_string( self.invalid, 9443, 5, 455 )

if __name__ == '__main__' :

    unittest.main()
