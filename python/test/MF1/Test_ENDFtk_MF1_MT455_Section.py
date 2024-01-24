# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF1.MT455 import Section
from ENDFtk.MF1.MT455 import DecayConstants
from ENDFtk.MF1.MT455 import EnergyIndependentConstants
from ENDFtk.MF1.MT455 import EnergyDependentConstants
from ENDFtk.MF1 import PolynomialMultiplicity
from ENDFtk.MF1 import TabulatedMultiplicity
from ENDFtk.tree import Tape

class Test_ENDFtk_MF1_MT455_Section( unittest.TestCase ) :
    """Unit test for the Section class."""

    chunk_ldg0_lnu1 = ( ' 9.223500+4 2.330248+2          0          1          0          09228 1455     \n'
                        ' 0.000000+0 0.000000+0          0          0          6          09228 1455     \n'
                        ' 1.333600-2 3.273900-2 1.207800-1 3.027800-1 8.494900-1 2.853000+09228 1455     \n'
                        ' 0.000000+0 0.000000+0          0          0          2          09228 1455     \n'
                        ' 2.436700+0 5.000000-2                                            9228 1455     \n' )

    chunk_ldg0_lnu2 = ( ' 9.223500+4 2.330248+2          0          2          0          09228 1455     \n'
                        ' 0.000000+0 0.000000+0          0          0          6          09228 1455     \n'
                        ' 1.333600-2 3.273900-2 1.207800-1 3.027800-1 8.494900-1 2.853000+09228 1455     \n'
                        ' 0.000000+0 0.000000+0          0          0          1          49228 1455     \n'
                        '          4          2                                            9228 1455     \n'
                        ' 1.000000-5 2.436700+0 2.530000-2 2.436700+0 5.000000-2 2.436700+09228 1455     \n'
                        ' 2.000000+7 5.209845+0                                            9228 1455     \n' )

    chunk_ldg1_lnu1 = ( ' 9.223500+4 2.330248+2          1          1          0          09228 1455     \n'
                        ' 0.000000+0 0.000000+0          0          0          1          29228 1455     \n'
                        '          2          4                                            9228 1455     \n'
                        ' 0.000000+0 1.000000-5          0          0         12          09228 1455     \n'
                        ' 1.000000+0 1.100000+0 2.000000+0 2.100000+0 3.000000+0 3.100000+09228 1455     \n'
                        ' 4.000000+0 4.100000+0 5.000000+0 5.100000+0 6.000000+0 6.100000+09228 1455     \n'
                        ' 0.000000+0 2.000000+7          0          0         12          09228 1455     \n'
                        ' 6.000000+0 6.100000+0 5.000000+0 5.100000+0 4.000000+0 4.100000+09228 1455     \n'
                        ' 3.000000+0 3.100000+0 2.000000+0 2.100000+0 1.000000+0 1.100000+09228 1455     \n'
                        ' 0.000000+0 0.000000+0          0          0          2          09228 1455     \n'
                        ' 2.436700+0 5.000000-2                                            9228 1455     \n' )

    chunk_ldg1_lnu2 = ( ' 9.223500+4 2.330248+2          1          2          0          09228 1455     \n'
                        ' 0.000000+0 0.000000+0          0          0          1          29228 1455     \n'
                        '          2          4                                            9228 1455     \n'
                        ' 0.000000+0 1.000000-5          0          0         12          09228 1455     \n'
                        ' 1.000000+0 1.100000+0 2.000000+0 2.100000+0 3.000000+0 3.100000+09228 1455     \n'
                        ' 4.000000+0 4.100000+0 5.000000+0 5.100000+0 6.000000+0 6.100000+09228 1455     \n'
                        ' 0.000000+0 2.000000+7          0          0         12          09228 1455     \n'
                        ' 6.000000+0 6.100000+0 5.000000+0 5.100000+0 4.000000+0 4.100000+09228 1455     \n'
                        ' 3.000000+0 3.100000+0 2.000000+0 2.100000+0 1.000000+0 1.100000+09228 1455     \n'
                        ' 0.000000+0 0.000000+0          0          0          1          49228 1455     \n'
                        '          4          2                                            9228 1455     \n'
                        ' 1.000000-5 2.436700+0 2.530000-2 2.436700+0 5.000000-2 2.436700+09228 1455     \n'
                        ' 2.000000+7 5.209845+0                                            9228 1455     \n' )

    invalid = ( ' 9.223500+4 2.330248+2          0          3          0          09228 1455     \n'
                ' 0.000000+0 0.000000+0          0          0          2          09228 1455     \n'
                ' 2.436700+0 5.000000-2                                            9228 1455     \n' )

    valid_TPID = 'Just a tape identifier                                                          \n'
    valid_SEND = '                                                                  9228 1  0     \n'
    valid_FEND = '                                                                  9228 0  0     \n'
    valid_MEND = '                                                                     0 0  0     \n'
    valid_TEND = '                                                                    -1 0  0     \n'
    invalid_SEND = '                                                                  9228 1  1     \n'

    def test_section( self ) :

        def verify_chunk_ldg0_lnu1( self, chunk ) :

            # verify content
            self.assertEqual( 455, chunk.MT )
            self.assertEqual( 455, chunk.section_number )
            self.assertEqual( 92235, chunk.ZA )
            self.assertEqual( 92235, chunk.target_identifier )
            self.assertAlmostEqual( 233.0248, chunk.AWR )
            self.assertAlmostEqual( 233.0248, chunk.atomic_weight_ratio )
            self.assertEqual( 1, chunk.LNU )
            self.assertEqual( 1, chunk.representation )
            self.assertEqual( 0, chunk.LDG )
            self.assertEqual( 0, chunk.type )

            self.assertEqual( 0, chunk.delayed_groups.LDG )
            self.assertEqual( 0, chunk.delayed_groups.type )
            self.assertEqual( 6, chunk.delayed_groups.NNF )
            self.assertEqual( 6, chunk.delayed_groups.number_precursors )

            self.assertEqual( 6, len( chunk.delayed_groups.lambdas ) )
            self.assertEqual( 6, len( chunk.delayed_groups.decay_constants ) )
            self.assertAlmostEqual( 0.013336, chunk.delayed_groups.lambdas[0] )
            self.assertAlmostEqual( 0.032739, chunk.delayed_groups.lambdas[1] )
            self.assertAlmostEqual( 0.12078, chunk.delayed_groups.lambdas[2] )
            self.assertAlmostEqual( 0.30278, chunk.delayed_groups.lambdas[3] )
            self.assertAlmostEqual( 0.84949, chunk.delayed_groups.lambdas[4] )
            self.assertAlmostEqual( 2.853000, chunk.delayed_groups.lambdas[5] )
            self.assertAlmostEqual( 0.013336, chunk.delayed_groups.decay_constants[0] )
            self.assertAlmostEqual( 0.032739, chunk.delayed_groups.decay_constants[1] )
            self.assertAlmostEqual( 0.12078, chunk.delayed_groups.decay_constants[2] )
            self.assertAlmostEqual( 0.30278, chunk.delayed_groups.decay_constants[3] )
            self.assertAlmostEqual( 0.84949, chunk.delayed_groups.decay_constants[4] )
            self.assertAlmostEqual( 2.853000, chunk.delayed_groups.decay_constants[5] )

            self.assertEqual( 1, chunk.nubar.LNU )
            self.assertEqual( 1, chunk.nubar.representation )

            self.assertEqual( 2, chunk.nubar.NCO )
            self.assertEqual( 2, chunk.nubar.number_coefficients )
            self.assertEqual( 2, len( chunk.nubar.C ) )
            self.assertEqual( 2, len( chunk.nubar.coefficients ) )
            self.assertAlmostEqual( 2.4367, chunk.nubar.C[0] )
            self.assertAlmostEqual( 5e-2, chunk.nubar.C[1] )
            self.assertAlmostEqual( 2.4367, chunk.nubar.coefficients[0] )
            self.assertAlmostEqual( 5e-2, chunk.nubar.coefficients[1] )

            self.assertEqual( 5, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_ldg0_lnu1 + self.valid_SEND,
                              chunk.to_string( 9228, 1 ) )

        def verify_chunk_ldg0_lnu2( self, chunk ) :

            # verify content
            self.assertEqual( 455, chunk.MT )
            self.assertEqual( 455, chunk.section_number )
            self.assertAlmostEqual( 92235, chunk.ZA )
            self.assertAlmostEqual( 92235, chunk.target_identifier )
            self.assertAlmostEqual( 233.0248, chunk.AWR )
            self.assertAlmostEqual( 233.0248, chunk.atomic_weight_ratio )
            self.assertEqual( 2, chunk.LNU )
            self.assertEqual( 2, chunk.representation )
            self.assertEqual( 0, chunk.LDG )
            self.assertEqual( 0, chunk.type )

            self.assertEqual( 0, chunk.delayed_groups.LDG )
            self.assertEqual( 0, chunk.delayed_groups.type )
            self.assertEqual( 6, chunk.delayed_groups.NNF )
            self.assertEqual( 6, chunk.delayed_groups.number_precursors )

            self.assertEqual( 6, len( chunk.delayed_groups.lambdas ) )
            self.assertEqual( 6, len( chunk.delayed_groups.decay_constants ) )
            self.assertAlmostEqual( 0.013336, chunk.delayed_groups.lambdas[0] )
            self.assertAlmostEqual( 0.032739, chunk.delayed_groups.lambdas[1] )
            self.assertAlmostEqual( 0.12078, chunk.delayed_groups.lambdas[2] )
            self.assertAlmostEqual( 0.30278, chunk.delayed_groups.lambdas[3] )
            self.assertAlmostEqual( 0.84949, chunk.delayed_groups.lambdas[4] )
            self.assertAlmostEqual( 2.853000, chunk.delayed_groups.lambdas[5] )
            self.assertAlmostEqual( 0.013336, chunk.delayed_groups.decay_constants[0] )
            self.assertAlmostEqual( 0.032739, chunk.delayed_groups.decay_constants[1] )
            self.assertAlmostEqual( 0.12078, chunk.delayed_groups.decay_constants[2] )
            self.assertAlmostEqual( 0.30278, chunk.delayed_groups.decay_constants[3] )
            self.assertAlmostEqual( 0.84949, chunk.delayed_groups.decay_constants[4] )
            self.assertAlmostEqual( 2.853000, chunk.delayed_groups.decay_constants[5] )

            self.assertEqual( 2, chunk.nubar.LNU )
            self.assertEqual( 2, chunk.nubar.representation )

            self.assertEqual( 4, chunk.nubar.NP )
            self.assertEqual( 1, chunk.nubar.NR )
            self.assertEqual( 1, len( chunk.nubar.interpolants ) )
            self.assertEqual( 1, len( chunk.nubar.boundaries ) )
            self.assertEqual( 2, chunk.nubar.interpolants[0] );
            self.assertEqual( 4, chunk.nubar.boundaries[0] );

            self.assertEqual( 4, len( chunk.nubar.E ) )
            self.assertEqual( 4, len( chunk.nubar.energies ) )
            self.assertEqual( 4, len( chunk.nubar.NU ) )
            self.assertEqual( 4, len( chunk.nubar.multiplicities ) )
            self.assertAlmostEqual( 1e-5, chunk.nubar.E[0] )
            self.assertAlmostEqual( 0.0253, chunk.nubar.E[1] )
            self.assertAlmostEqual( 0.05, chunk.nubar.E[2] )
            self.assertAlmostEqual( 2e+7, chunk.nubar.E[3] )
            self.assertAlmostEqual( 1e-5, chunk.nubar.energies[0] )
            self.assertAlmostEqual( 0.0253, chunk.nubar.energies[1] )
            self.assertAlmostEqual( 0.05, chunk.nubar.energies[2] )
            self.assertAlmostEqual( 2e+7, chunk.nubar.energies[3] )
            self.assertAlmostEqual( 2.4367, chunk.nubar.NU[0] )
            self.assertAlmostEqual( 2.4367, chunk.nubar.NU[1] )
            self.assertAlmostEqual( 2.4367, chunk.nubar.NU[2] )
            self.assertAlmostEqual( 5.209845, chunk.nubar.NU[3] )
            self.assertAlmostEqual( 2.4367, chunk.nubar.multiplicities[0] )
            self.assertAlmostEqual( 2.4367, chunk.nubar.multiplicities[1] )
            self.assertAlmostEqual( 2.4367, chunk.nubar.multiplicities[2] )
            self.assertAlmostEqual( 5.209845, chunk.nubar.multiplicities[3] )

            self.assertEqual( 7, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_ldg0_lnu2 + self.valid_SEND,
                              chunk.to_string( 9228, 1 ) )

        def verify_chunk_ldg1_lnu1( self, chunk ) :

            # verify content
            self.assertEqual( 455, chunk.MT )
            self.assertEqual( 455, chunk.section_number )
            self.assertAlmostEqual( 92235, chunk.ZA )
            self.assertAlmostEqual( 92235, chunk.target_identifier )
            self.assertAlmostEqual( 233.0248, chunk.AWR )
            self.assertAlmostEqual( 233.0248, chunk.atomic_weight_ratio )
            self.assertEqual( 1, chunk.LNU )
            self.assertEqual( 1, chunk.representation )
            self.assertEqual( 1, chunk.LDG )
            self.assertEqual( 1, chunk.type )

            self.assertEqual( 1, chunk.delayed_groups.LDG )
            self.assertEqual( 1, chunk.delayed_groups.type )
            self.assertEqual( 6, chunk.delayed_groups.NNF )
            self.assertEqual( 6, chunk.delayed_groups.number_precursors )

            self.assertEqual( 1, chunk.delayed_groups.NR )
            self.assertEqual( 2, chunk.delayed_groups.NE )
            self.assertEqual( 1, len( chunk.delayed_groups.interpolants ) )
            self.assertEqual( 1, len( chunk.delayed_groups.boundaries ) )
            self.assertEqual( 4, chunk.delayed_groups.interpolants[0] );
            self.assertEqual( 2, chunk.delayed_groups.boundaries[0] );

            self.assertEqual( 2, len( chunk.delayed_groups.constants ) )
            self.assertAlmostEqual( 1e-5, chunk.delayed_groups.constants[0].incident_energy )
            self.assertAlmostEqual( 2e+7, chunk.delayed_groups.constants[1].incident_energy )

            self.assertEqual( 6, len( chunk.delayed_groups.constants[0].lambdas ) )
            self.assertEqual( 6, len( chunk.delayed_groups.constants[0].decay_constants ) )
            self.assertAlmostEqual( 1., chunk.delayed_groups.constants[0].lambdas[0] )
            self.assertAlmostEqual( 2., chunk.delayed_groups.constants[0].lambdas[1] )
            self.assertAlmostEqual( 3., chunk.delayed_groups.constants[0].lambdas[2] )
            self.assertAlmostEqual( 4., chunk.delayed_groups.constants[0].lambdas[3] )
            self.assertAlmostEqual( 5., chunk.delayed_groups.constants[0].lambdas[4] )
            self.assertAlmostEqual( 6., chunk.delayed_groups.constants[0].lambdas[5] )
            self.assertAlmostEqual( 1., chunk.delayed_groups.constants[0].decay_constants[0] )
            self.assertAlmostEqual( 2., chunk.delayed_groups.constants[0].decay_constants[1] )
            self.assertAlmostEqual( 3., chunk.delayed_groups.constants[0].decay_constants[2] )
            self.assertAlmostEqual( 4., chunk.delayed_groups.constants[0].decay_constants[3] )
            self.assertAlmostEqual( 5., chunk.delayed_groups.constants[0].decay_constants[4] )
            self.assertAlmostEqual( 6., chunk.delayed_groups.constants[0].decay_constants[5] )

            self.assertEqual( 6, len( chunk.delayed_groups.constants[1].lambdas ) )
            self.assertEqual( 6, len( chunk.delayed_groups.constants[1].decay_constants ) )
            self.assertAlmostEqual( 6., chunk.delayed_groups.constants[1].lambdas[0] )
            self.assertAlmostEqual( 5., chunk.delayed_groups.constants[1].lambdas[1] )
            self.assertAlmostEqual( 4., chunk.delayed_groups.constants[1].lambdas[2] )
            self.assertAlmostEqual( 3., chunk.delayed_groups.constants[1].lambdas[3] )
            self.assertAlmostEqual( 2., chunk.delayed_groups.constants[1].lambdas[4] )
            self.assertAlmostEqual( 1., chunk.delayed_groups.constants[1].lambdas[5] )
            self.assertAlmostEqual( 6., chunk.delayed_groups.constants[1].decay_constants[0] )
            self.assertAlmostEqual( 5., chunk.delayed_groups.constants[1].decay_constants[1] )
            self.assertAlmostEqual( 4., chunk.delayed_groups.constants[1].decay_constants[2] )
            self.assertAlmostEqual( 3., chunk.delayed_groups.constants[1].decay_constants[3] )
            self.assertAlmostEqual( 2., chunk.delayed_groups.constants[1].decay_constants[4] )
            self.assertAlmostEqual( 1., chunk.delayed_groups.constants[1].decay_constants[5] )

            self.assertEqual( 6, len( chunk.delayed_groups.constants[0].alphas ) )
            self.assertEqual( 6, len( chunk.delayed_groups.constants[0].abundances ) )
            self.assertAlmostEqual( 1.1, chunk.delayed_groups.constants[0].alphas[0] )
            self.assertAlmostEqual( 2.1, chunk.delayed_groups.constants[0].alphas[1] )
            self.assertAlmostEqual( 3.1, chunk.delayed_groups.constants[0].alphas[2] )
            self.assertAlmostEqual( 4.1, chunk.delayed_groups.constants[0].alphas[3] )
            self.assertAlmostEqual( 5.1, chunk.delayed_groups.constants[0].alphas[4] )
            self.assertAlmostEqual( 6.1, chunk.delayed_groups.constants[0].alphas[5] )
            self.assertAlmostEqual( 1.1, chunk.delayed_groups.constants[0].abundances[0] )
            self.assertAlmostEqual( 2.1, chunk.delayed_groups.constants[0].abundances[1] )
            self.assertAlmostEqual( 3.1, chunk.delayed_groups.constants[0].abundances[2] )
            self.assertAlmostEqual( 4.1, chunk.delayed_groups.constants[0].abundances[3] )
            self.assertAlmostEqual( 5.1, chunk.delayed_groups.constants[0].abundances[4] )
            self.assertAlmostEqual( 6.1, chunk.delayed_groups.constants[0].abundances[5] )

            self.assertEqual( 6, len( chunk.delayed_groups.constants[1].alphas ) )
            self.assertEqual( 6, len( chunk.delayed_groups.constants[1].abundances ) )
            self.assertAlmostEqual( 6.1, chunk.delayed_groups.constants[1].alphas[0] )
            self.assertAlmostEqual( 5.1, chunk.delayed_groups.constants[1].alphas[1] )
            self.assertAlmostEqual( 4.1, chunk.delayed_groups.constants[1].alphas[2] )
            self.assertAlmostEqual( 3.1, chunk.delayed_groups.constants[1].alphas[3] )
            self.assertAlmostEqual( 2.1, chunk.delayed_groups.constants[1].alphas[4] )
            self.assertAlmostEqual( 1.1, chunk.delayed_groups.constants[1].alphas[5] )
            self.assertAlmostEqual( 6.1, chunk.delayed_groups.constants[1].abundances[0] )
            self.assertAlmostEqual( 5.1, chunk.delayed_groups.constants[1].abundances[1] )
            self.assertAlmostEqual( 4.1, chunk.delayed_groups.constants[1].abundances[2] )
            self.assertAlmostEqual( 3.1, chunk.delayed_groups.constants[1].abundances[3] )
            self.assertAlmostEqual( 2.1, chunk.delayed_groups.constants[1].abundances[4] )
            self.assertAlmostEqual( 1.1, chunk.delayed_groups.constants[1].abundances[5] )

            self.assertEqual( 1, chunk.nubar.LNU )
            self.assertEqual( 1, chunk.nubar.representation )

            self.assertEqual( 2, chunk.nubar.NCO )
            self.assertEqual( 2, chunk.nubar.number_coefficients )
            self.assertEqual( 2, len( chunk.nubar.C ) )
            self.assertEqual( 2, len( chunk.nubar.coefficients ) )
            self.assertAlmostEqual( 2.4367, chunk.nubar.C[0] )
            self.assertAlmostEqual( 5e-2, chunk.nubar.C[1] )
            self.assertAlmostEqual( 2.4367, chunk.nubar.coefficients[0] )
            self.assertAlmostEqual( 5e-2, chunk.nubar.coefficients[1] )

            self.assertEqual( 11, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_ldg1_lnu1 + self.valid_SEND,
                              chunk.to_string( 9228, 1 ) )

        def verify_chunk_ldg1_lnu2( self, chunk ) :

            # verify content
            self.assertEqual( 455, chunk.MT )
            self.assertEqual( 455, chunk.section_number )
            self.assertAlmostEqual( 92235, chunk.ZA )
            self.assertAlmostEqual( 92235, chunk.target_identifier )
            self.assertAlmostEqual( 233.0248, chunk.AWR )
            self.assertAlmostEqual( 233.0248, chunk.atomic_weight_ratio )
            self.assertEqual( 2, chunk.LNU )
            self.assertEqual( 2, chunk.representation )
            self.assertEqual( 1, chunk.LDG )
            self.assertEqual( 1, chunk.type )

            self.assertEqual( 1, chunk.delayed_groups.LDG )
            self.assertEqual( 1, chunk.delayed_groups.type )
            self.assertEqual( 6, chunk.delayed_groups.NNF )
            self.assertEqual( 6, chunk.delayed_groups.number_precursors )

            self.assertEqual( 1, chunk.delayed_groups.NR )
            self.assertEqual( 2, chunk.delayed_groups.NE )
            self.assertEqual( 1, len( chunk.delayed_groups.interpolants ) )
            self.assertEqual( 1, len( chunk.delayed_groups.boundaries ) )
            self.assertEqual( 4, chunk.delayed_groups.interpolants[0] );
            self.assertEqual( 2, chunk.delayed_groups.boundaries[0] );

            self.assertEqual( 2, len( chunk.delayed_groups.constants ) )
            self.assertAlmostEqual( 1e-5, chunk.delayed_groups.constants[0].incident_energy )
            self.assertAlmostEqual( 2e+7, chunk.delayed_groups.constants[1].incident_energy )

            self.assertEqual( 6, len( chunk.delayed_groups.constants[0].lambdas ) )
            self.assertEqual( 6, len( chunk.delayed_groups.constants[0].decay_constants ) )
            self.assertAlmostEqual( 1., chunk.delayed_groups.constants[0].lambdas[0] )
            self.assertAlmostEqual( 2., chunk.delayed_groups.constants[0].lambdas[1] )
            self.assertAlmostEqual( 3., chunk.delayed_groups.constants[0].lambdas[2] )
            self.assertAlmostEqual( 4., chunk.delayed_groups.constants[0].lambdas[3] )
            self.assertAlmostEqual( 5., chunk.delayed_groups.constants[0].lambdas[4] )
            self.assertAlmostEqual( 6., chunk.delayed_groups.constants[0].lambdas[5] )
            self.assertAlmostEqual( 1., chunk.delayed_groups.constants[0].decay_constants[0] )
            self.assertAlmostEqual( 2., chunk.delayed_groups.constants[0].decay_constants[1] )
            self.assertAlmostEqual( 3., chunk.delayed_groups.constants[0].decay_constants[2] )
            self.assertAlmostEqual( 4., chunk.delayed_groups.constants[0].decay_constants[3] )
            self.assertAlmostEqual( 5., chunk.delayed_groups.constants[0].decay_constants[4] )
            self.assertAlmostEqual( 6., chunk.delayed_groups.constants[0].decay_constants[5] )

            self.assertEqual( 6, len( chunk.delayed_groups.constants[1].lambdas ) )
            self.assertEqual( 6, len( chunk.delayed_groups.constants[1].decay_constants ) )
            self.assertAlmostEqual( 6., chunk.delayed_groups.constants[1].lambdas[0] )
            self.assertAlmostEqual( 5., chunk.delayed_groups.constants[1].lambdas[1] )
            self.assertAlmostEqual( 4., chunk.delayed_groups.constants[1].lambdas[2] )
            self.assertAlmostEqual( 3., chunk.delayed_groups.constants[1].lambdas[3] )
            self.assertAlmostEqual( 2., chunk.delayed_groups.constants[1].lambdas[4] )
            self.assertAlmostEqual( 1., chunk.delayed_groups.constants[1].lambdas[5] )
            self.assertAlmostEqual( 6., chunk.delayed_groups.constants[1].decay_constants[0] )
            self.assertAlmostEqual( 5., chunk.delayed_groups.constants[1].decay_constants[1] )
            self.assertAlmostEqual( 4., chunk.delayed_groups.constants[1].decay_constants[2] )
            self.assertAlmostEqual( 3., chunk.delayed_groups.constants[1].decay_constants[3] )
            self.assertAlmostEqual( 2., chunk.delayed_groups.constants[1].decay_constants[4] )
            self.assertAlmostEqual( 1., chunk.delayed_groups.constants[1].decay_constants[5] )

            self.assertEqual( 6, len( chunk.delayed_groups.constants[0].alphas ) )
            self.assertEqual( 6, len( chunk.delayed_groups.constants[0].abundances ) )
            self.assertAlmostEqual( 1.1, chunk.delayed_groups.constants[0].alphas[0] )
            self.assertAlmostEqual( 2.1, chunk.delayed_groups.constants[0].alphas[1] )
            self.assertAlmostEqual( 3.1, chunk.delayed_groups.constants[0].alphas[2] )
            self.assertAlmostEqual( 4.1, chunk.delayed_groups.constants[0].alphas[3] )
            self.assertAlmostEqual( 5.1, chunk.delayed_groups.constants[0].alphas[4] )
            self.assertAlmostEqual( 6.1, chunk.delayed_groups.constants[0].alphas[5] )
            self.assertAlmostEqual( 1.1, chunk.delayed_groups.constants[0].abundances[0] )
            self.assertAlmostEqual( 2.1, chunk.delayed_groups.constants[0].abundances[1] )
            self.assertAlmostEqual( 3.1, chunk.delayed_groups.constants[0].abundances[2] )
            self.assertAlmostEqual( 4.1, chunk.delayed_groups.constants[0].abundances[3] )
            self.assertAlmostEqual( 5.1, chunk.delayed_groups.constants[0].abundances[4] )
            self.assertAlmostEqual( 6.1, chunk.delayed_groups.constants[0].abundances[5] )

            self.assertEqual( 6, len( chunk.delayed_groups.constants[1].alphas ) )
            self.assertEqual( 6, len( chunk.delayed_groups.constants[1].abundances ) )
            self.assertAlmostEqual( 6.1, chunk.delayed_groups.constants[1].alphas[0] )
            self.assertAlmostEqual( 5.1, chunk.delayed_groups.constants[1].alphas[1] )
            self.assertAlmostEqual( 4.1, chunk.delayed_groups.constants[1].alphas[2] )
            self.assertAlmostEqual( 3.1, chunk.delayed_groups.constants[1].alphas[3] )
            self.assertAlmostEqual( 2.1, chunk.delayed_groups.constants[1].alphas[4] )
            self.assertAlmostEqual( 1.1, chunk.delayed_groups.constants[1].alphas[5] )
            self.assertAlmostEqual( 6.1, chunk.delayed_groups.constants[1].abundances[0] )
            self.assertAlmostEqual( 5.1, chunk.delayed_groups.constants[1].abundances[1] )
            self.assertAlmostEqual( 4.1, chunk.delayed_groups.constants[1].abundances[2] )
            self.assertAlmostEqual( 3.1, chunk.delayed_groups.constants[1].abundances[3] )
            self.assertAlmostEqual( 2.1, chunk.delayed_groups.constants[1].abundances[4] )
            self.assertAlmostEqual( 1.1, chunk.delayed_groups.constants[1].abundances[5] )

            self.assertEqual( 2, chunk.nubar.LNU )
            self.assertEqual( 2, chunk.nubar.representation )

            self.assertEqual( 4, chunk.nubar.NP )
            self.assertEqual( 1, chunk.nubar.NR )
            self.assertEqual( 1, len( chunk.nubar.interpolants ) )
            self.assertEqual( 1, len( chunk.nubar.boundaries ) )
            self.assertEqual( 2, chunk.nubar.interpolants[0] );
            self.assertEqual( 4, chunk.nubar.boundaries[0] );

            self.assertEqual( 4, len( chunk.nubar.E ) )
            self.assertEqual( 4, len( chunk.nubar.energies ) )
            self.assertEqual( 4, len( chunk.nubar.NU ) )
            self.assertEqual( 4, len( chunk.nubar.multiplicities ) )
            self.assertAlmostEqual( 1e-5, chunk.nubar.E[0] )
            self.assertAlmostEqual( 0.0253, chunk.nubar.E[1] )
            self.assertAlmostEqual( 0.05, chunk.nubar.E[2] )
            self.assertAlmostEqual( 2e+7, chunk.nubar.E[3] )
            self.assertAlmostEqual( 1e-5, chunk.nubar.energies[0] )
            self.assertAlmostEqual( 0.0253, chunk.nubar.energies[1] )
            self.assertAlmostEqual( 0.05, chunk.nubar.energies[2] )
            self.assertAlmostEqual( 2e+7, chunk.nubar.energies[3] )
            self.assertAlmostEqual( 2.4367, chunk.nubar.NU[0] )
            self.assertAlmostEqual( 2.4367, chunk.nubar.NU[1] )
            self.assertAlmostEqual( 2.4367, chunk.nubar.NU[2] )
            self.assertAlmostEqual( 5.209845, chunk.nubar.NU[3] )
            self.assertAlmostEqual( 2.4367, chunk.nubar.multiplicities[0] )
            self.assertAlmostEqual( 2.4367, chunk.nubar.multiplicities[1] )
            self.assertAlmostEqual( 2.4367, chunk.nubar.multiplicities[2] )
            self.assertAlmostEqual( 5.209845, chunk.nubar.multiplicities[3] )

            self.assertEqual( 13, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_ldg1_lnu2 + self.valid_SEND,
                              chunk.to_string( 9228, 1 ) )

        # the data is given explicitly
        chunk = Section( zaid = 92235, awr = 233.0248,
                         constants = EnergyIndependentConstants(
                                         [ 1.3336e-2, 3.2739e-2, 1.2078e-1,
                                           3.0278e-1, 8.4949e-1, 2.853 ] ),
                         multiplicity = PolynomialMultiplicity( [ 2.4367, 0.05 ] ) )

        verify_chunk_ldg0_lnu1( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk_ldg0_lnu1 + self.valid_SEND )

        verify_chunk_ldg0_lnu1( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk_ldg0_lnu1 +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.material( 9228 ).file( 1 ).section( 455 ).parse()

        verify_chunk_ldg0_lnu1( self, chunk )

        # the data is copied
        copy = Section( chunk )

        verify_chunk_ldg0_lnu1( self, copy )

        # the data is given explicitly
        chunk = Section( zaid = 92235, awr = 233.0248,
                         constants = EnergyIndependentConstants(
                                         [ 1.3336e-2, 3.2739e-2, 1.2078e-1,
                                           3.0278e-1, 8.4949e-1, 2.853 ] ),
                         multiplicity =
                             TabulatedMultiplicity( [ 4 ], [ 2 ],
                                                    [ 1.00e-5, 2.53e-2, 5.00e-2, 2.00e+7 ],
                                                    [ 2.436700e+0, 2.436700e+0,
                                                       2.436700e+0, 5.209845e+0 ] ) )

        verify_chunk_ldg0_lnu2( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk_ldg0_lnu2 + self.valid_SEND )

        verify_chunk_ldg0_lnu2( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk_ldg0_lnu2 +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.material( 9228 ).file( 1 ).section( 455 ).parse()

        verify_chunk_ldg0_lnu2( self, chunk )

        # the data is copied
        copy = Section( chunk )

        verify_chunk_ldg0_lnu2( self, copy )

        # the data is given explicitly
        chunk = Section( zaid = 92235, awr = 233.0248,
                         constants = EnergyDependentConstants(
                                       [ 2 ], [ 4 ],
                                       [ DecayConstants( 1e-5, [ 1., 2., 3., 4., 5., 6. ],
                                                         [ 1.1, 2.1, 3.1, 4.1, 5.1, 6.1 ] ),
                                         DecayConstants( 2e+7, [ 6., 5., 4., 3., 2., 1. ],
                                                         [ 6.1, 5.1, 4.1, 3.1, 2.1, 1.1 ] ) ] ),
                         multiplicity = PolynomialMultiplicity( [ 2.4367, 0.05 ] ) )

        verify_chunk_ldg1_lnu1( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk_ldg1_lnu1 + self.valid_SEND )

        verify_chunk_ldg1_lnu1( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk_ldg1_lnu1 +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.material( 9228 ).file( 1 ).section( 455 ).parse()

        verify_chunk_ldg1_lnu1( self, chunk )

        # the data is copied
        copy = Section( chunk )

        verify_chunk_ldg1_lnu1( self, copy )

        # the data is given explicitly
        chunk = Section( zaid = 92235, awr = 233.0248,
                         constants = EnergyDependentConstants(
                                       [ 2 ], [ 4 ],
                                       [ DecayConstants( 1e-5, [ 1., 2., 3., 4., 5., 6. ],
                                                         [ 1.1, 2.1, 3.1, 4.1, 5.1, 6.1 ] ),
                                         DecayConstants( 2e+7, [ 6., 5., 4., 3., 2., 1. ],
                                                         [ 6.1, 5.1, 4.1, 3.1, 2.1, 1.1 ] ) ] ),
                         multiplicity =
                             TabulatedMultiplicity( [ 4 ], [ 2 ],
                                                    [ 1.00e-5, 2.53e-2, 5.00e-2, 2.00e+7 ],
                                                    [ 2.436700e+0, 2.436700e+0,
                                                       2.436700e+0, 5.209845e+0 ] ) )

        verify_chunk_ldg1_lnu2( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk_ldg1_lnu2 + self.valid_SEND )

        verify_chunk_ldg1_lnu2( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk_ldg1_lnu2 +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.material( 9228 ).file( 1 ).section( 455 ).parse()

        verify_chunk_ldg1_lnu2( self, chunk )

        # the data is copied
        copy = Section( chunk )

        verify_chunk_ldg1_lnu2( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # illegal SEND
        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.chunk + self.invalid_SEND )

if __name__ == '__main__' :

    unittest.main()
