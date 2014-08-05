/*
*
*  Copyright 2013 Mario Alviano, Carmine Dodaro, and Francesco Ricca.
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*/

#ifndef HCCOMPONENT_H
#define	HCCOMPONENT_H

#include <vector>
#include "util/Assert.h"
#include "stl/Vector.h"
#include "PostPropagator.h"
#include "Literal.h"
#include "Solver.h"
using namespace std;

class Clause;
class Learning;

class HCComponent : public PostPropagator
{
    public:
        HCComponent( vector< GUSData* >& gusData_, Solver& s );
        ~HCComponent();

        virtual void reset();

        virtual Clause* getClauseToPropagate( Learning& learning );
        virtual bool onLiteralFalse( Literal literal );

        void addClauseToChecker( Clause* c, Var headAtom );        
        
        inline void addHCVariable( Var v ) { hcVariables.push_back( v ); }
        inline void addExternalLiteral( Literal lit ) { externalLiterals.push_back( lit ); }
        
        inline unsigned int size() const { return hcVariables.size(); }
        inline Var getVariable( unsigned int pos ) const { assert( pos < hcVariables.size() ); return hcVariables[ pos ]; }
        
        inline unsigned int externalLiteralsSize() const { return externalLiterals.size(); }
        inline Literal getExternalLiteral( unsigned int pos ) const { assert( pos < externalLiterals.size() ); return externalLiterals[ pos ]; }
        
        void computeReasonForUnfoundedAtom( Var v );
        
        GUSData& getGUSData( Var v ) { assert( v < gusData.size() ); return *( gusData[ v ] ); }

    private:
        inline HCComponent( const HCComponent& orig );

        bool isInUnfoundedSet( Var v ) { assert( v < inUnfoundedSet.size() ); return inUnfoundedSet[ v ] == numberOfCalling; }
        void setInUnfoundedSet( Var v ) { assert( v < inUnfoundedSet.size() ); inUnfoundedSet[ v ] = numberOfCalling; }
        
        vector< GUSData* >& gusData;
        Vector< Literal > trail;
        Solver& solver;
        Solver checker;

        vector< Var > hcVariables;
        vector< Literal > externalLiterals;
        Vector< Var > unfoundedSet;
        
        Vector< unsigned int > inUnfoundedSet;
        unsigned int numberOfCalling;
        bool first;

        void testModel();
        void computeAssumptions( vector< Literal >& assumptionsAND, vector< Literal >& assumptionsOR );                
};

#endif