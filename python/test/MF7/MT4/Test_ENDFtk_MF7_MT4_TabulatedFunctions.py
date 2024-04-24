# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF7.MT4 import TabulatedFunctions
from ENDFtk.MF7.MT4 import ScatteringFunction

class Test_ENDFtk_MF7_MT4_Tabulated( unittest.TestCase ) :
    """Unit test for the Tabulated class."""

    chunk = ( ' 0.000000+0 0.000000+0          0          0          1          2  27 7  4     \n'
              '          2          4                                              27 7  4     \n'
              ' 2.936000+2 0.000000+0          0          0          1          5  27 7  4     \n'
              '          5          4                                              27 7  4     \n'
              ' 4.423802-3 2.386876-4 4.649528-3 2.508466-4 4.886772-3 2.636238-4  27 7  4     \n'
              ' 8.418068+1 1.306574-9 8.847604+1 5.29573-10                        27 7  4     \n'
              ' 2.936000+2 3.952570-2          0          0          1          5  27 7  4     \n'
              '          5          2                                              27 7  4     \n'
              ' 4.423802-3 2.386694-4 4.649528-3 2.508273-4 4.886772-3 2.636238-4  27 7  4     \n'
              ' 8.418068+1 2.770291-4 8.847604+1 2.911373-4                        27 7  4     \n' )

    invalid = ( ' 0.000000+0 0.000000+0          0          0          1          2  27 7  4     \n'
                '          2          4                                              27 7  4     \n'
                ' 2.936000+2 0.000000+0          1          0          1          5  27 7  4     \n'
                '          5          4                                              27 7  4     \n'
                ' 4.423802-3 2.386876-4 4.649528-3 2.508466-4 4.886772-3 2.636238-4  27 7  4     \n'
                ' 8.418068+1 1.306574-9 8.847604+1 5.29573-10                        27 7  4     \n'
                ' 2.936000+2 3.952570-2          0          0          1          5  27 7  4     \n'
                '          5          2                                              27 7  4     \n'
                ' 4.423802-3 2.386694-4 4.649528-3 2.508273-4 4.886772-3 2.636238-4  27 7  4     \n'
                ' 8.418068+1 2.770291-4 8.847604+1 2.911373-4                        27 7  4     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, chunk.number_interpolation_regions )
            self.assertEqual( 2, chunk.NB )
            self.assertEqual( 2, chunk.number_betas )
            self.assertEqual( 1, len( chunk.NBT ) )
            self.assertEqual( 2, chunk.NBT[0] )
            self.assertEqual( 1, len( chunk.INT ) )
            self.assertEqual( 4, chunk.INT[0] )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 2, chunk.boundaries[0] )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 4, chunk.interpolants[0] )

            self.assertEqual( 2, len( chunk.B ) )
            self.assertEqual( 2, len( chunk.betas ) )
            self.assertAlmostEqual( 0.0, chunk.B[0] )
            self.assertAlmostEqual( 3.952570e-2, chunk.B[1] )
            self.assertAlmostEqual( 0.0, chunk.betas[0] )
            self.assertAlmostEqual( 3.952570e-2, chunk.betas[1] )

            value = chunk.scattering_functions[0]
            self.assertAlmostEqual( 0.0, value.beta )
            self.assertEqual( 0, value.LT )
            self.assertEqual( 0, value.temperature_dependence_flag )
            self.assertEqual( 1, value.NT )
            self.assertEqual( 1, value.number_temperatures )

            self.assertEqual( 1, value.NR )
            self.assertEqual( 1, value.number_interpolation_regions )
            self.assertEqual( 5, value.NP )
            self.assertEqual( 5, value.number_points )
            self.assertEqual( 5, value.NA )
            self.assertEqual( 5, value.number_alphas )
            self.assertEqual( 1, len( value.NBT ) )
            self.assertEqual( 5, value.NBT[0] )
            self.assertEqual( 1, len( value.INT ) )
            self.assertEqual( 4, value.INT[0] )
            self.assertEqual( 1, len( value.boundaries ) )
            self.assertEqual( 5, value.boundaries[0] )
            self.assertEqual( 1, len( value.interpolants ) )
            self.assertEqual( 4, value.interpolants[0] )

            self.assertEqual( 1, len( value.T ) )
            self.assertEqual( 1, len( value.temperatures ) )
            self.assertAlmostEqual( 293.6, value.T[0] )
            self.assertAlmostEqual( 293.6, value.temperatures[0] )

            self.assertEqual( 5, len( value.A ) )
            self.assertEqual( 5, len( value.alphas ) )
            self.assertAlmostEqual( 4.423802e-3, value.A[0] )
            self.assertAlmostEqual( 4.649528e-3, value.A[1] )
            self.assertAlmostEqual( 4.886772e-3, value.A[2] )
            self.assertAlmostEqual( 8.418068e+1, value.A[3] )
            self.assertAlmostEqual( 8.847604e+1, value.A[4] )
            self.assertAlmostEqual( 4.423802e-3, value.alphas[0] )
            self.assertAlmostEqual( 4.649528e-3, value.alphas[1] )
            self.assertAlmostEqual( 4.886772e-3, value.alphas[2] )
            self.assertAlmostEqual( 8.418068e+1, value.alphas[3] )
            self.assertAlmostEqual( 8.847604e+1, value.alphas[4] )

            self.assertEqual( 0, len( value.LI ) )
            self.assertEqual( 0, len( value.temperature_interpolants ) )

            values = value.S
            self.assertEqual( 1, len( values ) )
            self.assertEqual( 5, len( values[0] ) )
            self.assertAlmostEqual( 2.386876e-4, values[0][0] )
            self.assertAlmostEqual( 2.508466e-4, values[0][1] )
            self.assertAlmostEqual( 2.636238e-4, values[0][2] )
            self.assertAlmostEqual( 1.306574e-9, values[0][3] )
            self.assertAlmostEqual( 5.29573e-10, values[0][4] )

            values = value.thermal_scattering_values
            self.assertEqual( 1, len( values ) )
            self.assertEqual( 5, len( values[0] ) )
            self.assertAlmostEqual( 2.386876e-4, values[0][0] )
            self.assertAlmostEqual( 2.508466e-4, values[0][1] )
            self.assertAlmostEqual( 2.636238e-4, values[0][2] )
            self.assertAlmostEqual( 1.306574e-9, values[0][3] )
            self.assertAlmostEqual( 5.29573e-10, values[0][4] )

            value = chunk.scattering_functions[1]
            self.assertAlmostEqual( 3.952570e-2, value.beta )
            self.assertEqual( 0, value.LT )
            self.assertEqual( 0, value.temperature_dependence_flag )
            self.assertEqual( 1, value.NT )
            self.assertEqual( 1, value.number_temperatures )

            self.assertEqual( 1, value.NR )
            self.assertEqual( 1, value.number_interpolation_regions )
            self.assertEqual( 5, value.NP )
            self.assertEqual( 5, value.number_points )
            self.assertEqual( 5, value.NA )
            self.assertEqual( 5, value.number_alphas )
            self.assertEqual( 1, len( value.NBT ) )
            self.assertEqual( 5, value.NBT[0] )
            self.assertEqual( 1, len( value.INT ) )
            self.assertEqual( 2, value.INT[0] )
            self.assertEqual( 1, len( value.boundaries ) )
            self.assertEqual( 5, value.boundaries[0] )
            self.assertEqual( 1, len( value.interpolants ) )
            self.assertEqual( 2, value.interpolants[0] )

            self.assertEqual( 1, len( value.T ) )
            self.assertEqual( 1, len( value.temperatures ) )
            self.assertAlmostEqual( 293.6, value.T[0] )
            self.assertAlmostEqual( 293.6, value.temperatures[0] )

            self.assertEqual( 5, len( value.A ) )
            self.assertEqual( 5, len( value.alphas ) )
            self.assertAlmostEqual( 4.423802e-3, value.A[0] )
            self.assertAlmostEqual( 4.649528e-3, value.A[1] )
            self.assertAlmostEqual( 4.886772e-3, value.A[2] )
            self.assertAlmostEqual( 8.418068e+1, value.A[3] )
            self.assertAlmostEqual( 8.847604e+1, value.A[4] )
            self.assertAlmostEqual( 4.423802e-3, value.alphas[0] )
            self.assertAlmostEqual( 4.649528e-3, value.alphas[1] )
            self.assertAlmostEqual( 4.886772e-3, value.alphas[2] )
            self.assertAlmostEqual( 8.418068e+1, value.alphas[3] )
            self.assertAlmostEqual( 8.847604e+1, value.alphas[4] )

            self.assertEqual( 0, len( value.LI ) )
            self.assertEqual( 0, len( value.temperature_interpolants ) )

            values = value.S
            self.assertEqual( 1, len( values ) )
            self.assertEqual( 5, len( values[0] ) )
            self.assertAlmostEqual( 2.386694e-4, values[0][0] )
            self.assertAlmostEqual( 2.508273e-4, values[0][1] )
            self.assertAlmostEqual( 2.636238e-4, values[0][2] )
            self.assertAlmostEqual( 2.770291e-4, values[0][3] )
            self.assertAlmostEqual( 2.911373e-4, values[0][4] )

            values = value.thermal_scattering_values
            self.assertEqual( 1, len( values ) )
            self.assertEqual( 5, len( values[0] ) )
            self.assertAlmostEqual( 2.386694e-4, values[0][0] )
            self.assertAlmostEqual( 2.508273e-4, values[0][1] )
            self.assertAlmostEqual( 2.636238e-4, values[0][2] )
            self.assertAlmostEqual( 2.770291e-4, values[0][3] )
            self.assertAlmostEqual( 2.911373e-4, values[0][4] )

            self.assertEqual( 10, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 27, 7, 4 ) )

        # the data is given explicitly
        chunk = TabulatedFunctions(
                    boundaries = [ 2 ], interpolants = [ 4 ],
                    functions = [ ScatteringFunction(
                                      293.6, 0.0, [ 5 ], [ 4 ],
                                      [ 4.423802e-3, 4.649528e-3, 4.886772e-3, 8.418068e+1,
                                        8.847604e+1 ],
                                      [ 2.386876e-4, 2.508466e-4, 2.636238e-4, 1.306574e-9,
                                        5.29573e-10 ] ),
                                  ScatteringFunction(
                                      293.6, 3.952570e-2, [ 5 ], [ 2 ],
                                      [ 4.423802e-3, 4.649528e-3, 4.886772e-3, 8.418068e+1,
                                        8.847604e+1 ],
                                      [ 2.386694e-4, 2.508273e-4, 2.636238e-4, 2.770291e-4,
                                        2.911373e-4 ] ) ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = TabulatedFunctions.from_string( self.chunk, 27, 7, 4 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = TabulatedFunctions( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # wrong boundaries
        with self.assertRaises( Exception ) :

            chunk = TabulatedFunctions(
                        boundaries = [ 2, 4 ], interpolants = [ 4 ],
                       functions = [ ScatteringFunction(
                                         293.6, 0.0, [ 5 ], [ 4 ],
                                         [ 4.423802e-3, 4.649528e-3, 4.886772e-3, 8.418068e+1,
                                           8.847604e+1 ],
                                         [ 2.386876e-4, 2.508466e-4, 2.636238e-4, 1.306574e-9,
                                           5.29573e-10 ] ),
                                     ScatteringFunction(
                                         293.6, 3.952570e-2, [ 5 ], [ 2 ],
                                         [ 4.423802e-3, 4.649528e-3, 4.886772e-3, 8.418068e+1,
                                           8.847604e+1 ],
                                         [ 2.386694e-4, 2.508273e-4, 2.636238e-4, 2.770291e-4,
                                           2.911373e-4 ] ) ] )

        with self.assertRaises( Exception ) :

            chunk = TabulatedFunctions.from_string( self.invalid, 27, 7, 4 )

if __name__ == '__main__' :

    unittest.main()
