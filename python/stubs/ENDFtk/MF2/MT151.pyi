"""
MT151 - resonance parameters
"""
from __future__ import annotations
import pybind11_stubgen.typing_ext
import typing
__all__: list[str] = ['BackgroundChannels', 'BreitWignerLValue', 'FrohnerBackgroundRMatrix', 'Isotope', 'MultiLevelBreitWigner', 'NoBackgroundRMatrix', 'ParticlePairs', 'RMatrixLimited', 'ReichMoore', 'ReichMooreLValue', 'ResonanceChannels', 'ResonanceParameters', 'ResonanceRange', 'SammyBackgroundRMatrix', 'ScatteringRadius', 'Section', 'SingleLevelBreitWigner', 'SpecialCase', 'SpinGroup', 'TabulatedBackgroundRMatrix', 'UnresolvedEnergyDependent', 'UnresolvedEnergyDependentFissionWidths', 'UnresolvedEnergyDependentFissionWidthsJValue', 'UnresolvedEnergyDependentFissionWidthsLValue', 'UnresolvedEnergyDependentJValue', 'UnresolvedEnergyDependentLValue', 'UnresolvedEnergyIndependent', 'UnresolvedEnergyIndependentLValue']
class BackgroundChannels:
    """
    MF2 MT151 section - background R-matrix values for each channel in the
                        spin group
    """
    @typing.overload
    def __init__(self, nch: int, channels: list[NoBackgroundRMatrix | TabulatedBackgroundRMatrix | SammyBackgroundRMatrix | FrohnerBackgroundRMatrix]) -> None:
        """
        Initialise the component
        
        Arguments:
            self        the component
            nch         the total number of channels in the spin group
            channels    the background R-matrix values for each channel
        """
    @typing.overload
    def __init__(self, component: BackgroundChannels) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def KBK(self) -> int:
        """
        The number of channels with background R-matrix values
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NCH(self) -> int:
        """
        The number of channels
        """
    @property
    def background_rmatrices(self) -> ...:
        """
        The complex R-matrix values
        """
    @property
    def number_background_channels(self) -> int:
        """
        The number of channels with background R-matrix values
        """
    @property
    def number_channels(self) -> int:
        """
        The number of channels
        """
class BreitWignerLValue:
    """
    MF2 MT151 section - resonance parameters for a given l value in the SLBW
                        or MLBW representation
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> BreitWignerLValue:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, awri: float, qx: float, l: int, lrx: bool, energies: list[float], spins: list[float], gt: list[float], gn: list[float], gg: list[float], gf: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self        the component
            awri        the atomic weight ratio
            qx          the competitive Q value
            l           the orbital angular momentum value
            lrx         the competitive width flag
            energies    the resonance energies (NRS values)
            spins       the spin values (NRS values)
            gt          the total widths (NRS values)
            gn          the neutron widths (NRS values)
            gg          the gamma widths (NRS values)
            gf          the fission widths (NRS values)
        """
    @typing.overload
    def __init__(self, component: BreitWignerLValue) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def AJ(self) -> ...:
        """
        The spin values
        """
    @property
    def AWRI(self) -> float:
        """
        The atomic weight ratio of the current isotope
        """
    @property
    def ER(self) -> ...:
        """
        The resonance energies
        """
    @property
    def GF(self) -> ...:
        """
        The fission widths
        """
    @property
    def GG(self) -> ...:
        """
        The gamma widths
        """
    @property
    def GN(self) -> ...:
        """
        The neutron widths
        """
    @property
    def GT(self) -> ...:
        """
        The total widths
        """
    @property
    def GX(self) -> ...:
        """
        The competitive widths
        """
    @property
    def L(self) -> int:
        """
        The value of the orbital momentum l
        """
    @property
    def LRX(self) -> bool:
        """
        The competitive width flag
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NRS(self) -> int:
        """
        The number of resonances for this l value
        """
    @property
    def QX(self) -> float:
        """
        The Q value of the competitive reaction
        """
    @property
    def atomic_weight_ratio(self) -> float:
        """
        The atomic weight ratio of the current isotope
        """
    @property
    def competitive_qvalue(self) -> float:
        """
        The Q value of the competitive reaction
        """
    @property
    def competitive_width_flag(self) -> bool:
        """
        The competitive width flag
        """
    @property
    def competitive_widths(self) -> ...:
        """
        The competitive widths
        """
    @property
    def fission_widths(self) -> ...:
        """
        The fission widths
        """
    @property
    def gamma_widths(self) -> ...:
        """
        The gamma widths
        """
    @property
    def neutron_widths(self) -> ...:
        """
        The neutron widths
        """
    @property
    def number_resonances(self) -> int:
        """
        The number of resonances for this l value
        """
    @property
    def orbital_momentum(self) -> int:
        """
        The value of the orbital momentum l
        """
    @property
    def resonance_energies(self) -> ...:
        """
        The resonance energies
        """
    @property
    def spin_values(self) -> ...:
        """
        The spin values
        """
    @property
    def total_widths(self) -> ...:
        """
        The total widths
        """
class FrohnerBackgroundRMatrix:
    """
    MF2 MT151 section - Frohner parametrisation as a channel's background R-matrix
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> FrohnerBackgroundRMatrix:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, index: int, ed: float, eu: float, r0: float, s0: float, ga: float) -> None:
        """
        Initialise the component
        
        Arguments:
            self     the component
            index    the channel index
            ed       the down energy parameter
            eu       the up energy parameter
            r0       the r0 parameter
            s0       the s0 parameter
            ga       the ga parameter
        """
    @typing.overload
    def __init__(self, component: FrohnerBackgroundRMatrix) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def ED(self) -> float:
        """
        The energy down parameter in the SAMMY parametrisation
        """
    @property
    def EU(self) -> float:
        """
        The energy up parameter in the SAMMY parametrisation
        """
    @property
    def GA(self) -> float:
        """
        The GA parameter in the SAMMY parametrisation
        """
    @property
    def LBK(self) -> int:
        """
        The background R-matrix representation
        """
    @property
    def LCH(self) -> int:
        """
        The channel index
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def R0(self) -> float:
        """
        The R0 parameter in the SAMMY parametrisation
        """
    @property
    def S0(self) -> float:
        """
        The S0 parameter in the SAMMY parametrisation
        """
    @property
    def channel_index(self) -> int:
        """
        The channel index
        """
    @property
    def representation(self) -> int:
        """
        The background R-matrix representation
        """
class Isotope:
    """
    MF2 MT151 section - an isotope with resonance energy ranges
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> Isotope:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, zai: int, abn: float, lfw: bool, ranges: list[ResonanceRange]) -> None:
        """
        Initialise the component
        
        Arguments:
            self      the component
            zai       the za of the isotope
            abn       the abundance of the isotope
            lfw       the lfw flag for unresolved resonances
            ranges    the resonance ranges defined for the isotope
        """
    @typing.overload
    def __init__(self, component: Isotope) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def ABN(self) -> float:
        """
        The abundance of the isotope
        """
    @property
    def LFW(self) -> int:
        """
        The average fission flag
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NER(self) -> int:
        """
        The number of resonance ranges for this isotope
        """
    @property
    def ZAI(self) -> int:
        """
        The ZA identifier of the isotope
        """
    @property
    def abundance(self) -> float:
        """
        The abundance of the isotope
        """
    @property
    def average_fission_width_flag(self) -> int:
        """
        The average fission flag
        """
    @property
    def isotope_identifier(self) -> int:
        """
        The ZA identifier of the isotope
        """
    @property
    def number_resonance_ranges(self) -> int:
        """
        The number of resonance ranges for this isotope
        """
    @property
    def resonance_ranges(self) -> ...:
        """
        The resonance ranges for this isotope
        """
