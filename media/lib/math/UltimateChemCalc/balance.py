#Utilize sympy for creating
#the matrices used within the
#chemical equation balancer
import sympy
#
#use the string module
#in order to get a list of
#all ascii_letters for the
#chemical equation balancer
import string


#Purpose: The purpose of the balance.py file is to provide other developers functionality that will
#         balance a given chemical equation.

#Functionality: In order to successfully balance a chemical equation, deveopers must call the function
#               getEquation(); upon calling it, the program will prompt the user for a chemical equation.
#               One big rule that must always be followed is that no spaces can in between elements that form
#               a molecule, but spaces can be in between the symbols that join the reactants and products. For example
#               H2+O2->H2O can also be represented with spaces as: H2 + O2 -> H2O, but not as H2 + O 2 -> H2 O.
#               After the equation is provided as input, it is handed to the balanceEquation(equation) function
#               and thoroughly analyzed for errors before being broken down into a system of linear equations
#               that when solved, will provide the coefficients needed to balance the equation.



#notAppended() serves the same purpose                                                                                  
#as Notcontains2(), only it doesn't accept                                                                              
#parameters and is ONLY used within the                                                                                
#chemical equation balancing functions.                                                                                 
def notAppended(arrName,sub):

    for rt in arrName:
        if(rt == sub):
            return 0
        
    #no match was made                      
    return 1



#alphaInLine() checks a string
#for a presence of any letters.
def alphaInLine(line):
    for x in line:
        if(x.isalpha()):
            return 1
    return 0

#The Notcontains2() function is used 
#within the chemicalEquation function to check
#if a selected element symbol is within the arrName2
#history list.              
def Notcontains2(component, data):
    for g in data:
        if(g == component):
            return 0

    #if data does not contain component
    #return 1 to proceed with row incrementing
    return 1






