"""
MT151 - resonance parameter covariances
"""
import ENDFtk
from __future__ import annotations
import typing
from . import LCOMP1
from . import LCOMP2
__all__: list[str] = ['CompactBreitWignerUncertainties', 'CompactCorrelationMatrix', 'CompactMultiLevelBreitWigner', 'CompactRMatrixLimited', 'CompactRMatrixLimitedUncertainties', 'CompactReichMoore', 'CompactReichMooreUncertainties', 'CompactSingleLevelBreitWigner', 'GeneralMultiLevelBreitWigner', 'GeneralRMatrixLimited', 'GeneralReichMoore', 'GeneralSingleLevelBreitWigner', 'Isotope', 'LCOMP1', 'LCOMP2', 'LimitedBreitWignerLValue', 'LimitedMultiLevelBreitWigner', 'LimitedSingleLevelBreitWigner', 'ReichMooreScatteringRadiusUncertainties', 'ResonanceRange', 'ScatteringRadiusCovariances', 'Section', 'ShortRangeBreitWignerBlock', 'ShortRangeRMatrixLimitedBlock', 'ShortRangeReichMooreBlock', 'UnresolvedCovarianceMatrix', 'UnresolvedLValue', 'UnresolvedRelativeCovariances']
class CompactBreitWignerUncertainties:
    """
    MF32 MT151 section - The resonance parameters and uncertainties in the SLBW or MLBW                      representation (LCOMP = 2)
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> CompactBreitWignerUncertainties:
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
    def __init__(self, awri: float, qx: float, lrx: bool, energies: list[float], spins: list[float], gt: list[float], gn: list[float], gg: list[float], gf: list[float], der: list[float], dgn: list[float], dgg: list[float], dgf: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self       the component
            awri       the atomic weight ratio
            qx         the competitive Q value
            lrx        the competitive width flag
            energies   the resonance energies (NRSA values)
            spins      the spin values (NRSA values)
            gt         the total widths (NRSA values)
            gn         the neutron widths (NRSA values)
            gg         the gamma widths (NRSA values)
            gf         the fission widths (NRSA values)
            der        the energy uncertainties (NRSA values)
            dgn        the neutron width uncertainties (NRSA values)
            dgg        the gamma width uncertainties (NRSA values)
            dgf        the fission width uncertainties (NRSA values)
        """
    @typing.overload
    def __init__(self, component: CompactBreitWignerUncertainties) -> None:
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
    def DER(self) -> ...:
        """
        The resonance energy uncertainties
        """
    @property
    def DGF(self) -> ...:
        """
        The fission width uncertainties
        """
    @property
    def DGG(self) -> ...:
        """
        The gamma width uncertainties
        """
    @property
    def DGN(self) -> ...:
        """
        The neutron width uncertainties
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
    def NRSA(self) -> int:
        """
        The number of resonances
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
    def fission_width_uncertainties(self) -> ...:
        """
        The fission width uncertainties
        """
    @property
    def fission_widths(self) -> ...:
        """
        The fission widths
        """
    @property
    def gamma_width_uncertainties(self) -> ...:
        """
        The gamma width uncertainties
        """
    @property
    def gamma_widths(self) -> ...:
        """
        The gamma widths
        """
    @property
    def neutron_width_uncertainties(self) -> ...:
        """
        The neutron width uncertainties
        """
    @property
    def neutron_widths(self) -> ...:
        """
        The neutron widths
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
    def resonance_energy_uncertainties(self) -> ...:
        """
        The resonance energy uncertainties
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
class CompactCorrelationMatrix:
    """
    MF32 MT151 section - compact correlation matrix (LCOMP = 2)
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> CompactCorrelationMatrix:
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
    def __init__(self, order: int, i: list[int], j: list[int], correlations: list[float], ndigit: int = 6) -> None:
        """
        Initialise the component
        
        Arguments:
            self           the component
            order          the order of the (square) correlation matrix
            i              the i coordinates
            j              the j coordinates
            correlations   the correlation values
            ndigit         the number of digits for compacting (default = 6)
        """
    @typing.overload
    def __init__(self, component: CompactCorrelationMatrix) -> None:
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
    def I(self) -> ...:
        """
        The i coordinates for which correlation values are available
        """
    @property
    def J(self) -> ...:
        """
        The j coordinates for which correlation values are available
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NDIGIT(self) -> int:
        """
        The number of digits used for compacting
        """
    @property
    def NNN(self) -> int:
        """
        The order of the correlation matrix
        """
    @property
    def correlations(self) -> ...:
        """
        The correlation values
        """
    @property
    def number_digits(self) -> int:
        """
        The number of digits used for compacting
        """
    @property
    def order(self) -> int:
        """
        The order of the correlation matrix
        """