class MultiLevelBreitWigner:
    """
    MF2 MT151 section - Multi-level Breit-Wigner resonance parameters
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> MultiLevelBreitWigner:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, spin: float, ap: float, lvalues: list[BreitWignerLValue]) -> None:
        """
        Initialise the component
        
        Arguments:
            self       the component
            spin       the target spin
            ap         the scattering radius
            lvalues    l values and the resonance parameters
        """
    @typing.overload
    def __init__(self, component: MultiLevelBreitWigner) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def AP(self) -> float:
        """
        The scattering radius
        """
    @property
    def LFW(self) -> bool:
        """
        The average fission flag
        """
    @property
    def LRF(self) -> int:
        """
        The resonance representation
        """
    @property
    def LRU(self) -> int:
        """
        The resonance type (resolved or unresolved)
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NLS(self) -> int:
        """
        The number of l values for which resonance parameters are given
        """
    @property
    def SPI(self) -> float:
        """
        The target spin
        """
    @property
    def average_fission_width_flag(self) -> int:
        """
        The average fission flag
        """
    @property
    def l_values(self) -> ...:
        """
        The l values and its resonance parameters
        """
    @property
    def number_l_values(self) -> int:
        """
        The number of l values for which resonance parameters are given
        """
    @property
    def representation(self) -> int:
        """
        The resonance representation
        """
    @property
    def scattering_radius(self) -> float:
        """
        The scattering radius
        """
    @property
    def spin(self) -> float:
        """
        The target spin
        """
    @property
    def type(self) -> int:
        """
        The resonance type (resolved or unresolved)
        """
class NoBackgroundRMatrix:
    """
    MF2 MT151 section - no background is given for the channel
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> NoBackgroundRMatrix:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, index: int) -> None:
        """
        Initialise the component
        
        Arguments:
            self     the component
            index    the channel index
        """
    @typing.overload
    def __init__(self, component: NoBackgroundRMatrix) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def LBK(self) -> int:
        """
        The background R-matrix representation
        """
    @property
    def LCH(self) -> int:
        """
        The channel index
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def channel_index(self) -> int:
        """
        The channel index
        """
    @property
    def representation(self) -> int:
        """
        The background R-matrix representation
        """
class ParticlePairs:
    """
    MF2 MT151 section - particle pair information
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> ParticlePairs:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, ma: list[float], mb: list[float], za: list[float], zb: list[float], ia: list[float], ib: list[float], pa: list[float], pb: list[float], q: list[float], pnt: list[int], shf: list[int], mt: list[int]) -> None:
        """
        Initialise the component
        
        Arguments:
            self    the component
            ma      the mass of the first particle in each particle pair
            mb      the mass of the second particle in each particle pair
            za      the charge of the first particle in each particle pair
            zb      the charge of the second particle in each particle pair
            ia      the spin of the first particle in each particle pair
            ib      the spin of the second particle in each particle pair
            pa      the parity of the first particle in each particle pair
            pb      the parity of the second particle in each particle pair
            q       the Q value for each particle pair
            pnt     the penetrability flag for each particle pair
            shf     the shift factor flag for each particle pair
            mt      the MT value for each particle pair
        """
    @typing.overload
    def __init__(self, component: ParticlePairs) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def IA(self) -> ...:
        """
        The spin of the first particle in each particle pair
        """
    @property
    def IB(self) -> ...:
        """
        The spin of the second particle in each particle pair
        """
    @property
    def MA(self) -> ...:
        """
        The mass of the first particle in each particle pair
        """
    @property
    def MB(self) -> ...:
        """
        The mass of the second particle in each particle pair
        """
    @property
    def MT(self) -> ...:
        """
        The MT value associated to each particle pair
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NPP(self) -> int:
        """
        The number of particle pairs
        """
    @property
    def PA(self) -> ...:
        """
        The parity of the first particle in each particle pair
        """
    @property
    def PB(self) -> ...:
        """
        The parity of the second particle in each particle pair
        """
    @property
    def PNT(self) -> ...:
        """
        The penetrability flag for each particle pair
        """
    @property
    def Q(self) -> ...:
        """
        The Q value for each particle pair
        """
    @property
    def SHF(self) -> ...:
        """
        The shift factor flag for each particle pair
        """
    @property
    def ZA(self) -> ...:
        """
        The charge of the first particle in each particle pair
        """
    @property
    def ZB(self) -> ...:
        """
        The charge of the second particle in each particle pair
        """
    @property
    def charge_particle_A(self) -> ...:
        """
        The charge of the first particle in each particle pair
        """
    @property
    def charge_particle_B(self) -> ...:
        """
        The charge of the second particle in each particle pair
        """
    @property
    def mass_particle_A(self) -> ...:
        """
        The mass of the first particle in each particle pair
        """
    @property
    def mass_particle_B(self) -> ...:
        """
        The mass of the second particle in each particle pair
        """
    @property
    def number_particle_pairs(self) -> int:
        """
        The number of particle pairs
        """
    @property
    def parity_particle_A(self) -> ...:
        """
        The parity of the first particle in each particle pair
        """
    @property
    def parity_particle_B(self) -> ...:
        """
        The parity of the second particle in each particle pair
        """
    @property
    def penetrability_flag(self) -> ...:
        """
        The penetrability flag for each particle pair
        """
    @property
    def shift_factor_flag(self) -> ...:
        """
        The shift factor flag for each particle pair
        """
    @property
    def spin_particle_A(self) -> ...:
        """
        The spin of the first particle in each particle pair
        """
    @property
    def spin_particle_B(self) -> ...:
        """
        The spin of the second particle in each particle pair
        """
class RMatrixLimited:
    """
    MF2 MT151 section - R-matrix limited resonance parameters
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> RMatrixLimited:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, ifg: bool, krl: bool, krm: int, pairs: ParticlePairs, groups: list[SpinGroup]) -> None:
        """
        Initialise the component
        
        Arguments:
            self      the component
            ifg       flag to indicate whether or not the widths are reduced
            krl       the non relativistic kinematics flag
            krm       the resonance formalism to be used
            pairs     the particle pairs
            groups    the spin groups
        """
    @typing.overload
    def __init__(self, component: RMatrixLimited) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def AP(self) -> float:
        """
        The scattering radius
        """
    @property
    def IFG(self) -> bool:
        """
        The flag to indicate whether or not the widths are reduced
        """
    @property
    def KRL(self) -> bool:
        """
        The non relativistic kinematics flag
        """
    @property
    def KRM(self) -> int:
        """
        The resonance formalism to be employed
        """
    @property
    def LFW(self) -> bool:
        """
        The average fission flag
        """
    @property
    def LRF(self) -> int:
        """
        The resonance representation
        """
    @property
    def LRU(self) -> int:
        """
        The resonance type (resolved or unresolved)
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NJS(self) -> int:
        """
        The number of spin groups
        """
    @property
    def SPI(self) -> float:
        """
        The target spin
        """
    @property
    def average_fission_width_flag(self) -> int:
        """
        The average fission flag
        """
    @property
    def formalism(self) -> int:
        """
        The resonance formalism to be employed
        """
    @property
    def non_relativistic_kinematics(self) -> bool:
        """
        The non relativistic kinematics flag
        """
    @property
    def number_spin_groups(self) -> int:
        """
        The number of spin groups
        """
    @property
    def particle_pairs(self) -> ParticlePairs:
        """
        The particle pair information
        """
    @property
    def reduced_widths(self) -> bool:
        """
        The flag to indicate whether or not the widths are reduced
        """
    @property
    def representation(self) -> int:
        """
        The resonance representation
        """
    @property
    def scattering_radius(self) -> float:
        """
        The scattering radius
        """
    @property
    def spin(self) -> float:
        """
        The target spin
        """
    @property
    def spin_groups(self) -> ...:
        """
        The spin groups
        """
    @property
    def type(self) -> int:
        """
        The resonance type (resolved or unresolved)
        """
