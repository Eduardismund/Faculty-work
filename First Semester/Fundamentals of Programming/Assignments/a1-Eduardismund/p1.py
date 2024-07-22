# Solve the problem from the first set here
n=int(input("n="))
def prime(m):
    """
    :param n: number that is interrogated
    :return: False if the number is not prime and True otherwise
    """
    if(m<2):
        return False
    else:
        for i in range(2, m//2+1):
            if(m%i==0):
                return False
    return True
s=0
for p1 in range(2,n):
    if prime(p1) and prime (n-p1):
        p2=n-p1
        print("p1="+str(p1))
        print("p2=" + str(p2))
        break