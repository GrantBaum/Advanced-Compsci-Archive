using namespace std;

class Fraction{
    public:
        Fraction(int top, int bottom);
        int getNum() const;
        int getDen() const;
        friend ostream &operator << (ostream &stream, const Fraction &other);
        Fraction operator + (const Fraction & other) const;
        Fraction operator - (const Fraction & other) const;
        Fraction operator * (const Fraction & other) const;
        Fraction operator / (const Fraction & other) const;
        bool operator == (Fraction &other) const;
    private:
        int num; //numerator 
        int den; //denominator
};