class ReichMoore:
    """
    MF2 MT151 section - Reich-Moore resonance parameters
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> ReichMoore:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, spin: float, ap: float, lad: bool, nlsc: int, lvalues: list[ReichMooreLValue]) -> None:
        """
        Initialise the component
        
        Arguments:
            self       the component
            spin       the target spin
            ap         the scattering radius
            lad        the angular distributions flag
            nlsc       the number of l values for convergence
            lvalues    l values and the resonance parameters
        """
    @typing.overload
    def __init__(self, component: ReichMoore) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def AP(self) -> float:
        """
        The scattering radius
        """
    @property
    def LAD(self) -> bool:
        """
        The angular distribution flag
        """
    @property
    def LFW(self) -> bool:
        """
        The average fission flag
        """
    @property
    def LRF(self) -> int:
        """
        The resonance representation
        """
    @property
    def LRU(self) -> int:
        """
        The resonance type (resolved or unresolved)
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NLS(self) -> int:
        """
        The number of l values for which resonance parameters are given
        """
    @property
    def NLSC(self) -> int:
        """
        The number of l values required for convergence of angular distributions
        """
    @property
    def SPI(self) -> float:
        """
        The target spin
        """
    @property
    def angular_distributions_flag(self) -> bool:
        """
        The angular distribution flag
        """
    @property
    def average_fission_width_flag(self) -> int:
        """
        The average fission flag
        """
    @property
    def l_values(self) -> ...:
        """
        The l values and its resonance parameters
        """
    @property
    def number_l_values(self) -> int:
        """
        The number of l values for which resonance parameters are given
        """
    @property
    def number_l_values_for_distributions(self) -> int:
        """
        The number of l values required for convergence of angular distributions
        """
    @property
    def representation(self) -> int:
        """
        The resonance representation
        """
    @property
    def scattering_radius(self) -> float:
        """
        The scattering radius
        """
    @property
    def spin(self) -> float:
        """
        The target spin
        """
    @property
    def type(self) -> int:
        """
        The resonance type (resolved or unresolved)
        """
