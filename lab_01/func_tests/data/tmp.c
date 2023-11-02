

MAX N = 10 sequence[MAX_N] CNT = 0 func print_chars(n)
{
    if (++CNT < 4)
        return for (i = 0; i < n; ++i)
            print(sequence[i])
                print("\n")
                    exit(0)
}
func gen(i, n, k)
{
    if (i == n)
    {
        print_chars(n)
    }
    return sequence[i] = '(' if (n - i >= k + 1)
               gen(i + 1, n, k + 1)
                   sequence[i] =
                       ')' if (k > 0)
                           gen(i + 1, n, k - 1)
}
gen(0, 6, 0)