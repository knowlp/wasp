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
#include "ThirdCompetitionOutputBuilder.h"

#include "../PositiveLiteral.h"

void
ThirdCompetitionOutputBuilder::startModel()
{
    cout << ANSWER_THIRD_COMPETITION << endl;
}

void
ThirdCompetitionOutputBuilder::printLiteral(
    PositiveLiteral* positiveLiteral )
{
    if( positiveLiteral->isTrue() )
    {
        cout << *positiveLiteral << ". ";
    }
}

void
ThirdCompetitionOutputBuilder::endModel()
{
    cout << endl;
}

void
ThirdCompetitionOutputBuilder::onProgramIncoherent()
{
    cout << NOMODEL_COMPETITION_OUTPUT << endl;
}