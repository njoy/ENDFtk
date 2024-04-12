# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF7.MT4 import ScatteringFunction

class Test_ENDFtk_MF7_MT4_ScatteringFunction( unittest.TestCase ) :
    """Unit test for the ScatteringFunction class."""

    chunk_one_temperature = ( ' 2.936000+2 0.000000+0          0          0          1          5  27 7  4     \n'
                              '          5          4                                              27 7  4     \n'
                              ' 4.423802-3 2.386876-4 4.649528-3 2.508466-4 4.886772-3 2.636238-4  27 7  4     \n'
                              ' 8.418068+1 1.306574-9 8.847604+1 5.29573-10                        27 7  4     \n' )

    chunk_two_temperatures = ( ' 2.936000+2 0.000000+0          1          0          1          5  27 7  4     \n'
                               '          5          4                                              27 7  4     \n'
                               ' 4.423802-3 2.386876-4 4.649528-3 2.508466-4 4.886772-3 2.636238-4  27 7  4     \n'
                               ' 8.418068+1 1.306574-9 8.847604+1 5.29573-10                        27 7  4     \n'
                               ' 4.000000+2 0.000000+0          4          0          5          0  27 7  4     \n'
                               ' 4.430020-4 4.655671-4 4.892796-4 4.510209-8 2.183942-8             27 7  4     \n' )

    invalid = ( ' 2.936000+2 0.000000+0          1          0          1          5  27 7  4     \n'
                '          5          4                                              27 7  4     \n'
                ' 4.423802-3 2.386876-4 4.649528-3 2.508466-4 4.886772-3 2.636238-4  27 7  4     \n'
                ' 8.418068+1 1.306574-9 8.847604+1 5.29573-10                        27 7  4     \n'
                ' 4.000000+2 1.000000+0          4          0          5          0  27 7  4     \n'
                ' 4.430020-4 4.655671-4 4.892796-4 4.510209-8 2.183942-8             27 7  4     \n' )

    def test_component( self ) :

        def verify_chunk_one_temperature( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 0.0, chunk.B )
            self.assertAlmostEqual( 0.0, chunk.beta )
            self.assertEqual( 0, chunk.LT )
            self.assertEqual( 0, chunk.temperature_dependence_flag )
            self.assertEqual( 1, chunk.NT )
            self.assertEqual( 1, chunk.number_temperatures )

            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, chunk.number_interpolation_regions )
            self.assertEqual( 5, chunk.NP )
            self.assertEqual( 5, chunk.number_points )
            self.assertEqual( 5, chunk.NA )
            self.assertEqual( 5, chunk.number_alphas )
            self.assertEqual( 1, len( chunk.NBT ) )
            self.assertEqual( 5, chunk.NBT[0] )
            self.assertEqual( 1, len( chunk.INT ) )
            self.assertEqual( 4, chunk.INT[0] )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 5, chunk.boundaries[0] )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 4, chunk.interpolants[0] )

            self.assertEqual( 1, len( chunk.T ) )
            self.assertEqual( 1, len( chunk.temperatures ) )
            self.assertAlmostEqual( 293.6, chunk.T[0] )
            self.assertAlmostEqual( 293.6, chunk.temperatures[0] )

            self.assertEqual( 5, len( chunk.A ) )
            self.assertEqual( 5, len( chunk.alphas ) )
            self.assertAlmostEqual( 4.423802e-3, chunk.A[0] )
            self.assertAlmostEqual( 4.649528e-3, chunk.A[1] )
            self.assertAlmostEqual( 4.886772e-3, chunk.A[2] )
            self.assertAlmostEqual( 8.418068e+1, chunk.A[3] )
            self.assertAlmostEqual( 8.847604e+1, chunk.A[4] )
            self.assertAlmostEqual( 4.423802e-3, chunk.alphas[0] )
            self.assertAlmostEqual( 4.649528e-3, chunk.alphas[1] )
            self.assertAlmostEqual( 4.886772e-3, chunk.alphas[2] )
            self.assertAlmostEqual( 8.418068e+1, chunk.alphas[3] )
            self.assertAlmostEqual( 8.847604e+1, chunk.alphas[4] )

            self.assertEqual( 0, len( chunk.LI ) )
            self.assertEqual( 0, len( chunk.temperature_interpolants ) )

            self.assertEqual( 1, len( chunk.S ) )
            self.assertEqual( 5, len( chunk.S[0] ) )
            self.assertAlmostEqual( 2.386876e-4, chunk.S[0][0] )
            self.assertAlmostEqual( 2.508466e-4, chunk.S[0][1] )
            self.assertAlmostEqual( 2.636238e-4, chunk.S[0][2] )
            self.assertAlmostEqual( 1.306574e-9, chunk.S[0][3] )
            self.assertAlmostEqual( 5.29573e-10, chunk.S[0][4] )

            self.assertEqual( 1, len( chunk.thermal_scattering_values ) )
            self.assertEqual( 5, len( chunk.thermal_scattering_values[0] ) )
            self.assertAlmostEqual( 2.386876e-4, chunk.thermal_scattering_values[0][0] )
            self.assertAlmostEqual( 2.508466e-4, chunk.thermal_scattering_values[0][1] )
            self.assertAlmostEqual( 2.636238e-4, chunk.thermal_scattering_values[0][2] )
            self.assertAlmostEqual( 1.306574e-9, chunk.thermal_scattering_values[0][3] )
            self.assertAlmostEqual( 5.29573e-10, chunk.thermal_scattering_values[0][4] )

            self.assertEqual( 4, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_one_temperature, chunk.to_string( 27, 7, 4 ) )

        def verify_chunk_two_temperature( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 0.0, chunk.B )
            self.assertAlmostEqual( 0.0, chunk.beta )
            self.assertEqual( 1, chunk.LT )
            self.assertEqual( 1, chunk.temperature_dependence_flag )
            self.assertEqual( 2, chunk.NT )
            self.assertEqual( 2, chunk.number_temperatures )

            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, chunk.number_interpolation_regions )
            self.assertEqual( 5, chunk.NP )
            self.assertEqual( 5, chunk.number_points )
            self.assertEqual( 5, chunk.NA )
            self.assertEqual( 5, chunk.number_alphas )
            self.assertEqual( 1, len( chunk.NBT ) )
            self.assertEqual( 5, chunk.NBT[0] )
            self.assertEqual( 1, len( chunk.INT ) )
            self.assertEqual( 4, chunk.INT[0] )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 5, chunk.boundaries[0] )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 4, chunk.interpolants[0] )

            self.assertEqual( 2, len( chunk.T ) )
            self.assertEqual( 2, len( chunk.temperatures ) )
            self.assertAlmostEqual( 293.6, chunk.T[0] )
            self.assertAlmostEqual( 400.0, chunk.T[1] )
            self.assertAlmostEqual( 293.6, chunk.temperatures[0] )
            self.assertAlmostEqual( 400.0, chunk.temperatures[1] )

            self.assertEqual( 5, len( chunk.A ) )
            self.assertEqual( 5, len( chunk.alphas ) )
            self.assertAlmostEqual( 4.423802e-3, chunk.A[0] )
            self.assertAlmostEqual( 4.649528e-3, chunk.A[1] )
            self.assertAlmostEqual( 4.886772e-3, chunk.A[2] )
            self.assertAlmostEqual( 8.418068e+1, chunk.A[3] )
            self.assertAlmostEqual( 8.847604e+1, chunk.A[4] )
            self.assertAlmostEqual( 4.423802e-3, chunk.alphas[0] )
            self.assertAlmostEqual( 4.649528e-3, chunk.alphas[1] )
            self.assertAlmostEqual( 4.886772e-3, chunk.alphas[2] )
            self.assertAlmostEqual( 8.418068e+1, chunk.alphas[3] )
            self.assertAlmostEqual( 8.847604e+1, chunk.alphas[4] )

            self.assertEqual( 1, len( chunk.LI ) )
            self.assertAlmostEqual( 4, chunk.LI[0] )
            self.assertEqual( 1, len( chunk.temperature_interpolants ) )
            self.assertAlmostEqual( 4, chunk.temperature_interpolants[0] )

            self.assertEqual( 2, len( chunk.S ) )
            self.assertEqual( 5, len( chunk.S[0] ) )
            self.assertAlmostEqual( 2.386876e-4, chunk.S[0][0] )
            self.assertAlmostEqual( 2.508466e-4, chunk.S[0][1] )
            self.assertAlmostEqual( 2.636238e-4, chunk.S[0][2] )
            self.assertAlmostEqual( 1.306574e-9, chunk.S[0][3] )
            self.assertAlmostEqual( 5.29573e-10, chunk.S[0][4] )
            self.assertEqual( 5, len( chunk.S[1] ) )
            self.assertAlmostEqual( 4.430020e-4, chunk.S[1][0] )
            self.assertAlmostEqual( 4.655671e-4, chunk.S[1][1] )
            self.assertAlmostEqual( 4.892796e-4, chunk.S[1][2] )
            self.assertAlmostEqual( 4.510209e-8, chunk.S[1][3] )
            self.assertAlmostEqual( 2.183942e-8, chunk.S[1][4] )

            self.assertEqual( 2, len( chunk.thermal_scattering_values ) )
            self.assertEqual( 5, len( chunk.thermal_scattering_values[0] ) )
            self.assertAlmostEqual( 2.386876e-4, chunk.thermal_scattering_values[0][0] )
            self.assertAlmostEqual( 2.508466e-4, chunk.thermal_scattering_values[0][1] )
            self.assertAlmostEqual( 2.636238e-4, chunk.thermal_scattering_values[0][2] )
            self.assertAlmostEqual( 1.306574e-9, chunk.thermal_scattering_values[0][3] )
            self.assertAlmostEqual( 5.29573e-10, chunk.thermal_scattering_values[0][4] )
            self.assertEqual( 5, len( chunk.thermal_scattering_values[1] ) )
            self.assertAlmostEqual( 4.430020e-4, chunk.thermal_scattering_values[1][0] )
            self.assertAlmostEqual( 4.655671e-4, chunk.thermal_scattering_values[1][1] )
            self.assertAlmostEqual( 4.892796e-4, chunk.thermal_scattering_values[1][2] )
            self.assertAlmostEqual( 4.510209e-8, chunk.thermal_scattering_values[1][3] )
            self.assertAlmostEqual( 2.183942e-8, chunk.thermal_scattering_values[1][4] )

            self.assertEqual( 6, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_two_temperatures, chunk.to_string( 27, 7, 4 ) )

        # the data is given explicitly
        chunk = ScatteringFunction( temperature = 293.6, beta = 0.0, interpolants = [ 4 ], boundaries = [ 5 ],
                                    alphas = [ 4.423802e-3, 4.649528e-3, 4.886772e-3, 8.418068e+1, 8.847604e+1 ],
                                    sab = [ 2.386876e-4, 2.508466e-4, 2.636238e-4, 1.306574e-9, 5.29573e-10 ] )

        verify_chunk_one_temperature( self, chunk )

        # the data is read from a string
        chunk = ScatteringFunction.from_string( self.chunk_one_temperature, 27, 7, 4 )

        verify_chunk_one_temperature( self, chunk )

        # the data is copied
        copy = ScatteringFunction( chunk )

        verify_chunk_one_temperature( self, copy )

        # the data is given explicitly
        chunk = ScatteringFunction( beta = 0.0, boundaries = [ 5 ], interpolants = [ 4 ], li = [ 4 ],
                                    alphas = [ 4.423802e-3, 4.649528e-3, 4.886772e-3, 8.418068e+1, 8.847604e+1 ],
                                    temperatures = [ 293.6, 400.0 ],
                                    sab = [ [ 2.386876e-4, 2.508466e-4, 2.636238e-4,
                                              1.306574e-9, 5.29573e-10 ],
                                            [ 4.430020e-4, 4.655671e-4, 4.892796e-4,
                                              4.510209e-8, 2.183942e-8 ] ] )

        verify_chunk_two_temperature( self, chunk )

        # the data is read from a string
        chunk = ScatteringFunction.from_string( self.chunk_two_temperatures, 27, 7, 4 )

        verify_chunk_two_temperature( self, chunk )

        # the data is copied
        copy = ScatteringFunction( chunk )

        verify_chunk_two_temperature( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # boundaries are wrong
        with self.assertRaises( Exception ) :

            chunk = ScatteringFunction( beta = 0.0, boundaries = [ 5, 6 ], interpolants = [ 4 ], li = [ 4 ],
                                        alphas = [ 4.423802e-3, 4.649528e-3, 4.886772e-3, 8.418068e+1, 8.847604e+1 ],
                                        temperatures = [ 293.6, 400.0 ],
                                        sab = [ [ 2.386876e-4, 2.508466e-4, 2.636238e-4,
                                                  1.306574e-9, 5.29573e-10 ],
                                                [ 4.430020e-4, 4.655671e-4, 4.892796e-4,
                                                  4.510209e-8, 2.183942e-8 ] ] )

        with self.assertRaises( Exception ) :

            chunk = ScatteringFunction.from_string( self.invalid, 27, 7, 4 )

if __name__ == '__main__' :

    unittest.main()