#The EquationWrong() function is responsible for
#returning an error code should the chemical equation
#within the equation text box have the wrong format.
def EquationWrong(equation):

    #initialize sub and arrName variables
    sub = ""
    arrName = []

    #get contents of text box
    chem = equation

    #Make sure + and -> components have a presence.
    #If not, immediately return an error code.
    if(not('+' in chem and '->' in chem)):
        return -2,None


    #Make sure there isn't more than one reaction symbol: ->
    #Perform a splice right after the first -> and see if another -> is present
    #in the second substring. If so, immediately return an error code.
    if(chem.index('->') + 2 < len(chem)):
        splice = chem[chem.index('->') + 2:len(chem)]
        if('->' in splice):
            return -3,None


    #Check for appropriate pairing/contents of parentheses if present. If
    #the contents or pairing is flawd, return an error code.
    code = BracketParentheseMatch(chem,'(',')')
    if(code != 0):
        return code,None

    #Check for appropriate pairing/contents/position of brackets if present.
    #If the pairing, contents, or positioning is wrong, return an error code.
    code = BracketParentheseMatch(chem,'[',']')
    if(code != 0):
        return code,None




    #bare bones equation must contain no coefficients,lone partial segments, or sequential +/-/> characters
    for BonJovie in range(len(chem)):

        #The very first element cannot be a digit, '-' or '>' character, and cannot be a '+' character
        if((chem[BonJovie].isdigit() or chem[BonJovie] == '-' or chem[BonJovie] == '>' or chem[BonJovie] == '+') and BonJovie == 0):
            return -1,None

        #The equation cannot end with a '+'
        elif(chem[BonJovie] == '+' and (BonJovie + 1 == len(chem))):
            return -1,None

        #The equation cannot have an inappropriate placement of +,-,> characters or inappropriate placement of coefficients
        elif(chem[BonJovie] == '+' and (chem[BonJovie + 1] == '+' or chem[BonJovie + 1].isdigit() or chem[BonJovie + 1] == '-' or chem[BonJovie + 1] == '>')):
            if(not('[' in chem and chem[BonJovie - 1] == '[')):
                return -1,None

        #The equation cannot end with a '-'
        elif(chem[BonJovie] == '-' and (BonJovie + 1 == len(chem))):
            return -1,None

        #The equation cannot have an inappropriate placement of +,-,> characters or inappropriate placement of coefficients
        elif(chem[BonJovie] == '-' and (chem[BonJovie + 1] == '+' or chem[BonJovie + 1].isdigit() or chem[BonJovie + 1] == '-' or chem[BonJovie + 1].isalpha())):
            if(not('[' in chem and chem[BonJovie - 1] == '[')):
                return -1,None

        #The equation cannot end with a > character
        elif(chem[BonJovie] == '>' and (BonJovie + 1 == len(chem))):

            #If the previous character is a '-' character
            #return the '1' error code
            if(chem[BonJovie - 1] == '-'):
                return 1,None

            #return the -1 error code
            return -1,None
        
        #If the current character is '>' and there is not a '-'
        #character before it, return a -1 error code
        elif(chem[BonJovie] == '>' and (chem[BonJovie - 1] != '-')):
            return -1,None



    #if all is good so far, loop through all elements with counter
    countMe = 0


    #all reactants elements...                                                                                 
    reactant = []

    #all product elements...                                                                                   
    product = []

    #indicator that the '->' symbol                                                                            
    #has been passed by the for loop...                                                                        
    dashA = False
    
    #loop through and put together a list of elements 
    for k in chem:

        #only take interest if the current character represents a letter
        if(k.isalpha()):

            #if the character is an upper case letter and the current
            #length of the sub string variable is 0, append the letter to
            #to the sub variable.
            if(k.isupper() and len(sub) == 0):

                #append the upper case character to the sub variable
                sub += k

                #if the next element isn't a lower case letter, then an element has just been appended to the
                #sub variable. Check if the lement has already been appended to arrName...if not, append it...
                #if yes, then ignore it. 
                if((countMe + 1 == len(chem) or not(chem[countMe + 1].islower()))):

                    #check to see if the element is unique...if so, append
                    #it to the arrName structure... (which will be used for
                    #deciding how many equations will be needed during the
                    #balancing process)
                    if(notAppended(arrName,sub)):
                        arrName.append(sub)

                    #if the symbol '->' has be passed...                                                       
                    if(dashA == True and not(sub in product)):

                        #append to product...                                                                  
                        product.append(sub)

                    #if the symbol -> hasn't been passed...                                                    
                    elif(not(sub in reactant)):

                        #append to reactants...                                                                
                        reactant.append(sub)

                    #when finished appending to arrName, clear the sub
                    #variable
                    sub = ""

                #if the current letter isn't a part of a two letter element symbol and is already appended
                #to the arrName list, erase the sub variable...
                elif((countMe + 1 == len(chem) or not(chem[countMe + 1].islower())) and not(notAppended(arrName,sub))):

                    #erase the sub variable by resetting to an empty string...
                    sub = ""

            #if the current character is a lowercase letter and the
            #lenth of the sub variable is equal to one (meaning an upper case letter is
            #already stored in it), then a full element has just been come across; the lower case
            #letter should be concatenated to the end of the sub variable and then the sub variable
            #should be appended to arrName if it's not already present...
            elif(k.islower() and len(sub) == 1):

                #concatenate the lower case letter to the end of sub
                sub += k

                #check if the current element is already within arrName
                if(notAppended(arrName,sub)):

                    #append sub to arrName if not present
                    #within arrName already
                    arrName.append(sub)

                #if the symbol '->' has be passed...                                                       
                if(dashA == True and not(sub in product)):

                    #append to product...                                                                  
                    product.append(sub)

                #if the symbol -> hasn't been passed...                                                    
                elif(not(sub in reactant)):

                    #append to reactants...                                                                
                    reactant.append(sub)

                #after appending, clear the sub variable
                sub = ""

            #If the current letter is lower case and the sub variable
            #has a length of zero, return an error code since no element
            #begins with a lower case letter.
            elif(k.islower() and len(sub) == 0):

                #clear arrName for the next attempt
                arrName = []

                #return error code three
                return 3,None

        #if a component of '->' is met...                                                                  
        elif(countMe+1 != len(chem) and k == '-' and chem[countMe + 1] == '>'):

            #set dash to true...                                                                           
            dashA = True

        #increment countMe, which acts
        #as an index in each iteration
        countMe = countMe + 1

        
    #check to see if the equation is valid based on the elements...                                            
    if(len(product) != len(reactant)):

        #return error code 12                                                                                  
        return 12,None

    else:

        #check all elements to see if they match...                                                            
        for x in reactant:

            #check to see if x is in product...                                                                
            if(not(x in product)):

                #return error code 12 if x is not in product...                                                
                return 12,None
    
    #no errors found
    return 0,arrName



