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

#include "ExternalPropagator.h"
#include "heuristic/interpreters/Interpreter.h"
#include "Literal.h"
#include "stl/Vector.h"
#include "Solver.h"
#include "Clause.h"
#include "heuristic/interpreters/MyPerlInterpreter.h"
#include "heuristic/interpreters/MyPythonInterpreter.h"

ExternalPropagator::~ExternalPropagator()
{
    delete interpreter;
    delete fn;
    clearClausesToDelete();
}

ExternalPropagator::ExternalPropagator( 
    const string& filename,
    unsigned int interpr,
    Solver& solver,
    string scriptDirectory ) : Propagator()
{
    fn = new char[ filename.length() + 1 ];
    strcpy( fn, filename.c_str() );
    interpreter = NULL;
    
    if( interpr == PYTHON_INTERPRETER )
        interpreter = new MyPythonInterpreter( fn, scriptDirectory );
    else if( interpr == PERL_INTERPRETER )
        interpreter = new MyPerlInterpreter( fn, scriptDirectory );
    else
        ErrorMessage::errorGeneric( "Unsupported interpreter" );
    check_addedVarName = interpreter->checkMethod( method_plugins_addedVarName );
    check_onAtomElimination = interpreter->checkMethod( method_plugins_onVariableElimination );
    check_simplifyAtLevelZero = interpreter->checkMethod( method_plugins_simplifyAtLevelZero );
    check_onAnswerSet = interpreter->checkMethod( method_plugins_onAnswerSet );
    
    check_checkAnswerSet = interpreter->checkMethod( method_plugins_checkAnswerSet );
    check_getReasonForCheckFailure = interpreter->checkMethod( method_plugins_getReasonForCheckFailure );
    check_onNewLowerBound = interpreter->checkMethod( method_plugins_foundLB );
    check_onNewUpperBound = interpreter->checkMethod( method_plugins_foundUB );
    check_onLitsTrue = interpreter->checkMethod( method_plugins_onLitsTrue );
    check_onLitTrue = interpreter->checkMethod( method_plugins_onLitTrue );
    check_addClauseFromCheckFailure = interpreter->checkMethod( method_plugins_addClauseFromCheckFailure );
    checkWellFormed();
    
    if( check_onLitsTrue )
        solver.addPropagatorAfterUnit( this );
    
    if( check_checkAnswerSet )
        solver.addPropagatorAttachedToCheckAnswerSet( this );
    
    if( check_onNewLowerBound || check_onNewUpperBound )
        solver.addPropagatorAttachedToBounds( this );
}

bool
ExternalPropagator::onLiteralFalse(
    Solver& solver,
    Literal literal,
    int )
{
    vector< int > output;
    if( check_onLitsTrue )
    {
        trueLiterals.push_back( literal.getOppositeLiteral() );
        return true;
    }
    assert( check_onLitTrue );
    interpreter->callListMethod( method_plugins_onLitTrue, literal.getOppositeLiteral().getId(), solver.getCurrentDecisionLevel(), output );    
    //True literals are stored in the trail
    if( solver.getCurrentDecisionLevel() > 0 )
    {
        assert( !trail.existElement( literal.getOppositeLiteral() ) );
        trail.push_back( literal.getOppositeLiteral() );
    }
    
    computeReason( solver, output );
    return true;
}

void
ExternalPropagator::reset(
    const Solver& solver )
{
    if( solver.getCurrentDecisionLevel() == 0 )
        clearClausesToDelete();
    trueLiterals.clear();
    vector< int > parameters;
    parameters.push_back( solver.getCurrentDecisionLevel() );
    while( !trail.empty() )
    {
        Literal lit = trail.back();
        if( !solver.isUndefined( lit ) )
            break;
        parameters.push_back( lit.getId() );
        trail.pop_back();
    }
    
    if( !parameters.empty() )
       interpreter->callVoidMethod( method_plugins_onLiteralsUndefined, parameters );    
}

void
ExternalPropagator::attachWatches(
    Solver& solver )
{
    if( interpreter->checkMethod( method_plugins_getLiterals ) )
    {
        vector< int > input;
        assert( solver.getCurrentDecisionLevel() == 0 );
        input.push_back( solver.numberOfVariables() );
        for( unsigned int i = 1; i <= solver.numberOfVariables(); i++ )
        {
            if( solver.isUndefined( i ) )
                continue;
            input.push_back( solver.isTrue( i ) ? i : -i );            
        }

        vector< int > output;
        interpreter->callListMethod( method_plugins_getLiterals, input, output );
        for( unsigned int i = 0; i < output.size(); i++ )
        {
            checkIdOfLiteral( solver, output[ i ] );
            Literal lit = Literal::createLiteralFromInt( output[ i ] );
            solver.setFrozen( lit.getVariable() );
            solver.addPropagator( lit.getOppositeLiteral(), this, i );
        }
    }
    if( interpreter->checkMethod( method_plugins_getVariablesToFreeze ) )
    {
        vector< int > output;
        interpreter->callListMethod( method_plugins_getVariablesToFreeze, output );
        for( unsigned int i = 0; i < output.size(); i++ )
        {
            checkIdOfLiteral( solver, output[ i ] );
            Literal lit = Literal::createLiteralFromInt( output[ i ] );
            solver.setFrozen( lit.getVariable() );
        }
    }
}
void
ExternalPropagator::checkWellFormed(
    const string& method )
{
   if( !interpreter->checkMethod( method ) )
        ErrorMessage::errorGeneric( "Method " + method + " is required." ); 
}

