"""
MT4 - incoherent inelastic scattering
"""
from __future__ import annotations
import typing
__all__: list[str] = ['AnalyticalFunctions', 'EffectiveTemperature', 'ScatteringFunction', 'ScatteringLawConstants', 'Section', 'TabulatedFunctions']
class AnalyticalFunctions:
    """
    MF7 MT4 section - scattering law for the principal scatterer are
                      analytical functions
    """
    @typing.overload
    def __init__(self) -> None:
        """
        Initialise the component
        
        Arguments:
            self              the component
        """
    @typing.overload
    def __init__(self, component: AnalyticalFunctions) -> None:
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
class EffectiveTemperature:
    """
    MF7 MT4 section - effective temperatures for the short collision-time
                      approximation
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> EffectiveTemperature:
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
    def __init__(self, boundaries: list[int], interpolants: list[int], tmod: list[float], teff: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self            the component
            boundaries      the interpolation range boundaries
            interpolants    the interpolation types for each range
            tmod            the moderator temperature values
            teff            the effective temperature values
        """
    @typing.overload
    def __init__(self, component: EffectiveTemperature) -> None:
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
    def NT(self) -> int:
        """
        The number of temperatures
        """
    @property
    def TEFF(self) -> ...:
        """
        The effective temperature values
        """
    @property
    def TMOD(self) -> ...:
        """
        The moderator temperature values
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def effective_temperatures(self) -> ...:
        """
        The effective temperature values
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def moderator_temperatures(self) -> ...:
        """
        The moderator temperature values
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
    def number_temperatures(self) -> int:
        """
        The number of temperatures
        """
class ScatteringFunction:
    """
    MF7 MT4 section - S(alpha,beta,T) data for a fixed value of beta
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> ScatteringFunction:
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
    def __init__(self, temperature: float, beta: float, boundaries: list[int], interpolants: list[int], alphas: list[float], sab: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self            the component
            temperature     the temperature
            beta            the beta value for which data will be given
            boundaries      the interpolation range boundaries for S(a,beta)
            interpolants    the interpolation types for each range
            alphas          the alpha values (NA values)
            sab             the thermal scattering values (NA values)
        """
    @typing.overload
    def __init__(self, beta: float, boundaries: list[int], interpolants: list[int], temperatures: list[float], li: list[int], alphas: list[float], sab: list[list[float]]) -> None:
        """
        Initialise the component
        
        Arguments:
            self            the component
            beta            the beta value for which data will be given
            boundaries      the interpolation range boundaries for S(a,beta)
            interpolants    the interpolation types for each range
            temperatures    the temperatures (NT values)
            li              the temperature interpolation flags (NT-1 values)
            alphas          the alpha values (NA values)
            sab             the thermal scattering values (NT arrays of NA values)
        """
    @typing.overload
    def __init__(self, component: ScatteringFunction) -> None:
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
    def A(self) -> ...:
        """
        The alpha grid
        """
    @property
    def B(self) -> float:
        """
        The current beta value
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def LI(self) -> ...:
        """
        The temperature interpolation flags (LT values will be given)
        """
    @property
    def LT(self) -> int:
        """
        The LT flag indicating the temperature dependence (equal to NT - 1)
        """
    @property
    def NA(self) -> int:
        """
        The number of alpha values
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
    def NT(self) -> int:
        """
        The number of temperatures
        """
    @property
    def S(self) -> ...:
        """
        The thermal scattering law values as an array, one for each temperature
        """
    @property
    def T(self) -> ...:
        """
        The temperature values
        """
    @property
    def alphas(self) -> ...:
        """
        The alpha grid
        """
    @property
    def beta(self) -> float:
        """
        The current beta value
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def number_alphas(self) -> int:
        """
        The number of alpha values
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
    def number_temperatures(self) -> int:
        """
        The number of temperatures
        """
    @property
    def temperature_dependence_flag(self) -> int:
        """
        The LT flag indicating the temperature dependence (equal to NT - 1)
        """
    @property
    def temperature_interpolants(self) -> ...:
        """
        The temperature interpolation flags (LT values will be given)
        """
    @property
    def temperatures(self) -> ...:
        """
        The temperature values
        """
    @property
    def thermal_scattering_values(self) -> ...:
        """
        The thermal scattering law values as an array, one for each temperature
        """
class ScatteringLawConstants:
    """
    MF7 MT4 section - scattering law constants
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> ScatteringLawConstants:
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
    def __init__(self, lln: int, ns: int, epsilon: float, emax: float, xs: list[float], awr: list[float], natoms: list[int], types: list[int]) -> None:
        """
        Initialise the component
        
        Arguments:
            self       the component
            lln        the LLN flag - store S or ln(S)
            ns         the number non-principal scatterers
            epsilon    B(2) - the E/kT ratio
            emax       B(4) - the maximum energy
            xs         the total free atom cross section for each scatterer
                       (ns + 1 values)
            awr        the atomic weight ratios for each scatterer
                       (ns + 1 values)
            natoms     the number of atoms for each scatterer (ns + 1 values)
            types      the function type for each secondary scatterer
                       (ns values)
        """
    @typing.overload
    def __init__(self, lln: int, epsilon: float, emax: float, xs: float, awr: float, natoms: int) -> None:
        """
        Initialise the component
        
        Arguments:
            self       the component
            lln        the LLN flag - store S or ln(S)
            epsilon    B(2) - the E/kT ratio
            emax       B(4) - the maximum energy
            xs         B(1) - the total free atom cross section
            awr        B(3) - the atomic weight ratio in neutron mass units
            natoms     B(6) - the number of principal scatterer atoms
        """
    @typing.overload
    def __init__(self, component: ScatteringLawConstants) -> None:
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
    def AWR(self) -> ...:
        """
        The ratio of the atomic weight to the neutron mass for each scattering
        atom type, stored in B(3), B(9) and B(15)
        """
    @property
    def EMAX(self) -> float:
        """
        The upper energy limit of the thermal scattering law, stored in B(4)
        """
    @property
    def LLN(self) -> int:
        """
        The LLN flag (either S or ln(S) is stored)
        """
    @property
    def M(self) -> ...:
        """
        The number of atoms for each scattering atom type present in the
        molecule or unit cell, stored in B(6), B(12) and B(18)
        """
    @property
    def MSIGMA(self) -> ...:
        """
        The total free atom cross section for each scattering atom type, stored
        in B(1), B(8) and B(14)
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NI(self) -> int:
        """
        The size of the B array, equal to 6*(NS+1)
        """
    @property
    def NS(self) -> int:
        """
        The number of non-principal scattering atom types
        """
    @property
    def analytical_function_types(self) -> ...:
        """
        The analytical function type for each non-principal scattering atom
        type, stored in B(7), B(13) and B(19)
        """
    @property
    def atomic_weight_ratios(self) -> ...:
        """
        The ratio of the atomic weight to the neutron mass for each scattering
        atom type, stored in B(3), B(9) and B(15)
        """
    @property
    def epsilon(self) -> float:
        """
        The value of epsilon = E/kT, stored in B(2)
        """
    @property
    def number_atoms(self) -> ...:
        """
        The number of atoms for each scattering atom type present in the
        molecule or unit cell, stored in B(6), B(12) and B(18)
        """
    @property
    def number_constants(self) -> int:
        """
        The size of the B array, equal to 6*(NS+1)
        """
    @property
    def number_non_principal_scatterers(self) -> int:
        """
        The number of non-principal scattering atom types
        """
    @property
    def sab_storage_type(self) -> int:
        """
        The LLN flag (either S or ln(S) is stored)
        """
    @property
    def total_free_cross_sections(self) -> ...:
        """
        The total free atom cross section for each scattering atom type, stored
        in B(1), B(8) and B(14)
        """
    @property
    def upper_energy_limit(self) -> float:
        """
        The upper energy limit of the thermal scattering law, stored in B(4)
        """
class Section:
    """
    MF7 MT4 section - incoherent inelastic scattering
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
    def __init__(self, zaid: float, awr: float, lat: int, lasym: int, constants: ScatteringLawConstants, law: AnalyticalFunctions | TabulatedFunctions, principal: EffectiveTemperature, secondaries: list[EffectiveTemperature | None] = []) -> None:
        """
        Initialise the section using isotopes
        
        Arguments:
            self           the section
            zaid           the ZA value of the material
            awr            the atomic weight ratio
            lat            the temperature flag for alpha and beta grid
            lasym          the S(a,b) symmetry flag
            constants      the thermal scattering law constants
            law            the thermal scattering law
            principal      the effective temperature of the
                           principal scatterer
            secondaries    the effective temperature of the
                           secondary scatterers (if required)
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
    def LASYM(self) -> int:
        """
        The LASYM flag (S(alpha,beta) is symmetric or not)
        """
    @property
    def LAT(self) -> int:
        """
        The LAT flag (temperature flag for alpha and beta grid)
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
    def constants(self) -> ScatteringLawConstants:
        """
        The thermal scattering law constants for the principal and and secondary
        scatterers (if any)
        """
    @property
    def principal_effective_temperature(self) -> EffectiveTemperature:
        """
        The effective temperature for the principal scatterer
        """
    @property
    def scattering_law(self) -> AnalyticalFunctions | TabulatedFunctions:
        """
        The LTHR flag (coherent or incoherent elastic scattering)
        """
    @property
    def secondary_effective_temperatures(self) -> ...:
        """
        The effective temperatures for the secondary scatterers (if any are
        defined)
        """
    @property
    def section_number(self) -> int:
        """
        The MT number of the section
        """
    @property
    def symmetry_option(self) -> int:
        """
        The LASYM flag (S(alpha,beta) is symmetric or not)
        """
    @property
    def target_identifier(self) -> int:
        """
        The ZA identifier for the section
        """
    @property
    def temperature_option(self) -> int:
        """
        The LAT flag (temperature flag for alpha and beta grid)
        """
class TabulatedFunctions:
    """
    MF7 MT4 section - tabulated incoherent inelastic scattering law
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> TabulatedFunctions:
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
    def __init__(self, boundaries: list[int], interpolants: list[int], functions: list[..., ...]) -> None:
        """
        Initialise the component
        
        Arguments:
            self            the component
            boundaries      the interpolation range boundaries
            interpolants    the interpolation types for each range
            functions       the beta values and associated S(alpha,T) functions
        """
    @typing.overload
    def __init__(self, component: TabulatedFunctions) -> None:
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
    def B(self) -> ...:
        """
        The beta values
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def NB(self) -> int:
        """
        The number of beta values
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
    def NR(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def S(self) -> ...:
        """
        The beta values and associated S(alpha,T) functions
        """
    @property
    def betas(self) -> ...:
        """
        The beta values
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def number_betas(self) -> int:
        """
        The number of beta values
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def scattering_functions(self) -> ...:
        """
        The beta values and associated S(alpha,T) functions
        """