class ReichMooreLValue:
    """
    MF2 MT151 section - resonance parameters for a given l value in the
                        Reich-Moore representation
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> ReichMooreLValue:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, awri: float, apl: float, l: int, energies: list[float], spins: list[float], gn: list[float], gg: list[float], gfa: list[float], gfb: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self        the component
            awri        the atomic weight ratio
            apl         the l dependent scattering radius
            l           the orbital angular momentum value
            energies    the resonance energies (NRS values)
            spins       the spin values (NRS values)
            gn          the neutron widths (NRS values)
            gg          the gamma widths (NRS values)
            gfa         the first fission widths (NRS values)
            gfb         the second fission widths (NRS values)
        """
    @typing.overload
    def __init__(self, component: ReichMooreLValue) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def AJ(self) -> ...:
        """
        The spin values
        """
    @property
    def APL(self) -> float:
        """
        The l dependent scattering radius
        """
    @property
    def AWRI(self) -> float:
        """
        The atomic weight ratio of the current isotope
        """
    @property
    def ER(self) -> ...:
        """
        The resonance energies
        """
    @property
    def GFA(self) -> ...:
        """
        The first fission widths
        """
    @property
    def GFB(self) -> ...:
        """
        The second fission widths
        """
    @property
    def GG(self) -> ...:
        """
        The gamma widths
        """
    @property
    def GN(self) -> ...:
        """
        The neutron widths
        """
    @property
    def L(self) -> int:
        """
        The value of the orbital momentum l
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NRS(self) -> int:
        """
        The number of resonances for this l value
        """
    @property
    def atomic_weight_ratio(self) -> float:
        """
        The atomic weight ratio of the current isotope
        """
    @property
    def first_fission_widths(self) -> ...:
        """
        The first fission widths
        """
    @property
    def gamma_widths(self) -> ...:
        """
        The gamma widths
        """
    @property
    def l_dependent_scattering_radius(self) -> float:
        """
        The l dependent scattering radius
        """
    @property
    def neutron_widths(self) -> ...:
        """
        The neutron widths
        """
    @property
    def number_resonances(self) -> int:
        """
        The number of resonances for this l value
        """
    @property
    def orbital_momentum(self) -> int:
        """
        The value of the orbital momentum l
        """
    @property
    def resonance_energies(self) -> ...:
        """
        The resonance energies
        """
    @property
    def second_fission_widths(self) -> ...:
        """
        The second fission widths
        """
    @property
    def spin_values(self) -> ...:
        """
        The spin values
        """
class ResonanceChannels:
    """
    MF2 MT151 section - resonance channel information for a spin group
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> ResonanceChannels:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, spin: float, parity: float, ppi: list[int], l: list[int], s: list[float], b: list[float], apt: list[float], ape: list[float], kbk: int = 0, kps: int = 0) -> None:
        """
        Initialise the component
        
        Arguments:
            self      the component
            spin      the spin group's spin value
            parity    the associated parity
            l         the orbital momentum values (NCH values)
            s         the channel spin values (NCH values)
            b         the boundary condition values (NCH values)
            apt       the true scattering radius values for the calculation
                      of the penetrability and the shift factor (NCH values)
            ape       the true scattering radius values for the calculation
                      of the phase shift (NCH values)
            kbk       the number of channels with a background R-matrix
            kps       the phase shift option
        """
    @typing.overload
    def __init__(self, spin: float, parity: float, ppi: list[int], l: list[int], s: list[float], b: list[float], ap: list[float], kbk: int = 0, kps: int = 0) -> None:
        """
        Initialise the component
        
        Arguments:
            self      the component
            spin      the spin group's spin value
            parity    the associated parity
            l         the orbital momentum values (NCH values)
            s         the channel spin values (NCH values)
            b         the boundary condition values (NCH values)
            ap        the scattering radius values (NCH values)
            kbk       the number of channels with a background R-matrix
            kps       the phase shift option
        """
    @typing.overload
    def __init__(self, component: ResonanceChannels) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def AJ(self) -> float:
        """
        The spin J of the spin group
        """
    @property
    def APE(self) -> ...:
        """
        The effective channel radii (used in the calculation of the phase shift)
        """
    @property
    def APT(self) -> ...:
        """
        The true channel radii (used in the calculation of the penetrability and
        shift factor)
        """
    @property
    def BND(self) -> ...:
        """
        The boundary condition values
        """
    @property
    def KBK(self) -> int:
        """
        The number of channels with background R-matrix values
        """
    @property
    def KPS(self) -> int:
        """
        The phase shift option
        """
    @property
    def L(self) -> ...:
        """
        The orbital momentum values for all channels
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NCH(self) -> int:
        """
        The number of channels
        """
    @property
    def PJ(self) -> float:
        """
        The parity of the spin group
        """
    @property
    def PPI(self) -> ...:
        """
        The particle pair numbers of each channel
        """
    @property
    def SCH(self) -> ...:
        """
        The channel spin values
        """
    @property
    def boundary_condition_values(self) -> ...:
        """
        The boundary condition values
        """
    @property
    def channel_spin_values(self) -> ...:
        """
        The channel spin values
        """
    @property
    def effective_channel_radii(self) -> ...:
        """
        The effective channel radii (used in the calculation of the phase shift)
        """
    @property
    def number_background_channels(self) -> int:
        """
        The number of channels with background R-matrix values
        """
    @property
    def number_channels(self) -> int:
        """
        The number of channels
        """
    @property
    def orbital_momentum_values(self) -> ...:
        """
        The orbital momentum values for all channels
        """
    @property
    def parity(self) -> float:
        """
        The parity of the spin group
        """
    @property
    def particle_pair_numbers(self) -> ...:
        """
        The particle pair numbers of each channel
        """
    @property
    def phase_shift_option(self) -> int:
        """
        The phase shift option
        """
    @property
    def spin(self) -> float:
        """
        The spin J of the spin group
        """
    @property
    def true_channel_radii(self) -> ...:
        """
        The true channel radii (used in the calculation of the penetrability and
        shift factor)
        """
class ResonanceParameters:
    """
    MF2 MT151 section - resonance parameters for a spin group
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> ResonanceParameters:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, energies: list[float], parameters: list[list[float]]) -> None:
        """
        Initialise the component
        
        Arguments:
            self          the component
            energies      the resonance energies (NRS values)
            parameters    the resonance parameters (NRS times NCH values)
        """
    @typing.overload
    def __init__(self, component: ResonanceParameters) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def ER(self) -> ...:
        """
        The resonance energies
        """
    @property
    def GAM(self) -> ...:
        """
        The resonance parameters
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NRS(self) -> int:
        """
        The number of resonances
        """
    @property
    def NX(self) -> int:
        """
        The number of lines for all parameters
        """
    @property
    def number_lines(self) -> int:
        """
        The number of lines for all parameters
        """
    @property
    def number_resonances(self) -> int:
        """
        The number of resonances
        """
    @property
    def resonance_energies(self) -> ...:
        """
        The resonance energies
        """
    @property
    def resonance_parameters(self) -> ...:
        """
        The resonance parameters
        """
class ResonanceRange:
    """
    MF2 MT151 section - a resonance energy range with parameters
    """
    def __init__(self, el: float, eh: float, naps: int, parameters: SpecialCase | SingleLevelBreitWigner | MultiLevelBreitWigner | ReichMoore | RMatrixLimited | UnresolvedEnergyIndependent | UnresolvedEnergyDependentFissionWidths | UnresolvedEnergyDependent, scattering_radius: ScatteringRadius | None = None) -> None:
        """
        Initialise the component
        
        Arguments:
            self                 the component
            el                   the lower energy of the resonance region
            eh                   the upper energy of the resonance region
            naps                 the flag to indicate then on how to calculate
                                 the scattering radius (0 or 1 if no energy
                                 dependent scattering radius is given and 0, 1
                                 or 2 if energy dependent scattering radius is
                                 given)
            parameters           the resonance parameters
            scattering_radius    An optional energy dependent scattering radius
        """
    @property
    def EH(self) -> float:
        """
        The upper energy boundary of the resonance region
        """
    @property
    def EL(self) -> float:
        """
        The lower energy boundary of the resonance region
        """
    @property
    def LFW(self) -> bool:
        """
        The average fission flag
        """
    @property
    def LRF(self) -> int:
        """
        The resonance representation
        """
    @property
    def LRU(self) -> int:
        """
        The resonance type (resolved or unresolved)
        """
    @property
    def NAPS(self) -> int:
        """
        The scattering radius calculation option flag
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NRO(self) -> bool:
        """
        Flag to indicate whether the scattering radius is energy dependent or not
        """
    @property
    def average_fission_width_flag(self) -> bool:
        """
        The average fission flag
        """
    @property
    def energy_dependent_scattering_radius(self) -> bool:
        """
        Flag to indicate whether the scattering radius is energy dependent or not
        """
    @property
    def lower_energy(self) -> float:
        """
        The lower energy boundary of the resonance region
        """
    @property
    def parameters(self) -> SpecialCase | SingleLevelBreitWigner | MultiLevelBreitWigner | ReichMoore | RMatrixLimited | UnresolvedEnergyIndependent | UnresolvedEnergyDependentFissionWidths | UnresolvedEnergyDependent:
        """
        The resonance parameters
        """
    @property
    def representation(self) -> int:
        """
        The resonance representation
        """
    @property
    def scattering_radius(self) -> ScatteringRadius | None:
        """
        The optional scattering radius
        """
    @property
    def scattering_radius_calculation_option(self) -> int:
        """
        The scattering radius calculation option flag
        """
    @property
    def type(self) -> int:
        """
        The resonance type (resolved or unresolved)
        """
    @property
    def upper_energy(self) -> float:
        """
        The upper energy boundary of the resonance region
        """
class SammyBackgroundRMatrix:
    """
    MF2 MT151 section - SAMMY parametrisation as a channel's background R-matrix
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> SammyBackgroundRMatrix:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, index: int, ed: float, eu: float, r0: float, r1: float, r2: float, s0: float, s1: float) -> None:
        """
        Initialise the component
        
        Arguments:
            self     the component
            index    the channel index
            ed       the down energy parameter
            eu       the up energy parameter
            r0       the r0 parameter
            r1       the r1 parameter
            r2       the r2 parameter
            s0       the s0 parameter
            s1       the s1 parameter
        """
    @typing.overload
    def __init__(self, component: SammyBackgroundRMatrix) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def ED(self) -> float:
        """
        The energy down parameter in the SAMMY parametrisation
        """
    @property
    def EU(self) -> float:
        """
        The energy up parameter in the SAMMY parametrisation
        """
    @property
    def LBK(self) -> int:
        """
        The background R-matrix representation
        """
    @property
    def LCH(self) -> int:
        """
        The channel index
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def R0(self) -> float:
        """
        The R0 parameter in the SAMMY parametrisation
        """
    @property
    def R1(self) -> float:
        """
        The R1 parameter in the SAMMY parametrisation
        """
    @property
    def R2(self) -> float:
        """
        The R2 parameter in the SAMMY parametrisation
        """
    @property
    def S0(self) -> float:
        """
        The S0 parameter in the SAMMY parametrisation
        """
    @property
    def S1(self) -> float:
        """
        The S1 parameter in the SAMMY parametrisation
        """
    @property
    def channel_index(self) -> int:
        """
        The channel index
        """
    @property
    def representation(self) -> int:
        """
        The background R-matrix representation
        """
