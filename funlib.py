def read_file(file_path:str) -> list:
    """
    Abre e varre todo o arquivo. Devolve uma lista com todos todas as linhas, sendo lines[n] a n-ésima linha do arquivo lido.
    """
    try:
        file = open(file_path, 'r') # abre o arquivo
        lines = []
        for line in file: # le linha por linha e adiciona na lista 'lines'
            lines.append(line)
        file.close() # fecha o arquivo
        return lines
    except FileNotFoundError:
        print("Arquivo não encontrado.")
        print("Não encontrado arquivo",file_path)
        raise # exceção

def mount_tokens(lines:list) -> list:
    """
    Escaneia a lista de strings inserida e separa em tokens, função não finalizada.\n
    O jeito que ele trata comentarios é ignorar todos os caracteres até achar outra chave.
    """
    token_list = []
    numOfComments = 0
    for line in lines:
        token = '' # token atual sendo lido 
        for char in line: 
            if char == "}": # se for o fim do comentario
                numOfComments-=1
                if numOfComments < 0:
                    numOfComments = 0
            if char == '\n':
                if token != '':
                    token_list.append(token)
                    token = ''
                else:
                    continue
            elif char != "{" and char != "}" and char != " " and numOfComments == 0:
                token+=char
            elif char == "{":
                numOfComments+=1
            elif char == " ":
                if token != '':
                    token_list.append(token)
                    token = ''
    if token != '':
        token_list.append(token)
    return token_list



lis = read_file('test.txt')
print(mount_tokens(lis))