#BracketPareentheseMatch ensures that all of the brackets and parenthesis within
#the equation match. If not, an error code is returne...
def BracketParentheseMatch(chemLine,left,right):

    #check for proper parentheses usage by utilizing the
    #following variables to make sure the same number of each
    #parenthesis/bracket type are used...
    SamWinchester = 0
    DeanWinchester = 0

    #first check if potential pairs are present
    if(right in chemLine and not(left in chemLine)):
        return 2
    elif(left in chemLine and not(right in chemLine)):
        return 2

    #Enter this block if a right and left form of bracket/parenthesis
    #were found within the chemLine. Now additional analysis in the form
    #of the number of each type needs to be performed...
    elif(left in chemLine and right in chemLine):

        #check for same number of parentheses of each type
        for x in chemLine:
            if(x == left):
                SamWinchester = SamWinchester + 1
        for x in chemLine:
            if(x == right):
                DeanWinchester = DeanWinchester + 1

        #if both variabes used above do not equal each other,
        #return error code two
        if(SamWinchester != DeanWinchester):
            return 2

        #if the same number of parenthesis for each type are found,
        #make sure pairing is done correctly...
        else:

            #check for appropriate pairing of parentheses/brackets
            #by utilizing the one/two variables
            one = 0
            two = 0

            #perform the check for appropriate parenthesis/bracket
            #pairing
            for x in chemLine:
                if(x == right or x == left):
                    if(x == left and one == 0):
                        one = 2
                    elif(x == right and one != 0 and two == 0):
                        two = 2
                    else:
                        return 2
                    if(one != 0 and two != 0):
                        one = 0
                        two = 0


    #check for proper contents of the brackets/parentheses
    #first get index values for all left and right components
    indecesL = []
    indecesR = []

    #get the index values of the brackets/parentheses
    for s in range(len(chemLine)):
        if(chemLine[s] == left):
            indecesL.append(s)
        elif(chemLine[s] == right):
            indecesR.append(s)

    #second, start pulling substrings that are within the brackets/parentheses
    #and start searching the contents!

    #The error code to be returned is initialy assigned
    #the value None...
    num = None

    #Brackets are associated with the error code
    #five and parentheses are associated with the error code
    #seven...
    if(left == '('):
        num = 5
    else:
        num = 7

    #perform the process of pulling substrings contained within the brackets/parentheses
    #and searching for appropriate content...
    for x in range(len(indecesL)):

        #Pull a substring from the first set of parentheses/brackets...
        CaptJackSparrow = chemLine[indecesL[x] + 1: indecesR[x]]
        if('>' in CaptJackSparrow):
            return num

        #special case number 1 (user forgets to give input to parenthese or bracket pairs)
        elif(CaptJackSparrow == ""):

            #return error code nine if no contents for a pair or pairs of parentheses
            #was given...
            if(left == '('):
                return 9

            #return error code eleven if no conetents for a pair or pairs of brackets
            #was given...
            else:
                return 11

        #The very first element within a pair of brackets or parentheses should
        #not be a digit...
        elif(CaptJackSparrow[0].isdigit()):
            return num

        #The '-' character cannot be within a set of
        #parentheses
        elif('-' in CaptJackSparrow and right == '('):
            return num

        #The '+' character cannot be within a set of
        #parentheses
        elif('+' in CaptJackSparrow and right == '('):
            return num

        #special case number 2: The user ends the equation right after a right parenthese or forgets to put
        #a subscript right after a right parenthese, throw error code ten...
        elif(right == ')' and not(indecesR[x] + 1 != len(chemLine) and chemLine[indecesR[x] + 1].isdigit())):
            return 10

        #If brackets occur within a set of parentheses, throw error code num...
        elif(('[' in CaptJackSparrow or ']' in CaptJackSparrow) and right == '('):
            return num

        #If parentheses occur within a set of brackets, throw error code num...
        elif(('(' in CaptJackSparrow or ')' in CaptJackSparrow) and right == '['):
            return num

        #Letters cannot occur within brackets, only charges (digits) and the '+'
        #character or '-' character. If letters are present, throw error code num...
        elif(right == ']' and alphaInLine(CaptJackSparrow)):
            return num

        #Make sure that '-' is used correctly within brackets
        elif('-' in CaptJackSparrow and right == '['):

            #If the previous character is a left bracket and the right character is a digit, then so far, '-' is being used
            #correctly; perform further analysis. If not, immediately return error code num...
            if(CaptJackSparrow[CaptJackSparrow.index('-') - 1] == '[' and CaptJackSparrow[CaptJackSparrow.index('-') + 1].isdigit()):

                #Get the substring that goes from the righ digit element to the end of the current substring to
                #make sure that only digits are used.
                AlexRusso = CaptJackSparrow[CaptJackSparrow.index('-') + 1:]

                #If '-' appears again or '('/'+' appears, throw error code num...
                if('-' in AlexRusso or '(' in AlexRusso or '+' in AlexRusso):
                    return num

            #return error code num if the first condition was not met.
            else:
                return num

        #Make sure that '+' is used correctly within the brackets...
        elif('+' in CaptJackSparrow and right == '['):

            #If the previous character is a left bracket and the right character is a digit, then so far, '-' is being used
            #correctly; perform further analysis. If not, immediately return error code num...
            if(CaptJackSparrow[CaptJackSparrow.index('+') - 1] == '[' and CaptJackSparrow[CaptJackSparrow.index('+') + 1].isdigit()):

                #Get the substring that goes from the righ digit element to the end of the current substring to
                #make sure that only digits are used.
                MaxRusso = CaptJackSparrow[CaptJackSparrow.index('+') + 1:]

                #If '+' appears again or '-'/'(' appears, throw error code num...
                if('-' in MaxRusso or '(' in MaxRusso or '+' in MaxRusso):
                    return num

            #return error code num if the first condition was not met...
            else:
                return num




    #Check for appropriate positioning of paired brackets (if present)
    #use the indecesL and indecesR variables from above

    #first retrieve the correct error numbers
    if(left == '['):

        #Assign the error code that will be used when an error is confronted.
        #Like in this case, and above in some areas, a variable did not have to be used,
        #but it made the development process a lot easier while trying different layouts and modifying
        #certain areas that weren't working. For instance, rather than having to re-type various number codes
        #for different segments that might have to be re-done (if there is a faulty segment) just assign the numbers
        #to a variable, based on what is being tested, at the biginning and use the same variable throughout.
        num = 8

        #Loop through all parenthese/bracket pairs
        for x in range(len(indecesL)):

            #1. The first element of the chemical equation cannot be a bracket or parenthese.
            #2. A bracket or parenthese cannot come right after a '>', '+', or '-' character.
            #If any of these conditions are met, return the num error code...
            if(indecesL[x] == 0 or chemLine[indecesL[x] - 1] == '>' or chemLine[indecesL[x] - 1] == '+' or chemLine[indecesL[x] - 1] == '-'):
                return num

            #If the bracket is followed by a digit, letter, or '>' character, throw the num error code.
            #The first check within the condition below: indecesR[x]+1 != len(chemLine), ensures that an illegal memory search isn't performed.
            elif(indecesR[x]+1 != len(chemLine) and (chemLine[indecesR[x] + 1].isdigit() or chemLine[indecesR[x] + 1].isalpha() or chemLine[indecesR[x] + 1] == '>')):
                return num


    #return 0 if no error was found
    return 0