void
ExternalPropagator::checkWellFormed()
{
//    checkWellFormed( method_plugins_getLiterals );
//    checkWellFormed( method_plugins_getReason );
//    checkWellFormed( method_plugins_getVariablesToFreeze );
//    checkWellFormed( method_plugins_onLiteralsUndefined );
    if( !check_checkAnswerSet && ( ( check_onLitTrue && check_onLitsTrue ) || ( !check_onLitTrue && !check_onLitsTrue ) ) )
        ErrorMessage::errorGeneric( "If " + string( method_plugins_checkAnswerSet ) + " is not used then exactly one method between " + string( method_plugins_onLitTrue ) + " and " +  string( method_plugins_onLitsTrue ) + " is required." );
    
    if( ( check_onLitTrue || check_onLitsTrue ) && 
        ( !interpreter->checkMethod( method_plugins_getReason ) || !interpreter->checkMethod( method_plugins_getLiterals ) || !interpreter->checkMethod( method_plugins_onLiteralsUndefined ) ) )
        ErrorMessage::errorGeneric( "If " + string( method_plugins_onLitTrue ) + " or " + string( method_plugins_onLitsTrue ) + " are used then " + 
                                    string( method_plugins_getReason ) + ", " + 
                                    string( method_plugins_getLiterals ) + ", and " + 
                                    string( method_plugins_onLiteralsUndefined ) + " are required." );
    if( ( check_checkAnswerSet && !check_getReasonForCheckFailure ) || ( !check_checkAnswerSet && check_getReasonForCheckFailure ) )
        ErrorMessage::errorGeneric( "Method " + string( method_plugins_getReasonForCheckFailure ) + " is required when " +  string( method_plugins_checkAnswerSet ) + " is used." );
    
    if( !check_checkAnswerSet && check_addClauseFromCheckFailure )
        ErrorMessage::errorGeneric( "Method " + string( method_plugins_addClauseFromCheckFailure ) + " can be defined only if " +  string( method_plugins_checkAnswerSet ) + " is used." );
}

Clause*
ExternalPropagator::getReason(
    Solver& solver )
{
    vector< int > output;
    interpreter->callListMethod( method_plugins_getReason, output );
    if( output.empty() )
    {
        solver.unrollToZero();
        return NULL;
    }
    Clause* clause = new Clause();
    clause->addLiteral( Literal::null );
    unsigned int max = 0;    
    for( unsigned int i = 0; i < output.size(); i++ )
    {
        checkIdOfLiteral( solver, output[ i ] );
        Literal l = Literal::createLiteralFromInt( output[ i ] );
        clause->addLiteral( l );        
        unsigned int dl = solver.getDecisionLevel( l );
        if( dl > max )
            max = dl;
    }
    
    if( max < solver.getCurrentDecisionLevel() )
        solver.unroll( max );
    
    unsigned int countUndefined = 0;
    for( unsigned int i = 1; i < clause->size(); i++ )
        if( solver.isUndefined( clause->getAt( i ) ) )
            countUndefined++;

    if( countUndefined != 0 )
        ErrorMessage::errorGeneric( "Reason is not well-formed" );
    reset( solver );
    return clause;
}

Clause*
ExternalPropagator::getReasonForCheckerFailureInternal(
    Solver& solver )
{
    vector< int > output;
    interpreter->callListMethod( method_plugins_getReasonForCheckFailure, output );
    if( output.empty() )
    {
        solver.unrollToZero();
        return NULL;
    }
    Clause* clause = new Clause();
    for( unsigned int i = 0; i < output.size(); i++ )
    {
        checkIdOfLiteral( solver, output[ i ] );
        Literal l = Literal::createLiteralFromInt( output[ i ] );
        clause->addLiteral( l );
    }
    if( clause->size() >= 2 )
        Learning::sortClause( clause, solver );
    
    return clause;
}


void
ExternalPropagator::clearClausesToDelete()
{
    for( unsigned int i = 0; i < clausesToDelete.size(); i++ )
        delete clausesToDelete[ i ];
    clausesToDelete.clear();
}

void
ExternalPropagator::addedVarName(
    Var var,
    const string& name )
{
    if( check_addedVarName )
        interpreter->callVoidMethod( method_plugins_addedVarName, var, name );
}

