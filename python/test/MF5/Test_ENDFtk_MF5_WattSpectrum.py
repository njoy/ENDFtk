# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF5 import Parameter
from ENDFtk.MF5 import WattSpectrum

class Test_ENDFtk_MF5_WattSpectrum( unittest.TestCase ) :
    """Unit test for the WattSpectrum class."""

    chunk = ( ' 0.000000+0 0.000000+0          0          0          1          39222 5 18     \n'
              '          3          2                                            9222 5 18     \n'
              ' 1.000000-5 9.770000+5 1.500000+6 1.000000+6 3.000000+7 1.060000+69222 5 18     \n'
              ' 0.000000+0 0.000000+0          0          0          1          59222 5 18     \n'
              '          5          2                                            9222 5 18     \n'
              ' 1.000000-5 2.546000-6 1.500000+6 2.546000-6 1.000000+7 2.474000-69222 5 18     \n'
              ' 1.220000+7 2.612000-6 3.000000+7 2.620000-6                      9222 5 18     \n' )

    invalid = ( ' 0.000000+0 0.000000+0          0          0          2          39222 5 18     \n'
                '          3          2                                            9222 5 18     \n'
                ' 1.000000-5 9.770000+5 1.500000+6 1.000000+6 3.000000+7 1.060000+69222 5 18     \n'
                ' 0.000000+0 0.000000+0          0          0          1          59222 5 18     \n'
                '          5          2                                            9222 5 18     \n'
                ' 1.000000-5 2.546000-6 1.500000+6 2.546000-6 1.000000+7 2.474000-69222 5 18     \n'
                ' 1.220000+7 2.612000-6 3.000000+7 2.620000-6                      9222 5 18     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 11, chunk.LF )
            self.assertEqual( 11, chunk.LAW )

            valueA = chunk.a
            self.assertEqual( 3, valueA.NP )
            self.assertEqual( 3, valueA.number_points )
            self.assertEqual( 1, valueA.NR )
            self.assertEqual( 1, valueA.number_interpolation_regions )
            self.assertEqual( 1, len( valueA.INT ) )
            self.assertEqual( 1, len( valueA.NBT ) )
            self.assertEqual( 2, valueA.INT[0] )
            self.assertEqual( 3, valueA.NBT[0] )
            self.assertEqual( 1, len( valueA.interpolants ) )
            self.assertEqual( 1, len( valueA.boundaries ) )
            self.assertEqual( 2, valueA.interpolants[0] )
            self.assertEqual( 3, valueA.boundaries[0] )
            self.assertEqual( 3, len( valueA.energies ) )
            self.assertEqual( 3, len( valueA.values ) )
            self.assertAlmostEqual( 1e-5, valueA.energies[0] )
            self.assertAlmostEqual( 1.5e+6, valueA.energies[1] )
            self.assertAlmostEqual( 3e+7, valueA.energies[2] )
            self.assertAlmostEqual( 9.77e+5, valueA.values[0] )
            self.assertAlmostEqual( 1e+6, valueA.values[1] )
            self.assertAlmostEqual( 1.06e+6, valueA.values[2] )

            valueB = chunk.b
            self.assertEqual( 5, valueB.NP )
            self.assertEqual( 5, valueB.number_points )
            self.assertEqual( 1, valueB.NR )
            self.assertEqual( 1, valueB.number_interpolation_regions )
            self.assertEqual( 1, len( valueB.INT ) )
            self.assertEqual( 1, len( valueB.NBT ) )
            self.assertEqual( 2, valueB.INT[0] )
            self.assertEqual( 5, valueB.NBT[0] )
            self.assertEqual( 1, len( valueB.interpolants ) )
            self.assertEqual( 1, len( valueB.boundaries ) )
            self.assertEqual( 2, valueB.interpolants[0] )
            self.assertEqual( 5, valueB.boundaries[0] )
            self.assertEqual( 5, len( valueB.energies ) )
            self.assertEqual( 5, len( valueB.values ) )
            self.assertAlmostEqual( 1e-5, valueB.energies[0] )
            self.assertAlmostEqual( 1.5e+6, valueB.energies[1] )
            self.assertAlmostEqual( 1e+7, valueB.energies[2] )
            self.assertAlmostEqual( 1.22e+7, valueB.energies[3] )
            self.assertAlmostEqual( 3e+7, valueB.energies[4] )
            self.assertAlmostEqual( 2.546e-6, valueB.values[0] )
            self.assertAlmostEqual( 2.546e-6, valueB.values[1] )
            self.assertAlmostEqual( 2.474e-6, valueB.values[2] )
            self.assertAlmostEqual( 2.612e-6, valueB.values[3] )
            self.assertAlmostEqual( 2.62e-6, valueB.values[4] )

            self.assertEqual( 7, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9222, 5, 18 ) )

        # the data is given explicitly
        chunk = WattSpectrum( a = Parameter( [ 3 ], [ 2 ],
                                             [ 1e-5, 1.5e+6, 3e+7 ],
                                             [ 9.77e+5, 1e+6, 1.06e+6 ] ),
                              b = Parameter( [ 5 ], [ 2 ],
                                             [ 1e-5, 1.5e+6, 1e+7, 1.22e+7, 3e+7 ],
                                             [ 2.546e-6, 2.546e-6, 2.474e-6, 2.612e-6, 2.62e-6 ] ) )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = WattSpectrum.from_string( self.chunk, 9222, 5, 18 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = WattSpectrum( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        with self.assertRaises( Exception ) :

            chunk = WattSpectrum.from_string( self.invalid, 9222, 5, 18 )

if __name__ == '__main__' :

    unittest.main()
