# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF8.MT457 import DecaySpectrum
from ENDFtk.MF8.MT457 import DiscreteSpectrum
from ENDFtk.MF8.MT457 import ContinuousSpectrum

class Test_ENDFtk_MF8_MT457_DecaySpectrum( unittest.TestCase ) :
    """Unit test for the DecaySpectrum class."""

    chunk_lcon_0 = ( ' 0.000000+0 0.000000+0          0          0          6          23580 8457     \n'
                     ' 1.000000+0 0.000000+0 2.107044+2 1.576284+1 0.000000+0 0.000000+03580 8457     \n'
                     ' 4.863000+4 5.000000+1          0          0         12          03580 8457     \n'
                     ' 3.000000+0 0.000000+0 1.420112-6 2.85306-10 0.000000+0 0.000000+03580 8457     \n'
                     ' 7.010000+5 1.106180-2 0.000000+0 0.000000+0 3.315735+5 5.608008+33580 8457     \n'
                     ' 4.935000+4 2.000000+1          0          0         12          03580 8457     \n'
                     ' 4.000000+0 0.000000+0 1.335690-3 5.409179-5 0.000000+0 0.000000+03580 8457     \n'
                     ' 8.209999-1 0.000000+0 0.000000+0 0.000000+0 6.160000-1 8.999999-33580 8457     \n' )

    chunk_lcon_1 = ( ' 0.000000+0 0.000000+0          1          0          6          03580 8457     \n'
                     ' 0.000000+0 0.000000+0 2.107044+2 1.576284+1 5.000000-1 2.500000-13580 8457     \n'
                     ' 4.000000+0 0.000000+0          0          0          1          33580 8457     \n'
                     '          3          1                                            3580 8457     \n'
                     ' 0.000000+0 6.133200-7 5.000000+5 6.133300-7 7.300000+6 6.02040-173580 8457     \n' )

    chunk_lcon_2 = ( ' 0.000000+0 0.000000+0          2          0          6          23580 8457     \n'
                     ' 1.000000+0 0.000000+0 2.107044+2 1.576284+1 5.000000-1 2.500000-13580 8457     \n'
                     ' 4.863000+4 5.000000+1          0          0         12          03580 8457     \n'
                     ' 3.000000+0 0.000000+0 1.420112-6 2.85306-10 0.000000+0 0.000000+03580 8457     \n'
                     ' 7.010000+5 1.106180-2 0.000000+0 0.000000+0 3.315735+5 5.608008+33580 8457     \n'
                     ' 4.935000+4 2.000000+1          0          0         12          03580 8457     \n'
                     ' 4.000000+0 0.000000+0 1.335690-3 5.409179-5 0.000000+0 0.000000+03580 8457     \n'
                     ' 8.209999-1 0.000000+0 0.000000+0 0.000000+0 6.160000-1 8.999999-33580 8457     \n'
                     ' 4.000000+0 0.000000+0          0          0          1          33580 8457     \n'
                     '          3          1                                            3580 8457     \n'
                     ' 0.000000+0 6.133200-7 5.000000+5 6.133300-7 7.300000+6 6.02040-173580 8457     \n' )

    invalid = ( ' 0.000000+0 0.000000+0          0          1          6          23580 8457     \n'
                ' 1.000000+0 0.000000+0 2.107044+2 1.576284+1 0.000000+0 0.000000+03580 8457     \n'
                ' 4.863000+4 5.000000+1          0          0         12          03580 8457     \n'
                ' 3.000000+0 0.000000+0 1.420112-6 2.85306-10 0.000000+0 0.000000+03580 8457     \n'
                ' 7.010000+5 1.106180-2 0.000000+0 0.000000+0 3.315735+5 5.608008+33580 8457     \n'
                ' 4.935000+4 2.000000+1          0          0         12          03580 8457     \n'
                ' 4.000000+0 0.000000+0 1.335690-3 5.409179-5 0.000000+0 0.000000+03580 8457     \n'
                ' 8.209999-1 0.000000+0 0.000000+0 0.000000+0 6.160000-1 8.999999-33580 8457     \n' )

    def test_component( self ) :

        def verify_chunk_lcon_0( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 0., chunk.STYP )
            self.assertAlmostEqual( 0., chunk.radiation_type )

            self.assertEqual( 0, chunk.LCON )
            self.assertEqual( 0, chunk.spectral_type_flag )
            self.assertEqual( 0, chunk.LCOV )
            self.assertEqual( 0, chunk.covariance_flag )
            self.assertEqual( 2, chunk.NER )
            self.assertEqual( 2, chunk.number_discrete_spectra )

            self.assertAlmostEqual( 1., chunk.FD[0] )
            self.assertAlmostEqual( 0., chunk.FD[1] )
            self.assertAlmostEqual( 1., chunk.discrete_normalisation_factor[0] )
            self.assertAlmostEqual( 0., chunk.discrete_normalisation_factor[1] )
            self.assertAlmostEqual( 0., chunk.FC[0] )
            self.assertAlmostEqual( 0., chunk.FC[1] )
            self.assertAlmostEqual( 0., chunk.continuous_normalisation_factor[0] )
            self.assertAlmostEqual( 0., chunk.continuous_normalisation_factor[1] )
            self.assertAlmostEqual( 2.107044e+2, chunk.ERAV[0] )
            self.assertAlmostEqual( 1.576284e+1, chunk.ERAV[1] )
            self.assertAlmostEqual( 2.107044e+2, chunk.average_decay_energy[0] )
            self.assertAlmostEqual( 1.576284e+1, chunk.average_decay_energy[1] )

            self.assertEqual( None, chunk.continuous_spectrum )

            discrete = chunk.discrete_spectra
            self.assertAlmostEqual( 3., discrete[0].RTYP )
            self.assertAlmostEqual( 3., discrete[0].decay_chain )
            self.assertEqual( 12, discrete[0].NT )
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
            self.assertAlmostEqual( 4., discrete[1].RTYP )
            self.assertAlmostEqual( 4., discrete[1].decay_chain )
            self.assertEqual( 12, discrete[1].NT )
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

            self.assertEqual( 8, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_lcon_0, chunk.to_string( 3580, 8, 457 ) )

        def verify_chunk_lcon_1( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 0., chunk.STYP )
            self.assertAlmostEqual( 0., chunk.radiation_type )

            self.assertEqual( 1, chunk.LCON )
            self.assertEqual( 1, chunk.spectral_type_flag )
            self.assertEqual( 0, chunk.LCOV )
            self.assertEqual( 0, chunk.covariance_flag )
            self.assertEqual( 0, chunk.NER )
            self.assertEqual( 0, chunk.number_discrete_spectra )

            self.assertAlmostEqual( 0., chunk.FD[0] )
            self.assertAlmostEqual( 0., chunk.FD[1] )
            self.assertAlmostEqual( 0., chunk.discrete_normalisation_factor[0] )
            self.assertAlmostEqual( 0., chunk.discrete_normalisation_factor[1] )
            self.assertAlmostEqual( 0.5, chunk.FC[0] )
            self.assertAlmostEqual( 0.25, chunk.FC[1] )
            self.assertAlmostEqual( 0.5, chunk.continuous_normalisation_factor[0] )
            self.assertAlmostEqual( 0.25, chunk.continuous_normalisation_factor[1] )
            self.assertAlmostEqual( 2.107044e+2, chunk.ERAV[0] )
            self.assertAlmostEqual( 1.576284e+1, chunk.ERAV[1] )
            self.assertAlmostEqual( 2.107044e+2, chunk.average_decay_energy[0] )
            self.assertAlmostEqual( 1.576284e+1, chunk.average_decay_energy[1] )

            self.assertEqual( True, None != chunk.continuous_spectrum )

            continuous = chunk.continuous_spectrum
            self.assertAlmostEqual( 4., continuous.RTYP )
            self.assertAlmostEqual( 4., continuous.decay_chain )
            self.assertEqual( 3, continuous.NP )
            self.assertEqual( 1, continuous.NR )
            self.assertEqual( 1, len( continuous.interpolants ) )
            self.assertEqual( 1, len( continuous.boundaries ) )
            self.assertEqual( 1, continuous.interpolants[0] )
            self.assertEqual( 3, continuous.boundaries[0] )
            self.assertEqual( 3, len( continuous.energies ) )
            self.assertEqual( 3, len( continuous.spectral_values ) )
            self.assertAlmostEqual( 0.0, continuous.energies[0] )
            self.assertAlmostEqual( 5e+5, continuous.energies[1] )
            self.assertAlmostEqual( 7.3e+6, continuous.energies[2] )
            self.assertAlmostEqual( 6.133200e-7, continuous.spectral_values[0] )
            self.assertAlmostEqual( 6.133300e-7, continuous.spectral_values[1] )
            self.assertAlmostEqual( 6.02040e-17, continuous.spectral_values[2] )

            self.assertEqual( 5, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_lcon_1, chunk.to_string( 3580, 8, 457 ) )

        def verify_chunk_lcon_2( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 0., chunk.STYP )
            self.assertAlmostEqual( 0., chunk.radiation_type )

            self.assertEqual( 2, chunk.LCON )
            self.assertEqual( 2, chunk.spectral_type_flag )
            self.assertEqual( 0, chunk.LCOV )
            self.assertEqual( 0, chunk.covariance_flag )
            self.assertEqual( 2, chunk.NER )
            self.assertEqual( 2, chunk.number_discrete_spectra )

            self.assertAlmostEqual( 1., chunk.FD[0] )
            self.assertAlmostEqual( 0., chunk.FD[1] )
            self.assertAlmostEqual( 1., chunk.discrete_normalisation_factor[0] )
            self.assertAlmostEqual( 0., chunk.discrete_normalisation_factor[1] )
            self.assertAlmostEqual( 0.5, chunk.FC[0] )
            self.assertAlmostEqual( 0.25, chunk.FC[1] )
            self.assertAlmostEqual( 0.5, chunk.continuous_normalisation_factor[0] )
            self.assertAlmostEqual( 0.25, chunk.continuous_normalisation_factor[1] )
            self.assertAlmostEqual( 2.107044e+2, chunk.ERAV[0] )
            self.assertAlmostEqual( 1.576284e+1, chunk.ERAV[1] )
            self.assertAlmostEqual( 2.107044e+2, chunk.average_decay_energy[0] )
            self.assertAlmostEqual( 1.576284e+1, chunk.average_decay_energy[1] )

            self.assertEqual( True, None != chunk.continuous_spectrum )

            discrete = chunk.discrete_spectra
            self.assertAlmostEqual( 3., discrete[0].RTYP )
            self.assertAlmostEqual( 3., discrete[0].decay_chain )
            self.assertEqual( 12, discrete[0].NT )
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
            self.assertAlmostEqual( 4., discrete[1].RTYP )
            self.assertAlmostEqual( 4., discrete[1].decay_chain )
            self.assertEqual( 12, discrete[1].NT )
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

            continuous = chunk.continuous_spectrum
            self.assertAlmostEqual( 4., continuous.RTYP )
            self.assertAlmostEqual( 4., continuous.decay_chain )
            self.assertEqual( 3, continuous.NP )
            self.assertEqual( 1, continuous.NR )
            self.assertEqual( 1, len( continuous.interpolants ) )
            self.assertEqual( 1, len( continuous.boundaries ) )
            self.assertEqual( 1, continuous.interpolants[0] )
            self.assertEqual( 3, continuous.boundaries[0] )
            self.assertEqual( 3, len( continuous.energies ) )
            self.assertEqual( 3, len( continuous.spectral_values ) )
            self.assertAlmostEqual( 0.0, continuous.energies[0] )
            self.assertAlmostEqual( 5e+5, continuous.energies[1] )
            self.assertAlmostEqual( 7.3e+6, continuous.energies[2] )
            self.assertAlmostEqual( 6.133200e-7, continuous.spectral_values[0] )
            self.assertAlmostEqual( 6.133300e-7, continuous.spectral_values[1] )
            self.assertAlmostEqual( 6.02040e-17, continuous.spectral_values[2] )

            self.assertEqual( 11, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_lcon_2, chunk.to_string( 3580, 8, 457 ) )

        # the data is given explicitly
        chunk = DecaySpectrum( type = 0.0, dnorm = [ 1., 0. ],
                               energy = [ 2.107044e+2, 1.576284e+1 ],
                               dspectra = [ DiscreteSpectrum( 3., [ 4.863000e+4, 5.000000e+1 ],
                                              [ 1.420112e-6, 2.85306e-10 ], 0.0,
                                              [ 0.0, 0.0 ], [ 7.010000e+5, 1.106180e-2 ], [ 0.0, 0.0 ],
                                              [ 3.315735e+5, 5.608008e+3 ] ),
                                            DiscreteSpectrum( 4., [ 4.935000e+4, 2.000000e+1 ],
                                              [ 1.335690e-3, 5.409179e-5 ], 0.0,
                                              [ 0.0, 0.0 ], [ 8.209999e-1, 0.000000e+0 ], [ 0.0, 0.0 ],
                                              [ 6.160000e-1, 8.999999e-3 ] ) ] )

        verify_chunk_lcon_0( self, chunk )

        # the data is read from a string
        chunk = DecaySpectrum.from_string( self.chunk_lcon_0, 3580, 8, 457 )

        verify_chunk_lcon_0( self, chunk )

        # the data is copied
        copy = DecaySpectrum( chunk )

        verify_chunk_lcon_0( self, copy )

        # the data is given explicitly
        chunk = DecaySpectrum( type = 0.0, cnorm = [ 0.5, 0.25 ],
                               energy = [ 2.107044e+2, 1.576284e+1 ],
                               cspectrum = ContinuousSpectrum( 4., [ 3 ], [ 1 ], [ 0.0, 5e+5, 7.3e+6 ],
                                                               [ 6.133200e-7, 6.133300e-7, 6.02040e-17 ] ) )

        verify_chunk_lcon_1( self, chunk )

        # the data is read from a string
        chunk = DecaySpectrum.from_string( self.chunk_lcon_1, 3580, 8, 457 )

        verify_chunk_lcon_1( self, chunk )

        # the data is copied
        copy = DecaySpectrum( chunk )

        verify_chunk_lcon_1( self, copy )

        # the data is given explicitly
        chunk = DecaySpectrum( type = 0.0, dnorm = [ 1., 0. ], cnorm = [ 0.5, 0.25 ],
                               energy = [ 2.107044e+2, 1.576284e+1 ],
                               dspectra = [ DiscreteSpectrum( 3., [ 4.863000e+4, 5.000000e+1 ],
                                              [ 1.420112e-6, 2.85306e-10 ], 0.0,
                                              [ 0.0, 0.0 ], [ 7.010000e+5, 1.106180e-2 ], [ 0.0, 0.0 ],
                                              [ 3.315735e+5, 5.608008e+3 ] ),
                                            DiscreteSpectrum( 4., [ 4.935000e+4, 2.000000e+1 ],
                                              [ 1.335690e-3, 5.409179e-5 ], 0.0,
                                              [ 0.0, 0.0 ], [ 8.209999e-1, 0.000000e+0 ], [ 0.0, 0.0 ],
                                              [ 6.160000e-1, 8.999999e-3 ] ) ],
                               cspectrum = ContinuousSpectrum( 4., [ 3 ], [ 1 ], [ 0.0, 5e+5, 7.3e+6 ],
                                                               [ 6.133200e-7, 6.133300e-7, 6.02040e-17 ] ) )

        verify_chunk_lcon_2( self, chunk )

        # the data is read from a string
        chunk = DecaySpectrum.from_string( self.chunk_lcon_2, 3580, 8, 457 )

        verify_chunk_lcon_2( self, chunk )

        # the data is copied
        copy = DecaySpectrum( chunk )

        verify_chunk_lcon_2( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # inconsistent data
        with self.assertRaises( Exception ) :

            chunk = DecaySpectrum( type = 0.0, dnorm = [ 1., 0. ],
                                   energy = [ 2.107044e+2, 1.576284e+1 ],
                                   dspectra = [],
                                   cspectrum = ContinuousSpectrum( 4., [ 3 ], [ 1 ], [ 0.0, 5e+5, 7.3e+6 ],
                                                                   [ 6.133200e-7, 6.133300e-7, 6.02040e-17 ] ) )

        with self.assertRaises( Exception ) :

            chunk = DecaySpectrum.from_string( self.invalid, 3580, 8, 457 )

if __name__ == '__main__' :

    unittest.main()
