#include <iostream>
using namespace std;
struct Node
{
    Node(int Coef, int Power)
    {
        coef = Coef;
        exp = Power;
    }
    int coef;
    int exp;
    Node *link;
};
class polynomial
{
public:
    polynomial()
    {
        first = NULL;
    }
    Node *insertNode(int Coef, int Power);
    polynomial polMultiply(Node *eqt1, Node *eqt2);
    void checkDuplicate(Node *next);
    void displayList(Node *equation);
    Node *getFirst()
    {
        return first;
    }

private:
    Node *first;
};

Node *polynomial::insertNode(int Coef, int Power)
{
    Node *add = new Node(Coef, Power);
    add->link = NULL;
    if (first == NULL)
    {
        first = add;
        return add;
    }
    Node *ptr = first;
    while (ptr->link != NULL)
        ptr = ptr->link;
    ptr->link = add;
    return first;
}
void polynomial::displayList(Node *equation)
{
    while (true)
    {
        if (equation->exp != 0)
            cout << equation->coef << "x^" << equation->exp;
        else
            cout << equation->coef;
        if (equation->link != NULL)
        {
            if (equation->coef < 0)
                cout << '-';
            else
                cout << '+';
        }
        else
            cout << endl;
        equation = equation->link;
    }
}
polynomial polynomial::polMultiply(Node *eqt1, Node *eqt2)
{ // eqt1->put polynomial one's first , eqt2->put polynomial two's first
    polynomial a;
    while (eqt1->link != NULL)
    {
        while (eqt2->link != NULL)
        {
            a.insertNode((eqt1->coef * eqt2->coef), (eqt1->exp + eqt2->exp));
            eqt2 = eqt2->link;
        }
        eqt1 = eqt1->link;
    }
    checkDuplicate(a.getFirst());
    return a;
}
void polynomial::checkDuplicate(Node *next) //->put the first of polynomial(after multiply)
{
    Node *compare;
    while (next->link != NULL)
    {
        compare = next->link;
        while (compare->link != NULL)
        {
            if (next->exp == compare->exp)
            {
                next->coef = next->coef + compare->coef;
                compare->link = compare->link->link;
                delete compare;
            }
            else
                compare = compare->link;
        }
        next = next->link;
    }
}
int main()
{
    polynomial equation, equation2, outcome;
    int coef, pow, m, n;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> coef >> pow;
        equation.insertNode(coef, pow);
    }
    equation.displayList(equation.getFirst());
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> coef >> pow;
        equation2.insertNode(coef, pow);
    }
    outcome.polMultiply(equation.getFirst(), equation2.getFirst());
    outcome.displayList(outcome.getFirst());
}