import sys
import pandas as pd

df = pd.DataFrame()
pathFileToConvert = sys.argv[1]
matrix = []
#pruebas = [150, 200, 250, 500, 1000, 2000, 3000, 20000, 100000, 500000, 1000000, 50000000]
fileTxt = open(pathFileToConvert, 'r')
dataTxt = fileTxt.readlines()
cont = 0

col = []
for line in dataTxt:
    print(line)
    if 'tiempo' in line.lower():
        col.append(line.replace('tiempo: ', '').replace('\n', ''))
        cont += 1

    if cont >= 12:
        cont = 0
        matrix.append(col)
        col = []
    
    

print('len Col', len(matrix[0]))
print('Col', matrix[0])
print('len Fila', len(matrix))
print('Fila', matrix)
df['150'] = [ a[0] for a in matrix]
df['200'] = [ a[1] for a in matrix]
df['250'] = [ a[2] for a in matrix]
df['500'] = [ a[3] for a in matrix]
df['1000'] = [ a[4] for a in matrix]
df['2000'] = [ a[5] for a in matrix]
df['3000'] = [ a[6] for a in matrix]
df['20000'] = [ a[7] for a in matrix]
df['100000'] = [ a[8] for a in matrix]
df['500000'] = [ a[9] for a in matrix]
df['1000000'] = [ a[10] for a in matrix]
df['50000000'] = [ a[11] for a in matrix]
df.to_csv(pathFileToConvert.replace('txt', 'csv'))

