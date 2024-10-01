# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF4 import LegendreCoefficients
from ENDFtk.MF4 import TabulatedDistribution
from ENDFtk.MF4 import Isotropic
from ENDFtk.MF4 import LegendreDistributions
from ENDFtk.MF4 import TabulatedDistributions
from ENDFtk.MF4 import MixedDistributions
from ENDFtk.MF4 import Section
from ENDFtk.tree import Tape

class Test_ENDFtk_MF4_Section( unittest.TestCase ) :
    """Unit test for the Section class."""

    chunk_LTT0 = ( ' 9.223500+4 2.330250+2          0          0          0          09228 4 18     \n'
                   ' 0.000000+0 2.330250+2          1          1          0          09228 4 18     \n' )

    chunk_LTT1 = ( ' 9.223500+4 2.330250+2          0          1          0          09228 4  2     \n'
                   ' 0.000000+0 2.330250+2          0          1          0          09228 4  2     \n'
                   ' 0.000000+0 0.000000+0          0          0          1          29228 4  2     \n'
                   '          2          1                                            9228 4  2     \n'
                   ' 0.000000+0 1.000000-5          0          0          3          09228 4  2     \n'
                   ' 7.392510-5 8.477139-9 1.17106-13                                 9228 4  2     \n'
                   ' 0.000000+0 2.000000+7          0          0          2          09228 4  2     \n'
                   ' 2.874390-2 3.19645-11                                            9228 4  2     \n' )

    chunk_LTT2 = ( ' 9.223500+4 2.330250+2          0          2          0          09228 4  2     \n'
                   ' 0.000000+0 2.330250+2          0          1          0          09228 4  2     \n'
                   ' 0.000000+0 0.000000+0          0          0          1          29228 4  2     \n'
                   '          2          1                                            9228 4  2     \n'
                   ' 0.000000+0 1.000000-5          0          0          1          29228 4  2     \n'
                   '          2          2                                            9228 4  2     \n'
                   '-1.000000+0 5.000000-1 1.000000+0 5.000000-1                      9228 4  2     \n'
                   ' 0.000000+0 2.000000+7          0          0          1          39228 4  2     \n'
                   '          3          2                                            9228 4  2     \n'
                   '-1.000000+0 0.000000+0 0.000000+0 1.000000+0 1.000000+0 0.000000+09228 4  2     \n' )

    chunk_LTT3 = ( ' 9.223500+4 2.330250+2          0          3          0          09228 4  2     \n'
                   ' 0.000000+0 2.330250+2          0          1          0          09228 4  2     \n'
                   ' 0.000000+0 0.000000+0          0          0          1          29228 4  2     \n'
                   '          2          1                                            9228 4  2     \n'
                   ' 0.000000+0 1.000000-5          0          0          3          09228 4  2     \n'
                   ' 7.392510-5 8.477139-9 1.17106-13                                 9228 4  2     \n'
                   ' 0.000000+0 1.000000+6          0          0          2          09228 4  2     \n'
                   ' 2.874390-2 3.19645-11                                            9228 4  2     \n'
                   ' 0.000000+0 0.000000+0          0          0          1          29228 4  2     \n'
                   '          2          5                                            9228 4  2     \n'
                   ' 0.000000+0 1.000000+6          0          0          1          29228 4  2     \n'
                   '          2          2                                            9228 4  2     \n'
                   '-1.000000+0 5.000000-1 1.000000+0 5.000000-1                      9228 4  2     \n'
                   ' 0.000000+0 2.000000+7          0          0          1          39228 4  2     \n'
                   '          3          2                                            9228 4  2     \n'
                   '-1.000000+0 0.000000+0 0.000000+0 1.000000+0 1.000000+0 0.000000+09228 4  2     \n' )

    invalid = ( ' 9.223500+4 2.330250+2          0          4          0          09228 4 18     \n'
                ' 0.000000+0 2.330250+2          1          1          0          09228 4 18     \n' )

    valid_TPID = 'Just a tape identifier                                                          \n'
    valid_SEND = '                                                                  9228 4  0     \n'
    valid_FEND = '                                                                  9228 0  0     \n'
    valid_MEND = '                                                                     0 0  0     \n'
    valid_TEND = '                                                                    -1 0  0     \n'
    invalid_SEND = '                                                                   125 3  1     \n'

    def test_section( self ) :

        def verify_chunk_LTT0( self, chunk ) :

            # verify content
            self.assertEqual( 18, chunk.MT )
            self.assertEqual( 18, chunk.section_number )

            self.assertEqual( 92235, chunk.ZA )
            self.assertEqual( 92235, chunk.target_identifier )
            self.assertAlmostEqual( 2.330250e+2, chunk.AWR )
            self.assertAlmostEqual( 2.330250e+2, chunk.atomic_weight_ratio )

            self.assertEqual( 1, chunk.LCT )
            self.assertEqual( 1, chunk.reference_frame )
            self.assertEqual( 0, chunk.LTT )
            self.assertEqual( 0, chunk.LAW )
            self.assertEqual( True, chunk.LI )
            self.assertEqual( True, chunk.isotropic_distributions )

            self.assertEqual( 0, chunk.NE )
            self.assertEqual( 0, chunk.number_incident_energies )
            self.assertEqual( 0, chunk.NR )
            self.assertEqual( 0, chunk.number_interpolation_regions )
            self.assertEqual( 0, len( chunk.NBT ) )
            self.assertEqual( 0, len( chunk.INT ) )
            self.assertEqual( 0, len( chunk.boundaries ) )
            self.assertEqual( 0, len( chunk.interpolants ) )
            self.assertEqual( 0, len( chunk.incident_energies ) )
            self.assertEqual( 0, len( chunk.angular_distributions ) )

            distributions = chunk.distributions
            self.assertEqual( 0, distributions.LTT )
            self.assertEqual( 0, distributions.LAW )

            self.assertEqual( 2, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_LTT0 + self.valid_SEND,
                              chunk.to_string( 9228, 4 ) )

        def verify_chunk_LTT1( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.MT )
            self.assertEqual( 2, chunk.section_number )

            self.assertEqual( 92235, chunk.ZA )
            self.assertEqual( 92235, chunk.target_identifier )
            self.assertAlmostEqual( 2.330250e+2, chunk.AWR )
            self.assertAlmostEqual( 2.330250e+2, chunk.atomic_weight_ratio )

            self.assertEqual( 1, chunk.LCT )
            self.assertEqual( 1, chunk.reference_frame )
            self.assertEqual( 1, chunk.LTT )
            self.assertEqual( 1, chunk.LAW )
            self.assertEqual( False, chunk.LI )
            self.assertEqual( False, chunk.isotropic_distributions )

            self.assertEqual( 2, chunk.NE )
            self.assertEqual( 2, chunk.number_incident_energies )
            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, chunk.number_interpolation_regions )
            self.assertEqual( 1, len( chunk.NBT ) )
            self.assertEqual( 1, len( chunk.INT ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 2, len( chunk.incident_energies ) )
            self.assertEqual( 2, len( chunk.angular_distributions ) )

            self.assertEqual( 1, chunk.interpolants[0] )
            self.assertEqual( 2, chunk.boundaries[0] )
            self.assertAlmostEqual( 1e-5, chunk.incident_energies[0] )
            self.assertAlmostEqual( 2e+7, chunk.incident_energies[1] )

            # direct access
            angulars = chunk.angular_distributions
            self.assertEqual( True, isinstance( angulars[0], LegendreCoefficients ) )
            self.assertEqual( True, isinstance( angulars[1], LegendreCoefficients ) )

            self.assertAlmostEqual( 1e-5, angulars[0].E )
            self.assertAlmostEqual( 1e-5, angulars[0].incident_energy )
            self.assertEqual( 3, angulars[0].NL )
            self.assertEqual( 3, angulars[0].legendre_order )
            self.assertEqual( 3, len( angulars[0].coefficients ) )
            self.assertAlmostEqual( 7.392510e-5 , angulars[0].coefficients[0] )
            self.assertAlmostEqual( 8.477139e-9, angulars[0].coefficients[1] )
            self.assertAlmostEqual( 1.17106e-13, angulars[0].coefficients[2] )

            self.assertAlmostEqual( 2e+7, angulars[1].E )
            self.assertAlmostEqual( 2e+7, angulars[1].incident_energy )
            self.assertEqual( 2, angulars[1].NL )
            self.assertEqual( 2, angulars[1].legendre_order )
            self.assertEqual( 2, len( angulars[1].coefficients ) )
            self.assertAlmostEqual( 2.874390e-2  ,  angulars[1].coefficients[0] )
            self.assertAlmostEqual( 3.19645e-11,  angulars[1].coefficients[1] )

            # access via the distributions object
            distribution = chunk.distributions
            self.assertEqual( 1, distribution.LTT )
            self.assertEqual( 1, distribution.LAW )

            self.assertEqual( 2, distribution.NE )
            self.assertEqual( 2, distribution.number_incident_energies )
            self.assertEqual( 1, distribution.NR )
            self.assertEqual( 1, distribution.number_interpolation_regions )
            self.assertEqual( 1, len( distribution.INT ) )
            self.assertEqual( 1, len( distribution.NBT ) )
            self.assertEqual( 1, distribution.INT[0] )
            self.assertEqual( 2, distribution.NBT[0] )
            self.assertEqual( 1, len( distribution.interpolants ) )
            self.assertEqual( 1, len( distribution.boundaries ) )
            self.assertEqual( 1, distribution.interpolants[0] )
            self.assertEqual( 2, distribution.boundaries[0] )

            distributions = distribution.angular_distributions
            d = distributions[0]
            self.assertAlmostEqual( 1e-5, d.E )
            self.assertAlmostEqual( 1e-5, d.incident_energy )
            self.assertEqual( 3, d.NL )
            self.assertEqual( 3, d.legendre_order )
            self.assertEqual( 3, len( d.coefficients ) )
            self.assertAlmostEqual( 7.392510e-5 , d.coefficients[0] )
            self.assertAlmostEqual( 8.477139e-9, d.coefficients[1] )
            self.assertAlmostEqual( 1.17106e-13, d.coefficients[2] )

            d = distributions[1]
            self.assertAlmostEqual( 2e+7, d.E )
            self.assertAlmostEqual( 2e+7, d.incident_energy )
            self.assertEqual( 2, d.NL )
            self.assertEqual( 2, d.legendre_order )
            self.assertEqual( 2, len( d.coefficients ) )
            self.assertAlmostEqual( 2.874390e-2  , d.coefficients[0] )
            self.assertAlmostEqual( 3.19645e-11, d.coefficients[1] )

            self.assertEqual( 8, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_LTT1 + self.valid_SEND,
                              chunk.to_string( 9228, 4 ) )

        def verify_chunk_LTT2( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.MT )
            self.assertEqual( 2, chunk.section_number )

            self.assertEqual( 92235, chunk.ZA )
            self.assertEqual( 92235, chunk.target_identifier )
            self.assertAlmostEqual( 2.330250e+2, chunk.AWR )
            self.assertAlmostEqual( 2.330250e+2, chunk.atomic_weight_ratio )

            self.assertEqual( 1, chunk.LCT )
            self.assertEqual( 1, chunk.reference_frame )
            self.assertEqual( 2, chunk.LTT )
            self.assertEqual( 2, chunk.LAW )
            self.assertEqual( False, chunk.LI )
            self.assertEqual( False, chunk.isotropic_distributions )

            self.assertEqual( 2, chunk.NE )
            self.assertEqual( 2, chunk.number_incident_energies )
            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, chunk.number_interpolation_regions )
            self.assertEqual( 1, len( chunk.NBT ) )
            self.assertEqual( 1, len( chunk.INT ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 2, len( chunk.incident_energies ) )
            self.assertEqual( 2, len( chunk.angular_distributions ) )

            self.assertEqual( 1, chunk.INT[0] )
            self.assertEqual( 2, chunk.NBT[0] )
            self.assertEqual( 1, chunk.interpolants[0] )
            self.assertEqual( 2, chunk.boundaries[0] )
            self.assertAlmostEqual( 1e-5, chunk.incident_energies[0] )
            self.assertAlmostEqual( 2e+7, chunk.incident_energies[1] )

            # direct access
            angulars = chunk.angular_distributions
            self.assertEqual( True, isinstance( angulars[0], TabulatedDistribution ) )
            self.assertEqual( True, isinstance( angulars[1], TabulatedDistribution ) )

            self.assertAlmostEqual( 1e-5, angulars[0].E )
            self.assertAlmostEqual( 1e-5, angulars[0].incident_energy )
            self.assertEqual( 2, angulars[0].NP )
            self.assertEqual( 2, angulars[0].number_points )
            self.assertEqual( 1, angulars[0].NR )
            self.assertEqual( 1, angulars[0].number_interpolation_regions )
            self.assertEqual( 1, len( angulars[0].NBT ) )
            self.assertEqual( 1, len( angulars[0].INT ) )
            self.assertEqual( 2, angulars[0].NBT[0] )
            self.assertEqual( 2, angulars[0].INT[0] )
            self.assertEqual( 1, len( angulars[0].boundaries ) )
            self.assertEqual( 1, len( angulars[0].interpolants ) )
            self.assertEqual( 2, angulars[0].boundaries[0] )
            self.assertEqual( 2, angulars[0].interpolants[0] )
            self.assertEqual( 2, len( angulars[0].cosines ) )
            self.assertAlmostEqual( -1.0 , angulars[0].cosines[0] )
            self.assertAlmostEqual( 1.0, angulars[0].cosines[1] )
            self.assertEqual( 2, len( angulars[0].probabilities ) )
            self.assertAlmostEqual( 0.5 , angulars[0].probabilities[0] )
            self.assertAlmostEqual( 0.5, angulars[0].probabilities[1] )

            self.assertAlmostEqual( 2e+7, angulars[1].E )
            self.assertAlmostEqual( 2e+7, angulars[1].incident_energy )
            self.assertEqual( 3, angulars[1].NP )
            self.assertEqual( 3, angulars[1].number_points )
            self.assertEqual( 1, angulars[1].NR )
            self.assertEqual( 1, angulars[1].number_interpolation_regions )
            self.assertEqual( 1, len( angulars[1].NBT ) )
            self.assertEqual( 1, len( angulars[1].INT ) )
            self.assertEqual( 3, angulars[1].NBT[0] )
            self.assertEqual( 2, angulars[1].INT[0] )
            self.assertEqual( 1, len( angulars[1].boundaries ) )
            self.assertEqual( 1, len( angulars[1].interpolants ) )
            self.assertEqual( 3, angulars[1].boundaries[0] )
            self.assertEqual( 2, angulars[1].interpolants[0] )
            self.assertEqual( 3, len( angulars[1].cosines ) )
            self.assertAlmostEqual( -1.0 , angulars[1].cosines[0] )
            self.assertAlmostEqual( 0.0, angulars[1].cosines[1] )
            self.assertAlmostEqual( 1.0, angulars[1].cosines[2] )
            self.assertEqual( 3, len( angulars[1].probabilities ) )
            self.assertAlmostEqual( 0.0 , angulars[1].probabilities[0] )
            self.assertAlmostEqual( 1.0, angulars[1].probabilities[1] )
            self.assertAlmostEqual( 0.0, angulars[1].probabilities[2] )

            # access via the distributions object
            distribution = chunk.distributions
            self.assertEqual( 2, distribution.LTT )
            self.assertEqual( 2, distribution.LAW )

            self.assertEqual( 2, distribution.NE )
            self.assertEqual( 2, distribution.number_incident_energies )
            self.assertEqual( 1, distribution.NR )
            self.assertEqual( 1, distribution.number_interpolation_regions )
            self.assertEqual( 1, len( distribution.INT ) )
            self.assertEqual( 1, len( distribution.NBT ) )
            self.assertEqual( 1, distribution.INT[0] )
            self.assertEqual( 2, distribution.NBT[0] )
            self.assertEqual( 1, len( distribution.interpolants ) )
            self.assertEqual( 1, len( distribution.boundaries ) )
            self.assertEqual( 1, distribution.interpolants[0] )
            self.assertEqual( 2, distribution.boundaries[0] )

            distributions = distribution.angular_distributions
            d = distributions[0]
            self.assertAlmostEqual( 1e-5, d.E )
            self.assertAlmostEqual( 1e-5, d.incident_energy )
            self.assertEqual( 2, d.NP )
            self.assertEqual( 2, d.number_points )
            self.assertEqual( 1, d.NR )
            self.assertEqual( 1, d.number_interpolation_regions )
            self.assertEqual( 1, len( d.NBT ) )
            self.assertEqual( 1, len( d.INT ) )
            self.assertEqual( 2, d.NBT[0] )
            self.assertEqual( 2, d.INT[0] )
            self.assertEqual( 1, len( d.boundaries ) )
            self.assertEqual( 1, len( d.interpolants ) )
            self.assertEqual( 2, d.boundaries[0] )
            self.assertEqual( 2, d.interpolants[0] )
            self.assertEqual( 2, len( d.cosines ) )
            self.assertAlmostEqual( -1.0 , d.cosines[0] )
            self.assertAlmostEqual( 1.0, d.cosines[1] )
            self.assertEqual( 2, len( d.probabilities ) )
            self.assertAlmostEqual( 0.5 , d.probabilities[0] )
            self.assertAlmostEqual( 0.5, d.probabilities[1] )

            d = distributions[1]
            self.assertAlmostEqual( 2e+7, d.E )
            self.assertAlmostEqual( 2e+7, d.incident_energy )
            self.assertEqual( 3, d.NP )
            self.assertEqual( 3, d.number_points )
            self.assertEqual( 1, d.NR )
            self.assertEqual( 1, d.number_interpolation_regions )
            self.assertEqual( 1, len( d.NBT ) )
            self.assertEqual( 1, len( d.INT ) )
            self.assertEqual( 3, d.NBT[0] )
            self.assertEqual( 2, d.INT[0] )
            self.assertEqual( 1, len( d.boundaries ) )
            self.assertEqual( 1, len( d.interpolants ) )
            self.assertEqual( 3, d.boundaries[0] )
            self.assertEqual( 2, d.interpolants[0] )
            self.assertEqual( 3, len( d.cosines ) )
            self.assertAlmostEqual( -1.0 , d.cosines[0] )
            self.assertAlmostEqual( 0.0, d.cosines[1] )
            self.assertAlmostEqual( 1.0, d.cosines[2] )
            self.assertEqual( 3, len( d.probabilities ) )
            self.assertAlmostEqual( 0.0 , d.probabilities[0] )
            self.assertAlmostEqual( 1.0, d.probabilities[1] )
            self.assertAlmostEqual( 0.0, d.probabilities[2] )

            self.assertEqual( 10, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_LTT2 + self.valid_SEND,
                              chunk.to_string( 9228, 4 ) )

        def verify_chunk_LTT3( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.MT )
            self.assertEqual( 2, chunk.section_number )

            self.assertEqual( 92235, chunk.ZA )
            self.assertEqual( 92235, chunk.target_identifier )
            self.assertAlmostEqual( 2.330250e+2, chunk.AWR )
            self.assertAlmostEqual( 2.330250e+2, chunk.atomic_weight_ratio )

            self.assertEqual( 1, chunk.LCT )
            self.assertEqual( 1, chunk.reference_frame )
            self.assertEqual( 3, chunk.LTT )
            self.assertEqual( 3, chunk.LAW )
            self.assertEqual( False, chunk.LI )
            self.assertEqual( False, chunk.isotropic_distributions )

            self.assertEqual( 4, chunk.NE )
            self.assertEqual( 4, chunk.number_incident_energies )
            self.assertEqual( 2, chunk.NR )
            self.assertEqual( 2, chunk.number_interpolation_regions )
            self.assertEqual( 2, len( chunk.NBT ) )
            self.assertEqual( 2, len( chunk.INT ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertEqual( 4, len( chunk.incident_energies ) )
            self.assertEqual( 4, len( chunk.angular_distributions ) )

            self.assertEqual( 1, chunk.INT[0] )
            self.assertEqual( 5, chunk.INT[1] )
            self.assertEqual( 2, chunk.NBT[0] )
            self.assertEqual( 4, chunk.NBT[1] )
            self.assertEqual( 1, chunk.interpolants[0] )
            self.assertEqual( 5, chunk.interpolants[1] )
            self.assertEqual( 2, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertAlmostEqual( 1e-5, chunk.incident_energies[0] )
            self.assertAlmostEqual( 1e+6, chunk.incident_energies[1] )
            self.assertAlmostEqual( 1e+6, chunk.incident_energies[2] )
            self.assertAlmostEqual( 2e+7, chunk.incident_energies[3] )

            # direct access
            angulars = chunk.angular_distributions
            self.assertEqual( True, isinstance( angulars[0], LegendreCoefficients ) )
            self.assertEqual( True, isinstance( angulars[1], LegendreCoefficients ) )
            self.assertEqual( True, isinstance( angulars[2], TabulatedDistribution ) )
            self.assertEqual( True, isinstance( angulars[3], TabulatedDistribution ) )

            self.assertAlmostEqual( 1e-5, angulars[0].E )
            self.assertAlmostEqual( 1e-5, angulars[0].incident_energy )
            self.assertEqual( 3, angulars[0].NL )
            self.assertEqual( 3, angulars[0].legendre_order )
            self.assertEqual( 3, len( angulars[0].coefficients ) )
            self.assertAlmostEqual( 7.392510e-5 , angulars[0].coefficients[0] )
            self.assertAlmostEqual( 8.477139e-9, angulars[0].coefficients[1] )
            self.assertAlmostEqual( 1.17106e-13, angulars[0].coefficients[2] )

            self.assertAlmostEqual( 1e+6, angulars[1].E )
            self.assertAlmostEqual( 1e+6, angulars[1].incident_energy )
            self.assertEqual( 2, angulars[1].NL )
            self.assertEqual( 2, angulars[1].legendre_order )
            self.assertEqual( 2, len( angulars[1].coefficients ) )
            self.assertAlmostEqual( 2.874390e-2  , angulars[1].coefficients[0] )
            self.assertAlmostEqual( 3.19645e-11, angulars[1].coefficients[1] )

            self.assertAlmostEqual( 1e+6, angulars[2].E )
            self.assertAlmostEqual( 1e+6, angulars[2].incident_energy )
            self.assertEqual( 2, angulars[2].NP )
            self.assertEqual( 2, angulars[2].number_points )
            self.assertEqual( 1, angulars[2].NR )
            self.assertEqual( 1, angulars[2].number_interpolation_regions )
            self.assertEqual( 1, len( angulars[2].NBT ) )
            self.assertEqual( 1, len( angulars[2].INT ) )
            self.assertEqual( 2, angulars[2].NBT[0] )
            self.assertEqual( 2, angulars[2].INT[0] )
            self.assertEqual( 1, len( angulars[2].boundaries ) )
            self.assertEqual( 1, len( angulars[2].interpolants ) )
            self.assertEqual( 2, angulars[2].boundaries[0] )
            self.assertEqual( 2, angulars[2].interpolants[0] )
            self.assertEqual( 2, len( angulars[2].cosines ) )
            self.assertAlmostEqual( -1.0 , angulars[2].cosines[0] )
            self.assertAlmostEqual( 1.0, angulars[2].cosines[1] )
            self.assertEqual( 2, len( angulars[2].probabilities ) )
            self.assertAlmostEqual( 0.5 , angulars[2].probabilities[0] )
            self.assertAlmostEqual( 0.5, angulars[2].probabilities[1] )

            self.assertAlmostEqual( 2e+7, angulars[3].E )
            self.assertAlmostEqual( 2e+7, angulars[3].incident_energy )
            self.assertEqual( 3, angulars[3].NP )
            self.assertEqual( 3, angulars[3].number_points )
            self.assertEqual( 1, angulars[3].NR )
            self.assertEqual( 1, angulars[3].number_interpolation_regions )
            self.assertEqual( 1, len( angulars[3].NBT ) )
            self.assertEqual( 1, len( angulars[3].INT ) )
            self.assertEqual( 3, angulars[3].NBT[0] )
            self.assertEqual( 2, angulars[3].INT[0] )
            self.assertEqual( 1, len( angulars[3].boundaries ) )
            self.assertEqual( 1, len( angulars[3].interpolants ) )
            self.assertEqual( 3, angulars[3].boundaries[0] )
            self.assertEqual( 2, angulars[3].interpolants[0] )
            self.assertEqual( 3, len( angulars[3].cosines ) )
            self.assertAlmostEqual( -1.0 , angulars[3].cosines[0] )
            self.assertAlmostEqual( 0.0, angulars[3].cosines[1] )
            self.assertAlmostEqual( 1.0, angulars[3].cosines[2] )
            self.assertEqual( 3, len( angulars[3].probabilities ) )
            self.assertAlmostEqual( 0.0 , angulars[3].probabilities[0] )
            self.assertAlmostEqual( 1.0, angulars[3].probabilities[1] )
            self.assertAlmostEqual( 0.0, angulars[3].probabilities[2] )

            # access via the distributions object
            distribution = chunk.distributions
            self.assertEqual( 3, distribution.LTT )
            self.assertEqual( 3, distribution.LAW )

            self.assertEqual( 2, distribution.NR )
            self.assertEqual( 2, distribution.number_interpolation_regions )
            self.assertEqual( 4, distribution.NE )
            self.assertEqual( 4, distribution.number_incident_energies )
            self.assertEqual( 2, len( distribution.INT ) )
            self.assertEqual( 2, len( distribution.NBT ) )
            self.assertEqual( 1, distribution.INT[0] )
            self.assertEqual( 5, distribution.INT[1] )
            self.assertEqual( 2, distribution.NBT[0] )
            self.assertEqual( 4, distribution.NBT[1] )
            self.assertEqual( 2, len( distribution.interpolants ) )
            self.assertEqual( 2, len( distribution.boundaries ) )
            self.assertEqual( 1, distribution.interpolants[0] )
            self.assertEqual( 5, distribution.interpolants[1] )
            self.assertEqual( 2, distribution.boundaries[0] )
            self.assertEqual( 4, distribution.boundaries[1] )

            self.assertEqual( 2, distribution.legendre.NE )
            self.assertEqual( 2, distribution.legendre.number_incident_energies )
            self.assertEqual( 1, distribution.legendre.NR )
            self.assertEqual( 1, distribution.legendre.number_interpolation_regions )
            self.assertEqual( 1, len( distribution.legendre.INT ) )
            self.assertEqual( 1, len( distribution.legendre.NBT ) )
            self.assertEqual( 1, distribution.legendre.INT[0] )
            self.assertEqual( 2, distribution.legendre.NBT[0] )
            self.assertEqual( 1, len( distribution.legendre.interpolants ) )
            self.assertEqual( 1, len( distribution.legendre.boundaries ) )
            self.assertEqual( 1, distribution.legendre.interpolants[0] )
            self.assertEqual( 2, distribution.legendre.boundaries[0] )

            ldistributions = distribution.legendre.angular_distributions

            ld = ldistributions[0]
            self.assertAlmostEqual( 1e-5, ld.E )
            self.assertAlmostEqual( 1e-5, ld.incident_energy )
            self.assertEqual( 3, ld.NL )
            self.assertEqual( 3, ld.legendre_order )
            self.assertEqual( 3, len( ld.coefficients ) )
            self.assertAlmostEqual( 7.392510e-5 , ld.coefficients[0] )
            self.assertAlmostEqual( 8.477139e-9, ld.coefficients[1] )
            self.assertAlmostEqual( 1.17106e-13, ld.coefficients[2] )

            ld = ldistributions[1]
            self.assertAlmostEqual( 1e+6, ld.E )
            self.assertAlmostEqual( 1e+6, ld.incident_energy )
            self.assertEqual( 2, ld.NL )
            self.assertEqual( 2, ld.legendre_order )
            self.assertEqual( 2, len( ld.coefficients ) )
            self.assertAlmostEqual( 2.874390e-2  , ld.coefficients[0] )
            self.assertAlmostEqual( 3.19645e-11, ld.coefficients[1] )

            self.assertEqual( 2, distribution.tabulated.NE )
            self.assertEqual( 2, distribution.tabulated.number_incident_energies )
            self.assertEqual( 1, distribution.tabulated.NR )
            self.assertEqual( 1, distribution.tabulated.number_interpolation_regions )
            self.assertEqual( 1, len( distribution.tabulated.INT ) )
            self.assertEqual( 1, len( distribution.tabulated.NBT ) )
            self.assertEqual( 5, distribution.tabulated.INT[0] )
            self.assertEqual( 2, distribution.tabulated.NBT[0] )
            self.assertEqual( 1, len( distribution.tabulated.interpolants ) )
            self.assertEqual( 1, len( distribution.tabulated.boundaries ) )
            self.assertEqual( 5, distribution.tabulated.interpolants[0] )
            self.assertEqual( 2, distribution.tabulated.boundaries[0] )

            tdistributions = distribution.tabulated.angular_distributions

            td = tdistributions[0]
            self.assertAlmostEqual( 1e+6, td.E )
            self.assertAlmostEqual( 1e+6, td.incident_energy )
            self.assertEqual( 2, td.NP )
            self.assertEqual( 2, td.number_points )
            self.assertEqual( 1, td.NR )
            self.assertEqual( 1, td.number_interpolation_regions )
            self.assertEqual( 1, len( td.NBT ) )
            self.assertEqual( 1, len( td.INT ) )
            self.assertEqual( 2, td.NBT[0] )
            self.assertEqual( 2, td.INT[0] )
            self.assertEqual( 1, len( td.boundaries ) )
            self.assertEqual( 1, len( td.interpolants ) )
            self.assertEqual( 2, td.boundaries[0] )
            self.assertEqual( 2, td.interpolants[0] )
            self.assertEqual( 2, len( td.cosines ) )
            self.assertAlmostEqual( -1.0 , td.cosines[0] )
            self.assertAlmostEqual( 1.0, td.cosines[1] )
            self.assertEqual( 2, len( td.probabilities ) )
            self.assertAlmostEqual( 0.5 , td.probabilities[0] )
            self.assertAlmostEqual( 0.5, td.probabilities[1] )

            td = tdistributions[1]
            self.assertAlmostEqual( 2e+7, td.E )
            self.assertAlmostEqual( 2e+7, td.incident_energy )
            self.assertEqual( 3, td.NP )
            self.assertEqual( 3, td.number_points )
            self.assertEqual( 1, td.NR )
            self.assertEqual( 1, td.number_interpolation_regions )
            self.assertEqual( 1, len( td.NBT ) )
            self.assertEqual( 1, len( td.INT ) )
            self.assertEqual( 3, td.NBT[0] )
            self.assertEqual( 2, td.INT[0] )
            self.assertEqual( 1, len( td.boundaries ) )
            self.assertEqual( 1, len( td.interpolants ) )
            self.assertEqual( 3, td.boundaries[0] )
            self.assertEqual( 2, td.interpolants[0] )
            self.assertEqual( 3, len( td.cosines ) )
            self.assertAlmostEqual( -1.0 , td.cosines[0] )
            self.assertAlmostEqual( 0.0, td.cosines[1] )
            self.assertAlmostEqual( 1.0, td.cosines[2] )
            self.assertEqual( 3, len( td.probabilities ) )
            self.assertAlmostEqual( 0.0 , td.probabilities[0] )
            self.assertAlmostEqual( 1.0, td.probabilities[1] )
            self.assertAlmostEqual( 0.0, td.probabilities[2] )

            self.assertEqual( 16, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_LTT3 + self.valid_SEND,
                              chunk.to_string( 9228, 4 ) )

        # the data is given explicitly for LTT=0
        chunk = Section( mt = 18, lct = 1, zaid = 92235, awr = 2.330250e+2,
                         distributions = Isotropic() )

        verify_chunk_LTT0( self, chunk )

        # the data is read from a string for LTT=0
        chunk = Section.from_string( self.chunk_LTT0 + self.valid_SEND )

        verify_chunk_LTT0( self, chunk )

        # the data is retrieved from a tree element and parsed for LTT=0
        tape = Tape.from_string( self.valid_TPID + self.chunk_LTT0 +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.materials.front().file( 4 ).section( 18 ).parse()

        verify_chunk_LTT0( self, chunk )

        # the data is copied for LTT=0
        copy = Section( chunk )

        verify_chunk_LTT0( self, copy )

        # the data is given explicitly for LTT=1
        distributions = LegendreDistributions(
                          boundaries = [ 2 ], interpolants = [ 1 ],
                          distributions = [ LegendreCoefficients( 1e-5, [ 7.392510e-5, 8.477139e-9, 1.17106e-13 ] ),
                                            LegendreCoefficients( 2e+7, [ 2.874390e-2, 3.19645e-11 ] ) ] )

        chunk = Section( mt = 2, lct = 1, zaid = 92235, awr = 2.330250e+2,
                         distributions = distributions )

        verify_chunk_LTT1( self, chunk )

        # the data is read from a string for LTT=1
        chunk = Section.from_string( self.chunk_LTT1 + self.valid_SEND )

        verify_chunk_LTT1( self, chunk )

        # the data is retrieved from a tree element and parsed for LTT=1
        tape = Tape.from_string( self.valid_TPID + self.chunk_LTT1 +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.materials.front().file( 4 ).section( 2 ).parse()

        verify_chunk_LTT1( self, chunk )

        # the data is copied for LTT=1
        copy = Section( chunk )

        verify_chunk_LTT1( self, copy )

        # the data is given explicitly for LTT=2
        distributions = TabulatedDistributions(
                            boundaries = [ 2 ], interpolants = [ 1 ],
                            distributions = [ TabulatedDistribution( 1e-5, [ 2 ], [ 2 ], [ -1.0, 1.0 ], [ 0.5, 0.5 ] ),
                                              TabulatedDistribution( 2e+7, [ 3 ], [ 2 ], [ -1.0, 0.0, 1.0 ], [ 0.0, 1.0, 0.0 ] ) ] )

        chunk = Section( mt = 2, lct = 1, zaid = 92235, awr = 2.330250e+2,
                         distributions = distributions )

        verify_chunk_LTT2( self, chunk )

        # the data is read from a string for LTT=2
        chunk = Section.from_string( self.chunk_LTT2 + self.valid_SEND )

        verify_chunk_LTT2( self, chunk )

        # the data is retrieved from a tree element and parsed for LTT=2
        tape = Tape.from_string( self.valid_TPID + self.chunk_LTT2 +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.materials.front().file( 4 ).section( 2 ).parse()

        verify_chunk_LTT2( self, chunk )

        # the data is copied for LTT=2
        copy = Section( chunk )

        verify_chunk_LTT2( self, copy )

        # the data is given explicitly for LTT=3
        distributions = MixedDistributions(
                            legendre = LegendreDistributions(
                                         [ 2 ], [ 1 ],
        	                             [ LegendreCoefficients( 1e-5, [ 7.392510e-5, 8.477139e-9, 1.17106e-13 ] ),
                                           LegendreCoefficients( 1e+6, [ 2.874390e-2, 3.19645e-11 ] ) ] ),
                            tabulated  = TabulatedDistributions(
                                           [ 2 ], [ 5 ],
                                           [ TabulatedDistribution( 1e+6, [ 2 ], [ 2 ], [ -1.0, 1.0 ], [ 0.5, 0.5 ] ),
                                             TabulatedDistribution( 2e+7, [ 3 ], [ 2 ], [ -1.0, 0.0, 1.0 ], [ 0.0, 1.0, 0.0 ] ) ] ) )

        chunk = Section( mt = 2, lct = 1, zaid = 92235, awr = 2.330250e+2,
                         distributions = distributions )

        verify_chunk_LTT3( self, chunk )

        # the data is read from a string for LTT=3
        chunk = Section.from_string( self.chunk_LTT3 + self.valid_SEND )

        verify_chunk_LTT3( self, chunk )

        # the data is retrieved from a tree element and parsed for LTT=3
        tape = Tape.from_string( self.valid_TPID + self.chunk_LTT3 +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.materials.front().file( 4 ).section( 2 ).parse()

        verify_chunk_LTT3( self, chunk )

        # the data is copied for LTT=3
        copy = Section( chunk )

        verify_chunk_LTT3( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # illegal SEND for LTT=0
        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.chunk_LTT0 + self.invalid_SEND )

        # illegal SEND for LTT=1
        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.chunk_LTT1 + self.invalid_SEND )

        # illegal SEND for LTT=2
        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.chunk_LTT2 + self.invalid_SEND )

        # illegal SEND for LTT=3
        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.chunk_LTT3 + self.invalid_SEND )

        # illegal LTT
        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.invalid + self.valid_SEND )

if __name__ == '__main__' :

    unittest.main()
