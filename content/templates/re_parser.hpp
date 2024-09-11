const int MAXL = 1e5+5;
char input[MAXL];
int pos;
double expr();
double term();
double fact();
double number();
#define SIGN(c) ( (c) == '+' ? 1 : -1 ) 
double expr() {
    double RES = term();
    while(input[pos] == '+' || input[pos] == '-') {
        double sign = SIGN(input[pos++]);
        RES += sign * term();
    }
    return RES;
}
#define OPER(c) ( (c) == '*' ? true : false )
double term() {
    double RES = fact();
    while(input[pos] == '*' || input[pos] == '/') {
        bool oper = OPER(input[pos++]);
        if(oper) RES *= fact();
        else RES /= fact();
    }
    return RES;
}
double fact() {
    double RES;
    if(input[pos] == '(') {
        pos++;
        RES = expr();
        pos++;
    }
    else
        RES = number();
    return RES;
}
#define ISVALID(c) ( (c) == '.' ? true : ((c) >= '0' && (c) <= '9') )
double number() {
    double RES;
    string tmp = "";
    while(ISVALID(input[pos])) tmp += input[pos++];
    sscanf(tmp.c_str(), "%lf", &RES);
    return RES;
}