void
ExternalPropagator::onAtomElimination(
    Var var )
{
    if( check_onAtomElimination )
        interpreter->callVoidMethod( method_plugins_onVariableElimination, var );
}

void
ExternalPropagator::simplifyAtLevelZero(
    Solver& solver )
{
    if( check_simplifyAtLevelZero )
    {
        assert( solver.getCurrentDecisionLevel() == 0 );
        vector< int > output;
        interpreter->callListMethod( method_plugins_simplifyAtLevelZero, output );
        for( unsigned int i = 0; i < output.size(); i++ )
        {
            checkIdOfLiteral( solver, output[ i ] );
            if( !solver.addClause( Literal::createLiteralFromInt( output[ i ] ) ) )
                break;
        }
    }
}

void ExternalPropagator::onAnswerSet(
    const Solver& solver )
{
    if( check_onAnswerSet )
    {
        vector< int > answerset;
        answerset.push_back( 0 );
        for( unsigned int i = 1; i <= solver.numberOfVariables(); i++ )
        {
            assert( !solver.isUndefined( i ) );
            if( solver.isTrue( i ) )
                answerset.push_back( i );
            else
                answerset.push_back( -i );
        }        
        interpreter->callVoidMethod( method_plugins_onAnswerSet, answerset );
    }
}

void ExternalPropagator::checkIdOfLiteral(
    const Solver& solver,
    int id ) const
{
    Var var = id > 0 ? id : -id;
    if( var == 0 || var > solver.numberOfVariables() )
        ErrorMessage::errorGeneric( "Variable " + to_string( var ) + " does not exist." );
}

void ExternalPropagator::foundLowerBound(
    uint64_t lb )
{
    if( check_onNewLowerBound )
        interpreter->callVoidMethod( method_plugins_foundLB, lb );    
}

void ExternalPropagator::foundUpperBound(
    uint64_t ub )
{
    if( check_onNewUpperBound )
        interpreter->callVoidMethod( method_plugins_foundUB, ub );
}

bool ExternalPropagator::checkAnswerSet( Solver& solver )
{
    bool retValue = true;
    if( check_checkAnswerSet )
    {
        vector< int > answerset;
        answerset.push_back( 0 );
        for( unsigned int i = 1; i <= solver.numberOfVariables(); i++ )
        {
            assert( !solver.isUndefined( i ) );
            if( solver.isTrue( i ) )
                answerset.push_back( i );
            else
                answerset.push_back( -i );
        }
        retValue = interpreter->callIntMethod( method_plugins_checkAnswerSet, answerset ) != 0;
    }
    return retValue;
}

Clause* ExternalPropagator::getReasonForCheckFailure(
    Solver& solver )
{
    assert( check_getReasonForCheckFailure );
    Clause* reason = getReasonForCheckerFailureInternal( solver );
    if( reason && !hasToAddClauseFromCheckFailure() && reason->size() >= 2 )
        clausesToDelete.push_back( reason );
    if( reason && hasToAddClauseFromCheckFailure() && reason->size() >= 2 )
    {
        reason->setLbd( solver.computeLBD( *reason ) );
        reason->setLearned();
    }
    return reason;
}

bool ExternalPropagator::hasToAddClauseFromCheckFailure()
{
    return check_addClauseFromCheckFailure;
}

void ExternalPropagator::endUnitPropagation(
    Solver& solver )
{
    assert( check_onLitsTrue );
    assert( !check_onLitTrue );
    vector< int > input;
    vector< int > output;
    input.push_back( solver.getCurrentDecisionLevel() );
    for( unsigned int i = 0; i < trueLiterals.size(); i++ )
    {
        assert( solver.isTrue( trueLiterals[ i ] ) );
        //True literals are stored in the trail
        if( solver.getCurrentDecisionLevel() > 0 )
            trail.push_back( trueLiterals[ i ] );
        input.push_back( trueLiterals[ i ].getId() );
    }
    interpreter->callListMethod( method_plugins_onLitsTrue, input, output );
    trueLiterals.clear();
    computeReason( solver, output );    
}

void ExternalPropagator::computeReason(
    Solver& solver,
    vector< int > output )
{
    if( output.empty() || ( output.size() == 1 && output[ 0 ] == 0 ) )
        return;
    
    Clause* reason = getReason( solver );
    //TODO: check for backjumping
    for( unsigned int i = 0; i < output.size(); i++ )
    {
        checkIdOfLiteral( solver, output[ i ] );
        Literal lit = Literal::createLiteralFromInt( output[ i ] );
        if( solver.isTrue( lit ) )
            continue;
        
//        //Literals inferred from the propagators are stored
//        trail.push_back( lit );
        solver.assignLiteral( lit, reason );
    }
    clausesToDelete.push_back( reason );
    return;
}

void ExternalPropagator::onStartingSolver()
{
    if( interpreter->checkMethod( method_plugins_onStartingSolver ) )
        interpreter->callVoidMethod( method_plugins_onStartingSolver );
}