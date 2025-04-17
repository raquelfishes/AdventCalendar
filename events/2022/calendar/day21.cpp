#include "std_includes.h"
#include "resource.h"
#include "utils.h"

namespace
{
  struct Instruction
  {
    Instruction() = default;
    Instruction(const std::string s)
    {
      std::vector<std::string> values;
      splitStringByChar(s, ' ', values);
      op1 = values[0];
      op2 = values[2];
      op = values[1][0];
    }

    long long resolve(long long v1, long long v2)
    {
      if (op == '=') return v1;
      if (op == '+') return v1 + v2;
      if (op == '-') return v1 - v2;
      if (op == '*') return v1 * v2;
      if (op == '/') return v1 / v2;
    }

    long long getValueToResolve(long long v, int i, long long res)
    {
      if (op == '=') return v;
      if (op == '+') return res - v;
      if (op == '-')
        if (i == 1) return v - res;
        else if (i == 2) return res + v;
      if (op == '*') return res / v;
      if (op == '/')
        if (i == 1) return v / res;
        else if (i == 2) return res * v;
    }


    std::string op1 = "";
    std::string op2 = "";
    char op = ' ';
  };

  struct MonkeyInfo
  {
    MonkeyInfo() = default;
    MonkeyInfo(const std::string& s)
    {
      std::string regExp = "(\\w+): (.*)";
      std::vector<std::string> values;
      splitByRegex(s, regExp, values);
      name = values[1];
      if (isAllDigits(values[2])) value = std::stoi(values[2]);
      else instruction = Instruction(values[2]);

    }
    bool isValidValue() const
    {
      return value != std::numeric_limits<long long>::max();
    }

    void resolve(long long op1, long long op2)
    {
      value = instruction.resolve(op1, op2);
    }
    
    long long getValueToOp(long long op, int index, long long result)
    {
      return instruction.getValueToResolve(op, index, result);
    }

    std::string name = "";
    Instruction instruction;
    long long value = std::numeric_limits<long long>::max();
  };
}

void resolve(const std::string& n, std::map<std::string, MonkeyInfo>& monkeys)
{

  if (monkeys[n].isValidValue()) 
    return;

  resolve(monkeys[n].instruction.op1, monkeys);
  long long op1 = monkeys[monkeys[n].instruction.op1].value;
  resolve(monkeys[n].instruction.op2, monkeys);
  long long op2 = monkeys[monkeys[n].instruction.op2].value;
  monkeys[n].resolve(op1, op2);
}

void day21Part1()
{
  std::vector<MonkeyInfo> input;
  readDocument<MonkeyInfo>(DAY21_PATH, input);

  std::map<std::string, MonkeyInfo> inputMap;
  std::for_each(input.begin(), input.end(), [&inputMap] (const MonkeyInfo& m) { inputMap[m.name] = m; });

  resolve("root", inputMap);

  long long result = inputMap["root"].value;
  printf("The solution for part 1 is: %lli \n", result);
}


void resolveToEq(const std::string& n, const long long eqValue, std::map<std::string, MonkeyInfo>& monkeys, std::stack<std::string>& stackHumn)
{
  if (stackHumn.empty()) return;

  std::string sOp1 = monkeys[n].instruction.op1;
  std::string sOp2 = monkeys[n].instruction.op2;
  std::string sStack = stackHumn.top();
  long long op = 0;
  int index = 0;
  if (sOp1 == sStack)
  {
    resolve(sOp2, monkeys);
    op = monkeys[sOp2].value;
    index = 2;
  }
  if (sOp2 == sStack)
  {
    resolve(sOp1, monkeys);
    op = monkeys[sOp1].value;
    index = 1;
  }

  long long aux = monkeys[n].getValueToOp(op, index, eqValue);
  monkeys[sStack].value = aux;
  stackHumn.pop();
  resolveToEq(sStack, aux, monkeys, stackHumn);
  
}

void stackToHumn(const std::string& n, const std::map<std::string, MonkeyInfo>& monkeys, std::stack<std::string>& stackHumn)
{
  if (n == "humn")
  {
    stackHumn.push(n);
    return;
  }

  std::string sOp1 = monkeys.at(n).instruction.op1;
  std::string sOp2 = monkeys.at(n).instruction.op2;
  if (sOp1.empty() || sOp2.empty()) return;
  
  stackToHumn(sOp1, monkeys, stackHumn);
  stackToHumn(sOp2, monkeys, stackHumn);

  if (!stackHumn.empty() && ( sOp1 == stackHumn.top() || sOp2 == stackHumn.top() ))
  {
    stackHumn.push(n);
    return;
  }


}

void day21Part2()
{
  std::vector<MonkeyInfo> input;
  readDocument<MonkeyInfo>(DAY21_PATH, input);
  
  std::map<std::string, MonkeyInfo> inputMap;
  std::for_each(input.begin(), input.end(), [&inputMap] (const MonkeyInfo& m) { inputMap[m.name] = m; });
  std::stack<std::string> stackHumn;

  inputMap["root"].instruction.op = '=';
  stackToHumn("root", inputMap, stackHumn);


  if (stackHumn.top() == "root") stackHumn.pop();

  resolveToEq("root", 0, inputMap, stackHumn);
  
  long long result = inputMap["humn"].value;
  printf("The solution for part 2 is: %lli \n", result);
}
