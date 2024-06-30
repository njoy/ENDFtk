# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF7.MT4 import Section
from ENDFtk.MF7.MT4 import AnalyticalFunctions
from ENDFtk.MF7.MT4 import EffectiveTemperature
from ENDFtk.MF7.MT4 import ScatteringLawConstants
from ENDFtk.tree import Tape

class Test_ENDFtk_MF7_MT4_Section( unittest.TestCase ) :
    """Unit test for the Section class."""

    chunk_analytical_functions = ( " 1.270000+2 8.934780+0          0          1          0          0  27 7  4     \n"
                                   " 0.000000+0 0.000000+0          0          0          6          0  27 7  4     \n"
                                   " 0.000000+0 1.976285+2 8.934780+0 5.000001+0 0.000000+0 1.000000+0  27 7  4     \n"
                                   " 0.000000+0 0.000000+0          0          0          1          3  27 7  4     \n"
                                   "          3          2                                              27 7  4     \n"
                                   " 2.936000+2 5.332083+2 6.000000+2 7.354726+2 1.200000+3 1.270678+3  27 7  4     \n" )

    # TODO add more tests for MF7 MT4

    valid_TPID = 'Just a tape identifier                                                          \n'
    valid_SEND = '                                                                    27 7  0     \n'
    valid_FEND = '                                                                    27 0  0     \n'
    valid_MEND = '                                                                     0 0  0     \n'
    valid_TEND = '                                                                    -1 0  0     \n'
    invalid_SEND = '                                                                    27 7  4     \n'

    def test_section( self ) :

        def verify_chunk_analytical_functions( self, chunk ) :

            # verify content
            self.assertEqual( 4, chunk.MT )
            self.assertEqual( 4, chunk.section_number )

            self.assertEqual( 127, chunk.ZA )
            self.assertEqual( 127, chunk.target_identifier )
            self.assertAlmostEqual( 8.934780e+0, chunk.AWR )
            self.assertAlmostEqual( 8.934780e+0, chunk.atomic_weight_ratio )
            self.assertEqual( 1, chunk.LAT )
            self.assertEqual( 1, chunk.temperature_option )
            self.assertEqual( 0, chunk.LASYM )
            self.assertEqual( 0, chunk.symmetry_option )

            barray = chunk.constants
            self.assertEqual( 0, barray.LLN )
            self.assertEqual( 0, barray.sab_storage_type )
            self.assertEqual( 6, barray.NI )
            self.assertEqual( 6, barray.number_constants )
            self.assertEqual( 0, barray.NS )
            self.assertEqual( 0, barray.number_non_principal_scatterers )

            self.assertAlmostEqual( 1.976285e+2, barray.epsilon )
            self.assertAlmostEqual( 5.000001e+0, barray.upper_energy_limit )
            self.assertEqual( 1, len( barray.total_free_cross_sections ) )
            self.assertAlmostEqual( 0.000000+0, barray.total_free_cross_sections[0] )
            self.assertEqual( 1, len( barray.atomic_weight_ratios ) )
            self.assertAlmostEqual( 8.934780e+0, barray.atomic_weight_ratios[0] )
            self.assertEqual( 1, len( barray.number_atoms ) )
            self.assertAlmostEqual( 1., barray.number_atoms[0] )
            self.assertEqual( 0, len( barray.analytical_function_types ) )

            law = chunk.scattering_law
            self.assertEqual( True, isinstance( law, AnalyticalFunctions ) )
            self.assertEqual( 0, law.NC )

            temp = chunk.principal_effective_temperature
            self.assertEqual( 3, temp.NT )
            self.assertEqual( 3, temp.number_temperatures )
            self.assertEqual( 1, temp.NR )
            self.assertEqual( 1, len( temp.interpolants ) )
            self.assertEqual( 1, len( temp.boundaries ) )
            self.assertEqual( 2, temp.interpolants[0] )
            self.assertEqual( 3, temp.boundaries[0] )
            self.assertEqual( 3, len( temp.moderator_temperatures ) )
            self.assertEqual( 3, len( temp.effective_temperatures ) )
            self.assertAlmostEqual( 293.6, temp.moderator_temperatures[0] )
            self.assertAlmostEqual( 600., temp.moderator_temperatures[1] )
            self.assertAlmostEqual( 1200., temp.moderator_temperatures[2] )
            self.assertAlmostEqual( 5.332083e+2, temp.effective_temperatures[0] )
            self.assertAlmostEqual( 7.354726e+2, temp.effective_temperatures[1] )
            self.assertAlmostEqual( 1.270678e+3, temp.effective_temperatures[2] )

            self.assertEqual( 0, len( chunk.secondary_effective_temperatures ) )

            self.assertEqual( 6, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_analytical_functions + self.valid_SEND,
                              chunk.to_string( 27, 7 ) )

        # the data is given explicitly
        chunk = Section( zaid = 127, awr = 8.934780e+0, lasym = 0, lat = 1,
                         constants = ScatteringLawConstants( 0, 1.976285e+2, 5.000001e+0, 0, 8.934780e+0, 1 ),
                         law = AnalyticalFunctions(),
                         principal = EffectiveTemperature( [ 3 ], [ 2 ],
                                                           [ 293.6, 600., 1200. ],
                                                           [ 5.332083e+2, 7.354726e+2, 1.270678e+3 ] ) )

        verify_chunk_analytical_functions( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk_analytical_functions + self.valid_SEND )

        verify_chunk_analytical_functions( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk_analytical_functions +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.materials.front().file( 7 ).section( 4 ).parse()

        verify_chunk_analytical_functions( self, chunk )

        # the data is copied
        copy = Section( chunk )

        verify_chunk_analytical_functions( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # illegal SEND
        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.chunk_analytical_functions + self.invalid_SEND )

if __name__ == '__main__' :

    unittest.main()