class CompactMultiLevelBreitWigner:
    """
    MF32 MT151 section - multi level Breit-Wigner resonance parameter
                         covariances (LCOMP = 2)
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> CompactMultiLevelBreitWigner:
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
    def __init__(self, spi: float, ap: float, dap: float, parameters: CompactBreitWignerUncertainties, matrix: CompactCorrelationMatrix) -> None:
        """
        Initialise the component
        
        Arguments:
            self          the component
            spi           the target spin value
            ap            the scattering radius
            dap           the scattering radius uncertainty data
            parameters    the resonance parameters and uncertainties
            matrix        the correlation matrix
        """
    @typing.overload
    def __init__(self, spi: float, ap: float, parameters: CompactBreitWignerUncertainties, matrix: CompactCorrelationMatrix) -> None:
        """
        Initialise the component
        
        Arguments:
            self          the component
            spi           the target spin value
            ap            the scattering radius
            parameters    the resonance parameters and uncertainties
            matrix        the correlation matrix
        """
    @typing.overload
    def __init__(self, component: CompactMultiLevelBreitWigner) -> None:
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
    def DAP(self) -> float | None:
        """
        The scattering radius uncertainty
        """
    @property
    def ISR(self) -> bool:
        """
        The scattering radius uncertainty flag
        """
    @property
    def LCOMP(self) -> int:
        """
        The covariance representation type
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
    def correlation_matrix(self) -> CompactCorrelationMatrix:
        """
        The correlation matrix
        """
    @property
    def covariance_representation(self) -> int:
        """
        The covariance representation type
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
    def scattering_radius_uncertainty(self) -> float | None:
        """
        The scattering radius uncertainty
        """
    @property
    def scattering_radius_uncertainty_flag(self) -> bool:
        """
        The scattering radius uncertainty flag
        """
    @property
    def spin(self) -> float:
        """
        The scattering radius
        """
    @property
    def type(self) -> int:
        """
        The resonance type (resolved or unresolved)
        """
    @property
    def uncertainties(self) -> CompactBreitWignerUncertainties:
        """
        The resonance parameter uncertainties
        """
class CompactRMatrixLimited:
    """
    MF32 MT151 section - Reich-Moore resonance parameter covariances (LCOMP = 2)
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> CompactRMatrixLimited:
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
    def __init__(self, ifg: bool, parameters: CompactRMatrixLimitedUncertainties, matrix: CompactCorrelationMatrix) -> None:
        """
        Initialise the component
        
        Arguments:
            self          the component
            ifg           flag to indicate whether or not the widths are reduced
            parameters    the resonance parameters and uncertainties
            matrix        the correlation matrix
        """
    @typing.overload
    def __init__(self, component: CompactRMatrixLimited) -> None:
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
    def DAP(self) -> ReichMooreScatteringRadiusUncertainties | None:
        """
        The scattering radius uncertainty
        """
    @property
    def IFG(self) -> bool:
        """
        The flag to indicate whether or not the widths are reduced
        """
    @property
    def ISR(self) -> bool:
        """
        The scattering radius uncertainty flag
        """
    @property
    def LCOMP(self) -> int:
        """
        The covariance representation type
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
    def average_fission_width_flag(self) -> bool:
        """
        The average fission flag
        """
    @property
    def correlation_matrix(self) -> CompactCorrelationMatrix:
        """
        The correlation matrix
        """
    @property
    def covariance_representation(self) -> int:
        """
        The covariance representation type
        """
    @property
    def number_spin_groups(self) -> int:
        """
        The number of spin groups
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
    def scattering_radius_uncertainty(self) -> ReichMooreScatteringRadiusUncertainties | None:
        """
        The scattering radius uncertainty
        """
    @property
    def scattering_radius_uncertainty_flag(self) -> bool:
        """
        The scattering radius uncertainty flag
        """
    @property
    def type(self) -> int:
        """
        The resonance type (resolved or unresolved)
        """
    @property
    def uncertainties(self) -> CompactRMatrixLimitedUncertainties:
        """
        The resonance parameter uncertainties
        """
class CompactRMatrixLimitedUncertainties:
    """
    MF32 MT151 section - The resonance parameters and uncertainties in the                      R-matrix limited representation (LCOMP = 2)
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int, njsx: int) -> CompactRMatrixLimitedUncertainties:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
            njsx      the number of spin groups
        """
    @typing.overload
    def __init__(self, pairs: LCOMP2.ParticlePairs, groups: list[LCOMP2.SpinGroup]) -> None:
        """
        Initialise the component
        
        Arguments:
            self     the component
            pairs    the particle pairs
            groups   the spin groups
        """
    @typing.overload
    def __init__(self, component: CompactRMatrixLimitedUncertainties) -> None:
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
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NJSX(self) -> int:
        """
        The number of spin groups
        """
    @property
    def number_spin_groups(self) -> int:
        """
        The number of spin groups
        """
    @property
    def particle_pairs(self) -> LCOMP2.ParticlePairs:
        """
        The particle pair information
        """
    @property
    def spin_groups(self) -> ...:
        """
        The spin groups
        """