class ScatteringRadius:
    """
    MF2 MT151 section - an energy dependent scattering radius function
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> ScatteringRadius:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, boundaries: list[int], interpolants: list[int], energies: list[float], radii: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self            the component
            boundaries      the interpolation range boundaries
            interpolants    the interpolation types for each range
            energies        the energy values
            radii           the scattering radii (in 10^-12 cm)
        """
    @typing.overload
    def __init__(self, component: ScatteringRadius) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def AP(self) -> ...:
        """
        The scattering radius values
        """
    @property
    def E(self) -> ...:
        """
        The energy values
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def NBT(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NP(self) -> int:
        """
        The number of points
        """
    @property
    def NR(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def energies(self) -> ...:
        """
        The energy values
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def number_points(self) -> int:
        """
        The number of points
        """
    @property
    def radii(self) -> ...:
        """
        The scattering radius values
        """
class Section:
    """
    MF2 MT151 section - resonance parameters
    """
    @staticmethod
    def from_string(section: str) -> Section:
        """
        Read the section from a string
        
        An exception is raised if something goes wrong while reading the
        section
        
        Arguments:
            section    the string representing the section
        """
    @typing.overload
    def __init__(self, zaid: int, awr: float, isotopes: list[Isotope]) -> None:
        """
        Initialise the section using isotopes
        
        Arguments:
            self        the section
            zaid        the ZA value of the material
            awr         the atomic weight ratio
            isotopes    the isotopes for the section
        """
    @typing.overload
    def __init__(self, zaid: int, awr: float, lfw: bool, ranges: list[ResonanceRange]) -> None:
        """
        Initialise the section using a single isotope
        
        Arguments:
            self      the section
            zaid      the ZA value of the material
            awr       the atomic weight ratio
            lfw       the lfw flag for unresolved resonances
            ranges    the resonance ranges defined for the isotope
        """
    @typing.overload
    def __init__(self, zaid: int, awr: float, el: float, eh: float, spin: float, ap: float) -> None:
        """
        Initialise the section for the special case (only scattering radius is
        given)
        
        Arguments:
            self    the section
            zaid    the ZA value of the material
            awr     the atomic weight ratio
            el      the lower limit of the resonance range
            eh      the upper limit of the resonance range
            spin    the spin of the target nucleus
            ap      the scattering radius (in units of 10^-12 cm)
        """
    @typing.overload
    def __init__(self, section: Section) -> None:
        """
        Initialise the section with another section
        
        Arguments:
            self       the section
            section    the section to be copied
        """
    def to_string(self, mat: int, mf: int) -> str:
        """
        Return the string representation of the section
        
        Arguments:
            self    the section
            mat     the MAT number to be used
            mf      the MF number to be used
        """
    def to_tree(self, mat: int) -> ...:
        """
        Return the ENDF tree representation of the section
        
        Arguments:
            self    the section
            mat     the MAT number to be used
        """
    @property
    def AWR(self) -> float:
        """
        The atomic weight ratio for the section
        """
    @property
    def MT(self) -> int:
        """
        The MT number of the section
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this section
        """
    @property
    def NIS(self) -> int:
        """
        The number of isotopes
        """
    @property
    def ZA(self) -> int:
        """
        The ZA identifier for the section
        """
    @property
    def atomic_weight_ratio(self) -> float:
        """
        The atomic weight ratio for the section
        """
    @property
    def isotopes(self) -> ...:
        """
        The isotopes defined in the section
        """
    @property
    def number_isotopes(self) -> int:
        """
        The number of isotopes
        """
    @property
    def section_number(self) -> int:
        """
        The MT number of the section
        """
    @property
    def target_identifier(self) -> int:
        """
        The ZA identifier for the section
        """
class SingleLevelBreitWigner:
    """
    MF2 MT151 section - Single level Breit-Wigner resonance parameters
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> SingleLevelBreitWigner:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, spin: float, ap: float, lvalues: list[BreitWignerLValue]) -> None:
        """
        Initialise the component
        
        Arguments:
            self       the component
            spin       the target spin
            ap         the scattering radius
            lvalues    l values and the resonance parameters
        """
    @typing.overload
    def __init__(self, component: SingleLevelBreitWigner) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def AP(self) -> float:
        """
        The scattering radius
        """
    @property
    def LFW(self) -> bool:
        """
        The average fission flag
        """
    @property
    def LRF(self) -> int:
        """
        The resonance representation
        """
    @property
    def LRU(self) -> int:
        """
        The resonance type (resolved or unresolved)
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NLS(self) -> int:
        """
        The number of l values for which resonance parameters are given
        """
    @property
    def SPI(self) -> float:
        """
        The target spin
        """
    @property
    def average_fission_width_flag(self) -> int:
        """
        The average fission flag
        """
    @property
    def l_values(self) -> ...:
        """
        The l values and its resonance parameters
        """
    @property
    def number_l_values(self) -> int:
        """
        The number of l values for which resonance parameters are given
        """
    @property
    def representation(self) -> int:
        """
        The resonance representation
        """
    @property
    def scattering_radius(self) -> float:
        """
        The scattering radius
        """
    @property
    def spin(self) -> float:
        """
        The target spin
        """
    @property
    def type(self) -> int:
        """
        The resonance type (resolved or unresolved)
        """
class SpecialCase:
    """
    MF2 MT151 section - special case: no parameters are given (LRU=0, LRF=0)
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> SpecialCase:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, spin: float, ap: float) -> None:
        """
        Initialise the component
        
        Arguments:
            self    the component
            spin    the target spin
            ap      the scattering radius
        """
    @typing.overload
    def __init__(self, component: SpecialCase) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def AP(self) -> float:
        """
        The scattering radius
        """
    @property
    def LFW(self) -> bool:
        """
        The average fission flag
        """
    @property
    def LRF(self) -> int:
        """
        The resonance representation
        """
    @property
    def LRU(self) -> int:
        """
        The resonance type (resolved or unresolved)
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def SPI(self) -> float:
        """
        The target spin
        """
    @property
    def average_fission_width_flag(self) -> bool:
        """
        The average fission flag
        """
    @property
    def representation(self) -> int:
        """
        The resonance representation
        """
    @property
    def scattering_radius(self) -> float:
        """
        The scattering radius
        """
    @property
    def spin(self) -> float:
        """
        The target spin
        """
    @property
    def type(self) -> int:
        """
        The resonance type (resolved or unresolved)
        """
