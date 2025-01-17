> [!NOTE]
> When using this software please cite following article:
> Jan Wilhelm Gärtner, Ali Shamooni, Thorsten Zirwes, Andreas Kronenburg,
> "A Chemistry Load Balancing Model for OpenFOAM", *Computer Physics Communications*,
> 2024, doi: 10.1016/j.cpc.2024.109322.

---

# Load Balanced Chemistry Model 

This library provides a load-balanced standard and TDAC chemistry model 
for OpenFOAM v2306. This library works with every OpenFOAM solver that uses
the BasicChemistryModel of OpenFOAM. There are currently no known solvers which
are not supported by this library.

## Supported OpenFOAM Versions

 * OpenFOAM v2312
 * OpenFOAM v2306
 * OpenFOAM v2212


## Compilation & Usage

To compile the library execute following steps:

 1. Execute the `./PrepareOpenFOAM.sh` script.
    This script will add the protected keyword to OpenFOAM's TDAC chemistry
    model. This is required to avoid significant code duplication and to use
    the TDAC member functions for the load-balanced TDAC model.
 2. Run the `./Allwmake` script. 
    This script accepts all arguments that you can pass to wmake. 
    E.g., to compile in parallel run `./Allwmake -j` for a debug compilation
    use `./Allwmake -debug`

### Usage

To select the load-balanced chemistry model, select it as the method in the 
chemistryProperties dictionary located in the constant folder and add the library
in your system/controlDict

**System Control Dictionary**
```c++
...
// Add the library to libs
libs
(
    "libloadBalancedChemistryModel.so"
);
```

**Constant Chemistry Properties Dictionary**
```c++
chemistryType
{
    solver            ode;
    method            LoadBalancedChemistryModel;
    // or for TDAC
    method            LoadBalancedTDAC;
}

// Optional Settings
LoadBalancedCoeffs
{
    updateIter  10; // Update the load balance every 10 time steps
                    // default value is every time step
}

// For the load-balanced TDAC model
LoadBalancedTDACCoeffs
{
    updateIter  10; // Update the load balance every 10 time steps
                    // default value is every time step
}
```

## Tutorial and Unit-Tests

The library is equipped with a unit-testing suite with the Catch2 framework. 
Further, one tutorial case of the counterflow 2D flame case of OpenFOAM using
the new load-balanced standard chemistry model is given in the tutorial/ 
directory.

### Unit-Tests

For detailed instructions about the unit-tests see the README in the tests/
directory.

### Tutorial

To run the tutorial navigate to the tutorial/counterFlowFlame2D case and 
execute:
```bash
blockMesh
decomposePar
mpirun -np 2 reactingFoam -parallel 
```

## License

This OpenFOAM library is under the GNU General Public License.


