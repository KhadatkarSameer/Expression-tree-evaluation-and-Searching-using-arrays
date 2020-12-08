#include <iostream>
#include <stack>
#include <string>
#include <cstddef>
#include <limits>

using namespace std;


/**
 * Class containing the data and functions for a single node in an expression tree
 *
 * @param type - stores the type of the node, it can either be {0 : (operator), 1: (operand)}
 * @param operator_ - stores the operator, values can be {+, -, *, /}. Present only if type is 0
 * @param operand_ - stores the operand, the value is a non-negetive integers. Present only if type is 1
 * @param left - link to the left child of the node
 * @param right - link to the right child of the node
*/
class ExprNode {
private:
	int type;
	char operator_;
	unsigned int operand_;
	ExprNode *left, *right;

public:
	/* Constructor definitions */
	ExprNode(unsigned int operand) {
		type = 1;
		operand_ = operand;
		operator_ = 0;
		left = NULL;
		right = NULL;
	}

	ExprNode(char op) {
		if (op == '+' || op == '-' || op == '*' || op == '/') {
			type = 0;
			operator_ = op;
			left = NULL;
			right = NULL;
		} else {
			throw invalid_argument("Invalid operator");
		}
	}

public:
	/* validates an operator */
	bool isOperator(ExprNode* r)
	{
	    if (r->type==0)
	    {return true;}
		else
		{return false;}
	}

	/* get operator value */
	char getOperator(ExprNode* r) {return r->operator_;}

	/* get operand value */
	unsigned int getOperand(ExprNode* r) {return r->operand_;}

    /* get left child */
	ExprNode* getLeft(ExprNode* r)	{return r->left;}


	/* get right child */
	ExprNode* getRight(ExprNode* r)	{return r->right;}

	/* set left child */
	void setLeft(ExprNode* l) { this->left=l;}

	/* set right child */
	void setRight(ExprNode* r) { this->right=r;}
};

/**
 * Function to construct infix tree from expression
 *
 * @param exp - string expression for which tree is to be constructed
 * @return node - returns root to infix expression tree
*/
ExprNode* buildInfixTree(string exp)
{
	stack<char> check_b , check_operator ;
	stack<ExprNode*> check_operand;         /*for storing nodes*/
    for(int i=0;i<exp.size();i++)
    {
        if (exp[i] == '(')
            check_b.push(exp[i]);

        else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/')
            check_operator.push(exp[i]);

        else if (exp[i]>='0' && exp[i]<='9')
        {
            unsigned int num=0;
            int count=0;
            while(i<exp.size() && exp[i]>='0'&& exp[i]<='9') /*if operands are not single digit*/
            {
                unsigned int y=(unsigned int)exp[i]-'0';
                num=num*10+y;
                count++;
                i++;
            }

            ExprNode* node=new ExprNode(num);
            check_operand.push(node);
            if(count!=0)
                i--;
        }

        else if (exp[i] == ')')  /*takes two operands from the check_operand stack and make a new node with operator in check_operator stack*/
        {
            ExprNode* node=new ExprNode(check_operator.top());
            check_operator.pop();
            node->setRight(check_operand.top());
            check_operand.pop();
            node->setLeft(check_operand.top());
            check_operand.pop();
            check_b.pop();
            check_operand.push(node);
        }

    }

	return check_operand.top();
}

/**
 * Function to print pre order traversal for infix expression tree
 *
 * @param root - reference to the root of the infix tree
 * @returns - resultant expression string after pre order traversal
*/
namespace global
{
  string preres=""; /*for storing preorder result*/
  stack<string> expst; /*for storing preorder stack*/
}


string doPreOrder(ExprNode* r)
{
    if(r->isOperator(r))
    {
        char str=r->getOperator(r);
        global::preres+=str;
        global::preres+=" ";
    }
    if(!r->isOperator(r))
    {
        int a=r->getOperand(r);
        string str = to_string(a);
        global::preres+=str;
        global::preres+=" ";
    }
    if(r->getLeft(r)!=NULL)
    {
        doPreOrder(r->getLeft(r));
    }
    if(r->getRight(r)!=NULL)
    {
        doPreOrder(r->getRight(r));
    }
    return global::preres;
}

void PreOrderStack(ExprNode* r)
{
    if(r->isOperator(r))
    {
        char op=r->getOperator(r);
        string str(1,op);
        global::expst.push(str);
    }
    else if(!r->isOperator(r))
    {
        int a=r->getOperand(r);
        string str = to_string(a);
       
        global::expst.push(str);
    }
    if(r->getLeft(r)!=NULL)
    {
        PreOrderStack(r->getLeft(r));
    }
    if(r->getRight(r)!=NULL)
    {
        PreOrderStack(r->getRight(r));
    }
}
/**
 * Function to evaluate the expression tree using stacks
 *
 * @param root - reference to the root of the infix tree
 * @returns - result after expression is evaluated
*/
int getIntMin()
{
	return numeric_limits<int>::min();
}