class CompactReichMoore:
    """
    MF32 MT151 section - Reich-Moore resonance parameter covariances (LCOMP = 2)
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> CompactReichMoore:
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
    def __init__(self, spi: float, ap: float, lad: bool, dap: ReichMooreScatteringRadiusUncertainties, parameters: CompactReichMooreUncertainties, matrix: CompactCorrelationMatrix) -> None:
        """
        Initialise the component
        
        Arguments:
            self          the component
            spi           the target spin value
            ap            the scattering radius
            lad           the angular distribution flag
            dap           the scattering radius uncertainty data
            parameters    the resonance parameters and uncertainties
            matrix        the correlation matrix
        """
    @typing.overload
    def __init__(self, spi: float, ap: float, lad: bool, parameters: CompactReichMooreUncertainties, matrix: CompactCorrelationMatrix) -> None:
        """
        Initialise the component
        
        Arguments:
            self          the component
            spi           the target spin value
            ap            the scattering radius
            lad           the angular distribution flag
            parameters    the resonance parameters and uncertainties
            matrix        the correlation matrix
        """
    @typing.overload
    def __init__(self, component: CompactReichMoore) -> None:
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
    def DAP(self) -> ReichMooreScatteringRadiusUncertainties | None:
        """
        The scattering radius uncertainty
        """
    @property
    def ISR(self) -> bool:
        """
        The scattering radius uncertainty flag
        """
    @property
    def LAD(self) -> bool:
        """
        The angular distribution flag
        """
    @property
    def LCOMP(self) -> int:
        """
        The covariance representation type
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
    def angular_distributions_flag(self) -> bool:
        """
        The angular distribution flag
        """
    @property
    def average_fission_width_flag(self) -> bool:
        """
        The average fission flag
        """
    @property
    def correlation_matrix(self) -> CompactCorrelationMatrix:
        """
        The correlation matrix
        """
    @property
    def covariance_representation(self) -> int:
        """
        The covariance representation type
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
    def scattering_radius_uncertainty(self) -> ReichMooreScatteringRadiusUncertainties | None:
        """
        The scattering radius uncertainty
        """
    @property
    def scattering_radius_uncertainty_flag(self) -> bool:
        """
        The scattering radius uncertainty flag
        """
    @property
    def spin(self) -> float:
        """
        The scattering radius
        """
    @property
    def type(self) -> int:
        """
        The resonance type (resolved or unresolved)
        """
    @property
    def uncertainties(self) -> CompactReichMooreUncertainties:
        """
        The resonance parameter uncertainties
        """
class CompactReichMooreUncertainties:
    """
    MF32 MT151 section - The resonance parameters and uncertainties in the RM                      representation (LCOMP = 2)
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> CompactReichMooreUncertainties:
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
    def __init__(self, awri: float, apl: float, energies: list[float], spins: list[float], gn: list[float], gg: list[float], gfa: list[float], gfb: list[float], der: list[float], dgn: list[float], dgg: list[float], dgfa: list[float], dgfb: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self       the component
            awri       the atomic weight ratio
            apl        the l dependent scattering radius
            energies   the resonance energies (NRSA values)
            spins      the spin values (NRSA values)
            gn         the neutron widths (NRSA values)
            gg         the gamma widths (NRSA values)
            gfa        the first fission widths (NRSA values)
            gfb        the second fission widths (NRSA values)
            der        the energy uncertainties (NRSA values)
            dgn        the neutron width uncertainties (NRSA values)
            dgg        the gamma width uncertainties (NRSA values)
            dgfa       the first fission width uncertainties (NRSA values)
            dgfb       the second fission width uncertainties (NRSA values)
        """
    @typing.overload
    def __init__(self, component: CompactReichMooreUncertainties) -> None:
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
        The value of the l dependent scattering radius
        """
    @property
    def AWRI(self) -> float:
        """
        The atomic weight ratio of the current isotope
        """
    @property
    def DER(self) -> ...:
        """
        The resonance energy uncertainties
        """
    @property
    def DGFA(self) -> ...:
        """
        The first fission width uncertainties
        """
    @property
    def DGFB(self) -> ...:
        """
        The second fission width uncertainties
        """
    @property
    def DGG(self) -> ...:
        """
        The gamma width uncertainties
        """
    @property
    def DGN(self) -> ...:
        """
        The neutron width uncertainties
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
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NRSA(self) -> int:
        """
        The number of resonances
        """
    @property
    def atomic_weight_ratio(self) -> float:
        """
        The atomic weight ratio of the current isotope
        """
    @property
    def first_fission_width_uncertainties(self) -> ...:
        """
        The first fission width uncertainties
        """
    @property
    def first_fission_widths(self) -> ...:
        """
        The first fission widths
        """
    @property
    def gamma_width_uncertainties(self) -> ...:
        """
        The gamma width uncertainties
        """
    @property
    def gamma_widths(self) -> ...:
        """
        The gamma widths
        """
    @property
    def l_dependent_scattering_radius(self) -> float:
        """
        The value of the l dependent scattering radius
        """
    @property
    def neutron_width_uncertainties(self) -> ...:
        """
        The neutron width uncertainties
        """
    @property
    def neutron_widths(self) -> ...:
        """
        The neutron widths
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
    def resonance_energy_uncertainties(self) -> ...:
        """
        The resonance energy uncertainties
        """
    @property
    def second_fission_width_uncertainties(self) -> ...:
        """
        The second fission width uncertainties
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
class CompactSingleLevelBreitWigner:
    """
    MF32 MT151 section - single level Breit-Wigner resonance parameter
                         covariances (LCOMP = 2)
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> CompactSingleLevelBreitWigner:
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
    def __init__(self, spi: float, ap: float, dap: float, parameters: CompactBreitWignerUncertainties, matrix: CompactCorrelationMatrix) -> None:
        """
        Initialise the component
        
        Arguments:
            self          the component
            spi           the target spin value
            ap            the scattering radius
            dap           the scattering radius uncertainty data
            parameters    the resonance parameters and uncertainties
            matrix        the correlation matrix
        """
    @typing.overload
    def __init__(self, spi: float, ap: float, parameters: CompactBreitWignerUncertainties, matrix: CompactCorrelationMatrix) -> None:
        """
        Initialise the component
        
        Arguments:
            self          the component
            spi           the target spin value
            ap            the scattering radius
            parameters    the resonance parameters and uncertainties
            matrix        the correlation matrix
        """
    @typing.overload
    def __init__(self, component: CompactSingleLevelBreitWigner) -> None:
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
    def DAP(self) -> float | None:
        """
        The scattering radius uncertainty
        """
    @property
    def ISR(self) -> bool:
        """
        The scattering radius uncertainty flag
        """
    @property
    def LCOMP(self) -> int:
        """
        The covariance representation type
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
    def correlation_matrix(self) -> CompactCorrelationMatrix:
        """
        The correlation matrix
        """
    @property
    def covariance_representation(self) -> int:
        """
        The covariance representation type
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
    def scattering_radius_uncertainty(self) -> float | None:
        """
        The scattering radius uncertainty
        """
    @property
    def scattering_radius_uncertainty_flag(self) -> bool:
        """
        The scattering radius uncertainty flag
        """
    @property
    def spin(self) -> float:
        """
        The scattering radius
        """
    @property
    def type(self) -> int:
        """
        The resonance type (resolved or unresolved)
        """
    @property
    def uncertainties(self) -> CompactBreitWignerUncertainties:
        """
        The resonance parameter uncertainties
        """
class GeneralMultiLevelBreitWigner:
    """
    MF32 MT151 section - Multi-level Breit-Wigner resonance parameters and
                         covariances using LCOMP=1
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> GeneralMultiLevelBreitWigner:
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
    def __init__(self, awri: float, spin: float, ap: float, dap: float, nls: int, short: list[ShortRangeBreitWignerBlock], long: list[ENDFtk.CovariancePairs | ENDFtk.SquareMatrix]) -> None:
        """
        Initialise the component
        
        Arguments:
            self      the component
            awri      the atomic mass ratio
            spi       the target spin value
            ap        the scattering radius
            dap       the scattering radius uncertainty data
            nls       the number of l values
            short     the short range covariance blocks
            long      the long range covariance blocks
        """
    @typing.overload
    def __init__(self, awri: float, spin: float, ap: float, nls: int, short: list[ShortRangeBreitWignerBlock], long: list[ENDFtk.CovariancePairs | ENDFtk.SquareMatrix]) -> None:
        """
        Initialise the component
        
        Arguments:
            self      the component
            awri      the atomic mass ratio
            spi       the target spin value
            ap        the scattering radius
            nls       the number of l values
            short     the short range covariance blocks
            long      the long range covariance blocks
        """
    @typing.overload
    def __init__(self, component: GeneralMultiLevelBreitWigner) -> None:
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
    def AWRI(self) -> float:
        """
        The atomic weight ratio of the current isotope
        """
    @property
    def DAP(self) -> float | None:
        """
        The scattering radius uncertainty
        """
    @property
    def ISR(self) -> bool:
        """
        The scattering radius uncertainty flag
        """
    @property
    def LCOMP(self) -> int:
        """
        The covariance representation type
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
    def NLRS(self) -> int:
        """
        The number of long range covariance blocks
        """
    @property
    def NLS(self) -> int:
        """
        The number of l values for which resonance parameters are given
        """
    @property
    def NSRS(self) -> int:
        """
        The number of short range covariance blocks
        """
    @property
    def SPI(self) -> float:
        """
        The target spin
        """
    @property
    def atomic_weight_ratio(self) -> float:
        """
        The atomic weight ratio of the current isotope
        """
    @property
    def average_fission_width_flag(self) -> bool:
        """
        The average fission flag
        """
    @property
    def covariance_representation(self) -> int:
        """
        The covariance representation type
        """
    @property
    def long_range_blocks(self) -> ...:
        """
        The long range resonance covariance blocks
        """
    @property
    def number_l_values(self) -> int:
        """
        The number of l values for which resonance parameters are given
        """
    @property
    def number_long_range_blocks(self) -> int:
        """
        The number of long range covariance blocks
        """
    @property
    def number_short_range_blocks(self) -> int:
        """
        The number of short range covariance blocks
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
    def scattering_radius_uncertainty(self) -> float | None:
        """
        The scattering radius uncertainty
        """
    @property
    def scattering_radius_uncertainty_flag(self) -> bool:
        """
        The scattering radius uncertainty flag
        """
    @property
    def short_range_blocks(self) -> ...:
        """
        The short range resonance covariance blocks
        """
    @property
    def spin(self) -> float:
        """
        The scattering radius
        """
    @property
    def type(self) -> int:
        """
        The resonance type (resolved or unresolved)
        """
class GeneralRMatrixLimited:
    """
    MF32 MT151 section - R-matrix limited resonance parameters and covariances
                         using LCOMP=1
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> GeneralRMatrixLimited:
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
    def __init__(self, awri: float, short: list[ShortRangeRMatrixLimitedBlock]) -> None:
        """
        Initialise the component
        
        Arguments:
            self      the component
            awri      the atomic mass ratio
            short     the short range covariance blocks
        """
    @typing.overload
    def __init__(self, component: GeneralRMatrixLimited) -> None:
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
    def AWRI(self) -> float:
        """
        The atomic weight ratio of the current isotope
        """
    @property
    def DAP(self) -> ReichMooreScatteringRadiusUncertainties | None:
        """
        The scattering radius uncertainty
        """
    @property
    def ISR(self) -> bool:
        """
        The scattering radius uncertainty flag
        """
    @property
    def LCOMP(self) -> int:
        """
        The covariance representation type
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
    def NLRS(self) -> int:
        """
        The number of long range covariance blocks
        """
    @property
    def NSRS(self) -> int:
        """
        The number of short range covariance blocks
        """
    @property
    def SPI(self) -> float:
        """
        The target spin
        """
    @property
    def atomic_weight_ratio(self) -> float:
        """
        The atomic weight ratio of the current isotope
        """
    @property
    def average_fission_width_flag(self) -> bool:
        """
        The average fission flag
        """
    @property
    def covariance_representation(self) -> int:
        """
        The covariance representation type
        """
    @property
    def number_long_range_blocks(self) -> int:
        """
        The number of long range covariance blocks
        """
    @property
    def number_short_range_blocks(self) -> int:
        """
        The number of short range covariance blocks
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
    def scattering_radius_uncertainty(self) -> ReichMooreScatteringRadiusUncertainties | None:
        """
        The scattering radius uncertainty
        """
    @property
    def scattering_radius_uncertainty_flag(self) -> bool:
        """
        The scattering radius uncertainty flag
        """
    @property
    def short_range_blocks(self) -> ...:
        """
        The short range resonance covariance blocks
        """
    @property
    def spin(self) -> float:
        """
        The scattering radius
        """
    @property
    def type(self) -> int:
        """
        The resonance type (resolved or unresolved)
        """
class GeneralReichMoore:
    """
    MF32 MT151 section - Reich-Moore resonance parameters and covariances
                         using LCOMP=1
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> GeneralReichMoore:
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
    def __init__(self, awri: float, spin: float, ap: float, dap: ReichMooreScatteringRadiusUncertainties, nls: int, short: list[ShortRangeReichMooreBlock], long: list[ENDFtk.CovariancePairs | ENDFtk.SquareMatrix]) -> None:
        """
        Initialise the component
        
        Arguments:
            self      the component
            awri      the atomic mass ratio
            spi       the target spin value
            ap        the scattering radius
            dap       the scattering radius uncertainty data
            nls       the number of l values
            short     the short range covariance blocks
            long      the long range covariance blocks
        """
    @typing.overload
    def __init__(self, awri: float, spin: float, ap: float, nls: int, short: list[ShortRangeReichMooreBlock], long: list[ENDFtk.CovariancePairs | ENDFtk.SquareMatrix]) -> None:
        """
        Initialise the component
        
        Arguments:
            self      the component
            awri      the atomic mass ratio
            spi       the target spin value
            ap        the scattering radius
            nls       the number of l values
            short     the short range covariance blocks
            long      the long range covariance blocks
        """
    @typing.overload
    def __init__(self, component: GeneralReichMoore) -> None:
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
    def AWRI(self) -> float:
        """
        The atomic weight ratio of the current isotope
        """
    @property
    def DAP(self) -> ReichMooreScatteringRadiusUncertainties | None:
        """
        The scattering radius uncertainty
        """
    @property
    def ISR(self) -> bool:
        """
        The scattering radius uncertainty flag
        """
    @property
    def LCOMP(self) -> int:
        """
        The covariance representation type
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
    def NLRS(self) -> int:
        """
        The number of long range covariance blocks
        """
    @property
    def NLS(self) -> int:
        """
        The number of l values for which resonance parameters are given
        """
    @property
    def NSRS(self) -> int:
        """
        The number of short range covariance blocks
        """
    @property
    def SPI(self) -> float:
        """
        The target spin
        """
    @property
    def atomic_weight_ratio(self) -> float:
        """
        The atomic weight ratio of the current isotope
        """
    @property
    def average_fission_width_flag(self) -> bool:
        """
        The average fission flag
        """
    @property
    def covariance_representation(self) -> int:
        """
        The covariance representation type
        """
    @property
    def long_range_blocks(self) -> ...:
        """
        The long range resonance covariance blocks
        """
    @property
    def number_l_values(self) -> int:
        """
        The number of l values for which resonance parameters are given
        """
    @property
    def number_long_range_blocks(self) -> int:
        """
        The number of long range covariance blocks
        """
    @property
    def number_short_range_blocks(self) -> int:
        """
        The number of short range covariance blocks
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
    def scattering_radius_uncertainty(self) -> ReichMooreScatteringRadiusUncertainties | None:
        """
        The scattering radius uncertainty
        """
    @property
    def scattering_radius_uncertainty_flag(self) -> bool:
        """
        The scattering radius uncertainty flag
        """
    @property
    def short_range_blocks(self) -> ...:
        """
        The short range resonance covariance blocks
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
class GeneralSingleLevelBreitWigner:
    """
    MF32 MT151 section - Single level Breit-Wigner resonance parameters and
                         covariances using LCOMP=1
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> GeneralSingleLevelBreitWigner:
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
    def __init__(self, awri: float, spin: float, ap: float, dap: float, nls: int, short: list[ShortRangeBreitWignerBlock], long: list[ENDFtk.CovariancePairs | ENDFtk.SquareMatrix]) -> None:
        """
        Initialise the component
        
        Arguments:
            self      the component
            awri      the atomic mass ratio
            spi       the target spin value
            ap        the scattering radius
            dap       the scattering radius uncertainty data
            nls       the number of l values
            short     the short range covariance blocks
            long      the long range covariance blocks
        """
    @typing.overload
    def __init__(self, awri: float, spin: float, ap: float, nls: int, short: list[ShortRangeBreitWignerBlock], long: list[ENDFtk.CovariancePairs | ENDFtk.SquareMatrix]) -> None:
        """
        Initialise the component
        
        Arguments:
            self      the component
            awri      the atomic mass ratio
            spi       the target spin value
            ap        the scattering radius
            nls       the number of l values
            short     the short range covariance blocks
            long      the long range covariance blocks
        """
    @typing.overload
    def __init__(self, component: GeneralSingleLevelBreitWigner) -> None:
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
    def AWRI(self) -> float:
        """
        The atomic weight ratio of the current isotope
        """
    @property
    def DAP(self) -> float | None:
        """
        The scattering radius uncertainty
        """
    @property
    def ISR(self) -> bool:
        """
        The scattering radius uncertainty flag
        """
    @property
    def LCOMP(self) -> int:
        """
        The covariance representation type
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
    def NLRS(self) -> int:
        """
        The number of long range covariance blocks
        """
    @property
    def NLS(self) -> int:
        """
        The number of l values for which resonance parameters are given
        """
    @property
    def NSRS(self) -> int:
        """
        The number of short range covariance blocks
        """
    @property
    def SPI(self) -> float:
        """
        The target spin
        """
    @property
    def atomic_weight_ratio(self) -> float:
        """
        The atomic weight ratio of the current isotope
        """
    @property
    def average_fission_width_flag(self) -> bool:
        """
        The average fission flag
        """
    @property
    def covariance_representation(self) -> int:
        """
        The covariance representation type
        """
    @property
    def long_range_blocks(self) -> ...:
        """
        The long range resonance covariance blocks
        """
    @property
    def number_l_values(self) -> int:
        """
        The number of l values for which resonance parameters are given
        """
    @property
    def number_long_range_blocks(self) -> int:
        """
        The number of long range covariance blocks
        """
    @property
    def number_short_range_blocks(self) -> int:
        """
        The number of short range covariance blocks
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
    def scattering_radius_uncertainty(self) -> float | None:
        """
        The scattering radius uncertainty
        """
    @property
    def scattering_radius_uncertainty_flag(self) -> bool:
        """
        The scattering radius uncertainty flag
        """
    @property
    def short_range_blocks(self) -> ...:
        """
        The short range resonance covariance blocks
        """
    @property
    def spin(self) -> float:
        """
        The scattering radius
        """
    @property
    def type(self) -> int:
        """
        The resonance type (resolved or unresolved)
        """
class Isotope:
    """
    MF32 MT151 section - an isotope with resonance energy ranges
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
    def __init__(self, zai: float, abn: float, lfw: bool, ranges: list[ResonanceRange]) -> None:
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
    def ZAI(self) -> float:
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
    def number_resonance_ranges(self) -> int:
        """
        The number of resonance ranges for this isotope
        """
    @property
    def resonance_ranges(self) -> ...:
        """
        The resonance ranges for this isotope
        """
class LimitedBreitWignerLValue:
    """
    MF32 MT151 section - resonance parameters and variance/covariance data for
                         a given l value in the SLBW or MLBW representation (LCOMP = 0)
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> LimitedBreitWignerLValue:
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
    def __init__(self, awri: float, l: int, energies: list[float], spins: list[float], gt: list[float], gn: list[float], gg: list[float], gf: list[float], de2: list[float], dn2: list[float], dndg: list[float], dg2: list[float], dndf: list[float], dgdf: list[float], df2: list[float], djdn: list[float], djdg: list[float], djdf: list[float], dj2: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self        the component
            awri        the atomic weight ratio
            l           the orbital angular momentum value
            energies    the resonance energies (NRS values)
            spins       the spin values (NRS values)
            gt          the total widths (NRS values)
            gn          the neutron widths (NRS values)
            gg          the gamma widths (NRS values)
            gf          the fission widths (NRS values)
            de2         the energy variances (NRS values)
            dn2         the neutron width variances (NRS values)
            dndg        the neutron and gamma width covariances (NRS values)
            dg2         the gamma width variances (NRS values)
            dndf        the neutron and fission width covariances (NRS values)
            dgdf        the gamma and fission width covariances (NRS values)
            df2         the fission width variances (NRS values)
            djdn        the spin and neutron width covariances (NRS values)
            djdg        the spin and gamma width covariances (NRS values)
            djdf        the spin and fission width covariances (NRS values)
            df2         the spin variances (NRS values)
        """
    @typing.overload
    def __init__(self, component: LimitedBreitWignerLValue) -> None:
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
    def DE2(self) -> ...:
        """
        The resonance energy variances
        """
    @property
    def DF2(self) -> ...:
        """
        The fission width variances
        """
    @property
    def DG2(self) -> ...:
        """
        The gamma width variances
        """
    @property
    def DGDF(self) -> ...:
        """
        The gamma and fission width covariances
        """
    @property
    def DJ2(self) -> ...:
        """
        The spin variances
        """
    @property
    def DJDF(self) -> ...:
        """
        The spin and fission width covariances
        """
    @property
    def DJDG(self) -> ...:
        """
        The spin and gamma width covariances
        """
    @property
    def DJDN(self) -> ...:
        """
        The spin and neutron width covariances
        """
    @property
    def DN2(self) -> ...:
        """
        The neutron width variances
        """
    @property
    def DNDF(self) -> ...:
        """
        The neutron and fission width covariances
        """
    @property
    def DNDG(self) -> ...:
        """
        The neutron and gamma width covariances
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
    def fission_width_variances(self) -> ...:
        """
        The fission width variances
        """
    @property
    def fission_widths(self) -> ...:
        """
        The fission widths
        """
    @property
    def gamma_and_fission_width_covariances(self) -> ...:
        """
        The gamma and fission width covariances
        """
    @property
    def gamma_width_variances(self) -> ...:
        """
        The gamma width variances
        """
    @property
    def gamma_widths(self) -> ...:
        """
        The gamma widths
        """
    @property
    def neutron_and_fission_width_covariances(self) -> ...:
        """
        The neutron and fission width covariances
        """
    @property
    def neutron_and_gamma_width_covariances(self) -> ...:
        """
        The neutron and gamma width covariances
        """
    @property
    def neutron_width_variances(self) -> ...:
        """
        The neutron width variances
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
    def resonance_energy_variances(self) -> ...:
        """
        The resonance energy variances
        """
    @property
    def spin_and_fission_width_covariances(self) -> ...:
        """
        The spin and fission width covariances
        """
    @property
    def spin_and_gamma_width_covariances(self) -> ...:
        """
        The spin and gamma width covariances
        """
    @property
    def spin_and_neutron_width_covariances(self) -> ...:
        """
        The spin and neutron width covariances
        """
    @property
    def spin_values(self) -> ...:
        """
        The spin values
        """
    @property
    def spin_variances(self) -> ...:
        """
        The spin variances
        """
    @property
    def total_widths(self) -> ...:
        """
        The total widths
        """
class LimitedMultiLevelBreitWigner:
    """
    MF32 MT151 section - Single level Breit-Wigner resonance parameters and
                         covariances using LCOMP=0
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> LimitedMultiLevelBreitWigner:
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
    def __init__(self, spin: float, ap: float, dap: float, lvalues: list[LimitedBreitWignerLValue]) -> None:
        """
        Initialise the component
        
        Arguments:
            self       the component
            spin       the target spin
            ap         the scattering radius
            dap        the scattering radius uncertainty
            lvalues    l values and the resonance parameters
        """
    @typing.overload
    def __init__(self, spin: float, ap: float, lvalues: list[LimitedBreitWignerLValue]) -> None:
        """
        Initialise the component
        
        Arguments:
            self       the component
            spin       the target spin
            ap         the scattering radius
            lvalues    l values and the resonance parameters
        """
    @typing.overload
    def __init__(self, component: LimitedMultiLevelBreitWigner) -> None:
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
    def DAP(self) -> float | None:
        """
        The scattering radius uncertainty
        """
    @property
    def ISR(self) -> bool:
        """
        The scattering radius uncertainty flag
        """
    @property
    def LCOMP(self) -> int:
        """
        The covariance representation type
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
    def covariance_representation(self) -> int:
        """
        The covariance representation type
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
    def scattering_radius_uncertainty(self) -> float | None:
        """
        The scattering radius uncertainty
        """
    @property
    def scattering_radius_uncertainty_flag(self) -> bool:
        """
        The scattering radius uncertainty flag
        """
    @property
    def spin(self) -> float:
        """
        The scattering radius
        """
    @property
    def type(self) -> int:
        """
        The resonance type (resolved or unresolved)
        """
class LimitedSingleLevelBreitWigner:
    """
    MF32 MT151 section - Single level Breit-Wigner resonance parameters and
                         covariances using LCOMP=0
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> LimitedSingleLevelBreitWigner:
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
    def __init__(self, spin: float, ap: float, dap: float, lvalues: list[LimitedBreitWignerLValue]) -> None:
        """
        Initialise the component
        
        Arguments:
            self       the component
            spin       the target spin
            ap         the scattering radius
            dap        the scattering radius uncertainty
            lvalues    l values and the resonance parameters
        """
    @typing.overload
    def __init__(self, spin: float, ap: float, lvalues: list[LimitedBreitWignerLValue]) -> None:
        """
        Initialise the component
        
        Arguments:
            self       the component
            spin       the target spin
            ap         the scattering radius
            lvalues    l values and the resonance parameters
        """
    @typing.overload
    def __init__(self, component: LimitedSingleLevelBreitWigner) -> None:
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
    def DAP(self) -> float | None:
        """
        The scattering radius uncertainty
        """
    @property
    def ISR(self) -> bool:
        """
        The scattering radius uncertainty flag
        """
    @property
    def LCOMP(self) -> int:
        """
        The covariance representation type
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
    def covariance_representation(self) -> int:
        """
        The covariance representation type
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
    def scattering_radius_uncertainty(self) -> float | None:
        """
        The scattering radius uncertainty
        """
    @property
    def scattering_radius_uncertainty_flag(self) -> bool:
        """
        The scattering radius uncertainty flag
        """
    @property
    def spin(self) -> float:
        """
        The scattering radius
        """
    @property
    def type(self) -> int:
        """
        The resonance type (resolved or unresolved)
        """
class ReichMooreScatteringRadiusUncertainties:
    """
    MF32 MT151 section - scattering radius uncertainties in the Reich-Moore
                         formalism (LCOMP = 1)
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> ReichMooreScatteringRadiusUncertainties:
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
    def __init__(self, dap: float, uncertainties: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self             the component
            dap              the default scattering radius uncertainty
            uncertainties    the l-dependent uncertainties
        """
    @typing.overload
    def __init__(self, component: ReichMooreScatteringRadiusUncertainties) -> None:
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
    def DAP(self) -> float:
        """
        The default scattering radius uncertainty
        """
    @property
    def DAPL(self) -> ...:
        """
        The l-dependent uncertainties
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def default_uncertainty(self) -> float:
        """
        The default scattering radius uncertainty
        """
    @property
    def uncertainties(self) -> ...:
        """
        The l-dependent uncertainties
        """
class ResonanceRange:
    """
    MF32 MT151 section - a resonance energy range with parameters and covariances
    """
    def __init__(self, el: float, eh: float, naps: int, parameters: LimitedSingleLevelBreitWigner | LimitedMultiLevelBreitWigner | GeneralSingleLevelBreitWigner | GeneralMultiLevelBreitWigner | GeneralReichMoore | GeneralRMatrixLimited | CompactSingleLevelBreitWigner | CompactMultiLevelBreitWigner | CompactReichMoore | CompactRMatrixLimited | UnresolvedRelativeCovariances, scattering_radius: ScatteringRadiusCovariances | None = None) -> None:
        """
        Initialise the component
        
        Arguments:
            self                the component
            el                  the lower energy of the resonance region
            eh                  the upper energy of the resonance region
            naps                the flag to indicate then on how to calculate
                                the scattering radius (0 or 1 if no energy
                                dependent scattering radius is given and 0, 1
                                or 2 if energy dependent scattering radius is
                                given)
            parameters          the resonance parameters
            scatteringRadius    An optional energy dependent scattering radius
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
    def parameters(self) -> LimitedSingleLevelBreitWigner | LimitedMultiLevelBreitWigner | GeneralSingleLevelBreitWigner | GeneralMultiLevelBreitWigner | GeneralReichMoore | GeneralRMatrixLimited | CompactSingleLevelBreitWigner | CompactMultiLevelBreitWigner | CompactReichMoore | CompactRMatrixLimited | UnresolvedRelativeCovariances:
        """
        The resonance parameters
        """
    @property
    def representation(self) -> int:
        """
        The resonance representation
        """
    @property
    def scattering_radius(self) -> ScatteringRadiusCovariances | None:
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
class ScatteringRadiusCovariances:
    """
    MF32 MT151 section - energy dependent scattering radius covariances
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> ScatteringRadiusCovariances:
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
    def __init__(self, data: list[ENDFtk.CovariancePairs | ENDFtk.SquareMatrix | ENDFtk.RectangularMatrix]) -> None:
        """
        Initialise the component
        
        Arguments:
            self    the component
            data    the NI-type data blocks
        """
    @typing.overload
    def __init__(self, component: ScatteringRadiusCovariances) -> None:
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
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NI(self) -> int:
        """
        The number of NI-type data blocks
        """
    @property
    def data(self) -> ...:
        """
        The NI-type subsubsections
        """
    @property
    def number_data_blocks(self) -> int:
        """
        The number of NI-type data blocks
        """
class Section:
    """
    MF32 MT151 section - resonance parameter covariances
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
    def __init__(self, zaid: float, awr: float, isotopes: list[Isotope]) -> None:
        """
        Initialise the section using isotopes
        
        Arguments:
            self        the section
            zaid        the ZA value of the material
            awr         the atomic weight ratio
            isotopes    the isotopes for the section
        """
    @typing.overload
    def __init__(self, zaid: float, awr: float, lfw: bool, ranges: list[ResonanceRange]) -> None:
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
class ShortRangeBreitWignerBlock:
    """
    MF32 MT151 section - resonance parameters and variance/covariance block for
                         in the SLBW or MLBW representation (LCOMP = 1)
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> ShortRangeBreitWignerBlock:
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
    def __init__(self, mpar: int, energies: list[float], spins: list[float], gt: list[float], gn: list[float], gg: list[float], gf: list[float], values: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self        the component
            mpar        the number of parameters with covariances
            energies    the resonance energies (NRB values)
            spins       the spin values (NRB values)
            gt          the total widths (NRB values)
            gn          the neutron widths (NRB values)
            gg          the gamma widths (NRB values)
            gf          the fission widths (NRB values)
            values      the values of the upper diagonal covaraince matrix
        """
    @typing.overload
    def __init__(self, component: ShortRangeBreitWignerBlock) -> None:
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
    def MPAR(self) -> int:
        """
        The number of resonance parameters with covariance data (for each resonance)
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NPARB(self) -> int:
        """
        The order of the covariance matrix
        """
    @property
    def NRB(self) -> int:
        """
        The number of resonances for this l value
        """
    @property
    def NVS(self) -> int:
        """
        The number of values in the upper triangular covariance matrix
        """
    @property
    def covariance_matrix(self) -> ...:
        """
        The upper triangular covariance matrix
        """
    @property
    def covariance_matrix_order(self) -> int:
        """
        The order of the covariance matrix
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
    def number_parameters_with_covariances(self) -> int:
        """
        The number of resonance parameters with covariance data (for each resonance)
        """
    @property
    def number_resonances(self) -> int:
        """
        The number of resonances for this l value
        """
    @property
    def number_values(self) -> int:
        """
        The number of values in the upper triangular covariance matrix
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
class ShortRangeRMatrixLimitedBlock:
    """
    MF32 MT151 section - resonance parameters and variance/covariance block for
                         in the R-matrix limited representation (LCOMP = 1)
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> ShortRangeRMatrixLimitedBlock:
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
    def __init__(self, parameters: list[LCOMP1.ResonanceParameters], covariances: LCOMP1.CovarianceMatrix) -> None:
        """
        Initialise the component
        
        Arguments:
            self           the component
            parameters     the resonance parameters
            covariances    the covariance matrix
        """
    @typing.overload
    def __init__(self, component: ShortRangeRMatrixLimitedBlock) -> None:
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
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NJSX(self) -> int:
        """
        The number of spin groups for which resonance parameters are given
        """
    @property
    def covariance_matrix(self) -> LCOMP1.CovarianceMatrix:
        """
        The covariance matrix
        """
    @property
    def number_spin_groups(self) -> int:
        """
        The number of spin groups for which resonance parameters are given
        """
    @property
    def resonance_parameters(self) -> ...:
        """
        The resonance parameters
        """
class ShortRangeReichMooreBlock:
    """
    MF32 MT151 section - resonance parameters and variance/covariance block for
                         in the RM representation (LCOMP = 1)
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> ShortRangeReichMooreBlock:
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
    def __init__(self, mpar: int, energies: list[float], spins: list[float], gn: list[float], gg: list[float], gfa: list[float], gfb: list[float], values: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self        the component
            mpar        the number of parameters with covariances
            energies    the resonance energies (NRB values)
            spins       the spin values (NRB values)
            gn          the neutron widths (NRB values)
            gg          the gamma widths (NRB values)
            gfa         the first fission widths (NRB values)
            gfb         the second fission widths (NRB values)
            values      the values of the upper diagonal covaraince matrix
        """
    @typing.overload
    def __init__(self, component: ShortRangeReichMooreBlock) -> None:
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
        The first fission widths
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
    def MPAR(self) -> int:
        """
        The number of resonance parameters with covariance data (for each resonance)
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NPARB(self) -> int:
        """
        The order of the covariance matrix
        """
    @property
    def NRB(self) -> int:
        """
        The number of resonances for this l value
        """
    @property
    def NVS(self) -> int:
        """
        The number of values in the upper triangular covariance matrix
        """
    @property
    def covariance_matrix(self) -> ...:
        """
        The upper triangular covariance matrix
        """
    @property
    def covariance_matrix_order(self) -> int:
        """
        The order of the covariance matrix
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
    def neutron_widths(self) -> ...:
        """
        The neutron widths
        """
    @property
    def number_parameters_with_covariances(self) -> int:
        """
        The number of resonance parameters with covariance data (for each resonance)
        """
    @property
    def number_resonances(self) -> int:
        """
        The number of resonances for this l value
        """
    @property
    def number_values(self) -> int:
        """
        The number of values in the upper triangular covariance matrix
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
class UnresolvedCovarianceMatrix:
    """
    MF32 MT151 section - covariance data for the unresolved resonances
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> UnresolvedCovarianceMatrix:
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
    def __init__(self, mpar: int, values: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self        the component
            mpar        the number of average parameters with covariance data
            values      the values of the upper diagonal covaraince matrix
        """
    @typing.overload
    def __init__(self, component: UnresolvedCovarianceMatrix) -> None:
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
    def MPAR(self) -> int:
        """
        The number of average parameters for which covariance data is given
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NPAR(self) -> int:
        """
        The order of the covariance matrix
        """
    @property
    def NVS(self) -> int:
        """
        The number of values in the upper triangular covariance matrix
        """
    @property
    def covariance_matrix(self) -> ...:
        """
        The upper triangular covariance matrix
        """
    @property
    def covariance_matrix_order(self) -> int:
        """
        The order of the covariance matrix
        """
    @property
    def number_average_parameters(self) -> int:
        """
        The number of average parameters for which covariance data is given
        """
    @property
    def number_values(self) -> int:
        """
        The number of values in the upper triangular covariance matrix
        """
class UnresolvedLValue:
    """
    MF32 MT151 section - resonance parameters for a given l value in the
                        unresolved resonance covariance data.
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> UnresolvedLValue:
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
    def __init__(self, awri: float, l: int, spins: list[float], d: list[float], gno: list[float], gg: list[float], gf: list[float], gx: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self     the component
            awri     the atomic weight ratio
            l        the orbital angular momentum value
            spins    the spin values (NJS values)
            d        the level spacing values (NJS values)
            gno      the average neutron widths (NJS values)
            gg       the average gamma widths (NJS values)
            gf       the average fission widths (NJS values)
            gx       the average competitive widths (NJS values)
        """
    @typing.overload
    def __init__(self, component: UnresolvedLValue) -> None:
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
    def GNO(self) -> ...:
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
class UnresolvedRelativeCovariances:
    """
    MF32 MT151 section - unresolved resonance relative covariance data
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> UnresolvedRelativeCovariances:
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
    def __init__(self, spin: float, ap: float, lvalues: list[UnresolvedLValue], matrix: UnresolvedCovarianceMatrix) -> None:
        """
        Initialise the component
        
        Arguments:
            self       the component
            spi        the target spin value
            ap         the scattering radius
            lvalues    the l values and the resonance parameters
            matrix     the covariance matrix
        """
    @typing.overload
    def __init__(self, component: UnresolvedRelativeCovariances) -> None:
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
        The target spin
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
    def average_fission_width_flag(self) -> bool:
        """
        The average fission flag
        """
    @property
    def covariance_matrix(self) -> UnresolvedCovarianceMatrix:
        """
        The covariance matrix
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
        The target spin
        """
    @property
    def spin(self) -> float:
        """
        The scattering radius
        """
    @property
    def type(self) -> int:
        """
        The resonance type (resolved or unresolved)
        """