#check if element is in substring...                                                                                                               
def inSubstring(el, substring):


    #check if el is length 2...                                                                                                                    
    if(len(el) == 2):
        if(el in substring):
            return substring.index(el)
        else:
            return -1
    else:
        for x in range(len(substring)):
            if(substring[x] == el and x+1 != len(substring) and not(substring[x+1].islower())):

                return x

            elif(substring[x] == el and x+1 == len(substring)):

                return x

        return -1


#Perform the process of balancing the chemical equation given
#by the user...
def balanceEquation(equation):

    #get string value of text box
    chem = equation
              
    #Perform initial security check
    #first to see if the chemical equation
    #provided by the user is valid...
    code,arrName = EquationWrong(equation)

    #If any errors are present within the chemical equationo, EquationWrong() above will return an error code value
    #to the code variable.
    if(code == -3 or code == -2 or code == -1 or code == 1 or code == 2 or code == 3 or code == 4 or code == 5 or code == 6 or code == 7 or code == 8 or code == 9 or code == 10 or code == 11 or code == 12):

        #All of the following blocks are didicated to error code conditions and
        #Their associated messages...
        if(code == -3):
            print("Can't have more than one reaction symbol: ->. Try Again!")
        elif(code == -2):
            print("Missing + and/or -> components! Try Again!\nIf + and/or -> are missing, it is not a valid chemical reaction.")
        elif(code == -1):
            print("There is a coefficient present before a element/molecule and/or inapropriate placement of '+', '-', and/or '>' characters. Try Again!")
        elif(code == 1):
            print("Incomplete chemical equation. Try Again!")
        elif(code == 2):
            print("Either the number of parentheses of each type are unbalanced (there must be the same # of ( and ) parenthesese) or the parenthesese of each type are not paired correctly -> (pair). Try Again!")
        elif(code == 3):
            print("Invalid Element Input! Try Again!")
        elif(code == 4):
            print("Either the number of brackets of each type are unnbalanced (there must be the same # of [ and ] brackets) or the brackets of each type are not paired correctly -> [pair]. Try Again!")
        elif(code == 5):
            print("Parenthese pair contents is incorrect. Try Again!")
        elif(code == 6):
            print("Parenthese pair positioning is incorrect. Try Again!")
        elif(code == 7):
            print("Bracket pair contents is incorrect. Try Again!")
        elif(code == 8):
            print("Bracket pair positioning is incorrect. Try Again!")
        elif(code == 9):
            print("Parenthese pair has no contents. Try Again!")
        elif(code == 10):
            print("Incorrect use of Parenthese. There should be a subscript after the right parenthese. For instance:\nCu3(PO4)2")
        elif(code == 11):
            print("Bracket pair has no contents. Try Again!")
        elif(code == 12):
            print("This is an invalid equation due to individual elements not appearing on both sides of the equat\
ion. Try Again!")

        #exit function after correct error code message has been
        #displayed
        return

  
    #get all indeces of '+' in the chemical equation....

    #substring will hold all of the element/compound segments that
    #exist in betweeen '+' and '->' symbols...
    substring = []

    #holds the indeces of all '+' characters
    indeces = []

    #Used for pulling substrings that are between
    #the '+' and '->' symbols
    countMe = 0

    #Get all indeces associatedd with the '+'
    #characters.
    for g in range(len(chem)):
        if(chem[g] == '+' or chem[g] == '-'):
            if(chem[g - 1] != '['):
                indeces.append(g)

    #now extract the substrings and append them
    #to the list associated with the substring variable.
    for g in range(len(indeces) + 1):
        if(countMe == 0):
            substring.append(chem[:indeces[g]])
            countMe = indeces[g]
        elif(g < len(indeces)):
            substring.append(chem[countMe:indeces[g]])
            countMe = indeces[g]
        else:
            substring.append(chem[countMe:])

    #The number of rows present within the
    #coefficient matrix be the same as the number of
    #unique elements present within the chemical equation.
    rows = len(arrName)

    #make sure to account for charges
    #(a row is reserved for all charges)
    if('[' in chem):
        rows += 1

    #The number of substrings extracted from
    #the chemical equation will be the same as the
    #number of columns needed within the coefficient matrix.
    columns = len(substring)

    #initial matrix template
    matrix = [[]] * rows
        
    #Insert all collumns into the matrix template
    for x in range(rows):
        matrix[x] = [0] * columns


    #now create the matrix... But first add all values:

    #Right now we only care about the values associated
    #with elements. Reduce the row variable for now if charges
    #are present.

    #initialize tempRow with None
    tempRow = None
    
    if('[' in chem):
        tempRow = rows - 1
    else:
        tempRow = rows

    #look over elements first
    for x in range(tempRow):

        #Get an element symbol from
        #the arrName list
        el = arrName[x]

        #Used to indiciate if the products portion of the
        #chemical equation has been reached (after the '->' symbol)...
        flag9 = 0

        #Add values to each column for the
        #corresponding row...
        for k in range(columns):
                
            #Enter this block if the element is within one of the
            #pulled substrings...
            nindex = inSubstring(el, substring[k])
            if(el in substring[k]):

                #enter this block if the element symbol is only one capital letter.
                if(len(el) == 1):

                    #Detect if a digit comes after the element symbol. If so, assign that digit value to the matrix cell
                    if((nindex + 1 != len(substring[k])) and substring[k][nindex + 1].isdigit()):

                        #Get the entire subscript...
                        #First get an even smaller substring
                        sty = substring[k][nindex + 2:]
                        
                        #now based on the smaller substring, extract the whole subscript
                        #(it most likely will only be one digit, but it could be more)
                        subscript2 = substring[k][nindex + 1]
                        for gh in range(len(sty)):

                            #check if the current element is a digit, and if so,
                            #append it to subscript2
                            if(sty[gh].isdigit()):

                                #append the digit to subscript2
                                subscript2 += sty[gh]

                            #if the element is not a digit, then the end of all subscript
                            #recording is done...
                            else:

                                #break out of the for loop
                                break

                        #once '->' has been passed, all subscript values must
                        #be multiplied by negative one.
                        if(('>' in substring[k]) or flag9 == 100):
                            matrix[x][k] = -1 * int(subscript2)
                            if(flag9 == 0):
                                flag9 = 100
                        
                        #If '->' has not been passed, assign the positive value
                        #to matrix...
                        else:
                            matrix[x][k] = int(subscript2)

                    #If not digit is detected after the element symbol, assign a value of
                    #positive or negative one...
                    else:
                        if('>' in substring[k] or flag9 == 100):
                            matrix[x][k] = -1
                            if(flag9 == 0):
                                flag9 = 100
                        else:
                            matrix[x][k] = 1

                #If an element made of two letters (one capital and one lowercase), move two elements ahead in order to
                #begin getting the subscript...
                else:

                    #Detect if a digit comes after the element symbol, and if so, assing that value to the matrix...
                    if((nindex + 2 != len(substring[k])) and substring[k][nindex + 2].isdigit()):

                        #Get the entire subscript...
                        #First get an even smaller substring
                        sty = substring[k][nindex + 3:]
                        
                        #now based on the smaller substring, extract the whole subscript
                        #(it most likely will only be one digit, but it could be more)
                        subscript3 = substring[k][nindex + 2]
                        for gh in range(len(sty)):

                            #check if the current element is a digit, and if so,
                            #append it to subscript2
                            if(sty[gh].isdigit()):

                                #append the digit to subscript2
                                subscript3 += sty[gh]

                            #if the element is not a digit, then the end of all subscript
                            #recording is done...
                            else:

                                #break out of the for loop
                                break

                        #If the '->' symbol has been passed,
                        #assign the subscript value multiplied by -1
                        if('>' in substring[k] or flag9 == 100):
                            matrix[x][k] = -1 * int(subscript3)
                            if(flag9 == 0):
                                flag9 = 100

                        #assign the positive version of the subscript if
                        #the '->' symbol has not been passed...
                        else:
                            matrix[x][k] = int(subscript3)

                    #assign a value of one or negative one if no
                    #digit is found after the element symbol...
                    else:
                        if('>' in substring[k] or flag9 == 100):
                            matrix[x][k] = -1
                            if(flag9 == 0):
                                flag9 = 100
                        else:
                            matrix[x][k] = 1
                
                #make sure to incorporate digit after parenthese if any
                #for instance: (H2SO4)2

                #first make sure that the element is actually within the parenthesis
                if(')' in substring[k]):

                    #check if the location of the element symbol is within the bounds of the parenthese pair...
                    if((nindex > substring[k].index('(')) and (nindex < substring[k].index(')'))):

                        #Get the entire subscript...
                        #First get an even smaller substring
                        stm = substring[k][substring[k].index(')') + 1:]
                        
                        #now based on the smaller substring, extract the whole subscript
                        #(it most likely will only be one digit, but it could be more)
                        subscript4 = ""
                        for gh in range(len(stm)):

                            #check if the current element is a digit, and if so,
                            #append it to subscript2
                            if(stm[gh].isdigit()):

                                #append the digit to subscript2
                                subscript4 += stm[gh]

                            #if the element is not a digit, then the end of all subscript
                            #recording is done...
                            else:

                                #break out of the for loop
                                break

                        #assign the subscript4 value to the matrix cell...
                        matrix[x][k] = matrix[x][k] * int(subscript4)
                
            #Make sure to indicate if a crossover from the ractants to
            #the products side of the chemical equation ahs been reached
            #by assigning the flag9 variable the value 100.
            else:
                if('>' in substring[k]):
                    flag9 = 100
    
    #Now look over the charges
    if('[' in chem):

        #reset the flag9 variable
        flag9 = 0

        #go over each substring..
        for y in range(columns):

            #Assign a charge value to the matrix if brackets
            #are present...
            if('[' in substring[y]):

                #Receive the charge value within the bracket pair...
                Megatron = int(substring[y][substring[y].index('[') + 1:substring[y].index(']')])

                #Make megatron a negative value if '->' has been passed...
                if('>' in substring[y] or flag9 == 100):
                    matrix[rows-1][y] = Megatron * -1
                    if(flag9 == 0):
                        flag9 = 100

                #Leave megatron as a positive value if '->' has not
                #been passed...
                else:
                    matrix[rows-1][y] = Megatron

            #assign 100 to flag9 if '->' is passed...
            elif('>' in substring[y]):
                flag9 = 100

    #turn 2d array represented by the matrix variable 
    #into a sympy matrix...
    matrix = sympy.Matrix(matrix)
    
    #now balance the equation
    reduced = matrix.rref()
    
    #check if solving is possible
    if(IsUnbalanceable(reduced,rows,columns)):
        print("Equation is unbalanceable.\nThis is most likely due to a mistyped/missing subscript or charge, but look for mistyped/missing elements too.\nGo over your chemical equation and try again. If there are more unique elements than there are reactants+products (a difference of two or more), it is possible that the equation is still solvable; the reason why it came back false is possibly because more than one free variable was detected. In the case of more than one free variable when balancing equations, the linear algebra method is no longer accurate.")
        return

    #Provide the balanced equation...
    else:

        #get individual equations from matrix
        arrEquations = []

        #create a blank equation variable
        equ = ""

        #hold in memory all lower case letters
        alphas = string.ascii_lowercase

        #counter for alphas
        counter = 0
        
        #hold a denominator value wheen necessary
        denominator = None

        #List of denominators
        denominators = []

        #n will be used to access the overall row and y will
        #be used to aid in creating separate equations to be evaluated...
        for n in range(columns * rows):

            #start writing the new equation
            if(reduced[0][n] == 1):
                equ += alphas[counter]+'='
                counter = counter + 1

            #The end of a row has been reached once a negative value
            #has been reached.
            elif(reduced[0][n] < 0):

                #invert the negative value and assign to equation
                equ += str(-1*reduced[0][n])

                #append the equation to the equations
                #structure
                arrEquations.append(equ)

                #reset equation variable
                equ = ""

                #store the inverted negative value in a temp
                #variable...
                temp = str(-1*reduced[0][n])

                #Find the greatest denominator value
                if(denominator == None and '/' in str(reduced[0][n])):
                    index = temp.index('/')
                    denominator = int(temp[index + 1:])
                elif('/' in str(reduced[0][n]) and int(temp[temp.index('/') + 1:]) > denominator):
                    denominator = int(temp[temp.index('/') + 1:])

                #save all denominators within structure so we can find Least common multiple later...
                if('/' in str(reduced[0][n])):
                    denominators.append(int(temp[temp.index('/') + 1:]))

        #find the least common multiple if denominators were present
        if(denominator != None and len(denominators) > 1):
            LCM = denominator
            BarneyStinson = 0
            while(BarneyStinson == 0):
                for x in range(len(denominators)):
                    if(LCM % denominators[x] != 0):
                        break
                    elif(LCM % denominators[x] == 0 and (x + 1 == len(denominators))):
                        BarneyStinson = 10
                        break
                if(BarneyStinson == 0):
                    LCM += 1

            denominator = LCM

        #setup a new equation variable
        newE = ""

        #If no denominators were present after reduction
        if(denominator == None):
            
            #in the case of no fractions         
            coeff = 0

            #Create the new balanced chemical equation
            for u2 in range(len(list(chem))):
                if(u2 == 0 or (((list(chem)[u2 - 1] == '+' and list(chem)[u2-2] != '[') or list(chem)[u2 - 1] == '>') and coeff != len(arrEquations))):
                    newE += str(arrEquations[coeff][arrEquations[coeff].index('=') + 1:])
                    newE += chem[u2]
                    coeff = coeff + 1
                else:
                    newE += chem[u2]

        #if denominators were present after reduction
        else:

            #in the case of fractions                 
            coeff = 0

            #create the new balanced chemical equation
            for u2 in range(len(list(chem))):
                if(u2 == 0 or (((list(chem)[u2 - 1] == '+' and list(chem)[u2-2] != '[') or list(chem)[u2 - 1] == '>') and coeff != len(arrEquations))):
                    str1 = arrEquations[coeff][arrEquations[coeff].index('=') + 1:]

                    #Make sure to multiply by the value within denominator...
                    if('/' not in str1):
                        newE += str(int(arrEquations[coeff][arrEquations[coeff].index('=') + 1:]) * denominator)
                        newE += chem[u2]

                    #If '/' is in the equation, divide the numerator and denominator and then
                    #multiply by the vale within denominator...
                    else:
                        num1 = str1[:str1.index('/')]
                        num2 = str1[str1.index('/') + 1:]
                        num3 = int((int(num1) / int(num2)) * denominator)
                        if(num3 != 1):
                            newE += str(num3)
                        newE += chem[u2]
                    coeff = coeff + 1
                elif((list(chem)[u2 - 1] == '+' and list(chem)[u2-2] != '[') or list(chem)[u2 - 1] == '>'):
                    newE += str(denominator)
                    newE += chem[u2]
                else:
                    newE += chem[u2]
            
        
    #write new equation to the answer text box
    print("\nAnswer: "+newE)


