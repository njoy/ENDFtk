# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF7.MT2 import CoherentElastic

class Test_ENDFtk_MF7_MT2_CoherentElastic( unittest.TestCase ) :
    """Unit test for the CoherentElastic class."""

    chunk_one_temp = ( ' 2.936000+2 0.000000+0          0          0          1          3  27 7  2     \n'
                       '          3          1                                              27 7  2     \n'
                       ' 1.059427-3 0.000000+0 3.718355-3 9.364524-3 4.237708-3 1.548925-2  27 7  2     \n' )

    chunk_two_temp = ( ' 2.936000+2 0.000000+0          1          0          1          3  27 7  2     \n'
                       '          3          1                                              27 7  2     \n'
                       ' 1.059427-3 0.000000+0 3.718355-3 9.364524-3 4.237708-3 1.548925-2  27 7  2     \n'
                       ' 4.000000+2 0.000000+0          2          0          3          0  27 7  2     \n'
                       ' 5.000000-1 8.318414-3 1.640584-2                                   27 7  2     \n' )

    invalid = ( ' 2.936000+2 0.000000+0          0          0          1          4  27 7  2     \n'
                '          3          1                                              27 7  2     \n'
                ' 1.059427-3 0.000000+0 3.718355-3 9.364524-3 4.237708-3 1.548925-2  27 7  2     \n' )

    def test_component( self ) :

        def verify_chunk_one_temp( self, chunk ) :

            # verify content
            self.assertEqual( 1, chunk.LTHR )
            self.assertEqual( 1, chunk.elastic_scattering_type )
            self.assertEqual( 0, chunk.LT )
            self.assertEqual( 0, chunk.temperature_dependence_flag )
            self.assertEqual( 1, chunk.NT )
            self.assertEqual( 1, chunk.number_temperatures )
            self.assertEqual( 3, chunk.NP )
            self.assertEqual( 3, chunk.number_bragg_edges )

            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, chunk.interpolants[0] )

            self.assertEqual( 1, len( chunk.T ) )
            self.assertEqual( 1, len( chunk.temperatures ) )
            self.assertAlmostEqual( 293.6, chunk.T[0] )
            self.assertAlmostEqual( 293.6, chunk.temperatures[0] )

            self.assertEqual( 3, len( chunk.E ) )
            self.assertEqual( 3, len( chunk.energies ) )
            self.assertAlmostEqual( 1.059427e-3, chunk.E[0] )
            self.assertAlmostEqual( 3.718355e-3, chunk.E[1] )
            self.assertAlmostEqual( 4.237708e-3, chunk.E[2] )
            self.assertAlmostEqual( 1.059427e-3, chunk.energies[0] )
            self.assertAlmostEqual( 3.718355e-3, chunk.energies[1] )
            self.assertAlmostEqual( 4.237708e-3, chunk.energies[2] )

            self.assertEqual( 0, len( chunk.LI ) )
            self.assertEqual( 0, len( chunk.temperature_interpolants ) )

            self.assertEqual( 1, len( chunk.S ) )
            self.assertEqual( 3, len( chunk.S[0] ) )
            self.assertAlmostEqual( 0.0, chunk.S[0][0] )
            self.assertAlmostEqual( 9.364524e-3, chunk.S[0][1] )
            self.assertAlmostEqual( 1.548925e-2, chunk.S[0][2] )

            self.assertEqual( 1, len( chunk.thermal_scattering_values ) )
            self.assertEqual( 3, len( chunk.thermal_scattering_values[0] ) )
            self.assertAlmostEqual( 0.0, chunk.thermal_scattering_values[0][0] )
            self.assertAlmostEqual( 9.364524e-3, chunk.thermal_scattering_values[0][1] )
            self.assertAlmostEqual( 1.548925e-2, chunk.thermal_scattering_values[0][2] )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_one_temp, chunk.to_string( 27, 7, 2 ) )

        def verify_chunk_two_temp( self, chunk ) :

            # verify content
            self.assertEqual( 1, chunk.LTHR )
            self.assertEqual( 1, chunk.elastic_scattering_type )
            self.assertEqual( 1, chunk.LT )
            self.assertEqual( 1, chunk.temperature_dependence_flag )
            self.assertEqual( 2, chunk.NT )
            self.assertEqual( 2, chunk.number_temperatures )
            self.assertEqual( 3, chunk.NP )
            self.assertEqual( 3, chunk.number_bragg_edges )

            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, chunk.interpolants[0] )

            self.assertEqual( 2, len( chunk.T ) )
            self.assertEqual( 2, len( chunk.temperatures ) )
            self.assertAlmostEqual( 293.6, chunk.T[0] )
            self.assertAlmostEqual( 400., chunk.T[1] )
            self.assertAlmostEqual( 293.6, chunk.temperatures[0] )
            self.assertAlmostEqual( 400., chunk.temperatures[1] )

            self.assertEqual( 3, len( chunk.E ) )
            self.assertEqual( 3, len( chunk.energies ) )
            self.assertAlmostEqual( 1.059427e-3, chunk.E[0] )
            self.assertAlmostEqual( 3.718355e-3, chunk.E[1] )
            self.assertAlmostEqual( 4.237708e-3, chunk.E[2] )
            self.assertAlmostEqual( 1.059427e-3, chunk.energies[0] )
            self.assertAlmostEqual( 3.718355e-3, chunk.energies[1] )
            self.assertAlmostEqual( 4.237708e-3, chunk.energies[2] )

            self.assertEqual( 1, len( chunk.LI ) )
            self.assertEqual( 2, chunk.LI[0] )
            self.assertEqual( 1, len( chunk.temperature_interpolants ) )
            self.assertEqual( 2, chunk.temperature_interpolants[0] )

            self.assertEqual( 2, len( chunk.S ) )
            self.assertEqual( 3, len( chunk.S[0] ) )
            self.assertAlmostEqual( 0.0, chunk.S[0][0] )
            self.assertAlmostEqual( 9.364524e-3, chunk.S[0][1] )
            self.assertAlmostEqual( 1.548925e-2, chunk.S[0][2] )
            self.assertEqual( 3, len( chunk.S[1] ) )
            self.assertAlmostEqual( 0.5, chunk.S[1][0] )
            self.assertAlmostEqual( 8.318414e-3, chunk.S[1][1] )
            self.assertAlmostEqual( 1.640584e-2, chunk.S[1][2] )

            self.assertEqual( 2, len( chunk.thermal_scattering_values ) )
            self.assertEqual( 3, len( chunk.thermal_scattering_values[0] ) )
            self.assertAlmostEqual( 0.0, chunk.thermal_scattering_values[0][0] )
            self.assertAlmostEqual( 9.364524e-3, chunk.thermal_scattering_values[0][1] )
            self.assertAlmostEqual( 1.548925e-2, chunk.thermal_scattering_values[0][2] )
            self.assertEqual( 3, len( chunk.thermal_scattering_values[1] ) )
            self.assertAlmostEqual( 0.5, chunk.thermal_scattering_values[1][0] )
            self.assertAlmostEqual( 8.318414e-3, chunk.thermal_scattering_values[1][1] )
            self.assertAlmostEqual( 1.640584e-2, chunk.thermal_scattering_values[1][2] )

            self.assertEqual( 5, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_two_temp, chunk.to_string( 27, 7, 2 ) )

        # the data is given explicitly
        chunk = CoherentElastic( temperature = 293.6, interpolants = [ 1 ], boundaries = [ 3 ],
                                 energies = [ 1.059427e-3, 3.718355e-3,  4.237708e-3 ],
                                 s = [ 0.0, 9.364524e-3, 1.548925e-2 ] )

        verify_chunk_one_temp( self, chunk )

        # the data is read from a string
        chunk = CoherentElastic.from_string( self.chunk_one_temp, 27, 7, 2 )

        verify_chunk_one_temp( self, chunk )

        # the data is copied
        copy = CoherentElastic( chunk )

        verify_chunk_one_temp( self, copy )

        # the data is given explicitly
        chunk = CoherentElastic( boundaries = [ 3 ], interpolants = [ 1 ], li = [ 2 ],
                                 temperatures = [ 293.6, 400.0 ],
                                 energies = [ 1.059427e-3, 3.718355e-3, 4.237708e-3 ],
                                 s = [ [ 0.0, 9.364524e-3, 1.548925e-2 ],
                                       [ 0.5, 8.318414e-3, 1.640584e-2 ] ] )

        verify_chunk_two_temp( self, chunk )

        # the data is read from a string
        chunk = CoherentElastic.from_string( self.chunk_two_temp, 27, 7, 2 )

        verify_chunk_two_temp( self, chunk )

        # the data is copied
        copy = CoherentElastic( chunk )

        verify_chunk_two_temp( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # wrong boundaries
        with self.assertRaises( Exception ) :

            chunk = CoherentElastic( sb = 8.198006e+1, boundaries = [ 3, 5 ], interpolants = [ 2 ],
                                       temperatures = [ 296., 400., 500. ],
                                       integrals = [ 8.486993e+0, 9.093191e+0, 9.828159e+0 ] )

        with self.assertRaises( Exception ) :

            chunk = CoherentElastic.from_string( self.invalid, 27, 7, 2 )

if __name__ == '__main__' :

    unittest.main()
