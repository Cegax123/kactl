double quad(double (*f)(double), double a, double b) {
	const int n = 1000;
	double h = (b - a) / 2 / n;
	double v = f(a) + f(b);
	rep(i,1,n*2)
		v += f(a + i*h) * (i&1 ? 4 : 2);
	return v * h / 3;
}
