#include <string>
#include <stack>
#include <iostream>



bool BalancedParentheses(std::string parentheses, int *pos)
{
	std::stack<int> stk;
	const int kLeftPar = 1;
	int i;
	for (i = 0; i < parentheses.size(); ++i)
	{
		if (parentheses[i] == '(')
		{
			stk.push(kLeftPar);
		}
		else
		{
			if (stk.empty())
			{
				*pos = i;
				return false;
			}
			else
			{
				stk.pop();
			}
		}
	}
	if (!stk.empty())
	{
		*pos = --i;
		return false;
	}
	return true;

}


int main()
{
	std::string str = "((()))(())";
	int pos = 0;
	bool b = BalancedParentheses(str, &pos);
	std::cout << b << pos << std::endl;
	system("pause");
	return 0;
}