class SpinGroup:
    """
    MF2 MT151 section - R-matrix limited spin group with resonance parameters
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> SpinGroup:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, channels: ResonanceChannels, parameters: ResonanceParameters) -> None:
        """
        Initialise the component
        
        Arguments:
            self          the component
            channels      the resonance channel information
            parameters    the associated resonance parameters
        """
    @typing.overload
    def __init__(self, channels: ResonanceChannels, parameters: ResonanceParameters, background: BackgroundChannels) -> None:
        """
        Initialise the component
        
        Arguments:
            self          the component
            channels      the resonance channel information
            parameters    the associated resonance parameters
            background    the background R-matrices
        """
    @typing.overload
    def __init__(self, component: SpinGroup) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def AJ(self) -> float:
        """
        The spin J of the spin group
        """
    @property
    def KBK(self) -> int:
        """
        The number of channels with background R-matrix values
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NCH(self) -> int:
        """
        The number of channels
        """
    @property
    def NRS(self) -> int:
        """
        The number of resonances
        """
    @property
    def PJ(self) -> float:
        """
        The parity of the spin group
        """
    @property
    def background(self) -> BackgroundChannels:
        """
        The background R-matrix values for the spin group channels
        """
    @property
    def channels(self) -> ResonanceChannels:
        """
        The channel information
        """
    @property
    def number_background_channels(self) -> int:
        """
        The number of channels with background R-matrix values
        """
    @property
    def number_channels(self) -> int:
        """
        The number of channels
        """
    @property
    def number_resonances(self) -> int:
        """
        The number of resonances
        """
    @property
    def parameters(self) -> ResonanceParameters:
        """
        The resonance parameters for this spin group
        """
    @property
    def parity(self) -> float:
        """
        The parity of the spin group
        """
    @property
    def spin(self) -> float:
        """
        The spin J of the spin group
        """
class TabulatedBackgroundRMatrix:
    """
    MF2 MT151 section - tabulated complex function as a channel's background
                        R-matrix
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> TabulatedBackgroundRMatrix:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, index: int, boundaries: list[int], interpolants: list[int], energies: list[float], real: list[float], imaginary: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self            the component
            index           the channel index
            boundaries      the interpolation range boundaries
            interpolants    the interpolation types for each range
            energies        the energy values
            real            the real values of the tabulated rmatrix
            imaginary       the imaginary values of the tabulated rmatrix
        """
    @typing.overload
    def __init__(self, index: int, boundaries: list[int], interpolants: list[int], energies: list[float], rmatrix: list[complex]) -> None:
        """
        Initialise the component
        
        Arguments:
            self            the component
            index           the channel index
            boundaries      the interpolation range boundaries
            interpolants    the interpolation types for each range
            energies        the energy values
            rmatrix         the complex tabulated rmatrix values
        """
    @typing.overload
    def __init__(self, component: TabulatedBackgroundRMatrix) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def E(self) -> ...:
        """
        The energy values
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def LBK(self) -> int:
        """
        The background R-matrix representation
        """
    @property
    def LCH(self) -> int:
        """
        The channel index
        """
    @property
    def NBT(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NP(self) -> int:
        """
        The number of points
        """
    @property
    def NR(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def RB(self) -> ...:
        """
        The complex R-matrix values
        """
    @property
    def RBI(self) -> ...:
        """
        The imaginary component of the R-matrix values
        """
    @property
    def RBR(self) -> ...:
        """
        The real component of the R-matrix values
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def channel_index(self) -> int:
        """
        The channel index
        """
    @property
    def energies(self) -> ...:
        """
        The energy values
        """
    @property
    def imaginary(self) -> ...:
        """
        The imaginary component of the R-matrix values
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def number_points(self) -> int:
        """
        The number of points
        """
    @property
    def real(self) -> ...:
        """
        The real component of the R-matrix values
        """
    @property
    def representation(self) -> int:
        """
        The background R-matrix representation
        """
    @property
    def rmatrix(self) -> ...:
        """
        The complex R-matrix values
        """
class UnresolvedEnergyDependent:
    """
    MF2 MT151 section - unresolved resonance parameters with energy
                        dependent widths
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> UnresolvedEnergyDependent:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, spin: float, ap: float, lssf: bool, lvalues: list[UnresolvedEnergyDependentLValue]) -> None:
        """
        Initialise the component
        
        Arguments:
            self       the component
            spin       the target spin
            ap         the scattering radius
            lssf        the self-shielding only flag
            lvalues    l values and the resonance parameters
        """
    @typing.overload
    def __init__(self, component: UnresolvedEnergyDependent) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def AP(self) -> float:
        """
        The scattering radius
        """
    @property
    def LFW(self) -> bool:
        """
        The average fission flag
        """
    @property
    def LRF(self) -> int:
        """
        The resonance representation
        """
    @property
    def LRU(self) -> int:
        """
        The resonance type (resolved or unresolved)
        """
    @property
    def LSSF(self) -> bool:
        """
        The self-shielding only flag
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NLS(self) -> int:
        """
        The number of l values for which resonance parameters are given
        """
    @property
    def SPI(self) -> float:
        """
        The target spin
        """
    @property
    def average_fission_width_flag(self) -> bool:
        """
        The average fission flag
        """
    @property
    def l_values(self) -> ...:
        """
        The l values and its resonance parameters
        """
    @property
    def number_l_values(self) -> int:
        """
        The number of l values for which resonance parameters are given
        """
    @property
    def representation(self) -> int:
        """
        The resonance representation
        """
    @property
    def scattering_radius(self) -> float:
        """
        The scattering radius
        """
    @property
    def self_shielding_only(self) -> bool:
        """
        The self-shielding only flag
        """
    @property
    def spin(self) -> float:
        """
        The target spin
        """
    @property
    def type(self) -> int:
        """
        The resonance type (resolved or unresolved)
        """
class UnresolvedEnergyDependentFissionWidths:
    """
    MF2 MT151 section - unresolved resonance parameters with energy
                        dependent fission widths
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> UnresolvedEnergyDependentFissionWidths:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, spin: float, ap: float, lssf: bool, energies: list[float], lvalues: list[UnresolvedEnergyDependentFissionWidthsLValue]) -> None:
        """
        Initialise the component
        
        Arguments:
            self        the component
            spin        the target spin
            ap          the scattering radius
            lssf        the self-shielding only flag
            energies    the energy values for which fission widths are given
            lvalues     l values and the resonance parameters
        """
    @typing.overload
    def __init__(self, component: UnresolvedEnergyDependentFissionWidths) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def AP(self) -> float:
        """
        The scattering radius
        """
    @property
    def ES(self) -> ...:
        """
        The energy values
        """
    @property
    def LFW(self) -> bool:
        """
        The average fission flag
        """
    @property
    def LRF(self) -> int:
        """
        The resonance representation
        """
    @property
    def LRU(self) -> int:
        """
        The resonance type (resolved or unresolved)
        """
    @property
    def LSSF(self) -> bool:
        """
        The self-shielding only flag
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NE(self) -> int:
        """
        The number of average fission width points
        """
    @property
    def NLS(self) -> int:
        """
        The number of l values for which resonance parameters are given
        """
    @property
    def SPI(self) -> float:
        """
        The target spin
        """
    @property
    def average_fission_width_flag(self) -> int:
        """
        The average fission flag
        """
    @property
    def energies(self) -> ...:
        """
        The energy values
        """
    @property
    def l_values(self) -> ...:
        """
        The l values and its resonance parameters
        """
    @property
    def number_l_values(self) -> int:
        """
        The number of l values for which resonance parameters are given
        """
    @property
    def representation(self) -> int:
        """
        The resonance representation
        """
    @property
    def scattering_radius(self) -> float:
        """
        The scattering radius
        """
    @property
    def self_shielding_only(self) -> bool:
        """
        The self-shielding only flag
        """
    @property
    def spin(self) -> float:
        """
        The target spin
        """
    @property
    def type(self) -> int:
        """
        The resonance type (resolved or unresolved)
        """
class UnresolvedEnergyDependentFissionWidthsJValue:
    """
    MF2 MT151 section - Unresolved resonance data associated to a given
                        J value when only the fission width is energy dependent
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> UnresolvedEnergyDependentFissionWidthsJValue:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, l: int, spin: float, d: float, amun: int, amuf: int, gn: float, gg: float, gf: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self    the component
            l       the orbital angular momentum value
            spin    the spin
            d       the level spacing
            amun    the degrees of freedom for the neutron width
            amuf    the degrees of freedom for the fission width
            gn      the average neutron width
            gg      the average gamma width
            gf      the average fission widths
        """
    @typing.overload
    def __init__(self, component: UnresolvedEnergyDependentFissionWidthsJValue) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def AJ(self) -> float:
        """
        The spin value
        """
    @property
    def AMUF(self) -> int:
        """
        The degrees of freedom for the fission width
        """
    @property
    def AMUG(self) -> int:
        """
        The degrees of freedom for the gamma width
        """
    @property
    def AMUN(self) -> float:
        """
        The degrees of freedom for the neutron width
        """
    @property
    def AMUX(self) -> int:
        """
        The degrees of freedom for the competitive width
        """
    @property
    def D(self) -> float:
        """
        The average level spacing
        """
    @property
    def GF(self) -> ...:
        """
        The average fission widths (energy dependent)
        """
    @property
    def GG(self) -> float:
        """
        The average gamma width
        """
    @property
    def GN(self) -> float:
        """
        The average neutron width
        """
    @property
    def GX(self) -> float:
        """
        The average competitive width
        """
    @property
    def L(self) -> int:
        """
        The value of the orbital momentum l
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NE(self) -> int:
        """
        The number of average fission width points
        """
    @property
    def NR(self) -> int:
        """
        The number of interpolation ranges
        """
    @property
    def average_competitive_width(self) -> float:
        """
        The average competitive width
        """
    @property
    def average_fission_widths(self) -> ...:
        """
        The average fission widths (energy dependent)
        """
    @property
    def average_gamma_width(self) -> float:
        """
        The average gamma width
        """
    @property
    def average_level_spacing(self) -> float:
        """
        The average level spacing
        """
    @property
    def average_neutron_width(self) -> float:
        """
        The average neutron width
        """
    @property
    def boundaries(self) -> typing.Annotated[list[int], pybind11_stubgen.typing_ext.FixedSize(1)]:
        """
        The interpolation range boundaries
        """
    @property
    def competitive_width_degrees_freedom(self) -> int:
        """
        The degrees of freedom for the competitive width
        """
    @property
    def fission_width_degrees_freedom(self) -> int:
        """
        The degrees of freedom for the fission width
        """
    @property
    def gamma_width_degrees_freedom(self) -> int:
        """
        The degrees of freedom for the gamma width
        """
    @property
    def interpolants(self) -> typing.Annotated[list[int], pybind11_stubgen.typing_ext.FixedSize(1)]:
        """
        The interpolants
        """
    @property
    def neutron_width_degrees_freedom(self) -> int:
        """
        The degrees of freedom for the neutron width
        """
    @property
    def orbital_momentum(self) -> int:
        """
        The value of the orbital momentum l
        """
    @property
    def spin(self) -> float:
        """
        The spin value
        """