#Check to see if the chemical equation is balanceable or not
#when given the corresponding coefficient matrix...
def IsUnbalanceable(matrix, rows, columns):

    #check for all zeros in rest of rows and for variable = 0
    if((rows == columns) or (rows == columns - 1)):
        num = FreeOrZero(rows,columns,matrix)
        if(num == 1):
            return 1
        else:
            return 0

    # check if there are two or more free variables right off the bat
    elif((columns - rows) > 1):
        return 1

    #for cases with more rows than columns
    #the last several rows will be full of zeros due to rref()
    #check the matrix as if it were a regular m x m matrix
    elif((rows - columns) >= 1):
       num = FreeOrZero(columns,columns,matrix) 
       if(num == 1):
           return 1
       else:
           return 0






#If another free variable is found or a row
#contains the form, 0 = 1 (indicating there is no solution).
def FreeOrZero(row,column,matrix):

    #both variables below are or counting
    #characteristics that indicate an unbalanceable
    #chemical equation...
    LordVoldemort = 0
    HarryPotter = 0

    #Go through each row, beginning with the last one...
    for t in range(row - 1,0,-1):

        #For each row, go through each column cell...
        for x in range((t * column) - column, t * column):

            #search for another free variable by counting
            #all zeros within the row
            if(matrix[0][x] == 0):
                LordVoldemort = LordVoldemort + 1

            #search for a one within the row...
            elif(matrix[0][x] == 1 or matrix[0][x] != 1):
                HarryPotter = HarryPotter + 1

        #If a whole row of zeros is found or a row with an ending
        #one is found, the equation is unbalnceable; return error code
        #one...
        if(LordVoldemort == column):
            return 1
        elif(HarryPotter == 1):
            return 1

        #reset variables
        LordVoldemort = 0
        HarryPotter = 0

    #No error found, return 0...
    return 0



#get an equation from the user and submit to the balance equation function...
def getEquation():

    #get a chemical equation from the user...
    equation = input("Please type a chemical equation you would like to balance:\n")

    #submit the equation to balanceEquation()
    balanceEquation(equation)
