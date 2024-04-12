# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF7.MT2 import CoherentElastic
from ENDFtk.MF7.MT2 import IncoherentElastic
from ENDFtk.MF7.MT2 import MixedElastic

class Test_ENDFtk_MF7_MT2_MixedElastic( unittest.TestCase ) :
    """Unit test for the MixedElastic class."""

    chunk = ( ' 2.936000+2 0.000000+0          1          0          1          3  27 7  2     \n'
              '          3          1                                              27 7  2     \n'
              ' 1.059427-3 0.000000+0 3.718355-3 9.364524-3 4.237708-3 1.548925-2  27 7  2     \n'
              ' 8.000000+2 0.000000+0          2          0          3          0  27 7  2     \n'
              ' 5.000000-1 8.318414-3 1.640584-2                                   27 7  2     \n'
              ' 2.054202+0 0.000000+0          0          0          1          2  27 7  2     \n'
              '          2          2                                              27 7  2     \n'
              ' 2.936000+2 8.937898+0 8.000000+2 1.765328+1                        27 7  2     \n' )

    invalid = ( ' 2.936000+2 0.000000+0          1          0          1          2  27 7  2     \n'
                '          3          1                                              27 7  2     \n'
                ' 1.059427-3 0.000000+0 3.718355-3 9.364524-3 4.237708-3 1.548925-2  27 7  2     \n'
                ' 8.000000+2 0.000000+0          2          0          3          0  27 7  2     \n'
                ' 5.000000-1 8.318414-3 1.640584-2                                   27 7  2     \n'
                ' 2.054202+0 0.000000+0          0          0          1          6  27 7  2     \n'
                '          2          2                                              27 7  2     \n'
                ' 2.936000+2 8.937898+0 8.000000+2 1.765328+1                        27 7  2     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 3, chunk.LTHR )
            self.assertEqual( 3, chunk.elastic_scattering_type )

            coherent = chunk.coherent

            self.assertEqual( 1, coherent.LTHR )
            self.assertEqual( 1, coherent.elastic_scattering_type )
            self.assertEqual( 1, coherent.LT )
            self.assertEqual( 1, coherent.temperature_dependence_flag )
            self.assertEqual( 2, coherent.NT )
            self.assertEqual( 2, coherent.number_temperatures )
            self.assertEqual( 3, coherent.NP )
            self.assertEqual( 3, coherent.number_bragg_edges )

            self.assertEqual( 1, coherent.NR )
            self.assertEqual( 1, coherent.number_interpolation_regions )
            self.assertEqual( 1, len( coherent.NBT ) )
            self.assertEqual( 3, coherent.NBT[0] );
            self.assertEqual( 1, len( coherent.INT ) )
            self.assertEqual( 1, coherent.INT[0] );
            self.assertEqual( 1, len( coherent.boundaries ) )
            self.assertEqual( 3, coherent.boundaries[0] );
            self.assertEqual( 1, len( coherent.interpolants ) )
            self.assertEqual( 1, coherent.interpolants[0] );

            self.assertEqual( 2, len( coherent.T ) )
            self.assertEqual( 2, len( coherent.temperatures ) )
            self.assertAlmostEqual( 293.6, coherent.T[0] )
            self.assertAlmostEqual( 800., coherent.T[1] )
            self.assertAlmostEqual( 293.6, coherent.temperatures[0] )
            self.assertAlmostEqual( 800., coherent.temperatures[1] )

            self.assertEqual( 3, len( coherent.E ) )
            self.assertEqual( 3, len( coherent.energies ) )
            self.assertAlmostEqual( 1.059427e-3, coherent.E[0] )
            self.assertAlmostEqual( 3.718355e-3, coherent.E[1] )
            self.assertAlmostEqual( 4.237708e-3, coherent.E[2] )
            self.assertAlmostEqual( 1.059427e-3, coherent.energies[0] )
            self.assertAlmostEqual( 3.718355e-3, coherent.energies[1] )
            self.assertAlmostEqual( 4.237708e-3, coherent.energies[2] )

            self.assertEqual( 1, len( coherent.LI ) )
            self.assertEqual( 2, coherent.LI[0] )
            self.assertEqual( 1, len( coherent.temperature_interpolants ) )
            self.assertEqual( 2, coherent.temperature_interpolants[0] );

            self.assertEqual( 2, len( coherent.S ) )
            self.assertEqual( 3, len( coherent.S[0] ) )
            self.assertAlmostEqual( 0.0, coherent.S[0][0] )
            self.assertAlmostEqual( 9.364524e-3, coherent.S[0][1] )
            self.assertAlmostEqual( 1.548925e-2, coherent.S[0][2] )
            self.assertEqual( 3, len( coherent.S[1] ) )
            self.assertAlmostEqual( 0.5, coherent.S[1][0] )
            self.assertAlmostEqual( 8.318414e-3, coherent.S[1][1] )
            self.assertAlmostEqual( 1.640584e-2, coherent.S[1][2] )

            self.assertEqual( 2, len( coherent.thermal_scattering_values ) )
            self.assertEqual( 3, len( coherent.thermal_scattering_values[0] ) )
            self.assertAlmostEqual( 0.0, coherent.thermal_scattering_values[0][0] )
            self.assertAlmostEqual( 9.364524e-3, coherent.thermal_scattering_values[0][1] )
            self.assertAlmostEqual( 1.548925e-2, coherent.thermal_scattering_values[0][2] )
            self.assertEqual( 3, len( coherent.thermal_scattering_values[1] ) )
            self.assertAlmostEqual( 0.5, coherent.thermal_scattering_values[1][0] )
            self.assertAlmostEqual( 8.318414e-3, coherent.thermal_scattering_values[1][1] )
            self.assertAlmostEqual( 1.640584e-2, coherent.thermal_scattering_values[1][2] )

            incoherent = chunk.incoherent

            self.assertEqual( 2, incoherent.LTHR )
            self.assertEqual( 2, incoherent.elastic_scattering_type )
            self.assertAlmostEqual( 2.054202, incoherent.SB )
            self.assertAlmostEqual( 2.054202, incoherent.bound_cross_section )
            self.assertEqual( 2, incoherent.NP )
            self.assertEqual( 2, incoherent.number_points )
            self.assertEqual( 2, incoherent.NT )
            self.assertEqual( 2, incoherent.number_temperatures )
            self.assertEqual( 1, incoherent.NR )
            self.assertEqual( 1, incoherent.number_interpolation_regions )
            self.assertEqual( 1, len( incoherent.INT ) )
            self.assertEqual( 1, len( incoherent.NBT ) )
            self.assertEqual( 2, incoherent.INT[0] );
            self.assertEqual( 2, incoherent.NBT[0] );
            self.assertEqual( 1, len( incoherent.interpolants ) )
            self.assertEqual( 1, len( incoherent.boundaries ) )
            self.assertEqual( 2, incoherent.interpolants[0] );
            self.assertEqual( 2, incoherent.boundaries[0] );
            self.assertEqual( 2, len( incoherent.T ) )
            self.assertEqual( 2, len( incoherent.temperatures ) )
            self.assertEqual( 2, len( incoherent.W ) )
            self.assertEqual( 2, len( incoherent.debye_waller_values ) )
            self.assertAlmostEqual( 293.6, incoherent.T[0] )
            self.assertAlmostEqual( 800., incoherent.T[1] )
            self.assertAlmostEqual( 293.6, incoherent.temperatures[0] )
            self.assertAlmostEqual( 800., incoherent.temperatures[1] )
            self.assertAlmostEqual( 8.937898, incoherent.W[0] )
            self.assertAlmostEqual( 17.65328, incoherent.W[1] )
            self.assertAlmostEqual( 8.937898, incoherent.debye_waller_values[0] )
            self.assertAlmostEqual( 17.65328, incoherent.debye_waller_values[1] )

            self.assertEqual( 8, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 27, 7, 2 ) )

        # the data is given explicitly
        chunk = MixedElastic(
                    coherent = CoherentElastic( [ 3 ], [ 1 ], [ 293.6, 800.0 ], [ 2 ],
                                                [ 1.059427e-3, 3.718355e-3, 4.237708e-3 ],
                                                [ [ 0.0, 9.364524e-3, 1.548925e-2 ],
                                                  [ 0.5, 8.318414e-3, 1.640584e-2 ] ] ),
                    incoherent = IncoherentElastic( 2.054202, [ 2 ], [ 2 ],
                                                    [ 293.6, 800. ],
                                                    [ 8.937898, 17.65328 ] ) )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = MixedElastic.from_string( self.chunk, 27, 7, 2 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = MixedElastic( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # wrong boundaries
        with self.assertRaises( Exception ) :

            chunk = MixedElastic(
                        coherent = CoherentElastic( [ 2 ], [ 1 ], [ 293.6, 800.0 ], [ 2 ],
                                                    [ 1.059427e-3, 3.718355e-3, 4.237708e-3 ],
                                                    [ [ 0.0, 9.364524e-3, 1.548925e-2 ],
                                                      [ 0.5, 8.318414e-3, 1.640584e-2 ] ] ),
                        incoherent = IncoherentElastic( 2.054202, [ 2 ], [ 2 ],
                                                        [ 293.6, 800. ],
                                                        [ 8.937898, 17.65328 ] ) )

        with self.assertRaises( Exception ) :

            chunk = MixedElastic.from_string( self.invalid, 27, 7, 2 )

if __name__ == '__main__' :

    unittest.main()
