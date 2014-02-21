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

#include "Component.h"


#include "Variable.h"
#include "Clause.h"
#include "Literal.h"
#include "util/VariableNames.h"

ostream& operator<<( 
    ostream& out,
    const Variable& var )
{
#ifndef NDEBUG    
    if( VariableNames::isHidden( &var ) )
        out << var.id;
    else
#endif
    out << VariableNames::getName( &var );
    return out;
}

Variable::~Variable()
{
//    if( heuristicCounters[ 0 ] )
//        delete heuristicCounters[ 0 ];
//    
//    if( heuristicCounters[ 1 ] )
//        delete heuristicCounters[ 1 ];
    if( definition )
        delete definition;
    
    if( signOfEliminatedVariable == ELIMINATED_BY_DISTRIBUTION )
    {
        for( unsigned int i = 0; i < numberOfOccurrences( POSITIVE ); i++ )
            delete getOccurrence( i, POSITIVE );
        
        for( unsigned int i = 0; i < numberOfOccurrences( NEGATIVE ); i++ )
            delete getOccurrence( i, NEGATIVE );
    }
}

//void
//Variable::setHeuristicCounterForLiterals( 
//    HeuristicCounterFactoryForLiteral* heuristicCounterFactoryForLiteral )
//{
//    heuristicCounters[ 0 ] = heuristicCounterFactoryForLiteral->createHeuristicCounter();
//    heuristicCounters[ 1 ] = heuristicCounterFactoryForLiteral->createHeuristicCounter();
//}

void
Variable::onLearning( 
    Learning* strategy )
{    
    //The implicant can be NULL if the literal is a choice.
    if( implicant != NULL )
    {
        implicant->onLearning( strategy );
    }
}

void
Variable::onLearningForUnfounded(
    Learning& learning )
{
    assert( component != NULL );
    component->onLearningForUnfounded( id, learning );
}