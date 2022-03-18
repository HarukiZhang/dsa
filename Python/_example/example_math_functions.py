def factorial(n):
    res = 1
    while n > 1:
        res *= n
        n -= 1
    return res

def isprime(n, opt_idx=False):
    assert isinstance(n, int), 'Non-integer Error'
    assert n > 0, 'Minus-value Error'
    if n == 1:
        res, idx = False, n
    elif n == 2 or n == 3:
        res, idx = True, n
    else:
        for idx in range(2, int(n**0.5) + 1):
            if n%idx == 0:
                res = False
                break
            res = True
    if opt_idx:
        return res, idx
    return res

def factorize(n):
    assert isinstance(n, int), 'Non-integer Error'
    if n == 0 or abs(n) == 1:
        return [1, n]
    else:
        idx = isprime(abs(n), opt_idx=True)
        if idx[0]:
            return [1, n]
        else:
            res = [idx[1], n//idx[1]]
            last = res[-1]
            if not isprime(abs(last)):
                a = factorize(last)
                res[-1] = a[0]
                for factor in a[1:]:
                    res.append(factor)
            return res

def reduction_for_compo(numer, denom):
    fd_numer, fd_denom = {}, {}
    for nume in numer:
        for factor in factorize(nume):
            fd_numer[factor] = fd_numer.get(factor, 0) + 1
    for deno in denom:
        for factor in factorize(deno):
            fd_denom[factor] = fd_denom.get(factor, 0) + 1
    for key in fd_numer:
        if key in fd_denom:
            if fd_numer[key] > fd_denom[key]:
                fd_numer[key] -= fd_denom[key]
                fd_denom[key] = 0
            else:
                fd_denom[key] -= fd_numer[key]
                fd_numer[key] = 0
    fin_numer = fin_denom = 1
    for key in fd_numer:
        fin_numer *= key**fd_numer[key]
    for key in fd_denom:
        fin_denom *= key**fd_denom[key]
    return fin_numer / fin_denom

def compo(k, n):
    assert isinstance(k, int) and isinstance(n, int)
    assert k > -1 and n > 0 
    assert k <= n
    if k == 0 or k == n:
        return 1
    else:
        if k >= n-k:
            numer = [nu for nu in range(k+1, n+1)]
            denom = [de for de in range(1, n-k+1)]
            return int(reduction_for_compo(numer, denom))
        else:
            numer = [nu for nu in range(n-k+1, n+1)]
            denom = [de for de in range(1, k+1)]
            return int(reduction_for_compo(numer, denom))

def univ_quad_eqn_solver(a:int, b:int, c:int):
    assert a != 0, "a == 0"
    bsq = b*b
    ac4 = 4*a*c
    if bsq < ac4:
        res_imag = abs(bsq-ac4)**(0.5)/2/a
        res_real = -b/2/a
        print(f'x1={res_real:.5f}+{res_imag:.5f}i;x2={res_real:.5f}-{res_imag:.5f}i')
    elif bsq == ac4:
        x1 = -b/2/a
        print(f'x1=x2={x1:.5f}')
    else:
        x1 = (-b + (bsq - ac4)**(0.5))/2/a
        x2 = (-b - (bsq - ac4)**(0.5))/2/a
        print(f'x1={x1:.5f};x2={x2:.5f}')