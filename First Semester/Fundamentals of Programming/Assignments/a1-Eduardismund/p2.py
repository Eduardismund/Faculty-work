# Solve the problem from the second set here
n1=int(input("n1="))
n2=int(input("n2="))
arr1 = [0,0,0,0,0,0,0,0,0,0]
arr2 = [0,0,0,0,0,0,0,0,0,0]

def digit_split( n, arr ):
    """
    :param n: the number whose digits need to be manipulated
    :param arr: the list in which to each position is overwritten 1 if the corresponding digit appears in the number, or 0 otherwise
    """
    while n > 0:
        arr[int(n % 10)] = 1
        n = n // 10

digit_split(n1,arr1)

digit_split(n2,arr2)

p=True

for i in range(0,10):
    if arr1[i]!=arr2[i]:
        p=False

if p==False:
    print("n1 and n2 DO NOT have the property p")
else:
    print("n1 and n2 have the property p")