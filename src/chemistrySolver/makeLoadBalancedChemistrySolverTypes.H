/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2017 OpenFOAM Foundation
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#ifndef makeLoadBalancedChemistrySolverTypes_H
#define makeLoadBalancedChemistrySolverTypes_H

#include "chemistrySolver.H"

#include "LoadBalancedChemistryModel.H"
#include "LoadBalancedTDACChemistryModel.H"

#include "noChemistrySolver.H"
#include "EulerImplicit.H"
#include "ode.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeLoadBalancedChemistrySolverType(SS, Comp, Thermo)                  \
                                                                               \
    typedef SS<LoadBalancedChemistryModel<Comp, Thermo>> SS##Comp##Thermo;     \
                                                                               \
    defineTemplateTypeNameAndDebugWithName                                     \
    (                                                                          \
        SS##Comp##Thermo,                                                      \
        (#SS"<" + word(LoadBalancedChemistryModel<Comp, Thermo>::typeName_())  \
        + "<" + word(Comp::typeName_()) + "," + Thermo::typeName()             \
        + ">>").c_str(),                                                       \
        0                                                                      \
    );                                                                         \
                                                                               \
    BasicChemistryModel<Comp>::                                                \
        add##thermo##ConstructorToTable<SS##Comp##Thermo>                      \
        add##SS##Comp##Thermo##thermo##ConstructorTo##BasicChemistryModel##Comp\
##Table_;                                                                      \
                                                                               \
    typedef SS<LoadBalancedTDACChemistryModel<Comp, Thermo>>                   \
        TDAC##SS##Comp##Thermo;                                                \
                                                                               \
    defineTemplateTypeNameAndDebugWithName                                     \
    (                                                                          \
        TDAC##SS##Comp##Thermo,                                                \
        (#SS"<"                                                                \
        + word(LoadBalancedTDACChemistryModel<Comp, Thermo>::typeName_()) + "<"\
        + word(Comp::typeName_()) + "," + Thermo::typeName() + ">>").c_str(),  \
        0                                                                      \
    );                                                                         \
                                                                               \
    BasicChemistryModel<Comp>::                                                \
        add##thermo##ConstructorToTable<TDAC##SS##Comp##Thermo>                \
        add##TDAC##SS##Comp##Thermo##thermo##ConstructorTo##BasicChemistryModel\
##Comp##Table_;


#define makeLoadBalancedChemistrySolverTypes(Comp, Thermo)                     \
                                                                               \
    makeLoadBalancedChemistrySolverType                                        \
    (                                                                          \
        noChemistrySolver,                                                     \
        Comp,                                                                  \
        Thermo                                                                 \
    );                                                                         \
                                                                               \
    makeLoadBalancedChemistrySolverType                                        \
    (                                                                          \
        EulerImplicit,                                                         \
        Comp,                                                                  \
        Thermo                                                                 \
    );                                                                         \
                                                                               \
    makeLoadBalancedChemistrySolverType                                        \
    (                                                                          \
        ode,                                                                   \
        Comp,                                                                  \
        Thermo                                                                 \
    );                                                                         \


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