int evaluate(ExprNode* root) 
{
    PreOrderStack(root);
    stack<int> eval_stack;
    int size=global::expst.size();
    for(int i=0;i<size;i++)
    {
        string x=global::expst.top();
        global::expst.pop();
        char y=x[0];
        if(y=='+'||y=='-'||y=='*'||y=='/')
        {
            int a , b , value, Max=numeric_limits<int>::max(); /*Max for checking division by Zero*/
            if(!eval_stack.empty())
            {
                a=eval_stack.top();
                eval_stack.pop();
            }
            if
            (!eval_stack.empty())
            {
                b=eval_stack.top();
                eval_stack.pop();
            }
            if(y=='+')
            {
                if(a==Max || b==Max)
                value=Max;
                else
                value=a+b;
            }
            else if(y=='-')
            {
                if(a==Max || b==Max)
                value=Max;
                else
                value=a-b;
            }
            else if(y=='*')
            {
                if(a==Max || b==Max)
                value=Max;
                else
                value=a*b;
            }
            else if(y=='/')
            {
                if(b==0|| a==Max || b==Max)
                value=Max;
                else 
                value=a/b;
            }
            eval_stack.push(value);
        }
        else
        {
            eval_stack.push(stoi(x)); 
        }
        
    }
    int result=eval_stack.top();
    eval_stack.pop();
    return result;
}



/**
 * Checks whether a given
 * expression is a valid mathematical expression
 *
 * @param exp - expression string to be validated
 * @returns - true if the expression is valid, false otherwise
*/
bool isValid(string exp)
{
    stack<char> st_b,st_operator,st_operand;  /*st_b for checking brackets*st_operator for checking operators*st_operand for checking operands */
    for(int i=0;i<exp.size();i++)
    {
        if(exp[i]=='(')
        st_b.push(exp[i]);
        
        else if(exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/')
        st_operator.push(exp[i]);
        
        else if(exp[i]>='0' && exp[i]<='9')
        {
            st_operand.push(0);
            while(i<exp.size() && exp[i]>='0' && exp[i]<='9')
            {
                i++;
            }
            i--;
        }
        
        else if(exp[i]==')' && !st_operand.empty())
        {
            if(!st_operator.empty() && !st_b.empty() )
            {
                st_operand.pop();
                if(!st_operand.empty())
                {
                    st_operator.pop();
                    st_operand.pop();
                    st_b.pop();
                    st_operand.push(0);
                }
            }
        }

    }
    
    
    if(st_operator.empty() && st_b.empty() && st_operand.size()==1)
    return true;
    else
    return false;

}

/**
 * Function to print output to console
 * @param result - result from evaluating validity of expression
 */
void printResultA(bool result) {
	cout << "A1a:" << (result ? "true" : "false") << endl;
}

/**
 * Function to print output to console
 * @param result - expression from the pre order traversal
 */
void printResultB(string result) {
	cout << "A1b:" << result << endl;
}

/**
 * Function to print output to console
 * @param result - result after evaluation of expression
 */
void printResultC(int result) {
    if (result!=numeric_limits<int>::max())
	cout << "A1c:" << result << endl;
	else
	cout << "A1c:" << "NA(Division by Zero)" << endl;
}

int main() {
	/* Expression string */
	string exp;

	/* Input taken from console */
	getline(cin, exp);

	/**
     * QUESTION 1 - PART A
     *
     * Check if the given expression is a valid mathematical expression
    */

	/* Validate expression */
	bool check = isValid(exp);

	/* Printing result to console */
	printResultA(check);

	/**
     * QUESTION 1 - PART B
     *
     * Build an infix expession tree for the given expression and
     * print the result of a pre order traversal on the expression tree
     *
     * Root : must be an operator
     * Left-subtree: sub expression
     * Right-subtree: sub expression
     * Leaves: integer operands
     *
    */
    if(check)
    {
	    /* Construct infix expression tree */
	    ExprNode *root = buildInfixTree(exp);
        /* Print pre order traversal */
	    string preOrderResult = doPreOrder(root);
	    printResultB(preOrderResult);
	    /**
        * QUESTION 1 - PART C
        *
        * Check if the given expression is a valid mathematical expression
        */
    
	    /* Evaluate infix expression tree */
	    /* Printing result to console */
	    int result = evaluate(root);
	    printResultC(result);

	    
	    
    }
    
    else
    {
        printResultB("NA");
        printResultC(getIntMin());
    }
	return 0;
}
