reason = []
answer = []

def checkAnswerSet(*answer_set):
    global answer
    #Check whether the answer set has exactly two atoms true
    count = 0
    for i in range(2,6):
        if answer_set[i] > 0:
            count = count+1
    if count != 2:
        answer = answer_set
        return 0
    return 1

def getReasonForCheckFailure():
    #In case of failure compute the clause
    global answer
    output = []
    for i in range(2,6):
        if answer[i] > 0:
            output.append(-i)
        else:
            output.append(i)
    return output

def storeClauseFromCheckFailure():
    #Store the clauses produced
    pass