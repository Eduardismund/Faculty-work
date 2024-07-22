# Solve the problem from the third set here
n=int(input("n="))
def prime(n):
    """
    :param n: number that is interrogated
    :return: False if the number is not prime and True otherwise
    """
    if(n<2):
        return False
    else:
        for i in range(2, n//2+1):
            if(n%i==0):
                return False
    return True

def factors(a ,b, m):
    """

    :param a: the number I have to take the prime factors from
    :param b: the factor used to divide "a"
    :param m: the nth element that has to be found
    :return: the difference that will become negative or equal to 0 when reached the mth element
    """
    ok= False
    while int(a%b)==0:
            a=a//j
            ok=True
    if ok:
        m=m-j
    return m
i=1

while n>0:
    if i==1 or prime(i)==True:
        n=n-1
        if(n==0):
            t=i
    else:
        for j in range(2, i//2+1):
            if n>=0:
                n=factors(i,j,n)
                if n<=0:
                    t=j
                    break
    i=i+1
print(t)