class UnresolvedEnergyDependentFissionWidthsLValue:
    """
    MF2 MT151 section - unresolved resonance parameters for a given l value
                        for energy dependent fission widths
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> UnresolvedEnergyDependentFissionWidthsLValue:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, awri: float, l: int, jvalues: list[UnresolvedEnergyDependentFissionWidthsJValue]) -> None:
        """
        Initialise the component
        
        Arguments:
            self       the component
            awri       the atomic weight ratio
            l          the orbital angular momentum value
            jvalues    the unresolved resonance parameters for every J value
                       (NJS elements)
        """
    @typing.overload
    def __init__(self, component: UnresolvedEnergyDependentFissionWidthsLValue) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def AWRI(self) -> float:
        """
        The atomic weight ratio of the current isotope
        """
    @property
    def L(self) -> int:
        """
        The value of the orbital momentum l
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NJS(self) -> int:
        """
        The number of J values for this l value
        """
    @property
    def atomic_weight_ratio(self) -> float:
        """
        The atomic weight ratio of the current isotope
        """
    @property
    def j_values(self) -> ...:
        """
        The data for each of the J values
        """
    @property
    def number_spin_values(self) -> int:
        """
        The number of J values for this l value
        """
    @property
    def orbital_momentum(self) -> int:
        """
        The value of the orbital momentum l
        """
