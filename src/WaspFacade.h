/*
 *
 *  Copyright 2013 Mario Alviano, Carmine Dodaro, Wolfgang Faber, Nicola Leone, Francesco Ricca, and Marco Sirianni.
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

/* 
 * File:   WaspFacade.h
 * Author: Carmine Dodaro
 *
 * Created on 21 July 2013, 17.00
 */

#ifndef WASPFACADE_H
#define	WASPFACADE_H

#include <cassert>
using namespace std;

#include "Constants.h"
#include "Solver.h"
#include "input/Dimacs.h"
#include "inputBuilders/SATFormulaBuilder.h"

class WaspFacade
{
    public:
        inline WaspFacade();
        inline ~WaspFacade();
        
        void readInput();
        void solve();
        
        void setDeletionPolicy( DELETION_POLICY );
        void setHeuristicPolicy( HEURISTIC_POLICY, unsigned int heuristicLimit );
        void setOutputPolicy( OUTPUT_POLICY );
        void setRestartsPolicy( RESTARTS_POLICY, unsigned int threshold );

        inline void setMaxModels( unsigned int max );
        inline void setPrintProgram( bool printProgram );        
        
    private:
        Solver solver;
        unsigned int numberOfModels;
        unsigned int maxModels;
        bool printProgram;
};

WaspFacade::WaspFacade() : numberOfModels( 0 ), maxModels( 1 ), printProgram( false )
{
}

WaspFacade::~WaspFacade()
{
}

void
WaspFacade::setMaxModels(
    unsigned int max )
{
    maxModels = max;
}

void
WaspFacade::setPrintProgram(
    bool print )
{
    printProgram = print;
}

#endif	/* WASPFACADE_H */