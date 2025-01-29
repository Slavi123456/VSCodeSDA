/*#include <string>

class Expression
{
public:
    virtual int value() = 0;
};
class ExprConst : Expression
{
public:
    ExprConst(int value) : _value(value) {}
    virtual int value() override { return _value; }

private:
    int _value;
};

class ExprConst : Expression
{
public:
    ExprConst(char op) : _operator(op) {}
    virtual int value() override { return operation(); }
    int operation()
    {
        switch (_operator)
        {
        case '+':
            return _left->value() + _right->value();
        case '-':
            return _left->value() - _right->value();
        case '*':
            return _left->value() * _right->value();
        case '/':
            return _left->value() / _right->value();
        default:
            throw "Invalid _operator in ExprConst::operation";
            break;
        }
    }

private:
    char _operator;
    Expression *_left;
    Expression *_right;
};

class Token
{
private:
    enum TokenType
    {
        None,
        number,
        oper
    };
    TokenType _type;
    std::string _value;
};

Token getTokenType(char ch)
{
    Token result;
    return result;
}

class Tokenizer
{
public:
    Tokenizer(std::string str)
    {
        tokenize(str);
    }
    void tokenize(std::string str)
    {
        for (char ch : str)
        {
            _tokenize.push_back(getTokenType(ch));
        }
    }

private:
    std::vector<Token> _tokenize;
}; */