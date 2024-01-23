# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF8.MT457 import Section
from ENDFtk.MF8.MT457 import AverageDecayEnergies
from ENDFtk.MF8.MT457 import DiscreteSpectrum
from ENDFtk.MF8.MT457 import ContinuousSpectrum
from ENDFtk.MF8.MT457 import DecaySpectrum
from ENDFtk.MF8.MT457 import DecayMode
from ENDFtk.MF8.MT457 import DecayModes
from ENDFtk.tree import Tape

class Test_ENDFtk_MF8_MT457_Section( unittest.TestCase ) :
    """Unit test for the Section class."""

    chunk = ( ' 9.524200+4 2.399801+2          2          1          0          23580 8457     \n'
              ' 4.449622+9 6.311520+7          0          0          6          03580 8457     \n'
              ' 4.008322+4 4.128931+3 5.373671+3 3.660206+2 2.441003+4 6.191754+23580 8457     \n'
              ' 5.000000+0-1.000000+0          0          0         18          33580 8457     \n'
              ' 4.000000+0 0.000000+0 5.637120+6 2.549510+2 4.590000-3 1.200000-43580 8457     \n'
              ' 3.000000+0 0.000000+0 4.860000+4 5.000000+1 9.954100-1 1.200000-43580 8457     \n'
              ' 6.000000+0 0.000000+0 1.884000+8 3.700000+6 1.60000-10 6.00000-113580 8457     \n'
              ' 0.000000+0 0.000000+0          0          0          6          23580 8457     \n'
              ' 1.000000+0 0.000000+0 2.107044+2 1.576284+1 0.000000+0 0.000000+03580 8457     \n'
              ' 4.863000+4 5.000000+1          0          0         12          03580 8457     \n'
              ' 3.000000+0 0.000000+0 1.420112-6 2.85306-10 0.000000+0 0.000000+03580 8457     \n'
              ' 7.010000+5 1.106180-2 0.000000+0 0.000000+0 3.315735+5 5.608008+33580 8457     \n'
              ' 4.935000+4 2.000000+1          0          0         12          03580 8457     \n'
              ' 4.000000+0 0.000000+0 1.335690-3 5.409179-5 0.000000+0 0.000000+03580 8457     \n'
              ' 8.209999-1 0.000000+0 0.000000+0 0.000000+0 6.160000-1 8.999999-33580 8457     \n'
              ' 0.000000+0 1.000000+0          1          0          6          03580 8457     \n'
              ' 0.000000+0 0.000000+0 3.107044+2 4.576284+1 5.000000-1 2.500000-13580 8457     \n'
              ' 4.000000+0 0.000000+0          0          0          1          33580 8457     \n'
              '          3          1                                            3580 8457     \n'
              ' 0.000000+0 6.133200-7 5.000000+5 6.133300-7 7.300000+6 6.02040-173580 8457     \n' )

    # TODO add more tests for MF7 MT4

    valid_TPID = 'Just a tape identifier                                                          \n'
    valid_SEND = '                                                                  3580 8  0     \n'
    valid_FEND = '                                                                  3580 0  0     \n'
    valid_MEND = '                                                                     0 0  0     \n'
    valid_TEND = '                                                                    -1 0  0     \n'
    invalid_SEND = '                                                                  3580 8457     \n'

    def test_section( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 457, chunk.MT )
            self.assertEqual( 457, chunk.section_number )

            self.assertEqual( 95242, chunk.ZA )
            self.assertAlmostEqual( 2.399801e+2, chunk.AWR )
            self.assertAlmostEqual( 2.399801e+2, chunk.atomic_weight_ratio )
            self.assertEqual( 2, chunk.LIS )
            self.assertEqual( 2, chunk.excited_state )
            self.assertEqual( 1, chunk.LISO )
            self.assertEqual( 1, chunk.isomeric_state )
            self.assertEqual( False, chunk.NST )
            self.assertEqual( False, chunk.is_stable )
            self.assertAlmostEqual( 5.0, chunk.spin )
            self.assertAlmostEqual( -1., chunk.parity )
            self.assertAlmostEqual( 4.449622e+9, chunk.T[0] )
            self.assertAlmostEqual( 6.311520e+7, chunk.T[1] )
            self.assertAlmostEqual( 4.449622e+9, chunk.half_life[0] )
            self.assertAlmostEqual( 6.311520e+7, chunk.half_life[1] )

            energies = chunk.average_decay_energies
            self.assertAlmostEqual( 4.449622e+9, energies.T[0] )
            self.assertAlmostEqual( 6.311520e+7, energies.T[1] )
            self.assertAlmostEqual( 4.449622e+9, energies.half_life[0] )
            self.assertAlmostEqual( 6.311520e+7, energies.half_life[1] )

            self.assertEqual( 3, energies.NCE )
            self.assertEqual( 3, energies.number_decay_energies )
            self.assertEqual( 3, len( energies.E ) )
            self.assertEqual( 3, len( energies.decay_energies ) )
            self.assertAlmostEqual( 4.008322e+4, energies.E[0][0] )
            self.assertAlmostEqual( 4.128931e+3, energies.E[0][1] )
            self.assertAlmostEqual( 5.373671e+3, energies.E[1][0] )
            self.assertAlmostEqual( 3.660206e+2, energies.E[1][1] )
            self.assertAlmostEqual( 2.441003e+4, energies.E[2][0] )
            self.assertAlmostEqual( 6.191754e+2, energies.E[2][1] )
            self.assertAlmostEqual( 4.008322e+4, energies.decay_energies[0][0] )
            self.assertAlmostEqual( 4.128931e+3, energies.decay_energies[0][1] )
            self.assertAlmostEqual( 5.373671e+3, energies.decay_energies[1][0] )
            self.assertAlmostEqual( 3.660206e+2, energies.decay_energies[1][1] )
            self.assertAlmostEqual( 2.441003e+4, energies.decay_energies[2][0] )
            self.assertAlmostEqual( 6.191754e+2, energies.decay_energies[2][1] )

            self.assertAlmostEqual( 4.008322e+4, energies.ELP[0] )
            self.assertAlmostEqual( 4.128931e+3, energies.ELP[1] )
            self.assertAlmostEqual( 4.008322e+4, energies.light_particle_decay_energy[0] )
            self.assertAlmostEqual( 4.128931e+3, energies.light_particle_decay_energy[1] )
            self.assertAlmostEqual( 5.373671e+3, energies.EEM[0] )
            self.assertAlmostEqual( 3.660206e+2, energies.EEM[1] )
            self.assertAlmostEqual( 5.373671e+3, energies.electromagnetic_decay_energy[0] )
            self.assertAlmostEqual( 3.660206e+2, energies.electromagnetic_decay_energy[1] )
            self.assertAlmostEqual( 2.441003e+4, energies.EHP[0] )
            self.assertAlmostEqual( 6.191754e+2, energies.EHP[1] )
            self.assertAlmostEqual( 2.441003e+4, energies.heavy_particle_decay_energy[0] )
            self.assertAlmostEqual( 6.191754e+2, energies.heavy_particle_decay_energy[1] )

            decaymodes = chunk.decay_modes
            self.assertAlmostEqual( 5.0, decaymodes.SPI )
            self.assertAlmostEqual( 5.0, decaymodes.spin )
            self.assertAlmostEqual( -1., decaymodes.PAR )
            self.assertAlmostEqual( -1., decaymodes.parity )

            modes = decaymodes.decay_modes
            self.assertEqual( 3, decaymodes.NDK )
            self.assertEqual( 3, len( modes ) )
            self.assertAlmostEqual( 4., modes[0].decay_chain )
            self.assertAlmostEqual( 0., modes[0].final_isomeric_state )
            self.assertAlmostEqual( 5.637120e+6, modes[0].Q[0] )
            self.assertAlmostEqual( 2.549510e+2, modes[0].Q[1] )
            self.assertAlmostEqual( 5.637120e+6, modes[0].q_value[0] )
            self.assertAlmostEqual( 2.549510e+2, modes[0].q_value[1] )
            self.assertAlmostEqual( 4.590000e-3, modes[0].BR[0] )
            self.assertAlmostEqual( 1.200000e-4, modes[0].BR[1] )
            self.assertAlmostEqual( 4.590000e-3, modes[0].branching_ratio[0] )
            self.assertAlmostEqual( 1.200000e-4, modes[0].branching_ratio[1] )
            self.assertAlmostEqual( 3., modes[1].decay_chain )
            self.assertAlmostEqual( 0., modes[1].final_isomeric_state )
            self.assertAlmostEqual( 4.860000e+4, modes[1].Q[0] )
            self.assertAlmostEqual( 5.000000e+1, modes[1].Q[1] )
            self.assertAlmostEqual( 4.860000e+4, modes[1].q_value[0] )
            self.assertAlmostEqual( 5.000000e+1, modes[1].q_value[1] )
            self.assertAlmostEqual( 9.954100e-1, modes[1].BR[0] )
            self.assertAlmostEqual( 1.200000e-4, modes[1].BR[1] )
            self.assertAlmostEqual( 9.954100e-1, modes[1].branching_ratio[0] )
            self.assertAlmostEqual( 1.200000e-4, modes[1].branching_ratio[1] )
            self.assertAlmostEqual( 6., modes[2].decay_chain )
            self.assertAlmostEqual( 0., modes[2].final_isomeric_state )
            self.assertAlmostEqual( 1.884000e+8, modes[2].Q[0] )
            self.assertAlmostEqual( 3.700000e+6, modes[2].Q[1] )
            self.assertAlmostEqual( 1.884000e+8, modes[2].q_value[0] )
            self.assertAlmostEqual( 3.700000e+6, modes[2].q_value[1] )
            self.assertAlmostEqual( 1.60000e-10, modes[2].BR[0] )
            self.assertAlmostEqual( 6.00000e-11, modes[2].BR[1] )
            self.assertAlmostEqual( 1.60000e-10, modes[2].branching_ratio[0] )
            self.assertAlmostEqual( 6.00000e-11, modes[2].branching_ratio[1] )

            self.assertAlmostEqual( 2, chunk.NSP )
            self.assertAlmostEqual( 2, chunk.number_decay_spectra )
            self.assertAlmostEqual( 2, len( chunk.decay_spectra ) )

            spectrum1 = chunk.decay_spectra[0]
            self.assertAlmostEqual( 0., spectrum1.STYP )
            self.assertAlmostEqual( 0., spectrum1.radiation_type )

            self.assertAlmostEqual( 0, spectrum1.LCON )
            self.assertAlmostEqual( 0, spectrum1.spectral_type_flag )
            self.assertAlmostEqual( 0, spectrum1.LCOV )
            self.assertAlmostEqual( 0, spectrum1.covariance_flag )
            self.assertAlmostEqual( 2, spectrum1.NER )
            self.assertAlmostEqual( 2, spectrum1.number_discrete_spectra )

            self.assertAlmostEqual( 1., spectrum1.FD[0] )
            self.assertAlmostEqual( 0., spectrum1.FD[1] )
            self.assertAlmostEqual( 1., spectrum1.discrete_normalisation_factor[0] )
            self.assertAlmostEqual( 0., spectrum1.discrete_normalisation_factor[1] )
            self.assertAlmostEqual( 0., spectrum1.FC[0] )
            self.assertAlmostEqual( 0., spectrum1.FC[1] )
            self.assertAlmostEqual( 0., spectrum1.continuous_normalisation_factor[0] )
            self.assertAlmostEqual( 0., spectrum1.continuous_normalisation_factor[1] )
            self.assertAlmostEqual( 2.107044e+2, spectrum1.ERAV[0] )
            self.assertAlmostEqual( 1.576284e+1, spectrum1.ERAV[1] )
            self.assertAlmostEqual( 2.107044e+2, spectrum1.average_decay_energy[0] )
            self.assertAlmostEqual( 1.576284e+1, spectrum1.average_decay_energy[1] )

            self.assertAlmostEqual( True, None == spectrum1.continuous_spectrum )

            discrete = spectrum1.discrete_spectra
            self.assertAlmostEqual( 3., discrete[0].RTYP )
            self.assertAlmostEqual( 3., discrete[0].decay_chain )
            self.assertAlmostEqual( 12, discrete[0].NT )
            self.assertAlmostEqual( 4.863000e+4, discrete[0].ER[0] )
            self.assertAlmostEqual( 5.000000e+1, discrete[0].ER[1] )
            self.assertAlmostEqual( 4.863000e+4, discrete[0].discrete_energy[0] )
            self.assertAlmostEqual( 5.000000e+1, discrete[0].discrete_energy[1] )
            self.assertAlmostEqual( 1.420112e-6, discrete[0].RI[0] )
            self.assertAlmostEqual( 2.85306e-10, discrete[0].RI[1] )
            self.assertAlmostEqual( 1.420112e-6, discrete[0].relative_intensity[0] )
            self.assertAlmostEqual( 2.85306e-10, discrete[0].relative_intensity[1] )
            self.assertAlmostEqual( 0., discrete[0].TYPE )
            self.assertAlmostEqual( 0., discrete[0].type )
            self.assertAlmostEqual( 0.0, discrete[0].RIS[0] )
            self.assertAlmostEqual( 0.0, discrete[0].RIS[1] )
            self.assertAlmostEqual( 0.0, discrete[0].internal_pair_formation_coefficient[0] )
            self.assertAlmostEqual( 0.0, discrete[0].internal_pair_formation_coefficient[1] )
            self.assertAlmostEqual( 7.010000e+5, discrete[0].RICC[0] )
            self.assertAlmostEqual( 1.106180e-2, discrete[0].RICC[1] )
            self.assertAlmostEqual( 7.010000e+5, discrete[0].total_internal_conversion_coefficient[0] )
            self.assertAlmostEqual( 1.106180e-2, discrete[0].total_internal_conversion_coefficient[1] )
            self.assertAlmostEqual( 0.0, discrete[0].RICK[0] )
            self.assertAlmostEqual( 0.0, discrete[0].RICK[1] )
            self.assertAlmostEqual( 0.0, discrete[0].internal_conversion_coefficient_k_shell[0] )
            self.assertAlmostEqual( 0.0, discrete[0].internal_conversion_coefficient_k_shell[1] )
            self.assertAlmostEqual( 3.315735e+5, discrete[0].RICL[0] )
            self.assertAlmostEqual( 5.608008e+3, discrete[0].RICL[1] )
            self.assertAlmostEqual( 3.315735e+5, discrete[0].internal_conversion_coefficient_l_shell[0] )
            self.assertAlmostEqual( 5.608008e+3, discrete[0].internal_conversion_coefficient_l_shell[1] )
            self.assertAlmostEqual( 4., discrete[1].decay_chain )
            self.assertAlmostEqual( 12, discrete[1].NT )
            self.assertAlmostEqual( 4.935000e+4, discrete[1].ER[0] )
            self.assertAlmostEqual( 2.000000e+1, discrete[1].ER[1] )
            self.assertAlmostEqual( 4.935000e+4, discrete[1].discrete_energy[0] )
            self.assertAlmostEqual( 2.000000e+1, discrete[1].discrete_energy[1] )
            self.assertAlmostEqual( 1.335690e-3, discrete[1].RI[0] )
            self.assertAlmostEqual( 5.409179e-5, discrete[1].RI[1] )
            self.assertAlmostEqual( 1.335690e-3, discrete[1].relative_intensity[0] )
            self.assertAlmostEqual( 5.409179e-5, discrete[1].relative_intensity[1] )
            self.assertAlmostEqual( 0., discrete[1].TYPE )
            self.assertAlmostEqual( 0., discrete[1].type )
            self.assertAlmostEqual( 0.0, discrete[1].RIS[0] )
            self.assertAlmostEqual( 0.0, discrete[1].RIS[1] )
            self.assertAlmostEqual( 0.0, discrete[1].internal_pair_formation_coefficient[0] )
            self.assertAlmostEqual( 0.0, discrete[1].internal_pair_formation_coefficient[1] )
            self.assertAlmostEqual( 8.209999e-1, discrete[1].RICC[0] )
            self.assertAlmostEqual( 0.000000e+0, discrete[1].RICC[1] )
            self.assertAlmostEqual( 8.209999e-1, discrete[1].total_internal_conversion_coefficient[0] )
            self.assertAlmostEqual( 0.000000e+0, discrete[1].total_internal_conversion_coefficient[1] )
            self.assertAlmostEqual( 0.0, discrete[1].RICK[0] )
            self.assertAlmostEqual( 0.0, discrete[1].RICK[1] )
            self.assertAlmostEqual( 0.0, discrete[1].internal_conversion_coefficient_k_shell[0] )
            self.assertAlmostEqual( 0.0, discrete[1].internal_conversion_coefficient_k_shell[1] )
            self.assertAlmostEqual( 6.160000e-1, discrete[1].RICL[0] )
            self.assertAlmostEqual( 8.999999e-3, discrete[1].RICL[1] )
            self.assertAlmostEqual( 6.160000e-1, discrete[1].internal_conversion_coefficient_l_shell[0] )
            self.assertAlmostEqual( 8.999999e-3, discrete[1].internal_conversion_coefficient_l_shell[1] )

            spectrum2 = chunk.decay_spectra[1]
            self.assertAlmostEqual( 1., spectrum2.STYP )
            self.assertAlmostEqual( 1., spectrum2.radiation_type )

            self.assertAlmostEqual( 1, spectrum2.LCON )
            self.assertAlmostEqual( 1, spectrum2.spectral_type_flag )
            self.assertAlmostEqual( 0, spectrum2.LCOV )
            self.assertAlmostEqual( 0, spectrum2.covariance_flag )
            self.assertAlmostEqual( 0, spectrum2.NER )
            self.assertAlmostEqual( 0, spectrum2.number_discrete_spectra )

            self.assertAlmostEqual( 0., spectrum2.FD[0] )
            self.assertAlmostEqual( 0., spectrum2.FD[1] )
            self.assertAlmostEqual( 0., spectrum2.discrete_normalisation_factor[0] )
            self.assertAlmostEqual( 0., spectrum2.discrete_normalisation_factor[1] )
            self.assertAlmostEqual( 0.5, spectrum2.FC[0] )
            self.assertAlmostEqual( 0.25, spectrum2.FC[1] )
            self.assertAlmostEqual( 0.5, spectrum2.continuous_normalisation_factor[0] )
            self.assertAlmostEqual( 0.25, spectrum2.continuous_normalisation_factor[1] )
            self.assertAlmostEqual( 3.107044e+2, spectrum2.ERAV[0] )
            self.assertAlmostEqual( 4.576284e+1, spectrum2.ERAV[1] )
            self.assertAlmostEqual( 3.107044e+2, spectrum2.average_decay_energy[0] )
            self.assertAlmostEqual( 4.576284e+1, spectrum2.average_decay_energy[1] )

            self.assertAlmostEqual( True, None != spectrum2.continuous_spectrum )

            continuous = spectrum2.continuous_spectrum
            self.assertAlmostEqual( 4., continuous.RTYP )
            self.assertAlmostEqual( 4., continuous.decay_chain )
            self.assertAlmostEqual( 3, continuous.NP )
            self.assertAlmostEqual( 1, continuous.NR )
            self.assertAlmostEqual( 1, len( continuous.interpolants ) )
            self.assertAlmostEqual( 1, len( continuous.boundaries ) )
            self.assertAlmostEqual( 1, continuous.interpolants[0] )
            self.assertAlmostEqual( 3, continuous.boundaries[0] )
            self.assertAlmostEqual( 3, len( continuous.energies ) )
            self.assertAlmostEqual( 3, len( continuous.spectral_values ) )
            self.assertAlmostEqual( 0.0, continuous.energies[0] )
            self.assertAlmostEqual( 5e+5, continuous.energies[1] )
            self.assertAlmostEqual( 7.3e+6, continuous.energies[2] )
            self.assertAlmostEqual( 6.133200e-7, continuous.spectral_values[0] )
            self.assertAlmostEqual( 6.133300e-7, continuous.spectral_values[1] )
            self.assertAlmostEqual( 6.02040e-17, continuous.spectral_values[2] )

            self.assertAlmostEqual( 20, chunk.NC )

            # verify string
            self.assertEqual( self.chunk + self.valid_SEND,
                              chunk.to_string( 3580, 8 ) )

        # the data is given explicitly
        chunk = Section( zaid = 95242, awr = 2.399801e+2, lis = 2, liso = 1,
                         energies = AverageDecayEnergies( [ 4.449622e+9, 6.311520e+7 ],
                                                          [ [ 4.008322e+4, 4.128931e+3 ],
                                                            [ 5.373671e+3, 3.660206e+2 ],
                                                            [ 2.441003e+4, 6.191754e+2 ] ] ),
                         modes = DecayModes( 5., -1.,
                                             [ DecayMode( 4., 0., 5.637120e+6, 2.549510e+2, 4.590000e-3, 1.200000e-4 ),
                                               DecayMode( 3., 0., 4.860000e+4, 5.000000e+1, 9.954100e-1, 1.200000e-4 ),
                                               DecayMode( 6., 0., 1.884000e+8, 3.700000e+6, 1.60000e-10, 6.00000e-11 ) ] ),
                         spectra = [ DecaySpectrum( 0.0, [ 1., 0. ], [ 2.107044e+2, 1.576284e+1 ],
                                                    [ DiscreteSpectrum( 3., [ 4.863000e+4, 5.000000e+1 ],
                                                                        [ 1.420112e-6, 2.85306e-10 ], 0.0,
                                                                        [ 0.0, 0.0 ], [ 7.010000e+5, 1.106180e-2 ], [ 0.0, 0.0 ],
                                                                        [ 3.315735e+5, 5.608008e+3 ] ),
                                                      DiscreteSpectrum( 4., [ 4.935000e+4, 2.000000e+1 ],
                                                                        [ 1.335690e-3, 5.409179e-5 ], 0.0,
                                                                        [ 0.0, 0.0 ], [ 8.209999e-1, 0.000000e+0 ], [ 0.0, 0.0 ],
                                                                        [ 6.160000e-1, 8.999999e-3 ] ) ] ),
                                     DecaySpectrum( 1.0, [ 0.5, 0.25 ], [ 3.107044e+2, 4.576284e+1 ],
                                                    ContinuousSpectrum( 4., [ 3 ], [ 1 ], [ 0.0, 5e+5, 7.3e+6 ],
                                                                        [ 6.133200e-7, 6.133300e-7, 6.02040e-17 ] ) ) ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk + self.valid_SEND )

        verify_chunk( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.material( 3580 ).file( 8 ).section( 457 ).parse()

        verify_chunk( self, chunk )

        # the data is copied
        copy = Section( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # illegal SEND
        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.chunk + self.invalid_SEND )

if __name__ == '__main__' :

    unittest.main()
