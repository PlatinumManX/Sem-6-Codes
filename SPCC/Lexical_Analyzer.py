import re
keywords = {
    "int", "float", "double", "char", "if", "else", "while", "for", "return", "void", "main"
    }
operators = {
    "+", "-", "*", "/", "%", "=", "=="
    }
punctuation = {
    "(", ")", "{", "}", "<", ">", ",", ";"
    }

def comments(code):
    code = re.sub(r"//.*", "", code)
    code = re.sub(r"/\*.*?\*/", "", code)
    return code

def token(lexeme):
    if(lexeme in keywords):
        return "Keyword"
    elif(lexeme in operators):
        return "Operator"
    elif(lexeme in punctuation):
        return "Punctuation"
    elif(lexeme.isdigit()):
        return "Number"
    else:
        return "Identifier"
                
def lexical(code):
    code = comments(code)
    lexemes = re.findall(r"[A-Za-z_]\w*|\d+|==|[-+*/<>(){};,=]", code)
    i = 1
    print("S.No\tLexeme\tToken")
    for lexeme in lexemes:
        temp = token(lexeme)
        print(f"{i}\t{lexeme}\t{temp}")
        i=i+1
    
        
with open("SampleCode.C", "r") as file:
    code = file.read()
lexical(code)
          
