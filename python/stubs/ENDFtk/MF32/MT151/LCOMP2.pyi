"""
LCOMP2 - compact resolved resonance covariance components
"""
from __future__ import annotations
import typing
__all__: list[str] = ['ParticlePairs', 'ResonanceChannels', 'ResonanceParameters', 'SpinGroup']
class ParticlePairs:
    """
    MF32 MT151 section - particle pair information for the R-matrix limited
                         uncertainty data (LCOMP = 2)
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
    def __init__(self, njsx: int, ma: list[float], mb: list[float], za: list[float], zb: list[float], ia: list[float], ib: list[float], pa: list[float], pb: list[float], q: list[float], pnt: list[int], shf: list[int], mt: list[int]) -> None:
        """
        Initialise the component
        
        Arguments:
            self    the component
            njsx    the number of spin groups included in the uncertainty data
            ma      the mass of the first particle in each particle pair
            mb      the mass of the first particle in each particle pair
            za      the charge of the first particle in each particle pair
            zb      the charge of the first particle in each particle pair
            ia      the spin of the first particle in each particle pair
            ib      the spin of the first particle in each particle pair
            pa      the parity of the first particle in each particle pair
            pb      the parity of the first particle in each particle pair
            q       the mass of the first particle in each particle pair
            pnt     the mass of the first particle in each particle pair
            shf     the charge of the first particle in each particle pair
            mt      the charge of the first particle in each particle pair
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
    def NJSX(self) -> int:
        """
        The number of spin groups for which resonance parameters are given
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
        The mass of the first particle in each particle pair
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
    def number_spin_groups(self) -> int:
        """
        The number of spin groups for which resonance parameters are given
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
class ResonanceChannels:
    """
    MF32 MT151 section - resonance channel information for a spin group
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
    def __init__(self, spin: float, parity: float, ppi: list[int], l: list[int], s: list[float], b: list[float], apt: list[float], ape: list[float]) -> None:
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
        """
    @typing.overload
    def __init__(self, spin: float, parity: float, ppi: list[int], l: list[int], s: list[float], b: list[float], ap: list[float]) -> None:
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
        The parity of the spin J
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
        The parity of the spin J
        """
    @property
    def particle_pair_numbers(self) -> ...:
        """
        The particle pair numbers of each channel
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
    MF32 MT151 section - resonance parameter uncertainties for a spin group
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
    def __init__(self, energies: list[float], parameters: list[list[float]], denergies: list[float], dparameters: list[list[float]]) -> None:
        """
        Initialise the component
        
        Arguments:
            self          the component
            energies      the resonance energies (NRS values)
            parameters    the resonance parameters (NRS times NCH values)
            denergies     the resonance energy uncertainties (NRS values)
            dparameters   the resonance parameter uncertainties (NRS times NCH values)
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
    def DER(self) -> ...:
        """
        The resonance energy uncertainties
        """
    @property
    def DGAM(self) -> ...:
        """
        The resonance parameter uncertainties
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
    def NRSA(self) -> int:
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
    def resonance_energy_uncertainties(self) -> ...:
        """
        The resonance energy uncertainties
        """
    @property
    def resonance_parameter_uncertainties(self) -> ...:
        """
        The resonance parameters uncertainties
        """
    @property
    def resonance_parameters(self) -> ...:
        """
        The resonance parameters
        """
class SpinGroup:
    """
    MF2 MT151 section - R-matrix limited spin group with resonance parameter uncertainties
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
    def NRSA(self) -> int:
        """
        The number of resonances
        """
    @property
    def PJ(self) -> float:
        """
        The parity of the spin J
        """
    @property
    def channels(self) -> ResonanceChannels:
        """
        The channel information
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
        The parity of the spin J
        """
    @property
    def spin(self) -> float:
        """
        The spin J of the spin group
        """
