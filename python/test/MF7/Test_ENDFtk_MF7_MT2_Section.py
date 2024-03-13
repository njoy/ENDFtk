# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF7.MT2 import Section
from ENDFtk.MF7.MT2 import CoherentElastic
from ENDFtk.MF7.MT2 import IncoherentElastic
from ENDFtk.tree import Tape

class Test_ENDFtk_MF7_MT2_Section( unittest.TestCase ) :
    """Unit test for the Section class."""

    chunk_coherent = ( ' 1.070000+2 1.000000+0          1          0          0          0  27 7  2     \n'
                       ' 2.936000+2 0.000000+0          0          0          1          3  27 7  2     \n'
                       '          3          1                                              27 7  2     \n'
                       ' 1.059427-3 0.000000+0 3.718355-3 9.364524-3 4.237708-3 1.548925-2  27 7  2     \n' )

    chunk_incoherent = ( ' 1.070000+2 1.000000+0          2          0          0          0  27 7  2     \n'
                         ' 8.198006+1 0.000000+0          0          0          1          3  27 7  2     \n'
                         '          3          2                                              27 7  2     \n'
                         ' 2.960000+2 8.486993+0 4.000000+2 9.093191+0 5.000000+2 9.828159+0  27 7  2     \n' )

    valid_TPID = 'Just a tape identifier                                                          \n'
    valid_SEND = '                                                                    27 7  0     \n'
    valid_FEND = '                                                                    27 0  0     \n'
    valid_MEND = '                                                                     0 0  0     \n'
    valid_TEND = '                                                                    -1 0  0     \n'
    invalid_SEND = '                                                                    27 7  2     \n'

    def test_section( self ) :

        def verify_chunk_coherent( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.MT )
            self.assertEqual( 2, chunk.section_number )

            self.assertEqual( 107, chunk.ZA )
            self.assertEqual( 107, chunk.target_identifier )
            self.assertAlmostEqual( 1., chunk.AWR )
            self.assertAlmostEqual( 1., chunk.atomic_weight_ratio )
            self.assertEqual( 1, chunk.LTHR )
            self.assertEqual( 1, chunk.elastic_scattering_type )

            law = chunk.scattering_law
            self.assertEqual( True, isinstance( law, CoherentElastic ) )

            self.assertEqual( 1, law.LTHR )
            self.assertEqual( 1, law.elastic_scattering_type )
            self.assertEqual( 0, law.LT )
            self.assertEqual( 0, law.temperature_dependence_flag )
            self.assertEqual( 1, law.NT )
            self.assertEqual( 1, law.number_temperatures )
            self.assertEqual( 3, law.NP )
            self.assertEqual( 3, law.number_bragg_edges )

            self.assertEqual( 1, law.NR )
            self.assertEqual( 1, len( law.boundaries ) )
            self.assertEqual( 3, law.boundaries[0] )
            self.assertEqual( 1, len( law.interpolants ) )
            self.assertEqual( 1, law.interpolants[0] )

            self.assertEqual( 1, len( law.T ) )
            self.assertEqual( 1, len( law.temperatures ) )
            self.assertAlmostEqual( 293.6, law.T[0] )
            self.assertAlmostEqual( 293.6, law.temperatures[0] )

            self.assertEqual( 3, len( law.E ) )
            self.assertEqual( 3, len( law.energies ) )
            self.assertAlmostEqual( 1.059427e-3, law.E[0] )
            self.assertAlmostEqual( 3.718355e-3, law.E[1] )
            self.assertAlmostEqual( 4.237708e-3, law.E[2] )
            self.assertAlmostEqual( 1.059427e-3, law.energies[0] )
            self.assertAlmostEqual( 3.718355e-3, law.energies[1] )
            self.assertAlmostEqual( 4.237708e-3, law.energies[2] )

            self.assertEqual( 0, len( law.LI ) )
            self.assertEqual( 0, len( law.temperature_interpolants ) )

            self.assertEqual( 1, len( law.thermal_scattering_values ) )
            self.assertEqual( 3, len( law.thermal_scattering_values[0] ) )
            self.assertAlmostEqual( 0.0, law.thermal_scattering_values[0][0] )
            self.assertAlmostEqual( 9.364524e-3, law.thermal_scattering_values[0][1] )
            self.assertAlmostEqual( 1.548925e-2, law.thermal_scattering_values[0][2] )

            self.assertEqual( 1, len( law.S ) )
            self.assertEqual( 3, len( law.S[0] ) )
            self.assertAlmostEqual( 0.0, law.S[0][0] )
            self.assertAlmostEqual( 9.364524e-3, law.S[0][1] )
            self.assertAlmostEqual( 1.548925e-2, law.S[0][2] )

            self.assertEqual( 4, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_coherent + self.valid_SEND,
                              chunk.to_string( 27, 7 ) )

        def verify_chunk_incoherent( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.MT )
            self.assertEqual( 2, chunk.section_number )

            self.assertEqual( 107, chunk.ZA )
            self.assertEqual( 107, chunk.target_identifier )
            self.assertEqual( 1., chunk.AWR )
            self.assertEqual( 1., chunk.atomic_weight_ratio )
            self.assertEqual( 2, chunk.LTHR )
            self.assertEqual( 2, chunk.elastic_scattering_type )

            law = chunk.scattering_law
            self.assertEqual( True, isinstance( law, IncoherentElastic ) )

            self.assertEqual( 2, law.LTHR )
            self.assertEqual( 2, law.elastic_scattering_type )
            self.assertAlmostEqual( 8.198006e+1, law.SB )
            self.assertAlmostEqual( 8.198006e+1, law.bound_cross_section )
            self.assertEqual( 3, law.NP )
            self.assertEqual( 3, law.number_temperatures )
            self.assertEqual( 1, law.NR )
            self.assertEqual( 1, len( law.interpolants ) )
            self.assertEqual( 1, len( law.boundaries ) )
            self.assertEqual( 2, law.interpolants[0] )
            self.assertEqual( 3, law.boundaries[0] )
            self.assertEqual( 3, len( law.temperatures ) )
            self.assertEqual( 3, len( law.debye_waller_values ) )
            self.assertAlmostEqual( 296., law.temperatures[0] )
            self.assertAlmostEqual( 400., law.temperatures[1] )
            self.assertAlmostEqual( 500., law.temperatures[2] )
            self.assertAlmostEqual( 8.486993e+0, law.debye_waller_values[0] )
            self.assertAlmostEqual( 9.093191e+0, law.debye_waller_values[1] )
            self.assertAlmostEqual( 9.828159e+0, law.debye_waller_values[2] )

            self.assertEqual( 4, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_incoherent + self.valid_SEND,
                              chunk.to_string( 27, 7 ) )

        # the data is given explicitly
        chunk = Section( zaid = 107, awr = 1.,
                         law = CoherentElastic(
                                   293.6, [ 3 ], [ 1 ],
                                   [ 1.059427e-3, 3.718355e-3,  4.237708e-3 ],
                                   [ 0.0, 9.364524e-3, 1.548925e-2 ] ) )

        verify_chunk_coherent( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk_coherent + self.valid_SEND )

        verify_chunk_coherent( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk_coherent +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.material( 27 ).file( 7 ).section( 2 ).parse()

        verify_chunk_coherent( self, chunk )

        # the data is copied
        copy = Section( chunk )

        verify_chunk_coherent( self, copy )

        # the data is given explicitly
        chunk = Section( zaid = 107., awr = 1.,
                         law = IncoherentElastic(
                                    8.198006e+1, [ 3 ], [ 2 ],
                                    [ 296., 400., 500. ],
                                    [ 8.486993e+0, 9.093191e+0, 9.828159e+0 ] ) )

        verify_chunk_incoherent( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk_incoherent + self.valid_SEND )

        verify_chunk_incoherent( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk_incoherent +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.material( 27 ).file( 7 ).section( 2 ).parse()

        verify_chunk_incoherent( self, chunk )

        # the data is copied
        copy = Section( chunk )

        verify_chunk_incoherent( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # illegal SEND
        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.chunk + self.invalid_SEND )

if __name__ == '__main__' :

    unittest.main()
