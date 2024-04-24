# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF6 import Section
from ENDFtk.MF6 import Multiplicity
from ENDFtk.MF6 import ReactionProduct
from ENDFtk.MF6 import ContinuumEnergyAngle
from ENDFtk.MF6.LAW1 import LegendreCoefficients
from ENDFtk.tree import Tape

class Test_ENDFtk_MF6_Section( unittest.TestCase ) :
    """Unit test for the Section class."""

    chunk = ( ' 9.223500+4 2.330248+2          0          2          3          09228 6  5     \n'
              ' 1.001000+3 9.986234-1          0          1          1          49228 6  5     \n'
              '          4          2                                            9228 6  5     \n'
              ' 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6  5     \n'
              ' 2.000000+7 2.149790-1                                            9228 6  5     \n'
              ' 0.000000+0 0.000000+0          1          2          1          29228 6  5     \n'
              '          2          1                                            9228 6  5     \n'
              ' 0.000000+0 1.000000-5          0          1         12          49228 6  5     \n'
              ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n'
              ' 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n'
              ' 0.000000+0 2.000000+7          0          1          6          29228 6  5     \n'
              ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n'
              ' 1.000000+0 1.000000+0          0          1          1          29228 6  5     \n'
              '          2          2                                            9228 6  5     \n'
              ' 1.858639+7 4.000000+0 2.000000+7 4.000000+0                      9228 6  5     \n'
              ' 0.000000+0 0.000000+0          1          2          1          29228 6  5     \n'
              '          2         22                                            9228 6  5     \n'
              ' 0.000000+0 1.858639+7          0          0          6          39228 6  5     \n'
              ' 0.000000+0 0.000000+0 5.000000-1 2.000000+0 1.000000+0 0.000000+09228 6  5     \n'
              ' 0.000000+0 2.000000+7          0          0          6          39228 6  5     \n'
              ' 0.000000+0 0.000000+0 5.000000-1 2.000000+0 1.000000+0 0.000000+09228 6  5     \n'
              ' 0.000000+0 0.000000+0          0          1          1          39228 6  5     \n'
              '          3          2                                            9228 6  5     \n'
              ' 1.858639+7 1.000000+0 1.900000+7 2.000000+0 2.000000+7 3.000000+09228 6  5     \n'
              ' 0.000000+0 0.000000+0          1          2          1          29228 6  5     \n'
              '          2          5                                            9228 6  5     \n'
              ' 0.000000+0 1.858639+7          0          0          6          39228 6  5     \n'
              ' 0.000000+0 0.000000+0 1.000000+0 1.000000+0 2.000000+0 0.000000+09228 6  5     \n'
              ' 0.000000+0 2.000000+7          0          0          6          39228 6  5     \n'
              ' 0.000000+0 0.000000+0 1.000000+0 1.000000+0 2.000000+0 0.000000+09228 6  5     \n' )

    valid_TPID = 'Just a tape identifier                                                          \n'
    valid_SEND = '                                                                  9228 6  0     \n'
    valid_FEND = '                                                                  9228 0  0     \n'
    valid_MEND = '                                                                     0 0  0     \n'
    valid_TEND = '                                                                    -1 0  0     \n'
    invalid_SEND = '                                                                  9228 3  1     \n'

    def test_section( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 5, chunk.MT )
            self.assertEqual( 5, chunk.section_number )
            self.assertEqual( 92235, chunk.ZA )
            self.assertEqual( 92235, chunk.target_identifier )
            self.assertAlmostEqual( 2.330248e+2, chunk.AWR )
            self.assertAlmostEqual( 2.330248e+2, chunk.atomic_weight_ratio )
            self.assertEqual( 0, chunk.JP )
            self.assertEqual( 0, chunk.average_multiple_particles_flag )
            self.assertEqual( 2, chunk.LCT )
            self.assertEqual( 2, chunk.reference_frame )
            self.assertEqual( 3, chunk.NK )
            self.assertEqual( 3, chunk.number_reaction_products )
            self.assertEqual( 5, chunk.MT )

            self.assertEqual( True, chunk.has_reaction_product( 1001 ) )
            self.assertEqual( True, chunk.has_reaction_product( 1 ) )
            self.assertEqual( True, chunk.has_reaction_product( 0 ) )
            self.assertEqual( False, chunk.has_reaction_product( 2004 ) )

            products = chunk.reaction_products
            self.assertEqual( 3, len( products ) )

            # product 1
            self.assertEqual( 1001, products[0].ZAP )
            self.assertEqual( 1001, products[0].product_identifier )
            self.assertAlmostEqual( 0.9986234, products[0].AWP )
            self.assertAlmostEqual( 0.9986234, products[0].product_weight_ratio )
            self.assertEqual( 0, products[0].LIP )
            self.assertEqual( 0, products[0].product_modifier_flag )
            self.assertEqual( 1, products[0].LAW )

            self.assertEqual( 1001, products[0].multiplicity.ZAP )
            self.assertEqual( 1001, products[0].multiplicity.product_identifier )
            self.assertAlmostEqual( 0.9986234, products[0].multiplicity.AWP )
            self.assertAlmostEqual( 0.9986234, products[0].multiplicity.product_weight_ratio )
            self.assertEqual( 0, products[0].multiplicity.LIP )
            self.assertEqual( 0, products[0].multiplicity.product_modifier_flag )
            self.assertEqual( 1, products[0].multiplicity.LAW )

            self.assertEqual( 4, products[0].multiplicity.NP )
            self.assertEqual( 4, products[0].multiplicity.number_points )
            self.assertEqual( 1, products[0].multiplicity.NR )
            self.assertEqual( 1, products[0].multiplicity.number_interpolation_regions )
            self.assertEqual( 1, len( products[0].multiplicity.INT ) )
            self.assertEqual( 1, len( products[0].multiplicity.NBT ) )
            self.assertEqual( 2, products[0].multiplicity.INT[0] )
            self.assertEqual( 4, products[0].multiplicity.NBT[0] )
            self.assertEqual( 1, len( products[0].multiplicity.interpolants ) )
            self.assertEqual( 1, len( products[0].multiplicity.boundaries ) )
            self.assertEqual( 2, products[0].multiplicity.interpolants[0] )
            self.assertEqual( 4, products[0].multiplicity.boundaries[0] )
            self.assertEqual( 4, len( products[0].multiplicity.energies ) )
            self.assertEqual( 4, len( products[0].multiplicity.multiplicities ) )
            self.assertAlmostEqual( 1e-5, products[0].multiplicity.energies[0] )
            self.assertAlmostEqual( 1.1e+7, products[0].multiplicity.energies[1] )
            self.assertAlmostEqual( 1.147e+7, products[0].multiplicity.energies[2] )
            self.assertAlmostEqual( 2e+7, products[0].multiplicity.energies[3] )
            self.assertAlmostEqual( 0., products[0].multiplicity.multiplicities[0] )
            self.assertAlmostEqual( 8.45368e-11, products[0].multiplicity.multiplicities[1] )
            self.assertAlmostEqual( 6.622950e-8, products[0].multiplicity.multiplicities[2] )
            self.assertAlmostEqual( 2.149790e-1, products[0].multiplicity.multiplicities[3] )

            law = products[0].distribution
            self.assertEqual( True, isinstance( law, ContinuumEnergyAngle ) )

            self.assertEqual( 1, law.LAW )
            self.assertEqual( 2, law.LEP )
            self.assertEqual( 2, law.NE )
            self.assertEqual( 2, law.number_incident_energies )
            self.assertEqual( 1, law.NR )
            self.assertEqual( 1, law.number_interpolation_regions )
            self.assertEqual( 1, len( law.INT ) )
            self.assertEqual( 1, len( law.NBT ) )
            self.assertEqual( 1, law.INT[0] )
            self.assertEqual( 2, law.NBT[0] )
            self.assertEqual( 1, len( law.interpolants ) )
            self.assertEqual( 1, len( law.boundaries ) )
            self.assertEqual( 1, law.interpolants[0] )
            self.assertEqual( 2, law.boundaries[0] )

            energies = law.distributions
            self.assertEqual( True, isinstance( energies[0], LegendreCoefficients ) )
            self.assertEqual( True, isinstance( energies[1], LegendreCoefficients ) )

            subsection1 = energies[0]
            self.assertEqual( 0, subsection1.ND )
            self.assertEqual( 0, subsection1.number_discrete_energies )
            self.assertEqual( 1, subsection1.NA )
            self.assertEqual( 1, subsection1.number_angular_parameters )
            self.assertEqual( 12, subsection1.NW )
            self.assertEqual( 4, subsection1.NEP )
            self.assertEqual( 4, subsection1.number_secondary_energies )
            self.assertEqual( 4, len( subsection1.energies ) )
            self.assertAlmostEqual( 1., subsection1.energies[0] )
            self.assertAlmostEqual( 4., subsection1.energies[1] )
            self.assertAlmostEqual( 7., subsection1.energies[2] )
            self.assertAlmostEqual( 10., subsection1.energies[3] )
            self.assertEqual( 4, len( subsection1.coefficients ) )
            self.assertAlmostEqual( 2., subsection1.coefficients[0][0] )
            self.assertAlmostEqual( 3., subsection1.coefficients[0][1] )
            self.assertAlmostEqual( 5., subsection1.coefficients[1][0] )
            self.assertAlmostEqual( 6., subsection1.coefficients[1][1] )
            self.assertAlmostEqual( 8., subsection1.coefficients[2][0] )
            self.assertAlmostEqual( 9., subsection1.coefficients[2][1] )
            self.assertAlmostEqual( 11., subsection1.coefficients[3][0] )
            self.assertAlmostEqual( 12., subsection1.coefficients[3][1] )
            self.assertEqual( 4, len( subsection1.total_emission_probabilities ) )
            self.assertAlmostEqual( 2., subsection1.total_emission_probabilities[0] )
            self.assertAlmostEqual( 5., subsection1.total_emission_probabilities[1] )
            self.assertAlmostEqual( 8., subsection1.total_emission_probabilities[2] )
            self.assertAlmostEqual( 11., subsection1.total_emission_probabilities[3] )

            subsection2 = energies[1]
            self.assertEqual( 1, subsection2.LANG )
            self.assertEqual( 0, subsection2.ND )
            self.assertEqual( 0, subsection2.number_discrete_energies )
            self.assertEqual( 1, subsection2.NA )
            self.assertEqual( 1, subsection2.number_angular_parameters )
            self.assertEqual( 6, subsection2.NW )
            self.assertEqual( 2, subsection2.NEP )
            self.assertEqual( 2, subsection2.number_secondary_energies )
            self.assertEqual( 2, len( subsection2.energies ) )
            self.assertAlmostEqual( 1., subsection2.energies[0] )
            self.assertAlmostEqual( 4., subsection2.energies[1] )
            self.assertEqual( 2, len( subsection2.coefficients ) )
            self.assertAlmostEqual( 2., subsection2.coefficients[0][0] )
            self.assertAlmostEqual( 3., subsection2.coefficients[0][1] )
            self.assertAlmostEqual( 5., subsection2.coefficients[1][0] )
            self.assertAlmostEqual( 6., subsection2.coefficients[1][1] )
            self.assertEqual( 2, len( subsection2.total_emission_probabilities ) )
            self.assertAlmostEqual( 2., subsection2.total_emission_probabilities[0] )
            self.assertAlmostEqual( 5., subsection2.total_emission_probabilities[1] )

            # product 2
            self.assertEqual( 1, products[1].ZAP )
            self.assertEqual( 1, products[1].product_identifier )
            self.assertAlmostEqual( 1., products[1].AWP )
            self.assertAlmostEqual( 1., products[1].product_weight_ratio )
            self.assertEqual( 0, products[1].LIP )
            self.assertEqual( 0, products[1].product_modifier_flag )
            self.assertEqual( 1, products[1].LAW )

            self.assertEqual( 1, products[1].multiplicity.ZAP )
            self.assertEqual( 1, products[1].multiplicity.product_identifier )
            self.assertAlmostEqual( 1., products[1].multiplicity.AWP )
            self.assertAlmostEqual( 1., products[1].multiplicity.product_weight_ratio )
            self.assertEqual( 0, products[1].multiplicity.LIP )
            self.assertEqual( 0, products[1].multiplicity.product_modifier_flag )
            self.assertEqual( 1, products[1].multiplicity.LAW )

            self.assertEqual( 2, products[1].multiplicity.NP )
            self.assertEqual( 2, products[1].multiplicity.number_points )
            self.assertEqual( 1, products[1].multiplicity.NR )
            self.assertEqual( 1, products[1].multiplicity.number_interpolation_regions )
            self.assertEqual( 1, len( products[1].multiplicity.INT ) )
            self.assertEqual( 1, len( products[1].multiplicity.NBT ) )
            self.assertEqual( 2, products[1].multiplicity.INT[0] )
            self.assertEqual( 2, products[1].multiplicity.NBT[0] )
            self.assertEqual( 1, len( products[1].multiplicity.interpolants ) )
            self.assertEqual( 1, len( products[1].multiplicity.boundaries ) )
            self.assertEqual( 2, products[1].multiplicity.interpolants[0] )
            self.assertEqual( 2, products[1].multiplicity.boundaries[0] )
            self.assertEqual( 2, len( products[1].multiplicity.energies ) )
            self.assertEqual( 2, len( products[1].multiplicity.multiplicities ) )
            self.assertAlmostEqual( 1.858639e+7, products[1].multiplicity.energies[0] )
            self.assertAlmostEqual( 2e+7, products[1].multiplicity.energies[1] )
            self.assertAlmostEqual( 4., products[1].multiplicity.multiplicities[0] )
            self.assertAlmostEqual( 4., products[1].multiplicity.multiplicities[1] )

            law = products[1].distribution
            self.assertEqual( True, isinstance( law, ContinuumEnergyAngle ) )

            self.assertEqual( 1, law.LAW )
            self.assertEqual( 2, law.LEP )
            self.assertEqual( 2, law.NE )
            self.assertEqual( 2, law.number_incident_energies )
            self.assertEqual( 1, law.NR )
            self.assertEqual( 1, law.number_interpolation_regions )
            self.assertEqual( 1, len( law.INT ) )
            self.assertEqual( 1, len( law.NBT ) )
            self.assertEqual( 22, law.INT[0] )
            self.assertEqual( 2, law.NBT[0] )
            self.assertEqual( 1, len( law.interpolants ) )
            self.assertEqual( 1, len( law.boundaries ) )
            self.assertEqual( 22, law.interpolants[0] )
            self.assertEqual( 2, law.boundaries[0] )

            energies = law.distributions
            self.assertEqual( True, isinstance( energies[0], LegendreCoefficients ) )
            self.assertEqual( True, isinstance( energies[1], LegendreCoefficients ) )

            subsection1 = energies[0]
            self.assertEqual( 0, subsection1.ND )
            self.assertEqual( 0, subsection1.number_discrete_energies )
            self.assertEqual( 0, subsection1.NA )
            self.assertEqual( 0, subsection1.number_angular_parameters )
            self.assertEqual( 6, subsection1.NW )
            self.assertEqual( 3, subsection1.NEP )
            self.assertEqual( 3, subsection1.number_secondary_energies )
            self.assertEqual( 3, len( subsection1.energies ) )
            self.assertAlmostEqual( 0., subsection1.energies[0] )
            self.assertAlmostEqual( 0.5, subsection1.energies[1] )
            self.assertAlmostEqual( 1., subsection1.energies[2] )
            self.assertEqual( 3, len( subsection1.coefficients ) )
            self.assertAlmostEqual( 0., subsection1.coefficients[0][0] )
            self.assertAlmostEqual( 2., subsection1.coefficients[1][0] )
            self.assertAlmostEqual( 0., subsection1.coefficients[2][0] )
            self.assertEqual( 3, len( subsection1.total_emission_probabilities ) )
            self.assertAlmostEqual( 0., subsection1.total_emission_probabilities[0] )
            self.assertAlmostEqual( 2., subsection1.total_emission_probabilities[1] )
            self.assertAlmostEqual( 0., subsection1.total_emission_probabilities[2] )

            subsection2 = energies[1]
            self.assertEqual( 1, subsection2.LANG )
            self.assertEqual( 0, subsection2.ND )
            self.assertEqual( 0, subsection2.number_discrete_energies )
            self.assertEqual( 0, subsection2.NA )
            self.assertEqual( 0, subsection2.number_angular_parameters )
            self.assertEqual( 6, subsection2.NW )
            self.assertEqual( 3, subsection2.NEP )
            self.assertEqual( 3, subsection2.number_secondary_energies )
            self.assertEqual( 3, len( subsection2.energies ) )
            self.assertAlmostEqual( 0., subsection2.energies[0] )
            self.assertAlmostEqual( .5, subsection2.energies[1] )
            self.assertAlmostEqual( 1., subsection2.energies[2] )
            self.assertEqual( 3, len( subsection2.coefficients ) )
            self.assertAlmostEqual( 0., subsection2.coefficients[0][0] )
            self.assertAlmostEqual( 2., subsection2.coefficients[1][0] )
            self.assertAlmostEqual( 0., subsection2.coefficients[2][0] )
            self.assertEqual( 3, len( subsection2.total_emission_probabilities ) )
            self.assertAlmostEqual( 0., subsection2.total_emission_probabilities[0] )
            self.assertAlmostEqual( 2., subsection2.total_emission_probabilities[1] )
            self.assertAlmostEqual( 0., subsection2.total_emission_probabilities[2] )

            # product 3
            self.assertEqual( 0, products[2].ZAP )
            self.assertEqual( 0, products[2].product_identifier )
            self.assertAlmostEqual( 0., products[2].AWP )
            self.assertAlmostEqual( 0., products[2].product_weight_ratio )
            self.assertEqual( 0, products[2].LIP )
            self.assertEqual( 0, products[2].product_modifier_flag )
            self.assertEqual( 1, products[2].LAW )

            self.assertEqual( 0, products[2].multiplicity.ZAP )
            self.assertEqual( 0, products[2].multiplicity.product_identifier )
            self.assertAlmostEqual( 0., products[2].multiplicity.AWP )
            self.assertAlmostEqual( 0., products[2].multiplicity.product_weight_ratio )
            self.assertEqual( 0, products[2].multiplicity.LIP )
            self.assertEqual( 0, products[2].multiplicity.product_modifier_flag )
            self.assertEqual( 1, products[2].multiplicity.LAW )

            self.assertEqual( 3, products[2].multiplicity.NP )
            self.assertEqual( 1, products[2].multiplicity.NR )
            self.assertEqual( 1, len( products[2].multiplicity.interpolants ) )
            self.assertEqual( 1, len( products[2].multiplicity.boundaries ) )
            self.assertEqual( 2, products[2].multiplicity.interpolants[0] )
            self.assertEqual( 3, products[2].multiplicity.boundaries[0] )
            self.assertEqual( 3, len( products[2].multiplicity.energies ) )
            self.assertEqual( 3, len( products[2].multiplicity.multiplicities ) )
            self.assertAlmostEqual( 1.858639e+7, products[2].multiplicity.energies[0] )
            self.assertAlmostEqual( 1.9e+7, products[2].multiplicity.energies[1] )
            self.assertAlmostEqual( 2e+7, products[2].multiplicity.energies[2] )
            self.assertAlmostEqual( 1., products[2].multiplicity.multiplicities[0] )
            self.assertAlmostEqual( 2., products[2].multiplicity.multiplicities[1] )
            self.assertAlmostEqual( 3., products[2].multiplicity.multiplicities[2] )

            law = products[2].distribution
            self.assertEqual( True, isinstance( law, ContinuumEnergyAngle ) )

            self.assertEqual( 1, law.LAW )
            self.assertEqual( 2, law.LEP )
            self.assertEqual( 2, law.NE )
            self.assertEqual( 2, law.number_incident_energies )
            self.assertEqual( 1, law.NR )
            self.assertEqual( 1, law.number_interpolation_regions )
            self.assertEqual( 1, len( law.INT ) )
            self.assertEqual( 1, len( law.NBT ) )
            self.assertEqual( 5, law.INT[0] )
            self.assertEqual( 2, law.NBT[0] )
            self.assertEqual( 1, len( law.interpolants ) )
            self.assertEqual( 1, len( law.boundaries ) )
            self.assertEqual( 5, law.interpolants[0] )
            self.assertEqual( 2, law.boundaries[0] )

            energies = law.distributions
            self.assertEqual( True, isinstance( energies[0], LegendreCoefficients ) )
            self.assertEqual( True, isinstance( energies[1], LegendreCoefficients ) )

            subsection1 = energies[0]
            self.assertEqual( 0, subsection1.ND )
            self.assertEqual( 0, subsection1.number_discrete_energies )
            self.assertEqual( 0, subsection1.NA )
            self.assertEqual( 0, subsection1.number_angular_parameters )
            self.assertEqual( 6, subsection1.NW )
            self.assertEqual( 3, subsection1.NEP )
            self.assertEqual( 3, subsection1.number_secondary_energies )
            self.assertEqual( 3, len( subsection1.energies ) )
            self.assertAlmostEqual( 0., subsection1.energies[0] )
            self.assertAlmostEqual( 1., subsection1.energies[1] )
            self.assertAlmostEqual( 2., subsection1.energies[2] )
            self.assertEqual( 3, len( subsection1.coefficients ) )
            self.assertAlmostEqual( 0., subsection1.coefficients[0][0] )
            self.assertAlmostEqual( 1., subsection1.coefficients[1][0] )
            self.assertAlmostEqual( 0., subsection1.coefficients[2][0] )
            self.assertEqual( 3, len( subsection1.total_emission_probabilities ) )
            self.assertAlmostEqual( 0., subsection1.total_emission_probabilities[0] )
            self.assertAlmostEqual( 1., subsection1.total_emission_probabilities[1] )
            self.assertAlmostEqual( 0., subsection1.total_emission_probabilities[2] )

            subsection2 = energies[1]
            self.assertEqual( 1, subsection2.LANG )
            self.assertEqual( 0, subsection2.ND )
            self.assertEqual( 0, subsection2.number_discrete_energies )
            self.assertEqual( 0, subsection2.NA )
            self.assertEqual( 0, subsection2.number_angular_parameters )
            self.assertEqual( 6, subsection2.NW )
            self.assertEqual( 3, subsection2.NEP )
            self.assertEqual( 3, subsection2.number_secondary_energies )
            self.assertEqual( 3, len( subsection2.energies ) )
            self.assertAlmostEqual( 0., subsection2.energies[0] )
            self.assertAlmostEqual( 1., subsection2.energies[1] )
            self.assertAlmostEqual( 2., subsection2.energies[2] )
            self.assertEqual( 3, len( subsection2.coefficients ) )
            self.assertAlmostEqual( 0., subsection2.coefficients[0][0] )
            self.assertAlmostEqual( 1., subsection2.coefficients[1][0] )
            self.assertAlmostEqual( 0., subsection2.coefficients[2][0] )
            self.assertEqual( 3, len( subsection2.total_emission_probabilities ) )
            self.assertAlmostEqual( 0., subsection2.total_emission_probabilities[0] )
            self.assertAlmostEqual( 1., subsection2.total_emission_probabilities[1] )
            self.assertAlmostEqual( 0., subsection2.total_emission_probabilities[2] )

            # product 1
            product = chunk.reaction_product( 1001 )
            self.assertEqual( 1001, product.ZAP )
            self.assertEqual( 1001, product.product_identifier )

            # product 2
            product = chunk.reaction_product( 1 )
            self.assertEqual( 1, product.ZAP )
            self.assertEqual( 1, product.product_identifier )

            # product 3
            product = chunk.reaction_product( 0 )
            self.assertEqual( 0, product.ZAP )
            self.assertEqual( 0, product.product_identifier )

            self.assertEqual( 30, chunk.NC )

            # verify string
            self.assertEqual( self.chunk + self.valid_SEND,
                              chunk.to_string( 9228, 6 ) )

        # the data is given explicitly
        zaid = 92235
        awr = 2.330248e+2
        jp = 0
        lct = 2
        mt = 5
        products = [
          ReactionProduct( Multiplicity ( 1001, 0.9986234, 0, 1, [ 4 ], [ 2 ],
                                          [ 1e-5, 1.1e+7, 1.147e+7, 2e+7 ],
                                          [ 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 ] ),
                           ContinuumEnergyAngle(
                               2, [ 2 ], [ 1 ],
                               [ LegendreCoefficients(
                                     1e-5, 0, 1,
                                     [ 1., 4., 7., 10. ],
                                     [ [ 2., 3. ], [ 5., 6. ],
                                       [ 8., 9. ], [  11., 12. ] ] ),
                                 LegendreCoefficients(
                                     2e+7, 0, 1, [ 1., 4. ], [ [ 2., 3. ], [ 5., 6. ] ] ) ] ) ),
          ReactionProduct( Multiplicity( 1, 1., 0, 1, [ 2 ], [ 2 ],
                                         [ 1.858639e+7, 2.e+7 ],
                                         [ 4., 4. ] ),
                           ContinuumEnergyAngle(
                               2, [ 2 ], [ 22 ],
                               [ LegendreCoefficients(
                                     1.858639e+7, 0, 0, [ 0., 0.5, 1. ], [ [ 0. ], [ 2. ], [ 0. ] ] ),
                                 LegendreCoefficients(
                                     2e+7, 0, 0, [ 0., 0.5, 1. ], [ [ 0. ], [ 2. ], [ 0. ] ] ) ] ) ),
          ReactionProduct( Multiplicity( 0, 0., 0, 1, [ 3 ], [ 2 ],
                                         [ 1.858639e+7, 1.9e+7, 2.e+7 ],
                                         [ 1., 2., 3. ] ),
                           ContinuumEnergyAngle(
                               2, [ 2 ], [ 5 ],
                               [ LegendreCoefficients(
                                      1.858639e+7, 0, 0, [ 0., 1., 2. ], [ [ 0. ], [ 1. ], [ 0. ] ] ),
                                 LegendreCoefficients(
                                      2e+7, 0, 0, [ 0., 1., 2. ], [ [ 0. ], [ 1. ], [ 0. ] ] ) ] ) ) ]

        chunk = Section( mt = mt, zaid = zaid, awr = awr, jp = jp, lct = lct,
                         products = products )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk + self.valid_SEND )

        verify_chunk( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.material( 9228 ).file( 6 ).section( 5 ).parse()

        verify_chunk( self, chunk )

        # the data is copied
        copy = Section( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # illegal SEND
        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.chunk + self.invalid_SEND )

if __name__ =='__main__' :

    unittest.main()