class UnresolvedEnergyDependentJValue:
    """
    MF2 MT151 section - unresolved resonance data associated to a given J value
                        with fully energy dependent widths (this is the most
                        general case for unresolved resonances)
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> UnresolvedEnergyDependentJValue:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, spin: float, amun: int, amug: int, amuf: int, amux: int, interpolation: int, energies: list[float], d: list[float], gn: list[float], gg: list[float], gf: list[float], gx: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self             the component
            spin             the spin
            amun             the degrees of freedom for the neutron width
            amug             the degrees of freedom for the gamma width
            amuf             the degrees of freedom for the fission width
            amux             the degrees of freedom for the competitive width
            interpolation    the interpolation scheme for the cross sections
            energies         the energy values (NE values)
            d                the level spacings (NE values)
            gn               the average neutron widths (NE values)
            gg               the average gamma widths (NE values)
            gf               the average fission widths (NE values)
            gx               the average competitive widths (NE values)
        """
    @typing.overload
    def __init__(self, component: UnresolvedEnergyDependentJValue) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def AJ(self) -> float:
        """
        The spin value
        """
    @property
    def AMUF(self) -> int:
        """
        The degrees of freedom for the fission width
        """
    @property
    def AMUG(self) -> int:
        """
        The degrees of freedom for the gamma width
        """
    @property
    def AMUN(self) -> int:
        """
        The degrees of freedom for the neutron width
        """
    @property
    def AMUX(self) -> int:
        """
        The degrees of freedom for the competitive width
        """
    @property
    def D(self) -> ...:
        """
        The average level spacing values
        """
    @property
    def ES(self) -> ...:
        """
        The energy values
        """
    @property
    def GF(self) -> ...:
        """
        The average fission widths
        """
    @property
    def GG(self) -> ...:
        """
        The average gamma widths
        """
    @property
    def GN(self) -> ...:
        """
        The average neutron widths
        """
    @property
    def GX(self) -> ...:
        """
        The average competitive widths
        """
    @property
    def INT(self) -> int:
        """
        The interpolation type
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NE(self) -> int:
        """
        The number of energy points
        """
    @property
    def NR(self) -> int:
        """
        The number of interpolation ranges
        """
    @property
    def average_competitive_widths(self) -> ...:
        """
        The average competitive widths
        """
    @property
    def average_fission_widths(self) -> ...:
        """
        The average fission widths
        """
    @property
    def average_gamma_widths(self) -> ...:
        """
        The average gamma widths
        """
    @property
    def average_level_spacings(self) -> ...:
        """
        The average level spacing values
        """
    @property
    def average_neutron_widths(self) -> ...:
        """
        The average neutron widths
        """
    @property
    def boundaries(self) -> typing.Annotated[list[int], pybind11_stubgen.typing_ext.FixedSize(1)]:
        """
        The interpolation range boundaries
        """
    @property
    def competitive_width_degrees_freedom(self) -> int:
        """
        The degrees of freedom for the competitive width
        """
    @property
    def energies(self) -> ...:
        """
        The energy values
        """
    @property
    def fission_width_degrees_freedom(self) -> int:
        """
        The degrees of freedom for the fission width
        """
    @property
    def gamma_width_degrees_freedom(self) -> int:
        """
        The degrees of freedom for the gamma width
        """
    @property
    def interpolants(self) -> typing.Annotated[list[int], pybind11_stubgen.typing_ext.FixedSize(1)]:
        """
        The interpolants
        """
    @property
    def neutron_width_degrees_freedom(self) -> int:
        """
        The degrees of freedom for the neutron width
        """
    @property
    def spin(self) -> float:
        """
        The spin value
        """
class UnresolvedEnergyDependentLValue:
    """
    MF2 MT151 section - unresolved resonance parameters for a given l value
                        for energy dependent widths
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> UnresolvedEnergyDependentLValue:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, awri: float, l: int, jvalues: list[UnresolvedEnergyDependentJValue]) -> None:
        """
        Initialise the component
        
        Arguments:
            self       the component
            awri       the atomic weight ratio
            l          the orbital angular momentum value
            jvalues    the unresolved resonance parameters for every J value
                       (NJS elements)
        """
    @typing.overload
    def __init__(self, component: UnresolvedEnergyDependentLValue) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def AWRI(self) -> float:
        """
        The atomic weight ratio of the current isotope
        """
    @property
    def L(self) -> int:
        """
        The value of the orbital momentum l
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NJS(self) -> int:
        """
        The number of J values for this l value
        """
    @property
    def atomic_weight_ratio(self) -> float:
        """
        The atomic weight ratio of the current isotope
        """
    @property
    def j_values(self) -> ...:
        """
        The data for each of the J values
        """
    @property
    def number_spin_values(self) -> int:
        """
        The number of J values for this l value
        """
    @property
    def orbital_momentum(self) -> int:
        """
        The value of the orbital momentum l
        """
class UnresolvedEnergyIndependent:
    """
    MF2 MT151 section - unresolved resonance parameters with energy
                        independent widths and no fission given
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> UnresolvedEnergyIndependent:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, spin: float, ap: float, lssf: bool, lvalues: list[UnresolvedEnergyIndependentLValue]) -> None:
        """
        Initialise the component
        
        Arguments:
            self       the component
            spin       the target spin
            ap         the scattering radius
            lssf       the self-shielding only flag
            lvalues    l values and the resonance parameters
        """
    @typing.overload
    def __init__(self, component: UnresolvedEnergyIndependent) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def AP(self) -> float:
        """
        The scattering radius
        """
    @property
    def LFW(self) -> bool:
        """
        The average fission flag
        """
    @property
    def LRF(self) -> int:
        """
        The resonance representation
        """
    @property
    def LRU(self) -> int:
        """
        The resonance type (resolved or unresolved)
        """
    @property
    def LSSF(self) -> bool:
        """
        The self-shielding only flag
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NLS(self) -> int:
        """
        The number of l values for which resonance parameters are given
        """
    @property
    def SPI(self) -> float:
        """
        The target spin
        """
    @property
    def average_fission_width_flag(self) -> int:
        """
        The average fission flag
        """
    @property
    def l_values(self) -> ...:
        """
        The l values and its resonance parameters
        """
    @property
    def number_l_values(self) -> int:
        """
        The number of l values for which resonance parameters are given
        """
    @property
    def representation(self) -> int:
        """
        The resonance representation
        """
    @property
    def scattering_radius(self) -> float:
        """
        The scattering radius
        """
    @property
    def self_shielding_only(self) -> bool:
        """
        The self-shielding only flag
        """
    @property
    def spin(self) -> float:
        """
        The target spin
        """
    @property
    def type(self) -> int:
        """
        The resonance type (resolved or unresolved)
        """
class UnresolvedEnergyIndependentLValue:
    """
    MF2 MT151 section - the unresolved resonance parameters for a given
                        l value or independent widths (with no fission given)
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> UnresolvedEnergyIndependentLValue:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, awri: float, l: int, spins: list[float], d: list[float], amun: list[int], gn: list[float], gg: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self     the component
            awri     the atomic weight ratio
            l        the orbital angular momentum value
            spins    the spin values (NJS values)
            d        the level spacing values (NJS values)
            amun     the degrees of freedom for the neutron width (NJS values)
            gn       the average neutron widths (NJS values)
            gg       the average gamma widths (NJS values)
        """
    @typing.overload
    def __init__(self, component: UnresolvedEnergyIndependentLValue) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def AJ(self) -> ...:
        """
        The spin values
        """
    @property
    def AMUF(self) -> ...:
        """
        The degrees of freedom for the fission width
        """
    @property
    def AMUG(self) -> ...:
        """
        The degrees of freedom for the gamma width
        """
    @property
    def AMUN(self) -> ...:
        """
        The degrees of freedom for the neutron width
        """
    @property
    def AMUX(self) -> ...:
        """
        The degrees of freedom for the competitive width
        """
    @property
    def AWRI(self) -> float:
        """
        The atomic weight ratio of the current isotope
        """
    @property
    def D(self) -> ...:
        """
        The average level spacing values
        """
    @property
    def GF(self) -> ...:
        """
        The average fission width values
        """
    @property
    def GG(self) -> ...:
        """
        The average gamma widths
        """
    @property
    def GN(self) -> ...:
        """
        The average neutron widths
        """
    @property
    def GX(self) -> ...:
        """
        The average competitive width values
        """
    @property
    def L(self) -> int:
        """
        The value of the orbital momentum l
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NJS(self) -> int:
        """
        The number of J values for this l value
        """
    @property
    def atomic_weight_ratio(self) -> float:
        """
        The atomic weight ratio of the current isotope
        """
    @property
    def average_competitive_widths(self) -> ...:
        """
        The average competitive width values
        """
    @property
    def average_fission_widths(self) -> ...:
        """
        The average fission width values
        """
    @property
    def average_gamma_widths(self) -> ...:
        """
        The average gamma widths
        """
    @property
    def average_level_spacings(self) -> ...:
        """
        The average level spacing values
        """
    @property
    def average_neutron_widths(self) -> ...:
        """
        The average neutron widths
        """
    @property
    def competitive_width_degrees_freedom(self) -> ...:
        """
        The degrees of freedom for the competitive width
        """
    @property
    def fission_width_degrees_freedom(self) -> ...:
        """
        The degrees of freedom for the gamma width
        """
    @property
    def gamma_width_degrees_freedom(self) -> ...:
        """
        The degrees of freedom for the gamma width
        """
    @property
    def neutron_width_degrees_freedom(self) -> ...:
        """
        The degrees of freedom for the neutron width
        """
    @property
    def number_spin_values(self) -> int:
        """
        The number of J values for this l value
        """
    @property
    def orbital_momentum(self) -> int:
        """
        The value of the orbital momentum l
        """
    @property
    def spin_values(self) -> ...:
        """
        The spin values
        """
